/**
 *
 * @file test.h
 *
 */
#ifndef SRC_TEST_H_
#define SRC_TEST_H_

#define EPS_10 1e-10
#define PI 3.141592653589

#include "off.h"
#include <check.h>
#include <stdio.h>

pars_mat delta = {};
pars_mat *res = &delta;

double res1[25] = {1.500000,  1.500000,  1.500000,  1.500000,  1.500000,
                   -1.500000, 1.500000,  -1.500000, 1.500000,  1.500000,
                   -1.500000, -1.500000, -1.500000, 1.500000,  -1.500000,
                   -1.500000, 1.500000,  1.500000,  -1.500000, -1.500000,
                   -1.500000, -1.500000, -1.500000, 1.500000, 0};

#endif // RC_TEST_H
