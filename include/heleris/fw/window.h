#ifndef HELERIS_WINDOW_H
#define HELERIS_WINDOW_H

#ifndef HELERIS_OPEN_GL_INCLUDE_ALREADY
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define HELERIS_OPEN_GL_INCLUDE_ALREADY
#endif

#include "types.h"
#include "elements/click_context.h"
#include "elements/color.h"
#include "elements/size.h"

// Structure representing a HRS window
typedef struct HRSWindow {
    GLFWwindow *glfwWindow;                                      // Pointer to the GLFW window
    HRSColor backgroundColor;                                    // Window background color
    string_t name;                                               // Window name
    HRSSize size;                                                // Window size
    HRSSize minimalSize;                                         // Minimal Window size
    bool_t isFullScreen;                                         // Indicates if the window is in fullscreen mode
    HRSSize (*onWindowResize)(struct HRSWindow*, HRSSize);       // Event for window resize
    void (*onWindowClicked)(struct HRSWindow*, HRSClickContext); // Event for window click
    void (*onWindowClose)(struct HRSWindow*);                    // Event for window close
} HRSWindow;

/*
 * Create an heap object (an pointer to heap memory) of HRSWindow.
 */
HRSWindow* hrswin_create(string_t name, HRSSize size, bool_t activeFullScreen);

/*
 * Register a function for the "onWindowResize" event.
 */
void hrswin_registerOnWindowResizeEvent(HRSWindow *window, HRSSize (*onWindowResize)(HRSWindow *window, HRSSize newSize));

/*
 * Register a function for the "onWindowClicked" event.
 * Will work in a future version of the Framework.
 * Try to use Scene GUI sistem and not this event.
 */
void hrswin_registerOnWindowClickedEvent(HRSWindow *window, void (*onWindowClicked)(HRSWindow *window, HRSClickContext clickContext));

/*
 * Register a function for the "onWindowClicked" event.
 */
void hrswin_registerOnWindowCloseEvent(HRSWindow *window, void (*onWindowClose)(HRSWindow *window));

/*
 * Changes the name of the specified window.
 */
void hrswin_changeName(HRSWindow *window, string_t newName);

/*
 * Changes the size of the specified window.
 * Can't be smaller than minimum size.
 */
void hrswin_changeWindowSize(HRSWindow *window, HRSSize newSize);

/*
 * Set the minimum window size can be. 
 * Default: 800x600 or the initial value (whichever is smaller).
 */
void hrswin_minimumWindowSize(HRSWindow *window, HRSSize newSize);

/*
 * Changes the background color of the specified window.
 */
void hrswin_changeBackgroundColor(HRSWindow *window, HRSColor backgroundColor);

/*
 * Assert that the HRSWindow object is not nullptr and has been initialized
 */
void hrswin_assert(HRSWindow *window);

/*
 * Frees the specified window and its resources.
 */
void hrswin_free(HRSWindow *window);

#endif
