#include "heleris/fw/gl_context.h"

#include "heleris/fw/errors/error.h"
#include "heleris/fw/errors/error_codes.h"
#include "heleris/fw/errors/error_presets.h"
#include "heleris/fw/graphics/device_graphics.h"
#include "heleris/fw/window.h"

#include "heleris/fw/math/math.h"

#include <stdlib.h>

// Private fields:

bool hasBeenInitialized = false;

void hrsglc_glfwResizeCallback(GLFWwindow *window, int width, int height) {

    HRSWindow* hrsWindow = (HRSWindow*)glfwGetWindowUserPointer(window);

    if (hrsWindow != nullptr && hrsWindow->onWindowResize != nullptr) {

        if (width == hrsWindow->minimumSize.width && height == hrsWindow->minimumSize.height) {

            HRSSize newSize = { width, height };
            hrsWindow->_size = newSize;
            return;
        }

        if (width < hrsWindow->minimumSize.width || height == hrsWindow->minimumSize.height) {

            glfwSetWindowSize(window, HRS_MAX(width, hrsWindow->minimumSize.width), HRS_MAX(height, hrsWindow->minimumSize.height));
            return;
        }

        HRSSize newSize = { width, height };
        hrsWindow->_size = hrsWindow->onWindowResize(hrsWindow, newSize);
        glViewport(0, 0, hrsWindow->_size.width, hrsWindow->_size.height);
    }
}

// Plublic fields:

// Heap manipulation

HRSGLContext* hrsglc_create(const enum EHRSMajorVersion _majorVersion, const int minorVersion, const enum EHRSProfileType _profileType) {

    if (hasBeenInitialized != false) {

        HRSError _error = {"attemp to create another type of \"HRSGLContext\"", "theres an attemp to create another \"HRSGLContext\" without finish other", HRS_ERROR_HRSGLC_ALREADY_INITIALIZED};
        hrserr_printAndStopProgram(&_error);
    }

    HRSGLContext *_glContext = malloc(sizeof(HRSGLContext));

    if (_glContext == nullptr) 
        errpre_malloc("HRSGLContext");

    if (_majorVersion == HRS_GL_MAJOR_THREE && minorVersion < 3)
        errpre_invalidArgument("int minorVersion (minimum version with HRS_GL_MAJOR_TREE is 3)");

    _glContext->_majorVersion = _majorVersion;
    _glContext->minorVersion = minorVersion;
    _glContext->_profileType = _profileType;
    _glContext->hasBeenInitialized = false;
    _glContext->useVSync = false;
    _glContext->swapCooldown = 1.0 / 60.0; 
    _glContext->fps = 0;
    _glContext->window = nullptr;
    _glContext->draw = nullptr;
    _glContext->onUpdate = nullptr;

    return _glContext;
}

void hrsglc_init(HRSGLContext *_glContext, HRSWindow *window) {

    if (_glContext == nullptr)
        errpre_nullptr("HRSGLContext");

    if (_glContext->hasBeenInitialized || hasBeenInitialized != false) {

        HRSError _error = {"attempt to reinitialize GLFW and GLAD", "there was an attempt to reset GLFW and GLAD, which may cause errors."
            " \nAvoid having more than one object of type \"HRSGLContext\"", HRS_ERROR_HRSGLC_ALREADY_INITIALIZED};
        hrserr_printAndStopProgram(&_error);
    }

    if (!glfwInit()) {

        HRSError _error = {"GLFW can't init", "unable to start GLFW, check your operating system", HRS_ERROR_GLFW_CANT_INIT};
        hrserr_printAndStopProgram(&_error);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _glContext->_majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _glContext->minorVersion);

    glfwWindowHint(GLFW_OPENGL_PROFILE, _glContext->_profileType);

    if (window == nullptr)
        errpre_nullptr("HRSWindow");

    _glContext->window = window;

    hrswin_init(_glContext->window);

    glfwSetFramebufferSizeCallback(window->_glfwWindow, hrsglc_glfwResizeCallback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

        HRSError _error = {"GLAD can't init", "GLAD can't get the correct address of OpenGL functions", HRS_ERROR_GLAD_CANT_FIND_IMPLEMENTATIONS};
        hrserr_printAndStopProgram(&_error);
    }

    glfwSwapInterval(_glContext->useVSync);

    hasBeenInitialized = true;
    _glContext->hasBeenInitialized = true;
}

void hrsglc_assert(const HRSGLContext *_glContext) {
    
    if (_glContext == nullptr) 
        errpre_nullptr("HRSGLContext");

    if (_glContext->hasBeenInitialized != true || hasBeenInitialized != true) {

        HRSError _error = {"GLFW and GLAD not initialized", "attempt to use an object of type HRSGLContext without initializing GLAD or GLFW", HRS_ERROR_HRSGLC_NOT_INITIALIZED};
        hrserr_printAndStopProgram(&_error);
    }
}

void hrsglc_terminate(HRSGLContext *_glContext) {

    hrsglc_assert(_glContext);
    
    hrswin_free(_glContext->window);
    
    free(_glContext);

    glfwTerminate();

    hasBeenInitialized = false;

    _glContext = nullptr;
}

// Call backs

void hrsglc_registerUpdatePreFixedCallback(HRSGLContext *_glContext, void (*onUpdatePreFixed)(HRSGLContext *_glContext, double deltaTime)) {

    hrsglc_assert(_glContext);

    if (onUpdatePreFixed == nullptr)
        errpre_nullptr("void (*onUpdatePreFixed)(HRSGLContext *_glContext, double deltaTime)");

    _glContext->onUpdatePreFixed = onUpdatePreFixed;
}

