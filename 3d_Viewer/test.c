/**
 *
 * @file test.c
 *
 */
#include "test.h"

START_TEST(test_1) {
  char *filename = "tests/box.txt";
  pars_mat delta = {};
  pars_mat *res = &delta;
  deallocation(res);
  quantity(res, filename);
  allocation(res);
  record(res, filename);

  autoscale(res);

  move_xyz(res, 1, 1, 1);
  rotation_x(res, PI * 2);
  rotation_y(res, PI * 2);
  rotation_z(res, PI * 2);

  for (unsigned int j = 3; j < res->matrix_xyz.rows; j++) {
    ck_assert_double_eq_tol(res->matrix_xyz.matrix[j], res1[j]+1, EPS_10);
  }

  deallocation(res);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, test_1);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
