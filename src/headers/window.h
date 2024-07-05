#ifndef HELERIS_WINDOW_H
#define HELERIS_WINDOW_H

#ifndef HELERIS_OPEN_GL_INCLUDE_ALREADY
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define HELERIS_OPEN_GL_INCLUDE_ALREADY
#endif

#include "../types.h"
#include "../elements/headers/click_context.h"
#include "../elements/headers/color.h"
#include "../elements/headers/size2.h"

// Structure representing a HRS window
typedef struct HRSWindow {
    GLFWwindow *glfwWindow;                 // Pointer to the GLFW window
    HRSColor backgroundColor;             // Window background color
    string_t name;                             // Window name
    HRSSize2 size;                              // Window size
    bool_t isFullScreen;                       // Indicates if the window is in fullscreen mode
    void (*onWindowResize)(struct HRSWindow*, HRSSize2); // Event for window resize
    void (*onWindowClicked)(struct HRSWindow*, HRSClickContext); // Event for window click
    void (*onWindowClose)(struct HRSWindow*);    // Event for window close
} HRSWindow;

/*
 * Creates a new HRSWindow.
 */
HRSWindow* hrswin_create(string_t name, HRSSize2 size, bool_t activeFullScreen);

/*
 * Register a function for the "onWindowResize" event
 */
void hrswin_registerOnWindowResizeEvent(HRSWindow *window, void (*onWindowResize)(HRSWindow *window, HRSSize2 newSize));

/*
 * Register a function for the "onWindowClicked" event
 */
void hrswin_registerOnWindowClickedEvent(HRSWindow *window, void (*onWindowClicked)(HRSWindow *window, HRSClickContext clickContext));

/*
 * Register a function for the "onWindowClicked" event
 */
void hrswin_registerOnWindowCloseEvent(HRSWindow *window, void (*onWindowClose)(HRSWindow *window));

/*
 * Changes the name of the specified window.
 */
void hrswin_changeName(HRSWindow *window, string_t newName);

/*
 * Changes the size of the specified window.
 */
void hrswin_changeWindowSize(HRSWindow *window, HRSSize2 newSize);

/*
 * Changes the background color of the specified window.
 */
void hrswin_changeBackgroundColor(HRSWindow *window, HRSColor backgroundColor);

/*
 * Applies changes made directly to the HRSWindow values.
 * It is not recommended to change the values directly, as it may cause strange errors,
 * especially if you forget to use this function.
 */
void hrswin_applyChanges(HRSWindow *window);

/*
 * Frees the specified window and its resources.
 */
void hrswin_free(HRSWindow *window);

#endif