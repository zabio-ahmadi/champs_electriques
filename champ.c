#include "champ.h"

double delta_x(int width, int height)
{
    return (1 / sqrt(pow(width, 2) + pow(height, 2)));
}

double compute_champs(charge_t c, vec2 p)
{
    return (PHYS_K * c.q) / pow(vec2_norm(vec2_sub(p, c.pos)), 2);
}

bool compute_e(charge_t c, vec2 p, double eps, vec2 *e)
{

    vec2 qP = vec2_sub(p, c.pos);
    double norm_qP = vec2_norm(qP);
    double E = compute_champs(c, p);

    // E * qp/||qp||
    *e = vec2_mul(E, vec2_create(qP.x / norm_qP, qP.y / norm_qP));
    return norm_qP > eps;
}

bool compute_total_normalized_e(charge_t *charges, int num_charges, vec2 p, double eps, vec2 *e)
{

    vec2 tmp;
    vec2 normalized_sum;
    for (int i = 0; i < num_charges; i++)
    {

        bool com_charge = compute_e(charges[i], p, eps, &tmp);
        if (!com_charge)
        {
            return false;
        }
        normalized_sum = vec2_add(normalized_sum, tmp);
    }

    *e = normalized_sum;
    return true;
}

void generate_random_charges(charge_t *charges, int nb_charges)
{
    srand(time(NULL));
    for (int i = 0; i < nb_charges; i++)
    {
        double charge = rand() % (10 - (-10)) + (-10);
        vec2 pos = vec2_create((double)rand() / (double)RAND_MAX, (double)rand() / (double)RAND_MAX);

        while (charge == 0)
        {
            charge = rand() % (10 - (-10)) + (-10);
        }

        while (pos.x == 0.0 || pos.y == 0.0)
        {
            pos = vec2_create((double)rand() / (double)RAND_MAX, (double)rand() / (double)RAND_MAX);
        }
        charges[i].pos = pos;
        charges[i].q = charge;
    }
}

// génère les points aléatoire dans notre univers [0:1]
void generate_random_points(vec2 *points, int nb_points)
{
    srand(time(NULL));
    for (int i = 0; i < nb_points; i++)
    {

        vec2 pos = vec2_create((double)rand() / (double)RAND_MAX, (double)rand() / (double)RAND_MAX);
        while (pos.x == 0.0 || pos.y == 0.0)
        {
            pos = vec2_create((double)rand() / (double)RAND_MAX, (double)rand() / (double)RAND_MAX);
        }
        points[i] = pos;
    }
}

bool draw_field_line(struct gfx_context_t *ctxt, charge_t *charges, int nb_charges, double x0, double x1, double y0, double y1, vec2 p0, double dx)
{
    for (int i = 0; i < 2; i++)
    {
        draw_curved_line(ctxt, charges, nb_charges, dx, x0, x1, y0, y1, p0, i);
    }
    return true;
}

bool draw_curved_line(struct gfx_context_t *ctxt, charge_t *charges, int nb_charge, double dx, double x0, double x1, double y0, double y1, vec2 p, int index)
{
    vec2 old_position = p;

    // tante que nous sommes dans l'ivers
    while ((p.x <= x1 && p.x >= x0 && p.y <= y1 && p.y >= y0) && !point_is_close_to_charge(p, charges, nb_charge))
    {
        coordinates_t c_old = position_to_coordinates(ctxt->width, ctxt->height, x0, x1, y0, y1, old_position);
        coordinates_t c_current = position_to_coordinates(ctxt->width, ctxt->height, x0, x1, y0, y1, p);

        // affiche les ligne
        draw_line(ctxt, c_current, c_old);

        // calcule le point suivant
        calc_next_position(charges, nb_charge, EPS, dx, &p, index);
        old_position = p;
    }
    return true;
}

// si les deux points calculés sont trop proche ou sont sur le meme coordinate dans notre univers
bool is_point(coordinates_t current, coordinates_t old)
{
    return (current.column == old.column && current.row == old.row);
}
void draw_line(struct gfx_context_t *ctxt, coordinates_t current, coordinates_t old)
{
    if (is_point(current, old))
    {
        gfx_putpixel(ctxt, current.column, current.row, champs_color);
    }
    else
    {
        // dans notre cas la norme de différence entre deux point est toujour 1 donc le emoyen de segement suffise de dessiner le segment entre deux point
        gfx_putpixel(ctxt, (current.column + old.column) / 2, (current.row + old.row) / 2, champs_color);
    }
}

bool point_is_close_to_charge(vec2 p, charge_t *charges, int nb_charges)
{
    for (int i = 0; i < nb_charges; i++)
    {
        double norm = vec2_norm(vec2_sub(p, charges[i].pos));
        if (norm < EPS)
        {
            return true;
        }
    }
    return false;
}

bool calc_next_position(charge_t *charges, int nb_charges, double eps, double delta, vec2 *p, int index)
{
    vec2 tmp;
    bool draw_is_valid = compute_total_normalized_e(charges, nb_charges, *p, eps, &tmp);

    // calc vecteur unitaire de point precédente
    // qui va nous donner la direction de ligne de champs entre deux points
    tmp = vec2_create(
        vec2_mul(delta, tmp).x / vec2_norm(tmp),
        vec2_mul(delta, tmp).y / vec2_norm(tmp));

    *p = (index) ? vec2_sub(*p, tmp) : vec2_add(*p, tmp);

    return draw_is_valid;
}

void draw_charges(struct gfx_context_t *ctxt, coordinates_t c, bool type, uint32_t radius, uint32_t color)
{
    int tmp = c.column;
    c.column = c.row;
    c.row = tmp;

    const int32_t diameter = (radius * 2);
    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    // draw lines
    int limit = ((20 / (double)100) * radius);

    // si la charge est positive affiche une + au centre de cercle
    if (type)
    {

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
    // sinon affiche une - au centre de cercle
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
        //  8 octant de notre cercle
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
            ty += 3;
        }
        else
        {
            --x;
            tx += 3;
            error += (tx - diameter);
        }
    }
}

void simulate_champs(struct gfx_context_t *ctxt)
{
    // 1.  génère les charges
    charge_t charges[NB_CHARGES];
    generate_random_charges(charges, NB_CHARGES);

    // 2. genère les points aléatoires
    /* a partir de ces points nous pouvons voir si les champs passe par ces points ou pas  */
    vec2 points[NB_POINTS];
    generate_random_points(points, NB_POINTS);

    double delta = delta_x(WIDTH, HEIGHT);

    // 3. dessine les charges dans matrice [0:1][0:1]
    for (int i = 0; i < NB_CHARGES; i++)
    {
        // position to coordinate va nous donner les position de charges aléatoire dans notre univers [0: 1]
        coordinates_t c_coord = position_to_coordinates(WIDTH, HEIGHT, X0, X1, Y0, Y1, charges[i].pos);

        // on dessine les charges à l'aide de fonction draw_cercle + deux ligne (horizonale, verticale)
        draw_charges(ctxt, c_coord, (charges[i].q > 0) ? true : false, CHARGE_RAYON, (charges[i].q > 0) ? COLOR_RED : COLOR_BLUE);
    }

    // nous dessinons les lignes de champs grace aux points que nous avons générés.
    for (int i = 0; i < NB_POINTS; i++)
    {
        draw_field_line(ctxt, charges, NB_CHARGES, X0, X1, Y0, Y1, points[i], delta);
    }
}