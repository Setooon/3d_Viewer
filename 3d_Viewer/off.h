/**
 *
 * @file off.h
 *
 */
#ifndef OFF_H
#define OFF_H

#include "core.h"
#include <math.h>

void move_xyz(pars_mat *a, double x, double y,
              double z); // перемещение по координатам
void scaling(pars_mat *a, double tmp);    // маштаб
void rotation_x(pars_mat *a, double tmp); // поворот x
void rotation_y(pars_mat *a, double tmp); // поворот y
void rotation_z(pars_mat *a, double tmp); // поворот z
void autoscale(pars_mat *a);
#endif // OFF_H
