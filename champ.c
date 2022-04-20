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

double compute_champs(charge_t c, vec2 p)
{
    return (k * c.q) / pow(vec2_norm(vec2_sub(p, c.pos)), 2);
}

bool compute_e(charge_t c, vec2 p, double eps, vec2 *e)
{

    vec2 qP = vec2_sub(p, c.pos);
    double norm_qP = vec2_norm(qP);
    double E = compute_champs(c, p);
    *e = vec2_mul(E, vec2_mul(1 / norm_qP, qP));

    return norm_qP > eps;
}

bool compute_total_normalized_e(charge_t *charges, int num_charges, vec2 p, double eps, vec2 *e)
{

    vec2 tmp;
    vec2 normalized_sum;
    for (int i = 0; i < num_charges; i++)
    {

        bool com_charge = compute_e(charges[i], p, eps, &tmp);
        normalized_sum = vec2_add(normalized_sum, tmp);
        if (!com_charge)
            return false;
    }

    *e = normalized_sum;
    return true;
}

// display charges position in [0: 1] universe
coordinates position_to_coordinates(vec2 p, int width, int height, double x0, double x1, double y0, double y1)
{
    coordinates coord;
    coord.row = (height * (p.y - y0) / (y1 - y0));
    coord.column = (width * (p.x - x0) / (x1 - x0));
    return coord;
}

void draw_charges(struct gfx_context_t *ctxt, coordinates c, bool type, uint32_t radius, uint32_t color)
{
    const int32_t diameter = (radius * 2);
    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    // draw lines
    int limit = ((20 / (double)100) * radius);

    if (type)
    { // charge is positive

        uint32_t i = (c.row - radius) + limit;
        while (i <= ((c.row + radius) - limit))
        {
            gfx_putpixel(ctxt, i, c.column, color);
            i++;
        }

        uint32_t j = (c.column - radius) + limit;
        while (j <= ((c.column + radius) - limit))
        {
            gfx_putpixel(ctxt, c.row, j, color);
            j++;
        }
    }
    else
    {
        uint32_t i = (c.row - radius) + limit;
        while (i <= ((c.row + radius) - limit))
        {
            gfx_putpixel(ctxt, i, c.column, color);
            i++;
        }
    }

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
        else
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}