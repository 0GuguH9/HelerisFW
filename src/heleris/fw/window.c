#include "heleris/fw/window.h"

#include "heleris/fw/elements/color.h"
#include "heleris/fw/errors/error.h"
#include "heleris/fw/errors/error_codes.h"
#include "heleris/fw/errors/error_presets.h"
#include "heleris/fw/types.h"
#include "heleris/fw/math/math.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>

// Heap manipulation

HRSWindow* hrswin_create(string_t name, HRSSize size, bool activeFullScreen){

    HRSWindow *helerisWindow = (HRSWindow*)malloc(sizeof(HRSWindow));
    
    if (helerisWindow == nullptr) 
        errpre_malloc("HRSWindow");
    
    helerisWindow->name = name;
    helerisWindow->size = size;
    helerisWindow->fullScreen = activeFullScreen;
    helerisWindow->onWindowResize = nullptr;
    helerisWindow->onWindowClose = nullptr;
    helerisWindow->onWindowClicked = nullptr;

    size.width = HRS_MAX(size.width, 1);
    size.height = HRS_MAX(size.height, 1);

    helerisWindow->minimumSize.width = HRS_MIN(size.width, 800);
    helerisWindow->minimumSize.height = HRS_MIN(size.height, 800);
    
    return helerisWindow;
}

void hrswin_init(HRSWindow *window) {
    
    window->glfwWindow = glfwCreateWindow(window->size.width, window->size.height, window->name, window->visible ? glfwGetPrimaryMonitor() : NULL, NULL);

    if (window->glfwWindow == nullptr) {

        HRSError error = {"can't make a GLFWwindow", "probally you pc don't have the enough memory to alloc a glfwWindow", HRS_ERROR_GLFW_CANT_MAKE_WINDOW};
        hrserr_printAndStopProgram(&error);
    }

    glfwMakeContextCurrent(window->glfwWindow);

    window->mainMonitor = glfwGetWindowMonitor(window->glfwWindow);

    glfwSetWindowOpacity(window->glfwWindow, hrsclr_toFloat(window->backgroundColor, HRS_COLOR_RGBA_A));

    hrswin_visible(window, window->visible);

    window->minimumSize.width = HRS_MAX(window->minimumSize.width, 1);
    window->minimumSize.height = HRS_MAX(window->minimumSize.height, 1);

    if (window->size.width > window->maximumSize.width || window->size.width > window->maximumSize.height) {

        window->maximumSize = hrswin_getMonitorSecureArea(window).size;
    }

    glfwSetWindowSizeLimits(window->glfwWindow, window->minimumSize.width, window->minimumSize.height, window->maximumSize.width, window->maximumSize.height);

    glfwSetWindowUserPointer(window->glfwWindow, window);
}

void hrswin_assert(HRSWindow *window) {

    if (window == nullptr) 
        errpre_nullptr("HRSWindow");

    if (window->glfwWindow == nullptr) 
        errpre_nullptr("GLFWwindow");
}

void hrswin_free(HRSWindow *window) {

    hrswin_assert(window);

    glfwDestroyWindow(window->glfwWindow);

    free(window);

    window = nullptr;
}

// Register Events

void hrswin_registerOnWindowResizeEvent(HRSWindow *window, HRSSize (*onWindowResize)(HRSWindow *window, HRSSize newSize)) {

    hrswin_assert(window);

    if (onWindowResize == nullptr)
        errpre_nullptr("void (*onWindowResize)(HRSWindow *window, HRSSize2 newSize)");

    window->onWindowResize = onWindowResize;
}

void hrswin_registerOnWindowClickedEvent(HRSWindow *window, void (*onWindowClicked)(HRSWindow *window, HRSClickContext clickContext)) {

    hrswin_assert(window);

    if (onWindowClicked == nullptr)
        errpre_nullptr("void (*onWindowClicked)(HRSWindow *window, HRSClickContext clickContext)");

    window->onWindowClicked = onWindowClicked;
}

void hrswin_registerOnWindowCloseEvent(HRSWindow *window, void (*onWindowClose)(HRSWindow *window)) {
    
    hrswin_assert(window);

    if (onWindowClose == nullptr)
        errpre_nullptr("void (*onWindowClose)(HRSWindow *window)");

    window->onWindowClose = onWindowClose;
}

// Set new params

