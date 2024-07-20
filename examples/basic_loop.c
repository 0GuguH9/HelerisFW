#include "heleris/fw/gl_context.h"

// Protyping functions

void onUpdate(HRSGLContext *context, double deltaTime);

void onFixedUpdate(HRSGLContext *context, double fixedDeltaTime);

void onDraw(HRSGLContext *context, HRSDeviceGraphics deviceGraphics);

int main() {

    // Creating a HRSGLContext, which is a struct to store and manage GL Context features, like program loop, gl functions loader, window maker and etc.
    HRSGLContext *context = hrsglc_create(HRS_GL_MAJOR_THREE, 3, HRS_GL_CORE_PROFILE);

    // Creating the window...
    HRSWindow *window = hrswin_create("Simple Window", hrssz_create(800, 600), false);
 
    // This initialize all glfw (window and input), glad (gl functions) and window (HRSWindow *)
    hrsglc_init(context, window);

    // Create a color struct from hexa. This hexa color can be formated in these formats:
    /*
     * RRGGBB
     * #RRGGBB
     * RRGGBBAA
     * #RRGGBBAA
     */
    hrswin_changeBackgroundColor(context->window, hrsclr_fromHexa("#8080FF"));
    
    // Register an update function
    hrsglc_registerUpdateCallback(context, onUpdate);

    // Register a fixed update function, called 60 times per second. 
    // You can set the "times per second" (aka cycle cooldown) using:
    /*
     * hrsglc_cycleCooldown(context, 1000 / times per second);
     */
    // Warn: DON'T SET THE SAME AS UPDATE CALLBACK! This will call 2 times in a row with diferrent delta time
    hrsglc_registerFixedUpdateCallback(context, onFixedUpdate);

    // The update sequence is:
    /*
     * Calculate FPS
     * Input update
     * Update
     * Fixed Update
     * Window cleared
     * Draw
     * Window events
     */

    // Register a draw function.
    hrsglc_registerDrawCallback(context, onDraw);

    // Start program loop
    hrsglc_startLoop(context);

    // Terminate and free the HRSGLContext and HRSWindow
    hrsglc_terminate(context);
}

// Called every frame draw. Use for exemple motion.
void onUpdate(HRSGLContext *context, double deltaTime) {

    printf("Update call! With delta time: %f", deltaTime);
}

void onFixedUpdate(HRSGLContext *context, double fixedDeltaTime) {

    printf("Fixed update call! With delta time: %f", fixedDeltaTime);
}

void onDraw(HRSGLContext *context, HRSDeviceGraphics deviceGraphics) {

    printf("Draw call!");
}
