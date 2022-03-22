/**
  * ###########################################################################
  * @file     Physics.h
  * @brief    New Vario
  * @author   Horst Rupp 
  * @brief    Header for library containing routines dealing with 
  *           physics and aerodynamics 
  *
  * @brief    This is a re-write of a lib from 10.06.2009
  *
  * ###########################################################################
  */

//
// ****************************************************************************
//
#include  <inttypes.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>

// ****************************************************************************

  #ifdef __cplusplus
    extern "C" {
  #endif

    float   FL_at               ( float AmbPressure );
    float   PressureAltitude_at ( float AmbPressure, float RefPressure );
    float   ISA_Temperature_at  ( int PressureAltitude );
    float   DensityAltitude_at  ( int PressureAltitude, float AltStep, float RefPressure, float OAT );
    float   Density_at          ( float AmbPressure, float OAT );
    int16_t IAS_at              ( float PitotPressure );
    int16_t TAS_at              ( int16_t CAS, float AmbDensity );
    float   QFF_at              ( int32_t Altitude, float OAT, float AmbPressure, float Latitude_in_Rad );
    float   QNH_at              ( int32_t Altitude, float AmbPressure, float Latitude_in_Rad );

  #ifdef __cplusplus
  }
  #endif

// ****************************************************************************
// Ende
// ****************************************************************************
