#include "champ.h"

void draw_circle(struct gfx_context_t *ctxt, coordinates c, uint32_t radius, uint32_t color)
{
    const int32_t diameter = (radius * 2);
    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        gfx_putpixel(ctxt, c.row + x, c.column - y, color);
        gfx_putpixel(ctxt, c.row + x, c.column + y, color);
        gfx_putpixel(ctxt, c.row - x, c.column - y, color);
        gfx_putpixel(ctxt, c.row - x, c.column + y, color);
        gfx_putpixel(ctxt, c.row + y, c.column - x, color);
        gfx_putpixel(ctxt, c.row + y, c.column + x, color);
        gfx_putpixel(ctxt, c.row - y, c.column - x, color);
        gfx_putpixel(ctxt, c.row - y, c.column + x, color);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void draw_disque(struct gfx_context_t *ctxt, int x_cord, int y_cord, int r, uint32_t color)
{
    // Consider a rectangle of size N*N
    int N = 2 * r + 1;

    int x = x_cord, y = y_cord; // Coordinates inside the rectangle

    // Draw a square of size N*N.
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // Start from the left most corner point
            x = i - r;
            y = j - r;

            // If this point is inside the circle, print it
            if (x * x + y * y <= r * r + 1)
            {
                gfx_putpixel(ctxt, x + WIDTH / 2, y + HEIGHT / 2, color);
            }
            else
            {
                gfx_putpixel(ctxt, x, y, COLOR_BLACK);
            }
        }
    }
}

double delta_x(int width, int height)
{
    return 1 / sqrt(pow(2, width) + pow(2, height));
}

bool compute_e(charge_t c, vec2 p, double eps, vec2 *e)
{
}