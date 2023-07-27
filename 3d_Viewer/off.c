/**
 *
 * @file off.c
 *
 */
#include "off.h"
/**
 * @brief Функция для автоматического маштабированя объекта при открытие по
 * размерам экрана
 *
 * @param a Матрица точек
 *
 */
void autoscale(pars_mat *a) {
  double max_x = 0, min_x = 0, max_y = 0, min_y = 0, max_z = 0, min_z = 0,
         max = 0;
  for (register unsigned int i = 0; i < a->matrix_xyz.rows; i += 3) {
    if (max_x < a->matrix_xyz.matrix[i])
      max_x = a->matrix_xyz.matrix[i];
    if (min_x > a->matrix_xyz.matrix[i])
      min_x = a->matrix_xyz.matrix[i];
    if (max_y < a->matrix_xyz.matrix[i + 1])
      max_y = a->matrix_xyz.matrix[i + 1];
    if (min_y > a->matrix_xyz.matrix[i + 1])
      min_y = a->matrix_xyz.matrix[i + 1];
    if (max_z < a->matrix_xyz.matrix[i + 2])
      max_z = a->matrix_xyz.matrix[i + 2];
    if (min_z > a->matrix_xyz.matrix[i + 2])
      min_z = a->matrix_xyz.matrix[i + 2];
  }
  int x = (max_x + min_x) / 2;
  int y = (max_y + min_y) / 2;
  int z = (max_z + min_z) / 2;
  move_xyz(a, -x, -y, -z);
  for (register unsigned int i = 0; i < a->matrix_xyz.rows; i++)
    if (max < fabs(a->matrix_xyz.matrix[i]))
      max = fabs(a->matrix_xyz.matrix[i]);
  scaling(a, 1.5 / max);
}
/**
 * @brief Функция для смещения объекта
 *
 * @param a Матрица точек
 * @param x смещение по оси "X"
 * @param y смещение по оси "Y"
 * @param Z смещение по оси "Z"
 *
 */
void move_xyz(pars_mat *a, double x, double y, double z) {
  if (x)
    for (unsigned int i = 0; i < a->matrix_xyz.rows; i += 3)
      a->matrix_xyz.matrix[i] += x;
  if (y)
    for (unsigned int i = 1; i < a->matrix_xyz.rows; i += 3)
      a->matrix_xyz.matrix[i] += y;
  if (z)
    for (unsigned int i = 2; i < a->matrix_xyz.rows; i += 3)
      a->matrix_xyz.matrix[i] += z;
}
/**
 * @brief Функция для маштабирования оъекта
 *
 * @param a Матрица точек
 * @param tmp Маштаб
 *
 */
void scaling(pars_mat *a, double tmp) {
  for (register unsigned int i = 0; i < a->matrix_xyz.rows; i++)
    a->matrix_xyz.matrix[i] *= tmp;
}
/**
 * @brief Функция для вращения оъекта по оси "X"
 *
 * @param a Матрица точек
 * @param tmp Угол
 *
 */
void rotation_x(pars_mat *a, double tmp) {
  register double c = cos(tmp), s = sin(tmp);
  for (register unsigned int i = 0; i < a->matrix_xyz.rows; i += 3) {
    register double temp_y = a->matrix_xyz.matrix[i + 1];
    register double temp_z = a->matrix_xyz.matrix[i + 2];
    a->matrix_xyz.matrix[i + 1] = c * temp_y - s * temp_z;
    a->matrix_xyz.matrix[i + 2] = s * temp_y + c * temp_z;
  }
}
/**
 * @brief Функция для вращения оъекта по оси "Y"
 *
 * @param a Матрица точек
 * @param tmp Угол
 *
 */
void rotation_y(pars_mat *a, double tmp) {
  register double c = cos(tmp), s = sin(tmp);
  for (register unsigned int i = 0; i < a->matrix_xyz.rows; i += 3) {
    register double temp_x = a->matrix_xyz.matrix[i];
    register double temp_z = a->matrix_xyz.matrix[i + 2];
    a->matrix_xyz.matrix[i] = c * temp_x - s * temp_z;
    a->matrix_xyz.matrix[i + 2] = temp_x * s + c * temp_z;
  }
}
/**
 * @brief Функция для вращения оъекта по оси "Z"
 *
 * @param a Матрица точек
 * @param tmp Угол
 *
 */
void rotation_z(pars_mat *a, double tmp) {
  register double c = cos(tmp), s = sin(tmp);
  for (register unsigned int i = 0; i < a->matrix_xyz.rows;
       i += 3) { // Усл цикла ?
    register double temp_x = a->matrix_xyz.matrix[i];
    register double temp_y = a->matrix_xyz.matrix[i + 1];
    a->matrix_xyz.matrix[i] = c * temp_x - s * temp_y;
    a->matrix_xyz.matrix[i + 1] = c * temp_y + temp_x * s;
  }
}
