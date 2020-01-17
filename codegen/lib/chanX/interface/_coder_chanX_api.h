/*
 * File: _coder_chanX_api.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 16-Jan-2020 19:37:25
 */

#ifndef _CODER_CHANX_API_H
#define _CODER_CHANX_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_chanX_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void chanX(real_T num_of_anchor, real_T anchor_position[14], real_T R[6],
                  real_T tag_position[2]);
extern void chanX_api(const mxArray *prhs[3], const mxArray *plhs[1]);
extern void chanX_atexit(void);
extern void chanX_initialize(void);
extern void chanX_terminate(void);
extern void chanX_xil_terminate(void);

#endif

/*
 * File trailer for _coder_chanX_api.h
 *
 * [EOF]
 */
