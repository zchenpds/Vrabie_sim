/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Vrabie_sfun.h"
#include "c4_Vrabie.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Vrabie_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c4_debug_family_names[15] = { "p", "diff", "nargin",
  "nargout", "i", "d", "x_bar_delta", "N", "start", "PP", "X", "Y", "P", "p_1",
  "has_converged" };

/* Function Declarations */
static void initialize_c4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance);
static void initialize_params_c4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance);
static void enable_c4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance);
static void disable_c4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance);
static void c4_update_debugger_state_c4_Vrabie(SFc4_VrabieInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c4_Vrabie(SFc4_VrabieInstanceStruct
  *chartInstance);
static void set_sim_state_c4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_st);
static void finalize_c4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance);
static void sf_gateway_c4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance);
static void mdl_start_c4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance);
static void c4_chartstep_c4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance);
static void initSimStructsc4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber, uint32_T c4_instanceNumber);
static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData);
static boolean_T c4_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_b_has_converged, const char_T *c4_identifier);
static boolean_T c4_b_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_c_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_b_p_1, const char_T *c4_identifier, real_T c4_y[10]);
static void c4_d_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[10]);
static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_e_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_b_P, const char_T *c4_identifier, real_T c4_y[16]);
static void c4_f_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[16]);
static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, real_T
  c4_inData_data[], int32_T c4_inData_sizes[2]);
static void c4_g_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_Y, const char_T *c4_identifier, real_T c4_y_data[], int32_T
  c4_y_sizes[2]);
static void c4_h_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y_data[],
  int32_T c4_y_sizes[2]);
static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, real_T c4_outData_data[], int32_T
  c4_outData_sizes[2]);
static const mxArray *c4_e_sf_marshallOut(void *chartInstanceVoid, real_T
  c4_inData_data[], int32_T c4_inData_sizes[2]);
static void c4_i_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_X, const char_T *c4_identifier, real_T c4_y_data[], int32_T
  c4_y_sizes[2]);
static void c4_j_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y_data[],
  int32_T c4_y_sizes[2]);
static void c4_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, real_T c4_outData_data[], int32_T
  c4_outData_sizes[2]);
static const mxArray *c4_f_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_k_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_b_PP, const char_T *c4_identifier, real_T c4_y[16]);
static void c4_l_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[16]);
static void c4_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_g_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_h_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_i_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static real_T c4_m_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static void c4_n_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[10]);
static void c4_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static void c4_info_helper(const mxArray **c4_info);
static const mxArray *c4_emlrt_marshallOut(const char * c4_u);
static const mxArray *c4_b_emlrt_marshallOut(const uint32_T c4_u);
static void c4_b_info_helper(const mxArray **c4_info);
static void c4_c_info_helper(const mxArray **c4_info);
static void c4_eml_scalar_eg(SFc4_VrabieInstanceStruct *chartInstance);
static boolean_T c4_use_refblas(SFc4_VrabieInstanceStruct *chartInstance);
static void c4_below_threshold(SFc4_VrabieInstanceStruct *chartInstance);
static void c4_threshold(SFc4_VrabieInstanceStruct *chartInstance);
static void c4_scalarEg(SFc4_VrabieInstanceStruct *chartInstance);
static void c4_eml_switch_helper(SFc4_VrabieInstanceStruct *chartInstance);
static void c4_eml_xgemm(SFc4_VrabieInstanceStruct *chartInstance, int32_T c4_k,
  real_T c4_A_data[], int32_T c4_A_sizes[2], real_T c4_B_data[], int32_T
  c4_B_sizes[2], int32_T c4_ldb, real_T c4_C[100]);
static void c4_check_forloop_overflow_error(SFc4_VrabieInstanceStruct
  *chartInstance, boolean_T c4_overflow);
static void c4_mldivide(SFc4_VrabieInstanceStruct *chartInstance, real_T c4_A
  [100], real_T c4_B_data[], int32_T c4_B_sizes[2], real_T c4_b_Y_data[],
  int32_T c4_b_Y_sizes[2]);
static void c4_b_eml_scalar_eg(SFc4_VrabieInstanceStruct *chartInstance);
static void c4_realmin(SFc4_VrabieInstanceStruct *chartInstance);
static void c4_eps(SFc4_VrabieInstanceStruct *chartInstance);
static void c4_eml_matlab_zgetrf(SFc4_VrabieInstanceStruct *chartInstance,
  real_T c4_A[100], real_T c4_b_A[100], int32_T c4_ipiv[10], int32_T *c4_info);
static int32_T c4_eml_ixamax(SFc4_VrabieInstanceStruct *chartInstance, int32_T
  c4_n, real_T c4_x[100], int32_T c4_ix0);
static void c4_b_eml_switch_helper(SFc4_VrabieInstanceStruct *chartInstance);
static void c4_eml_xgeru(SFc4_VrabieInstanceStruct *chartInstance, int32_T c4_m,
  int32_T c4_n, real_T c4_alpha1, int32_T c4_ix0, int32_T c4_iy0, real_T c4_A
  [100], int32_T c4_ia0, real_T c4_b_A[100]);
static void c4_eml_warning(SFc4_VrabieInstanceStruct *chartInstance);
static void c4_eml_xtrsm(SFc4_VrabieInstanceStruct *chartInstance, int32_T c4_n,
  real_T c4_A[100], real_T c4_B_data[], int32_T c4_B_sizes[2], real_T
  c4_b_B_data[], int32_T c4_b_B_sizes[2]);
static void c4_b_eml_xtrsm(SFc4_VrabieInstanceStruct *chartInstance, int32_T
  c4_n, real_T c4_A[100], real_T c4_B_data[], int32_T c4_B_sizes[2], real_T
  c4_b_B_data[], int32_T c4_b_B_sizes[2]);
static real_T c4_rdivide(SFc4_VrabieInstanceStruct *chartInstance, real_T c4_x,
  real_T c4_y);
static void c4_c_eml_scalar_eg(SFc4_VrabieInstanceStruct *chartInstance);
static void c4_b_eml_xgemm(SFc4_VrabieInstanceStruct *chartInstance, int32_T
  c4_k, real_T c4_A_data[], int32_T c4_A_sizes[2], real_T c4_B_data[], int32_T
  c4_B_sizes, int32_T c4_ldb, real_T c4_C[10], real_T c4_b_C[10]);
static void c4_b_below_threshold(SFc4_VrabieInstanceStruct *chartInstance);
static real_T c4_norm(SFc4_VrabieInstanceStruct *chartInstance, real_T c4_x[10]);
static void c4_c_below_threshold(SFc4_VrabieInstanceStruct *chartInstance);
static const mxArray *c4_j_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static int32_T c4_o_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static uint8_T c4_p_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_b_is_active_c4_Vrabie, const char_T *c4_identifier);
static uint8_T c4_q_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_b_eml_matlab_zgetrf(SFc4_VrabieInstanceStruct *chartInstance,
  real_T c4_A[100], int32_T c4_ipiv[10], int32_T *c4_info);
static void c4_b_eml_xgeru(SFc4_VrabieInstanceStruct *chartInstance, int32_T
  c4_m, int32_T c4_n, real_T c4_alpha1, int32_T c4_ix0, int32_T c4_iy0, real_T
  c4_A[100], int32_T c4_ia0);
static void c4_c_eml_xtrsm(SFc4_VrabieInstanceStruct *chartInstance, int32_T
  c4_n, real_T c4_A[100], real_T c4_B_data[], int32_T c4_B_sizes[2]);
static void c4_d_eml_xtrsm(SFc4_VrabieInstanceStruct *chartInstance, int32_T
  c4_n, real_T c4_A[100], real_T c4_B_data[], int32_T c4_B_sizes[2]);
static void c4_c_eml_xgemm(SFc4_VrabieInstanceStruct *chartInstance, int32_T
  c4_k, real_T c4_A_data[], int32_T c4_A_sizes[2], real_T c4_B_data[], int32_T
  c4_B_sizes, int32_T c4_ldb, real_T c4_C[10]);
static void init_dsm_address_info(SFc4_VrabieInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc4_VrabieInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance)
{
  chartInstance->c4_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c4_X_not_empty = false;
  chartInstance->c4_Y_not_empty = false;
  chartInstance->c4_P_not_empty = false;
  chartInstance->c4_p_1_not_empty = false;
  chartInstance->c4_has_converged_not_empty = false;
  chartInstance->c4_is_active_c4_Vrabie = 0U;
}

static void initialize_params_c4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c4_update_debugger_state_c4_Vrabie(SFc4_VrabieInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c4_Vrabie(SFc4_VrabieInstanceStruct
  *chartInstance)
{
  const mxArray *c4_st;
  const mxArray *c4_y = NULL;
  int32_T c4_i0;
  real_T c4_u[16];
  const mxArray *c4_b_y = NULL;
  int32_T c4_i1;
  real_T c4_b_u[16];
  const mxArray *c4_c_y = NULL;
  int32_T c4_u_sizes[2];
  int32_T c4_c_u;
  int32_T c4_d_u;
  int32_T c4_loop_ub;
  int32_T c4_i2;
  real_T c4_u_data[1990];
  const mxArray *c4_d_y = NULL;
  int32_T c4_b_u_sizes[2];
  int32_T c4_e_u;
  int32_T c4_f_u;
  int32_T c4_b_loop_ub;
  int32_T c4_i3;
  real_T c4_b_u_data[199];
  const mxArray *c4_e_y = NULL;
  boolean_T c4_hoistedGlobal;
  boolean_T c4_g_u;
  const mxArray *c4_f_y = NULL;
  int32_T c4_i4;
  real_T c4_h_u[10];
  const mxArray *c4_g_y = NULL;
  uint8_T c4_b_hoistedGlobal;
  uint8_T c4_i_u;
  const mxArray *c4_h_y = NULL;
  c4_st = NULL;
  c4_st = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createcellmatrix(7, 1), false);
  for (c4_i0 = 0; c4_i0 < 16; c4_i0++) {
    c4_u[c4_i0] = (*chartInstance->c4_PP)[c4_i0];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 2, 4, 4), false);
  sf_mex_setcell(c4_y, 0, c4_b_y);
  for (c4_i1 = 0; c4_i1 < 16; c4_i1++) {
    c4_b_u[c4_i1] = chartInstance->c4_P[c4_i1];
  }

  c4_c_y = NULL;
  if (!chartInstance->c4_P_not_empty) {
    sf_mex_assign(&c4_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c4_c_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 2, 4, 4),
                  false);
  }

  sf_mex_setcell(c4_y, 1, c4_c_y);
  c4_u_sizes[0] = 10;
  c4_u_sizes[1] = chartInstance->c4_X_sizes[1];
  c4_c_u = c4_u_sizes[0];
  c4_d_u = c4_u_sizes[1];
  c4_loop_ub = chartInstance->c4_X_sizes[0] * chartInstance->c4_X_sizes[1] - 1;
  for (c4_i2 = 0; c4_i2 <= c4_loop_ub; c4_i2++) {
    c4_u_data[c4_i2] = chartInstance->c4_X_data[c4_i2];
  }

  c4_d_y = NULL;
  if (!chartInstance->c4_X_not_empty) {
    sf_mex_assign(&c4_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c4_d_y, sf_mex_create("y", c4_u_data, 0, 0U, 1U, 0U, 2,
      c4_u_sizes[0], c4_u_sizes[1]), false);
  }

  sf_mex_setcell(c4_y, 2, c4_d_y);
  c4_b_u_sizes[0] = 1;
  c4_b_u_sizes[1] = chartInstance->c4_Y_sizes[1];
  c4_e_u = c4_b_u_sizes[0];
  c4_f_u = c4_b_u_sizes[1];
  c4_b_loop_ub = chartInstance->c4_Y_sizes[0] * chartInstance->c4_Y_sizes[1] - 1;
  for (c4_i3 = 0; c4_i3 <= c4_b_loop_ub; c4_i3++) {
    c4_b_u_data[c4_i3] = chartInstance->c4_Y_data[c4_i3];
  }

  c4_e_y = NULL;
  if (!chartInstance->c4_Y_not_empty) {
    sf_mex_assign(&c4_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c4_e_y, sf_mex_create("y", c4_b_u_data, 0, 0U, 1U, 0U, 2,
      c4_b_u_sizes[0], c4_b_u_sizes[1]), false);
  }

  sf_mex_setcell(c4_y, 3, c4_e_y);
  c4_hoistedGlobal = chartInstance->c4_has_converged;
  c4_g_u = c4_hoistedGlobal;
  c4_f_y = NULL;
  if (!chartInstance->c4_has_converged_not_empty) {
    sf_mex_assign(&c4_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c4_f_y, sf_mex_create("y", &c4_g_u, 11, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c4_y, 4, c4_f_y);
  for (c4_i4 = 0; c4_i4 < 10; c4_i4++) {
    c4_h_u[c4_i4] = chartInstance->c4_p_1[c4_i4];
  }

  c4_g_y = NULL;
  if (!chartInstance->c4_p_1_not_empty) {
    sf_mex_assign(&c4_g_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c4_g_y, sf_mex_create("y", c4_h_u, 0, 0U, 1U, 0U, 1, 10),
                  false);
  }

  sf_mex_setcell(c4_y, 5, c4_g_y);
  c4_b_hoistedGlobal = chartInstance->c4_is_active_c4_Vrabie;
  c4_i_u = c4_b_hoistedGlobal;
  c4_h_y = NULL;
  sf_mex_assign(&c4_h_y, sf_mex_create("y", &c4_i_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 6, c4_h_y);
  sf_mex_assign(&c4_st, c4_y, false);
  return c4_st;
}

static void set_sim_state_c4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_st)
{
  const mxArray *c4_u;
  real_T c4_dv0[16];
  int32_T c4_i5;
  real_T c4_dv1[16];
  int32_T c4_i6;
  int32_T c4_tmp_sizes[2];
  real_T c4_tmp_data[1990];
  int32_T c4_i7;
  int32_T c4_i8;
  int32_T c4_loop_ub;
  int32_T c4_i9;
  int32_T c4_b_tmp_sizes[2];
  real_T c4_b_tmp_data[199];
  int32_T c4_i10;
  int32_T c4_i11;
  int32_T c4_b_loop_ub;
  int32_T c4_i12;
  real_T c4_dv2[10];
  int32_T c4_i13;
  chartInstance->c4_doneDoubleBufferReInit = true;
  c4_u = sf_mex_dup(c4_st);
  c4_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 0)), "PP",
                        c4_dv0);
  for (c4_i5 = 0; c4_i5 < 16; c4_i5++) {
    (*chartInstance->c4_PP)[c4_i5] = c4_dv0[c4_i5];
  }

  c4_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 1)), "P",
                        c4_dv1);
  for (c4_i6 = 0; c4_i6 < 16; c4_i6++) {
    chartInstance->c4_P[c4_i6] = c4_dv1[c4_i6];
  }

  c4_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 2)), "X",
                        c4_tmp_data, c4_tmp_sizes);
  chartInstance->c4_X_sizes[0] = 10;
  chartInstance->c4_X_sizes[1] = c4_tmp_sizes[1];
  c4_i7 = chartInstance->c4_X_sizes[0];
  c4_i8 = chartInstance->c4_X_sizes[1];
  c4_loop_ub = c4_tmp_sizes[0] * c4_tmp_sizes[1] - 1;
  for (c4_i9 = 0; c4_i9 <= c4_loop_ub; c4_i9++) {
    chartInstance->c4_X_data[c4_i9] = c4_tmp_data[c4_i9];
  }

  c4_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 3)), "Y",
                        c4_b_tmp_data, c4_b_tmp_sizes);
  chartInstance->c4_Y_sizes[0] = 1;
  chartInstance->c4_Y_sizes[1] = c4_b_tmp_sizes[1];
  c4_i10 = chartInstance->c4_Y_sizes[0];
  c4_i11 = chartInstance->c4_Y_sizes[1];
  c4_b_loop_ub = c4_b_tmp_sizes[0] * c4_b_tmp_sizes[1] - 1;
  for (c4_i12 = 0; c4_i12 <= c4_b_loop_ub; c4_i12++) {
    chartInstance->c4_Y_data[c4_i12] = c4_b_tmp_data[c4_i12];
  }

  chartInstance->c4_has_converged = c4_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c4_u, 4)), "has_converged");
  c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 5)),
                        "p_1", c4_dv2);
  for (c4_i13 = 0; c4_i13 < 10; c4_i13++) {
    chartInstance->c4_p_1[c4_i13] = c4_dv2[c4_i13];
  }

  chartInstance->c4_is_active_c4_Vrabie = c4_p_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c4_u, 6)), "is_active_c4_Vrabie");
  sf_mex_destroy(&c4_u);
  c4_update_debugger_state_c4_Vrabie(chartInstance);
  sf_mex_destroy(&c4_st);
}

static void finalize_c4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance)
{
  int32_T c4_i14;
  int32_T c4_i15;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_i, 0U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_d, 1U);
  chartInstance->c4_sfEvent = CALL_EVENT;
  c4_chartstep_c4_Vrabie(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_VrabieMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c4_i14 = 0; c4_i14 < 16; c4_i14++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_PP)[c4_i14], 2U);
  }

  for (c4_i15 = 0; c4_i15 < 10; c4_i15++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_x_bar_delta)[c4_i15], 3U);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_N, 4U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_start, 5U);
}

