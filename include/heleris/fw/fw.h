#ifndef HELERIS_FRAMEWORK_GLOBAL_INCLUDE_H
#define HELERIS_FRAMEWORK_GLOBAL_INCLUDE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define HELERIS_OPEN_GL_INCLUDE_ALREADY // For files that need to include Glad and GLFW libs

// High order main files
#include "errors/error_codes.h"
#include "types.h"

// Error files
#include "errors/error.h"
#include "errors/error_presets.h"

// Elements files
#include "elements/color.h"
#include "elements/vector2.h"
#include "elements/size.h"
#include "elements/rectangle.h"

// Input files (not implemented)

// Low order main files
#include "window.h"
#include "gl_context.h"

#endif