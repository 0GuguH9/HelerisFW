#include "heleris/fw/gl_context.h"

#include "heleris/fw/errors/error.h"
#include "heleris/fw/errors/error_codes.h"
#include "heleris/fw/errors/error_presets.h"
#include "heleris/fw/window.h"

#include "heleris/fw/math/math.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>

// Private fields:

bool_t hasBeenInitialized = FALSE;

void hrsglc_glfwResizeCallback(GLFWwindow *window, int width, int height) {

    HRSWindow* hrsWindow = (HRSWindow*)glfwGetWindowUserPointer(window);

    if (hrsWindow != nullptr && hrsWindow->onWindowResize != nullptr) {

        if (width == hrsWindow->minimalSize.width && height == hrsWindow->minimalSize.height) {

            HRSSize newSize = { width, height };
            hrsWindow->size = newSize;
            return;
        }

        if (width < hrsWindow->minimalSize.width || height == hrsWindow->minimalSize.height) {

            glfwSetWindowSize(window, HRS_MAX(width, hrsWindow->minimalSize.width), HRS_MAX(height, hrsWindow->minimalSize.height));
            return;
        }

        HRSSize newSize = { width, height };
        hrsWindow->size = hrsWindow->onWindowResize(hrsWindow, newSize);
        glViewport(0, 0, hrsWindow->size.width, hrsWindow->size.height);
    }
}

// Plublic fields:

HRSGLContext* hrsglc_create(enum EHRSMajorVersion majorVersion, int minorVersion, enum EHRSProfileType profileType) {

    if (hasBeenInitialized != FALSE) {

        HRSError error = {"attemp to create another type of \"HRSGLContext\"", "theres an attemp to create another \"HRSGLContext\" without finish other", HRS_ERROR_HRSGLC_ALREADY_INITIALIZED};
        hrserr_printAndStopProgram(&error);
    }

    HRSGLContext *context = malloc(sizeof(HRSGLContext));

    if (context == nullptr) 
        errpre_malloc("HRSGLContext");

    if (majorVersion == HRS_GL_MAJOR_TREE && minorVersion < 3)
        errpre_invalidArgument("int minorVersion (minimum version with HRS_GL_MAJOR_TREE is 3)");

    context->majorVersion = majorVersion;
    context->minorVersion = minorVersion;
    context->profileType = profileType;
    context->hasBeenInitialized = FALSE;
    context->useVSync = FALSE;
    context->swapCooldown = 0; // No cooldown
    context->fps = 0;
    context->window = nullptr;
    context->draw = nullptr;
    context->onUpdate = nullptr;

    return context;
}

