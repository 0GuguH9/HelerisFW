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
    enum EHRSProfileType profileType;                                           // OpenGL profile type
    enum EHRSMajorVersion majorVersion;                                         // Major version of OpenGL
    int minorVersion;                                                           // Minor version of OpenGL
    int swapCooldown;                                                           // Cooldown between update and Draw (calls only) 
    bool_t useVSync;                                                            // Use V-Sync?
    float estimatedFPS;                                                         // Estimated frames per second based on last deltaTime
    float fps;                                                                  // Frames per second
    HRSWindow *window;                                                          // Pointer to the current window
    void (*onUpdate)(struct HRSGLContext *context, double deltaTime);           // Update callback
    void (*onFixedUpdate)(struct HRSGLContext *context, double fixedDeltaTime); // Fixed Update callback
    void (*onDraw)(struct HRSGLContext *context);                               // Draw callback
} HRSGLContext;

/*
 * Creates a new OpenGL context.
 */
HRSGLContext* hrsglc_create(enum EHRSMajorVersion majorVersion, int minorVersion, enum EHRSProfileType profileType);

/*
 * Initializes the OpenGL context using GLFW and GLAD.
 * Ensures the correct setup and association with the given window.
 */
void hrsglc_init(HRSGLContext *context, HRSWindow *window);

/*
 * Register the update callback
 */
void hrsglc_registerUpdateCallback(HRSGLContext *context, void (*onUpdate)(HRSGLContext *context, double deltaTime));

/*
 * This only work if double update is activated.
 */
void hrsglc_registerFixedUpdateCallback(HRSGLContext *context, void (*onFixed)(HRSGLContext *context, double fixedDeltaTime));

/*
 * Register the draw callback
 */
void hrsglc_registerDrawCallback(HRSGLContext *context, void (*onDraw)(HRSGLContext *context));

/*
 * Sets the update cycle cooldown (fixed update calls) for the OpenGL context in seconds. 
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
 * Assert the context is already initialized. Can stop the program flow.
 */
void hrsglc_assertIsAlreadyInitialized(HRSGLContext *context);

/*
 * Terminates and frees the OpenGL context.
 */
void hrsglc_terminate(HRSGLContext *context);

#endif

