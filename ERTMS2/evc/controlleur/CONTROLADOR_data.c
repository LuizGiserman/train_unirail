/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: CONTROLADOR_data.c
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

/* Block parameters (default storage) */
P_CONTROLADOR_T CONTROLADOR_P = {
  /* Variable: A
   * Referenced by: '<Root>/Gain3'
   */
  -5.0706437649769773,

  /* Variable: B
   * Referenced by: '<Root>/Gain2'
   */
  5.0668697690916673,

  /* Variable: C
   * Referenced by: '<Root>/Gain4'
   */
  1.0,

  /* Variable: Ki
   * Referenced by:
   *   '<Root>/Gain'
   *   '<Root>/Gain6'
   */
  8.2891414056473529,

  /* Variable: Kx
   * Referenced by: '<Root>/Gain1'
   */
  1.5649417878061223,

  /* Variable: L
   * Referenced by: '<Root>/Gain5'
   */
  8.9293562350230218,

  /* Expression: 0
   * Referenced by: '<Root>/Integrator'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Integrator1'
   */
  0.0,

  /* Expression: 50
   * Referenced by: '<Root>/Saturation'
   */
  50.0,

  /* Expression: -50
   * Referenced by: '<Root>/Saturation'
   */
  -50.0
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
