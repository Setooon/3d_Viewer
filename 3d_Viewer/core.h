/**
 *
 * @file core.h
 *
 */
#ifndef CORE_H
#define CORE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct facets {
  int *vertexes;
  unsigned int count_vertexes;
} polygon_t;

typedef struct Matrix {
  double *matrix;
  unsigned int rows;
} matrix_t;

typedef struct core {
  matrix_t matrix_xyz;
  polygon_t polygons;
} pars_mat;

void quantity(pars_mat *tmp, char *filename); // посчет количесва v && f
int allocation(pars_mat *a);                  // выделения памяти
void record(pars_mat *a, char *filename); // заполнее матрицы f
void deallocation(pars_mat *a);           // очистка памяти

#endif // CORE_H
