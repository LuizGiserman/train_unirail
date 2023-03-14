/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: CONTROLADOR.c
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

#include "CONTROLADOR.h"
#include "rtwtypes.h"
#include "CONTROLADOR_private.h"

/* Block signals (default storage) */
B_CONTROLADOR_T CONTROLADOR_B;

/* Continuous states */
X_CONTROLADOR_T CONTROLADOR_X;

/* External inputs (root inport signals with default storage) */
ExtU_CONTROLADOR_T CONTROLADOR_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_CONTROLADOR_T CONTROLADOR_Y;

/* Real-time model */
static RT_MODEL_CONTROLADOR_T CONTROLADOR_M_;
RT_MODEL_CONTROLADOR_T *const CONTROLADOR_M = &CONTROLADOR_M_;

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  CONTROLADOR_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void CONTROLADOR_step(void)
{
  real_T rtb_Sum1;
  real_T x;
  if (rtmIsMajorTimeStep(CONTROLADOR_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&CONTROLADOR_M->solverInfo,
                          ((CONTROLADOR_M->Timing.clockTick0+1)*
      CONTROLADOR_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(CONTROLADOR_M)) {
    CONTROLADOR_M->Timing.t[0] = rtsiGetT(&CONTROLADOR_M->solverInfo);
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Gain: '<Root>/Gain'
   *  Gain: '<Root>/Gain1'
   *  Integrator: '<Root>/Integrator'
   *  Integrator: '<Root>/Integrator1'
   */
  rtb_Sum1 = CONTROLADOR_P.Ki * CONTROLADOR_X.Integrator_CSTATE -
    CONTROLADOR_P.Kx * CONTROLADOR_X.Integrator1_CSTATE;

  /* Saturate: '<Root>/Saturation' */
  if (rtb_Sum1 > CONTROLADOR_P.Saturation_UpperSat) {
    /* Saturate: '<Root>/Saturation' */
    CONTROLADOR_Y.Vitesse_Envoyer = CONTROLADOR_P.Saturation_UpperSat;
  } else if (rtb_Sum1 < CONTROLADOR_P.Saturation_LowerSat) {
    /* Saturate: '<Root>/Saturation' */
    CONTROLADOR_Y.Vitesse_Envoyer = CONTROLADOR_P.Saturation_LowerSat;
  } else {
    /* Saturate: '<Root>/Saturation' */
    CONTROLADOR_Y.Vitesse_Envoyer = rtb_Sum1;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Inport: '<Root>/Posiciton_souhaite'
   *  Inport: '<Root>/Posiction_actuelle '
   *  Inport: '<Root>/Vitesse_Consigne'
   */
  x = CONTROLADOR_U.Posiciton_souhaite - CONTROLADOR_U.Posiction_actuelle;
  if (x <= 1.0604200000000001) {
    x = 0.0;
  } else if ((x > 1.0604200000000001) && (x <= 62.6042)) {
    x = (((x * x - 10.0 * x) - 112.44905764) + 626.042) *
      CONTROLADOR_U.Vitesse_Consigne / 3919.2858576400004;
  } else if (CONTROLADOR_U.Posiction_actuelle <= 31.1042) {
    x = ((CONTROLADOR_U.Posiction_actuelle * CONTROLADOR_U.Posiction_actuelle +
          5.0 * CONTROLADOR_U.Posiction_actuelle) + 112.44905764) *
      CONTROLADOR_U.Vitesse_Consigne / 1235.44131528;
  } else {
    x = CONTROLADOR_U.Vitesse_Consigne;
  }

  /* End of MATLAB Function: '<Root>/MATLAB Function' */

  /* Sum: '<Root>/Sum' incorporates:
   *  Gain: '<Root>/Gain6'
   *  Inport: '<Root>/Vitesse_Reele'
   *  Sum: '<Root>/Sum4'
   */
  CONTROLADOR_B.Sum = ((CONTROLADOR_Y.Vitesse_Envoyer - rtb_Sum1) *
                       CONTROLADOR_P.Ki + x) - CONTROLADOR_U.Vitesse_Reele;

  /* Sum: '<Root>/Sum2' incorporates:
   *  Gain: '<Root>/Gain2'
   *  Gain: '<Root>/Gain3'
   *  Gain: '<Root>/Gain4'
   *  Gain: '<Root>/Gain5'
   *  Inport: '<Root>/Vitesse_Reele'
   *  Integrator: '<Root>/Integrator1'
   *  Sum: '<Root>/Sum3'
   */
  CONTROLADOR_B.Sum2 = ((CONTROLADOR_U.Vitesse_Reele - CONTROLADOR_P.C *
    CONTROLADOR_X.Integrator1_CSTATE) * CONTROLADOR_P.L + CONTROLADOR_P.B *
                        CONTROLADOR_Y.Vitesse_Envoyer) + CONTROLADOR_P.A *
    CONTROLADOR_X.Integrator1_CSTATE;
  if (rtmIsMajorTimeStep(CONTROLADOR_M)) {
    rt_ertODEUpdateContinuousStates(&CONTROLADOR_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++CONTROLADOR_M->Timing.clockTick0;
    CONTROLADOR_M->Timing.t[0] = rtsiGetSolverStopTime
      (&CONTROLADOR_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.015s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.015, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      CONTROLADOR_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void CONTROLADOR_derivatives(void)
{
  XDot_CONTROLADOR_T *_rtXdot;
  _rtXdot = ((XDot_CONTROLADOR_T *) CONTROLADOR_M->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = CONTROLADOR_B.Sum;

  /* Derivatives for Integrator: '<Root>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = CONTROLADOR_B.Sum2;
}

/* Model initialize function */
void CONTROLADOR_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&CONTROLADOR_M->solverInfo,
                          &CONTROLADOR_M->Timing.simTimeStep);
    rtsiSetTPtr(&CONTROLADOR_M->solverInfo, &rtmGetTPtr(CONTROLADOR_M));
    rtsiSetStepSizePtr(&CONTROLADOR_M->solverInfo,
                       &CONTROLADOR_M->Timing.stepSize0);
    rtsiSetdXPtr(&CONTROLADOR_M->solverInfo, &CONTROLADOR_M->derivs);
    rtsiSetContStatesPtr(&CONTROLADOR_M->solverInfo, (real_T **)
                         &CONTROLADOR_M->contStates);
    rtsiSetNumContStatesPtr(&CONTROLADOR_M->solverInfo,
      &CONTROLADOR_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&CONTROLADOR_M->solverInfo,
      &CONTROLADOR_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&CONTROLADOR_M->solverInfo,
      &CONTROLADOR_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&CONTROLADOR_M->solverInfo,
      &CONTROLADOR_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&CONTROLADOR_M->solverInfo, (&rtmGetErrorStatus
      (CONTROLADOR_M)));
    rtsiSetRTModelPtr(&CONTROLADOR_M->solverInfo, CONTROLADOR_M);
  }

  rtsiSetSimTimeStep(&CONTROLADOR_M->solverInfo, MAJOR_TIME_STEP);
  CONTROLADOR_M->intgData.f[0] = CONTROLADOR_M->odeF[0];
  CONTROLADOR_M->contStates = ((X_CONTROLADOR_T *) &CONTROLADOR_X);
  rtsiSetSolverData(&CONTROLADOR_M->solverInfo, (void *)&CONTROLADOR_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&CONTROLADOR_M->solverInfo, false);
  rtsiSetSolverName(&CONTROLADOR_M->solverInfo,"ode1");
  rtmSetTPtr(CONTROLADOR_M, &CONTROLADOR_M->Timing.tArray[0]);
  CONTROLADOR_M->Timing.stepSize0 = 0.015;

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  CONTROLADOR_X.Integrator_CSTATE = CONTROLADOR_P.Integrator_IC;

  /* InitializeConditions for Integrator: '<Root>/Integrator1' */
  CONTROLADOR_X.Integrator1_CSTATE = CONTROLADOR_P.Integrator1_IC;
}

/* Model terminate function */
void CONTROLADOR_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
