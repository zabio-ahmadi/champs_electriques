#include "utils/gfx/gfx.h"
#include "champ.h"

// Render some white noise.
// @param context graphical context to use.
// static void render(struct gfx_context_t *context, int width, int height)
// {
//     gfx_clear(context, COLOR_BLUE);
// }

/// Program entry point.
/// @return the application status code (0 if success).

int main()
{

    struct gfx_context_t *ctxt = gfx_create("ligne de champs", WIDTH, HEIGHT);
    if (!ctxt)
    {
        fprintf(stderr, "Graphics initialization failed!\n");
        return EXIT_FAILURE;
    }

    while (gfx_keypressed() != SDLK_ESCAPE)
    {

        gfx_clear(ctxt, COLOR_BLACK);
        // render(ctxt, WIDTH, HEIGHT);

        coordinates c;
        c.row = 400;
        c.column = 400;
        // draw a line
        for (int i = 0; i < 100; i++)
        {
            gfx_putpixel(ctxt, c.column + i, c.row, COLOR_GREEN);
        }

        // coordinates c;
        // c.row = 400;
        // c.column = 400;
        // draw_circle(ctxt, c, 50, COLOR_BLUE);
        gfx_present(ctxt);
    }

    gfx_destroy(ctxt);
    return EXIT_SUCCESS;
}