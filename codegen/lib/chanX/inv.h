/*
 * File: inv.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 16-Jan-2020 19:37:25
 */

#ifndef INV_H
#define INV_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "chanX_types.h"

/* Function Declarations */
extern void b_inv(const double x[9], double y[9]);
extern void inv(const emxArray_real_T *x, emxArray_real_T *y);

#endif

/*
 * File trailer for inv.h
 *
 * [EOF]
 */
