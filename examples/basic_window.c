// Defining the OpenGL version of this exemple
#define HRS_OPENGL_MAJOR_VERSION 3
#define HRS_OPENGL_MINOR_VERSION 3

#include "heleris/fw/fw.h"

int main() {

    // Creating a HRSGLContext, which is a struct to store and manage GL Context features, like program loop, gl functions loader, window maker and etc.
    HRSGLContext *context = hrsglc_create();

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
    hrswin_changeBackgroundColor(context->_window, hrsclr_fromHexa("#8080FF"));
    
    // Start program loop
    hrsglc_startLoop(context);

    // Terminate and free the HRSGLContext and HRSWindow
    hrsglc_terminate(context);

    return 0;
}