static void mdl_start_c4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_chartstep_c4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance)
{
  uint8_T c4_hoistedGlobal;
  real_T c4_b_hoistedGlobal;
  real_T c4_c_hoistedGlobal;
  real_T c4_d_hoistedGlobal;
  uint8_T c4_b_i;
  real_T c4_b_d;
  int32_T c4_i16;
  real_T c4_b_x_bar_delta[10];
  real_T c4_b_N;
  real_T c4_b_start;
  uint32_T c4_debug_family_var_map[15];
  real_T c4_p[10];
  real_T c4_diff;
  real_T c4_nargin = 5.0;
  real_T c4_nargout = 1.0;
  real_T c4_b_PP[16];
  int32_T c4_i17;
  static char_T c4_varargin_1[12] = { 'N', ' ', 'i', 's', ' ', 't', 'o', 'o',
    ' ', 'b', 'i', 'g' };

  char_T c4_u[12];
  const mxArray *c4_y = NULL;
  int32_T c4_i18;
  static char_T c4_b_varargin_1[27] = { 's', 't', 'a', 'r', 't', ' ', 'c', 'a',
    'n', 'n', 'o', 't', ' ', 'b', 'e', ' ', 'l', 'e', 's', 's', ' ', 't', 'h',
    'a', 'n', ' ', '1' };

  char_T c4_b_u[27];
  const mxArray *c4_b_y = NULL;
  int32_T c4_i19;
  static char_T c4_c_varargin_1[47] = { '(', 'N', ' ', '-', ' ', 's', 't', 'a',
    'r', 't', ')', ' ', 'm', 'u', 's', 't', ' ', 'b', 'e', ' ', 'g', 'r', 'e',
    'a', 't', 'e', 'r', ' ', 't', 'h', 'a', 'n', ' ', 'o', 'r', ' ', 'e', 'q',
    'u', 'a', 'l', ' ', 't', 'o', ' ', '1', '0' };

  char_T c4_c_u[47];
  const mxArray *c4_c_y = NULL;
  int32_T c4_iv0[2];
  int32_T c4_i20;
  int32_T c4_i21;
  int32_T c4_loop_ub;
  int32_T c4_i22;
  boolean_T c4_b0;
  int32_T c4_iv1[2];
  int32_T c4_i23;
  int32_T c4_i24;
  int32_T c4_b_loop_ub;
  int32_T c4_i25;
  boolean_T c4_b1;
  int32_T c4_i26;
  int32_T c4_i27;
  int32_T c4_iv2[2];
  int32_T c4_i28;
  int32_T c4_i29;
  int32_T c4_c_loop_ub;
  int32_T c4_i30;
  boolean_T c4_b2;
  int32_T c4_iv3[2];
  int32_T c4_i31;
  int32_T c4_i32;
  int32_T c4_d_loop_ub;
  int32_T c4_i33;
  boolean_T c4_b3;
  int32_T c4_i34;
  uint32_T c4_u0;
  real_T c4_d0;
  uint8_T c4_u1;
  int32_T c4_c_i;
  int32_T c4_i35;
  uint32_T c4_u2;
  real_T c4_d1;
  uint8_T c4_u3;
  int32_T c4_hoistedGlobal_sizes[2];
  int32_T c4_e_hoistedGlobal;
  int32_T c4_f_hoistedGlobal;
  int32_T c4_e_loop_ub;
  int32_T c4_i36;
  real_T c4_hoistedGlobal_data[1990];
  int32_T c4_b_hoistedGlobal_sizes[2];
  int32_T c4_g_hoistedGlobal;
  int32_T c4_h_hoistedGlobal;
  int32_T c4_f_loop_ub;
  int32_T c4_i37;
  real_T c4_b_hoistedGlobal_data[1990];
  int32_T c4_b_sizes[2];
  int32_T c4_i38;
  int32_T c4_g_loop_ub;
  int32_T c4_i39;
  real_T c4_b_data[1990];
  boolean_T c4_innerDimOk;
  int32_T c4_i40;
  static char_T c4_cv0[21] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T', 'L',
    'A', 'B', ':', 'i', 'n', 'n', 'e', 'r', 'd', 'i', 'm' };

  char_T c4_d_u[21];
  const mxArray *c4_d_y = NULL;
  int32_T c4_i41;
  int32_T c4_i42;
  real_T c4_e_y[100];
  int32_T c4_h_loop_ub;
  int32_T c4_i43;
  int32_T c4_k;
  int32_T c4_c_hoistedGlobal_sizes[2];
  int32_T c4_i_hoistedGlobal;
  int32_T c4_j_hoistedGlobal;
  int32_T c4_i_loop_ub;
  int32_T c4_i44;
  real_T c4_c_hoistedGlobal_data[1990];
  int32_T c4_b_b_sizes[2];
  int32_T c4_b;
  int32_T c4_b_b;
  int32_T c4_j_loop_ub;
  int32_T c4_i45;
  real_T c4_b_b_data[1990];
  int32_T c4_k_hoistedGlobal;
  int32_T c4_l_hoistedGlobal;
  int32_T c4_k_loop_ub;
  int32_T c4_i46;
  int32_T c4_d_hoistedGlobal_sizes[2];
  int32_T c4_m_hoistedGlobal;
  int32_T c4_n_hoistedGlobal;
  int32_T c4_l_loop_ub;
  int32_T c4_i47;
  real_T c4_d_hoistedGlobal_data[199];
  int32_T c4_i48;
  real_T c4_f_y[100];
  int32_T c4_e_hoistedGlobal_sizes[2];
  int32_T c4_o_hoistedGlobal;
  int32_T c4_p_hoistedGlobal;
  int32_T c4_m_loop_ub;
  int32_T c4_i49;
  real_T c4_e_hoistedGlobal_data[1990];
  int32_T c4_c_b_sizes;
  int32_T c4_n_loop_ub;
  int32_T c4_i50;
  real_T c4_c_b_data[199];
  boolean_T c4_b_innerDimOk;
  int32_T c4_i51;
  static char_T c4_cv1[45] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'm', 't', 'i', 'm', 'e', 's', '_', 'n', 'o', 'D', 'y',
    'n', 'a', 'm', 'i', 'c', 'S', 'c', 'a', 'l', 'a', 'r', 'E', 'x', 'p', 'a',
    'n', 's', 'i', 'o', 'n' };

  char_T c4_e_u[45];
  const mxArray *c4_g_y = NULL;
  int32_T c4_i52;
  char_T c4_f_u[21];
  const mxArray *c4_h_y = NULL;
  int32_T c4_i53;
  int32_T c4_o_loop_ub;
  int32_T c4_i54;
  int32_T c4_b_k;
  int32_T c4_i55;
  int32_T c4_i56;
  real_T c4_q_hoistedGlobal[10];
  int32_T c4_f_hoistedGlobal_sizes[2];
  int32_T c4_r_hoistedGlobal;
  int32_T c4_s_hoistedGlobal;
  int32_T c4_p_loop_ub;
  int32_T c4_i57;
  real_T c4_f_hoistedGlobal_data[1990];
  int32_T c4_d_b_sizes;
  int32_T c4_q_loop_ub;
  int32_T c4_i58;
  real_T c4_d_b_data[199];
  int32_T c4_i59;
  int32_T c4_i60;
  int32_T c4_i61;
  real_T c4_b_p[10];
  real_T c4_A;
  int32_T c4_i62;
  real_T c4_c_p[10];
  real_T c4_B;
  int32_T c4_i63;
  int32_T c4_i64;
  int32_T c4_i65;
  int32_T c4_i66;
  int32_T c4_i67;
  int32_T c4_i68;
  real_T c4_t_hoistedGlobal[16];
  int32_T c4_i69;
  real_T c4_u_hoistedGlobal[16];
  int32_T c4_i70;
  int32_T c4_i71;
  int32_T c4_i72;
  int32_T c4_i73;
  real_T c4_b_A[16];
  int32_T c4_i74;
  int32_T c4_i75;
  int32_T c4_i76;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  boolean_T guard3 = false;
  boolean_T guard4 = false;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  c4_hoistedGlobal = *chartInstance->c4_i;
  c4_b_hoistedGlobal = *chartInstance->c4_d;
  c4_c_hoistedGlobal = *chartInstance->c4_N;
  c4_d_hoistedGlobal = *chartInstance->c4_start;
  c4_b_i = c4_hoistedGlobal;
  c4_b_d = c4_b_hoistedGlobal;
  for (c4_i16 = 0; c4_i16 < 10; c4_i16++) {
    c4_b_x_bar_delta[c4_i16] = (*chartInstance->c4_x_bar_delta)[c4_i16];
  }

  c4_b_N = c4_c_hoistedGlobal;
  c4_b_start = c4_d_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 15U, 15U, c4_debug_family_names,
    c4_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_p, 0U, c4_h_sf_marshallOut,
    c4_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_diff, 1U, c4_g_sf_marshallOut,
    c4_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargin, 2U, c4_g_sf_marshallOut,
    c4_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargout, 3U, c4_g_sf_marshallOut,
    c4_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_b_i, 4U, c4_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_b_d, 5U, c4_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_b_x_bar_delta, 6U, c4_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_b_N, 7U, c4_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_b_start, 8U, c4_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_b_PP, 9U, c4_f_sf_marshallOut,
    c4_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(chartInstance->c4_X_data, (const
    int32_T *)&chartInstance->c4_X_sizes, NULL, 1, 10, (void *)
    c4_e_sf_marshallOut, (void *)c4_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(chartInstance->c4_Y_data, (const
    int32_T *)&chartInstance->c4_Y_sizes, NULL, 1, 11, (void *)
    c4_d_sf_marshallOut, (void *)c4_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c4_P, 12U,
    c4_c_sf_marshallOut, c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c4_p_1, 13U,
    c4_b_sf_marshallOut, c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c4_has_converged, 14U,
    c4_sf_marshallOut, c4_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 2);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 3);
  if (CV_EML_IF(0, 1, 0, CV_RELATIONAL_EVAL(4U, 0U, 0, c4_b_N, 200.0, -1, 4U,
        c4_b_N > 200.0))) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 5);
    for (c4_i17 = 0; c4_i17 < 12; c4_i17++) {
      c4_u[c4_i17] = c4_varargin_1[c4_i17];
    }

    c4_y = NULL;
    sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 10, 0U, 1U, 0U, 2, 1, 12),
                  false);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14, c4_y);
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 7);
  if (CV_EML_IF(0, 1, 1, CV_RELATIONAL_EVAL(4U, 0U, 1, c4_b_start, 1.0, -1, 2U,
        c4_b_start < 1.0))) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 8);
    for (c4_i18 = 0; c4_i18 < 27; c4_i18++) {
      c4_b_u[c4_i18] = c4_b_varargin_1[c4_i18];
    }

    c4_b_y = NULL;
    sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_b_u, 10, 0U, 1U, 0U, 2, 1, 27),
                  false);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14, c4_b_y);
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 10);
  if (CV_EML_IF(0, 1, 2, CV_RELATIONAL_EVAL(4U, 0U, 2, c4_b_N - c4_b_start, 10.0,
        -1, 2U, c4_b_N - c4_b_start < 10.0))) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 11);
    for (c4_i19 = 0; c4_i19 < 47; c4_i19++) {
      c4_c_u[c4_i19] = c4_c_varargin_1[c4_i19];
    }

    c4_c_y = NULL;
    sf_mex_assign(&c4_c_y, sf_mex_create("y", c4_c_u, 10, 0U, 1U, 0U, 2, 1, 47),
                  false);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14, c4_c_y);
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 13);
  if (CV_EML_IF(0, 1, 3, !chartInstance->c4_X_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 14);
    chartInstance->c4_X_sizes[0] = 10;
    c4_iv0[0] = 10;
    c4_iv0[1] = (int32_T)_SFD_INTEGER_CHECK("N-start", _SFD_NON_NEGATIVE_CHECK(
      "N-start", c4_b_N - c4_b_start));
    chartInstance->c4_X_sizes[1] = c4_iv0[1];
    c4_i20 = chartInstance->c4_X_sizes[0];
    c4_i21 = chartInstance->c4_X_sizes[1];
    c4_loop_ub = 10 * (int32_T)_SFD_INTEGER_CHECK("N-start",
      _SFD_NON_NEGATIVE_CHECK("N-start", c4_b_N - c4_b_start)) - 1;
    for (c4_i22 = 0; c4_i22 <= c4_loop_ub; c4_i22++) {
      chartInstance->c4_X_data[c4_i22] = 0.0;
    }

    chartInstance->c4_X_not_empty = true;
    c4_b0 = (chartInstance->c4_X_sizes[1] == 0);
    chartInstance->c4_X_not_empty = !c4_b0;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 16);
  if (CV_EML_IF(0, 1, 4, !chartInstance->c4_Y_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 17);
    chartInstance->c4_Y_sizes[0] = 1;
    c4_iv1[0] = 1;
    c4_iv1[1] = (int32_T)_SFD_INTEGER_CHECK("N-start", _SFD_NON_NEGATIVE_CHECK(
      "N-start", c4_b_N - c4_b_start));
    chartInstance->c4_Y_sizes[1] = c4_iv1[1];
    c4_i23 = chartInstance->c4_Y_sizes[0];
    c4_i24 = chartInstance->c4_Y_sizes[1];
    c4_b_loop_ub = (int32_T)_SFD_INTEGER_CHECK("N-start",
      _SFD_NON_NEGATIVE_CHECK("N-start", c4_b_N - c4_b_start)) - 1;
    for (c4_i25 = 0; c4_i25 <= c4_b_loop_ub; c4_i25++) {
      chartInstance->c4_Y_data[c4_i25] = 0.0;
    }

    chartInstance->c4_Y_not_empty = true;
    c4_b1 = (chartInstance->c4_Y_sizes[1] == 0);
    chartInstance->c4_Y_not_empty = !c4_b1;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 19);
  if (CV_EML_IF(0, 1, 5, !chartInstance->c4_P_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 20);
    for (c4_i26 = 0; c4_i26 < 16; c4_i26++) {
      chartInstance->c4_P[c4_i26] = 0.0;
    }

    chartInstance->c4_P_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 22);
  if (CV_EML_IF(0, 1, 6, !chartInstance->c4_p_1_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 23);
    for (c4_i27 = 0; c4_i27 < 10; c4_i27++) {
      chartInstance->c4_p_1[c4_i27] = 0.0;
    }

    chartInstance->c4_p_1_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 25);
  if (CV_EML_IF(0, 1, 7, !chartInstance->c4_has_converged_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 26);
    chartInstance->c4_has_converged = false;
    chartInstance->c4_has_converged_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 29);
  if (CV_EML_IF(0, 1, 8, CV_RELATIONAL_EVAL(4U, 0U, 3, (real_T)c4_b_i, 0.0, -1,
        0U, (real_T)c4_b_i == 0.0))) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 30);
    chartInstance->c4_X_sizes[0] = 10;
    c4_iv2[0] = 10;
    c4_iv2[1] = (int32_T)_SFD_INTEGER_CHECK("N-start", _SFD_NON_NEGATIVE_CHECK(
      "N-start", c4_b_N - c4_b_start));
    chartInstance->c4_X_sizes[1] = c4_iv2[1];
    c4_i28 = chartInstance->c4_X_sizes[0];
    c4_i29 = chartInstance->c4_X_sizes[1];
    c4_c_loop_ub = 10 * (int32_T)_SFD_INTEGER_CHECK("N-start",
      _SFD_NON_NEGATIVE_CHECK("N-start", c4_b_N - c4_b_start)) - 1;
    for (c4_i30 = 0; c4_i30 <= c4_c_loop_ub; c4_i30++) {
      chartInstance->c4_X_data[c4_i30] = 0.0;
    }

    c4_b2 = (chartInstance->c4_X_sizes[1] == 0);
    chartInstance->c4_X_not_empty = !c4_b2;
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 31);
    chartInstance->c4_Y_sizes[0] = 1;
    c4_iv3[0] = 1;
    c4_iv3[1] = (int32_T)_SFD_INTEGER_CHECK("N-start", _SFD_NON_NEGATIVE_CHECK(
      "N-start", c4_b_N - c4_b_start));
    chartInstance->c4_Y_sizes[1] = c4_iv3[1];
    c4_i31 = chartInstance->c4_Y_sizes[0];
    c4_i32 = chartInstance->c4_Y_sizes[1];
    c4_d_loop_ub = (int32_T)_SFD_INTEGER_CHECK("N-start",
      _SFD_NON_NEGATIVE_CHECK("N-start", c4_b_N - c4_b_start)) - 1;
    for (c4_i33 = 0; c4_i33 <= c4_d_loop_ub; c4_i33++) {
      chartInstance->c4_Y_data[c4_i33] = 0.0;
    }

    c4_b3 = (chartInstance->c4_Y_sizes[1] == 0);
    chartInstance->c4_Y_not_empty = !c4_b3;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 32);
    guard4 = false;
    if (CV_EML_COND(0, 1, 0, CV_RELATIONAL_EVAL(4U, 0U, 4, (real_T)c4_b_i,
          c4_b_start, -1, 5U, (real_T)c4_b_i >= c4_b_start))) {
      if (CV_EML_COND(0, 1, 1, CV_RELATIONAL_EVAL(4U, 0U, 5, (real_T)c4_b_i,
            c4_b_N - 1.0, -1, 3U, (real_T)c4_b_i <= c4_b_N - 1.0))) {
        CV_EML_MCDC(0, 1, 0, true);
        CV_EML_IF(0, 1, 9, true);
        _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 33);
        c4_i34 = chartInstance->c4_X_sizes[1];
        c4_u0 = (uint32_T)c4_b_i + 1U;
        if (CV_SATURATION_EVAL(4, 0, 0, 0, c4_u0 > 255U)) {
          c4_u0 = 255U;
        }

        c4_d0 = muDoubleScalarRound((real_T)(uint8_T)c4_u0 - c4_b_start);
        if (c4_d0 < 256.0) {
          if (CV_SATURATION_EVAL(4, 0, 1, 1, c4_d0 >= 0.0)) {
            c4_u1 = (uint8_T)c4_d0;
          } else {
            c4_u1 = 0U;
          }
        } else if (CV_SATURATION_EVAL(4, 0, 1, 0, c4_d0 >= 256.0)) {
          c4_u1 = MAX_uint8_T;
        } else {
          c4_u1 = 0U;
        }

        c4_c_i = (uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("X", (int32_T)c4_u1, 1,
          c4_i34, 2, 0) - 1;
        for (c4_i35 = 0; c4_i35 < 10; c4_i35++) {
          chartInstance->c4_X_data[c4_i35 + chartInstance->c4_X_sizes[0] *
            c4_c_i] = c4_b_x_bar_delta[c4_i35];
        }

        _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 34);
        c4_u2 = (uint32_T)c4_b_i + 1U;
        if (CV_SATURATION_EVAL(4, 0, 2, 0, c4_u2 > 255U)) {
          c4_u2 = 255U;
        }

        c4_d1 = muDoubleScalarRound((real_T)(uint8_T)c4_u2 - c4_b_start);
        if (c4_d1 < 256.0) {
          if (CV_SATURATION_EVAL(4, 0, 3, 1, c4_d1 >= 0.0)) {
            c4_u3 = (uint8_T)c4_d1;
          } else {
            c4_u3 = 0U;
          }
        } else if (CV_SATURATION_EVAL(4, 0, 3, 0, c4_d1 >= 256.0)) {
          c4_u3 = MAX_uint8_T;
        } else {
          c4_u3 = 0U;
        }

        chartInstance->c4_Y_data[chartInstance->c4_Y_sizes[0] * ((uint8_T)
          _SFD_EML_ARRAY_BOUNDS_CHECK("Y", (int32_T)c4_u3, 1,
          chartInstance->c4_Y_sizes[1], 2, 0) - 1)] = c4_b_d;
      } else {
        guard4 = true;
      }
    } else {
      guard4 = true;
    }

    if (guard4 == true) {
      CV_EML_MCDC(0, 1, 0, false);
      CV_EML_IF(0, 1, 9, false);
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 37);
  guard1 = false;
  if (CV_EML_COND(0, 1, 2, CV_RELATIONAL_EVAL(4U, 0U, 6, (real_T)c4_b_i, c4_b_N
        - 1.0, -1, 0U, (real_T)c4_b_i == c4_b_N - 1.0))) {
    if (CV_EML_COND(0, 1, 3, !chartInstance->c4_has_converged)) {
      CV_EML_MCDC(0, 1, 1, true);
      CV_EML_IF(0, 1, 10, true);
      _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 38);
      c4_hoistedGlobal_sizes[0] = 10;
      c4_hoistedGlobal_sizes[1] = chartInstance->c4_X_sizes[1];
      c4_e_hoistedGlobal = c4_hoistedGlobal_sizes[0];
      c4_f_hoistedGlobal = c4_hoistedGlobal_sizes[1];
      c4_e_loop_ub = chartInstance->c4_X_sizes[0] * chartInstance->c4_X_sizes[1]
        - 1;
      for (c4_i36 = 0; c4_i36 <= c4_e_loop_ub; c4_i36++) {
        c4_hoistedGlobal_data[c4_i36] = chartInstance->c4_X_data[c4_i36];
      }

      c4_b_hoistedGlobal_sizes[0] = 10;
      c4_b_hoistedGlobal_sizes[1] = chartInstance->c4_X_sizes[1];
      c4_g_hoistedGlobal = c4_b_hoistedGlobal_sizes[0];
      c4_h_hoistedGlobal = c4_b_hoistedGlobal_sizes[1];
      c4_f_loop_ub = chartInstance->c4_X_sizes[0] * chartInstance->c4_X_sizes[1]
        - 1;
      for (c4_i37 = 0; c4_i37 <= c4_f_loop_ub; c4_i37++) {
        c4_b_hoistedGlobal_data[c4_i37] = chartInstance->c4_X_data[c4_i37];
      }

      c4_b_sizes[0] = c4_b_hoistedGlobal_sizes[1];
      c4_b_sizes[1] = 10;
      for (c4_i38 = 0; c4_i38 < 10; c4_i38++) {
        c4_g_loop_ub = c4_b_hoistedGlobal_sizes[1] - 1;
        for (c4_i39 = 0; c4_i39 <= c4_g_loop_ub; c4_i39++) {
          c4_b_data[c4_i39 + c4_b_sizes[0] * c4_i38] =
            c4_b_hoistedGlobal_data[c4_i38 + c4_b_hoistedGlobal_sizes[0] *
            c4_i39];
        }
      }

      c4_innerDimOk = ((real_T)c4_hoistedGlobal_sizes[1] == (real_T)c4_b_sizes[0]);
      if (!c4_innerDimOk) {
        for (c4_i40 = 0; c4_i40 < 21; c4_i40++) {
          c4_d_u[c4_i40] = c4_cv0[c4_i40];
        }

        c4_d_y = NULL;
        sf_mex_assign(&c4_d_y, sf_mex_create("y", c4_d_u, 10, 0U, 1U, 0U, 2, 1,
          21), false);
        sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                          sf_mex_call_debug(sfGlobalDebugInstanceStruct,
          "message", 1U, 1U, 14, c4_d_y));
      }

      guard3 = false;
      if ((real_T)c4_hoistedGlobal_sizes[1] == 1.0) {
        guard3 = true;
      } else if ((real_T)c4_b_sizes[0] == 1.0) {
        guard3 = true;
      } else {
        c4_k = c4_hoistedGlobal_sizes[1];
        c4_eml_scalar_eg(chartInstance);
        c4_eml_scalar_eg(chartInstance);
        c4_c_hoistedGlobal_sizes[0] = 10;
        c4_c_hoistedGlobal_sizes[1] = c4_hoistedGlobal_sizes[1];
        c4_i_hoistedGlobal = c4_c_hoistedGlobal_sizes[0];
        c4_j_hoistedGlobal = c4_c_hoistedGlobal_sizes[1];
        c4_i_loop_ub = c4_hoistedGlobal_sizes[0] * c4_hoistedGlobal_sizes[1] - 1;
        for (c4_i44 = 0; c4_i44 <= c4_i_loop_ub; c4_i44++) {
          c4_c_hoistedGlobal_data[c4_i44] = c4_hoistedGlobal_data[c4_i44];
        }

        c4_b_b_sizes[0] = c4_b_sizes[0];
        c4_b_b_sizes[1] = 10;
        c4_b = c4_b_b_sizes[0];
        c4_b_b = c4_b_b_sizes[1];
        c4_j_loop_ub = c4_b_sizes[0] * c4_b_sizes[1] - 1;
        for (c4_i45 = 0; c4_i45 <= c4_j_loop_ub; c4_i45++) {
          c4_b_b_data[c4_i45] = c4_b_data[c4_i45];
        }

        c4_eml_xgemm(chartInstance, c4_k, c4_c_hoistedGlobal_data,
                     c4_c_hoistedGlobal_sizes, c4_b_b_data, c4_b_b_sizes, c4_k,
                     c4_e_y);
      }

      if (guard3 == true) {
        for (c4_i41 = 0; c4_i41 < 10; c4_i41++) {
          for (c4_i42 = 0; c4_i42 < 10; c4_i42++) {
            c4_e_y[c4_i41 + 10 * c4_i42] = 0.0;
            c4_h_loop_ub = c4_hoistedGlobal_sizes[1] - 1;
            for (c4_i43 = 0; c4_i43 <= c4_h_loop_ub; c4_i43++) {
              c4_e_y[c4_i41 + 10 * c4_i42] += c4_hoistedGlobal_data[c4_i41 +
                c4_hoistedGlobal_sizes[0] * c4_i43] * c4_b_data[c4_i43 +
                c4_b_sizes[0] * c4_i42];
            }
          }
        }
      }

      c4_hoistedGlobal_sizes[0] = 10;
      c4_hoistedGlobal_sizes[1] = chartInstance->c4_X_sizes[1];
      c4_k_hoistedGlobal = c4_hoistedGlobal_sizes[0];
      c4_l_hoistedGlobal = c4_hoistedGlobal_sizes[1];
      c4_k_loop_ub = chartInstance->c4_X_sizes[0] * chartInstance->c4_X_sizes[1]
        - 1;
      for (c4_i46 = 0; c4_i46 <= c4_k_loop_ub; c4_i46++) {
        c4_hoistedGlobal_data[c4_i46] = chartInstance->c4_X_data[c4_i46];
      }

      c4_d_hoistedGlobal_sizes[0] = 1;
      c4_d_hoistedGlobal_sizes[1] = chartInstance->c4_Y_sizes[1];
      c4_m_hoistedGlobal = c4_d_hoistedGlobal_sizes[0];
      c4_n_hoistedGlobal = c4_d_hoistedGlobal_sizes[1];
      c4_l_loop_ub = chartInstance->c4_Y_sizes[0] * chartInstance->c4_Y_sizes[1]
        - 1;
      for (c4_i47 = 0; c4_i47 <= c4_l_loop_ub; c4_i47++) {
        c4_d_hoistedGlobal_data[c4_i47] = chartInstance->c4_Y_data[c4_i47];
      }

      for (c4_i48 = 0; c4_i48 < 100; c4_i48++) {
        c4_f_y[c4_i48] = c4_e_y[c4_i48];
      }

      c4_e_hoistedGlobal_sizes[0] = 10;
      c4_e_hoistedGlobal_sizes[1] = c4_hoistedGlobal_sizes[1];
      c4_o_hoistedGlobal = c4_e_hoistedGlobal_sizes[0];
      c4_p_hoistedGlobal = c4_e_hoistedGlobal_sizes[1];
      c4_m_loop_ub = c4_hoistedGlobal_sizes[0] * c4_hoistedGlobal_sizes[1] - 1;
      for (c4_i49 = 0; c4_i49 <= c4_m_loop_ub; c4_i49++) {
        c4_e_hoistedGlobal_data[c4_i49] = c4_hoistedGlobal_data[c4_i49];
      }

      c4_mldivide(chartInstance, c4_f_y, c4_e_hoistedGlobal_data,
                  c4_e_hoistedGlobal_sizes, c4_b_hoistedGlobal_data,
                  c4_b_hoistedGlobal_sizes);
      c4_c_b_sizes = c4_d_hoistedGlobal_sizes[1];
      c4_n_loop_ub = c4_d_hoistedGlobal_sizes[1] - 1;
      for (c4_i50 = 0; c4_i50 <= c4_n_loop_ub; c4_i50++) {
        c4_c_b_data[c4_i50] = c4_d_hoistedGlobal_data[c4_d_hoistedGlobal_sizes[0]
          * c4_i50];
      }

      c4_b_innerDimOk = ((real_T)c4_b_hoistedGlobal_sizes[1] == (real_T)
                         c4_c_b_sizes);
      if (!c4_b_innerDimOk) {
        if (c4_c_b_sizes == 1) {
          for (c4_i51 = 0; c4_i51 < 45; c4_i51++) {
            c4_e_u[c4_i51] = c4_cv1[c4_i51];
          }

          c4_g_y = NULL;
          sf_mex_assign(&c4_g_y, sf_mex_create("y", c4_e_u, 10, 0U, 1U, 0U, 2, 1,
            45), false);
          sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                            sf_mex_call_debug(sfGlobalDebugInstanceStruct,
            "message", 1U, 1U, 14, c4_g_y));
        } else {
          for (c4_i52 = 0; c4_i52 < 21; c4_i52++) {
            c4_f_u[c4_i52] = c4_cv0[c4_i52];
          }

          c4_h_y = NULL;
          sf_mex_assign(&c4_h_y, sf_mex_create("y", c4_f_u, 10, 0U, 1U, 0U, 2, 1,
            21), false);
          sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                            sf_mex_call_debug(sfGlobalDebugInstanceStruct,
            "message", 1U, 1U, 14, c4_h_y));
        }
      }

      guard2 = false;
      if ((real_T)c4_b_hoistedGlobal_sizes[1] == 1.0) {
        guard2 = true;
      } else if ((real_T)c4_c_b_sizes == 1.0) {
        guard2 = true;
      } else {
        c4_b_k = c4_b_hoistedGlobal_sizes[1];
        c4_c_eml_scalar_eg(chartInstance);
        c4_c_eml_scalar_eg(chartInstance);
        for (c4_i55 = 0; c4_i55 < 10; c4_i55++) {
          c4_p[c4_i55] = 0.0;
        }

        for (c4_i56 = 0; c4_i56 < 10; c4_i56++) {
          c4_q_hoistedGlobal[c4_i56] = 0.0;
        }

        c4_f_hoistedGlobal_sizes[0] = 10;
        c4_f_hoistedGlobal_sizes[1] = c4_b_hoistedGlobal_sizes[1];
        c4_r_hoistedGlobal = c4_f_hoistedGlobal_sizes[0];
        c4_s_hoistedGlobal = c4_f_hoistedGlobal_sizes[1];
        c4_p_loop_ub = c4_b_hoistedGlobal_sizes[0] * c4_b_hoistedGlobal_sizes[1]
          - 1;
        for (c4_i57 = 0; c4_i57 <= c4_p_loop_ub; c4_i57++) {
          c4_f_hoistedGlobal_data[c4_i57] = c4_b_hoistedGlobal_data[c4_i57];
        }

        c4_d_b_sizes = c4_c_b_sizes;
        c4_q_loop_ub = c4_c_b_sizes - 1;
        for (c4_i58 = 0; c4_i58 <= c4_q_loop_ub; c4_i58++) {
          c4_d_b_data[c4_i58] = c4_c_b_data[c4_i58];
        }

        c4_c_eml_xgemm(chartInstance, c4_b_k, c4_f_hoistedGlobal_data,
                       c4_f_hoistedGlobal_sizes, c4_d_b_data, c4_d_b_sizes,
                       c4_b_k, c4_q_hoistedGlobal);
        for (c4_i59 = 0; c4_i59 < 10; c4_i59++) {
          c4_p[c4_i59] = c4_q_hoistedGlobal[c4_i59];
        }
      }

      if (guard2 == true) {
        for (c4_i53 = 0; c4_i53 < 10; c4_i53++) {
          c4_p[c4_i53] = 0.0;
          c4_o_loop_ub = c4_b_hoistedGlobal_sizes[1] - 1;
          for (c4_i54 = 0; c4_i54 <= c4_o_loop_ub; c4_i54++) {
            c4_p[c4_i53] += c4_b_hoistedGlobal_data[c4_i53 +
              c4_b_hoistedGlobal_sizes[0] * c4_i54] * c4_c_b_data[c4_i54];
          }
        }
      }

      _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 39);
      for (c4_i60 = 0; c4_i60 < 10; c4_i60++) {
        c4_q_hoistedGlobal[c4_i60] = chartInstance->c4_p_1[c4_i60];
      }

      for (c4_i61 = 0; c4_i61 < 10; c4_i61++) {
        c4_b_p[c4_i61] = c4_p[c4_i61] - c4_q_hoistedGlobal[c4_i61];
      }

      c4_A = c4_norm(chartInstance, c4_b_p);
      for (c4_i62 = 0; c4_i62 < 10; c4_i62++) {
        c4_c_p[c4_i62] = c4_p[c4_i62];
      }

      c4_B = c4_norm(chartInstance, c4_c_p);
      c4_diff = c4_rdivide(chartInstance, c4_A, c4_B);
      _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 40);
      if (CV_EML_IF(0, 1, 11, CV_RELATIONAL_EVAL(4U, 0U, 8, c4_diff, 0.1, -1, 2U,
            c4_diff < 0.1))) {
        _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 41);
        chartInstance->c4_has_converged = true;
      }

      _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 43);
      for (c4_i63 = 0; c4_i63 < 10; c4_i63++) {
        chartInstance->c4_p_1[c4_i63] = c4_p[c4_i63];
      }

      _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 45);
      for (c4_i64 = 0; c4_i64 < 16; c4_i64++) {
        chartInstance->c4_P[c4_i64] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 46);
      for (c4_i65 = 0; c4_i65 < 4; c4_i65++) {
        chartInstance->c4_P[c4_i65] = c4_p[c4_i65];
      }

      _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 47);
      for (c4_i66 = 0; c4_i66 < 3; c4_i66++) {
        chartInstance->c4_P[c4_i66 + 5] = c4_p[c4_i66 + 4];
      }

      _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 48);
      for (c4_i67 = 0; c4_i67 < 2; c4_i67++) {
        chartInstance->c4_P[c4_i67 + 10] = c4_p[c4_i67 + 7];
      }

      _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 49);
      chartInstance->c4_P[15] = c4_p[9];
      _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 50);
      for (c4_i68 = 0; c4_i68 < 16; c4_i68++) {
        c4_t_hoistedGlobal[c4_i68] = chartInstance->c4_P[c4_i68];
      }

      for (c4_i69 = 0; c4_i69 < 16; c4_i69++) {
        c4_u_hoistedGlobal[c4_i69] = chartInstance->c4_P[c4_i69];
      }

      c4_i70 = 0;
      for (c4_i71 = 0; c4_i71 < 4; c4_i71++) {
        c4_i72 = 0;
        for (c4_i73 = 0; c4_i73 < 4; c4_i73++) {
          c4_b_A[c4_i73 + c4_i70] = c4_t_hoistedGlobal[c4_i73 + c4_i70] +
            c4_u_hoistedGlobal[c4_i72 + c4_i71];
          c4_i72 += 4;
        }

        c4_i70 += 4;
      }

      for (c4_i74 = 0; c4_i74 < 16; c4_i74++) {
        chartInstance->c4_P[c4_i74] = c4_b_A[c4_i74] / 2.0;
      }
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1 == true) {
    CV_EML_MCDC(0, 1, 1, false);
    CV_EML_IF(0, 1, 10, false);
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 53);
  for (c4_i75 = 0; c4_i75 < 16; c4_i75++) {
    c4_b_PP[c4_i75] = chartInstance->c4_P[c4_i75];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, -53);
  _SFD_SYMBOL_SCOPE_POP();
  for (c4_i76 = 0; c4_i76 < 16; c4_i76++) {
    (*chartInstance->c4_PP)[c4_i76] = c4_b_PP[c4_i76];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
}

