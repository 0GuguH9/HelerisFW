#include "headers/window.h"

#include "headers/error_codes.h"
#include "types.h"

#include <stdlib.h>

HRSWindow* hrswin_create(string_t name, HRSSize2 size, bool_t activeFullScreen){

    HRSWindow *helerisWindow = (HRSWindow*)malloc(sizeof(HRSWindow));
    
    if (helerisWindow == NULL) {

        fprintf(stderr, "[HRSWindow]: can't alloc memory for a window");
        exit(HRS_ERROR_MALLOC_ERROR);
    }

    helerisWindow->glfwWindow = glfwCreateWindow(size.width, size.height, name, activeFullScreen == TRUE ? NULL: NULL, NULL);

    if (helerisWindow->glfwWindow == NULL) {

        fprintf(stderr, "[HRSWindow]: can't make a GLFWwindow");
        exit(HRS_ERROR_GLFW_CANT_MAKE_WINDOW);
    }
    
    helerisWindow->name = str_fromPrimitive(name);
    helerisWindow->size = size;
    helerisWindow->isFullScreen = activeFullScreen;
    helerisWindow->onWindowResize = NULL;
    helerisWindow->onWindowClose = NULL;
    helerisWindow->onWindowClicked = NULL;
    
    return helerisWindow;
}
