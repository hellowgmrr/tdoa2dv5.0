/*
 * File: eye.c
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 16-Jan-2020 19:37:25
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "chanX.h"
#include "eye.h"
#include "chanX_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : double varargin_1
 *                emxArray_real_T *I
 * Return Type  : void
 */
void b_eye(double varargin_1, emxArray_real_T *I)
{
  int d;
  int k;
  int loop_ub;
  if (varargin_1 <= 3.0) {
    d = (int)varargin_1;
  } else {
    d = 3;
  }

  k = I->size[0] * I->size[1];
  I->size[0] = (int)varargin_1;
  I->size[1] = 3;
  emxEnsureCapacity((emxArray__common *)I, k, (int)sizeof(double));
  loop_ub = (int)varargin_1 * 3;
  for (k = 0; k < loop_ub; k++) {
    I->data[k] = 0.0;
  }

  if (d > 0) {
    for (k = 0; k + 1 <= d; k++) {
      I->data[k + I->size[0] * k] = 1.0;
    }
  }
}

/*
 * Arguments    : double varargin_1
 *                emxArray_real_T *I
 * Return Type  : void
 */
void c_eye(double varargin_1, emxArray_real_T *I)
{
  int k;
  int loop_ub;
  k = I->size[0] * I->size[1];
  I->size[0] = (int)varargin_1;
  I->size[1] = (int)varargin_1;
  emxEnsureCapacity((emxArray__common *)I, k, (int)sizeof(double));
  loop_ub = (int)varargin_1 * (int)varargin_1;
  for (k = 0; k < loop_ub; k++) {
    I->data[k] = 0.0;
  }

  if ((int)varargin_1 > 0) {
    for (k = 0; k + 1 <= (int)varargin_1; k++) {
      I->data[k + I->size[0] * k] = 1.0;
    }
  }
}

/*
 * Arguments    : double varargin_2
 *                emxArray_real_T *I
 * Return Type  : void
 */
void eye(double varargin_2, emxArray_real_T *I)
{
  int d;
  int k;
  int loop_ub;
  if (1.0 <= varargin_2) {
    d = 1;
  } else {
    d = (int)varargin_2;
  }

  k = I->size[0] * I->size[1];
  I->size[0] = 1;
  I->size[1] = (int)varargin_2;
  emxEnsureCapacity((emxArray__common *)I, k, (int)sizeof(double));
  loop_ub = (int)varargin_2;
  for (k = 0; k < loop_ub; k++) {
    I->data[k] = 0.0;
  }

  if (d > 0) {
    k = 1;
    while (k <= d) {
      I->data[0] = 1.0;
      k = 2;
    }
  }
}

/*
 * File trailer for eye.c
 *
 * [EOF]
 */
