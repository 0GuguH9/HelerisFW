#include "heleris/fw/gl_context.h"

#include "heleris/fw/errors/error.h"
#include "heleris/fw/errors/error_codes.h"
#include "heleris/fw/errors/error_presets.h"
#include "heleris/fw/graphics/device_graphics.h"
#include "heleris/fw/window.h"

#include "heleris/fw/math/math.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>

// Private fields:

bool hasBeenInitialized = false;

void hrsglc_glfwResizeCallback(GLFWwindow *window, int width, int height) {

    HRSWindow* hrsWindow = (HRSWindow*)glfwGetWindowUserPointer(window);

    if (hrsWindow != nullptr && hrsWindow->onWindowResize != nullptr) {

        if (width == hrsWindow->minimumSize.width && height == hrsWindow->minimumSize.height) {

            HRSSize newSize = { width, height };
            hrsWindow->size = newSize;
            return;
        }

        if (width < hrsWindow->minimumSize.width || height == hrsWindow->minimumSize.height) {

            glfwSetWindowSize(window, HRS_MAX(width, hrsWindow->minimumSize.width), HRS_MAX(height, hrsWindow->minimumSize.height));
            return;
        }

        HRSSize newSize = { width, height };
        hrsWindow->size = hrsWindow->onWindowResize(hrsWindow, newSize);
        glViewport(0, 0, hrsWindow->size.width, hrsWindow->size.height);
    }
}

// Plublic fields:

// Heap manipulation

HRSGLContext* hrsglc_create(const enum EHRSMajorVersion majorVersion, const int minorVersion, const enum EHRSProfileType profileType) {

    if (hasBeenInitialized != false) {

        HRSError error = {"attemp to create another type of \"HRSGLContext\"", "theres an attemp to create another \"HRSGLContext\" without finish other", HRS_ERROR_HRSGLC_ALREADY_INITIALIZED};
        hrserr_printAndStopProgram(&error);
    }

    HRSGLContext *context = malloc(sizeof(HRSGLContext));

    if (context == nullptr) 
        errpre_malloc("HRSGLContext");

    if (majorVersion == HRS_GL_MAJOR_THREE && minorVersion < 3)
        errpre_invalidArgument("int minorVersion (minimum version with HRS_GL_MAJOR_TREE is 3)");

    context->majorVersion = majorVersion;
    context->minorVersion = minorVersion;
    context->profileType = profileType;
    context->hasBeenInitialized = false;
    context->useVSync = false;
    context->swapCooldown = 1.0 / 60.0; 
    context->fps = 0;
    context->window = nullptr;
    context->draw = nullptr;
    context->onUpdate = nullptr;

    return context;
}

void hrsglc_init(HRSGLContext *context, HRSWindow *window) {

    if (context == nullptr)
        errpre_nullptr("HRSGLContext");

    if (context->hasBeenInitialized || hasBeenInitialized != false) {

        HRSError error = {"attempt to reinitialize GLFW and GLAD", "there was an attempt to reset GLFW and GLAD, which may cause errors."
            " \nAvoid having more than one object of type \"HRSGLContext\"", HRS_ERROR_HRSGLC_ALREADY_INITIALIZED};
        hrserr_printAndStopProgram(&error);
    }

    if (!glfwInit()) {

        HRSError error = {"GLFW can't init", "unable to start GLFW, check your operating system", HRS_ERROR_GLFW_CANT_INIT};
        hrserr_printAndStopProgram(&error);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, context->majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, context->minorVersion);

    glfwWindowHint(GLFW_OPENGL_PROFILE, context->profileType);

    if (window == nullptr)
        errpre_nullptr("HRSWindow");

    context->window = window;

    hrswin_init(context->window);

    glfwSetFramebufferSizeCallback(window->glfwWindow, hrsglc_glfwResizeCallback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

        HRSError error = {"GLAD can't init", "GLAD can't get the correct address of OpenGL functions", HRS_ERROR_GLAD_CANT_FIND_IMPLEMENTATIONS};
        hrserr_printAndStopProgram(&error);
    }

    glfwSwapInterval(context->useVSync);

    hasBeenInitialized = true;
    context->hasBeenInitialized = true;
}

void hrsglc_assert(const HRSGLContext *context) {
    
    if (context == nullptr) 
        errpre_nullptr("HRSGLContext");

    if (context->hasBeenInitialized != true || hasBeenInitialized != true) {

        HRSError error = {"GLFW and GLAD not initialized", "attempt to use an object of type HRSGLContext without initializing GLAD or GLFW", HRS_ERROR_HRSGLC_NOT_INITIALIZED};
        hrserr_printAndStopProgram(&error);
    }
}

void hrsglc_terminate(HRSGLContext *context) {

    hrsglc_assert(context);
    
    hrswin_free(context->window);
    
    free(context);

    glfwTerminate();

    hasBeenInitialized = false;

    context = nullptr;
}

// Call backs

