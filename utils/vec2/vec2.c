
/*
@Author : ZABIULLAH AHMADI && KURTESHI AGNON
@Devoire : Date: 22.10.2021
@Description: should have the compile bundle first
@Test : should replace the vec2\vec2.c with this file 
*/



#include "vec2.h"
#include <math.h>
#include <stdio.h>

/// Create a 2d vector.
/// @param x_ The first component.
/// @param y_ The second component.
/// @return The newly created vector.
vec2 vec2_create(double x_, double y_) {

    vec2 v;
    v.x = x_;
    v.y = y_;
    return v;
}

/// Create a zero 2d vector.
/// @return The newly created zero vector.
vec2 vec2_create_zero() {
    vec2 v = vec2_create(0.0, 0.0);
    return v; 
}

/// Add two vectors.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return The sum in a new vector.
vec2 vec2_add(vec2 lhs, vec2 rhs) {

    vec2 sum;
    sum.x = lhs.x + rhs.x;
    sum.y = lhs.y + rhs.y;
    return sum;
}

/// Substract two vectors.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return The difference in a new vector.
vec2 vec2_sub(vec2 lhs, vec2 rhs) {

    vec2 sub;
    sub.x = lhs.x - rhs.x;
    sub.y = lhs.y - rhs.y;
    return sub;
}

/// Multiply a vector by a scalar.
/// @param scalar The left operand, a scalar.
/// @param rhs The right operand, a vector.
/// @return The product in a new vector.
vec2 vec2_mul(double scalar, vec2 rhs) {
    vec2 v;
    v.x  = rhs.x * scalar;
    v.y  = rhs.y * scalar;
    return v; 
}

/// Compute the dot product (scalar product) between two vectors.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return The dot product.
double vec2_dot(vec2 lhs, vec2 rhs) {
    return lhs.x*rhs.x + lhs.y*rhs.y;
}

/// Compute the square of the euclidean norm of a given vector.
/// @param v The vector.
/// @return The square of the norm.
double vec2_norm_sqr(vec2 v) {

    return pow(v.x, 2) + pow(v.y, 2);
}

/// Compute the euclidean norm of a given vector.
/// @param v The vector.
/// @return The norm.
double vec2_norm(vec2 v) {
    return sqrt(vec2_norm_sqr(v));
}

/// Compute the normalization of a given vector.
/// @param v The vector.
/// @return The new normalized vector.
vec2 vec2_normalize(vec2 v) {
    double norm = vec2_norm(v);
    vec2 normalized;
    normalized.x  = v.x / norm;
    normalized.y = v.y /norm;

    return normalized;
}

/// Check whether two vectors are approximately equals within a given tolerance.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @param eps The tolerance.
/// @return true if vector are approximately equal, false otherwise.
bool vec2_is_approx_equal(vec2 lhs, vec2 rhs, double eps) {

    vec2 sub = vec2_sub(lhs, rhs);
    double norm = vec2_norm(sub);
    return (norm < eps);
}

/// Compute the coordinates of a 2d vector (with components between 0 and 1)
/// in a given screen matrix.
/// @param v The 2d vector.
/// @param width The screen width.
/// @param height The screen height.
/// @return The coordinates (rwo, column).
coordinates vec2_to_coordinates(vec2 v, uint32_t width, uint32_t height) {

    coordinates coord;
	coord.row=(height)/2+((double)height -1.0)/2.0*v.y;
	coord.column=(width)/2+ ((double)width -1.0)/2.0*v.x;
	return coord;

}

/// Print a vector in the standard output.
/// @param v The vector.
void vec2_print(vec2 v) {
    printf("x = %g, y = %g\n", v.x, v.y);
}
