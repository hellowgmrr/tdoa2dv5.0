/*
 * File: inv.c
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 16-Jan-2020 19:37:25
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "chanX.h"
#include "inv.h"
#include "chanX_emxutil.h"

/* Function Declarations */
static void invNxN(const emxArray_real_T *x, emxArray_real_T *y);

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
static void invNxN(const emxArray_real_T *x, emxArray_real_T *y)
{
  int n;
  int i3;
  int yk;
  emxArray_real_T *A;
  int b_n;
  emxArray_int32_T *ipiv;
  int k;
  emxArray_int32_T *p;
  int j;
  int mmj;
  int c;
  int ix;
  double smax;
  int i4;
  int jy;
  double s;
  int ijA;
  n = x->size[0];
  i3 = y->size[0] * y->size[1];
  y->size[0] = x->size[0];
  y->size[1] = x->size[1];
  emxEnsureCapacity((emxArray__common *)y, i3, (int)sizeof(double));
  yk = x->size[0] * x->size[1];
  for (i3 = 0; i3 < yk; i3++) {
    y->data[i3] = 0.0;
  }

  emxInit_real_T(&A, 2);
  i3 = A->size[0] * A->size[1];
  A->size[0] = x->size[0];
  A->size[1] = x->size[1];
  emxEnsureCapacity((emxArray__common *)A, i3, (int)sizeof(double));
  yk = x->size[0] * x->size[1];
  for (i3 = 0; i3 < yk; i3++) {
    A->data[i3] = x->data[i3];
  }

  yk = x->size[0];
  if (yk < 1) {
    b_n = 0;
  } else {
    b_n = yk;
  }

  emxInit_int32_T(&ipiv, 2);
  i3 = ipiv->size[0] * ipiv->size[1];
  ipiv->size[0] = 1;
  ipiv->size[1] = b_n;
  emxEnsureCapacity((emxArray__common *)ipiv, i3, (int)sizeof(int));
  if (b_n > 0) {
    ipiv->data[0] = 1;
    yk = 1;
    for (k = 2; k <= b_n; k++) {
      yk++;
      ipiv->data[k - 1] = yk;
    }
  }

  if (x->size[0] < 1) {
    b_n = 0;
  } else {
    if (x->size[0] - 1 <= x->size[0]) {
      i3 = x->size[0] - 1;
    } else {
      i3 = x->size[0];
    }

    for (j = 0; j + 1 <= i3; j++) {
      mmj = n - j;
      c = j * (n + 1);
      if (mmj < 1) {
        yk = -1;
      } else {
        yk = 0;
        if (mmj > 1) {
          ix = c;
          smax = fabs(A->data[c]);
          for (k = 2; k <= mmj; k++) {
            ix++;
            s = fabs(A->data[ix]);
            if (s > smax) {
              yk = k - 1;
              smax = s;
            }
          }
        }
      }

      if (A->data[c + yk] != 0.0) {
        if (yk != 0) {
          ipiv->data[j] = (j + yk) + 1;
          ix = j;
          yk += j;
          for (k = 1; k <= n; k++) {
            smax = A->data[ix];
            A->data[ix] = A->data[yk];
            A->data[yk] = smax;
            ix += n;
            yk += n;
          }
        }

        i4 = c + mmj;
        for (jy = c + 1; jy + 1 <= i4; jy++) {
          A->data[jy] /= A->data[c];
        }
      }

      yk = n - j;
      b_n = (c + n) + 1;
      jy = c + n;
      for (k = 1; k < yk; k++) {
        smax = A->data[jy];
        if (A->data[jy] != 0.0) {
          ix = c + 1;
          i4 = mmj + b_n;
          for (ijA = b_n; ijA + 1 < i4; ijA++) {
            A->data[ijA] += A->data[ix] * -smax;
            ix++;
          }
        }

        jy += n;
        b_n += n;
      }
    }

    b_n = x->size[0];
  }

  emxInit_int32_T(&p, 2);
  i3 = p->size[0] * p->size[1];
  p->size[0] = 1;
  p->size[1] = b_n;
  emxEnsureCapacity((emxArray__common *)p, i3, (int)sizeof(int));
  if (b_n > 0) {
    p->data[0] = 1;
    yk = 1;
    for (k = 2; k <= b_n; k++) {
      yk++;
      p->data[k - 1] = yk;
    }
  }

  for (k = 0; k < ipiv->size[1]; k++) {
    if (ipiv->data[k] > 1 + k) {
      yk = p->data[ipiv->data[k] - 1];
      p->data[ipiv->data[k] - 1] = p->data[k];
      p->data[k] = yk;
    }
  }

  emxFree_int32_T(&ipiv);
  for (k = 0; k + 1 <= n; k++) {
    c = p->data[k] - 1;
    y->data[k + y->size[0] * (p->data[k] - 1)] = 1.0;
    for (j = k; j + 1 <= n; j++) {
      if (y->data[j + y->size[0] * c] != 0.0) {
        for (jy = j + 1; jy + 1 <= n; jy++) {
          y->data[jy + y->size[0] * c] -= y->data[j + y->size[0] * c] * A->
            data[jy + A->size[0] * j];
        }
      }
    }
  }

  emxFree_int32_T(&p);
  if ((x->size[0] != 0) && (!((y->size[0] == 0) || (y->size[1] == 0)))) {
    for (j = 1; j <= n; j++) {
      yk = n * (j - 1) - 1;
      for (k = n; k > 0; k--) {
        b_n = n * (k - 1) - 1;
        if (y->data[k + yk] != 0.0) {
          smax = y->data[k + yk];
          s = A->data[k + b_n];
          y->data[k + yk] = smax / s;
          for (jy = 1; jy < k; jy++) {
            y->data[jy + yk] -= y->data[k + yk] * A->data[jy + b_n];
          }
        }
      }
    }
  }

  emxFree_real_T(&A);
}

