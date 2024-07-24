#include "heleris/fw/gl_context.h"

#include "heleris/fw/errors/error.h"
#include "heleris/fw/errors/error_codes.h"
#include "heleris/fw/errors/error_presets.h"
#include "heleris/fw/graphics/device_graphics.h"
#include "heleris/fw/window.h"

#include "heleris/fw/math/math.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>

#ifndef HRS_OPENGL_MAJOR_VERSION
#define HRS_OPENGL_MAJOR_VERSION 3
#endif

#ifndef HRS_OPENGL_MINOR_VERSION
#define HRS_OPENGL_MINOR_VERSION 3
#endif

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

HRSGLContext* hrsglc_create() {

    if (hasBeenInitialized != false) {

        HRSError _error = {"attemp to create another type of \"HRSGLContext\"", "theres an attemp to create another \"HRSGLContext\" without finish other", HRS_ERROR_HRSGLC_ALREADY_INITIALIZED};
        hrserr_printAndStopProgram(&_error);
    }

    HRSGLContext *_glContext = malloc(sizeof(HRSGLContext));

    if (_glContext == nullptr) 
        errpre_malloc("HRSGLContext");

    _glContext->_majorVersion = HRS_OPENGL_MAJOR_VERSION;
    _glContext->minorVersion = HRS_OPENGL_MINOR_VERSION;
    _glContext->_profileType = HRS_GL_CORE_PROFILE;
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

void hrsglc_registerPreUpdateCallback(HRSGLContext *_glContext, void (*onPreUpdate)(HRSGLContext *_glContext, double deltaTime)) {

    hrsglc_assert(_glContext);

    if (onPreUpdate == nullptr)
        errpre_nullptr("void (*onPreUpdate)(HRSGLContext *_glContext, double deltaTime)");

    _glContext->onPreUpdate = onPreUpdate;
}

void hrsglc_registerPreFixedUpdateCallback(HRSGLContext *_glContext, void (*onPreFixedUpdate)(HRSGLContext *_glContext, double fixedDeltaTime)) {

    hrsglc_assert(_glContext);

    if (onPreFixedUpdate == nullptr)
        errpre_nullptr("void (*onPreFixedUpdate)(HRSGLContext *_glContext, double fixedDeltaTime)");

    _glContext->onPreFixedUpdate = onPreFixedUpdate;
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

void hrsglc_registerPostFixedUpdateCallback(HRSGLContext *_glContext, void (*onPostFixedUpdate)(HRSGLContext *_glContext, double fixedDeltaTime)) {

    hrsglc_assert(_glContext);

    if (onPostFixedUpdate == nullptr)
        errpre_nullptr("void (*onPostFixedUpdate)(HRSGLContext *_glContext, double fixedDeltaTime)");

    _glContext->onPostFixedUpdate = onPostFixedUpdate;
}

void hrsglc_registerPostUpdateCallback(HRSGLContext *_glContext, void (*onPostUpdate)(HRSGLContext *_glContext, double deltaTime)) {

    hrsglc_assert(_glContext);

    if (onPostUpdate == nullptr)
        errpre_nullptr("void (*onPostUpdate)(HRSGLContext *_glContext, double deltaTime)");

    _glContext->onPostUpdate = onPostUpdate;
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

    double currentTime = glfwGetTime();
    double previousTime = currentTime;
    double previousPreUpdateTime = previousTime;
    double previousUpdateTime = previousTime;
    double previousPostUpdateTime = previousTime;
    double previousPreFixedTime = previousTime;
    double previousFixedTime = previousTime;
    double previousPostFixedTime = previousTime;

    double deltaTime = 0;

    double fixedDeltaAccumulator = 0;
    int fixedCalls = 0;

    double fpsTimer = 0.0;
    int frameCount = 0;

    HRSDeviceGraphics deviceGraphics = hrsdgr_create();


    while(!glfwWindowShouldClose(_glContext->window->_glfwWindow)) {

        // Get basic times and fps updates
        currentTime = glfwGetTime();
        deltaTime = currentTime - previousTime;

        fpsTimer += deltaTime;
        frameCount++;

        if (fpsTimer >= 1.0) {

            _glContext->fps = frameCount / fpsTimer;
            fpsTimer -= 1.0;
            frameCount = 0;
        }

        _glContext->estimatedFPS = 1.0 / deltaTime;

        // Call pre update callback (if ins't nullptr)
        if (_glContext->onPreUpdate != nullptr)
            _glContext->onPreUpdate(_glContext, currentTime - previousPreUpdateTime);

        previousPreUpdateTime = glfwGetTime();

        // Pre Fixed and Fixed Updates callbacks

        fixedDeltaAccumulator += deltaTime;

        if (_glContext->onFixedUpdate != nullptr)
            while (fixedDeltaAccumulator >= _glContext->swapCooldown) {



                // Call pre fixed update callback
                if(_glContext->onPreFixedUpdate != nullptr)
                    // previousPreFixedTime - previousTime -> Calc delta time between pre fixed update calls
                    _glContext->onPreFixedUpdate(_glContext, glfwGetTime() - previousPreFixedTime );

                // Save curent time
                previousPreFixedTime = glfwGetTime();

                // Calc delta time between fixedUpdate calls

                // Call fixed update callback
                _glContext->onFixedUpdate(_glContext, glfwGetTime() - previousFixedTime);

                // Save current time
                previousFixedTime = glfwGetTime();

                // Reduce delta accumulator
                fixedDeltaAccumulator -= _glContext->swapCooldown;
            
                // Add 1 to fixed calls (for post fixed update)
                fixedCalls++;
            }

        if (_glContext->onUpdate != nullptr)
            _glContext->onUpdate(_glContext, glfwGetTime() - previousUpdateTime);

        if (_glContext->onPostFixedUpdate != nullptr) {
            while (fixedCalls > 0) {
            
                _glContext->onPostFixedUpdate(_glContext, glfwGetTime() - previousPostFixedTime);

                previousPostFixedTime = glfwGetTime();

                fixedCalls--;
            }
        } else
            fixedCalls = 0;

        if (_glContext->onPostUpdate != nullptr)
            _glContext->onPostUpdate(_glContext, glfwGetTime() - previousPostUpdateTime);

        previousPostUpdateTime = glfwGetTime();

        // Background color
        glClearColor(hrsclr_toFloat(_glContext->window->backgroundColor, HRS_COLOR_RGBA_R),
            hrsclr_toFloat(_glContext->window->backgroundColor, HRS_COLOR_RGBA_G),
            hrsclr_toFloat(_glContext->window->backgroundColor, HRS_COLOR_RGBA_B),
            1);

        // Clear background with a color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Call Draw callback (if ins't nullptr)
        if (_glContext->draw != nullptr)
            _glContext->draw(_glContext, deviceGraphics);

        // Swap buffers
        glfwSwapBuffers(_glContext->window->_glfwWindow);

        // Pool window events
        glfwPollEvents();
        previousTime = currentTime;
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
