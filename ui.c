#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#include "ui.h"

void ui_main(GLFWwindow *win,struct nk_context *ctx)
{

    // 你的 GUI 逻辑
    enum {EASY, HARD};
    static int op = EASY;
    static int property = 20;


    nk_layout_row_dynamic(ctx, 30, 2);
    if (nk_option_label(ctx, "简单", op == EASY)) op = EASY;
    if (nk_option_label(ctx, "困难", op == HARD)) op = HARD;

    nk_layout_row_dynamic(ctx, 25, 1);

}