/*
 * Arguments    : const double x[9]
 *                double y[9]
 * Return Type  : void
 */
void b_inv(const double x[9], double y[9])
{
  double b_x[9];
  int p1;
  int p2;
  int p3;
  double absx11;
  double absx21;
  double absx31;
  int itmp;
  memcpy(&b_x[0], &x[0], 9U * sizeof(double));
  p1 = 0;
  p2 = 3;
  p3 = 6;
  absx11 = fabs(x[0]);
  absx21 = fabs(x[1]);
  absx31 = fabs(x[2]);
  if ((absx21 > absx11) && (absx21 > absx31)) {
    p1 = 3;
    p2 = 0;
    b_x[0] = x[1];
    b_x[1] = x[0];
    b_x[3] = x[4];
    b_x[4] = x[3];
    b_x[6] = x[7];
    b_x[7] = x[6];
  } else {
    if (absx31 > absx11) {
      p1 = 6;
      p3 = 0;
      b_x[0] = x[2];
      b_x[2] = x[0];
      b_x[3] = x[5];
      b_x[5] = x[3];
      b_x[6] = x[8];
      b_x[8] = x[6];
    }
  }

  absx11 = b_x[1] / b_x[0];
  b_x[1] /= b_x[0];
  absx21 = b_x[2] / b_x[0];
  b_x[2] /= b_x[0];
  b_x[4] -= absx11 * b_x[3];
  b_x[5] -= absx21 * b_x[3];
  b_x[7] -= absx11 * b_x[6];
  b_x[8] -= absx21 * b_x[6];
  if (fabs(b_x[5]) > fabs(b_x[4])) {
    itmp = p2;
    p2 = p3;
    p3 = itmp;
    b_x[1] = absx21;
    b_x[2] = absx11;
    absx11 = b_x[4];
    b_x[4] = b_x[5];
    b_x[5] = absx11;
    absx11 = b_x[7];
    b_x[7] = b_x[8];
    b_x[8] = absx11;
  }

  absx11 = b_x[5] / b_x[4];
  b_x[5] /= b_x[4];
  b_x[8] -= absx11 * b_x[7];
  absx11 = (b_x[5] * b_x[1] - b_x[2]) / b_x[8];
  absx21 = -(b_x[1] + b_x[7] * absx11) / b_x[4];
  y[p1] = ((1.0 - b_x[3] * absx21) - b_x[6] * absx11) / b_x[0];
  y[p1 + 1] = absx21;
  y[p1 + 2] = absx11;
  absx11 = -b_x[5] / b_x[8];
  absx21 = (1.0 - b_x[7] * absx11) / b_x[4];
  y[p2] = -(b_x[3] * absx21 + b_x[6] * absx11) / b_x[0];
  y[p2 + 1] = absx21;
  y[p2 + 2] = absx11;
  absx11 = 1.0 / b_x[8];
  absx21 = -b_x[7] * absx11 / b_x[4];
  y[p3] = -(b_x[3] * absx21 + b_x[6] * absx11) / b_x[0];
  y[p3 + 1] = absx21;
  y[p3 + 2] = absx11;
}

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void inv(const emxArray_real_T *x, emxArray_real_T *y)
{
  int i2;
  int loop_ub;
  if ((x->size[0] == 0) || (x->size[1] == 0)) {
    i2 = y->size[0] * y->size[1];
    y->size[0] = x->size[0];
    y->size[1] = x->size[1];
    emxEnsureCapacity((emxArray__common *)y, i2, (int)sizeof(double));
    loop_ub = x->size[0] * x->size[1];
    for (i2 = 0; i2 < loop_ub; i2++) {
      y->data[i2] = x->data[i2];
    }
  } else {
    invNxN(x, y);
  }
}

/*
 * File trailer for inv.c
 *
 * [EOF]
 */
