#include <math.h>


/* --------------------------------------------------------- [ Demo Info ] -- */


static const char *
demo_name = "Color Swap";


static const char *
demo_desc = "Cycle RBG at different rates using sin/cos";


static const char *
demo_link = "http://www.google.com";


/* ---------------------------------------------------- [ Demo Interface ] -- */


static struct change_color {
        /* colors and rate of change */
        float r, dr;
        float g, dg;
        float b, db;

        GLuint vao;
} demo = {0};


static int 
demo_start()
{
        demo.r = 1.f;
        demo.dr = 0.004f;

        demo.g = 0.5f;
        demo.dg = 0.008f;

        demo.b = 1.f;
        demo.db = 0.016f;

        /*
        glGenVertexArrays(1, &demo.vao);
        glBindVertexArray(demo.vao);
        */

        return 1;
}


static int 
demo_tick()
{ 
        demo.r += demo.dr;
        demo.g += demo.dg;
        demo.b += demo.db;

        /* use trig functions to flip from 0 to 1 */
        float r = (float)cos(demo.r);
        float g = (float)sin(demo.g);
        float b = (float)cos(demo.b);

        r = (r / 0.5f) + 1.f;
        g = (g / 0.5f) + 1.f;
        b = (b / 0.5f) + 1.f;

        glClearColor(r, g, b, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        return 1;
}


static int 
demo_end()
{
        /*glDeleteVertexArrays(1, &demo.vao);*/
        return 1;
}


static int
demo_resize(int width, int height) {
        glViewport(0, 0, width, height);
        return 1;
}