static void initSimStructsc4_Vrabie(SFc4_VrabieInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber, uint32_T c4_instanceNumber)
{
  (void)c4_machineNumber;
  (void)c4_chartNumber;
  (void)c4_instanceNumber;
}

static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  boolean_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_VrabieInstanceStruct *chartInstance;
  chartInstance = (SFc4_VrabieInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(boolean_T *)c4_inData;
  c4_y = NULL;
  if (!chartInstance->c4_has_converged_not_empty) {
    sf_mex_assign(&c4_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 11, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static boolean_T c4_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_b_has_converged, const char_T *c4_identifier)
{
  boolean_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_has_converged),
    &c4_thisId);
  sf_mex_destroy(&c4_b_has_converged);
  return c4_y;
}

static boolean_T c4_b_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  boolean_T c4_y;
  boolean_T c4_b4;
  if (mxIsEmpty(c4_u)) {
    chartInstance->c4_has_converged_not_empty = false;
  } else {
    chartInstance->c4_has_converged_not_empty = true;
    sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_b4, 1, 11, 0U, 0, 0U, 0);
    c4_y = c4_b4;
  }

  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_has_converged;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  boolean_T c4_y;
  SFc4_VrabieInstanceStruct *chartInstance;
  chartInstance = (SFc4_VrabieInstanceStruct *)chartInstanceVoid;
  c4_b_has_converged = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_has_converged),
    &c4_thisId);
  sf_mex_destroy(&c4_b_has_converged);
  *(boolean_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i77;
  real_T c4_b_inData[10];
  int32_T c4_i78;
  real_T c4_u[10];
  const mxArray *c4_y = NULL;
  SFc4_VrabieInstanceStruct *chartInstance;
  chartInstance = (SFc4_VrabieInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i77 = 0; c4_i77 < 10; c4_i77++) {
    c4_b_inData[c4_i77] = (*(real_T (*)[10])c4_inData)[c4_i77];
  }

  for (c4_i78 = 0; c4_i78 < 10; c4_i78++) {
    c4_u[c4_i78] = c4_b_inData[c4_i78];
  }

  c4_y = NULL;
  if (!chartInstance->c4_p_1_not_empty) {
    sf_mex_assign(&c4_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 1, 10), false);
  }

  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static void c4_c_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_b_p_1, const char_T *c4_identifier, real_T c4_y[10])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_p_1), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_b_p_1);
}

static void c4_d_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[10])
{
  real_T c4_dv3[10];
  int32_T c4_i79;
  if (mxIsEmpty(c4_u)) {
    chartInstance->c4_p_1_not_empty = false;
  } else {
    chartInstance->c4_p_1_not_empty = true;
    sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_dv3, 1, 0, 0U, 1, 0U, 1, 10);
    for (c4_i79 = 0; c4_i79 < 10; c4_i79++) {
      c4_y[c4_i79] = c4_dv3[c4_i79];
    }
  }

  sf_mex_destroy(&c4_u);
}

static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_p_1;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[10];
  int32_T c4_i80;
  SFc4_VrabieInstanceStruct *chartInstance;
  chartInstance = (SFc4_VrabieInstanceStruct *)chartInstanceVoid;
  c4_b_p_1 = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_p_1), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_b_p_1);
  for (c4_i80 = 0; c4_i80 < 10; c4_i80++) {
    (*(real_T (*)[10])c4_outData)[c4_i80] = c4_y[c4_i80];
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i81;
  int32_T c4_i82;
  int32_T c4_i83;
  real_T c4_b_inData[16];
  int32_T c4_i84;
  int32_T c4_i85;
  int32_T c4_i86;
  real_T c4_u[16];
  const mxArray *c4_y = NULL;
  SFc4_VrabieInstanceStruct *chartInstance;
  chartInstance = (SFc4_VrabieInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_i81 = 0;
  for (c4_i82 = 0; c4_i82 < 4; c4_i82++) {
    for (c4_i83 = 0; c4_i83 < 4; c4_i83++) {
      c4_b_inData[c4_i83 + c4_i81] = (*(real_T (*)[16])c4_inData)[c4_i83 +
        c4_i81];
    }

    c4_i81 += 4;
  }

  c4_i84 = 0;
  for (c4_i85 = 0; c4_i85 < 4; c4_i85++) {
    for (c4_i86 = 0; c4_i86 < 4; c4_i86++) {
      c4_u[c4_i86 + c4_i84] = c4_b_inData[c4_i86 + c4_i84];
    }

    c4_i84 += 4;
  }

  c4_y = NULL;
  if (!chartInstance->c4_P_not_empty) {
    sf_mex_assign(&c4_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 2, 4, 4), false);
  }

  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static void c4_e_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_b_P, const char_T *c4_identifier, real_T c4_y[16])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_P), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_b_P);
}

static void c4_f_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[16])
{
  real_T c4_dv4[16];
  int32_T c4_i87;
  if (mxIsEmpty(c4_u)) {
    chartInstance->c4_P_not_empty = false;
  } else {
    chartInstance->c4_P_not_empty = true;
    sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_dv4, 1, 0, 0U, 1, 0U, 2, 4,
                  4);
    for (c4_i87 = 0; c4_i87 < 16; c4_i87++) {
      c4_y[c4_i87] = c4_dv4[c4_i87];
    }
  }

  sf_mex_destroy(&c4_u);
}

static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_P;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[16];
  int32_T c4_i88;
  int32_T c4_i89;
  int32_T c4_i90;
  SFc4_VrabieInstanceStruct *chartInstance;
  chartInstance = (SFc4_VrabieInstanceStruct *)chartInstanceVoid;
  c4_b_P = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_P), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_b_P);
  c4_i88 = 0;
  for (c4_i89 = 0; c4_i89 < 4; c4_i89++) {
    for (c4_i90 = 0; c4_i90 < 4; c4_i90++) {
      (*(real_T (*)[16])c4_outData)[c4_i90 + c4_i88] = c4_y[c4_i90 + c4_i88];
    }

    c4_i88 += 4;
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, real_T
  c4_inData_data[], int32_T c4_inData_sizes[2])
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_u_sizes[2];
  int32_T c4_u;
  int32_T c4_b_u;
  int32_T c4_inData;
  int32_T c4_b_inData;
  int32_T c4_b_inData_sizes;
  int32_T c4_loop_ub;
  int32_T c4_i91;
  real_T c4_b_inData_data[199];
  int32_T c4_b_loop_ub;
  int32_T c4_i92;
  real_T c4_u_data[199];
  const mxArray *c4_y = NULL;
  SFc4_VrabieInstanceStruct *chartInstance;
  chartInstance = (SFc4_VrabieInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u_sizes[0] = 1;
  c4_u_sizes[1] = c4_inData_sizes[1];
  c4_u = c4_u_sizes[0];
  c4_b_u = c4_u_sizes[1];
  c4_inData = c4_inData_sizes[0];
  c4_b_inData = c4_inData_sizes[1];
  c4_b_inData_sizes = c4_inData * c4_b_inData;
  c4_loop_ub = c4_inData * c4_b_inData - 1;
  for (c4_i91 = 0; c4_i91 <= c4_loop_ub; c4_i91++) {
    c4_b_inData_data[c4_i91] = c4_inData_data[c4_i91];
  }

  c4_b_loop_ub = c4_b_inData_sizes - 1;
  for (c4_i92 = 0; c4_i92 <= c4_b_loop_ub; c4_i92++) {
    c4_u_data[c4_i92] = c4_b_inData_data[c4_i92];
  }

  c4_y = NULL;
  if (!chartInstance->c4_Y_not_empty) {
    sf_mex_assign(&c4_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c4_y, sf_mex_create("y", c4_u_data, 0, 0U, 1U, 0U, 2,
      c4_u_sizes[0], c4_u_sizes[1]), false);
  }

  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static void c4_g_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_Y, const char_T *c4_identifier, real_T c4_y_data[], int32_T
  c4_y_sizes[2])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_Y), &c4_thisId, c4_y_data,
                        c4_y_sizes);
  sf_mex_destroy(&c4_Y);
}

static void c4_h_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y_data[],
  int32_T c4_y_sizes[2])
{
  int32_T c4_i93;
  uint32_T c4_uv0[2];
  int32_T c4_i94;
  static boolean_T c4_bv0[2] = { false, true };

  boolean_T c4_bv1[2];
  int32_T c4_tmp_sizes[2];
  real_T c4_tmp_data[199];
  int32_T c4_y;
  int32_T c4_b_y;
  int32_T c4_loop_ub;
  int32_T c4_i95;
  for (c4_i93 = 0; c4_i93 < 2; c4_i93++) {
    c4_uv0[c4_i93] = 1U + 198U * (uint32_T)c4_i93;
  }

  if (mxIsEmpty(c4_u)) {
    chartInstance->c4_Y_not_empty = false;
    c4_y_sizes[0] = 1;
    c4_y_sizes[1] = 0;
  } else {
    chartInstance->c4_Y_not_empty = true;
    for (c4_i94 = 0; c4_i94 < 2; c4_i94++) {
      c4_bv1[c4_i94] = c4_bv0[c4_i94];
    }

    sf_mex_import_vs(c4_parentId, sf_mex_dup(c4_u), c4_tmp_data, 1, 0, 0U, 1, 0U,
                     2, c4_bv1, c4_uv0, c4_tmp_sizes);
    c4_y_sizes[0] = 1;
    c4_y_sizes[1] = c4_tmp_sizes[1];
    c4_y = c4_y_sizes[0];
    c4_b_y = c4_y_sizes[1];
    c4_loop_ub = c4_tmp_sizes[0] * c4_tmp_sizes[1] - 1;
    for (c4_i95 = 0; c4_i95 <= c4_loop_ub; c4_i95++) {
      c4_y_data[c4_i95] = c4_tmp_data[c4_i95];
    }
  }

  sf_mex_destroy(&c4_u);
}

static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, real_T c4_outData_data[], int32_T
  c4_outData_sizes[2])
{
  const mxArray *c4_Y;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int32_T c4_y_sizes[2];
  real_T c4_y_data[199];
  int32_T c4_loop_ub;
  int32_T c4_i96;
  SFc4_VrabieInstanceStruct *chartInstance;
  chartInstance = (SFc4_VrabieInstanceStruct *)chartInstanceVoid;
  c4_Y = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_Y), &c4_thisId, c4_y_data,
                        c4_y_sizes);
  sf_mex_destroy(&c4_Y);
  c4_outData_sizes[0] = 1;
  c4_outData_sizes[1] = c4_y_sizes[1];
  c4_loop_ub = c4_y_sizes[1] - 1;
  for (c4_i96 = 0; c4_i96 <= c4_loop_ub; c4_i96++) {
    c4_outData_data[c4_outData_sizes[0] * c4_i96] = c4_y_data[c4_y_sizes[0] *
      c4_i96];
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_e_sf_marshallOut(void *chartInstanceVoid, real_T
  c4_inData_data[], int32_T c4_inData_sizes[2])
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_u_sizes[2];
  int32_T c4_u;
  int32_T c4_b_u;
  int32_T c4_inData;
  int32_T c4_b_inData;
  int32_T c4_b_inData_sizes;
  int32_T c4_loop_ub;
  int32_T c4_i97;
  real_T c4_b_inData_data[1990];
  int32_T c4_b_loop_ub;
  int32_T c4_i98;
  real_T c4_u_data[1990];
  const mxArray *c4_y = NULL;
  SFc4_VrabieInstanceStruct *chartInstance;
  chartInstance = (SFc4_VrabieInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u_sizes[0] = 10;
  c4_u_sizes[1] = c4_inData_sizes[1];
  c4_u = c4_u_sizes[0];
  c4_b_u = c4_u_sizes[1];
  c4_inData = c4_inData_sizes[0];
  c4_b_inData = c4_inData_sizes[1];
  c4_b_inData_sizes = c4_inData * c4_b_inData;
  c4_loop_ub = c4_inData * c4_b_inData - 1;
  for (c4_i97 = 0; c4_i97 <= c4_loop_ub; c4_i97++) {
    c4_b_inData_data[c4_i97] = c4_inData_data[c4_i97];
  }

  c4_b_loop_ub = c4_b_inData_sizes - 1;
  for (c4_i98 = 0; c4_i98 <= c4_b_loop_ub; c4_i98++) {
    c4_u_data[c4_i98] = c4_b_inData_data[c4_i98];
  }

  c4_y = NULL;
  if (!chartInstance->c4_X_not_empty) {
    sf_mex_assign(&c4_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c4_y, sf_mex_create("y", c4_u_data, 0, 0U, 1U, 0U, 2,
      c4_u_sizes[0], c4_u_sizes[1]), false);
  }

  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static void c4_i_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_X, const char_T *c4_identifier, real_T c4_y_data[], int32_T
  c4_y_sizes[2])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_X), &c4_thisId, c4_y_data,
                        c4_y_sizes);
  sf_mex_destroy(&c4_X);
}

static void c4_j_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y_data[],
  int32_T c4_y_sizes[2])
{
  int32_T c4_i99;
  uint32_T c4_uv1[2];
  int32_T c4_i100;
  static boolean_T c4_bv2[2] = { false, true };

  boolean_T c4_bv3[2];
  int32_T c4_tmp_sizes[2];
  real_T c4_tmp_data[1990];
  int32_T c4_y;
  int32_T c4_b_y;
  int32_T c4_loop_ub;
  int32_T c4_i101;
  for (c4_i99 = 0; c4_i99 < 2; c4_i99++) {
    c4_uv1[c4_i99] = 10U + 189U * (uint32_T)c4_i99;
  }

  if (mxIsEmpty(c4_u)) {
    chartInstance->c4_X_not_empty = false;
    c4_y_sizes[0] = 10;
    c4_y_sizes[1] = 0;
  } else {
    chartInstance->c4_X_not_empty = true;
    for (c4_i100 = 0; c4_i100 < 2; c4_i100++) {
      c4_bv3[c4_i100] = c4_bv2[c4_i100];
    }

    sf_mex_import_vs(c4_parentId, sf_mex_dup(c4_u), c4_tmp_data, 1, 0, 0U, 1, 0U,
                     2, c4_bv3, c4_uv1, c4_tmp_sizes);
    c4_y_sizes[0] = 10;
    c4_y_sizes[1] = c4_tmp_sizes[1];
    c4_y = c4_y_sizes[0];
    c4_b_y = c4_y_sizes[1];
    c4_loop_ub = c4_tmp_sizes[0] * c4_tmp_sizes[1] - 1;
    for (c4_i101 = 0; c4_i101 <= c4_loop_ub; c4_i101++) {
      c4_y_data[c4_i101] = c4_tmp_data[c4_i101];
    }
  }

  sf_mex_destroy(&c4_u);
}

static void c4_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, real_T c4_outData_data[], int32_T
  c4_outData_sizes[2])
{
  const mxArray *c4_X;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int32_T c4_y_sizes[2];
  real_T c4_y_data[1990];
  int32_T c4_loop_ub;
  int32_T c4_i102;
  int32_T c4_i103;
  SFc4_VrabieInstanceStruct *chartInstance;
  chartInstance = (SFc4_VrabieInstanceStruct *)chartInstanceVoid;
  c4_X = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_X), &c4_thisId, c4_y_data,
                        c4_y_sizes);
  sf_mex_destroy(&c4_X);
  c4_outData_sizes[0] = 10;
  c4_outData_sizes[1] = c4_y_sizes[1];
  c4_loop_ub = c4_y_sizes[1] - 1;
  for (c4_i102 = 0; c4_i102 <= c4_loop_ub; c4_i102++) {
    for (c4_i103 = 0; c4_i103 < 10; c4_i103++) {
      c4_outData_data[c4_i103 + c4_outData_sizes[0] * c4_i102] =
        c4_y_data[c4_i103 + c4_y_sizes[0] * c4_i102];
    }
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_f_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i104;
  int32_T c4_i105;
  int32_T c4_i106;
  real_T c4_b_inData[16];
  int32_T c4_i107;
  int32_T c4_i108;
  int32_T c4_i109;
  real_T c4_u[16];
  const mxArray *c4_y = NULL;
  SFc4_VrabieInstanceStruct *chartInstance;
  chartInstance = (SFc4_VrabieInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_i104 = 0;
  for (c4_i105 = 0; c4_i105 < 4; c4_i105++) {
    for (c4_i106 = 0; c4_i106 < 4; c4_i106++) {
      c4_b_inData[c4_i106 + c4_i104] = (*(real_T (*)[16])c4_inData)[c4_i106 +
        c4_i104];
    }

    c4_i104 += 4;
  }

  c4_i107 = 0;
  for (c4_i108 = 0; c4_i108 < 4; c4_i108++) {
    for (c4_i109 = 0; c4_i109 < 4; c4_i109++) {
      c4_u[c4_i109 + c4_i107] = c4_b_inData[c4_i109 + c4_i107];
    }

    c4_i107 += 4;
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 2, 4, 4), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static void c4_k_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_b_PP, const char_T *c4_identifier, real_T c4_y[16])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_PP), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_b_PP);
}

static void c4_l_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[16])
{
  real_T c4_dv5[16];
  int32_T c4_i110;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_dv5, 1, 0, 0U, 1, 0U, 2, 4, 4);
  for (c4_i110 = 0; c4_i110 < 16; c4_i110++) {
    c4_y[c4_i110] = c4_dv5[c4_i110];
  }

  sf_mex_destroy(&c4_u);
}

static void c4_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_PP;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[16];
  int32_T c4_i111;
  int32_T c4_i112;
  int32_T c4_i113;
  SFc4_VrabieInstanceStruct *chartInstance;
  chartInstance = (SFc4_VrabieInstanceStruct *)chartInstanceVoid;
  c4_b_PP = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_PP), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_b_PP);
  c4_i111 = 0;
  for (c4_i112 = 0; c4_i112 < 4; c4_i112++) {
    for (c4_i113 = 0; c4_i113 < 4; c4_i113++) {
      (*(real_T (*)[16])c4_outData)[c4_i113 + c4_i111] = c4_y[c4_i113 + c4_i111];
    }

    c4_i111 += 4;
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_g_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_VrabieInstanceStruct *chartInstance;
  chartInstance = (SFc4_VrabieInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static const mxArray *c4_h_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i114;
  real_T c4_b_inData[10];
  int32_T c4_i115;
  real_T c4_u[10];
  const mxArray *c4_y = NULL;
  SFc4_VrabieInstanceStruct *chartInstance;
  chartInstance = (SFc4_VrabieInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i114 = 0; c4_i114 < 10; c4_i114++) {
    c4_b_inData[c4_i114] = (*(real_T (*)[10])c4_inData)[c4_i114];
  }

  for (c4_i115 = 0; c4_i115 < 10; c4_i115++) {
    c4_u[c4_i115] = c4_b_inData[c4_i115];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 1, 10), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static const mxArray *c4_i_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  uint8_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_VrabieInstanceStruct *chartInstance;
  chartInstance = (SFc4_VrabieInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(uint8_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static real_T c4_m_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d2;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d2, 1, 0, 0U, 0, 0U, 0);
  c4_y = c4_d2;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_nargout;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_VrabieInstanceStruct *chartInstance;
  chartInstance = (SFc4_VrabieInstanceStruct *)chartInstanceVoid;
  c4_nargout = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_nargout), &c4_thisId);
  sf_mex_destroy(&c4_nargout);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static void c4_n_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[10])
{
  real_T c4_dv6[10];
  int32_T c4_i116;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_dv6, 1, 0, 0U, 1, 0U, 1, 10);
  for (c4_i116 = 0; c4_i116 < 10; c4_i116++) {
    c4_y[c4_i116] = c4_dv6[c4_i116];
  }

  sf_mex_destroy(&c4_u);
}

