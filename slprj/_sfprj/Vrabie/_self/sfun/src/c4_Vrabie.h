#ifndef __c4_Vrabie_h__
#define __c4_Vrabie_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc4_VrabieInstanceStruct
#define typedef_SFc4_VrabieInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c4_sfEvent;
  boolean_T c4_isStable;
  boolean_T c4_doneDoubleBufferReInit;
  uint8_T c4_is_active_c4_Vrabie;
  real_T c4_X_data[1990];
  int32_T c4_X_sizes[2];
  boolean_T c4_X_not_empty;
  real_T c4_Y_data[199];
  int32_T c4_Y_sizes[2];
  boolean_T c4_Y_not_empty;
  real_T c4_P[16];
  boolean_T c4_P_not_empty;
  real_T c4_p_1[10];
  boolean_T c4_p_1_not_empty;
  boolean_T c4_has_converged;
  boolean_T c4_has_converged_not_empty;
  uint8_T *c4_i;
  real_T *c4_d;
  real_T (*c4_PP)[16];
  real_T (*c4_x_bar_delta)[10];
  real_T *c4_N;
  real_T *c4_start;
} SFc4_VrabieInstanceStruct;

#endif                                 /*typedef_SFc4_VrabieInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c4_Vrabie_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c4_Vrabie_get_check_sum(mxArray *plhs[]);
extern void c4_Vrabie_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