void hrsglc_registerUpdatePreFixedCallback(HRSGLContext *context, void (*onUpdatePreFixed)(HRSGLContext *context, double deltaTime)) {

    hrsglc_assert(context);

    if (onUpdatePreFixed == nullptr)
        errpre_nullptr("void (*onUpdatePreFixed)(HRSGLContext *context, double deltaTime)");

    context->onUpdatePreFixed = onUpdatePreFixed;
}

void hrsglc_registerFixedUpdateCallback(HRSGLContext *context, void (*onFixedUpdate)(HRSGLContext *context, double fixedDeltaTime)) {

    hrsglc_assert(context);

    if (onFixedUpdate == nullptr)
        errpre_nullptr("void (*onFixedUpdate)(HRSGLContext *context, double fixedDeltaTime)");

    context->onFixedUpdate = onFixedUpdate;
}

void hrsglc_registerUpdateCallback(HRSGLContext *context, void (*onUpdate)(HRSGLContext *context, double deltaTime)) {

    hrsglc_assert(context);

    if (onUpdate == nullptr)
        errpre_nullptr("void (*onUpdate)(HRSGLContext *context, double deltaTime)");

    context->onUpdate = onUpdate;
}

void hrsglc_registerFixedPostUpdateCallback(HRSGLContext *context, void (*onFixedPostUpdate)(HRSGLContext *context, double fixedDeltaTime)) {

    hrsglc_assert(context);

    if (onFixedPostUpdate == nullptr)
        errpre_nullptr("void (*onFixedPostUpdate)(HRSGLContext *context, double fixedDeltaTime)");

    context->onFixedPostUpdate = onFixedPostUpdate;
}

void hrsglc_registerDrawCallback(HRSGLContext *context, void (*draw)(HRSGLContext *context, HRSDeviceGraphics deviceGraphics)) {

    hrsglc_assert(context);

    if (draw == nullptr)
        errpre_nullptr("void (*draw)(HRSGLContext *context, HRSDeviceGraphics deviceGraphics)");

    context->draw = draw;
}

// Context struct sets

void hrsglc_cycleCooldown(HRSGLContext *context, const double cooldown) {

    hrsglc_assert(context);

    context->swapCooldown = cooldown;
}

void hrsglc_startLoop(HRSGLContext *context) {

    hrsglc_assert(context);

    hrswin_assert(context->window);

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

    while(!glfwWindowShouldClose(context->window->glfwWindow)) {

        currentTime = glfwGetTime();
        deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        fpsTimer += deltaTime;
        frameCount++;

        if (fpsTimer >= 1.0) {

            context->fps = frameCount / fpsTimer;
            fpsTimer -= 1.0;
            frameCount = 0;
        }

        context->estimatedFPS = 1.0 / deltaTime;

        if (context->onUpdatePreFixed != nullptr)
            context->onUpdatePreFixed(context, deltaTime);

        fixedDeltaTime = glfwGetTime() - previousFixedTime;

        fixedDeltaAccumulator += deltaTime;

        while (fixedDeltaAccumulator >= context->swapCooldown) {

            previousFixedTime = glfwGetTime();

            if (context->onFixedUpdate != nullptr) {
                context->onFixedUpdate(context, fixedDeltaTime);
            }

            fixedDeltaAccumulator -= fixedDeltaTime;

            fixedDeltaTime = glfwGetTime() - previousFixedTime;

            postFixedCalls++;
        }

        if (context->onUpdate != nullptr)
            context->onUpdate(context, deltaTime);

        double fixedPostDeltaTime = glfwGetTime() - previousFixedTime;

        double postFixedTime = previousTime;

        while (postFixedCalls > 0) {

            postFixedTime = glfwGetTime();
            
            if (context->onFixedPostUpdate != nullptr)
                context->onFixedPostUpdate(context, fixedPostDeltaTime);

            fixedPostDeltaTime = glfwGetTime() - postFixedTime;

            postFixedCalls--;
        }

        glClearColor(hrsclr_toFloat(context->window->backgroundColor, HRS_COLOR_RGBA_R),
            hrsclr_toFloat(context->window->backgroundColor, HRS_COLOR_RGBA_G),
            hrsclr_toFloat(context->window->backgroundColor, HRS_COLOR_RGBA_B),
            1);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        if (context->draw != nullptr)
            context->draw(context, deviceGraphics);

        glfwSwapBuffers(context->window->glfwWindow);

        glfwPollEvents();
    }
}

void hrsglc_closeLoop(HRSGLContext *context) {

    hrsglc_assert(context);
    
    hrswin_assert(context->window);

    glfwSetWindowShouldClose(context->window->glfwWindow, GLFW_TRUE);

    if (context->window->onWindowClose != nullptr)
        context->window->onWindowClose(context->window);
}

// GLContext sets

void hrsglc_vSync(HRSGLContext *context, const bool newState) {

    hrsglc_assert(context);

    context->useVSync = newState;
    glfwSwapInterval(newState);
}

