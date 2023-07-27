/**
 *
 * @file core.c
 *
 */
#include "core.h"
/**
 * @brief Функция для подсчёта количества точек (вершин) и линий
 *
 * @param a Матрица
 * @param filename Имя файла
 *
 */
void quantity(pars_mat *tmp, char *filename) {
  FILE *f1 = fopen(filename, "r");
  if (f1 != NULL)
    while (!feof(f1)) {
      char str[512] = {0};
      if (!fgets(str, 511, f1))
        continue;
      int t = 0, x = 0;
      if (str[0] == 'v' && str[1] == ' ')
        tmp->matrix_xyz.rows++;
      else if (str[0] == 'f' && str[1] == ' ')
        while (str[t] != '\n')
          if ((str[t++] == ' ') && (sscanf(str + t, "%d", &x)))
            tmp->polygons.count_vertexes++;
    }
  else
    perror("Error occured while opening file");
  fclose(f1);
}
/**
 * @brief Функция для очистки выделенной памяти
 *
 * @param a Матрица
 *
 */
void deallocation(pars_mat *a) {
  if (a->matrix_xyz.matrix)
    free(a->matrix_xyz.matrix);
  if (a->polygons.vertexes)
    free(a->polygons.vertexes);
  a->matrix_xyz = (matrix_t){0, 0};
  a->polygons = (polygon_t){0, 0};
}
/**
 * @brief Функция для выделения памяти
 *
 * @param a Матрица
 *
 */
int allocation(pars_mat *a) {
  a->polygons.vertexes =
      (int *)calloc((a->polygons.count_vertexes *= 2), sizeof(int));
  a->matrix_xyz.matrix = (double *)calloc(
      (a->matrix_xyz.rows = a->matrix_xyz.rows * 3), sizeof(double));
  return (a->polygons.vertexes != 0) * (a->matrix_xyz.matrix != 0);
}
/**
 * @brief Функция для заполения массивов точек (вершин) и линий
 *
 * @param a Матрица
 *
 */
void record(pars_mat *a, char *filename) {
  FILE *f1 = fopen(filename, "r");
  int n = 0, n2 = 0, tmp = 0, t = 1, x = 0, xc = 0;
  char s[256] = {0};
  if (f1 != NULL) {
    while (!feof(f1)) {
      fgets(s, 255, f1);
      if ((s[0] == 'f') & (!(xc = 0)) & (t = 1)) {
        while (s[t] != '\n') {
          if (sscanf(s + (t++), " %d", &x)) {
            a->polygons.vertexes[n++] = x - 1;
            if (xc != 0)
              a->polygons.vertexes[n++] = x - 1;
            else
              tmp = x - (xc = 1);
            while ((s[t] != ' ') && (s[t] != '\n'))
              t++;
          }
        }
        a->polygons.vertexes[n++] = tmp;
      } else if (s[0] == 'v' && s[1] == ' ')
        if (sscanf(s, "v %lf %lf %lf", a->matrix_xyz.matrix + n2,
                   a->matrix_xyz.matrix + n2 + 1,
                   a->matrix_xyz.matrix + n2 + 2) == 3)
          n2 += 3;
    }
  } else
    perror("Error occured while opening file");
  fclose(f1);
}
