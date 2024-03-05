#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "parser.h"

int move_model(vertex*, double, double, double);
int scale_model(vertex*, double);
int rotate_model_x(vertex*, double);
int rotate_model_y(vertex*, double);
int rotate_model_z(vertex*, double);

#endif