void hrsglc_registerFixedUpdateCallback(HRSGLContext *_glContext, void (*onFixedUpdate)(HRSGLContext *_glContext, double fixedDeltaTime)) {

    hrsglc_assert(_glContext);

    if (onFixedUpdate == nullptr)
        errpre_nullptr("void (*onFixedUpdate)(HRSGLContext *_glContext, double fixedDeltaTime)");

    _glContext->onFixedUpdate = onFixedUpdate;
}

void hrsglc_registerUpdateCallback(HRSGLContext *_glContext, void (*onUpdate)(HRSGLContext *_glContext, double deltaTime)) {

    hrsglc_assert(_glContext);

    if (onUpdate == nullptr)
        errpre_nullptr("void (*onUpdate)(HRSGLContext *_glContext, double deltaTime)");

    _glContext->onUpdate = onUpdate;
}

void hrsglc_registerFixedPostUpdateCallback(HRSGLContext *_glContext, void (*onFixedPostUpdate)(HRSGLContext *_glContext, double fixedDeltaTime)) {

    hrsglc_assert(_glContext);

    if (onFixedPostUpdate == nullptr)
        errpre_nullptr("void (*onFixedPostUpdate)(HRSGLContext *_glContext, double fixedDeltaTime)");

    _glContext->onFixedPostUpdate = onFixedPostUpdate;
}

void hrsglc_registerDrawCallback(HRSGLContext *_glContext, void (*draw)(HRSGLContext *_glContext, HRSDeviceGraphics deviceGraphics)) {

    hrsglc_assert(_glContext);

    if (draw == nullptr)
        errpre_nullptr("void (*draw)(HRSGLContext *_glContext, HRSDeviceGraphics deviceGraphics)");

    _glContext->draw = draw;
}

// Context struct sets

void hrsglc_cycleCooldown(HRSGLContext *_glContext, const double cooldown) {

    hrsglc_assert(_glContext);

    _glContext->swapCooldown = cooldown;
}

void hrsglc_startLoop(HRSGLContext *_glContext) {

    hrsglc_assert(_glContext);

    hrswin_assert(_glContext->window);

    double previousTime = glfwGetTime();
    double previousFixedTime = glfwGetTime();
    double currentTime;

    double deltaTime;
    double fixedDeltaTime;

    double fixedDeltaAccumulator = 0;
    int postFixedCalls = 0;

    double fpsTimer = 0.0;
    int frameCount = 0;

    HRSDeviceGraphics deviceGraphics = hrsdgr_create();

    while(!glfwWindowShouldClose(_glContext->window->_glfwWindow)) {

        currentTime = glfwGetTime();
        deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        fpsTimer += deltaTime;
        frameCount++;

        if (fpsTimer >= 1.0) {

            _glContext->fps = frameCount / fpsTimer;
            fpsTimer -= 1.0;
            frameCount = 0;
        }

        _glContext->estimatedFPS = 1.0 / deltaTime;

        if (_glContext->onUpdatePreFixed != nullptr)
            _glContext->onUpdatePreFixed(_glContext, deltaTime);

        fixedDeltaTime = glfwGetTime() - previousFixedTime;

        fixedDeltaAccumulator += deltaTime;

        while (fixedDeltaAccumulator >= _glContext->swapCooldown) {

            previousFixedTime = glfwGetTime();

            if (_glContext->onFixedUpdate != nullptr) {
                _glContext->onFixedUpdate(_glContext, fixedDeltaTime);
            }

            fixedDeltaAccumulator -= fixedDeltaTime;

            fixedDeltaTime = glfwGetTime() - previousFixedTime;

            postFixedCalls++;
        }

        if (_glContext->onUpdate != nullptr)
            _glContext->onUpdate(_glContext, deltaTime);

        double fixedPostDeltaTime = glfwGetTime() - previousFixedTime;

        double postFixedTime = previousTime;

        while (postFixedCalls > 0) {

            postFixedTime = glfwGetTime();
            
            if (_glContext->onFixedPostUpdate != nullptr)
                _glContext->onFixedPostUpdate(_glContext, fixedPostDeltaTime);

            fixedPostDeltaTime = glfwGetTime() - postFixedTime;

            postFixedCalls--;
        }

        glClearColor(hrsclr_toFloat(_glContext->window->backgroundColor, HRS_COLOR_RGBA_R),
            hrsclr_toFloat(_glContext->window->backgroundColor, HRS_COLOR_RGBA_G),
            hrsclr_toFloat(_glContext->window->backgroundColor, HRS_COLOR_RGBA_B),
            1);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        if (_glContext->draw != nullptr)
            _glContext->draw(_glContext, deviceGraphics);

        glfwSwapBuffers(_glContext->window->_glfwWindow);

        glfwPollEvents();
    }
}

void hrsglc_closeLoop(HRSGLContext *_glContext) {

    hrsglc_assert(_glContext);
    
    hrswin_assert(_glContext->window);

    glfwSetWindowShouldClose(_glContext->window->_glfwWindow, GLFW_TRUE);

    if (_glContext->window->onWindowClose != nullptr)
        _glContext->window->onWindowClose(_glContext->window);
}

// GLContext sets

void hrsglc_vSync(HRSGLContext *_glContext, const bool newState) {

    hrsglc_assert(_glContext);

    _glContext->useVSync = newState;
    glfwSwapInterval(newState);
}

