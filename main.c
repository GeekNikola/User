#include "ui.h"

void debug_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    vfprintf(stdout, format, args);

    va_end(args);

    // 刷新缓冲区
    fflush(stdout);
}

int cp_x;
int cp_y;
int offset_cpx;
int offset_cpy;
int w_posx;
int w_posy;
int buttonEvent;


char btn_move_string[30]="按下移动窗口";
// 弹出对话框状态
int popup_close_active = 0;
#define NK_POPUP_CLOSE_CONFIRM "是否关闭窗口和结束程序？"
void cursor_position_callback(GLFWwindow* window, double x, double y){
//    if (buttonEvent == 1) {
//        offset_cpx = x - cp_x;
//        offset_cpy = y - cp_y;
//    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        buttonEvent = 1;
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        cp_x = floor(x);
        cp_y = floor(y);
    }
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        buttonEvent = 0;
        cp_x = 0;
        cp_y = 0;
    }
}

// GLFW 窗口移动回调函数
void window_move_callback(GLFWwindow* window, int x, int y) {
    // 保存 GL 窗口的位置
    w_posx = x;
    w_posy = y;


}
/* ===============================================================
 *
 *                          EXAMPLE
 *
 * ===============================================================*/
/* This are some code examples to provide a small overview of what can be
 * done with this library. To try out an example uncomment the defines */
//#define INCLUDE_ALL
//#define INCLUDE_STYLE
//#define INCLUDE_CALCULATOR
//#define INCLUDE_CANVAS
//#define INCLUDE_OVERVIEW
//#define INCLUDE_NODE_EDITOR

//#define STYLE_DARK



#ifdef INCLUDE_ALL
  #define INCLUDE_STYLE
  #define INCLUDE_CALCULATOR
  #define INCLUDE_CANVAS
  #define INCLUDE_OVERVIEW
  #define INCLUDE_NODE_EDITOR
#endif

#ifdef INCLUDE_STYLE
  #include "../demo/common/style.c"
#endif
#ifdef INCLUDE_CALCULATOR
  #include "../demo/common/calculator.c"
#endif
#ifdef INCLUDE_CANVAS
  #include "../demo/common/canvas.c"
#endif
#ifdef INCLUDE_OVERVIEW
  #include "../demo/common/overview.c"
#endif
#ifdef INCLUDE_NODE_EDITOR
  #include "../demo/common/node_editor.c"
#endif




/* ===============================================================
 *
 *                          DEMO
 *
 * ===============================================================*/
static void error_callback(int e, const char *d)
{printf("Error %d: %s\n", e, d);}

