#include "heleris/fw/window.h"

#include "heleris/fw/errors/error.h"
#include "heleris/fw/errors/error_codes.h"
#include "heleris/fw/errors/error_presets.h"
#include "heleris/fw/math/math.h"

#include <stdlib.h>

// Heap manipulation

HRSWindow* hrswin_create(const string_t name, const HRSSize _size, const bool activeFullScreen){

    HRSWindow *helerisWindow = (HRSWindow*)malloc(sizeof(HRSWindow));
    
    if (helerisWindow == nullptr) 
        errpre_malloc("HRSWindow");
    
    helerisWindow->name = name;
    helerisWindow->fullScreen = activeFullScreen;
    helerisWindow->onWindowResize = nullptr;
    helerisWindow->onWindowClose = nullptr;
    helerisWindow->onWindowClicked = nullptr;

    helerisWindow->_size.width = HRS_MAX(_size.width, 1);
    helerisWindow->_size.height = HRS_MAX(_size.height, 1);

    helerisWindow->minimumSize.width = HRS_MIN(helerisWindow->_size.width, 800);
    helerisWindow->minimumSize.height = HRS_MIN(helerisWindow->_size.height, 800);

    helerisWindow->canResize = true;
    helerisWindow->visible = true;
    helerisWindow->hasBorder = true;
    
    return helerisWindow;
}

void hrswin_init(HRSWindow *_window) {
    
    _window->_monitor = glfwGetPrimaryMonitor();

    _window->_glfwWindow = glfwCreateWindow(_window->_size.width, _window->_size.height, _window->name, _window->fullScreen ? _window->_monitor : NULL, NULL);

    if (_window->_glfwWindow == nullptr) {

        HRSError _error = {"can't make a GLFWwindow", "probally you pc don't have the enough memory to alloc a _glfwWindow", HRS_ERROR_GLFW_CANT_MAKE_WINDOW};
        hrserr_printAndStopProgram(&_error);
    }

    glfwMakeContextCurrent(_window->_glfwWindow);

    glfwSetWindowOpacity(_window->_glfwWindow, hrsclr_toFloat(_window->backgroundColor, HRS_COLOR_RGBA_A));

    hrswin_visible(_window, _window->visible);

    _window->minimumSize.width = HRS_MAX(_window->minimumSize.width, 1);
    _window->minimumSize.height = HRS_MAX(_window->minimumSize.height, 1);

    if (_window->_size.width > _window->maximumSize.width || _window->_size.width > _window->maximumSize.height) {

        _window->maximumSize = hrswin_getMonitorSecureArea(_window)._size;
    }

    glfwSetWindowAttrib(_window->_glfwWindow, GLFW_DECORATED, _window->hasBorder);
    glfwSetWindowAttrib(_window->_glfwWindow, GLFW_RESIZABLE, _window->canResize);

    glfwSetWindowSizeLimits(_window->_glfwWindow, _window->minimumSize.width, _window->minimumSize.height, _window->maximumSize.width, _window->maximumSize.height);

    glfwSetWindowUserPointer(_window->_glfwWindow, _window);
}

void hrswin_assert(const HRSWindow *_window) {

    if (_window == nullptr) 
        errpre_nullptr("HRSWindow");

    if (_window->_glfwWindow == nullptr) 
        errpre_nullptr("GLFWwindow");
}

void hrswin_free(HRSWindow *_window) {

    hrswin_assert(_window);

    glfwDestroyWindow(_window->_glfwWindow);

    free(_window);

    _window = nullptr;
}

// Register Events

void hrswin_registerOnWindowResizeEvent(HRSWindow *_window, HRSSize (*onWindowResize)(HRSWindow *_window, HRSSize newSize)) {

    hrswin_assert(_window);

    if (onWindowResize == nullptr)
        errpre_nullptr("void (*onWindowResize)(HRSWindow *_window, HRSSize2 newSize)");

    _window->onWindowResize = onWindowResize;
}

void hrswin_registerOnWindowClickedEvent(HRSWindow *_window, void (*onWindowClicked)(HRSWindow *_window, HRSClickContext clickContext)) {

    hrswin_assert(_window);

    if (onWindowClicked == nullptr)
        errpre_nullptr("void (*onWindowClicked)(HRSWindow *_window, HRSClickContext clickContext)");

    _window->onWindowClicked = onWindowClicked;
}

void hrswin_registerOnWindowCloseEvent(HRSWindow *_window, void (*onWindowClose)(HRSWindow *_window)) {
    
    hrswin_assert(_window);

    if (onWindowClose == nullptr)
        errpre_nullptr("void (*onWindowClose)(HRSWindow *_window)");

    _window->onWindowClose = onWindowClose;
}

// Set new params

void hrswin_changeName(HRSWindow *_window, const string_t newName) {

    hrswin_assert(_window);

    if (STR_IS_EMPTY(newName)) {

        glfwSetWindowTitle(_window->_glfwWindow, "");
        return;
    }

    glfwSetWindowTitle(_window->_glfwWindow, newName);
}

