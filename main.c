#include "champ.h"

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

        charge_t charges[2];
        charge_t c1;
        c1.pos.x = 0.7;
        c1.pos.y = 0.7;
        c1.q = 4;

        charge_t c2;
        c2.pos.x = 0.1;
        c2.pos.y = 0.9;
        c2.q = 6;

        charges[0] = c1;
        charges[1] = c2;

        // vec2 tmp;
        for (int i = 0; i < nb_charges; i++)
        {

            coordinates c_coord = position_to_coordinates(charges[i].pos, WIDTH, HEIGHT, X0, X1, Y0, Y1);
            draw_charges(ctxt, c_coord, i, 10, (i == 1) ? COLOR_RED : COLOR_BLUE);
        }
        gfx_present(ctxt);
    }

    gfx_destroy(ctxt);
    return EXIT_SUCCESS;
}