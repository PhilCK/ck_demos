#include <math.h>


/* --------------------------------------------------------- [ Demo Info ] -- */


static const char *
demo_name = "Cube Rotate";


static const char *
demo_desc = "Create a cube and spin it";


static const char *
demo_link = "http://republicofalmost.com/2018/08/25/gl_hello_world.html";


/* --------------------------------------------------------- [ Demo Data ] -- */


static const char *
demo_vs_src = "";


static const char *
demo_fs_src = "";


static const float
demo_vbo[] = {0.f};


static const unsigned
demo_ibo[] = {1};


/* ---------------------------------------------------- [ Demo Interface ] -- */


static struct demo_data {
        GLuint program;
        GLuint vbo, ibo;

        float time;

        float proj_mat[16];
        float view_mat[16];
        float world_mat[16];
} demo = {0};


static int 
demo_start()
{
        /* create program */

        /* create mesh */

        
        return 1;
}


static int 
demo_tick()
{
        glClearColor(0, 1, 0.2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* time is used to calculate the spin */
        demo.time += 0.016f;

        /* calculate mats */

        /* bind program and vbo */

        /* bind input format */

        /* draw cube */

        return 1;  
}


static int 
demo_end()
{
        /* free gl resources */
        return 1;
}


static int
demo_resize(int width, int height) {
        glViewport(0, 0, width, height);
        return 1;
}

