#ifndef HELERIS_FRAMEWORK_GLOBAL_INCLUDE_H
#define HELERIS_FRAMEWORK_GLOBAL_INCLUDE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define HELERIS_OPEN_GL_INCLUDE_ALREADY // For files that need to include Glad and GLFW libs

// High order main files
#include "src/headers/error_codes.h"
#include "src/types.h"

// Error Handler files
#include "src/error_handle/headers/error_printer.h"

// Elements files
#include "src/elements/headers/color.h"
#include "src/elements/headers/size2.h"
#include "src/elements/headers/vector2.h"
#include "src/elements/headers/rectangle.h"

// Input files
#include "src/input/mouse/headers/mouse_click.h"
#include "src/input/mouse/headers/mouse_input.h"
#include "src/input/headers/input.h"

// Low order main files
#include "src/headers/window.h"

#endif