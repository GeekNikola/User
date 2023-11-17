#ifndef UI_H
#define UI_H

/* nuklear - 1.32.0 - public domain */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

#define NK_KEYSTATE_BASED_INPUT

#include "nuklear.h"
#include "nuklear_glfw_gl3.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024




#define NK_WIN_title_name "例程"
//#define INCLUDE_ALL
#define INCLUDE_STYLE
//#define INCLUDE_CALCULATOR
//#define INCLUDE_CANVAS
//#define INCLUDE_OVERVIEW
//#define INCLUDE_NODE_EDITOR

#define STYLE_BULE

void ui_main(GLFWwindow *win,struct nk_context *ctx);
#endif // UI_H
