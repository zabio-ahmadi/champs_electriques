#include <stdio.h>
#include <stdlib.h>
#include "utils/gfx/gfx.h"
#include "utils/vec2/vec2.h"

#define HEIGHT 500
#define WIDTH 500
#ifndef _CHAMPS_
#define _CHAMPS_

#define k 9e9

#define X0 0
#define X1 1
#define Y0 0
#define Y1 1
#define nb_charges 2

typedef struct
{
   double q;
   vec2 pos;
} charge_t;

void draw_disque(struct gfx_context_t *ctxt, int x_cord, int y_cord, int r, uint32_t color);

void draw_circle(struct gfx_context_t *ctxt, coordinates c, uint32_t radius, uint32_t color);

/**
 * @brief
 * calcule champs de charge en un point
 *
 * E = k*q/r^2
 */
double compute_champs(charge_t c, vec2 p);

/**
 * @brief
    Compute E*qP/norm(qP)
    Return false if norm(qP) < eps
 */
bool compute_e(charge_t c, vec2 p, double eps, vec2 *e);

/**
 * @brief
    Compute the normalized sum of Ei*qiP/norm(qiP)
    Return false if for some qiP, norm(qiP) < eps
 */
bool compute_total_normalized_e(charge_t *charges, int num_charges, vec2 p, double eps, vec2 *e);

coordinates position_to_coordinates(vec2 p, int width, int height, double x0, double x1, double y0, double y1);
double delta_x(int width, int height);

void draw_charges(struct gfx_context_t *ctxt, coordinates c, bool type, uint32_t radius, uint32_t color);

/**
 * @brief
    Compute and then draw all the points belonging to a field line,
    starting from pos0.
    Returns false if pos0 is not a valid position
    (for example if pos0 is too close to a charge).
 */
// void draw_field_line(struct gfx_context_t *ctxt, charge_t *charges, int num_charges, double dx, double eps)
// {

//     vec2 pos = vec2_create(0, 0);
//     vec2 tmp;

//     for (int i = 0; i < WIDTH; i++)
//     {
//         bool is_valid = compute_total_normalized_e(charges, num_charges, pos, eps, &tmp);
//         for (int j = 0; j < HEIGHT; j++)
//         {
//             pos = vec2_create((double)i, (double)j);
//         }
//     }
// }

/**
 * @brief
    Draw all the charges
    A circle with minus sign for negative charges
    A circle with a plus sign for positive charges
 */
// static void draw_charges(struct gfx_context_t *context, charge_t *charges, int num_charges, double x0, double x1, double y0, double y1);
#endif