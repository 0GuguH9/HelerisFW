#ifndef HELERIS_GL_CONTEXT_H
#define HELERIS_GL_CONTEXT_H

#include "window.h"

#ifndef HELERIS_OPEN_GL_INCLUDE_ALREADY
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define HELERIS_OPEN_GL_INCLUDE_ALREADY
#endif

// Enumeration of OpenGL major supported versions (Major.Minor)
enum EHRSMajorVersion {
    HRS_GL_MAJOR_TREE = 3,
    HRS_GL_MAJOR_FOUR,
};

// Enumeration of OpenGL profile types
enum EHRSProfileType {
    HRS_GL_CORE_PROFILE = GLFW_OPENGL_CORE_PROFILE,
    HRS_GL_COMPATIBILITY_PROFILE = GLFW_OPENGL_COMPAT_PROFILE, // Avoid this profile type
};

// Structure representing an OpenGL context
typedef struct HRSGLContext {
    bool_t hasBeenInitialized;
    enum EHRSProfileType profileType;    // OpenGL profile type
    enum EHRSMajorVersion majorVersion;  // Major version of OpenGL
    int minorVersion;                    // Minor version of OpenGL
    int swapCooldown;                    // Cooldown between update and Draw (calls only) 
    bool_t useVSync;                     // Use V-Sync?
    float fps;                           // Frames per second
    HRSWindow *currentWindow;            // Pointer to the current window
    void (*onUpdate)(double deltaTime);  // Update callback
    void (*onDraw)();                    // Draw callback
} HRSGLContext;

/*
 * Creates a new OpenGL context.
 */
HRSGLContext* hrsglc_create(enum EHRSMajorVersion majorVersion, int minorVersion, enum EHRSProfileType profileType);

/*
 * Initializes the OpenGL context.
 */
void hrsglc_init(HRSGLContext *context);

/*
 * Sets the active window for the OpenGL context.
 */
void hrsglc_useWindow(HRSGLContext *context, HRSWindow *window);

/*
 * Register the update callback
 */
void hrsglc_registerUpdateCallback(HRSGLContext *context, void (*onUpdate)(double deltaTime));

/*
 * Register the draw callback
 */
void hrsglc_registerDrawCallback(HRSGLContext *context, void (*onDraw)());

/*
 * Sets the update cycle cooldown (update and draw calls) for the OpenGL context in seconds.
 */
void hrsglc_cycleCooldown(HRSGLContext *context, double cooldown);

/*
 * Set the new V-Sync state
 */
void hrsglc_vSync(HRSGLContext *context, bool_t newState);

/*
 * Starts the main loop for the OpenGL context.
 * You can make your own loop.
 */
void hrsglc_startLoop(HRSGLContext *context);

/*
 * Close the main loop for the OpenGL context.
 */
void hrsglc_closeLoop(HRSGLContext *context);

/*
 * Swaps the buffers for the OpenGL context.
 */
void hrsglc_swapBuffers(HRSGLContext *context);

/*
 * Assert the context is alreadt initialized. Can stop the program flow.
 */
void hrsglc_assertIsAlredyInitialized(HRSGLContext *context);

/*
 * Terminates and frees the OpenGL context.
 */
void hrsglc_terminate(HRSGLContext *context);

#endif