static void c4_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_p;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[10];
  int32_T c4_i117;
  SFc4_VrabieInstanceStruct *chartInstance;
  chartInstance = (SFc4_VrabieInstanceStruct *)chartInstanceVoid;
  c4_p = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_p), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_p);
  for (c4_i117 = 0; c4_i117 < 10; c4_i117++) {
    (*(real_T (*)[10])c4_outData)[c4_i117] = c4_y[c4_i117];
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

const mxArray *sf_c4_Vrabie_get_eml_resolved_functions_info(void)
{
  const mxArray *c4_nameCaptureInfo = NULL;
  c4_nameCaptureInfo = NULL;
  sf_mex_assign(&c4_nameCaptureInfo, sf_mex_createstruct("structure", 2, 170, 1),
                false);
  c4_info_helper(&c4_nameCaptureInfo);
  c4_b_info_helper(&c4_nameCaptureInfo);
  c4_c_info_helper(&c4_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c4_nameCaptureInfo);
  return c4_nameCaptureInfo;
}

static void c4_info_helper(const mxArray **c4_info)
{
  const mxArray *c4_rhs0 = NULL;
  const mxArray *c4_lhs0 = NULL;
  const mxArray *c4_rhs1 = NULL;
  const mxArray *c4_lhs1 = NULL;
  const mxArray *c4_rhs2 = NULL;
  const mxArray *c4_lhs2 = NULL;
  const mxArray *c4_rhs3 = NULL;
  const mxArray *c4_lhs3 = NULL;
  const mxArray *c4_rhs4 = NULL;
  const mxArray *c4_lhs4 = NULL;
  const mxArray *c4_rhs5 = NULL;
  const mxArray *c4_lhs5 = NULL;
  const mxArray *c4_rhs6 = NULL;
  const mxArray *c4_lhs6 = NULL;
  const mxArray *c4_rhs7 = NULL;
  const mxArray *c4_lhs7 = NULL;
  const mxArray *c4_rhs8 = NULL;
  const mxArray *c4_lhs8 = NULL;
  const mxArray *c4_rhs9 = NULL;
  const mxArray *c4_lhs9 = NULL;
  const mxArray *c4_rhs10 = NULL;
  const mxArray *c4_lhs10 = NULL;
  const mxArray *c4_rhs11 = NULL;
  const mxArray *c4_lhs11 = NULL;
  const mxArray *c4_rhs12 = NULL;
  const mxArray *c4_lhs12 = NULL;
  const mxArray *c4_rhs13 = NULL;
  const mxArray *c4_lhs13 = NULL;
  const mxArray *c4_rhs14 = NULL;
  const mxArray *c4_lhs14 = NULL;
  const mxArray *c4_rhs15 = NULL;
  const mxArray *c4_lhs15 = NULL;
  const mxArray *c4_rhs16 = NULL;
  const mxArray *c4_lhs16 = NULL;
  const mxArray *c4_rhs17 = NULL;
  const mxArray *c4_lhs17 = NULL;
  const mxArray *c4_rhs18 = NULL;
  const mxArray *c4_lhs18 = NULL;
  const mxArray *c4_rhs19 = NULL;
  const mxArray *c4_lhs19 = NULL;
  const mxArray *c4_rhs20 = NULL;
  const mxArray *c4_lhs20 = NULL;
  const mxArray *c4_rhs21 = NULL;
  const mxArray *c4_lhs21 = NULL;
  const mxArray *c4_rhs22 = NULL;
  const mxArray *c4_lhs22 = NULL;
  const mxArray *c4_rhs23 = NULL;
  const mxArray *c4_lhs23 = NULL;
  const mxArray *c4_rhs24 = NULL;
  const mxArray *c4_lhs24 = NULL;
  const mxArray *c4_rhs25 = NULL;
  const mxArray *c4_lhs25 = NULL;
  const mxArray *c4_rhs26 = NULL;
  const mxArray *c4_lhs26 = NULL;
  const mxArray *c4_rhs27 = NULL;
  const mxArray *c4_lhs27 = NULL;
  const mxArray *c4_rhs28 = NULL;
  const mxArray *c4_lhs28 = NULL;
  const mxArray *c4_rhs29 = NULL;
  const mxArray *c4_lhs29 = NULL;
  const mxArray *c4_rhs30 = NULL;
  const mxArray *c4_lhs30 = NULL;
  const mxArray *c4_rhs31 = NULL;
  const mxArray *c4_lhs31 = NULL;
  const mxArray *c4_rhs32 = NULL;
  const mxArray *c4_lhs32 = NULL;
  const mxArray *c4_rhs33 = NULL;
  const mxArray *c4_lhs33 = NULL;
  const mxArray *c4_rhs34 = NULL;
  const mxArray *c4_lhs34 = NULL;
  const mxArray *c4_rhs35 = NULL;
  const mxArray *c4_lhs35 = NULL;
  const mxArray *c4_rhs36 = NULL;
  const mxArray *c4_lhs36 = NULL;
  const mxArray *c4_rhs37 = NULL;
  const mxArray *c4_lhs37 = NULL;
  const mxArray *c4_rhs38 = NULL;
  const mxArray *c4_lhs38 = NULL;
  const mxArray *c4_rhs39 = NULL;
  const mxArray *c4_lhs39 = NULL;
  const mxArray *c4_rhs40 = NULL;
  const mxArray *c4_lhs40 = NULL;
  const mxArray *c4_rhs41 = NULL;
  const mxArray *c4_lhs41 = NULL;
  const mxArray *c4_rhs42 = NULL;
  const mxArray *c4_lhs42 = NULL;
  const mxArray *c4_rhs43 = NULL;
  const mxArray *c4_lhs43 = NULL;
  const mxArray *c4_rhs44 = NULL;
  const mxArray *c4_lhs44 = NULL;
  const mxArray *c4_rhs45 = NULL;
  const mxArray *c4_lhs45 = NULL;
  const mxArray *c4_rhs46 = NULL;
  const mxArray *c4_lhs46 = NULL;
  const mxArray *c4_rhs47 = NULL;
  const mxArray *c4_lhs47 = NULL;
  const mxArray *c4_rhs48 = NULL;
  const mxArray *c4_lhs48 = NULL;
  const mxArray *c4_rhs49 = NULL;
  const mxArray *c4_lhs49 = NULL;
  const mxArray *c4_rhs50 = NULL;
  const mxArray *c4_lhs50 = NULL;
  const mxArray *c4_rhs51 = NULL;
  const mxArray *c4_lhs51 = NULL;
  const mxArray *c4_rhs52 = NULL;
  const mxArray *c4_lhs52 = NULL;
  const mxArray *c4_rhs53 = NULL;
  const mxArray *c4_lhs53 = NULL;
  const mxArray *c4_rhs54 = NULL;
  const mxArray *c4_lhs54 = NULL;
  const mxArray *c4_rhs55 = NULL;
  const mxArray *c4_lhs55 = NULL;
  const mxArray *c4_rhs56 = NULL;
  const mxArray *c4_lhs56 = NULL;
  const mxArray *c4_rhs57 = NULL;
  const mxArray *c4_lhs57 = NULL;
  const mxArray *c4_rhs58 = NULL;
  const mxArray *c4_lhs58 = NULL;
  const mxArray *c4_rhs59 = NULL;
  const mxArray *c4_lhs59 = NULL;
  const mxArray *c4_rhs60 = NULL;
  const mxArray *c4_lhs60 = NULL;
  const mxArray *c4_rhs61 = NULL;
  const mxArray *c4_lhs61 = NULL;
  const mxArray *c4_rhs62 = NULL;
  const mxArray *c4_lhs62 = NULL;
  const mxArray *c4_rhs63 = NULL;
  const mxArray *c4_lhs63 = NULL;
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("error"), "name", "name", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/lang/error.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1319708366U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c4_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1383852094U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c4_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1395906656U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c4_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1323145378U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c4_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375959088U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c4_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c4_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 6);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_xgemm"), "name", "name", 6);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375959090U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c4_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 7);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c4_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 8);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.xgemm"),
                  "name", "name", 8);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c4_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 9);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 9);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c4_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!below_threshold"),
                  "context", "context", 10);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 10);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c4_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "context", "context", 11);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 11);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1393305658U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c4_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 12);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 12);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c4_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 13);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.refblas.xgemm"),
                  "name", "name", 13);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "resolved", "resolved", 13);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c4_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "context", "context", 14);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 14);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 14);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372561560U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c4_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "context", "context", 15);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 15);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 15);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c4_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "context", "context", 16);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexTimes"),
                  "name", "name", 16);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 16);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexTimes.m"),
                  "resolved", "resolved", 16);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372561560U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c4_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "context", "context", 17);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 17);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 17);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 17);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372561560U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c4_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "context", "context", 18);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 18);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 18);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1397235822U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c4_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 19);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfi"), "name", "name", 19);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 19);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 19);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346488758U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c4_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "context",
                  "context", 20);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 20);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 20);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1398853998U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c4_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 21);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("intmax"), "name", "name", 21);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 21);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1362236682U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c4_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "context",
                  "context", 22);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 22);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 22);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1393305658U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c4_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 23);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("intmin"), "name", "name", 23);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 23);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1362236682U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c4_rhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "context",
                  "context", 24);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 24);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 24);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1393305658U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c4_rhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "context", "context", 25);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 25);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 25);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 25);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372561560U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c4_rhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 26);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.int"),
                  "name", "name", 26);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 26);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/int.p"),
                  "resolved", "resolved", 26);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c4_rhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!ceval_xgemm"),
                  "context", "context", 27);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.size_ptr"),
                  "name", "name", 27);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 27);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/size_ptr.p"),
                  "resolved", "resolved", 27);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c4_rhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs27), "lhs", "lhs",
                  27);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!ceval_xgemm"),
                  "context", "context", 28);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.c_cast"),
                  "name", "name", 28);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("int32"), "dominantType",
                  "dominantType", 28);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/c_cast.p"),
                  "resolved", "resolved", 28);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 28);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 28);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 28);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 28);
  sf_mex_assign(&c4_rhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs28), "rhs", "rhs",
                  28);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs28), "lhs", "lhs",
                  28);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 29);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("mldivide"), "name", "name", 29);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 29);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mldivide.p"), "resolved",
                  "resolved", 29);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786048U), "fileTimeLo",
                  "fileTimeLo", 29);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 29);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1319708366U), "mFileTimeLo",
                  "mFileTimeLo", 29);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 29);
  sf_mex_assign(&c4_rhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs29), "rhs", "rhs",
                  29);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs29), "lhs", "lhs",
                  29);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mldivide.p"), "context",
                  "context", 30);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 30);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 30);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 30);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375959088U), "fileTimeLo",
                  "fileTimeLo", 30);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 30);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 30);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 30);
  sf_mex_assign(&c4_rhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs30), "rhs", "rhs",
                  30);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs30), "lhs", "lhs",
                  30);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mldivide.p"), "context",
                  "context", 31);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_lusolve"), "name", "name",
                  31);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 31);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m"), "resolved",
                  "resolved", 31);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1369988286U), "fileTimeLo",
                  "fileTimeLo", 31);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 31);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 31);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 31);
  sf_mex_assign(&c4_rhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs31), "rhs", "rhs",
                  31);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs31), "lhs", "lhs",
                  31);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolveNxN"),
                  "context", "context", 32);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_xgetrf"), "name", "name",
                  32);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 32);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m"),
                  "resolved", "resolved", 32);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286797206U), "fileTimeLo",
                  "fileTimeLo", 32);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 32);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 32);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 32);
  sf_mex_assign(&c4_rhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs32), "rhs", "rhs",
                  32);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs32), "lhs", "lhs",
                  32);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m"),
                  "context", "context", 33);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_lapack_xgetrf"), "name",
                  "name", 33);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 33);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m"),
                  "resolved", "resolved", 33);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286797210U), "fileTimeLo",
                  "fileTimeLo", 33);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 33);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 33);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 33);
  sf_mex_assign(&c4_rhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs33), "rhs", "rhs",
                  33);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs33), "lhs", "lhs",
                  33);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m"),
                  "context", "context", 34);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_matlab_zgetrf"), "name",
                  "name", 34);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 34);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "resolved", "resolved", 34);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1302667394U), "fileTimeLo",
                  "fileTimeLo", 34);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 34);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 34);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 34);
  sf_mex_assign(&c4_rhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs34), "rhs", "rhs",
                  34);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs34), "lhs", "lhs",
                  34);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 35);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("realmin"), "name", "name", 35);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 35);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m"), "resolved",
                  "resolved", 35);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1307629642U), "fileTimeLo",
                  "fileTimeLo", 35);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 35);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 35);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 35);
  sf_mex_assign(&c4_rhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs35), "rhs", "rhs",
                  35);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs35), "lhs", "lhs",
                  35);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m"), "context",
                  "context", 36);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_realmin"), "name", "name",
                  36);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 36);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m"), "resolved",
                  "resolved", 36);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1307629644U), "fileTimeLo",
                  "fileTimeLo", 36);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 36);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 36);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 36);
  sf_mex_assign(&c4_rhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs36), "rhs", "rhs",
                  36);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs36), "lhs", "lhs",
                  36);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m"), "context",
                  "context", 37);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 37);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 37);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 37);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1326702796U), "fileTimeLo",
                  "fileTimeLo", 37);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 37);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 37);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 37);
  sf_mex_assign(&c4_rhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs37), "rhs", "rhs",
                  37);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs37), "lhs", "lhs",
                  37);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 38);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eps"), "name", "name", 38);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 38);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "resolved",
                  "resolved", 38);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1326702796U), "fileTimeLo",
                  "fileTimeLo", 38);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 38);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 38);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 38);
  sf_mex_assign(&c4_rhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs38), "rhs", "rhs",
                  38);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs38), "lhs", "lhs",
                  38);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "context",
                  "context", 39);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_is_float_class"), "name",
                  "name", 39);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 39);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m"),
                  "resolved", "resolved", 39);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286797182U), "fileTimeLo",
                  "fileTimeLo", 39);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 39);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 39);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 39);
  sf_mex_assign(&c4_rhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs39), "rhs", "rhs",
                  39);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs39), "lhs", "lhs",
                  39);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "context",
                  "context", 40);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_eps"), "name", "name", 40);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 40);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m"), "resolved",
                  "resolved", 40);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1326702796U), "fileTimeLo",
                  "fileTimeLo", 40);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 40);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 40);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 40);
  sf_mex_assign(&c4_rhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs40), "rhs", "rhs",
                  40);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs40), "lhs", "lhs",
                  40);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m"), "context",
                  "context", 41);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 41);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 41);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 41);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1326702796U), "fileTimeLo",
                  "fileTimeLo", 41);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 41);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 41);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 41);
  sf_mex_assign(&c4_rhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs41), "rhs", "rhs",
                  41);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs41), "lhs", "lhs",
                  41);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 42);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("min"), "name", "name", 42);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 42);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 42);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1311233718U), "fileTimeLo",
                  "fileTimeLo", 42);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 42);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 42);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 42);
  sf_mex_assign(&c4_rhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs42), "rhs", "rhs",
                  42);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs42), "lhs", "lhs",
                  42);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "context",
                  "context", 43);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_min_or_max"), "name",
                  "name", 43);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 43);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m"),
                  "resolved", "resolved", 43);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378274384U), "fileTimeLo",
                  "fileTimeLo", 43);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 43);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 43);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 43);
  sf_mex_assign(&c4_rhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs43), "rhs", "rhs",
                  43);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs43), "lhs", "lhs",
                  43);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 44);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 44);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 44);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 44);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375959088U), "fileTimeLo",
                  "fileTimeLo", 44);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 44);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 44);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 44);
  sf_mex_assign(&c4_rhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs44), "rhs", "rhs",
                  44);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs44), "lhs", "lhs",
                  44);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 45);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 45);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 45);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 45);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 45);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 45);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 45);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 45);
  sf_mex_assign(&c4_rhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs45), "rhs", "rhs",
                  45);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs45), "lhs", "lhs",
                  45);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 46);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 46);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 46);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 46);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375959088U), "fileTimeLo",
                  "fileTimeLo", 46);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 46);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 46);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 46);
  sf_mex_assign(&c4_rhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs46), "rhs", "rhs",
                  46);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs46), "lhs", "lhs",
                  46);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 47);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 47);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 47);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 47);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 47);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 47);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 47);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 47);
  sf_mex_assign(&c4_rhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs47), "rhs", "rhs",
                  47);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs47), "lhs", "lhs",
                  47);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 48);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 48);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 48);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 48);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1323145378U), "fileTimeLo",
                  "fileTimeLo", 48);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 48);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 48);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 48);
  sf_mex_assign(&c4_rhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs48), "rhs", "rhs",
                  48);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs48), "lhs", "lhs",
                  48);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 49);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 49);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 49);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 49);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375959088U), "fileTimeLo",
                  "fileTimeLo", 49);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 49);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 49);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 49);
  sf_mex_assign(&c4_rhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs49), "rhs", "rhs",
                  49);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs49), "lhs", "lhs",
                  49);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 50);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 50);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 50);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 50);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1395906656U), "fileTimeLo",
                  "fileTimeLo", 50);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 50);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 50);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 50);
  sf_mex_assign(&c4_rhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs50), "rhs", "rhs",
                  50);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs50), "lhs", "lhs",
                  50);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 51);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("colon"), "name", "name", 51);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 51);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "resolved",
                  "resolved", 51);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378274388U), "fileTimeLo",
                  "fileTimeLo", 51);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 51);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 51);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 51);
  sf_mex_assign(&c4_rhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs51), "rhs", "rhs",
                  51);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs51), "lhs", "lhs",
                  51);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 52);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("colon"), "name", "name", 52);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 52);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "resolved",
                  "resolved", 52);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378274388U), "fileTimeLo",
                  "fileTimeLo", 52);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 52);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 52);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 52);
  sf_mex_assign(&c4_rhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs52), "rhs", "rhs",
                  52);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs52), "lhs", "lhs",
                  52);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 53);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 53);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 53);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 53);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1395906656U), "fileTimeLo",
                  "fileTimeLo", 53);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 53);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 53);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 53);
  sf_mex_assign(&c4_rhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs53), "rhs", "rhs",
                  53);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs53), "lhs", "lhs",
                  53);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 54);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 54);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 54);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 54);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1395906656U), "fileTimeLo",
                  "fileTimeLo", 54);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 54);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 54);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 54);
  sf_mex_assign(&c4_rhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs54), "rhs", "rhs",
                  54);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs54), "lhs", "lhs",
                  54);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 55);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("floor"), "name", "name", 55);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 55);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 55);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363688654U), "fileTimeLo",
                  "fileTimeLo", 55);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 55);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 55);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 55);
  sf_mex_assign(&c4_rhs55, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs55, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs55), "rhs", "rhs",
                  55);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs55), "lhs", "lhs",
                  55);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 56);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 56);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 56);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 56);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1395906656U), "fileTimeLo",
                  "fileTimeLo", 56);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 56);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 56);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 56);
  sf_mex_assign(&c4_rhs56, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs56, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs56), "rhs", "rhs",
                  56);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs56), "lhs", "lhs",
                  56);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 57);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 57);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 57);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 57);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286797126U), "fileTimeLo",
                  "fileTimeLo", 57);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 57);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 57);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 57);
  sf_mex_assign(&c4_rhs57, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs57, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs57), "rhs", "rhs",
                  57);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs57), "lhs", "lhs",
                  57);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange"),
                  "context", "context", 58);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("intmin"), "name", "name", 58);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 58);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 58);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1362236682U), "fileTimeLo",
                  "fileTimeLo", 58);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 58);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 58);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 58);
  sf_mex_assign(&c4_rhs58, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs58, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs58), "rhs", "rhs",
                  58);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs58), "lhs", "lhs",
                  58);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange"),
                  "context", "context", 59);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("intmax"), "name", "name", 59);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 59);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 59);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1362236682U), "fileTimeLo",
                  "fileTimeLo", 59);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 59);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 59);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 59);
  sf_mex_assign(&c4_rhs59, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs59, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs59), "rhs", "rhs",
                  59);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs59), "lhs", "lhs",
                  59);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 60);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("intmin"), "name", "name", 60);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 60);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 60);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1362236682U), "fileTimeLo",
                  "fileTimeLo", 60);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 60);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 60);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 60);
  sf_mex_assign(&c4_rhs60, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs60, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs60), "rhs", "rhs",
                  60);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs60), "lhs", "lhs",
                  60);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 61);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("intmax"), "name", "name", 61);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 61);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 61);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1362236682U), "fileTimeLo",
                  "fileTimeLo", 61);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 61);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 61);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 61);
  sf_mex_assign(&c4_rhs61, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs61, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs61), "rhs", "rhs",
                  61);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs61), "lhs", "lhs",
                  61);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 62);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_isa_uint"), "name", "name",
                  62);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 62);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "resolved",
                  "resolved", 62);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375959088U), "fileTimeLo",
                  "fileTimeLo", 62);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 62);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 62);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 62);
  sf_mex_assign(&c4_rhs62, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs62, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs62), "rhs", "rhs",
                  62);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs62), "lhs", "lhs",
                  62);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "context",
                  "context", 63);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.isaUint"),
                  "name", "name", 63);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 63);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/isaUint.p"),
                  "resolved", "resolved", 63);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 63);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 63);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 63);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 63);
  sf_mex_assign(&c4_rhs63, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs63, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs63), "rhs", "rhs",
                  63);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs63), "lhs", "lhs",
                  63);
  sf_mex_destroy(&c4_rhs0);
  sf_mex_destroy(&c4_lhs0);
  sf_mex_destroy(&c4_rhs1);
  sf_mex_destroy(&c4_lhs1);
  sf_mex_destroy(&c4_rhs2);
  sf_mex_destroy(&c4_lhs2);
  sf_mex_destroy(&c4_rhs3);
  sf_mex_destroy(&c4_lhs3);
  sf_mex_destroy(&c4_rhs4);
  sf_mex_destroy(&c4_lhs4);
  sf_mex_destroy(&c4_rhs5);
  sf_mex_destroy(&c4_lhs5);
  sf_mex_destroy(&c4_rhs6);
  sf_mex_destroy(&c4_lhs6);
  sf_mex_destroy(&c4_rhs7);
  sf_mex_destroy(&c4_lhs7);
  sf_mex_destroy(&c4_rhs8);
  sf_mex_destroy(&c4_lhs8);
  sf_mex_destroy(&c4_rhs9);
  sf_mex_destroy(&c4_lhs9);
  sf_mex_destroy(&c4_rhs10);
  sf_mex_destroy(&c4_lhs10);
  sf_mex_destroy(&c4_rhs11);
  sf_mex_destroy(&c4_lhs11);
  sf_mex_destroy(&c4_rhs12);
  sf_mex_destroy(&c4_lhs12);
  sf_mex_destroy(&c4_rhs13);
  sf_mex_destroy(&c4_lhs13);
  sf_mex_destroy(&c4_rhs14);
  sf_mex_destroy(&c4_lhs14);
  sf_mex_destroy(&c4_rhs15);
  sf_mex_destroy(&c4_lhs15);
  sf_mex_destroy(&c4_rhs16);
  sf_mex_destroy(&c4_lhs16);
  sf_mex_destroy(&c4_rhs17);
  sf_mex_destroy(&c4_lhs17);
  sf_mex_destroy(&c4_rhs18);
  sf_mex_destroy(&c4_lhs18);
  sf_mex_destroy(&c4_rhs19);
  sf_mex_destroy(&c4_lhs19);
  sf_mex_destroy(&c4_rhs20);
  sf_mex_destroy(&c4_lhs20);
  sf_mex_destroy(&c4_rhs21);
  sf_mex_destroy(&c4_lhs21);
  sf_mex_destroy(&c4_rhs22);
  sf_mex_destroy(&c4_lhs22);
  sf_mex_destroy(&c4_rhs23);
  sf_mex_destroy(&c4_lhs23);
  sf_mex_destroy(&c4_rhs24);
  sf_mex_destroy(&c4_lhs24);
  sf_mex_destroy(&c4_rhs25);
  sf_mex_destroy(&c4_lhs25);
  sf_mex_destroy(&c4_rhs26);
  sf_mex_destroy(&c4_lhs26);
  sf_mex_destroy(&c4_rhs27);
  sf_mex_destroy(&c4_lhs27);
  sf_mex_destroy(&c4_rhs28);
  sf_mex_destroy(&c4_lhs28);
  sf_mex_destroy(&c4_rhs29);
  sf_mex_destroy(&c4_lhs29);
  sf_mex_destroy(&c4_rhs30);
  sf_mex_destroy(&c4_lhs30);
  sf_mex_destroy(&c4_rhs31);
  sf_mex_destroy(&c4_lhs31);
  sf_mex_destroy(&c4_rhs32);
  sf_mex_destroy(&c4_lhs32);
  sf_mex_destroy(&c4_rhs33);
  sf_mex_destroy(&c4_lhs33);
  sf_mex_destroy(&c4_rhs34);
  sf_mex_destroy(&c4_lhs34);
  sf_mex_destroy(&c4_rhs35);
  sf_mex_destroy(&c4_lhs35);
  sf_mex_destroy(&c4_rhs36);
  sf_mex_destroy(&c4_lhs36);
  sf_mex_destroy(&c4_rhs37);
  sf_mex_destroy(&c4_lhs37);
  sf_mex_destroy(&c4_rhs38);
  sf_mex_destroy(&c4_lhs38);
  sf_mex_destroy(&c4_rhs39);
  sf_mex_destroy(&c4_lhs39);
  sf_mex_destroy(&c4_rhs40);
  sf_mex_destroy(&c4_lhs40);
  sf_mex_destroy(&c4_rhs41);
  sf_mex_destroy(&c4_lhs41);
  sf_mex_destroy(&c4_rhs42);
  sf_mex_destroy(&c4_lhs42);
  sf_mex_destroy(&c4_rhs43);
  sf_mex_destroy(&c4_lhs43);
  sf_mex_destroy(&c4_rhs44);
  sf_mex_destroy(&c4_lhs44);
  sf_mex_destroy(&c4_rhs45);
  sf_mex_destroy(&c4_lhs45);
  sf_mex_destroy(&c4_rhs46);
  sf_mex_destroy(&c4_lhs46);
  sf_mex_destroy(&c4_rhs47);
  sf_mex_destroy(&c4_lhs47);
  sf_mex_destroy(&c4_rhs48);
  sf_mex_destroy(&c4_lhs48);
  sf_mex_destroy(&c4_rhs49);
  sf_mex_destroy(&c4_lhs49);
  sf_mex_destroy(&c4_rhs50);
  sf_mex_destroy(&c4_lhs50);
  sf_mex_destroy(&c4_rhs51);
  sf_mex_destroy(&c4_lhs51);
  sf_mex_destroy(&c4_rhs52);
  sf_mex_destroy(&c4_lhs52);
  sf_mex_destroy(&c4_rhs53);
  sf_mex_destroy(&c4_lhs53);
  sf_mex_destroy(&c4_rhs54);
  sf_mex_destroy(&c4_lhs54);
  sf_mex_destroy(&c4_rhs55);
  sf_mex_destroy(&c4_lhs55);
  sf_mex_destroy(&c4_rhs56);
  sf_mex_destroy(&c4_lhs56);
  sf_mex_destroy(&c4_rhs57);
  sf_mex_destroy(&c4_lhs57);
  sf_mex_destroy(&c4_rhs58);
  sf_mex_destroy(&c4_lhs58);
  sf_mex_destroy(&c4_rhs59);
  sf_mex_destroy(&c4_lhs59);
  sf_mex_destroy(&c4_rhs60);
  sf_mex_destroy(&c4_lhs60);
  sf_mex_destroy(&c4_rhs61);
  sf_mex_destroy(&c4_lhs61);
  sf_mex_destroy(&c4_rhs62);
  sf_mex_destroy(&c4_lhs62);
  sf_mex_destroy(&c4_rhs63);
  sf_mex_destroy(&c4_lhs63);
}

static const mxArray *c4_emlrt_marshallOut(const char * c4_u)
{
  const mxArray *c4_y = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c4_u)), false);
  return c4_y;
}

static const mxArray *c4_b_emlrt_marshallOut(const uint32_T c4_u)
{
  const mxArray *c4_y = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 7, 0U, 0U, 0U, 0), false);
  return c4_y;
}

