#ifndef __c1_Vrabie_h__
#define __c1_Vrabie_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc1_VrabieInstanceStruct
#define typedef_SFc1_VrabieInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  boolean_T c1_isStable;
  boolean_T c1_doneDoubleBufferReInit;
  uint8_T c1_is_active_c1_Vrabie;
  real_T (*c1_x)[4];
  real_T *c1_u;
  real_T *c1_V_dot;
  real_T (*c1_Q)[16];
  real_T *c1_R;
} SFc1_VrabieInstanceStruct;

#endif                                 /*typedef_SFc1_VrabieInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_Vrabie_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_Vrabie_get_check_sum(mxArray *plhs[]);
extern void c1_Vrabie_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
