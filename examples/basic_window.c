#include "heleris/fw/fw.h" // you can use "heleris/fw/gl_context.h", "heleris/fw/window.h", "heleris/fw/size.h" and "heleris/fw/elements/color.h"

int main() {

    // Creating a HRSGLContext, which is a struct to store and manage GL Context features, like program loop, gl functions loader, window maker and etc.
    HRSGLContext *context = hrsglc_create(HRS_GL_MAJOR_THREE, 3, HRS_GL_CORE_PROFILE);

    // Creating the window...
    HRSWindow *window = hrswin_create("Simple Window", hrssz_create(800, 600), FALSE);
 
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
    
    // Start program loop
    hrsglc_startLoop(context);

    // Terminate and free the HRSGLContext and HRSWindow
    hrsglc_terminate(context);

    return 0;
}