static void c4_b_info_helper(const mxArray **c4_info)
{
  const mxArray *c4_rhs64 = NULL;
  const mxArray *c4_lhs64 = NULL;
  const mxArray *c4_rhs65 = NULL;
  const mxArray *c4_lhs65 = NULL;
  const mxArray *c4_rhs66 = NULL;
  const mxArray *c4_lhs66 = NULL;
  const mxArray *c4_rhs67 = NULL;
  const mxArray *c4_lhs67 = NULL;
  const mxArray *c4_rhs68 = NULL;
  const mxArray *c4_lhs68 = NULL;
  const mxArray *c4_rhs69 = NULL;
  const mxArray *c4_lhs69 = NULL;
  const mxArray *c4_rhs70 = NULL;
  const mxArray *c4_lhs70 = NULL;
  const mxArray *c4_rhs71 = NULL;
  const mxArray *c4_lhs71 = NULL;
  const mxArray *c4_rhs72 = NULL;
  const mxArray *c4_lhs72 = NULL;
  const mxArray *c4_rhs73 = NULL;
  const mxArray *c4_lhs73 = NULL;
  const mxArray *c4_rhs74 = NULL;
  const mxArray *c4_lhs74 = NULL;
  const mxArray *c4_rhs75 = NULL;
  const mxArray *c4_lhs75 = NULL;
  const mxArray *c4_rhs76 = NULL;
  const mxArray *c4_lhs76 = NULL;
  const mxArray *c4_rhs77 = NULL;
  const mxArray *c4_lhs77 = NULL;
  const mxArray *c4_rhs78 = NULL;
  const mxArray *c4_lhs78 = NULL;
  const mxArray *c4_rhs79 = NULL;
  const mxArray *c4_lhs79 = NULL;
  const mxArray *c4_rhs80 = NULL;
  const mxArray *c4_lhs80 = NULL;
  const mxArray *c4_rhs81 = NULL;
  const mxArray *c4_lhs81 = NULL;
  const mxArray *c4_rhs82 = NULL;
  const mxArray *c4_lhs82 = NULL;
  const mxArray *c4_rhs83 = NULL;
  const mxArray *c4_lhs83 = NULL;
  const mxArray *c4_rhs84 = NULL;
  const mxArray *c4_lhs84 = NULL;
  const mxArray *c4_rhs85 = NULL;
  const mxArray *c4_lhs85 = NULL;
  const mxArray *c4_rhs86 = NULL;
  const mxArray *c4_lhs86 = NULL;
  const mxArray *c4_rhs87 = NULL;
  const mxArray *c4_lhs87 = NULL;
  const mxArray *c4_rhs88 = NULL;
  const mxArray *c4_lhs88 = NULL;
  const mxArray *c4_rhs89 = NULL;
  const mxArray *c4_lhs89 = NULL;
  const mxArray *c4_rhs90 = NULL;
  const mxArray *c4_lhs90 = NULL;
  const mxArray *c4_rhs91 = NULL;
  const mxArray *c4_lhs91 = NULL;
  const mxArray *c4_rhs92 = NULL;
  const mxArray *c4_lhs92 = NULL;
  const mxArray *c4_rhs93 = NULL;
  const mxArray *c4_lhs93 = NULL;
  const mxArray *c4_rhs94 = NULL;
  const mxArray *c4_lhs94 = NULL;
  const mxArray *c4_rhs95 = NULL;
  const mxArray *c4_lhs95 = NULL;
  const mxArray *c4_rhs96 = NULL;
  const mxArray *c4_lhs96 = NULL;
  const mxArray *c4_rhs97 = NULL;
  const mxArray *c4_lhs97 = NULL;
  const mxArray *c4_rhs98 = NULL;
  const mxArray *c4_lhs98 = NULL;
  const mxArray *c4_rhs99 = NULL;
  const mxArray *c4_lhs99 = NULL;
  const mxArray *c4_rhs100 = NULL;
  const mxArray *c4_lhs100 = NULL;
  const mxArray *c4_rhs101 = NULL;
  const mxArray *c4_lhs101 = NULL;
  const mxArray *c4_rhs102 = NULL;
  const mxArray *c4_lhs102 = NULL;
  const mxArray *c4_rhs103 = NULL;
  const mxArray *c4_lhs103 = NULL;
  const mxArray *c4_rhs104 = NULL;
  const mxArray *c4_lhs104 = NULL;
  const mxArray *c4_rhs105 = NULL;
  const mxArray *c4_lhs105 = NULL;
  const mxArray *c4_rhs106 = NULL;
  const mxArray *c4_lhs106 = NULL;
  const mxArray *c4_rhs107 = NULL;
  const mxArray *c4_lhs107 = NULL;
  const mxArray *c4_rhs108 = NULL;
  const mxArray *c4_lhs108 = NULL;
  const mxArray *c4_rhs109 = NULL;
  const mxArray *c4_lhs109 = NULL;
  const mxArray *c4_rhs110 = NULL;
  const mxArray *c4_lhs110 = NULL;
  const mxArray *c4_rhs111 = NULL;
  const mxArray *c4_lhs111 = NULL;
  const mxArray *c4_rhs112 = NULL;
  const mxArray *c4_lhs112 = NULL;
  const mxArray *c4_rhs113 = NULL;
  const mxArray *c4_lhs113 = NULL;
  const mxArray *c4_rhs114 = NULL;
  const mxArray *c4_lhs114 = NULL;
  const mxArray *c4_rhs115 = NULL;
  const mxArray *c4_lhs115 = NULL;
  const mxArray *c4_rhs116 = NULL;
  const mxArray *c4_lhs116 = NULL;
  const mxArray *c4_rhs117 = NULL;
  const mxArray *c4_lhs117 = NULL;
  const mxArray *c4_rhs118 = NULL;
  const mxArray *c4_lhs118 = NULL;
  const mxArray *c4_rhs119 = NULL;
  const mxArray *c4_lhs119 = NULL;
  const mxArray *c4_rhs120 = NULL;
  const mxArray *c4_lhs120 = NULL;
  const mxArray *c4_rhs121 = NULL;
  const mxArray *c4_lhs121 = NULL;
  const mxArray *c4_rhs122 = NULL;
  const mxArray *c4_lhs122 = NULL;
  const mxArray *c4_rhs123 = NULL;
  const mxArray *c4_lhs123 = NULL;
  const mxArray *c4_rhs124 = NULL;
  const mxArray *c4_lhs124 = NULL;
  const mxArray *c4_rhs125 = NULL;
  const mxArray *c4_lhs125 = NULL;
  const mxArray *c4_rhs126 = NULL;
  const mxArray *c4_lhs126 = NULL;
  const mxArray *c4_rhs127 = NULL;
  const mxArray *c4_lhs127 = NULL;
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 64);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_unsigned_class"), "name",
                  "name", 64);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 64);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m"),
                  "resolved", "resolved", 64);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375959088U), "fileTimeLo",
                  "fileTimeLo", 64);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 64);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 64);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 64);
  sf_mex_assign(&c4_rhs64, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs64, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs64), "rhs", "rhs",
                  64);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs64), "lhs", "lhs",
                  64);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m"),
                  "context", "context", 65);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.unsignedClass"),
                  "name", "name", 65);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 65);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/unsignedClass.p"),
                  "resolved", "resolved", 65);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 65);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 65);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 65);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 65);
  sf_mex_assign(&c4_rhs65, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs65, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs65), "rhs", "rhs",
                  65);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs65), "lhs", "lhs",
                  65);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/unsignedClass.p"),
                  "context", "context", 66);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 66);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 66);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 66);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1393305658U), "fileTimeLo",
                  "fileTimeLo", 66);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 66);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 66);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 66);
  sf_mex_assign(&c4_rhs66, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs66, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs66), "rhs", "rhs",
                  66);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs66), "lhs", "lhs",
                  66);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/unsignedClass.p"),
                  "context", "context", 67);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 67);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 67);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 67);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1323145378U), "fileTimeLo",
                  "fileTimeLo", 67);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 67);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 67);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 67);
  sf_mex_assign(&c4_rhs67, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs67, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs67), "rhs", "rhs",
                  67);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs67), "lhs", "lhs",
                  67);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 68);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 68);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 68);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 68);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1323145378U), "fileTimeLo",
                  "fileTimeLo", 68);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 68);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 68);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 68);
  sf_mex_assign(&c4_rhs68, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs68, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs68), "rhs", "rhs",
                  68);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs68), "lhs", "lhs",
                  68);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 69);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("intmax"), "name", "name", 69);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 69);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 69);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1362236682U), "fileTimeLo",
                  "fileTimeLo", 69);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 69);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 69);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 69);
  sf_mex_assign(&c4_rhs69, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs69, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs69), "rhs", "rhs",
                  69);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs69), "lhs", "lhs",
                  69);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 70);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_isa_uint"), "name", "name",
                  70);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 70);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "resolved",
                  "resolved", 70);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375959088U), "fileTimeLo",
                  "fileTimeLo", 70);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 70);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 70);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 70);
  sf_mex_assign(&c4_rhs70, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs70, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs70), "rhs", "rhs",
                  70);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs70), "lhs", "lhs",
                  70);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 71);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 71);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 71);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 71);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372560816U), "fileTimeLo",
                  "fileTimeLo", 71);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 71);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 71);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 71);
  sf_mex_assign(&c4_rhs71, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs71, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs71), "rhs", "rhs",
                  71);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs71), "lhs", "lhs",
                  71);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"), "context",
                  "context", 72);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 72);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 72);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 72);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372561560U), "fileTimeLo",
                  "fileTimeLo", 72);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 72);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 72);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 72);
  sf_mex_assign(&c4_rhs72, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs72, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs72), "rhs", "rhs",
                  72);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs72), "lhs", "lhs",
                  72);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_signed_integer_colon"),
                  "context", "context", 73);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 73);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 73);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 73);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1397235822U), "fileTimeLo",
                  "fileTimeLo", 73);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 73);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 73);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 73);
  sf_mex_assign(&c4_rhs73, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs73, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs73), "rhs", "rhs",
                  73);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs73), "lhs", "lhs",
                  73);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 74);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 74);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 74);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 74);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1323145378U), "fileTimeLo",
                  "fileTimeLo", 74);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 74);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 74);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 74);
  sf_mex_assign(&c4_rhs74, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs74, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs74), "rhs", "rhs",
                  74);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs74), "lhs", "lhs",
                  74);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 75);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 75);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 75);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 75);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372560816U), "fileTimeLo",
                  "fileTimeLo", 75);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 75);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 75);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 75);
  sf_mex_assign(&c4_rhs75, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs75, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs75), "rhs", "rhs",
                  75);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs75), "lhs", "lhs",
                  75);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 76);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 76);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 76);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 76);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1397235822U), "fileTimeLo",
                  "fileTimeLo", 76);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 76);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 76);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 76);
  sf_mex_assign(&c4_rhs76, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs76, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs76), "rhs", "rhs",
                  76);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs76), "lhs", "lhs",
                  76);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 77);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 77);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 77);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 77);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372560816U), "fileTimeLo",
                  "fileTimeLo", 77);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 77);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 77);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 77);
  sf_mex_assign(&c4_rhs77, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs77, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs77), "rhs", "rhs",
                  77);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs77), "lhs", "lhs",
                  77);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "context", "context", 78);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 78);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 78);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 78);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372561560U), "fileTimeLo",
                  "fileTimeLo", 78);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 78);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 78);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 78);
  sf_mex_assign(&c4_rhs78, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs78, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs78), "rhs", "rhs",
                  78);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs78), "lhs", "lhs",
                  78);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 79);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 79);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 79);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 79);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372560816U), "fileTimeLo",
                  "fileTimeLo", 79);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 79);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 79);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 79);
  sf_mex_assign(&c4_rhs79, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs79, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs79), "rhs", "rhs",
                  79);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs79), "lhs", "lhs",
                  79);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "context", "context", 80);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 80);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 80);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 80);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372561560U), "fileTimeLo",
                  "fileTimeLo", 80);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 80);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 80);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 80);
  sf_mex_assign(&c4_rhs80, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs80, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs80), "rhs", "rhs",
                  80);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs80), "lhs", "lhs",
                  80);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 81);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_index_times"), "name",
                  "name", 81);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 81);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "resolved", "resolved", 81);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372560816U), "fileTimeLo",
                  "fileTimeLo", 81);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 81);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 81);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 81);
  sf_mex_assign(&c4_rhs81, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs81, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs81), "rhs", "rhs",
                  81);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs81), "lhs", "lhs",
                  81);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "context", "context", 82);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexTimes"),
                  "name", "name", 82);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 82);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexTimes.m"),
                  "resolved", "resolved", 82);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372561560U), "fileTimeLo",
                  "fileTimeLo", 82);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 82);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 82);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 82);
  sf_mex_assign(&c4_rhs82, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs82, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs82), "rhs", "rhs",
                  82);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs82), "lhs", "lhs",
                  82);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 83);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 83);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 83);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 83);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372560816U), "fileTimeLo",
                  "fileTimeLo", 83);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 83);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 83);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 83);
  sf_mex_assign(&c4_rhs83, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs83, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs83), "rhs", "rhs",
                  83);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs83), "lhs", "lhs",
                  83);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"), "context",
                  "context", 84);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 84);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 84);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 84);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372561560U), "fileTimeLo",
                  "fileTimeLo", 84);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 84);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 84);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 84);
  sf_mex_assign(&c4_rhs84, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs84, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs84), "rhs", "rhs",
                  84);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs84), "lhs", "lhs",
                  84);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 85);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_ixamax"), "name", "name",
                  85);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 85);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m"),
                  "resolved", "resolved", 85);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375959088U), "fileTimeLo",
                  "fileTimeLo", 85);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 85);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 85);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 85);
  sf_mex_assign(&c4_rhs85, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs85, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs85), "rhs", "rhs",
                  85);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs85), "lhs", "lhs",
                  85);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m"),
                  "context", "context", 86);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 86);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 86);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 86);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 86);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 86);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 86);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 86);
  sf_mex_assign(&c4_rhs86, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs86, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs86), "rhs", "rhs",
                  86);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs86), "lhs", "lhs",
                  86);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m"),
                  "context", "context", 87);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.ixamax"),
                  "name", "name", 87);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 87);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/ixamax.p"),
                  "resolved", "resolved", 87);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 87);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 87);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 87);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 87);
  sf_mex_assign(&c4_rhs87, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs87, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs87), "rhs", "rhs",
                  87);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs87), "lhs", "lhs",
                  87);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/ixamax.p"),
                  "context", "context", 88);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 88);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 88);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 88);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 88);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 88);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 88);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 88);
  sf_mex_assign(&c4_rhs88, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs88, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs88), "rhs", "rhs",
                  88);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs88), "lhs", "lhs",
                  88);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/ixamax.p!below_threshold"),
                  "context", "context", 89);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 89);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 89);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 89);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 89);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 89);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 89);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 89);
  sf_mex_assign(&c4_rhs89, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs89, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs89), "rhs", "rhs",
                  89);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs89), "lhs", "lhs",
                  89);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/ixamax.p!below_threshold"),
                  "context", "context", 90);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("length"), "name", "name", 90);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 90);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 90);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1303124606U), "fileTimeLo",
                  "fileTimeLo", 90);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 90);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 90);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 90);
  sf_mex_assign(&c4_rhs90, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs90, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs90), "rhs", "rhs",
                  90);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs90), "lhs", "lhs",
                  90);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m!intlength"),
                  "context", "context", 91);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 91);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 91);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 91);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1323145378U), "fileTimeLo",
                  "fileTimeLo", 91);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 91);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 91);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 91);
  sf_mex_assign(&c4_rhs91, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs91, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs91), "rhs", "rhs",
                  91);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs91), "lhs", "lhs",
                  91);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/ixamax.p"),
                  "context", "context", 92);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.refblas.ixamax"),
                  "name", "name", 92);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 92);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/ixamax.p"),
                  "resolved", "resolved", 92);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 92);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 92);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 92);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 92);
  sf_mex_assign(&c4_rhs92, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs92, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs92), "rhs", "rhs",
                  92);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs92), "lhs", "lhs",
                  92);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/ixamax.p"),
                  "context", "context", 93);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.refblas.xcabs1"),
                  "name", "name", 93);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 93);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xcabs1.p"),
                  "resolved", "resolved", 93);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 93);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 93);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 93);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 93);
  sf_mex_assign(&c4_rhs93, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs93, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs93), "rhs", "rhs",
                  93);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs93), "lhs", "lhs",
                  93);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xcabs1.p"),
                  "context", "context", 94);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("abs"), "name", "name", 94);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 94);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 94);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363688652U), "fileTimeLo",
                  "fileTimeLo", 94);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 94);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 94);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 94);
  sf_mex_assign(&c4_rhs94, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs94, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs94), "rhs", "rhs",
                  94);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs94), "lhs", "lhs",
                  94);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 95);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 95);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 95);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 95);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1395906656U), "fileTimeLo",
                  "fileTimeLo", 95);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 95);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 95);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 95);
  sf_mex_assign(&c4_rhs95, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs95, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs95), "rhs", "rhs",
                  95);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs95), "lhs", "lhs",
                  95);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 96);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_abs"), "name",
                  "name", 96);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 96);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m"),
                  "resolved", "resolved", 96);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286797112U), "fileTimeLo",
                  "fileTimeLo", 96);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 96);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 96);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 96);
  sf_mex_assign(&c4_rhs96, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs96, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs96), "rhs", "rhs",
                  96);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs96), "lhs", "lhs",
                  96);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/ixamax.p"),
                  "context", "context", 97);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 97);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 97);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 97);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1397235822U), "fileTimeLo",
                  "fileTimeLo", 97);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 97);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 97);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 97);
  sf_mex_assign(&c4_rhs97, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs97, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs97), "rhs", "rhs",
                  97);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs97), "lhs", "lhs",
                  97);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/ixamax.p"),
                  "context", "context", 98);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 98);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 98);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 98);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372561560U), "fileTimeLo",
                  "fileTimeLo", 98);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 98);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 98);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 98);
  sf_mex_assign(&c4_rhs98, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs98, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs98), "rhs", "rhs",
                  98);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs98), "lhs", "lhs",
                  98);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 99);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_xswap"), "name", "name",
                  99);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 99);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m"),
                  "resolved", "resolved", 99);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375959092U), "fileTimeLo",
                  "fileTimeLo", 99);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 99);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 99);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 99);
  sf_mex_assign(&c4_rhs99, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs99, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs99), "rhs", "rhs",
                  99);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs99), "lhs", "lhs",
                  99);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m"), "context",
                  "context", 100);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 100);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 100);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 100);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 100);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 100);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 100);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 100);
  sf_mex_assign(&c4_rhs100, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs100, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs100), "rhs", "rhs",
                  100);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs100), "lhs", "lhs",
                  100);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m"), "context",
                  "context", 101);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.xswap"),
                  "name", "name", 101);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 101);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xswap.p"),
                  "resolved", "resolved", 101);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 101);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 101);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 101);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 101);
  sf_mex_assign(&c4_rhs101, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs101, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs101), "rhs", "rhs",
                  101);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs101), "lhs", "lhs",
                  101);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xswap.p"),
                  "context", "context", 102);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 102);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 102);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 102);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 102);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 102);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 102);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 102);
  sf_mex_assign(&c4_rhs102, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs102, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs102), "rhs", "rhs",
                  102);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs102), "lhs", "lhs",
                  102);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xswap.p!below_threshold"),
                  "context", "context", 103);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 103);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 103);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 103);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 103);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 103);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 103);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 103);
  sf_mex_assign(&c4_rhs103, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs103, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs103), "rhs", "rhs",
                  103);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs103), "lhs", "lhs",
                  103);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xswap.p"),
                  "context", "context", 104);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.refblas.xswap"),
                  "name", "name", 104);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 104);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xswap.p"),
                  "resolved", "resolved", 104);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 104);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 104);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 104);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 104);
  sf_mex_assign(&c4_rhs104, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs104, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs104), "rhs", "rhs",
                  104);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs104), "lhs", "lhs",
                  104);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xswap.p"),
                  "context", "context", 105);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("abs"), "name", "name", 105);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 105);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 105);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363688652U), "fileTimeLo",
                  "fileTimeLo", 105);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 105);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 105);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 105);
  sf_mex_assign(&c4_rhs105, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs105, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs105), "rhs", "rhs",
                  105);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs105), "lhs", "lhs",
                  105);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 106);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 106);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 106);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 106);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1395906656U), "fileTimeLo",
                  "fileTimeLo", 106);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 106);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 106);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 106);
  sf_mex_assign(&c4_rhs106, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs106, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs106), "rhs", "rhs",
                  106);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs106), "lhs", "lhs",
                  106);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 107);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_abs"), "name",
                  "name", 107);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 107);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m"),
                  "resolved", "resolved", 107);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286797112U), "fileTimeLo",
                  "fileTimeLo", 107);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 107);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 107);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 107);
  sf_mex_assign(&c4_rhs107, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs107, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs107), "rhs", "rhs",
                  107);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs107), "lhs", "lhs",
                  107);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xswap.p"),
                  "context", "context", 108);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 108);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 108);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 108);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1397235822U), "fileTimeLo",
                  "fileTimeLo", 108);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 108);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 108);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 108);
  sf_mex_assign(&c4_rhs108, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs108, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs108), "rhs", "rhs",
                  108);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs108), "lhs", "lhs",
                  108);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xswap.p"),
                  "context", "context", 109);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 109);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 109);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 109);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372561560U), "fileTimeLo",
                  "fileTimeLo", 109);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 109);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 109);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 109);
  sf_mex_assign(&c4_rhs109, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs109, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs109), "rhs", "rhs",
                  109);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs109), "lhs", "lhs",
                  109);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 110);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_div"), "name", "name", 110);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 110);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 110);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1386398752U), "fileTimeLo",
                  "fileTimeLo", 110);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 110);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 110);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 110);
  sf_mex_assign(&c4_rhs110, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs110, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs110), "rhs", "rhs",
                  110);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs110), "lhs", "lhs",
                  110);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "context",
                  "context", 111);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.div"), "name",
                  "name", 111);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 111);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p"), "resolved",
                  "resolved", 111);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 111);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 111);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 111);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 111);
  sf_mex_assign(&c4_rhs111, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs111, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs111), "rhs", "rhs",
                  111);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs111), "lhs", "lhs",
                  111);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 112);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_xgeru"), "name", "name",
                  112);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 112);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m"),
                  "resolved", "resolved", 112);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375959090U), "fileTimeLo",
                  "fileTimeLo", 112);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 112);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 112);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 112);
  sf_mex_assign(&c4_rhs112, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs112, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs112), "rhs", "rhs",
                  112);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs112), "lhs", "lhs",
                  112);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m"), "context",
                  "context", 113);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 113);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 113);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 113);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 113);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 113);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 113);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 113);
  sf_mex_assign(&c4_rhs113, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs113, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs113), "rhs", "rhs",
                  113);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs113), "lhs", "lhs",
                  113);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m"), "context",
                  "context", 114);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.xgeru"),
                  "name", "name", 114);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 114);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgeru.p"),
                  "resolved", "resolved", 114);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 114);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 114);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 114);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 114);
  sf_mex_assign(&c4_rhs114, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs114, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs114), "rhs", "rhs",
                  114);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs114), "lhs", "lhs",
                  114);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgeru.p"),
                  "context", "context", 115);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.xger"),
                  "name", "name", 115);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 115);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p"),
                  "resolved", "resolved", 115);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 115);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 115);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 115);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 115);
  sf_mex_assign(&c4_rhs115, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs115, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs115), "rhs", "rhs",
                  115);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs115), "lhs", "lhs",
                  115);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p"),
                  "context", "context", 116);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 116);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 116);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 116);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 116);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 116);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 116);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 116);
  sf_mex_assign(&c4_rhs116, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs116, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs116), "rhs", "rhs",
                  116);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs116), "lhs", "lhs",
                  116);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p!below_threshold"),
                  "context", "context", 117);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 117);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 117);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 117);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 117);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 117);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 117);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 117);
  sf_mex_assign(&c4_rhs117, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs117, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs117), "rhs", "rhs",
                  117);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs117), "lhs", "lhs",
                  117);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p!below_threshold"),
                  "context", "context", 118);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.int"),
                  "name", "name", 118);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 118);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/int.p"),
                  "resolved", "resolved", 118);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 118);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 118);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 118);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 118);
  sf_mex_assign(&c4_rhs118, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs118, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs118), "rhs", "rhs",
                  118);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs118), "lhs", "lhs",
                  118);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p!below_threshold"),
                  "context", "context", 119);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("intmax"), "name", "name", 119);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 119);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 119);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1362236682U), "fileTimeLo",
                  "fileTimeLo", 119);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 119);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 119);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 119);
  sf_mex_assign(&c4_rhs119, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs119, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs119), "rhs", "rhs",
                  119);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs119), "lhs", "lhs",
                  119);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p!below_threshold"),
                  "context", "context", 120);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("min"), "name", "name", 120);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 120);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 120);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1311233718U), "fileTimeLo",
                  "fileTimeLo", 120);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 120);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 120);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 120);
  sf_mex_assign(&c4_rhs120, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs120, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs120), "rhs", "rhs",
                  120);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs120), "lhs", "lhs",
                  120);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 121);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 121);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 121);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 121);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375959088U), "fileTimeLo",
                  "fileTimeLo", 121);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 121);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 121);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 121);
  sf_mex_assign(&c4_rhs121, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs121, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs121), "rhs", "rhs",
                  121);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs121), "lhs", "lhs",
                  121);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 122);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 122);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 122);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 122);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375959088U), "fileTimeLo",
                  "fileTimeLo", 122);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 122);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 122);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 122);
  sf_mex_assign(&c4_rhs122, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs122, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs122), "rhs", "rhs",
                  122);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs122), "lhs", "lhs",
                  122);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 123);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 123);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 123);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 123);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 123);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 123);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 123);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 123);
  sf_mex_assign(&c4_rhs123, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs123, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs123), "rhs", "rhs",
                  123);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs123), "lhs", "lhs",
                  123);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 124);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 124);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 124);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 124);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375959088U), "fileTimeLo",
                  "fileTimeLo", 124);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 124);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 124);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 124);
  sf_mex_assign(&c4_rhs124, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs124, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs124), "rhs", "rhs",
                  124);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs124), "lhs", "lhs",
                  124);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 125);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 125);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 125);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 125);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1395906656U), "fileTimeLo",
                  "fileTimeLo", 125);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 125);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 125);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 125);
  sf_mex_assign(&c4_rhs125, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs125, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs125), "rhs", "rhs",
                  125);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs125), "lhs", "lhs",
                  125);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p"),
                  "context", "context", 126);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.refblas.xger"),
                  "name", "name", 126);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 126);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xger.p"),
                  "resolved", "resolved", 126);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 126);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 126);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 126);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 126);
  sf_mex_assign(&c4_rhs126, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs126, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs126), "rhs", "rhs",
                  126);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs126), "lhs", "lhs",
                  126);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xger.p"),
                  "context", "context", 127);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.refblas.xgerx"),
                  "name", "name", 127);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 127);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "resolved", "resolved", 127);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 127);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 127);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 127);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 127);
  sf_mex_assign(&c4_rhs127, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs127, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs127), "rhs", "rhs",
                  127);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs127), "lhs", "lhs",
                  127);
  sf_mex_destroy(&c4_rhs64);
  sf_mex_destroy(&c4_lhs64);
  sf_mex_destroy(&c4_rhs65);
  sf_mex_destroy(&c4_lhs65);
  sf_mex_destroy(&c4_rhs66);
  sf_mex_destroy(&c4_lhs66);
  sf_mex_destroy(&c4_rhs67);
  sf_mex_destroy(&c4_lhs67);
  sf_mex_destroy(&c4_rhs68);
  sf_mex_destroy(&c4_lhs68);
  sf_mex_destroy(&c4_rhs69);
  sf_mex_destroy(&c4_lhs69);
  sf_mex_destroy(&c4_rhs70);
  sf_mex_destroy(&c4_lhs70);
  sf_mex_destroy(&c4_rhs71);
  sf_mex_destroy(&c4_lhs71);
  sf_mex_destroy(&c4_rhs72);
  sf_mex_destroy(&c4_lhs72);
  sf_mex_destroy(&c4_rhs73);
  sf_mex_destroy(&c4_lhs73);
  sf_mex_destroy(&c4_rhs74);
  sf_mex_destroy(&c4_lhs74);
  sf_mex_destroy(&c4_rhs75);
  sf_mex_destroy(&c4_lhs75);
  sf_mex_destroy(&c4_rhs76);
  sf_mex_destroy(&c4_lhs76);
  sf_mex_destroy(&c4_rhs77);
  sf_mex_destroy(&c4_lhs77);
  sf_mex_destroy(&c4_rhs78);
  sf_mex_destroy(&c4_lhs78);
  sf_mex_destroy(&c4_rhs79);
  sf_mex_destroy(&c4_lhs79);
  sf_mex_destroy(&c4_rhs80);
  sf_mex_destroy(&c4_lhs80);
  sf_mex_destroy(&c4_rhs81);
  sf_mex_destroy(&c4_lhs81);
  sf_mex_destroy(&c4_rhs82);
  sf_mex_destroy(&c4_lhs82);
  sf_mex_destroy(&c4_rhs83);
  sf_mex_destroy(&c4_lhs83);
  sf_mex_destroy(&c4_rhs84);
  sf_mex_destroy(&c4_lhs84);
  sf_mex_destroy(&c4_rhs85);
  sf_mex_destroy(&c4_lhs85);
  sf_mex_destroy(&c4_rhs86);
  sf_mex_destroy(&c4_lhs86);
  sf_mex_destroy(&c4_rhs87);
  sf_mex_destroy(&c4_lhs87);
  sf_mex_destroy(&c4_rhs88);
  sf_mex_destroy(&c4_lhs88);
  sf_mex_destroy(&c4_rhs89);
  sf_mex_destroy(&c4_lhs89);
  sf_mex_destroy(&c4_rhs90);
  sf_mex_destroy(&c4_lhs90);
  sf_mex_destroy(&c4_rhs91);
  sf_mex_destroy(&c4_lhs91);
  sf_mex_destroy(&c4_rhs92);
  sf_mex_destroy(&c4_lhs92);
  sf_mex_destroy(&c4_rhs93);
  sf_mex_destroy(&c4_lhs93);
  sf_mex_destroy(&c4_rhs94);
  sf_mex_destroy(&c4_lhs94);
  sf_mex_destroy(&c4_rhs95);
  sf_mex_destroy(&c4_lhs95);
  sf_mex_destroy(&c4_rhs96);
  sf_mex_destroy(&c4_lhs96);
  sf_mex_destroy(&c4_rhs97);
  sf_mex_destroy(&c4_lhs97);
  sf_mex_destroy(&c4_rhs98);
  sf_mex_destroy(&c4_lhs98);
  sf_mex_destroy(&c4_rhs99);
  sf_mex_destroy(&c4_lhs99);
  sf_mex_destroy(&c4_rhs100);
  sf_mex_destroy(&c4_lhs100);
  sf_mex_destroy(&c4_rhs101);
  sf_mex_destroy(&c4_lhs101);
  sf_mex_destroy(&c4_rhs102);
  sf_mex_destroy(&c4_lhs102);
  sf_mex_destroy(&c4_rhs103);
  sf_mex_destroy(&c4_lhs103);
  sf_mex_destroy(&c4_rhs104);
  sf_mex_destroy(&c4_lhs104);
  sf_mex_destroy(&c4_rhs105);
  sf_mex_destroy(&c4_lhs105);
  sf_mex_destroy(&c4_rhs106);
  sf_mex_destroy(&c4_lhs106);
  sf_mex_destroy(&c4_rhs107);
  sf_mex_destroy(&c4_lhs107);
  sf_mex_destroy(&c4_rhs108);
  sf_mex_destroy(&c4_lhs108);
  sf_mex_destroy(&c4_rhs109);
  sf_mex_destroy(&c4_lhs109);
  sf_mex_destroy(&c4_rhs110);
  sf_mex_destroy(&c4_lhs110);
  sf_mex_destroy(&c4_rhs111);
  sf_mex_destroy(&c4_lhs111);
  sf_mex_destroy(&c4_rhs112);
  sf_mex_destroy(&c4_lhs112);
  sf_mex_destroy(&c4_rhs113);
  sf_mex_destroy(&c4_lhs113);
  sf_mex_destroy(&c4_rhs114);
  sf_mex_destroy(&c4_lhs114);
  sf_mex_destroy(&c4_rhs115);
  sf_mex_destroy(&c4_lhs115);
  sf_mex_destroy(&c4_rhs116);
  sf_mex_destroy(&c4_lhs116);
  sf_mex_destroy(&c4_rhs117);
  sf_mex_destroy(&c4_lhs117);
  sf_mex_destroy(&c4_rhs118);
  sf_mex_destroy(&c4_lhs118);
  sf_mex_destroy(&c4_rhs119);
  sf_mex_destroy(&c4_lhs119);
  sf_mex_destroy(&c4_rhs120);
  sf_mex_destroy(&c4_lhs120);
  sf_mex_destroy(&c4_rhs121);
  sf_mex_destroy(&c4_lhs121);
  sf_mex_destroy(&c4_rhs122);
  sf_mex_destroy(&c4_lhs122);
  sf_mex_destroy(&c4_rhs123);
  sf_mex_destroy(&c4_lhs123);
  sf_mex_destroy(&c4_rhs124);
  sf_mex_destroy(&c4_lhs124);
  sf_mex_destroy(&c4_rhs125);
  sf_mex_destroy(&c4_lhs125);
  sf_mex_destroy(&c4_rhs126);
  sf_mex_destroy(&c4_lhs126);
  sf_mex_destroy(&c4_rhs127);
  sf_mex_destroy(&c4_lhs127);
}