void hrswin_changeWindowSize(HRSWindow *_window, HRSSize newSize) {

    hrswin_assert(_window);

    if (newSize.width < _window->minimumSize.width)
        newSize.width = _window->minimumSize.width;

    if (newSize.height < _window->minimumSize.width)
        newSize.height = _window->minimumSize.height;

    glfwSetWindowSize(_window->_glfwWindow, newSize.width, newSize.height);
}

void hrswin_minimumWindowSize(HRSWindow *_window, HRSSize minimumSize) {

    hrswin_assert(_window);

    minimumSize.width = HRS_MAX(minimumSize.width, 1);
    minimumSize.height = HRS_MAX(minimumSize.height, 1);

    if (minimumSize.height > _window->minimumSize.height) {

        int height = minimumSize.height;
        _window->minimumSize.height = _window->maximumSize.height;
        _window->maximumSize.height = height;
    }

    if (minimumSize.width > _window->minimumSize.width) {

        int width = minimumSize.width;
        _window->minimumSize.width = _window->maximumSize.width;
        _window->maximumSize.width = width;
    }

    _window->minimumSize.width = minimumSize.width;
    _window->minimumSize.height = minimumSize.height;

    glfwSetWindowSizeLimits(_window->_glfwWindow, _window->minimumSize.width, _window->minimumSize.height, _window->maximumSize.width, _window->maximumSize.height);
}

void hrswin_maximumWindowSize(HRSWindow *_window, HRSSize maximumSize) {

    hrswin_assert(_window);

    maximumSize.width = HRS_MAX(maximumSize.width, 800);
    maximumSize.height = HRS_MAX(maximumSize.height, 600);

    if (maximumSize.height < 600)
        maximumSize.height = 600;

    if (maximumSize.height < _window->minimumSize.height) {

        int height = maximumSize.height;
        _window->maximumSize.height = _window->minimumSize.height;
        _window->minimumSize.height = height;
    }

    if (maximumSize.width < _window->minimumSize.width) {

        int width = maximumSize.width;
        _window->maximumSize.width = _window->minimumSize.width;
        _window->minimumSize.width = width;
    }

    _window->maximumSize.width = maximumSize.width;
    _window->maximumSize.height = maximumSize.height;

    glfwSetWindowSizeLimits(_window->_glfwWindow, _window->minimumSize.width, _window->minimumSize.height, _window->maximumSize.width, _window->maximumSize.height);
}

void hrswin_setAspectRadio(HRSWindow *_window, const HRSSize aspectRadio) {

    hrswin_assert(_window);

    glfwSetWindowAspectRatio(_window->_glfwWindow, aspectRadio.width,  aspectRadio.height);
}

void hrswin_changeBackgroundColor(HRSWindow *_window, HRSColor backgroundColor) {

    hrswin_assert(_window);

    _window->backgroundColor = backgroundColor;
    glfwSetWindowOpacity(_window->_glfwWindow, hrsclr_toFloat(_window->backgroundColor, HRS_COLOR_RGBA_A));
}

// Set GLFW _window context

void hrswin_fullScreen(HRSWindow *_window, const bool fullScreen) {

    hrswin_assert(_window);

    if (fullScreen) {
        
        int x, y, width, height;
        glfwGetWindowPos(_window->_glfwWindow, &x, &y);
        glfwGetWindowSize(_window->_glfwWindow, &width, &height);

        _window->windedPos.x = x;
        _window->windedPos.y = y;

        _window->_monitor = glfwGetWindowMonitor(_window->_glfwWindow);
        const GLFWvidmode *mode = glfwGetVideoMode(_window->_monitor);

        glfwSetWindowMonitor(_window->_glfwWindow, _window->_monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    } 
    else
        glfwSetWindowMonitor(_window->_glfwWindow, NULL, _window->windedPos.x, _window->windedPos.y, _window->_size.width, _window->_size.height, 0);
}

void hrswin_canResize(HRSWindow *_window, const bool canResize) {

    hrswin_assert(_window);
    
    glfwSetWindowAttrib(_window->_glfwWindow, GLFW_RESIZABLE, canResize);

    _window->canResize = canResize;
}

void hrswin_visible(HRSWindow *_window, const bool visible) {

    hrswin_assert(_window);
    
    if (visible)
        glfwShowWindow(_window->_glfwWindow);
    else
        glfwHideWindow(_window->_glfwWindow);

    _window->visible = visible;
}

void hrswin_border(HRSWindow *_window, const bool border) {

    hrswin_assert(_window);
    
    glfwSetWindowAttrib(_window->_glfwWindow, GLFW_DECORATED, border);

    _window->hasBorder = border;
}

// Get params

HRSRectangle hrswin_getMonitorSecureArea(HRSWindow *_window) {

    int x, y, width, height;

    glfwGetMonitorWorkarea(_window->_monitor, &x, &y, &width, &height);
    
    return hrsrec_create(hrsvc2_create(x, y), hrssz_create(width, height));
}
