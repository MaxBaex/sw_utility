/**
 * @file    General_Const.h
 * @brief   New Vario
 * @author  Horst Rupp
 * @brief   Constants relevant to any application
 */
//
// ****************************************************************************
//

#ifndef  __General_Const_h
  #define  __General_Const_h

  #define   my_break_point    asm("bkpt 0")

  // ***************************************************************************
  //

  #define   c_small_buffer_size                 80
  #define   c_big_buffer_size                   150

  #define   c_CR                                13
  #define   c_LF                                10

  #define   TRUE                                1
  //#define   true                                TRUE
  #define   FALSE                               ~TRUE
  //#define   false                               FALSE

  #define   c_status_failed                     0
  #define   c_status_success                    1

  #define   IsSet                               1
  #define   IsUnSet                             0
  #define   IsNotSet                            0

  #define   GPIO_PIN_HIGH                       GPIO_PIN_SET
  #define   GPIO_PIN_LOW                        GPIO_PIN_RESET



  //
  // ***************************************************************************
  //
  //  constants for physics and math
  //
  #define    c_Pi_180Grad                   3.14159265359F
  #define    c_2Pi_360Grad                  ( 2.0 * c_Pi_180Grad )

  #define    c_PiD4_45Grad                  ( c_Pi_180Grad / 4.0 )
  #define    c_PiD2_90Grad                  ( c_Pi_180Grad / 2.0 )

  #define    c_Rad_for_45Grad               ( c_Pi_180Grad / 4.0 )
  #define    c_Rad_for_90Grad               ( c_Pi_180Grad / 2.0 )
  #define    c_Rad_for_180Grad              ( c_Pi_180Grad )
  #define    c_Rad_for_270Grad              ( c_Rad_for_180Grad + c_Rad_for_90Grad )
  #define    c_Rad_for_360Grad              ( 2.0 * c_Pi_180Grad  )


  #define    c_Limit                        1e-9F
  #define    c_1D60                         1.0 / 60.0
  #define    c_1D3600                       1.0 / 3600.0
  #define    c_Radian_per_Degree            ( c_Pi_180Grad / 180.0 )
  #define    c_Degree_per_Radian            ( 180.0 / c_Pi_180Grad )
  #define    c_Jota                         ( 0.1 * c_Radian_per_Degree )

  #define    c_Radius_Earth                 6371.0F                         /* km */
  #define    c_Circumference_Earth          ( c_Radius_Earth * c_2Pi_360Grad )      /* km */
  #define    c_MeridianDistance_per_Degree  ( c_Circumference_Earth / 360.0 )/* km */
  #define    c_MeridianDistance_per_Radian  c_Radius_Earth                  /* km */

  #define    c_Meter_per_Feet               0.3048F                         /* m */
  #define    c_km_per_nm                    1.852F                          /* km */

  #define    c_mbar_per psi                 68.94757F                       /* mbar == hPa */

  #define    c_Rho_NN                       1.225F                          /* kg / m**3 */
  #define    c_QNH_NN                       1013.25F                        /* hPa */
  #define    c_ISA_Temp_NN                  15.0F                           /* °C */
  #define    c_Zero_Deg_C_in_K              273.13F                         /* °K */
  #define    c_ISA_TempGradient             0.0065F                         /* °/m */
  #define    c_TempStep_Per_Deg             36.576F                         /* m/° */
  #define    c_Rd                           287.0F                          /* J / ( kg * °K ) Gaskonstante */
  #define    c_Gravitation                  9.8063F                         /* m / sec**2 */

  //#define   l_TC_CAN_Bus_Receiver           10



#endif

//
// ****************************************************************************
// The End
// ****************************************************************************
