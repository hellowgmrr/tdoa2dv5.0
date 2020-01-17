/*
 * File: chanX.c
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 16-Jan-2020 19:37:25
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "chanX.h"
#include "inv.h"
#include "chanX_emxutil.h"
#include "eye.h"

/* Function Definitions */

/*
 * Arguments    : double num_of_anchor
 *                const double anchor_position[14]
 *                const double R[6]
 *                double tag_position[2]
 * Return Type  : void
 */
void chanX(double num_of_anchor, const double anchor_position[14], const double
           R[6], double tag_position[2])
{
  emxArray_real_T *K;
  emxArray_real_T *Ga;
  emxArray_real_T *h;
  emxArray_real_T *Q;
  double m;
  int i;
  emxArray_real_T *a;
  int i0;
  int br;
  emxArray_real_T *B;
  int i1;
  emxArray_real_T *y;
  int k;
  unsigned int unnamed_idx_1;
  double sFI[9];
  int ar;
  int cr;
  double sB[9];
  int ic;
  int ib;
  emxArray_real_T *b_y;
  int ia;
  emxArray_real_T *c_y;
  emxArray_real_T *b;
  double Za0[3];
  emxArray_real_T *d_y;
  double b_a;
  unsigned int unnamed_idx_0;
  int b_m;
  emxArray_real_T *FI;
  emxArray_real_T *e_y;
  emxArray_real_T *f_y;
  emxArray_real_T *g_y;
  emxArray_real_T *h_y;
  double CovZa[9];
  static const signed char iv0[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  double dv0[9];
  double c_a[6];
  double i_y[4];
  double r;
  double t;
  double j_y[4];
  static const signed char d_a[6] = { 1, 0, 0, 1, 1, 1 };

  static const signed char b_b[6] = { 1, 0, 1, 0, 1, 1 };

  double k_y[6];
  double e_a[3];
  double reout[2];
  double Za[2];
  double Za2[2];
  emxInit_real_T(&K, 2);
  emxInit_real_T(&Ga, 2);
  emxInit_real_T(&h, 2);
  emxInit_real_T(&Q, 2);
  eye(num_of_anchor - 1.0, K);
  b_eye(num_of_anchor - 1.0, Ga);
  eye(num_of_anchor - 1.0, h);
  c_eye(num_of_anchor - 1.0, Q);
  m = anchor_position[0] * anchor_position[0] + anchor_position[1] *
    anchor_position[1];
  for (i = 0; i < (int)(num_of_anchor - 1.0); i++) {
    K->data[i] = anchor_position[((int)((1.0 + (double)i) + 1.0) - 1) << 1] *
      anchor_position[((int)((1.0 + (double)i) + 1.0) - 1) << 1] +
      anchor_position[1 + (((int)((1.0 + (double)i) + 1.0) - 1) << 1)] *
      anchor_position[1 + (((int)((1.0 + (double)i) + 1.0) - 1) << 1)];
  }

  for (i = 0; i < (int)(num_of_anchor - 1.0); i++) {
    Ga->data[i] = -(anchor_position[((int)((1.0 + (double)i) + 1.0) - 1) << 1] -
                    anchor_position[0]);
    Ga->data[i + Ga->size[0]] = -(anchor_position[1 + (((int)((1.0 + (double)i)
      + 1.0) - 1) << 1)] - anchor_position[1]);
    Ga->data[i + (Ga->size[0] << 1)] = -R[i];
  }

  for (i = 0; i < (int)(num_of_anchor - 1.0); i++) {
    h->data[i] = 0.5 * ((R[i] * R[i] - K->data[i]) + m);
  }

  emxFree_real_T(&K);
  emxInit_real_T(&a, 2);
  i0 = a->size[0] * a->size[1];
  a->size[0] = 3;
  a->size[1] = Ga->size[0];
  emxEnsureCapacity((emxArray__common *)a, i0, (int)sizeof(double));
  br = Ga->size[0];
  for (i0 = 0; i0 < br; i0++) {
    for (i1 = 0; i1 < 3; i1++) {
      a->data[i1 + a->size[0] * i0] = Ga->data[i0 + Ga->size[0] * i1];
    }
  }

  emxInit_real_T(&B, 2);
  inv(Q, B);
  emxInit_real_T(&y, 2);
  if ((a->size[1] == 1) || (B->size[0] == 1)) {
    i0 = y->size[0] * y->size[1];
    y->size[0] = 3;
    y->size[1] = B->size[1];
    emxEnsureCapacity((emxArray__common *)y, i0, (int)sizeof(double));
    for (i0 = 0; i0 < 3; i0++) {
      br = B->size[1];
      for (i1 = 0; i1 < br; i1++) {
        y->data[i0 + y->size[0] * i1] = 0.0;
        ar = a->size[1];
        for (i = 0; i < ar; i++) {
          y->data[i0 + y->size[0] * i1] += a->data[i0 + a->size[0] * i] *
            B->data[i + B->size[0] * i1];
        }
      }
    }
  } else {
    k = a->size[1];
    unnamed_idx_1 = (unsigned int)B->size[1];
    i0 = y->size[0] * y->size[1];
    y->size[0] = 3;
    y->size[1] = (int)unnamed_idx_1;
    y->size[0] = 3;
    emxEnsureCapacity((emxArray__common *)y, i0, (int)sizeof(double));
    br = y->size[1];
    for (i0 = 0; i0 < br; i0++) {
      for (i1 = 0; i1 < 3; i1++) {
        y->data[i1 + y->size[0] * i0] = 0.0;
      }
    }

    if (B->size[1] != 0) {
      i = 3 * (B->size[1] - 1);
      for (cr = 0; cr <= i; cr += 3) {
        for (ic = cr + 1; ic <= cr + 3; ic++) {
          y->data[ic - 1] = 0.0;
        }
      }

      br = 0;
      for (cr = 0; cr <= i; cr += 3) {
        ar = -1;
        i0 = br + k;
        for (ib = br; ib + 1 <= i0; ib++) {
          if (B->data[ib] != 0.0) {
            ia = ar;
            for (ic = cr; ic + 1 <= cr + 3; ic++) {
              ia++;
              y->data[ic] += B->data[ib] * a->data[ia];
            }
          }

          ar += 3;
        }

        br += k;
      }
    }
  }

  if ((y->size[1] == 1) || (Ga->size[0] == 1)) {
    for (i0 = 0; i0 < 3; i0++) {
      for (i1 = 0; i1 < 3; i1++) {
        sFI[i0 + 3 * i1] = 0.0;
        br = y->size[1];
        for (i = 0; i < br; i++) {
          sFI[i0 + 3 * i1] += y->data[i0 + y->size[0] * i] * Ga->data[i +
            Ga->size[0] * i1];
        }
      }
    }
  } else {
    k = y->size[1];
    memset(&sFI[0], 0, 9U * sizeof(double));
    for (cr = 0; cr <= 7; cr += 3) {
      for (ic = cr; ic + 1 <= cr + 3; ic++) {
        sFI[ic] = 0.0;
      }
    }

    br = 0;
    for (cr = 0; cr <= 7; cr += 3) {
      ar = -1;
      i0 = br + k;
      for (ib = br; ib + 1 <= i0; ib++) {
        if (Ga->data[ib] != 0.0) {
          ia = ar;
          for (ic = cr; ic + 1 <= cr + 3; ic++) {
            ia++;
            sFI[ic] += Ga->data[ib] * y->data[ia];
          }
        }

        ar += 3;
      }

      br += k;
    }
  }

  emxFree_real_T(&y);
  b_inv(sFI, sB);
  i0 = a->size[0] * a->size[1];
  a->size[0] = 3;
  a->size[1] = Ga->size[0];
  emxEnsureCapacity((emxArray__common *)a, i0, (int)sizeof(double));
  br = Ga->size[0];
  for (i0 = 0; i0 < br; i0++) {
    for (i1 = 0; i1 < 3; i1++) {
      a->data[i1 + a->size[0] * i0] = Ga->data[i0 + Ga->size[0] * i1];
    }
  }

  emxInit_real_T(&b_y, 2);
  unnamed_idx_1 = (unsigned int)a->size[1];
  i0 = b_y->size[0] * b_y->size[1];
  b_y->size[0] = 3;
  b_y->size[1] = (int)unnamed_idx_1;
  b_y->size[0] = 3;
  emxEnsureCapacity((emxArray__common *)b_y, i0, (int)sizeof(double));
  br = b_y->size[1];
  for (i0 = 0; i0 < br; i0++) {
    for (i1 = 0; i1 < 3; i1++) {
      b_y->data[i1 + b_y->size[0] * i0] = 0.0;
    }
  }

  if (a->size[1] != 0) {
    i = 3 * (a->size[1] - 1);
    for (cr = 0; cr <= i; cr += 3) {
      for (ic = cr + 1; ic <= cr + 3; ic++) {
        b_y->data[ic - 1] = 0.0;
      }
    }

    br = 0;
    for (cr = 0; cr <= i; cr += 3) {
      ar = -1;
      for (ib = br; ib + 1 <= br + 3; ib++) {
        if (a->data[ib] != 0.0) {
          ia = ar;
          for (ic = cr; ic + 1 <= cr + 3; ic++) {
            ia++;
            b_y->data[ic] += a->data[ib] * sB[ia];
          }
        }

        ar += 3;
      }

      br += 3;
    }
  }

  inv(Q, B);
  emxInit_real_T(&c_y, 2);
  if ((b_y->size[1] == 1) || (B->size[0] == 1)) {
    i0 = c_y->size[0] * c_y->size[1];
    c_y->size[0] = 3;
    c_y->size[1] = B->size[1];
    emxEnsureCapacity((emxArray__common *)c_y, i0, (int)sizeof(double));
    for (i0 = 0; i0 < 3; i0++) {
      br = B->size[1];
      for (i1 = 0; i1 < br; i1++) {
        c_y->data[i0 + c_y->size[0] * i1] = 0.0;
        ar = b_y->size[1];
        for (i = 0; i < ar; i++) {
          c_y->data[i0 + c_y->size[0] * i1] += b_y->data[i0 + b_y->size[0] * i] *
            B->data[i + B->size[0] * i1];
        }
      }
    }
  } else {
    k = b_y->size[1];
    unnamed_idx_1 = (unsigned int)B->size[1];
    i0 = c_y->size[0] * c_y->size[1];
    c_y->size[0] = 3;
    c_y->size[1] = (int)unnamed_idx_1;
    c_y->size[0] = 3;
    emxEnsureCapacity((emxArray__common *)c_y, i0, (int)sizeof(double));
    br = c_y->size[1];
    for (i0 = 0; i0 < br; i0++) {
      for (i1 = 0; i1 < 3; i1++) {
        c_y->data[i1 + c_y->size[0] * i0] = 0.0;
      }
    }

    if (B->size[1] != 0) {
      i = 3 * (B->size[1] - 1);
      for (cr = 0; cr <= i; cr += 3) {
        for (ic = cr + 1; ic <= cr + 3; ic++) {
          c_y->data[ic - 1] = 0.0;
        }
      }

      br = 0;
      for (cr = 0; cr <= i; cr += 3) {
        ar = -1;
        i0 = br + k;
        for (ib = br; ib + 1 <= i0; ib++) {
          if (B->data[ib] != 0.0) {
            ia = ar;
            for (ic = cr; ic + 1 <= cr + 3; ic++) {
              ia++;
              c_y->data[ic] += B->data[ib] * b_y->data[ia];
            }
          }

          ar += 3;
        }

        br += k;
      }
    }
  }

  emxFree_real_T(&b_y);
  emxInit_real_T1(&b, 1);
  i0 = b->size[0];
  b->size[0] = h->size[1];
  emxEnsureCapacity((emxArray__common *)b, i0, (int)sizeof(double));
  br = h->size[1];
  for (i0 = 0; i0 < br; i0++) {
    b->data[i0] = h->data[h->size[0] * i0];
  }

  if ((c_y->size[1] == 1) || (b->size[0] == 1)) {
    for (i0 = 0; i0 < 3; i0++) {
      Za0[i0] = 0.0;
      br = c_y->size[1];
      for (i1 = 0; i1 < br; i1++) {
        m = Za0[i0] + c_y->data[i0 + c_y->size[0] * i1] * b->data[i1];
        Za0[i0] = m;
      }
    }
  } else {
    for (ic = 0; ic < 3; ic++) {
      Za0[ic] = 0.0;
    }

    ar = -1;
    for (ib = 0; ib + 1 <= c_y->size[1]; ib++) {
      if (b->data[ib] != 0.0) {
        ia = ar;
        for (ic = 0; ic < 3; ic++) {
          ia++;
          m = Za0[ic] + b->data[ib] * c_y->data[ia];
          Za0[ic] = m;
        }
      }

      ar += 3;
    }
  }

  emxFree_real_T(&c_y);

  /* (14b） */
  c_eye(num_of_anchor - 1.0, B);
  for (i = 0; i < (int)(num_of_anchor - 1.0); i++) {
    m = anchor_position[((int)((1.0 + (double)i) + 1.0) - 1) << 1] - Za0[0];
    b_a = anchor_position[1 + (((int)((1.0 + (double)i) + 1.0) - 1) << 1)] -
      Za0[1];
    B->data[i + B->size[0] * i] = sqrt(m * m + b_a * b_a);
  }

  emxInit_real_T(&d_y, 2);
  if ((B->size[1] == 1) || (Q->size[0] == 1)) {
    i0 = d_y->size[0] * d_y->size[1];
    d_y->size[0] = B->size[0];
    d_y->size[1] = Q->size[1];
    emxEnsureCapacity((emxArray__common *)d_y, i0, (int)sizeof(double));
    br = B->size[0];
    for (i0 = 0; i0 < br; i0++) {
      ar = Q->size[1];
      for (i1 = 0; i1 < ar; i1++) {
        d_y->data[i0 + d_y->size[0] * i1] = 0.0;
        cr = B->size[1];
        for (i = 0; i < cr; i++) {
          d_y->data[i0 + d_y->size[0] * i1] += B->data[i0 + B->size[0] * i] *
            Q->data[i + Q->size[0] * i1];
        }
      }
    }
  } else {
    k = B->size[1];
    unnamed_idx_0 = (unsigned int)B->size[0];
    unnamed_idx_1 = (unsigned int)Q->size[1];
    i0 = d_y->size[0] * d_y->size[1];
    d_y->size[0] = (int)unnamed_idx_0;
    d_y->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity((emxArray__common *)d_y, i0, (int)sizeof(double));
    b_m = B->size[0];
    i0 = d_y->size[0] * d_y->size[1];
    emxEnsureCapacity((emxArray__common *)d_y, i0, (int)sizeof(double));
    br = d_y->size[1];
    for (i0 = 0; i0 < br; i0++) {
      ar = d_y->size[0];
      for (i1 = 0; i1 < ar; i1++) {
        d_y->data[i1 + d_y->size[0] * i0] = 0.0;
      }
    }

    if ((B->size[0] == 0) || (Q->size[1] == 0)) {
    } else {
      i = B->size[0] * (Q->size[1] - 1);
      cr = 0;
      while ((b_m > 0) && (cr <= i)) {
        i0 = cr + b_m;
        for (ic = cr; ic + 1 <= i0; ic++) {
          d_y->data[ic] = 0.0;
        }

        cr += b_m;
      }

      br = 0;
      cr = 0;
      while ((b_m > 0) && (cr <= i)) {
        ar = -1;
        i0 = br + k;
        for (ib = br; ib + 1 <= i0; ib++) {
          if (Q->data[ib] != 0.0) {
            ia = ar;
            i1 = cr + b_m;
            for (ic = cr; ic + 1 <= i1; ic++) {
              ia++;
              d_y->data[ic] += Q->data[ib] * B->data[ia];
            }
          }

          ar += b_m;
        }

        br += k;
        cr += b_m;
      }
    }
  }

  emxFree_real_T(&Q);
  emxInit_real_T(&FI, 2);
  if ((d_y->size[1] == 1) || (B->size[0] == 1)) {
    i0 = FI->size[0] * FI->size[1];
    FI->size[0] = d_y->size[0];
    FI->size[1] = B->size[1];
    emxEnsureCapacity((emxArray__common *)FI, i0, (int)sizeof(double));
    br = d_y->size[0];
    for (i0 = 0; i0 < br; i0++) {
      ar = B->size[1];
      for (i1 = 0; i1 < ar; i1++) {
        FI->data[i0 + FI->size[0] * i1] = 0.0;
        cr = d_y->size[1];
        for (i = 0; i < cr; i++) {
          FI->data[i0 + FI->size[0] * i1] += d_y->data[i0 + d_y->size[0] * i] *
            B->data[i + B->size[0] * i1];
        }
      }
    }
  } else {
    k = d_y->size[1];
    unnamed_idx_0 = (unsigned int)d_y->size[0];
    unnamed_idx_1 = (unsigned int)B->size[1];
    i0 = FI->size[0] * FI->size[1];
    FI->size[0] = (int)unnamed_idx_0;
    FI->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity((emxArray__common *)FI, i0, (int)sizeof(double));
    b_m = d_y->size[0];
    i0 = FI->size[0] * FI->size[1];
    emxEnsureCapacity((emxArray__common *)FI, i0, (int)sizeof(double));
    br = FI->size[1];
    for (i0 = 0; i0 < br; i0++) {
      ar = FI->size[0];
      for (i1 = 0; i1 < ar; i1++) {
        FI->data[i1 + FI->size[0] * i0] = 0.0;
      }
    }

    if ((d_y->size[0] == 0) || (B->size[1] == 0)) {
    } else {
      i = d_y->size[0] * (B->size[1] - 1);
      cr = 0;
      while ((b_m > 0) && (cr <= i)) {
        i0 = cr + b_m;
        for (ic = cr; ic + 1 <= i0; ic++) {
          FI->data[ic] = 0.0;
        }

        cr += b_m;
      }

      br = 0;
      cr = 0;
      while ((b_m > 0) && (cr <= i)) {
        ar = -1;
        i0 = br + k;
        for (ib = br; ib + 1 <= i0; ib++) {
          if (B->data[ib] != 0.0) {
            ia = ar;
            i1 = cr + b_m;
            for (ic = cr; ic + 1 <= i1; ic++) {
              ia++;
              FI->data[ic] += B->data[ib] * d_y->data[ia];
            }
          }

          ar += b_m;
        }

        br += k;
        cr += b_m;
      }
    }
  }

  emxFree_real_T(&d_y);
  i0 = a->size[0] * a->size[1];
  a->size[0] = 3;
  a->size[1] = Ga->size[0];
  emxEnsureCapacity((emxArray__common *)a, i0, (int)sizeof(double));
  br = Ga->size[0];
  for (i0 = 0; i0 < br; i0++) {
    for (i1 = 0; i1 < 3; i1++) {
      a->data[i1 + a->size[0] * i0] = Ga->data[i0 + Ga->size[0] * i1];
    }
  }

  inv(FI, B);
  emxInit_real_T(&e_y, 2);
  if ((a->size[1] == 1) || (B->size[0] == 1)) {
    i0 = e_y->size[0] * e_y->size[1];
    e_y->size[0] = 3;
    e_y->size[1] = B->size[1];
    emxEnsureCapacity((emxArray__common *)e_y, i0, (int)sizeof(double));
    for (i0 = 0; i0 < 3; i0++) {
      br = B->size[1];
      for (i1 = 0; i1 < br; i1++) {
        e_y->data[i0 + e_y->size[0] * i1] = 0.0;
        ar = a->size[1];
        for (i = 0; i < ar; i++) {
          e_y->data[i0 + e_y->size[0] * i1] += a->data[i0 + a->size[0] * i] *
            B->data[i + B->size[0] * i1];
        }
      }
    }
  } else {
    k = a->size[1];
    unnamed_idx_1 = (unsigned int)B->size[1];
    i0 = e_y->size[0] * e_y->size[1];
    e_y->size[0] = 3;
    e_y->size[1] = (int)unnamed_idx_1;
    e_y->size[0] = 3;
    emxEnsureCapacity((emxArray__common *)e_y, i0, (int)sizeof(double));
    br = e_y->size[1];
    for (i0 = 0; i0 < br; i0++) {
      for (i1 = 0; i1 < 3; i1++) {
        e_y->data[i1 + e_y->size[0] * i0] = 0.0;
      }
    }

    if (B->size[1] != 0) {
      i = 3 * (B->size[1] - 1);
      for (cr = 0; cr <= i; cr += 3) {
        for (ic = cr + 1; ic <= cr + 3; ic++) {
          e_y->data[ic - 1] = 0.0;
        }
      }

      br = 0;
      for (cr = 0; cr <= i; cr += 3) {
        ar = -1;
        i0 = br + k;
        for (ib = br; ib + 1 <= i0; ib++) {
          if (B->data[ib] != 0.0) {
            ia = ar;
            for (ic = cr; ic + 1 <= cr + 3; ic++) {
              ia++;
              e_y->data[ic] += B->data[ib] * a->data[ia];
            }
          }

          ar += 3;
        }

        br += k;
      }
    }
  }

  if ((e_y->size[1] == 1) || (Ga->size[0] == 1)) {
    for (i0 = 0; i0 < 3; i0++) {
      for (i1 = 0; i1 < 3; i1++) {
        sFI[i0 + 3 * i1] = 0.0;
        br = e_y->size[1];
        for (i = 0; i < br; i++) {
          sFI[i0 + 3 * i1] += e_y->data[i0 + e_y->size[0] * i] * Ga->data[i +
            Ga->size[0] * i1];
        }
      }
    }
  } else {
    k = e_y->size[1];
    memset(&sFI[0], 0, 9U * sizeof(double));
    for (cr = 0; cr <= 7; cr += 3) {
      for (ic = cr; ic + 1 <= cr + 3; ic++) {
        sFI[ic] = 0.0;
      }
    }

    br = 0;
    for (cr = 0; cr <= 7; cr += 3) {
      ar = -1;
      i0 = br + k;
      for (ib = br; ib + 1 <= i0; ib++) {
        if (Ga->data[ib] != 0.0) {
          ia = ar;
          for (ic = cr; ic + 1 <= cr + 3; ic++) {
            ia++;
            sFI[ic] += Ga->data[ib] * e_y->data[ia];
          }
        }

        ar += 3;
      }

      br += k;
    }
  }

  emxFree_real_T(&e_y);
  b_inv(sFI, sB);
  i0 = a->size[0] * a->size[1];
  a->size[0] = 3;
  a->size[1] = Ga->size[0];
  emxEnsureCapacity((emxArray__common *)a, i0, (int)sizeof(double));
  br = Ga->size[0];
  for (i0 = 0; i0 < br; i0++) {
    for (i1 = 0; i1 < 3; i1++) {
      a->data[i1 + a->size[0] * i0] = Ga->data[i0 + Ga->size[0] * i1];
    }
  }

  emxInit_real_T(&f_y, 2);
  unnamed_idx_1 = (unsigned int)a->size[1];
  i0 = f_y->size[0] * f_y->size[1];
  f_y->size[0] = 3;
  f_y->size[1] = (int)unnamed_idx_1;
  f_y->size[0] = 3;
  emxEnsureCapacity((emxArray__common *)f_y, i0, (int)sizeof(double));
  br = f_y->size[1];
  for (i0 = 0; i0 < br; i0++) {
    for (i1 = 0; i1 < 3; i1++) {
      f_y->data[i1 + f_y->size[0] * i0] = 0.0;
    }
  }

  if (a->size[1] != 0) {
    i = 3 * (a->size[1] - 1);
    for (cr = 0; cr <= i; cr += 3) {
      for (ic = cr + 1; ic <= cr + 3; ic++) {
        f_y->data[ic - 1] = 0.0;
      }
    }

    br = 0;
    for (cr = 0; cr <= i; cr += 3) {
      ar = -1;
      for (ib = br; ib + 1 <= br + 3; ib++) {
        if (a->data[ib] != 0.0) {
          ia = ar;
          for (ic = cr; ic + 1 <= cr + 3; ic++) {
            ia++;
            f_y->data[ic] += a->data[ib] * sB[ia];
          }
        }

        ar += 3;
      }

      br += 3;
    }
  }

  inv(FI, B);
  emxInit_real_T(&g_y, 2);
  if ((f_y->size[1] == 1) || (B->size[0] == 1)) {
    i0 = g_y->size[0] * g_y->size[1];
    g_y->size[0] = 3;
    g_y->size[1] = B->size[1];
    emxEnsureCapacity((emxArray__common *)g_y, i0, (int)sizeof(double));
    for (i0 = 0; i0 < 3; i0++) {
      br = B->size[1];
      for (i1 = 0; i1 < br; i1++) {
        g_y->data[i0 + g_y->size[0] * i1] = 0.0;
        ar = f_y->size[1];
        for (i = 0; i < ar; i++) {
          g_y->data[i0 + g_y->size[0] * i1] += f_y->data[i0 + f_y->size[0] * i] *
            B->data[i + B->size[0] * i1];
        }
      }
    }
  } else {
    k = f_y->size[1];
    unnamed_idx_1 = (unsigned int)B->size[1];
    i0 = g_y->size[0] * g_y->size[1];
    g_y->size[0] = 3;
    g_y->size[1] = (int)unnamed_idx_1;
    g_y->size[0] = 3;
    emxEnsureCapacity((emxArray__common *)g_y, i0, (int)sizeof(double));
    br = g_y->size[1];
    for (i0 = 0; i0 < br; i0++) {
      for (i1 = 0; i1 < 3; i1++) {
        g_y->data[i1 + g_y->size[0] * i0] = 0.0;
      }
    }

    if (B->size[1] != 0) {
      i = 3 * (B->size[1] - 1);
      for (cr = 0; cr <= i; cr += 3) {
        for (ic = cr + 1; ic <= cr + 3; ic++) {
          g_y->data[ic - 1] = 0.0;
        }
      }

      br = 0;
      for (cr = 0; cr <= i; cr += 3) {
        ar = -1;
        i0 = br + k;
        for (ib = br; ib + 1 <= i0; ib++) {
          if (B->data[ib] != 0.0) {
            ia = ar;
            for (ic = cr; ic + 1 <= cr + 3; ic++) {
              ia++;
              g_y->data[ic] += B->data[ib] * f_y->data[ia];
            }
          }

          ar += 3;
        }

        br += k;
      }
    }
  }

  emxFree_real_T(&f_y);
  i0 = b->size[0];
  b->size[0] = h->size[1];
  emxEnsureCapacity((emxArray__common *)b, i0, (int)sizeof(double));
  br = h->size[1];
  for (i0 = 0; i0 < br; i0++) {
    b->data[i0] = h->data[h->size[0] * i0];
  }

  emxFree_real_T(&h);
  if ((g_y->size[1] == 1) || (b->size[0] == 1)) {
    for (i0 = 0; i0 < 3; i0++) {
      Za0[i0] = 0.0;
      br = g_y->size[1];
      for (i1 = 0; i1 < br; i1++) {
        m = Za0[i0] + g_y->data[i0 + g_y->size[0] * i1] * b->data[i1];
        Za0[i0] = m;
      }
    }
  } else {
    for (ic = 0; ic < 3; ic++) {
      Za0[ic] = 0.0;
    }

    ar = -1;
    for (ib = 0; ib + 1 <= g_y->size[1]; ib++) {
      if (b->data[ib] != 0.0) {
        ia = ar;
        for (ic = 0; ic < 3; ic++) {
          ia++;
          m = Za0[ic] + b->data[ib] * g_y->data[ia];
          Za0[ic] = m;
        }
      }

      ar += 3;
    }
  }

  emxFree_real_T(&g_y);
  emxFree_real_T(&b);

  /* （14a） */
  if (Za0[2] < 0.0) {
    Za0[2] = fabs(Za0[2]);
  }

  i0 = a->size[0] * a->size[1];
  a->size[0] = 3;
  a->size[1] = Ga->size[0];
  emxEnsureCapacity((emxArray__common *)a, i0, (int)sizeof(double));
  br = Ga->size[0];
  for (i0 = 0; i0 < br; i0++) {
    for (i1 = 0; i1 < 3; i1++) {
      a->data[i1 + a->size[0] * i0] = Ga->data[i0 + Ga->size[0] * i1];
    }
  }

  inv(FI, B);
  emxFree_real_T(&FI);
  emxInit_real_T(&h_y, 2);
  if ((a->size[1] == 1) || (B->size[0] == 1)) {
    i0 = h_y->size[0] * h_y->size[1];
    h_y->size[0] = 3;
    h_y->size[1] = B->size[1];
    emxEnsureCapacity((emxArray__common *)h_y, i0, (int)sizeof(double));
    for (i0 = 0; i0 < 3; i0++) {
      br = B->size[1];
      for (i1 = 0; i1 < br; i1++) {
        h_y->data[i0 + h_y->size[0] * i1] = 0.0;
        ar = a->size[1];
        for (i = 0; i < ar; i++) {
          h_y->data[i0 + h_y->size[0] * i1] += a->data[i0 + a->size[0] * i] *
            B->data[i + B->size[0] * i1];
        }
      }
    }
  } else {
    k = a->size[1];
    unnamed_idx_1 = (unsigned int)B->size[1];
    i0 = h_y->size[0] * h_y->size[1];
    h_y->size[0] = 3;
    h_y->size[1] = (int)unnamed_idx_1;
    h_y->size[0] = 3;
    emxEnsureCapacity((emxArray__common *)h_y, i0, (int)sizeof(double));
    br = h_y->size[1];
    for (i0 = 0; i0 < br; i0++) {
      for (i1 = 0; i1 < 3; i1++) {
        h_y->data[i1 + h_y->size[0] * i0] = 0.0;
      }
    }

    if (B->size[1] != 0) {
      i = 3 * (B->size[1] - 1);
      for (cr = 0; cr <= i; cr += 3) {
        for (ic = cr + 1; ic <= cr + 3; ic++) {
          h_y->data[ic - 1] = 0.0;
        }
      }

      br = 0;
      for (cr = 0; cr <= i; cr += 3) {
        ar = -1;
        i0 = br + k;
        for (ib = br; ib + 1 <= i0; ib++) {
          if (B->data[ib] != 0.0) {
            ia = ar;
            for (ic = cr; ic + 1 <= cr + 3; ic++) {
              ia++;
              h_y->data[ic] += B->data[ib] * a->data[ia];
            }
          }

          ar += 3;
        }

        br += k;
      }
    }
  }

  emxFree_real_T(&a);
  emxFree_real_T(&B);
  if ((h_y->size[1] == 1) || (Ga->size[0] == 1)) {
    for (i0 = 0; i0 < 3; i0++) {
      for (i1 = 0; i1 < 3; i1++) {
        sFI[i0 + 3 * i1] = 0.0;
        br = h_y->size[1];
        for (i = 0; i < br; i++) {
          sFI[i0 + 3 * i1] += h_y->data[i0 + h_y->size[0] * i] * Ga->data[i +
            Ga->size[0] * i1];
        }
      }
    }
  } else {
    k = h_y->size[1];
    memset(&sFI[0], 0, 9U * sizeof(double));
    for (cr = 0; cr <= 7; cr += 3) {
      for (ic = cr; ic + 1 <= cr + 3; ic++) {
        sFI[ic] = 0.0;
      }
    }

    br = 0;
    for (cr = 0; cr <= 7; cr += 3) {
      ar = -1;
      i0 = br + k;
      for (ib = br; ib + 1 <= i0; ib++) {
        if (Ga->data[ib] != 0.0) {
          ia = ar;
          for (ic = cr; ic + 1 <= cr + 3; ic++) {
            ia++;
            sFI[ic] += Ga->data[ib] * h_y->data[ia];
          }
        }

        ar += 3;
      }

      br += k;
    }
  }

  emxFree_real_T(&h_y);
  emxFree_real_T(&Ga);
  b_inv(sFI, CovZa);
  for (i0 = 0; i0 < 9; i0++) {
    sB[i0] = iv0[i0];
  }

  /*  for i = 1: 3 */
  /*     sB(i,i) = Za1(i); */
  /* end */
  sB[0] = Za0[0] - anchor_position[0];
  sB[4] = Za0[1] - anchor_position[1];
  sB[8] = Za0[2];
  for (i0 = 0; i0 < 3; i0++) {
    for (i1 = 0; i1 < 3; i1++) {
      dv0[i0 + 3 * i1] = 0.0;
      for (i = 0; i < 3; i++) {
        dv0[i0 + 3 * i1] += 4.0 * sB[i0 + 3 * i] * CovZa[i + 3 * i1];
      }
    }

    for (i1 = 0; i1 < 3; i1++) {
      sFI[i0 + 3 * i1] = 0.0;
      for (i = 0; i < 3; i++) {
        sFI[i0 + 3 * i1] += dv0[i0 + 3 * i] * sB[i + 3 * i1];
      }
    }
  }

  m = Za0[0] - anchor_position[0];
  b_a = Za0[1] - anchor_position[1];

  /* x1,y1,在此处也进行了运算； */
  b_inv(sFI, sB);
  for (i0 = 0; i0 < 2; i0++) {
    for (i1 = 0; i1 < 3; i1++) {
      c_a[i0 + (i1 << 1)] = 0.0;
      for (i = 0; i < 3; i++) {
        c_a[i0 + (i1 << 1)] += (double)d_a[i0 + (i << 1)] * sB[i + 3 * i1];
      }
    }

    for (i1 = 0; i1 < 2; i1++) {
      i_y[i0 + (i1 << 1)] = 0.0;
      for (i = 0; i < 3; i++) {
        i_y[i0 + (i1 << 1)] += c_a[i0 + (i << 1)] * (double)b_b[i + 3 * i1];
      }
    }
  }

  if (fabs(i_y[1]) > fabs(i_y[0])) {
    r = i_y[0] / i_y[1];
    t = 1.0 / (r * i_y[3] - i_y[2]);
    j_y[0] = i_y[3] / i_y[1] * t;
    j_y[1] = -t;
    j_y[2] = -i_y[2] / i_y[1] * t;
    j_y[3] = r * t;
  } else {
    r = i_y[1] / i_y[0];
    t = 1.0 / (i_y[3] - r * i_y[2]);
    j_y[0] = i_y[3] / i_y[0] * t;
    j_y[1] = -r * t;
    j_y[2] = -i_y[2] / i_y[0] * t;
    j_y[3] = t;
  }

  b_inv(sFI, sB);
  e_a[0] = m * m;
  e_a[1] = b_a * b_a;
  e_a[2] = Za0[2] * Za0[2];
  reout[0] = anchor_position[0];
  reout[1] = anchor_position[1];
  for (k = 0; k < 2; k++) {
    for (i0 = 0; i0 < 3; i0++) {
      c_a[k + (i0 << 1)] = 0.0;
      for (i1 = 0; i1 < 2; i1++) {
        c_a[k + (i0 << 1)] += j_y[k + (i1 << 1)] * (double)d_a[i1 + (i0 << 1)];
      }
    }

    Za2[k] = 0.0;
    for (i0 = 0; i0 < 3; i0++) {
      k_y[k + (i0 << 1)] = 0.0;
      for (i1 = 0; i1 < 3; i1++) {
        k_y[k + (i0 << 1)] += c_a[k + (i1 << 1)] * sB[i1 + 3 * i0];
      }

      Za2[k] += k_y[k + (i0 << 1)] * e_a[i0];
    }

    Za[k] = fabs(Za2[k]);
    Za[k] = sqrt(Za[k]);
    tag_position[k] = Za[k];
    tag_position[k] += reout[k];
  }
}

/*
 * File trailer for chanX.c
 *
 * [EOF]
 */
