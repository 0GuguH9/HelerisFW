#include "headers/window.h"

#include "types.h"

#include <stdlib.h>

HRSWindow* hrswin_create(char *name, HRSSize2 size, bool_t activeFullScreen, void (*onWindowResize)(HRSWindow*, int, int), void (*onWindowClose)(HRSWindow*), void (*onWindowClicked)(HRSWindow*, HRSClickContext)){

    HRSWindow *helerisWindow = (HRSWindow*)malloc(sizeof(HRSWindow));
    
    if (helerisWindow == NULL) {

        //TODO:add "ErrorHandler" struct
        return NULL;
    }

    helerisWindow->glfwWindow = glfwCreateWindow(size.width, size.height, name, activeFullScreen == TRUE ? NULL: NULL);

    if (helerisWindow->glfwWindow == NULL) {

        //TODO:add "ErrorHandler" struct
        return NULL;
    }
    
    helerisWindow->name = str_fromPrimitive(name);
    helerisWindow->size = size;
    helerisWindow->isFullScreen = activeFullScreen;
    helerisWindow->onWindowResize = onWindowResize;
    helerisWindow->onWindowClose = onWindowClose;
    helerisWindow->onWindowClicked = onWindowClicked;
    
    glfwInit();

    return helerisWindow;
}
