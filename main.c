#include "champ.h"

int main()
{
    // utils pour générer les charges aléatoires
    srand(time(NULL));

    struct gfx_context_t *ctxt = gfx_create("ligne de champs", WIDTH, HEIGHT);
    if (!ctxt)
    {
        fprintf(stderr, "Graphics initialization failed!\n");
        return EXIT_FAILURE;
    }

    gfx_clear(ctxt, COLOR_BLACK);

    // simulate les lignes de champs
    simulate_champs(ctxt);
    while (gfx_keypressed() != SDLK_ESCAPE)
    {
        gfx_present(ctxt);
        sleep(0.5);
    }

    gfx_destroy(ctxt);
    return EXIT_SUCCESS;
}