static void c4_c_info_helper(const mxArray **c4_info)
{
  const mxArray *c4_rhs128 = NULL;
  const mxArray *c4_lhs128 = NULL;
  const mxArray *c4_rhs129 = NULL;
  const mxArray *c4_lhs129 = NULL;
  const mxArray *c4_rhs130 = NULL;
  const mxArray *c4_lhs130 = NULL;
  const mxArray *c4_rhs131 = NULL;
  const mxArray *c4_lhs131 = NULL;
  const mxArray *c4_rhs132 = NULL;
  const mxArray *c4_lhs132 = NULL;
  const mxArray *c4_rhs133 = NULL;
  const mxArray *c4_lhs133 = NULL;
  const mxArray *c4_rhs134 = NULL;
  const mxArray *c4_lhs134 = NULL;
  const mxArray *c4_rhs135 = NULL;
  const mxArray *c4_lhs135 = NULL;
  const mxArray *c4_rhs136 = NULL;
  const mxArray *c4_lhs136 = NULL;
  const mxArray *c4_rhs137 = NULL;
  const mxArray *c4_lhs137 = NULL;
  const mxArray *c4_rhs138 = NULL;
  const mxArray *c4_lhs138 = NULL;
  const mxArray *c4_rhs139 = NULL;
  const mxArray *c4_lhs139 = NULL;
  const mxArray *c4_rhs140 = NULL;
  const mxArray *c4_lhs140 = NULL;
  const mxArray *c4_rhs141 = NULL;
  const mxArray *c4_lhs141 = NULL;
  const mxArray *c4_rhs142 = NULL;
  const mxArray *c4_lhs142 = NULL;
  const mxArray *c4_rhs143 = NULL;
  const mxArray *c4_lhs143 = NULL;
  const mxArray *c4_rhs144 = NULL;
  const mxArray *c4_lhs144 = NULL;
  const mxArray *c4_rhs145 = NULL;
  const mxArray *c4_lhs145 = NULL;
  const mxArray *c4_rhs146 = NULL;
  const mxArray *c4_lhs146 = NULL;
  const mxArray *c4_rhs147 = NULL;
  const mxArray *c4_lhs147 = NULL;
  const mxArray *c4_rhs148 = NULL;
  const mxArray *c4_lhs148 = NULL;
  const mxArray *c4_rhs149 = NULL;
  const mxArray *c4_lhs149 = NULL;
  const mxArray *c4_rhs150 = NULL;
  const mxArray *c4_lhs150 = NULL;
  const mxArray *c4_rhs151 = NULL;
  const mxArray *c4_lhs151 = NULL;
  const mxArray *c4_rhs152 = NULL;
  const mxArray *c4_lhs152 = NULL;
  const mxArray *c4_rhs153 = NULL;
  const mxArray *c4_lhs153 = NULL;
  const mxArray *c4_rhs154 = NULL;
  const mxArray *c4_lhs154 = NULL;
  const mxArray *c4_rhs155 = NULL;
  const mxArray *c4_lhs155 = NULL;
  const mxArray *c4_rhs156 = NULL;
  const mxArray *c4_lhs156 = NULL;
  const mxArray *c4_rhs157 = NULL;
  const mxArray *c4_lhs157 = NULL;
  const mxArray *c4_rhs158 = NULL;
  const mxArray *c4_lhs158 = NULL;
  const mxArray *c4_rhs159 = NULL;
  const mxArray *c4_lhs159 = NULL;
  const mxArray *c4_rhs160 = NULL;
  const mxArray *c4_lhs160 = NULL;
  const mxArray *c4_rhs161 = NULL;
  const mxArray *c4_lhs161 = NULL;
  const mxArray *c4_rhs162 = NULL;
  const mxArray *c4_lhs162 = NULL;
  const mxArray *c4_rhs163 = NULL;
  const mxArray *c4_lhs163 = NULL;
  const mxArray *c4_rhs164 = NULL;
  const mxArray *c4_lhs164 = NULL;
  const mxArray *c4_rhs165 = NULL;
  const mxArray *c4_lhs165 = NULL;
  const mxArray *c4_rhs166 = NULL;
  const mxArray *c4_lhs166 = NULL;
  const mxArray *c4_rhs167 = NULL;
  const mxArray *c4_lhs167 = NULL;
  const mxArray *c4_rhs168 = NULL;
  const mxArray *c4_lhs168 = NULL;
  const mxArray *c4_rhs169 = NULL;
  const mxArray *c4_lhs169 = NULL;
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 128);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("abs"), "name", "name", 128);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 128);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 128);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363688652U), "fileTimeLo",
                  "fileTimeLo", 128);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 128);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 128);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 128);
  sf_mex_assign(&c4_rhs128, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs128, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs128), "rhs", "rhs",
                  128);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs128), "lhs", "lhs",
                  128);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 129);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 129);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 129);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 129);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372561560U), "fileTimeLo",
                  "fileTimeLo", 129);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 129);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 129);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 129);
  sf_mex_assign(&c4_rhs129, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs129, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs129), "rhs", "rhs",
                  129);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs129), "lhs", "lhs",
                  129);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 130);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 130);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 130);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 130);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1397235822U), "fileTimeLo",
                  "fileTimeLo", 130);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 130);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 130);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 130);
  sf_mex_assign(&c4_rhs130, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs130, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs130), "rhs", "rhs",
                  130);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs130), "lhs", "lhs",
                  130);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 131);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 131);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 131);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 131);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372561560U), "fileTimeLo",
                  "fileTimeLo", 131);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 131);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 131);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 131);
  sf_mex_assign(&c4_rhs131, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs131, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs131), "rhs", "rhs",
                  131);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs131), "lhs", "lhs",
                  131);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 132);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 132);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 132);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 132);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372561560U), "fileTimeLo",
                  "fileTimeLo", 132);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 132);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 132);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 132);
  sf_mex_assign(&c4_rhs132, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs132, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs132), "rhs", "rhs",
                  132);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs132), "lhs", "lhs",
                  132);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!warn_singular"),
                  "context", "context", 133);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_warning"), "name", "name",
                  133);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 133);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m"), "resolved",
                  "resolved", 133);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286797202U), "fileTimeLo",
                  "fileTimeLo", 133);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 133);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 133);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 133);
  sf_mex_assign(&c4_rhs133, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs133, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs133), "rhs", "rhs",
                  133);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs133), "lhs", "lhs",
                  133);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolveNxN"),
                  "context", "context", 134);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 134);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 134);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 134);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375959088U), "fileTimeLo",
                  "fileTimeLo", 134);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 134);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 134);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 134);
  sf_mex_assign(&c4_rhs134, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs134, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs134), "rhs", "rhs",
                  134);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs134), "lhs", "lhs",
                  134);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolveNxN"),
                  "context", "context", 135);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 135);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 135);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 135);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1397235822U), "fileTimeLo",
                  "fileTimeLo", 135);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 135);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 135);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 135);
  sf_mex_assign(&c4_rhs135, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs135, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs135), "rhs", "rhs",
                  135);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs135), "lhs", "lhs",
                  135);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolveNxN"),
                  "context", "context", 136);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_xtrsm"), "name", "name",
                  136);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 136);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xtrsm.m"),
                  "resolved", "resolved", 136);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375959092U), "fileTimeLo",
                  "fileTimeLo", 136);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 136);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 136);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 136);
  sf_mex_assign(&c4_rhs136, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs136, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs136), "rhs", "rhs",
                  136);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs136), "lhs", "lhs",
                  136);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xtrsm.m"), "context",
                  "context", 137);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 137);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 137);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 137);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 137);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 137);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 137);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 137);
  sf_mex_assign(&c4_rhs137, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs137, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs137), "rhs", "rhs",
                  137);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs137), "lhs", "lhs",
                  137);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xtrsm.m"), "context",
                  "context", 138);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.xtrsm"),
                  "name", "name", 138);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 138);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xtrsm.p"),
                  "resolved", "resolved", 138);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 138);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 138);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 138);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 138);
  sf_mex_assign(&c4_rhs138, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs138, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs138), "rhs", "rhs",
                  138);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs138), "lhs", "lhs",
                  138);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xtrsm.p"),
                  "context", "context", 139);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 139);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 139);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 139);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 139);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 139);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 139);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 139);
  sf_mex_assign(&c4_rhs139, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs139, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs139), "rhs", "rhs",
                  139);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs139), "lhs", "lhs",
                  139);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xtrsm.p"),
                  "context", "context", 140);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 140);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 140);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 140);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 140);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 140);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 140);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 140);
  sf_mex_assign(&c4_rhs140, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs140, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs140), "rhs", "rhs",
                  140);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs140), "lhs", "lhs",
                  140);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xtrsm.p"),
                  "context", "context", 141);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.refblas.xtrsm"),
                  "name", "name", 141);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 141);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xtrsm.p"),
                  "resolved", "resolved", 141);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 141);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 141);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 141);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 141);
  sf_mex_assign(&c4_rhs141, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs141, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs141), "rhs", "rhs",
                  141);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs141), "lhs", "lhs",
                  141);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xtrsm.p"),
                  "context", "context", 142);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 142);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 142);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 142);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1389692574U), "fileTimeLo",
                  "fileTimeLo", 142);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 142);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 142);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 142);
  sf_mex_assign(&c4_rhs142, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs142, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs142), "rhs", "rhs",
                  142);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs142), "lhs", "lhs",
                  142);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xtrsm.p"),
                  "context", "context", 143);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 143);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 143);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 143);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 143);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 143);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 143);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 143);
  sf_mex_assign(&c4_rhs143, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs143, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs143), "rhs", "rhs",
                  143);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs143), "lhs", "lhs",
                  143);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xtrsm.p"),
                  "context", "context", 144);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 144);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 144);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 144);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1397235822U), "fileTimeLo",
                  "fileTimeLo", 144);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 144);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 144);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 144);
  sf_mex_assign(&c4_rhs144, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs144, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs144), "rhs", "rhs",
                  144);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs144), "lhs", "lhs",
                  144);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xtrsm.p"),
                  "context", "context", 145);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.int"),
                  "name", "name", 145);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 145);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/int.p"),
                  "resolved", "resolved", 145);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 145);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 145);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 145);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 145);
  sf_mex_assign(&c4_rhs145, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs145, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs145), "rhs", "rhs",
                  145);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs145), "lhs", "lhs",
                  145);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xtrsm.p!ceval_xtrsm"),
                  "context", "context", 146);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.size_ptr"),
                  "name", "name", 146);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 146);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/size_ptr.p"),
                  "resolved", "resolved", 146);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 146);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 146);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 146);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 146);
  sf_mex_assign(&c4_rhs146, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs146, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs146), "rhs", "rhs",
                  146);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs146), "lhs", "lhs",
                  146);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xtrsm.p!ceval_xtrsm"),
                  "context", "context", 147);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.c_cast"),
                  "name", "name", 147);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("int32"), "dominantType",
                  "dominantType", 147);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/c_cast.p"),
                  "resolved", "resolved", 147);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 147);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 147);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 147);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 147);
  sf_mex_assign(&c4_rhs147, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs147, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs147), "rhs", "rhs",
                  147);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs147), "lhs", "lhs",
                  147);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xtrsm.p"),
                  "context", "context", 148);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("rdivide"), "name", "name", 148);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 148);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 148);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363688680U), "fileTimeLo",
                  "fileTimeLo", 148);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 148);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 148);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 148);
  sf_mex_assign(&c4_rhs148, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs148, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs148), "rhs", "rhs",
                  148);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs148), "lhs", "lhs",
                  148);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 149);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 149);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 149);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 149);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1395906656U), "fileTimeLo",
                  "fileTimeLo", 149);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 149);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 149);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 149);
  sf_mex_assign(&c4_rhs149, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs149, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs149), "rhs", "rhs",
                  149);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs149), "lhs", "lhs",
                  149);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 150);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 150);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 150);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 150);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286797196U), "fileTimeLo",
                  "fileTimeLo", 150);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 150);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 150);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 150);
  sf_mex_assign(&c4_rhs150, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs150, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs150), "rhs", "rhs",
                  150);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs150), "lhs", "lhs",
                  150);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 151);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_div"), "name", "name", 151);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 151);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 151);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1386398752U), "fileTimeLo",
                  "fileTimeLo", 151);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 151);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 151);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 151);
  sf_mex_assign(&c4_rhs151, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs151, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs151), "rhs", "rhs",
                  151);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs151), "lhs", "lhs",
                  151);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 152);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("norm"), "name", "name", 152);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 152);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m"), "resolved",
                  "resolved", 152);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363688668U), "fileTimeLo",
                  "fileTimeLo", 152);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 152);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 152);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 152);
  sf_mex_assign(&c4_rhs152, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs152, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs152), "rhs", "rhs",
                  152);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs152), "lhs", "lhs",
                  152);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm"),
                  "context", "context", 153);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 153);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 153);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 153);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1323145378U), "fileTimeLo",
                  "fileTimeLo", 153);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 153);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 153);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 153);
  sf_mex_assign(&c4_rhs153, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs153, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs153), "rhs", "rhs",
                  153);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs153), "lhs", "lhs",
                  153);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm"),
                  "context", "context", 154);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 154);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 154);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 154);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1395906656U), "fileTimeLo",
                  "fileTimeLo", 154);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 154);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 154);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 154);
  sf_mex_assign(&c4_rhs154, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs154, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs154), "rhs", "rhs",
                  154);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs154), "lhs", "lhs",
                  154);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm"),
                  "context", "context", 155);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_xnrm2"), "name", "name",
                  155);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 155);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m"),
                  "resolved", "resolved", 155);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375959092U), "fileTimeLo",
                  "fileTimeLo", 155);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 155);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 155);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 155);
  sf_mex_assign(&c4_rhs155, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs155, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs155), "rhs", "rhs",
                  155);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs155), "lhs", "lhs",
                  155);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m"), "context",
                  "context", 156);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 156);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 156);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 156);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 156);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 156);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 156);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 156);
  sf_mex_assign(&c4_rhs156, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs156, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs156), "rhs", "rhs",
                  156);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs156), "lhs", "lhs",
                  156);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m"), "context",
                  "context", 157);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.xnrm2"),
                  "name", "name", 157);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 157);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xnrm2.p"),
                  "resolved", "resolved", 157);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 157);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 157);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 157);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 157);
  sf_mex_assign(&c4_rhs157, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs157, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs157), "rhs", "rhs",
                  157);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs157), "lhs", "lhs",
                  157);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xnrm2.p"),
                  "context", "context", 158);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 158);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 158);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 158);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 158);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 158);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 158);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 158);
  sf_mex_assign(&c4_rhs158, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs158, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs158), "rhs", "rhs",
                  158);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs158), "lhs", "lhs",
                  158);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xnrm2.p!below_threshold"),
                  "context", "context", 159);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 159);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 159);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 159);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 159);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 159);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 159);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 159);
  sf_mex_assign(&c4_rhs159, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs159, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs159), "rhs", "rhs",
                  159);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs159), "lhs", "lhs",
                  159);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xnrm2.p"),
                  "context", "context", 160);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.refblas.xnrm2"),
                  "name", "name", 160);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 160);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xnrm2.p"),
                  "resolved", "resolved", 160);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 160);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 160);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 160);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 160);
  sf_mex_assign(&c4_rhs160, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs160, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs160), "rhs", "rhs",
                  160);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs160), "lhs", "lhs",
                  160);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xnrm2.p"),
                  "context", "context", 161);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("realmin"), "name", "name", 161);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 161);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m"), "resolved",
                  "resolved", 161);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1307629642U), "fileTimeLo",
                  "fileTimeLo", 161);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 161);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 161);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 161);
  sf_mex_assign(&c4_rhs161, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs161, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs161), "rhs", "rhs",
                  161);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs161), "lhs", "lhs",
                  161);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xnrm2.p"),
                  "context", "context", 162);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 162);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 162);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 162);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372561560U), "fileTimeLo",
                  "fileTimeLo", 162);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 162);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 162);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 162);
  sf_mex_assign(&c4_rhs162, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs162, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs162), "rhs", "rhs",
                  162);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs162), "lhs", "lhs",
                  162);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xnrm2.p"),
                  "context", "context", 163);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexTimes"),
                  "name", "name", 163);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 163);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexTimes.m"),
                  "resolved", "resolved", 163);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372561560U), "fileTimeLo",
                  "fileTimeLo", 163);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 163);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 163);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 163);
  sf_mex_assign(&c4_rhs163, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs163, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs163), "rhs", "rhs",
                  163);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs163), "lhs", "lhs",
                  163);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xnrm2.p"),
                  "context", "context", 164);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 164);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 164);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 164);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372561560U), "fileTimeLo",
                  "fileTimeLo", 164);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 164);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 164);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 164);
  sf_mex_assign(&c4_rhs164, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs164, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs164), "rhs", "rhs",
                  164);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs164), "lhs", "lhs",
                  164);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xnrm2.p"),
                  "context", "context", 165);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 165);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 165);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 165);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1397235822U), "fileTimeLo",
                  "fileTimeLo", 165);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 165);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 165);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 165);
  sf_mex_assign(&c4_rhs165, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs165, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs165), "rhs", "rhs",
                  165);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs165), "lhs", "lhs",
                  165);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xnrm2.p"),
                  "context", "context", 166);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("abs"), "name", "name", 166);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 166);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 166);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363688652U), "fileTimeLo",
                  "fileTimeLo", 166);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 166);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 166);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 166);
  sf_mex_assign(&c4_rhs166, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs166, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs166), "rhs", "rhs",
                  166);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs166), "lhs", "lhs",
                  166);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 167);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("mrdivide"), "name", "name",
                  167);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 167);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 167);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1410786048U), "fileTimeLo",
                  "fileTimeLo", 167);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 167);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1369988286U), "mFileTimeLo",
                  "mFileTimeLo", 167);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 167);
  sf_mex_assign(&c4_rhs167, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs167, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs167), "rhs", "rhs",
                  167);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs167), "lhs", "lhs",
                  167);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 168);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 168);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 168);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 168);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1389692574U), "fileTimeLo",
                  "fileTimeLo", 168);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 168);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 168);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 168);
  sf_mex_assign(&c4_rhs168, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs168, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs168), "rhs", "rhs",
                  168);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs168), "lhs", "lhs",
                  168);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 169);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("rdivide"), "name", "name", 169);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 169);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 169);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363688680U), "fileTimeLo",
                  "fileTimeLo", 169);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 169);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 169);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 169);
  sf_mex_assign(&c4_rhs169, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs169, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs169), "rhs", "rhs",
                  169);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs169), "lhs", "lhs",
                  169);
  sf_mex_destroy(&c4_rhs128);
  sf_mex_destroy(&c4_lhs128);
  sf_mex_destroy(&c4_rhs129);
  sf_mex_destroy(&c4_lhs129);
  sf_mex_destroy(&c4_rhs130);
  sf_mex_destroy(&c4_lhs130);
  sf_mex_destroy(&c4_rhs131);
  sf_mex_destroy(&c4_lhs131);
  sf_mex_destroy(&c4_rhs132);
  sf_mex_destroy(&c4_lhs132);
  sf_mex_destroy(&c4_rhs133);
  sf_mex_destroy(&c4_lhs133);
  sf_mex_destroy(&c4_rhs134);
  sf_mex_destroy(&c4_lhs134);
  sf_mex_destroy(&c4_rhs135);
  sf_mex_destroy(&c4_lhs135);
  sf_mex_destroy(&c4_rhs136);
  sf_mex_destroy(&c4_lhs136);
  sf_mex_destroy(&c4_rhs137);
  sf_mex_destroy(&c4_lhs137);
  sf_mex_destroy(&c4_rhs138);
  sf_mex_destroy(&c4_lhs138);
  sf_mex_destroy(&c4_rhs139);
  sf_mex_destroy(&c4_lhs139);
  sf_mex_destroy(&c4_rhs140);
  sf_mex_destroy(&c4_lhs140);
  sf_mex_destroy(&c4_rhs141);
  sf_mex_destroy(&c4_lhs141);
  sf_mex_destroy(&c4_rhs142);
  sf_mex_destroy(&c4_lhs142);
  sf_mex_destroy(&c4_rhs143);
  sf_mex_destroy(&c4_lhs143);
  sf_mex_destroy(&c4_rhs144);
  sf_mex_destroy(&c4_lhs144);
  sf_mex_destroy(&c4_rhs145);
  sf_mex_destroy(&c4_lhs145);
  sf_mex_destroy(&c4_rhs146);
  sf_mex_destroy(&c4_lhs146);
  sf_mex_destroy(&c4_rhs147);
  sf_mex_destroy(&c4_lhs147);
  sf_mex_destroy(&c4_rhs148);
  sf_mex_destroy(&c4_lhs148);
  sf_mex_destroy(&c4_rhs149);
  sf_mex_destroy(&c4_lhs149);
  sf_mex_destroy(&c4_rhs150);
  sf_mex_destroy(&c4_lhs150);
  sf_mex_destroy(&c4_rhs151);
  sf_mex_destroy(&c4_lhs151);
  sf_mex_destroy(&c4_rhs152);
  sf_mex_destroy(&c4_lhs152);
  sf_mex_destroy(&c4_rhs153);
  sf_mex_destroy(&c4_lhs153);
  sf_mex_destroy(&c4_rhs154);
  sf_mex_destroy(&c4_lhs154);
  sf_mex_destroy(&c4_rhs155);
  sf_mex_destroy(&c4_lhs155);
  sf_mex_destroy(&c4_rhs156);
  sf_mex_destroy(&c4_lhs156);
  sf_mex_destroy(&c4_rhs157);
  sf_mex_destroy(&c4_lhs157);
  sf_mex_destroy(&c4_rhs158);
  sf_mex_destroy(&c4_lhs158);
  sf_mex_destroy(&c4_rhs159);
  sf_mex_destroy(&c4_lhs159);
  sf_mex_destroy(&c4_rhs160);
  sf_mex_destroy(&c4_lhs160);
  sf_mex_destroy(&c4_rhs161);
  sf_mex_destroy(&c4_lhs161);
  sf_mex_destroy(&c4_rhs162);
  sf_mex_destroy(&c4_lhs162);
  sf_mex_destroy(&c4_rhs163);
  sf_mex_destroy(&c4_lhs163);
  sf_mex_destroy(&c4_rhs164);
  sf_mex_destroy(&c4_lhs164);
  sf_mex_destroy(&c4_rhs165);
  sf_mex_destroy(&c4_lhs165);
  sf_mex_destroy(&c4_rhs166);
  sf_mex_destroy(&c4_lhs166);
  sf_mex_destroy(&c4_rhs167);
  sf_mex_destroy(&c4_lhs167);
  sf_mex_destroy(&c4_rhs168);
  sf_mex_destroy(&c4_lhs168);
  sf_mex_destroy(&c4_rhs169);
  sf_mex_destroy(&c4_lhs169);
}