int main(void)
{
    /* Platform */
    struct nk_glfw glfw = {0};
    static GLFWwindow *win;
    int width = 0, height = 0;
    struct nk_context *ctx;
    struct nk_colorf bg;
    struct nk_vec2 NK_win_size;
    struct nk_vec2 NK_win_pos;

    /* GLFW */
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {

        //fprintf(stdout, "[GFLW] failed to init!\n");
        debug_printf("[GFLW] failed to init!\n");

        exit(1);
    }

    // 提示 GLFW 不要显示窗口边框
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Nuklear_GLFW", NULL, NULL);


//    glfwSetCursorPosCallback(win, cursor_position_callback);
     // glfwSetMouseButtonCallback(win, mouse_button_callback);//估计鼠标回调已经被nuklear接管所以无效
    // 设置窗口移动回调函数
    glfwSetWindowPosCallback(win, window_move_callback);

    glfwMakeContextCurrent(win);
    glfwGetWindowSize(win, &width, &height);
    glfwGetWindowPos(win, &w_posx, &w_posy);

    /* OpenGL */
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glewExperimental = 1;
    if (glewInit() != GLEW_OK) {
//        fprintf(stderr, "Failed to setup GLEW\n");
        debug_printf("Failed to setup GLEW\n");
        exit(1);
    }

    ctx = nk_glfw3_init(&glfw, win, NK_GLFW3_INSTALL_CALLBACKS);
    /* Load Fonts: if none of these are loaded a default font will be used  */
    /* Load Cursor: if you uncomment cursor loading please hide the cursor */
    {struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&glfw, &atlas);

    /*添加中文支持*/
    struct nk_font_config cfg = nk_font_config(22);
           //cfg.merge_mode = nk_true;
           cfg.range = nk_font_chinese_glyph_ranges();
           //cfg.coord_type = NK_COORD_PIXEL;


    struct nk_font *droid = nk_font_atlas_add_from_file(atlas, "./CangErYuYangTiW03-2.ttf", 32, &cfg);
    /*struct nk_font *roboto = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Roboto-Regular.ttf", 14, 0);*/
    /*struct nk_font *future = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13, 0);*/
    /*struct nk_font *clean = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyClean.ttf", 12, 0);*/
    /*struct nk_font *tiny = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyTiny.ttf", 10, 0);*/
    /*struct nk_font *cousine = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Cousine-Regular.ttf", 13, 0);*/
    nk_glfw3_font_stash_end(&glfw);
    /*nk_style_load_all_cursors(ctx, atlas->cursors);*/
    nk_style_set_font(ctx, &droid->handle);}

    #ifdef INCLUDE_STYLE
    /* ease regression testing during Nuklear release process; not needed for anything else */
    #ifdef STYLE_WHITE
    set_style(ctx, THEME_WHITE);
    #elif defined(STYLE_RED)
    set_style(ctx, THEME_RED);
    #elif defined(STYLE_BLUE)
    set_style(ctx, THEME_BLUE);
    #elif defined(STYLE_DARK)
    set_style(ctx, THEME_DARK);
    #endif
    #endif

    bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
    while (!glfwWindowShouldClose(win))
    {
        /* Input */
        glfwPollEvents();



        nk_glfw3_new_frame(&glfw);

        /* GUI */
        if (nk_begin(ctx, NK_WIN_title_name, nk_rect(0,0, WINDOW_WIDTH, WINDOW_HEIGHT),
            NK_WINDOW_BORDER|NK_WINDOW_SCALABLE|NK_WINDOW_BACKGROUND|NK_WINDOW_MOVABLE|
            NK_WINDOW_TITLE))

            //NK_WINDOW_BORDER
            //NK_WINDOW_MOVABLE
            //NK_WINDOW_MINIMIZABLE

{


            nk_layout_row_static(ctx, 30, 200, 3);

            if (nk_button_label(ctx, "按下关闭窗口"))
            {
                printf("close\n");
                popup_close_active=1;
//                nk_end(ctx);  // 关闭窗口
//                 break;  // 退出主循环

            }

            ui_main(win,ctx);










}
        NK_win_size=nk_window_get_size(ctx);
       // 获取NK控件窗口的新大小
        if(width!=NK_win_size.x||height!=NK_win_size.y)
        {
        width = NK_win_size.x;
        height = NK_win_size.y;
        glfwSetWindowSize(win, width, height);
        //debug_printf("w=%d,h=%d\n",width,height);
        }

        //获取NK控件窗口的新位置
         NK_win_pos= nk_window_get_position(ctx);

        if(NK_win_pos.x!=0||NK_win_pos.y!=0)
        {

        //移动GL窗程序总口然后NK控件窗口保持(0,0)
        //是的GL程序窗口隐藏边框标题栏后，还能通过NK的控件窗口移动GL程序窗口
         glfwGetWindowPos(win, &cp_x, &cp_y);
         glfwSetWindowPos(win, w_posx + NK_win_pos.x, w_posy +NK_win_pos.y);
         NK_win_pos.x -=cp_x-w_posx;
         NK_win_pos.y -=cp_x-w_posy;
         //printf("x=%f,y=%f\n",pos.x,pos.y);//NK的坐标是浮点型需要%f输出，%d则是0
        }



        // 渲染关闭确认对话框
        if (popup_close_active) {

            if (nk_popup_begin(ctx, NK_POPUP_STATIC, NK_POPUP_CLOSE_CONFIRM, NK_WINDOW_CLOSABLE, nk_rect((NK_win_size.x-400)/2, (NK_win_size.y-150)/2, 400, 150)))

            {
//                    debug_printf("popup\n");

                // 结束弹出窗口//
                // 在对话框中添加文本和按钮

                nk_label(ctx, "是否关闭窗口?", NK_TEXT_CENTERED);
              nk_layout_row_dynamic(ctx, 20, 3);


                // 如果按钮被点击
                if (nk_button_label(ctx, "确定")) {
                    printf("close\n");
                    nk_popup_close(ctx);// 关闭对话框
                    break;// 关闭窗口
                }

                // 添加间隔
                 nk_spacing(ctx, 1);

                // 如果按钮被点击
                if (nk_button_label(ctx, "取消")) {
                    // 关闭对话框
                    nk_popup_close(ctx);
                    popup_close_active=0;
                }



                nk_popup_end(ctx);



            }




    }






        nk_end(ctx);

        /* -------------- EXAMPLES ---------------- */
        #ifdef INCLUDE_CALCULATOR
          calculator(ctx);
        #endif
        #ifdef INCLUDE_CANVAS
          canvas(ctx);
        #endif
        #ifdef INCLUDE_OVERVIEW
          overview(ctx);
        #endif
        #ifdef INCLUDE_NODE_EDITOR
          node_editor(ctx);
        #endif
        /* ----------------------------------------- */

        /* Draw */
        glfwGetWindowSize(win, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(bg.r, bg.g, bg.b, bg.a);
        /* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
         * with blending, scissor, face culling, depth test and viewport and
         * defaults everything back into a default state.
         * Make sure to either a.) save and restore or b.) reset your own state after
         * rendering the UI. */
        nk_glfw3_render(&glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
        glfwSwapBuffers(win);
    }
    nk_glfw3_shutdown(&glfw);
    glfwTerminate();
    return 0;
}

