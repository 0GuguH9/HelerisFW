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
    bool useVSync;                                                                    // Use V-Sync?
    enum EHRSProfileType _profileType;                                                // OpenGL profile type
    enum EHRSMajorVersion _majorVersion;                                              // Major version of OpenGL
    int minorVersion;                                                                 // Minor version of OpenGL
    float estimatedFPS;                                                               // Estimated frames per second based on last deltaTime
    float fps;                                                                        // Frames per second
    double swapCooldown;                                                              // Cycle cooldown of fixed update call back
    HRSWindow *_window;                                                                // Pointer to the current window
    void (*onPreUpdate)(struct HRSGLContext *_glContext, double deltaTime);           // Update before all Update callback
    void (*onPreFixedUpdate)(struct HRSGLContext *_glContext, double fixedDeltaTime); // Update pre Fixed Update callback
    void (*onFixedUpdate)(struct HRSGLContext *_glContext, double fixedDeltaTime);    // Fixed Update callback
    void (*onUpdate)(struct HRSGLContext *_glContext, double deltaTime);              // Update callback
    void (*onPostFixedUpdate)(struct HRSGLContext *_glContext, double fixedDeltaTime);// Fixed Update post Update callback
    void (*onPostUpdate)(struct HRSGLContext *_glContext, double deltaTime);          // Update after all Update callback
    void (*draw)(struct HRSGLContext *_glContext, HRSDeviceGraphics *_deviceGraphics);  // Draw callback
} HRSGLContext;

// Heap manipulation

/*
 * Create an heap object (an pointer to heap memory) of HRSGLContext. 
 * You can't create a HRSGLContext with another active.
 */
HRSGLContext* hrsglc_create();

/*
 * Init all OpenGL context for the application. 
 * You can't have more than one HRSGLContext actived in the same time.
 */
void hrsglc_init(HRSGLContext *_glContext, HRSWindow *_window);

/*
 * Assert that the HRSGLContext object is not nullptr and has been initialized.
 */
void hrsglc_assert(const HRSGLContext *_glContext);

/*
 * Terminates and frees the OpenGL context.
 */
void hrsglc_terminate(HRSGLContext *_glContext);

// Call backs

/*
 * Register the pre update callback.
 */
void hrsglc_registerPreUpdateCallback(HRSGLContext *_glContext, void (*onPreUpdate)(HRSGLContext *_glContext, double deltaTime));

/*
 * Register the update pre fixed update callback.
 */
void hrsglc_registerPreFixedUpdateCallback(HRSGLContext *_glContext, void (*onPreFixedUpdate)(HRSGLContext *_glContext, double fixedDeltaTime));

/*
 * Register the fixed update callback.
 */
void hrsglc_registerFixedUpdateCallback(HRSGLContext *_glContext, void (*onFixedUpdate)(HRSGLContext *_glContext, double fixedDeltaTime));

/*
 * Register the update callback.
 */
void hrsglc_registerUpdateCallback(HRSGLContext *_glContext, void (*onUpdate)(HRSGLContext *_glContext, double deltaTime));

/*
 * Register the update post fixed and update callback.
 */
void hrsglc_registerPostFixedUpdateCallback(HRSGLContext *_glContext, void (*onFixedUpdatePostUpdate)(HRSGLContext *_glContext, double fixedDeltaTime));

/*
 * Register the post update callback.
 */
void hrsglc_registerPostUpdateCallback(HRSGLContext *_glContext, void (*onPostUpdate)(HRSGLContext *_glContext, double deltaTime));

/*
 * Register the draw callback.
 */
void hrsglc_registerDrawCallback(HRSGLContext *_glContext, void (*draw)(HRSGLContext *_glContext, HRSDeviceGraphics *_deviceGraphics));

// Context struct sets

/*
 * Sets the update cycle cooldown (fixed update calls) for the OpenGL context in seconds. 
 */
void hrsglc_cycleCooldown(HRSGLContext *_glContext, const double cooldown);

/*
 * Starts the main loop for the OpenGL context.
 * You can make your own loop.
 */
void hrsglc_startLoop(HRSGLContext *_glContext);

/*
 * Close the main loop for the OpenGL context.
 */
void hrsglc_closeLoop(HRSGLContext *_glContext);

// GLContext sets

/*
 * Set the new V-Sync state
 */
void hrsglc_vSync(HRSGLContext *_glContext, const bool newState);

#endif