static void c4_eml_scalar_eg(SFc4_VrabieInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static boolean_T c4_use_refblas(SFc4_VrabieInstanceStruct *chartInstance)
{
  (void)chartInstance;
  return false;
}

static void c4_below_threshold(SFc4_VrabieInstanceStruct *chartInstance)
{
  c4_threshold(chartInstance);
}

static void c4_threshold(SFc4_VrabieInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_scalarEg(SFc4_VrabieInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_eml_switch_helper(SFc4_VrabieInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_eml_xgemm(SFc4_VrabieInstanceStruct *chartInstance, int32_T c4_k,
  real_T c4_A_data[], int32_T c4_A_sizes[2], real_T c4_B_data[], int32_T
  c4_B_sizes[2], int32_T c4_ldb, real_T c4_C[100])
{
  int32_T c4_b_k;
  int32_T c4_b_ldb;
  int32_T c4_i118;
  int32_T c4_c_k;
  int32_T c4_c_ldb;
  int32_T c4_ldb1;
  int32_T c4_cr;
  int32_T c4_b_cr;
  int32_T c4_a;
  int32_T c4_i119;
  int32_T c4_b_a;
  int32_T c4_i120;
  int32_T c4_c_a;
  int32_T c4_b;
  int32_T c4_d_a;
  int32_T c4_b_b;
  boolean_T c4_overflow;
  int32_T c4_ic;
  int32_T c4_b_ic;
  int32_T c4_br;
  int32_T c4_c_cr;
  int32_T c4_ar;
  int32_T c4_e_a;
  int32_T c4_i121;
  int32_T c4_f_a;
  int32_T c4_c_b;
  int32_T c4_i122;
  int32_T c4_g_a;
  int32_T c4_d_b;
  int32_T c4_h_a;
  int32_T c4_e_b;
  boolean_T c4_b_overflow;
  int32_T c4_ib;
  int32_T c4_b_ib;
  real_T c4_temp;
  int32_T c4_ia;
  int32_T c4_i_a;
  int32_T c4_i123;
  int32_T c4_j_a;
  int32_T c4_i124;
  int32_T c4_k_a;
  int32_T c4_f_b;
  int32_T c4_l_a;
  int32_T c4_g_b;
  boolean_T c4_c_overflow;
  int32_T c4_c_ic;
  int32_T c4_m_a;
  int32_T c4_n_a;
  int32_T c4_o_a;
  int32_T c4_h_b;
  int32_T c4_d_k;
  real_T c4_alpha1;
  int32_T c4_d_ldb;
  real_T c4_beta1;
  char_T c4_TRANSB;
  char_T c4_TRANSA;
  ptrdiff_t c4_m_t;
  ptrdiff_t c4_n_t;
  int32_T c4_var;
  ptrdiff_t c4_k_t;
  ptrdiff_t c4_lda_t;
  int32_T c4_b_var;
  ptrdiff_t c4_ldb_t;
  ptrdiff_t c4_ldc_t;
  double * c4_alpha1_t;
  double * c4_Aia0_t;
  double * c4_Bib0_t;
  double * c4_beta1_t;
  double * c4_Cic0_t;
  c4_b_k = c4_k;
  c4_b_ldb = c4_ldb;
  for (c4_i118 = 0; c4_i118 < 100; c4_i118++) {
    c4_C[c4_i118] = 0.0;
  }

  if (c4_use_refblas(chartInstance)) {
    c4_scalarEg(chartInstance);
    c4_scalarEg(chartInstance);
    c4_c_k = c4_b_k;
    c4_c_ldb = c4_b_ldb;
    c4_ldb1 = c4_c_ldb;
    c4_eml_switch_helper(chartInstance);
    for (c4_cr = 0; c4_cr < 91; c4_cr += 10) {
      c4_b_cr = c4_cr;
      c4_a = c4_b_cr + 1;
      c4_i119 = c4_a;
      c4_b_a = c4_b_cr + 10;
      c4_i120 = c4_b_a;
      c4_c_a = c4_i119;
      c4_b = c4_i120;
      c4_d_a = c4_c_a;
      c4_b_b = c4_b;
      if (c4_d_a > c4_b_b) {
        c4_overflow = false;
      } else {
        c4_eml_switch_helper(chartInstance);
        c4_eml_switch_helper(chartInstance);
        c4_overflow = (c4_b_b > 2147483646);
      }

      if (c4_overflow) {
        c4_check_forloop_overflow_error(chartInstance, true);
      }

      for (c4_ic = c4_i119; c4_ic <= c4_i120; c4_ic++) {
        c4_b_ic = c4_ic;
        c4_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_b_ic, 1, 100, 1, 0) - 1] = 0.0;
      }
    }

    c4_br = 0;
    c4_eml_switch_helper(chartInstance);
    for (c4_c_cr = 0; c4_c_cr < 91; c4_c_cr += 10) {
      c4_b_cr = c4_c_cr;
      c4_ar = 0;
      c4_e_a = c4_br + 1;
      c4_i121 = c4_e_a;
      c4_f_a = c4_br;
      c4_c_b = c4_c_k;
      c4_i122 = c4_f_a + c4_c_b;
      c4_g_a = c4_i121;
      c4_d_b = c4_i122;
      c4_h_a = c4_g_a;
      c4_e_b = c4_d_b;
      if (c4_h_a > c4_e_b) {
        c4_b_overflow = false;
      } else {
        c4_eml_switch_helper(chartInstance);
        c4_eml_switch_helper(chartInstance);
        c4_b_overflow = (c4_e_b > 2147483646);
      }

      if (c4_b_overflow) {
        c4_check_forloop_overflow_error(chartInstance, true);
      }

      for (c4_ib = c4_i121; c4_ib <= c4_i122; c4_ib++) {
        c4_b_ib = c4_ib;
        if (c4_B_data[_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_b_ib, 1, c4_B_sizes[0] *
             10, 1, 0) - 1] != 0.0) {
          c4_temp = c4_B_data[_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_b_ib, 1,
            c4_B_sizes[0] * 10, 1, 0) - 1];
          c4_ia = c4_ar;
          c4_i_a = c4_b_cr + 1;
          c4_i123 = c4_i_a;
          c4_j_a = c4_b_cr + 10;
          c4_i124 = c4_j_a;
          c4_k_a = c4_i123;
          c4_f_b = c4_i124;
          c4_l_a = c4_k_a;
          c4_g_b = c4_f_b;
          if (c4_l_a > c4_g_b) {
            c4_c_overflow = false;
          } else {
            c4_eml_switch_helper(chartInstance);
            c4_eml_switch_helper(chartInstance);
            c4_c_overflow = (c4_g_b > 2147483646);
          }

          if (c4_c_overflow) {
            c4_check_forloop_overflow_error(chartInstance, true);
          }

          for (c4_c_ic = c4_i123; c4_c_ic <= c4_i124; c4_c_ic++) {
            c4_b_ic = c4_c_ic;
            c4_m_a = c4_ia + 1;
            c4_ia = c4_m_a;
            c4_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_b_ic, 1, 100, 1, 0) - 1] =
              c4_C[_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_b_ic, 1, 100, 1, 0) - 1] +
              c4_temp * c4_A_data[_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_ia, 1, 10 *
              c4_A_sizes[1], 1, 0) - 1];
          }
        }

        c4_n_a = c4_ar + 10;
        c4_ar = c4_n_a;
      }

      c4_o_a = c4_br;
      c4_h_b = c4_ldb1;
      c4_br = c4_o_a + c4_h_b;
    }
  } else {
    c4_below_threshold(chartInstance);
    if (c4_b_k < 1) {
    } else {
      c4_d_k = c4_b_k;
      c4_alpha1 = 1.0;
      c4_d_ldb = c4_b_ldb;
      c4_beta1 = 0.0;
      c4_TRANSB = 'N';
      c4_TRANSA = 'N';
      c4_m_t = (ptrdiff_t)(10);
      c4_n_t = (ptrdiff_t)(10);
      c4_var = c4_d_k;
      c4_k_t = (ptrdiff_t)(c4_var);
      c4_lda_t = (ptrdiff_t)(10);
      c4_b_var = c4_d_ldb;
      c4_ldb_t = (ptrdiff_t)(c4_b_var);
      c4_ldc_t = (ptrdiff_t)(10);
      c4_alpha1_t = (double *)(&c4_alpha1);
      _SFD_EML_ARRAY_BOUNDS_CHECK("", 1, 1, 10 * c4_A_sizes[1], 1, 0);
      c4_Aia0_t = (double *)(&c4_A_data[0]);
      _SFD_EML_ARRAY_BOUNDS_CHECK("", 1, 1, c4_B_sizes[0] * 10, 1, 0);
      c4_Bib0_t = (double *)(&c4_B_data[0]);
      c4_beta1_t = (double *)(&c4_beta1);
      c4_Cic0_t = (double *)(&c4_C[0]);
      dgemm(&c4_TRANSA, &c4_TRANSB, &c4_m_t, &c4_n_t, &c4_k_t, c4_alpha1_t,
            c4_Aia0_t, &c4_lda_t, c4_Bib0_t, &c4_ldb_t, c4_beta1_t, c4_Cic0_t,
            &c4_ldc_t);
    }
  }
}

static void c4_check_forloop_overflow_error(SFc4_VrabieInstanceStruct
  *chartInstance, boolean_T c4_overflow)
{
  int32_T c4_i125;
  static char_T c4_cv2[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o', 'p',
    '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  char_T c4_u[34];
  const mxArray *c4_y = NULL;
  int32_T c4_i126;
  static char_T c4_cv3[5] = { 'i', 'n', 't', '3', '2' };

  char_T c4_b_u[5];
  const mxArray *c4_b_y = NULL;
  (void)chartInstance;
  (void)c4_overflow;
  for (c4_i125 = 0; c4_i125 < 34; c4_i125++) {
    c4_u[c4_i125] = c4_cv2[c4_i125];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 10, 0U, 1U, 0U, 2, 1, 34), false);
  for (c4_i126 = 0; c4_i126 < 5; c4_i126++) {
    c4_b_u[c4_i126] = c4_cv3[c4_i126];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_b_u, 10, 0U, 1U, 0U, 2, 1, 5),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    2U, 14, c4_y, 14, c4_b_y));
}

static void c4_mldivide(SFc4_VrabieInstanceStruct *chartInstance, real_T c4_A
  [100], real_T c4_B_data[], int32_T c4_B_sizes[2], real_T c4_b_Y_data[],
  int32_T c4_b_Y_sizes[2])
{
  boolean_T c4_b5;
  real_T c4_dv7[2];
  int32_T c4_iv4[2];
  int32_T c4_Y;
  int32_T c4_b_Y;
  int32_T c4_loop_ub;
  int32_T c4_i127;
  int32_T c4_i128;
  real_T c4_b_A[100];
  int32_T c4_info;
  int32_T c4_ipiv[10];
  int32_T c4_b_info;
  int32_T c4_c_info;
  int32_T c4_d_info;
  int32_T c4_c_Y;
  int32_T c4_d_Y;
  int32_T c4_b_loop_ub;
  int32_T c4_i129;
  int32_T c4_nb;
  int32_T c4_xi;
  int32_T c4_b_xi;
  int32_T c4_ip;
  int32_T c4_b_nb;
  int32_T c4_b;
  int32_T c4_b_b;
  int32_T c4_xj;
  int32_T c4_b_xj;
  real_T c4_temp;
  int32_T c4_i130;
  real_T c4_c_A[100];
  int32_T c4_i131;
  real_T c4_d_A[100];
  c4_b5 = (c4_B_sizes[1] == 0);
  if (c4_b5) {
    c4_b_eml_scalar_eg(chartInstance);
    c4_dv7[0] = 10.0;
    c4_dv7[1] = (real_T)c4_B_sizes[1];
    c4_b_Y_sizes[0] = 10;
    c4_iv4[0] = 10;
    c4_iv4[1] = (int32_T)c4_dv7[1];
    c4_b_Y_sizes[1] = c4_iv4[1];
    c4_Y = c4_b_Y_sizes[0];
    c4_b_Y = c4_b_Y_sizes[1];
    c4_loop_ub = 10 * (int32_T)c4_dv7[1] - 1;
    for (c4_i127 = 0; c4_i127 <= c4_loop_ub; c4_i127++) {
      c4_b_Y_data[c4_i127] = 0.0;
    }
  } else {
    for (c4_i128 = 0; c4_i128 < 100; c4_i128++) {
      c4_b_A[c4_i128] = c4_A[c4_i128];
    }

    c4_b_eml_matlab_zgetrf(chartInstance, c4_b_A, c4_ipiv, &c4_info);
    c4_b_info = c4_info;
    c4_c_info = c4_b_info;
    c4_d_info = c4_c_info;
    if (c4_d_info > 0) {
      c4_eml_warning(chartInstance);
    }

    c4_b_eml_scalar_eg(chartInstance);
    c4_b_Y_sizes[0] = 10;
    c4_b_Y_sizes[1] = c4_B_sizes[1];
    c4_c_Y = c4_b_Y_sizes[0];
    c4_d_Y = c4_b_Y_sizes[1];
    c4_b_loop_ub = c4_B_sizes[0] * c4_B_sizes[1] - 1;
    for (c4_i129 = 0; c4_i129 <= c4_b_loop_ub; c4_i129++) {
      c4_b_Y_data[c4_i129] = c4_B_data[c4_i129];
    }

    c4_nb = c4_B_sizes[1];
    c4_eml_switch_helper(chartInstance);
    for (c4_xi = 1; c4_xi < 10; c4_xi++) {
      c4_b_xi = c4_xi - 1;
      if (c4_ipiv[c4_b_xi] != c4_b_xi + 1) {
        c4_ip = c4_ipiv[c4_b_xi];
        c4_b_nb = c4_nb;
        c4_b = c4_b_nb;
        c4_b_b = c4_b;
        if (1 > c4_b_b) {
        } else {
          c4_eml_switch_helper(chartInstance);
          c4_eml_switch_helper(chartInstance);
        }

        for (c4_xj = 1; c4_xj <= c4_b_nb; c4_xj++) {
          c4_b_xj = c4_xj;
          c4_temp = c4_b_Y_data[c4_b_xi + c4_b_Y_sizes[0] *
            (_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_b_xj, 1, c4_b_Y_sizes[1], 2, 0)
             - 1)];
          c4_b_Y_data[c4_b_xi + c4_b_Y_sizes[0] * (_SFD_EML_ARRAY_BOUNDS_CHECK(
            "", c4_b_xj, 1, c4_b_Y_sizes[1], 2, 0) - 1)] = c4_b_Y_data
            [(_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_ip, 1, 10, 1, 0) +
              c4_b_Y_sizes[0] * (_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_b_xj, 1,
                c4_b_Y_sizes[1], 2, 0) - 1)) - 1];
          c4_b_Y_data[(c4_ip + c4_b_Y_sizes[0] * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
            c4_b_xj, 1, c4_b_Y_sizes[1], 2, 0) - 1)) - 1] = c4_temp;
        }
      }
    }

    for (c4_i130 = 0; c4_i130 < 100; c4_i130++) {
      c4_c_A[c4_i130] = c4_b_A[c4_i130];
    }

    c4_c_eml_xtrsm(chartInstance, c4_nb, c4_c_A, c4_b_Y_data, c4_b_Y_sizes);
    for (c4_i131 = 0; c4_i131 < 100; c4_i131++) {
      c4_d_A[c4_i131] = c4_b_A[c4_i131];
    }

    c4_d_eml_xtrsm(chartInstance, c4_nb, c4_d_A, c4_b_Y_data, c4_b_Y_sizes);
  }
}

static void c4_b_eml_scalar_eg(SFc4_VrabieInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_realmin(SFc4_VrabieInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_eps(SFc4_VrabieInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_eml_matlab_zgetrf(SFc4_VrabieInstanceStruct *chartInstance,
  real_T c4_A[100], real_T c4_b_A[100], int32_T c4_ipiv[10], int32_T *c4_info)
{
  int32_T c4_i132;
  for (c4_i132 = 0; c4_i132 < 100; c4_i132++) {
    c4_b_A[c4_i132] = c4_A[c4_i132];
  }

  c4_b_eml_matlab_zgetrf(chartInstance, c4_b_A, c4_ipiv, c4_info);
}

static int32_T c4_eml_ixamax(SFc4_VrabieInstanceStruct *chartInstance, int32_T
  c4_n, real_T c4_x[100], int32_T c4_ix0)
{
  int32_T c4_idxmax;
  int32_T c4_b_n;
  int32_T c4_b_ix0;
  int32_T c4_c_n;
  int32_T c4_c_ix0;
  int32_T c4_ix;
  real_T c4_b_x;
  real_T c4_c_x;
  real_T c4_d_x;
  real_T c4_y;
  real_T c4_e_x;
  real_T c4_f_x;
  real_T c4_b_y;
  real_T c4_smax;
  int32_T c4_d_n;
  int32_T c4_b;
  int32_T c4_b_b;
  boolean_T c4_overflow;
  int32_T c4_k;
  int32_T c4_b_k;
  int32_T c4_a;
  real_T c4_g_x;
  real_T c4_h_x;
  real_T c4_i_x;
  real_T c4_c_y;
  real_T c4_j_x;
  real_T c4_k_x;
  real_T c4_d_y;
  real_T c4_s;
  c4_b_n = c4_n;
  c4_b_ix0 = c4_ix0;
  c4_c_n = c4_b_n;
  c4_c_ix0 = c4_b_ix0;
  if (c4_c_n < 1) {
    c4_idxmax = 0;
  } else {
    c4_idxmax = 1;
    if (c4_c_n > 1) {
      c4_ix = c4_c_ix0;
      c4_b_x = c4_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_ix, 1, 100, 1, 0) - 1];
      c4_c_x = c4_b_x;
      c4_d_x = c4_c_x;
      c4_y = muDoubleScalarAbs(c4_d_x);
      c4_e_x = 0.0;
      c4_f_x = c4_e_x;
      c4_b_y = muDoubleScalarAbs(c4_f_x);
      c4_smax = c4_y + c4_b_y;
      c4_d_n = c4_c_n;
      c4_b = c4_d_n;
      c4_b_b = c4_b;
      c4_eml_switch_helper(chartInstance);
      c4_eml_switch_helper(chartInstance);
      c4_overflow = (c4_b_b > 2147483646);
      if (c4_overflow) {
        c4_check_forloop_overflow_error(chartInstance, true);
      }

      for (c4_k = 2; c4_k <= c4_d_n; c4_k++) {
        c4_b_k = c4_k;
        c4_a = c4_ix + 1;
        c4_ix = c4_a;
        c4_g_x = c4_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_ix, 1, 100, 1, 0) - 1];
        c4_h_x = c4_g_x;
        c4_i_x = c4_h_x;
        c4_c_y = muDoubleScalarAbs(c4_i_x);
        c4_j_x = 0.0;
        c4_k_x = c4_j_x;
        c4_d_y = muDoubleScalarAbs(c4_k_x);
        c4_s = c4_c_y + c4_d_y;
        if (c4_s > c4_smax) {
          c4_idxmax = c4_b_k;
          c4_smax = c4_s;
        }
      }
    }
  }

  return c4_idxmax;
}

static void c4_b_eml_switch_helper(SFc4_VrabieInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_eml_xgeru(SFc4_VrabieInstanceStruct *chartInstance, int32_T c4_m,
  int32_T c4_n, real_T c4_alpha1, int32_T c4_ix0, int32_T c4_iy0, real_T c4_A
  [100], int32_T c4_ia0, real_T c4_b_A[100])
{
  int32_T c4_i133;
  for (c4_i133 = 0; c4_i133 < 100; c4_i133++) {
    c4_b_A[c4_i133] = c4_A[c4_i133];
  }

  c4_b_eml_xgeru(chartInstance, c4_m, c4_n, c4_alpha1, c4_ix0, c4_iy0, c4_b_A,
                 c4_ia0);
}

static void c4_eml_warning(SFc4_VrabieInstanceStruct *chartInstance)
{
  int32_T c4_i134;
  static char_T c4_varargin_1[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a',
    't', 'r', 'i', 'x' };

  char_T c4_u[27];
  const mxArray *c4_y = NULL;
  (void)chartInstance;
  for (c4_i134 = 0; c4_i134 < 27; c4_i134++) {
    c4_u[c4_i134] = c4_varargin_1[c4_i134];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 10, 0U, 1U, 0U, 2, 1, 27), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "warning", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    1U, 14, c4_y));
}

static void c4_eml_xtrsm(SFc4_VrabieInstanceStruct *chartInstance, int32_T c4_n,
  real_T c4_A[100], real_T c4_B_data[], int32_T c4_B_sizes[2], real_T
  c4_b_B_data[], int32_T c4_b_B_sizes[2])
{
  int32_T c4_B;
  int32_T c4_b_B;
  int32_T c4_loop_ub;
  int32_T c4_i135;
  int32_T c4_i136;
  real_T c4_b_A[100];
  c4_b_B_sizes[0] = 10;
  c4_b_B_sizes[1] = c4_B_sizes[1];
  c4_B = c4_b_B_sizes[0];
  c4_b_B = c4_b_B_sizes[1];
  c4_loop_ub = c4_B_sizes[0] * c4_B_sizes[1] - 1;
  for (c4_i135 = 0; c4_i135 <= c4_loop_ub; c4_i135++) {
    c4_b_B_data[c4_i135] = c4_B_data[c4_i135];
  }

  for (c4_i136 = 0; c4_i136 < 100; c4_i136++) {
    c4_b_A[c4_i136] = c4_A[c4_i136];
  }

  c4_c_eml_xtrsm(chartInstance, c4_n, c4_b_A, c4_b_B_data, c4_b_B_sizes);
}

static void c4_b_eml_xtrsm(SFc4_VrabieInstanceStruct *chartInstance, int32_T
  c4_n, real_T c4_A[100], real_T c4_B_data[], int32_T c4_B_sizes[2], real_T
  c4_b_B_data[], int32_T c4_b_B_sizes[2])
{
  int32_T c4_B;
  int32_T c4_b_B;
  int32_T c4_loop_ub;
  int32_T c4_i137;
  int32_T c4_i138;
  real_T c4_b_A[100];
  c4_b_B_sizes[0] = 10;
  c4_b_B_sizes[1] = c4_B_sizes[1];
  c4_B = c4_b_B_sizes[0];
  c4_b_B = c4_b_B_sizes[1];
  c4_loop_ub = c4_B_sizes[0] * c4_B_sizes[1] - 1;
  for (c4_i137 = 0; c4_i137 <= c4_loop_ub; c4_i137++) {
    c4_b_B_data[c4_i137] = c4_B_data[c4_i137];
  }

  for (c4_i138 = 0; c4_i138 < 100; c4_i138++) {
    c4_b_A[c4_i138] = c4_A[c4_i138];
  }

  c4_d_eml_xtrsm(chartInstance, c4_n, c4_b_A, c4_b_B_data, c4_b_B_sizes);
}

static real_T c4_rdivide(SFc4_VrabieInstanceStruct *chartInstance, real_T c4_x,
  real_T c4_y)
{
  real_T c4_b_x;
  real_T c4_b_y;
  real_T c4_c_x;
  real_T c4_c_y;
  (void)chartInstance;
  c4_b_x = c4_x;
  c4_b_y = c4_y;
  c4_c_x = c4_b_x;
  c4_c_y = c4_b_y;
  return c4_c_x / c4_c_y;
}

static void c4_c_eml_scalar_eg(SFc4_VrabieInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_b_eml_xgemm(SFc4_VrabieInstanceStruct *chartInstance, int32_T
  c4_k, real_T c4_A_data[], int32_T c4_A_sizes[2], real_T c4_B_data[], int32_T
  c4_B_sizes, int32_T c4_ldb, real_T c4_C[10], real_T c4_b_C[10])
{
  int32_T c4_i139;
  int32_T c4_b_A_sizes[2];
  int32_T c4_A;
  int32_T c4_b_A;
  int32_T c4_loop_ub;
  int32_T c4_i140;
  real_T c4_b_A_data[1990];
  int32_T c4_b_B_sizes;
  int32_T c4_b_loop_ub;
  int32_T c4_i141;
  real_T c4_b_B_data[199];
  for (c4_i139 = 0; c4_i139 < 10; c4_i139++) {
    c4_b_C[c4_i139] = c4_C[c4_i139];
  }

  c4_b_A_sizes[0] = 10;
  c4_b_A_sizes[1] = c4_A_sizes[1];
  c4_A = c4_b_A_sizes[0];
  c4_b_A = c4_b_A_sizes[1];
  c4_loop_ub = c4_A_sizes[0] * c4_A_sizes[1] - 1;
  for (c4_i140 = 0; c4_i140 <= c4_loop_ub; c4_i140++) {
    c4_b_A_data[c4_i140] = c4_A_data[c4_i140];
  }

  c4_b_B_sizes = c4_B_sizes;
  c4_b_loop_ub = c4_B_sizes - 1;
  for (c4_i141 = 0; c4_i141 <= c4_b_loop_ub; c4_i141++) {
    c4_b_B_data[c4_i141] = c4_B_data[c4_i141];
  }

  c4_c_eml_xgemm(chartInstance, c4_k, c4_b_A_data, c4_b_A_sizes, c4_b_B_data,
                 c4_b_B_sizes, c4_ldb, c4_b_C);
}

static void c4_b_below_threshold(SFc4_VrabieInstanceStruct *chartInstance)
{
  c4_threshold(chartInstance);
}

static real_T c4_norm(SFc4_VrabieInstanceStruct *chartInstance, real_T c4_x[10])
{
  real_T c4_y;
  real_T c4_scale;
  int32_T c4_k;
  int32_T c4_b_k;
  real_T c4_b_x;
  real_T c4_c_x;
  real_T c4_absxk;
  real_T c4_t;
  c4_c_below_threshold(chartInstance);
  c4_y = 0.0;
  c4_realmin(chartInstance);
  c4_scale = 2.2250738585072014E-308;
  c4_eml_switch_helper(chartInstance);
  for (c4_k = 1; c4_k < 11; c4_k++) {
    c4_b_k = c4_k - 1;
    c4_b_x = c4_x[c4_b_k];
    c4_c_x = c4_b_x;
    c4_absxk = muDoubleScalarAbs(c4_c_x);
    if (c4_absxk > c4_scale) {
      c4_t = c4_scale / c4_absxk;
      c4_y = 1.0 + c4_y * c4_t * c4_t;
      c4_scale = c4_absxk;
    } else {
      c4_t = c4_absxk / c4_scale;
      c4_y += c4_t * c4_t;
    }
  }

  return c4_scale * muDoubleScalarSqrt(c4_y);
}

static void c4_c_below_threshold(SFc4_VrabieInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *c4_j_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_VrabieInstanceStruct *chartInstance;
  chartInstance = (SFc4_VrabieInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(int32_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static int32_T c4_o_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int32_T c4_y;
  int32_T c4_i142;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_i142, 1, 6, 0U, 0, 0U, 0);
  c4_y = c4_i142;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_sfEvent;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int32_T c4_y;
  SFc4_VrabieInstanceStruct *chartInstance;
  chartInstance = (SFc4_VrabieInstanceStruct *)chartInstanceVoid;
  c4_b_sfEvent = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_sfEvent),
    &c4_thisId);
  sf_mex_destroy(&c4_b_sfEvent);
  *(int32_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static uint8_T c4_p_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_b_is_active_c4_Vrabie, const char_T *c4_identifier)
{
  uint8_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_q_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c4_b_is_active_c4_Vrabie), &c4_thisId);
  sf_mex_destroy(&c4_b_is_active_c4_Vrabie);
  return c4_y;
}

