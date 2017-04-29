#ifndef __c2_Vrabie_h__
#define __c2_Vrabie_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc2_VrabieInstanceStruct
#define typedef_SFc2_VrabieInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_isStable;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_Vrabie;
  real_T (*c2_P)[16];
  real_T (*c2_K)[4];
  real_T *c2_R;
  real_T (*c2_B)[4];
} SFc2_VrabieInstanceStruct;

#endif                                 /*typedef_SFc2_VrabieInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_Vrabie_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_Vrabie_get_check_sum(mxArray *plhs[]);
extern void c2_Vrabie_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
