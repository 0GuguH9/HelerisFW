#ifndef HELERIS_GL_CONTEXT_H
#define HELERIS_GL_CONTEXT_H

#ifndef HELERIS_OPEN_GL_INCLUDE_ALREADY
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define HELERIS_OPEN_GL_INCLUDE_ALREADY
#endif

#include "heleris/fw/graphics/device_graphics.h"
#include "window.h"

// Enumeration of OpenGL major supported versions (Major.Minor)
enum EHRSMajorVersion {
    HRS_GL_MAJOR_THREE = 3,
    HRS_GL_MAJOR_FOUR,
};

// Enumeration of OpenGL profile types
enum EHRSProfileType {
    HRS_GL_CORE_PROFILE = GLFW_OPENGL_CORE_PROFILE,
    HRS_GL_COMPATIBILITY_PROFILE = GLFW_OPENGL_COMPAT_PROFILE, // Avoid this profile type
};

// Structure representing an OpenGL context
typedef struct HRSGLContext {
    bool hasBeenInitialized;
    bool useVSync;                                                                 // Use V-Sync?
    enum EHRSProfileType profileType;                                              // OpenGL profile type
    enum EHRSMajorVersion majorVersion;                                            // Major version of OpenGL
    int minorVersion;                                                              // Minor version of OpenGL
    float estimatedFPS;                                                            // Estimated frames per second based on last deltaTime
    float fps;                                                                     // Frames per second
    double swapCooldown;                                                           // Cycle cooldown of fixed update call back
    HRSWindow *window;                                                             // Pointer to the current window
    void (*onUpdatePreFixed)(struct HRSGLContext *context, double deltaTime);      // Update pre Fixed Update callback
    void (*onFixedUpdate)(struct HRSGLContext *context, double fixedDeltaTime);    // Fixed Update callback
    void (*onUpdate)(struct HRSGLContext *context, double deltaTime);              // Update callback
    void (*onFixedPostUpdate)(struct HRSGLContext *context, double fixedDeltaTime);// Fixed Update post Update callback
    void (*draw)(struct HRSGLContext *context, HRSDeviceGraphics deviceGraphics);  // Draw callback
} HRSGLContext;

// Heap manipulation

/*
 * Create an heap object (an pointer to heap memory) of HRSGLContext. 
 * You can't create a HRSGLContext with another active.
 */
HRSGLContext* hrsglc_create(const enum EHRSMajorVersion majorVersion, const int minorVersion, const enum EHRSProfileType profileType);

/*
 * Init all OpenGL context for the application. 
 * You can't have more than one HRSGLContext actived in the same time.
 */
void hrsglc_init(HRSGLContext *context, HRSWindow *window);

/*
 * Assert that the HRSGLContext object is not nullptr and has been initialized.
 */
void hrsglc_assert(const HRSGLContext *context);

/*
 * Terminates and frees the OpenGL context.
 */
void hrsglc_terminate(HRSGLContext *context);

// Call backs

/*
 * Register the update pre fixed update callback
 */
void hrsglc_registerUpdatePreFixedCallback(HRSGLContext *context, void (*onUpdatePreFixed)(HRSGLContext *context, double deltaTime));

/*
 * Register the fixed update callback
 */
void hrsglc_registerFixedUpdateCallback(HRSGLContext *context, void (*onFixedUpdate)(HRSGLContext *context, double fixedDeltaTime));

/*
 * Register the update callback
 */
void hrsglc_registerUpdateCallback(HRSGLContext *context, void (*onUpdate)(HRSGLContext *context, double deltaTime));

/*
 * Register the update post fixed and update callback
 */
void hrsglc_registerFixedPostUpdateCallback(HRSGLContext *context, void (*onUpdatePostFixed)(HRSGLContext *context, double fixedDeltaTime));

/*
 * Register the draw callback
 */
void hrsglc_registerDrawCallback(HRSGLContext *context, void (*draw)(HRSGLContext *context, HRSDeviceGraphics deviceGraphics));

// Context struct sets

/*
 * Sets the update cycle cooldown (fixed update calls) for the OpenGL context in seconds. 
 */
void hrsglc_cycleCooldown(HRSGLContext *context, const double cooldown);

/*
 * Starts the main loop for the OpenGL context.
 * You can make your own loop.
 */
void hrsglc_startLoop(HRSGLContext *context);

/*
 * Close the main loop for the OpenGL context.
 */
void hrsglc_closeLoop(HRSGLContext *context);

// GLContext sets

/*
 * Set the new V-Sync state
 */
void hrsglc_vSync(HRSGLContext *context, const bool newState);

#endif