
#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#include <emscripten.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif

#include <SDL2/SDL.h>
#include <stdio.h>

/* comment out one demo to run */
/* #include "color_change.c" */
#include "cube_rotate.c"


/* ----------------------------------------------------- [ SDL Interface ] -- */


/* SDL details */
struct sdl_app {
        SDL_Window *window;
        SDL_GLContext *gl_context;
        GLuint vao;
} app = {0};


int
app_start()
{
        SDL_Init(SDL_INIT_EVERYTHING);

        Uint32 flags = SDL_WINDOW_RESIZABLE |
                       SDL_WINDOW_OPENGL;

        app.window = SDL_CreateWindow(
                demo_name, 
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                640,
                480,
                flags 
        );

        #ifndef __EMSCRIPTEN__
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(
                SDL_GL_CONTEXT_PROFILE_MASK,
                SDL_GL_CONTEXT_PROFILE_CORE);
        #else
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(
                SDL_GL_CONTEXT_PROFILE_MASK,
                SDL_GL_CONTEXT_PROFILE_ES);
        #endif
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 2);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

        app.gl_context = SDL_GL_CreateContext(app.window);
        SDL_GL_MakeCurrent(app.window, app.gl_context);
        SDL_GL_SetSwapInterval(1);

        #ifndef __EMSCRIPTEN__
        glGenVertexArrays(1, &app.vao);
        #endif

        return app.window ? 1 : 0;
}


int
app_tick()
{
        #ifndef __EMSCRIPTEN__
        glBindVertexArray(app.vao);
        #endif

        /* demo draws */
        demo_tick();

        /* update SDL */
        SDL_Event evt;

        while(SDL_PollEvent(&evt)) {
                if(evt.type == SDL_QUIT) {
                        return 0;
                }
                else if(evt.type == SDL_WINDOWEVENT) {
                        if(evt.window.event == SDL_WINDOWEVENT_RESIZED) {
                                demo_resize(
                                    evt.window.data1,
                                    evt.window.data2);
                        }
                }
        }

        /* present */
        SDL_GL_SwapWindow(app.window);

        return 1;
}


void
app_end()
{ 
        #ifndef __EMSCRIPTEN__
        glDeleteVertexArrays(1, &app.vao);
        #endif

        SDL_DestroyWindow(app.window);
        SDL_Quit();
}


/* -------------------------------------------------- [ Emscripten Hooks ] -- */


#ifdef __EMSCRIPTEN__
void
em_tick_wrapper() {
        app_tick();
}

EMSCRIPTEN_KEEPALIVE
int
demo_app_resize(int width, int height) {
        SDL_SetWindowSize(app.window, width, height);
        return demo_resize(width, height);
}

EMSCRIPTEN_KEEPALIVE
const char *
demo_app_name() {
        return demo_name;
}

EMSCRIPTEN_KEEPALIVE
const char *
demo_app_desc() {
        return demo_desc;
}

EMSCRIPTEN_KEEPALIVE
const char *
demo_app_link() {
        return demo_link;
}
#endif


/* ------------------------------------------------------- [ Application ] -- */


int
main()
{
        printf("Start\n");
        if(!app_start() || !demo_start()) {
                printf("Failed to startup app\n");
                return 0;
        }
        
        #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(em_tick_wrapper, -1, 1);
        #else
        while(app_tick());
        #endif

        printf("Quit\n");
        demo_end();
        app_end();

        return 0;
}
