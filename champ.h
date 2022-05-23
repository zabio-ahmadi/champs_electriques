#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "utils/gfx/gfx.h"
#include "utils/vec2/vec2.h"
#include "utils/utils.h"

#ifndef _CHAMPS_
#define _CHAMPS_

#define X0 0
#define X1 1
#define Y0 0
#define Y1 1

#define PHYS_K 8.988e9 // constant de coulomb
#define HEIGHT 500
#define WIDTH 500

#define NB_CHARGES 4
#define NB_POINTS 300

#define champs_color COLOR_WHITE

#define EPS 0.022
#define CHARGE_RAYON 8
/**
 * @brief E = k*q/r^2
 * calcule champs de charge en un point
 */
double
compute_champs(charge_t c, vec2 p);

/**
 * @brief Compute E*qP/norm(qP)
 * Return false if norm(qP) < eps
 */
bool compute_e(charge_t c, vec2 p, double eps, vec2 *e);

/**
 * @brief Compute the normalized sum of Ei*qiP/norm(qiP)
 *  Return false if for some qiP, norm(qiP) < eps
 */
bool compute_total_normalized_e(charge_t *charges, int num_charges, vec2 p, double eps, vec2 *e);

/**
 * @brief  calc delta_x
 *
 */
double delta_x(int width, int height);

/**
 * @brief generate random charges, position in [0, 1] univers
 */
void generate_random_charges(charge_t *charges, int nb_charges);

/**
 * @brief generate random point in [0, 1] univers
 */
void generate_random_points(vec2 *points, int nb_points);

/**
 * @brief draw charges in [0, 1] univers
 */
void draw_charges(struct gfx_context_t *ctxt, coordinates_t c, bool type, uint32_t radius, uint32_t color);

bool point_is_close_to_charge(vec2 p, charge_t *charges, int nb_charges);

/**
 * @brief verify if the old point and current point is the same
 */
bool is_point(coordinates_t current, coordinates_t old);

void draw_line(struct gfx_context_t *ctxt, coordinates_t old, coordinates_t current);

bool calc_next_position(charge_t *charges, int nb_charges, double eps, double delta, vec2 *p, int index);
/**
 * @brief
 * compute & draw points of a field line
 * validate each point
 * return false if the point is not a valide point
 */
bool draw_field_line(struct gfx_context_t *ctxt, charge_t *charges, int nb_charges, double x0, double x1, double y0, double y1, vec2 p0, double dx);

bool draw_curved_line(struct gfx_context_t *ctxt, charge_t *charges, int nb_charge, double dx, double x0, double x1, double y0, double y1, vec2 p, int index);

void simulate_champs(struct gfx_context_t *ctxt);
#endif