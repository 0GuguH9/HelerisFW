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

void glfwResizeCallback(GLFWwindow *_window, int width, int height) {

    HRSWindow* hrsWindow = (HRSWindow*)glfwGetWindowUserPointer(_window);

    if (hrsWindow != nullptr && hrsWindow->onWindowResize != nullptr) {

        if (width == hrsWindow->minimumSize.width && height == hrsWindow->minimumSize.height) {

            HRSSize newSize = { width, height };
            hrsWindow->_size = newSize;
            return;
        }

        if (width < hrsWindow->minimumSize.width || height == hrsWindow->minimumSize.height) {

            glfwSetWindowSize(_window, HRS_MAX(width, hrsWindow->minimumSize.width), HRS_MAX(height, hrsWindow->minimumSize.height));
            return;
        }

        HRSSize newSize = { width, height };
        hrsWindow->_size = hrsWindow->onWindowResize(hrsWindow, newSize);
        glViewport(0, 0, hrsWindow->_size.width, hrsWindow->_size.height);
    }
}

//  Inline "Functions"

#define INLINE_DRAW_LOGIC() glClearColor(hrsclr_toFloat(_glContext->_window->backgroundColor, HRS_COLOR_RGBA_R), \
        hrsclr_toFloat(_glContext->_window->backgroundColor, HRS_COLOR_RGBA_G), \
        hrsclr_toFloat(_glContext->_window->backgroundColor, HRS_COLOR_RGBA_B), \
        1); \
\
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); \
\
    _glContext->draw(_glContext, &_deviceGraphics); \
\
    glfwSwapBuffers(_glContext->_window->_glfwWindow); \

/*
* This "inline function" (just a define :D) is for the fixed update loop
* The order is: 
*  Pre Update callback
*  Pre Fixed Update callback
*  Fixed Update callback
*  Update callback
*  Post Fixed Update callback
*  Post Update callback
*
* We use do while because its only called if "fixedDeltaAccumulator" its allready higher or equals to "swapCooldown"
*/
#define INLINE_FIXED_UPDATE_LOGIC(previousPreUpdateTime, previousPreFixedTime, previousFixedTime, previousUpdateTime, previousPostFixedTime, previousPostUpdateTime, fixedDeltaAccumulator) do { \
\
        _glContext->onPreUpdate(_glContext, glfwGetTime() - previousPreUpdateTime); \
\
        previousPreUpdateTime = glfwGetTime(); \
\
        _glContext->onPreFixedUpdate(_glContext, glfwGetTime() - previousPreFixedTime ); \
\
        previousPreFixedTime = glfwGetTime(); \
\
        _glContext->onFixedUpdate(_glContext, glfwGetTime() - previousFixedTime); \
\
        previousFixedTime = glfwGetTime(); \
\
        _glContext->onUpdate(_glContext, glfwGetTime() - previousUpdateTime); \
\
        previousUpdateTime = glfwGetTime(); \
\
        _glContext->onPostFixedUpdate(_glContext, glfwGetTime() - previousPostFixedTime); \
\
        previousPostFixedTime = glfwGetTime(); \
\
        _glContext->onPostUpdate(_glContext, glfwGetTime() - previousPostUpdateTime); \
\
        previousPostUpdateTime = glfwGetTime(); \
\
        fixedDeltaAccumulator -= _glContext->swapCooldown; \
    } while(fixedDeltaAccumulator >= _glContext->swapCooldown); \

#define INLINE_UPDATE_LOGIC(previousPreUpdateTime, previousUpdateTime, previousPostUpdateTime) _glContext->onPreUpdate(_glContext, glfwGetTime() - previousPreUpdateTime); \
\
        previousPreUpdateTime = glfwGetTime(); \
\
        _glContext->onUpdate(_glContext, glfwGetTime() - previousUpdateTime); \
\
        previousUpdateTime = glfwGetTime(); \
\
        _glContext->onPostUpdate(_glContext, glfwGetTime() - previousPostUpdateTime); \
\
        previousPostUpdateTime = glfwGetTime(); \

void nullUpdate(HRSGLContext *_glContext, double deltaTime) {}
void nullDraw(HRSGLContext *_glContext, HRSDeviceGraphics *_deviceGraphics) {}

// Plublic fields:

//  Heap manipulation

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
    _glContext->_window = nullptr;

    // "Null Functions"
    _glContext->draw = nullDraw;
    _glContext->onPreUpdate = nullUpdate;
    _glContext->onPreFixedUpdate = nullUpdate;
    _glContext->onFixedUpdate = nullUpdate;
    _glContext->onUpdate = nullUpdate;
    _glContext->onPostFixedUpdate = nullUpdate;
    _glContext->onPostUpdate = nullUpdate;

    return _glContext;
}

void hrsglc_init(HRSGLContext *_glContext, HRSWindow *_window) {

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

    if (_window == nullptr)
        errpre_nullptr("HRSWindow");

    _glContext->_window = _window;

    hrswin_init(_glContext->_window);

    glfwSetFramebufferSizeCallback(_window->_glfwWindow, glfwResizeCallback);
    
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
    
    hrswin_free(_glContext->_window);
    
    free(_glContext);

    glfwTerminate();

    hasBeenInitialized = false;

    _glContext = nullptr;
}

//  Call backs

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

void hrsglc_registerDrawCallback(HRSGLContext *_glContext, void (*draw)(HRSGLContext *_glContext, HRSDeviceGraphics *_deviceGraphics)) {

    hrsglc_assert(_glContext);

    if (draw == nullptr)
        errpre_nullptr("void (*draw)(HRSGLContext *_glContext, HRSDeviceGraphics *_deviceGraphics)");

    _glContext->draw = draw;
}

//  Context struct sets

void hrsglc_cycleCooldown(HRSGLContext *_glContext, const double cooldown) {

    hrsglc_assert(_glContext);

    _glContext->swapCooldown = cooldown;
}

void hrsglc_startLoop(HRSGLContext *_glContext) {

    hrsglc_assert(_glContext);

    hrswin_assert(_glContext->_window);

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

    double fpsTimer = 0.0;
    int frameCount = 0;

    HRSDeviceGraphics _deviceGraphics = hrsdgr_create();


    while(!glfwWindowShouldClose(_glContext->_window->_glfwWindow)) {

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

        if (fixedDeltaAccumulator >= _glContext->swapCooldown) {
            INLINE_FIXED_UPDATE_LOGIC(previousPreUpdateTime, previousPreFixedTime, previousFixedTime, previousUpdateTime, previousPostFixedTime, previousPostUpdateTime, fixedDeltaAccumulator)
        } else {
            INLINE_UPDATE_LOGIC(previousPreUpdateTime, previousUpdateTime, previousPostUpdateTime)
        }

        INLINE_DRAW_LOGIC();

        // Pool _window events
        glfwPollEvents();
        previousTime = currentTime;
    }
}

void hrsglc_closeLoop(HRSGLContext *_glContext) {

    hrsglc_assert(_glContext);
    
    hrswin_assert(_glContext->_window);

    glfwSetWindowShouldClose(_glContext->_window->_glfwWindow, GLFW_TRUE);

    if (_glContext->_window->onWindowClose != nullptr)
        _glContext->_window->onWindowClose(_glContext->_window);
}

//  GLContext sets

void hrsglc_vSync(HRSGLContext *_glContext, const bool newState) {

    hrsglc_assert(_glContext);

    _glContext->useVSync = newState;
    glfwSwapInterval(newState);
}
