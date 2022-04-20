#include <stdio.h>
#include <stdlib.h>
#include "utils/gfx/gfx.h"
#include "utils/vec2/vec2.h"

#define HEIGHT 1080
#define WIDTH 1920
#ifndef _CHAMPS_
#define _CHAMPS_
// void drawCircle(struct gfx_context_t *ctxt, int x, int y, int r, uint32_t color);
#define k 9e9

typedef struct
{
    double q;
    vec2 pos;
} charge_t;

void draw_disque(struct gfx_context_t *ctxt, int x_cord, int y_cord, int r, uint32_t color);

void draw_circle(struct gfx_context_t *ctxt, coordinates c, uint32_t radius, uint32_t color);

double delta_x(int width, int height);

/**
 * @brief
 * calcule champs de charge en un point
 */
double compute_champs(charge_t c, vec2 p)
{
    return (k * c.q) / pow(vec2_norm(vec2_sub(p, c.pos)), 2);
}

/**
 * @brief
    Compute E*qP/norm(qP)
    Return false if norm(qP) < eps
 */
bool compute_e(charge_t c, vec2 p, double eps, vec2 *e)
{

    vec2 qP = vec2_sub(p, c.pos);
    double norm_qP = vec2_norm(qP);
    if (norm_qP < eps)
        return false;
    else
    {
        double E = compute_champs(c, p);
        *e = vec2_mul(1 / norm_qP, qP);
    }
}

/**
 * @brief
    Compute the normalized sum of Ei*qiP/norm(qiP)
    Return false if for some qiP, norm(qiP) < eps
 */
bool compute_total_normalized_e(charge_t *charges, int num_charges, vec2 p, double eps, vec2 *e)
{

    vec2 tmp;
    vec2 normalized_sum;
    for (int i = 0; i < num_charges; i++)
    {

        bool com_charge = compute_e(charges[i], p, eps, &tmp);
        if (com_charge)
        {
            normalized_sum = vec2_add(sum, tmp);
        }
        else
            return false;
    }

    *e = normalized_sum;
    return true;
}

/**
 * @brief
    Compute and then draw all the points belonging to a field line,
    starting from pos0.
    Returns false if pos0 is not a valid position
    (for example if pos0 is too close to a charge).
 */
static bool draw_field_line(struct gfx_context_t *ctxt, charge_t *charges, int num_charges, double dx, vec2 pos0, double x0, double x1, double y0, double y1);

/**
 * @brief
    Draw all the charges
    A circle with minus sign for negative charges
    A circle with a plus sign for positive charges
 */
static void draw_charges(struct gfx_context_t *context, charge_t *charges, int num_charges, double x0, double x1, double y0, double y1);
#endif