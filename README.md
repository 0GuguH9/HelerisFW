# Heleris FW

Heleris FW is a C framework designed to help create programs or (mainly 2D) games using OpenGL. The minimum supported version of OpenGL is 3.3.

## Current Features

- **Facilitates the creation of Window and GL Context**: Offers two structs, `HRSGLContext` and `HRSWindow`, to simplify the creation and management of GLFW windows and OpenGL contexts.
- **Program loop facilitation**: Provides a loop that provides two updates, the onUpdate (called every frame) and the onFixedUpdate (called every cycle cooldown, the default is 60 per second), each with one delta time. Allows setting a maximum FPS (Frames Per Second), cycle cooldown (for onFixedUpdate), vertical synchronization (V-Sync), delta time (time difference between frames), and easy creation of backgrounds.

## Getting Started

### Prerequisites

- Hardware compatible with OpenGL 3.3
- C compiler (GCC, Clang, etc.)
- [GLFW](https://www.glfw.org/), OpenGL window and input manager library

#### Third-party internal libraries

- [GLAD](https://glad.dav1d.de/), OpenGL functions loader library
- [stb_image.h](https://github.com/nothings/stb/tree/master), "single-file public domain (or MIT licensed) libraries for C/C++", used for texture loading
- [FastNoiseLite](https://github.com/Auburn/FastNoiseLite), "Fast Portable Noise Library", used for noise generation

## Usage

All code is designed with internal use in mind. In case of errors, it is standard for resources to stop the program flow to avoid major issues. To avoid this, use C++ try/catch/finally feature.

### Example

This example creates a window with the color `#8080FF`, 800x600 in size, using the minimum OpenGL version. Here is the simple code:

```c
#include "heleris/fw/fw.h" // you can use "heleris/fw/gl_context.h", "heleris/fw/window.h", "heleris/fw/size.h" and "heleris/fw/elements/color.h"

int main() {

    HRSGLContext *context = hrsglc_create(HRS_GL_MAJOR_THREE, 3, HRS_GL_CORE_PROFILE);

    HRSWindow *window = hrswin_create("Simple Window", hrssz_create(800, 600), FALSE);

    hrsglc_init(context, window);

    hrswin_changeBackgroundColor(context->window, hrsclr_fromHexa("8080FF"));

    hrsglc_startLoop(context);

    hrsglc_terminate(context);

    return 0;
}
```

*To see other examples, visit the [examples directory](https://github.com/0GuguH9/HelerisFW/tree/master/examples/)*

## License

This project is licensed under the MIT License - see the [LICENSE file](https://github.com/0GuguH9/HelerisFW/blob/master/LICENSE) for details.

## Contact

For issues, use GitHub's [Issues](https://github.com/0GuguH9/HelerisFW/issues) feature. Avoid contacting me directly for usage problems. If you encounter problems with certain functions resulting in unexpected or undocumented behavior, contact me on Discord: '0guguh9'.