static uint8_T c4_q_emlrt_marshallIn(SFc4_VrabieInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  uint8_T c4_u4;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_u4, 1, 3, 0U, 0, 0U, 0);
  c4_y = c4_u4;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_b_eml_matlab_zgetrf(SFc4_VrabieInstanceStruct *chartInstance,
  real_T c4_A[100], int32_T c4_ipiv[10], int32_T *c4_info)
{
  int32_T c4_i143;
  int32_T c4_j;
  int32_T c4_b_j;
  int32_T c4_a;
  int32_T c4_b_a;
  int32_T c4_jm1;
  int32_T c4_b;
  int32_T c4_b_b;
  int32_T c4_mmj;
  int32_T c4_c_a;
  int32_T c4_d_a;
  int32_T c4_c;
  int32_T c4_c_b;
  int32_T c4_d_b;
  int32_T c4_jj;
  int32_T c4_e_a;
  int32_T c4_f_a;
  int32_T c4_jp1j;
  int32_T c4_g_a;
  int32_T c4_h_a;
  int32_T c4_b_c;
  int32_T c4_i144;
  real_T c4_b_A[100];
  int32_T c4_i_a;
  int32_T c4_j_a;
  int32_T c4_jpiv_offset;
  int32_T c4_k_a;
  int32_T c4_e_b;
  int32_T c4_l_a;
  int32_T c4_f_b;
  int32_T c4_jpiv;
  int32_T c4_m_a;
  int32_T c4_g_b;
  int32_T c4_n_a;
  int32_T c4_h_b;
  int32_T c4_c_c;
  int32_T c4_i_b;
  int32_T c4_j_b;
  int32_T c4_jrow;
  int32_T c4_o_a;
  int32_T c4_k_b;
  int32_T c4_p_a;
  int32_T c4_l_b;
  int32_T c4_jprow;
  int32_T c4_ix0;
  int32_T c4_iy0;
  int32_T c4_b_ix0;
  int32_T c4_b_iy0;
  int32_T c4_c_ix0;
  int32_T c4_c_iy0;
  int32_T c4_ix;
  int32_T c4_iy;
  int32_T c4_k;
  real_T c4_temp;
  int32_T c4_q_a;
  int32_T c4_r_a;
  int32_T c4_b_jp1j;
  int32_T c4_s_a;
  int32_T c4_t_a;
  int32_T c4_d_c;
  int32_T c4_u_a;
  int32_T c4_m_b;
  int32_T c4_v_a;
  int32_T c4_n_b;
  int32_T c4_i145;
  int32_T c4_w_a;
  int32_T c4_o_b;
  int32_T c4_x_a;
  int32_T c4_p_b;
  boolean_T c4_overflow;
  int32_T c4_b_i;
  int32_T c4_c_i;
  real_T c4_x;
  real_T c4_y;
  real_T c4_b_x;
  real_T c4_b_y;
  real_T c4_z;
  int32_T c4_q_b;
  int32_T c4_r_b;
  int32_T c4_e_c;
  int32_T c4_y_a;
  int32_T c4_ab_a;
  int32_T c4_f_c;
  int32_T c4_bb_a;
  int32_T c4_cb_a;
  int32_T c4_g_c;
  c4_realmin(chartInstance);
  c4_eps(chartInstance);
  for (c4_i143 = 0; c4_i143 < 10; c4_i143++) {
    c4_ipiv[c4_i143] = 1 + c4_i143;
  }

  *c4_info = 0;
  c4_eml_switch_helper(chartInstance);
  for (c4_j = 1; c4_j < 10; c4_j++) {
    c4_b_j = c4_j;
    c4_a = c4_b_j;
    c4_b_a = c4_a - 1;
    c4_jm1 = c4_b_a;
    c4_b = c4_b_j;
    c4_b_b = c4_b;
    c4_mmj = 10 - c4_b_b;
    c4_c_a = c4_jm1;
    c4_d_a = c4_c_a;
    c4_c = c4_d_a * 11;
    c4_c_b = c4_c;
    c4_d_b = c4_c_b + 1;
    c4_jj = c4_d_b;
    c4_e_a = c4_jj;
    c4_f_a = c4_e_a + 1;
    c4_jp1j = c4_f_a;
    c4_g_a = c4_mmj;
    c4_h_a = c4_g_a;
    c4_b_c = c4_h_a;
    for (c4_i144 = 0; c4_i144 < 100; c4_i144++) {
      c4_b_A[c4_i144] = c4_A[c4_i144];
    }

    c4_i_a = c4_eml_ixamax(chartInstance, c4_b_c + 1, c4_b_A, c4_jj);
    c4_j_a = c4_i_a - 1;
    c4_jpiv_offset = c4_j_a;
    c4_k_a = c4_jj;
    c4_e_b = c4_jpiv_offset;
    c4_l_a = c4_k_a;
    c4_f_b = c4_e_b;
    c4_jpiv = c4_l_a + c4_f_b;
    if (c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_jpiv, 1, 100, 1, 0) - 1] != 0.0)
    {
      if (c4_jpiv_offset != 0) {
        c4_m_a = c4_b_j;
        c4_g_b = c4_jpiv_offset;
        c4_n_a = c4_m_a;
        c4_h_b = c4_g_b;
        c4_c_c = c4_n_a + c4_h_b;
        c4_ipiv[c4_b_j - 1] = c4_c_c;
        c4_i_b = c4_jm1;
        c4_j_b = c4_i_b + 1;
        c4_jrow = c4_j_b;
        c4_o_a = c4_jrow;
        c4_k_b = c4_jpiv_offset;
        c4_p_a = c4_o_a;
        c4_l_b = c4_k_b;
        c4_jprow = c4_p_a + c4_l_b;
        c4_ix0 = c4_jrow;
        c4_iy0 = c4_jprow;
        c4_b_ix0 = c4_ix0;
        c4_b_iy0 = c4_iy0;
        c4_b_eml_switch_helper(chartInstance);
        c4_c_ix0 = c4_b_ix0;
        c4_c_iy0 = c4_b_iy0;
        c4_ix = c4_c_ix0;
        c4_iy = c4_c_iy0;
        c4_eml_switch_helper(chartInstance);
        for (c4_k = 1; c4_k < 11; c4_k++) {
          c4_temp = c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_ix, 1, 100, 1, 0) -
            1];
          c4_A[c4_ix - 1] = c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_iy, 1, 100,
            1, 0) - 1];
          c4_A[c4_iy - 1] = c4_temp;
          c4_q_a = c4_ix + 10;
          c4_ix = c4_q_a;
          c4_r_a = c4_iy + 10;
          c4_iy = c4_r_a;
        }
      }

      c4_b_jp1j = c4_jp1j;
      c4_s_a = c4_mmj;
      c4_t_a = c4_s_a;
      c4_d_c = c4_t_a;
      c4_u_a = c4_jp1j;
      c4_m_b = c4_d_c - 1;
      c4_v_a = c4_u_a;
      c4_n_b = c4_m_b;
      c4_i145 = c4_v_a + c4_n_b;
      c4_w_a = c4_b_jp1j;
      c4_o_b = c4_i145;
      c4_x_a = c4_w_a;
      c4_p_b = c4_o_b;
      if (c4_x_a > c4_p_b) {
        c4_overflow = false;
      } else {
        c4_eml_switch_helper(chartInstance);
        c4_eml_switch_helper(chartInstance);
        c4_overflow = (c4_p_b > 2147483646);
      }

      if (c4_overflow) {
        c4_check_forloop_overflow_error(chartInstance, true);
      }

      for (c4_b_i = c4_b_jp1j; c4_b_i <= c4_i145; c4_b_i++) {
        c4_c_i = c4_b_i;
        c4_x = c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_c_i, 1, 100, 1, 0) - 1];
        c4_y = c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_jj, 1, 100, 1, 0) - 1];
        c4_b_x = c4_x;
        c4_b_y = c4_y;
        c4_z = c4_b_x / c4_b_y;
        c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_c_i, 1, 100, 1, 0) - 1] = c4_z;
      }
    } else {
      *c4_info = c4_b_j;
    }

    c4_q_b = c4_b_j;
    c4_r_b = c4_q_b;
    c4_e_c = 10 - c4_r_b;
    c4_y_a = c4_jj;
    c4_ab_a = c4_y_a;
    c4_f_c = c4_ab_a;
    c4_bb_a = c4_jj;
    c4_cb_a = c4_bb_a;
    c4_g_c = c4_cb_a;
    c4_b_eml_xgeru(chartInstance, c4_mmj, c4_e_c, -1.0, c4_jp1j, c4_f_c + 10,
                   c4_A, c4_g_c + 11);
  }

  if (*c4_info == 0) {
    if (!(c4_A[99] != 0.0)) {
      *c4_info = 10;
    }
  }
}

static void c4_b_eml_xgeru(SFc4_VrabieInstanceStruct *chartInstance, int32_T
  c4_m, int32_T c4_n, real_T c4_alpha1, int32_T c4_ix0, int32_T c4_iy0, real_T
  c4_A[100], int32_T c4_ia0)
{
  int32_T c4_b_m;
  int32_T c4_b_n;
  int32_T c4_b_ix0;
  int32_T c4_b_iy0;
  int32_T c4_b_ia0;
  int32_T c4_c_m;
  int32_T c4_c_n;
  int32_T c4_c_ix0;
  int32_T c4_c_iy0;
  int32_T c4_c_ia0;
  int32_T c4_d_m;
  int32_T c4_d_n;
  int32_T c4_d_ix0;
  int32_T c4_d_iy0;
  int32_T c4_d_ia0;
  int32_T c4_e_m;
  int32_T c4_e_n;
  int32_T c4_e_ix0;
  int32_T c4_e_iy0;
  int32_T c4_e_ia0;
  int32_T c4_ixstart;
  int32_T c4_a;
  int32_T c4_jA;
  int32_T c4_jy;
  int32_T c4_f_n;
  int32_T c4_b;
  int32_T c4_b_b;
  int32_T c4_j;
  real_T c4_yjy;
  real_T c4_temp;
  int32_T c4_ix;
  int32_T c4_c_b;
  int32_T c4_i146;
  int32_T c4_b_a;
  int32_T c4_d_b;
  int32_T c4_i147;
  int32_T c4_c_a;
  int32_T c4_e_b;
  int32_T c4_d_a;
  int32_T c4_f_b;
  boolean_T c4_overflow;
  int32_T c4_ijA;
  int32_T c4_b_ijA;
  int32_T c4_e_a;
  int32_T c4_f_a;
  int32_T c4_g_a;
  (void)c4_alpha1;
  c4_b_m = c4_m;
  c4_b_n = c4_n;
  c4_b_ix0 = c4_ix0;
  c4_b_iy0 = c4_iy0;
  c4_b_ia0 = c4_ia0;
  c4_c_m = c4_b_m;
  c4_c_n = c4_b_n;
  c4_c_ix0 = c4_b_ix0;
  c4_c_iy0 = c4_b_iy0;
  c4_c_ia0 = c4_b_ia0;
  c4_d_m = c4_c_m;
  c4_d_n = c4_c_n;
  c4_d_ix0 = c4_c_ix0;
  c4_d_iy0 = c4_c_iy0;
  c4_d_ia0 = c4_c_ia0;
  c4_e_m = c4_d_m;
  c4_e_n = c4_d_n;
  c4_e_ix0 = c4_d_ix0;
  c4_e_iy0 = c4_d_iy0;
  c4_e_ia0 = c4_d_ia0;
  c4_ixstart = c4_e_ix0;
  c4_a = c4_e_ia0 - 1;
  c4_jA = c4_a;
  c4_jy = c4_e_iy0;
  c4_f_n = c4_e_n;
  c4_b = c4_f_n;
  c4_b_b = c4_b;
  if (1 > c4_b_b) {
  } else {
    c4_eml_switch_helper(chartInstance);
    c4_eml_switch_helper(chartInstance);
  }

  for (c4_j = 1; c4_j <= c4_f_n; c4_j++) {
    c4_yjy = c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_jy, 1, 100, 1, 0) - 1];
    if (c4_yjy != 0.0) {
      c4_temp = -c4_yjy;
      c4_ix = c4_ixstart;
      c4_c_b = c4_jA + 1;
      c4_i146 = c4_c_b;
      c4_b_a = c4_e_m;
      c4_d_b = c4_jA;
      c4_i147 = c4_b_a + c4_d_b;
      c4_c_a = c4_i146;
      c4_e_b = c4_i147;
      c4_d_a = c4_c_a;
      c4_f_b = c4_e_b;
      if (c4_d_a > c4_f_b) {
        c4_overflow = false;
      } else {
        c4_eml_switch_helper(chartInstance);
        c4_eml_switch_helper(chartInstance);
        c4_overflow = (c4_f_b > 2147483646);
      }

      if (c4_overflow) {
        c4_check_forloop_overflow_error(chartInstance, true);
      }

      for (c4_ijA = c4_i146; c4_ijA <= c4_i147; c4_ijA++) {
        c4_b_ijA = c4_ijA;
        c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_b_ijA, 1, 100, 1, 0) - 1] =
          c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_b_ijA, 1, 100, 1, 0) - 1] +
          c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", c4_ix, 1, 100, 1, 0) - 1] *
          c4_temp;
        c4_e_a = c4_ix + 1;
        c4_ix = c4_e_a;
      }
    }

    c4_f_a = c4_jy + 10;
    c4_jy = c4_f_a;
    c4_g_a = c4_jA + 10;
    c4_jA = c4_g_a;
  }
}

static void c4_c_eml_xtrsm(SFc4_VrabieInstanceStruct *chartInstance, int32_T
  c4_n, real_T c4_A[100], real_T c4_B_data[], int32_T c4_B_sizes[2])
{
  int32_T c4_b_n;
  int32_T c4_c_n;
  real_T c4_alpha1;
  char_T c4_DIAGA;
  char_T c4_TRANSA;
  char_T c4_UPLO;
  char_T c4_SIDE;
  ptrdiff_t c4_m_t;
  int32_T c4_var;
  ptrdiff_t c4_n_t;
  ptrdiff_t c4_lda_t;
  ptrdiff_t c4_ldb_t;
  double * c4_Aia0_t;
  int32_T c4_iv5[1];
  double * c4_Bib0_t;
  double * c4_alpha1_t;
  (void)chartInstance;
  c4_b_n = c4_n;
  if (c4_b_n < 1) {
  } else {
    c4_c_n = c4_b_n;
    c4_alpha1 = 1.0;
    c4_DIAGA = 'U';
    c4_TRANSA = 'N';
    c4_UPLO = 'L';
    c4_SIDE = 'L';
    c4_m_t = (ptrdiff_t)(10);
    c4_var = c4_c_n;
    c4_n_t = (ptrdiff_t)(c4_var);
    c4_lda_t = (ptrdiff_t)(10);
    c4_ldb_t = (ptrdiff_t)(10);
    c4_Aia0_t = (double *)(&c4_A[0]);
    _SFD_EML_ARRAY_BOUNDS_CHECK("", 1, 1, 10 * c4_B_sizes[1], 1, 0);
    c4_iv5[0] = 10 * c4_B_sizes[1];
    c4_Bib0_t = (double *)(&c4_B_data[0]);
    c4_alpha1_t = (double *)(&c4_alpha1);
    dtrsm(&c4_SIDE, &c4_UPLO, &c4_TRANSA, &c4_DIAGA, &c4_m_t, &c4_n_t,
          c4_alpha1_t, c4_Aia0_t, &c4_lda_t, c4_Bib0_t, &c4_ldb_t);
  }
}

static void c4_d_eml_xtrsm(SFc4_VrabieInstanceStruct *chartInstance, int32_T
  c4_n, real_T c4_A[100], real_T c4_B_data[], int32_T c4_B_sizes[2])
{
  int32_T c4_b_n;
  int32_T c4_c_n;
  real_T c4_alpha1;
  char_T c4_DIAGA;
  char_T c4_TRANSA;
  char_T c4_UPLO;
  char_T c4_SIDE;
  ptrdiff_t c4_m_t;
  int32_T c4_var;
  ptrdiff_t c4_n_t;
  ptrdiff_t c4_lda_t;
  ptrdiff_t c4_ldb_t;
  double * c4_Aia0_t;
  int32_T c4_iv6[1];
  double * c4_Bib0_t;
  double * c4_alpha1_t;
  (void)chartInstance;
  c4_b_n = c4_n;
  if (c4_b_n < 1) {
  } else {
    c4_c_n = c4_b_n;
    c4_alpha1 = 1.0;
    c4_DIAGA = 'N';
    c4_TRANSA = 'N';
    c4_UPLO = 'U';
    c4_SIDE = 'L';
    c4_m_t = (ptrdiff_t)(10);
    c4_var = c4_c_n;
    c4_n_t = (ptrdiff_t)(c4_var);
    c4_lda_t = (ptrdiff_t)(10);
    c4_ldb_t = (ptrdiff_t)(10);
    c4_Aia0_t = (double *)(&c4_A[0]);
    _SFD_EML_ARRAY_BOUNDS_CHECK("", 1, 1, 10 * c4_B_sizes[1], 1, 0);
    c4_iv6[0] = 10 * c4_B_sizes[1];
    c4_Bib0_t = (double *)(&c4_B_data[0]);
    c4_alpha1_t = (double *)(&c4_alpha1);
    dtrsm(&c4_SIDE, &c4_UPLO, &c4_TRANSA, &c4_DIAGA, &c4_m_t, &c4_n_t,
          c4_alpha1_t, c4_Aia0_t, &c4_lda_t, c4_Bib0_t, &c4_ldb_t);
  }
}

static void c4_c_eml_xgemm(SFc4_VrabieInstanceStruct *chartInstance, int32_T
  c4_k, real_T c4_A_data[], int32_T c4_A_sizes[2], real_T c4_B_data[], int32_T
  c4_B_sizes, int32_T c4_ldb, real_T c4_C[10])
{
  int32_T c4_b_k;
  int32_T c4_b_ldb;
  int32_T c4_c_k;
  real_T c4_alpha1;
  int32_T c4_c_ldb;
  real_T c4_beta1;
  char_T c4_TRANSB;
  char_T c4_TRANSA;
  ptrdiff_t c4_m_t;
  ptrdiff_t c4_n_t;
  int32_T c4_var;
  ptrdiff_t c4_k_t;
  ptrdiff_t c4_lda_t;
  int32_T c4_b_var;
  ptrdiff_t c4_ldb_t;
  ptrdiff_t c4_ldc_t;
  double * c4_alpha1_t;
  double * c4_Aia0_t;
  double * c4_Bib0_t;
  double * c4_beta1_t;
  double * c4_Cic0_t;
  c4_b_k = c4_k;
  c4_b_ldb = c4_ldb;
  c4_b_below_threshold(chartInstance);
  if (c4_b_k < 1) {
  } else {
    c4_c_k = c4_b_k;
    c4_alpha1 = 1.0;
    c4_c_ldb = c4_b_ldb;
    c4_beta1 = 0.0;
    c4_TRANSB = 'N';
    c4_TRANSA = 'N';
    c4_m_t = (ptrdiff_t)(10);
    c4_n_t = (ptrdiff_t)(1);
    c4_var = c4_c_k;
    c4_k_t = (ptrdiff_t)(c4_var);
    c4_lda_t = (ptrdiff_t)(10);
    c4_b_var = c4_c_ldb;
    c4_ldb_t = (ptrdiff_t)(c4_b_var);
    c4_ldc_t = (ptrdiff_t)(10);
    c4_alpha1_t = (double *)(&c4_alpha1);
    _SFD_EML_ARRAY_BOUNDS_CHECK("", 1, 1, 10 * c4_A_sizes[1], 1, 0);
    c4_Aia0_t = (double *)(&c4_A_data[0]);
    _SFD_EML_ARRAY_BOUNDS_CHECK("", 1, 1, c4_B_sizes, 1, 0);
    c4_Bib0_t = (double *)(&c4_B_data[0]);
    c4_beta1_t = (double *)(&c4_beta1);
    c4_Cic0_t = (double *)(&c4_C[0]);
    dgemm(&c4_TRANSA, &c4_TRANSB, &c4_m_t, &c4_n_t, &c4_k_t, c4_alpha1_t,
          c4_Aia0_t, &c4_lda_t, c4_Bib0_t, &c4_ldb_t, c4_beta1_t, c4_Cic0_t,
          &c4_ldc_t);
  }
}

static void init_dsm_address_info(SFc4_VrabieInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc4_VrabieInstanceStruct *chartInstance)
{
  chartInstance->c4_i = (uint8_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    0);
  chartInstance->c4_d = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    1);
  chartInstance->c4_PP = (real_T (*)[16])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c4_x_bar_delta = (real_T (*)[10])ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c4_N = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    3);
  chartInstance->c4_start = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c4_Vrabie_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1802178591U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2137373189U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1143935507U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(622630814U);
}

mxArray* sf_c4_Vrabie_get_post_codegen_info(void);
mxArray *sf_c4_Vrabie_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("8BnMciVxBeBs4StNrVlTpG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(10);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(4);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c4_Vrabie_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c4_Vrabie_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c4_Vrabie_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "incompatibleSymbol", };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 3, infoFields);
  mxArray *fallbackReason = mxCreateString("feature_off");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxArray *fallbackType = mxCreateString("early");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c4_Vrabie_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c4_Vrabie_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c4_Vrabie(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x7'type','srcId','name','auxInfo'{{M[1],M[9],T\"PP\",},{M[4],M[0],T\"P\",S'l','i','p'{{M1x2[62 63],M[0],}}},{M[4],M[0],T\"X\",S'l','i','p'{{M1x2[58 59],M[0],}}},{M[4],M[0],T\"Y\",S'l','i','p'{{M1x2[60 61],M[0],}}},{M[4],M[0],T\"has_converged\",S'l','i','p'{{M1x2[68 81],M[0],}}},{M[4],M[0],T\"p_1\",S'l','i','p'{{M1x2[64 67],M[0],}}},{M[8],M[0],T\"is_active_c4_Vrabie\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 7, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c4_Vrabie_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc4_VrabieInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc4_VrabieInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _VrabieMachineNumber_,
           4,
           1,
           1,
           0,
           6,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_VrabieMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_VrabieMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _VrabieMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"i");
          _SFD_SET_DATA_PROPS(1,1,1,0,"d");
          _SFD_SET_DATA_PROPS(2,2,0,1,"PP");
          _SFD_SET_DATA_PROPS(3,1,1,0,"x_bar_delta");
          _SFD_SET_DATA_PROPS(4,1,1,0,"N");
          _SFD_SET_DATA_PROPS(5,1,1,0,"start");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,12,0,4,0,0,0,4,2);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,993);
        _SFD_CV_INIT_EML_SATURATION(0,1,0,614,-1,617);
        _SFD_CV_INIT_EML_SATURATION(0,1,1,614,-1,623);
        _SFD_CV_INIT_EML_SATURATION(0,1,2,649,-1,652);
        _SFD_CV_INIT_EML_SATURATION(0,1,3,649,-1,658);
        _SFD_CV_INIT_EML_IF(0,1,0,82,92,-1,138);
        _SFD_CV_INIT_EML_IF(0,1,1,139,151,-1,197);
        _SFD_CV_INIT_EML_IF(0,1,2,198,212,-1,278);
        _SFD_CV_INIT_EML_IF(0,1,3,279,292,-1,325);
        _SFD_CV_INIT_EML_IF(0,1,4,326,339,-1,370);
        _SFD_CV_INIT_EML_IF(0,1,5,371,384,-1,408);
        _SFD_CV_INIT_EML_IF(0,1,6,409,424,-1,451);
        _SFD_CV_INIT_EML_IF(0,1,7,452,477,-1,508);
        _SFD_CV_INIT_EML_IF(0,1,8,510,519,575,604);
        _SFD_CV_INIT_EML_IF(0,1,9,575,604,-1,604);
        _SFD_CV_INIT_EML_IF(0,1,10,670,707,-1,972);
        _SFD_CV_INIT_EML_IF(0,1,11,768,781,-1,819);

        {
          static int condStart[] = { 582, 596 };

          static int condEnd[] = { 592, 604 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,582,604,2,0,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 673, 685 };

          static int condEnd[] = { 681, 707 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,1,673,707,2,2,&(condStart[0]),&(condEnd[0]),
                                3,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML_RELATIONAL(0,1,0,85,92,-1,4);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,1,142,151,-1,2);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,2,201,212,-1,2);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,3,513,519,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,4,582,592,-1,5);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,5,596,604,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,6,673,681,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,8,771,781,-1,2);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_i_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_g_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_f_sf_marshallOut,(MexInFcnForType)
            c4_f_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 10;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_h_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_g_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_g_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c4_i);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c4_d);
        _SFD_SET_DATA_VALUE_PTR(2U, *chartInstance->c4_PP);
        _SFD_SET_DATA_VALUE_PTR(3U, *chartInstance->c4_x_bar_delta);
        _SFD_SET_DATA_VALUE_PTR(4U, chartInstance->c4_N);
        _SFD_SET_DATA_VALUE_PTR(5U, chartInstance->c4_start);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _VrabieMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "fmtnoCCFRT4vO0j4kIKgkG";
}

static void sf_opaque_initialize_c4_Vrabie(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc4_VrabieInstanceStruct*) chartInstanceVar)->S,
    0);
  initialize_params_c4_Vrabie((SFc4_VrabieInstanceStruct*) chartInstanceVar);
  initialize_c4_Vrabie((SFc4_VrabieInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c4_Vrabie(void *chartInstanceVar)
{
  enable_c4_Vrabie((SFc4_VrabieInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c4_Vrabie(void *chartInstanceVar)
{
  disable_c4_Vrabie((SFc4_VrabieInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c4_Vrabie(void *chartInstanceVar)
{
  sf_gateway_c4_Vrabie((SFc4_VrabieInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c4_Vrabie(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c4_Vrabie((SFc4_VrabieInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c4_Vrabie(SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c4_Vrabie((SFc4_VrabieInstanceStruct*)chartInfo->chartInstance,
    st);
}

static void sf_opaque_terminate_c4_Vrabie(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc4_VrabieInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Vrabie_optimization_info();
    }

    finalize_c4_Vrabie((SFc4_VrabieInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc4_Vrabie((SFc4_VrabieInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c4_Vrabie(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c4_Vrabie((SFc4_VrabieInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c4_Vrabie(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Vrabie_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,4);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,4,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,4,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,4);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,4,5);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,4,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 5; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,4);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3007414022U));
  ssSetChecksum1(S,(3938287828U));
  ssSetChecksum2(S,(113412935U));
  ssSetChecksum3(S,(81498072U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c4_Vrabie(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c4_Vrabie(SimStruct *S)
{
  SFc4_VrabieInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc4_VrabieInstanceStruct *)utMalloc(sizeof
    (SFc4_VrabieInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc4_VrabieInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c4_Vrabie;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c4_Vrabie;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c4_Vrabie;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c4_Vrabie;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c4_Vrabie;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c4_Vrabie;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c4_Vrabie;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c4_Vrabie;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c4_Vrabie;
  chartInstance->chartInfo.mdlStart = mdlStart_c4_Vrabie;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c4_Vrabie;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->checksum = SF_RUNTIME_INFO_CHECKSUM;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  crtInfo->compiledInfo = NULL;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c4_Vrabie_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c4_Vrabie(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c4_Vrabie(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c4_Vrabie(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c4_Vrabie_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
