#include "heleris/fw/window.h"

#include "heleris/fw/errors/error.h"
#include "heleris/fw/errors/error_codes.h"
#include "heleris/fw/errors/error_presets.h"
#include "heleris/fw/types.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>

HRSWindow* hrswin_create(string_t name, HRSSize2 size, bool_t activeFullScreen){

    HRSWindow *helerisWindow = (HRSWindow*)malloc(sizeof(HRSWindow));
    
    if (helerisWindow == NULL) 
        errpre_malloc("HRSWindow");

    helerisWindow->glfwWindow = glfwCreateWindow(size.width, size.height, name, activeFullScreen == TRUE ? NULL: NULL, NULL);

    if (helerisWindow->glfwWindow == NULL) {

        HRSError error = {"can't make a GLFWwindow", "It was not possible to create a window of type GLFWwindow. Check if a context was previously created and initialized", HRS_ERROR_GLFW_CANT_MAKE_WINDOW};
        hrserr_printAndStopProgram(&error);
    }
    
    helerisWindow->name = name;
    helerisWindow->size = size;
    helerisWindow->isFullScreen = activeFullScreen;
    helerisWindow->onWindowResize = NULL;
    helerisWindow->onWindowClose = NULL;
    helerisWindow->onWindowClicked = NULL;
    
    return helerisWindow;
}

void hrswin_registerOnWindowResizeEvent(HRSWindow *window, void (*onWindowResize)(HRSWindow *window, HRSSize2 newSize)) {

    hrswin_assertWindowInstNull(window);

    if (onWindowResize == nullptr)
        errpre_nullptr("void (*onWindowResize)(HRSWindow *window, HRSSize2 newSize)");

    window->onWindowResize = onWindowResize;
}

void hrswin_registerOnWindowClickedEvent(HRSWindow *window, void (*onWindowClicked)(HRSWindow *window, HRSClickContext clickContext)) {

    hrswin_assertWindowInstNull(window);

    if (onWindowClicked == nullptr)
        errpre_nullptr("void (*onWindowClicked)(HRSWindow *window, HRSClickContext clickContext)");

    window->onWindowClicked = onWindowClicked;
}

void hrswin_registerOnWindowCloseEvent(HRSWindow *window, void (*onWindowClose)(HRSWindow *window)) {
    
    hrswin_assertWindowInstNull(window);

    if (onWindowClose == nullptr)
        errpre_nullptr("void (*onWindowClose)(HRSWindow *window)");

    window->onWindowClose = onWindowClose;
}
void hrswin_changeName(HRSWindow *window, string_t newName) {

    hrswin_assertWindowInstNull(window);

    if (STR_IS_EMPTY(newName)) {

        glfwSetWindowTitle(window->glfwWindow, "");
        return;
    }

    glfwSetWindowTitle(window->glfwWindow, newName);
}

void hrswin_changeWindowSize(HRSWindow *window, HRSSize2 newSize) {

    hrswin_assertWindowInstNull(window);

    if (newSize.width < 1)
        newSize.width = 1;

    if (newSize.height < 1)
        newSize.height = 1;

    glfwSetWindowSize(window->glfwWindow, newSize.width, newSize.height);
}

void hrswin_changeBackgroundColor(HRSWindow *window, HRSColor backgroundColor) {

    hrswin_assertWindowInstNull(window);

    window->backgroundColor = backgroundColor;
}

void hrswin_applyChanges(HRSWindow *window) {

    hrswin_assertWindowInstNull(window);

    if (STR_IS_EMPTY(window->name)) {

        glfwSetWindowTitle(window->glfwWindow, "");
        return;
    }

    if (window->size.width < 1)
        window->size.width = 1;

    if (window->size.height < 1)
        window->size.height = 1;

    glfwSetWindowTitle(window->glfwWindow, window->name);
    glfwSetWindowSize(window->glfwWindow, window->size.width, window->size.height);
}

void hrswin_assertWindowInstNull(HRSWindow *window) {

    if (window == nullptr) 
        errpre_nullptr("HRSWindow");

    if (window->glfwWindow == nullptr) 
        errpre_nullptr("GLFWwindow");
}
