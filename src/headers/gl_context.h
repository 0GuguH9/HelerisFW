#ifndef HELERIS_GL_CONTEXT_H
#define HELERIS_GL_CONTEXT_H

#include "window.h"

// Enumeration of OpenGL profile types
enum EHRSProfileType {
    HRS_GL_CORE_PROFILE,
    HRS_GL_COMPATIBILITY_PROFILE, // Avoid this profile type
};

// Structure representing an OpenGL context
typedef struct HRSGLContext {
    enum EHRSProfileType profileType;    // OpenGL profile type
    HRSWindow *currentWindow;            // Pointer to the current window
    int majorVersion;                    // Major version of OpenGL
    int minorVersion;                    // Minor version of OpenGL
    float fps;                           // Frames per second
    void (*onUpdate)(double deltaTime);  // Update callback
    void (*onDraw)();                    // Draw callback
} HRSGLContext;

/*
 * Creates a new OpenGL context.
 */
HRSGLContext* hrsglc_create(int majorVersion, int minorVersion, enum EHRSProfileType profileType, void (*onUpdate)(double deltaTime), void (*onDraw)());

/*
 * Initializes the OpenGL context.
 */
void hrsglc_init(HRSGLContext *context);

/*
 * Sets the active window for the OpenGL context.
 */
void hrsglc_activeWindow(HRSGLContext *context, HRSWindow *window);

/*
 * Sets the update cycle cooldown for the OpenGL context.
 */
void hrsglc_cicleCooldown(HRSGLContext *context, double cooldown);

/*
 * Starts the main loop for the OpenGL context.
 */
void hrsglc_startLoop(HRSGLContext *context);

/*
 * Requests to close the OpenGL context.
 */
void hrsglc_close(HRSGLContext *context);

/*
 * Swaps the buffers for the OpenGL context.
 */
void hrsglc_swapBuffers(HRSGLContext *context);

/*
 * Terminates and frees the OpenGL context.
 */
void hrsglc_terminate(HRSGLContext *context);

#endif