void hrswin_changeName(HRSWindow *window, string_t newName) {

    hrswin_assert(window);

    if (STR_IS_EMPTY(newName)) {

        glfwSetWindowTitle(window->glfwWindow, "");
        return;
    }

    glfwSetWindowTitle(window->glfwWindow, newName);
}

void hrswin_changeWindowSize(HRSWindow *window, HRSSize newSize) {

    hrswin_assert(window);

    if (newSize.width < window->minimumSize.width)
        newSize.width = window->minimumSize.width;

    if (newSize.height < window->minimumSize.width)
        newSize.height = window->minimumSize.height;

    glfwSetWindowSize(window->glfwWindow, newSize.width, newSize.height);
}

void hrswin_minimumWindowSize(HRSWindow *window, HRSSize minimumSize) {

    hrswin_assert(window);

    minimumSize.width = HRS_MAX(minimumSize.width, 1);
    minimumSize.height = HRS_MAX(minimumSize.height, 1);

    if (minimumSize.height > window->minimumSize.height) {

        int height = minimumSize.height;
        window->minimumSize.height = window->maximumSize.height;
        window->maximumSize.height = height;
    }

    if (minimumSize.width > window->minimumSize.width) {

        int width = minimumSize.width;
        window->minimumSize.width = window->maximumSize.width;
        window->maximumSize.width = width;
    }

    window->minimumSize.width = minimumSize.width;
    window->minimumSize.height = minimumSize.height;

    glfwSetWindowSizeLimits(window->glfwWindow, window->minimumSize.width, window->minimumSize.height, window->maximumSize.width, window->maximumSize.height);
}

void hrswin_maximumWindowSize(HRSWindow *window, HRSSize maximumSize) {

    hrswin_assert(window);

    maximumSize.width = HRS_MAX(maximumSize.width, 800);
    maximumSize.height = HRS_MAX(maximumSize.height, 600);

    if (maximumSize.height < 600)
        maximumSize.height = 600;

    if (maximumSize.height < window->minimumSize.height) {

        int height = maximumSize.height;
        window->maximumSize.height = window->minimumSize.height;
        window->minimumSize.height = height;
    }

    if (maximumSize.width < window->minimumSize.width) {

        int width = maximumSize.width;
        window->maximumSize.width = window->minimumSize.width;
        window->minimumSize.width = width;
    }

    window->maximumSize.width = maximumSize.width;
    window->maximumSize.height = maximumSize.height;

    glfwSetWindowSizeLimits(window->glfwWindow, window->minimumSize.width, window->minimumSize.height, window->maximumSize.width, window->maximumSize.height);
}

void hrswin_setAspectRadio(HRSWindow *window, HRSSize aspectRadio) {

    hrswin_assert(window);

    glfwSetWindowAspectRatio(window->glfwWindow, aspectRadio.width,  aspectRadio.height);
}

void hrswin_changeBackgroundColor(HRSWindow *window, HRSColor backgroundColor) {

    hrswin_assert(window);

    window->backgroundColor = backgroundColor;
}

// Set GLFW window context

void hrswin_visible(HRSWindow *window, bool visible) {

    hrswin_assert(window);
    
    if (visible)
        glfwShowWindow(window->glfwWindow);
    else
        glfwHideWindow(window->glfwWindow);

    window->visible = visible;
}

void hrswin_fullScreen(HRSWindow *window, bool fullScreen) {

    hrswin_assert(window);

    if (fullScreen) {
        
        int x, y, width, height;
        glfwGetWindowPos(window->glfwWindow, &x, &y);
        glfwGetWindowSize(window->glfwWindow, &width, &height);

        window->windedPos.x = x;
        window->windedPos.y = y;

        window->mainMonitor = glfwGetWindowMonitor(window->glfwWindow);
        const GLFWvidmode *mode = glfwGetVideoMode(window->mainMonitor);

        glfwSetWindowMonitor(window->glfwWindow, window->mainMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    } else {
        
        int x = window->windedPos.x;
        int y = window->windedPos.y;

        glfwSetWindowMonitor(window->glfwWindow, NULL, 0, 0, window->size.width, window->size.height, 0);
    }
}

// Get params

HRSRectangle hrswin_getMonitorSecureArea(HRSWindow *window) {

    int x, y, width, height;
    glfwGetMonitorWorkarea(window->mainMonitor, &x, &y, &width, &height);
    
    return hrsrec_create(hrsvc2_create(x, y), hrssz_create(width, height));
}