void hrsglc_init(HRSGLContext *context, HRSWindow *window) {

    if (context == nullptr)
        errpre_nullptr("HRSGLContext");

    if (context->hasBeenInitialized || hasBeenInitialized != FALSE) {

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

    // Rust ownership concept :D
    context->window->glfwWindow = glfwCreateWindow(context->window->size.width, context->window->size.height, context->window->name, NULL, NULL);

    if (context->window->glfwWindow == NULL) {

        HRSError error = {"can't make a GLFWwindow", "probally you pc don't have the enough memory to alloc a glfwWindow", HRS_ERROR_GLFW_CANT_MAKE_WINDOW};
        hrserr_printAndStopProgram(&error);
    }

    glfwMakeContextCurrent(context->window->glfwWindow); 

    glfwSetWindowUserPointer(context->window->glfwWindow, context->window);
    glfwSetFramebufferSizeCallback(window->glfwWindow, hrsglc_glfwResizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

        HRSError error = {"GLAD can't init", "GLAD can't get the correct address of OpenGL functions", HRS_ERROR_GLAD_CANT_FIND_IMPLEMENTATIONS};
        hrserr_printAndStopProgram(&error);
    }

    context->hasBeenInitialized = TRUE;
}

void hrsglc_registerUpdateCallback(HRSGLContext *context, void (*onUpdate)(HRSGLContext *context, double deltaTime)) {

    hrsglc_assert(context);

    if (onUpdate == nullptr)
        errpre_nullptr("void (*onUpdate)(HRSGLContext *context, double deltaTime)");

    context->onUpdate = onUpdate;
}

void hrsglc_registerFixedUpdateCallback(HRSGLContext *context, void (*onFixedUpdate)(HRSGLContext *context, double fixedDeltaTime)) {

    hrsglc_assert(context);

    if (onFixedUpdate == nullptr)
        errpre_nullptr("void (*onFixedUpdate)(HRSGLContext *context, double deltaTime)");

    context->onFixedUpdate = onFixedUpdate;
}

void hrsglc_registerDrawCallback(HRSGLContext *context, void (*draw)(HRSGLContext *context)) {

    hrsglc_assert(context);

    if (draw == nullptr)
        errpre_nullptr("void (*draw)(HRSGLContext *context)");

    context->draw = draw;
}

void hrsglc_cycleCooldown(HRSGLContext *context, double cooldown) {

    hrsglc_assert(context);

    context->swapCooldown = (int)(cooldown * 1000.0);
}

void hrsglc_vSync(HRSGLContext *context, bool_t newState) {

    hrsglc_assert(context);

    glfwSwapInterval(newState);
}

void hrsglc_startLoop(HRSGLContext *context) {

    hrsglc_assert(context);

    hrswin_assert(context->window);

    double previousTime = glfwGetTime();
    double previousFixedTime = glfwGetTime();
    double currentTime;
    double deltaTime;
    double fixedDeltaTime;
    double fpsTimer = 0.0;
    int frameCount = 0;

    while(!glfwWindowShouldClose(context->window->glfwWindow)) {

        currentTime = glfwGetTime();
        deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        fpsTimer += deltaTime;
        frameCount++;

        if (fpsTimer >= 1.0) {

            context->fps = frameCount / fpsTimer;
            fpsTimer = 0.0;
            frameCount = 0;
        }

        context->estimatedFPS = 1.0 / deltaTime;

        if (context->onUpdate != nullptr)
            context->onUpdate(context, deltaTime);

        fixedDeltaTime = currentTime - previousFixedTime;

        if (context->swapCooldown / 1000.0 <= fixedDeltaTime && context->onFixedUpdate != nullptr) {
            
            context->onFixedUpdate(context, fixedDeltaTime);
            previousFixedTime = currentTime;
        }
        glClearColor(hrsclr_toFloat(context->window->backgroundColor, HRS_COLOR_RGBA_R),
            hrsclr_toFloat(context->window->backgroundColor, HRS_COLOR_RGBA_G),
            hrsclr_toFloat(context->window->backgroundColor, HRS_COLOR_RGBA_B),
            hrsclr_toFloat(context->window->backgroundColor, HRS_COLOR_RGBA_A));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        if (context->draw != nullptr)
            context->draw(context);

        hrsglc_swapBuffers(context);

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

void hrsglc_swapBuffers(HRSGLContext *context) {

    hrsglc_assert(context);
    
    hrswin_assert(context->window);

    glfwSwapBuffers(context->window->glfwWindow);
}

void hrsglc_assert(HRSGLContext *context) {
    
    if (context == nullptr) 
        errpre_nullptr("HRSGLContext");

    if (context->hasBeenInitialized != TRUE || hasBeenInitialized != TRUE) {

        HRSError error = {"GLFW and GLAD not initialized", "attempt to use an object of type HRSGLContext without initializing GLAD or GLFW", HRS_ERROR_HRSGLC_NOT_INITIALIZED};
        hrserr_printAndStopProgram(&error);
    }
}

void hrsglc_terminate(HRSGLContext *context) {

    hrsglc_assert(context);
    
    hrswin_free(context->window);
    
    free(context);

    glfwTerminate();

    hasBeenInitialized = FALSE;

    context = nullptr;
}
