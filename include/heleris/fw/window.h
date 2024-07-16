#ifndef HELERIS_WINDOW_H
#define HELERIS_WINDOW_H

#ifndef HELERIS_OPEN_GL_INCLUDE_ALREADY
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define HELERIS_OPEN_GL_INCLUDE_ALREADY
#endif

#include "elements/click_context.h"
#include "elements/color.h"
#include "elements/rectangle.h"
#include "elements/size.h"
#include "types.h"

// Structure representing a HRS window
typedef struct HRSWindow {
    // GLFW objects
    GLFWwindow *glfwWindow;     // GLFW window
    GLFWmonitor *mainMonitor;   // GLFW monitor, the monitor of the window
    
    // Basic datas
    string_t name;              // Window name
    HRSSize size;               // Window size
    HRSColor backgroundColor;   // Window background color

    // GLFW hint datas
    // Booleans
    bool fullScreen;          // is in full screen?
    bool canResize;             // can be resized?
    bool visible;             // is visible?
    bool hasBorder;            // has a border?

    // Sizes
    HRSSize minimumSize;                                         // Minimal Window size
    HRSSize maximumSize;                                         // Maximal Window size

    // Others
    HRSVector2 windedPos;                                        // Used only in full screen functions

    // Events
    HRSSize (*onWindowResize)(struct HRSWindow*, HRSSize);       // Event for window resize
    void (*onWindowClicked)(struct HRSWindow*, HRSClickContext); // Event for window click
    void (*onWindowClose)(struct HRSWindow*);                    // Event for window close
} HRSWindow;

// Heap manipulation

/*
 * Create an heap object (an pointer to heap memory) of HRSWindow.
 */
HRSWindow* hrswin_create(string_t name, HRSSize size, bool activeFullScreen);

/*
 * Initialize window object (don't use).
 */
void hrswin_init(HRSWindow *window);

/*
 * Assert that the HRSWindow object is not nullptr and has been initialized
 */
void hrswin_assert(HRSWindow *window);

/*
 * Frees the specified window and its resources.
 */
void hrswin_free(HRSWindow *window);

// Register Events

/*
 * Register a function for the "onWindowResize" event.
 */
void hrswin_registerOnWindowResizeEvent(HRSWindow *window, HRSSize (*onWindowResize)(HRSWindow *window, HRSSize newSize));

/*
 * Register a function for the "onWindowClicked" event.
 * Will work in a future version of the Framework.
 */
void hrswin_registerOnWindowClickedEvent(HRSWindow *window, void (*onWindowClicked)(HRSWindow *window, HRSClickContext clickContext));

/*
 * Register a function for the "onWindowClicked" event.
 */
void hrswin_registerOnWindowCloseEvent(HRSWindow *window, void (*onWindowClose)(HRSWindow *window));

// Set new params

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
void hrswin_minimumWindowSize(HRSWindow *window, HRSSize minimumSize);

/*
 * Set the maximum window size can be. 
 * Default: the size of secure area of monitor.
 */
void hrswin_maximumWindowSize(HRSWindow *window, HRSSize maximumSize);

/*
 * Set the aspect radio of the window.
 * All possible window size will be a multipler of these values
 */
void hrswin_setAspectRadio(HRSWindow *window, HRSSize aspectRadio);

/*
 * Changes the background color of the specified window.
 */
void hrswin_changeBackgroundColor(HRSWindow *window, HRSColor backgroundColor);

// Set GLFW window context

/*
 * Toggle if window will be visible or not
 */
void hrswin_visible(HRSWindow *window, bool visible);

/*
 * Toggle full screen
 */
void hrswin_fullScreen(HRSWindow *window, bool fullScreen);

// Get params

/*
 * Get the secure area of monitor, which is the maximum area that the window can have for the maximum number of pixels that can appear.
 */
HRSRectangle hrswin_getMonitorSecureArea(HRSWindow *window);

#endif
