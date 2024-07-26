#ifndef HELERIS_FRAMEWORK_GLOBAL_INCLUDE_H
#define HELERIS_FRAMEWORK_GLOBAL_INCLUDE_H

#ifndef HRS_OPENGL_MAJOR_VERSION
#define HRS_OPENGL_MAJOR_VERSION 3
#endif

#ifndef HRS_OPENGL_MINOR_VERSION
#define HRS_OPENGL_MINOR_VERSION 3
#endif

#if HRS_OPENGL_MAJOR_VERSION < 3
#error "Your HRS_OPENLG_MAJOR_VERSION need to be 3 or higher"
#endif

#if HRS_OPENGL_MAJOR_VERSION == 3 && HRS_OPENGL_MINOR_VERSION < 3
#error "Your HRS_OPENGL_MINOR_VERSION need to be 3 or higher with HRS_OPENGL_MAJOR_VERSION == 3"
#endif

// Debug define is: HRS_DEBUG

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

// Content
#include "content/texture.h"
#include "content/content_loader.h"

// Graphics
#include "graphics/shader.h"
#include "graphics/shader_program.h"
#include "graphics/vbo.h"
#include "graphics/vao.h"
#include "graphics/render_options.h"
#include "graphics/device_graphics.h"
#include "graphics/render.h"

// Input files (not implemented)

// Low order main files
#include "window.h"
#include "gl_context.h"

// Presets

// RenderBatch

#ifdef HRS_INCLUDE_RENDER_GRAPHICS
#include "graphics/render_batch/render_batch.h"
#endif

#endif