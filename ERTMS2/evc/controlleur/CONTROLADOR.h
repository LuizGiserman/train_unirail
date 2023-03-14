/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: CONTROLADOR.h
 *
 * Code generated for Simulink model 'CONTROLADOR'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Tue Mar 14 18:12:02 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_CONTROLADOR_h_
#define RTW_HEADER_CONTROLADOR_h_
#ifndef CONTROLADOR_COMMON_INCLUDES_
#define CONTROLADOR_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* CONTROLADOR_COMMON_INCLUDES_ */

#include "CONTROLADOR_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Sum;                          /* '<Root>/Sum' */
  real_T Sum2;                         /* '<Root>/Sum2' */
} B_CONTROLADOR_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<Root>/Integrator1' */
} X_CONTROLADOR_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T Integrator1_CSTATE;           /* '<Root>/Integrator1' */
} XDot_CONTROLADOR_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<Root>/Integrator' */
  boolean_T Integrator1_CSTATE;        /* '<Root>/Integrator1' */
} XDis_CONTROLADOR_T;

#ifndef ODE1_INTG
#define ODE1_INTG

/* ODE1 Integration Data */
typedef struct {
  real_T *f[1];                        /* derivatives */
} ODE1_IntgData;

#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Vitesse_Consigne;             /* '<Root>/Vitesse_Consigne' */
  real_T Posiction_actuelle;           /* '<Root>/Posiction_actuelle ' */
  real_T Posiciton_souhaite;           /* '<Root>/Posiciton_souhaite' */
  real_T Vitesse_Reele;                /* '<Root>/Vitesse_Reele' */
} ExtU_CONTROLADOR_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Vitesse_Envoyer;              /* '<Root>/Vitesse_Envoyer' */
} ExtY_CONTROLADOR_T;

/* Parameters (default storage) */
struct P_CONTROLADOR_T_ {
  real_T A;                            /* Variable: A
                                        * Referenced by: '<Root>/Gain3'
                                        */
  real_T B;                            /* Variable: B
                                        * Referenced by: '<Root>/Gain2'
                                        */
  real_T C;                            /* Variable: C
                                        * Referenced by: '<Root>/Gain4'
                                        */
  real_T Ki;                           /* Variable: Ki
                                        * Referenced by:
                                        *   '<Root>/Gain'
                                        *   '<Root>/Gain6'
                                        */
  real_T Kx;                           /* Variable: Kx
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real_T L;                            /* Variable: L
                                        * Referenced by: '<Root>/Gain5'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<Root>/Integrator'
                                        */
  real_T Integrator1_IC;               /* Expression: 0
                                        * Referenced by: '<Root>/Integrator1'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 50
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -50
                                        * Referenced by: '<Root>/Saturation'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_CONTROLADOR_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_CONTROLADOR_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_CONTROLADOR_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeF[1][2];
  ODE1_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_CONTROLADOR_T CONTROLADOR_P;

/* Block signals (default storage) */
extern B_CONTROLADOR_T CONTROLADOR_B;

/* Continuous states (default storage) */
extern X_CONTROLADOR_T CONTROLADOR_X;

/* External inputs (root inport signals with default storage) */
extern ExtU_CONTROLADOR_T CONTROLADOR_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_CONTROLADOR_T CONTROLADOR_Y;

/* Model entry point functions */
extern void CONTROLADOR_initialize(void);
extern void CONTROLADOR_step(void);
extern void CONTROLADOR_terminate(void);

/* Real-time Model object */
extern RT_MODEL_CONTROLADOR_T *const CONTROLADOR_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'CONTROLADOR'
 * '<S1>'   : 'CONTROLADOR/MATLAB Function'
 */
#endif                                 /* RTW_HEADER_CONTROLADOR_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
