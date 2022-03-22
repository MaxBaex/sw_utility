/**
 * @file    Generic_Const.h
 * @brief   New Vario
 * @author  Horst Rupp
 * @brief   Constants relevant to application
 */
//
// ****************************************************************************
//

#ifndef  __Generic_Const_h
  #define  __Generic_Const_h

#include  "System_Configuration.h"
//#include  "ff.h"

#ifdef  BUILD_VARIO
  #include  "NV_CAN_Ids.h"
#endif

#if ( defined BUILD_VARIO ) || ( defined BUILD_BOOTLOADER )
  // ***************************************************************************
  //  !!!!!!!!!!!!! Constants relevant to screen output !!!!!!!!!!!!!!!
  // ***************************************************************************
  //
  //  defining visible area / not covered by rim
  //
  #define   c_origin_x      0
  #define   c_origin_y      0

  #define   c_canvas_width  (int16_t)LCD_AVAIL_WIDTH_PORTRAIT     // total width 0-227
  #define   c_canvas_height (int16_t)LCD_AVAIL_HEIGHT_PORTRAIT    // total height 0-285

  #define   c_left_most_x   c_origin_x                   // left boundary
  #define   c_tops_most_y   c_origin_y                   // top boundary

  #define   c_rite_most_x   c_origin_x + c_canvas_width - 1   // right boundary
  #define   c_btms_most_y   c_origin_y + c_canvas_height - 1  // bottom boundary

  #define   c_canvas_half_width   (int16_t)( c_canvas_width / 2 )      // half width
  #define   c_canvas_half_height  (int16_t)( c_canvas_height / 2 )     // half height

  #define   c_center_x      ( c_origin_x + c_canvas_half_width )  // horizontal mid point
  #define   c_center_y      ( c_origin_y + c_canvas_half_height ) // vertical mid point

  // ***************************************************************************
  //
  //  constants pertaining to the menue page and all box images
  //
  #define   c_max_no_menue_lines  10  //  no of lines on menue pages

  #define   c_char_offset_x   2   //  offset of char output from left box border
  #define   c_char_offset_y   3   //  offset of char output from top box border

  // ***************************************************************************
  //
  //  constants pertaining to all box fields
  //
  //  Explanation field
  //
  #define   c_no_of_explanation_lines   2
  #define   c_size_Explanation          21
  #define   c_explanation_x_offset      2
  #define   c_explanation_y_offset      239
  #define   c_explanation_width         ( c_canvas_width - 2 * c_explanation_x_offset )

  //  Menue and vario line layout
  //
  #define   c_size_TextWholeLine        27
  #define   c_size_TextLeft             17
  #define   c_size_TextShort            11
  #define   c_size_TextValue            11
  #define   c_size_TextUnits            8

  //  Anchor position in field
  //
  enum
  {
    c_center,
    c_ulc,
    c_umid,
    c_urc,
    c_left_half_height,
    c_rite_half_height
  };

  //  Alignment of char string in the box
  //
  enum
  {
    c_left_aligned,
    c_center_aligned,
    c_rite_aligned,
  };

  //  Return value selection from DISPLAY routines
  //
  #define   c_Ret_BoxHeight           0
  #define   c_Ret_BoxWidth            1
  #define   c_Ret_PixWidth            2

  //  Rim color suppression
  //
  #define   c_RimColour_Showing       0
  #define   c_RimColour_Suppressed    1

  // ***************************************************************************
  //
  //  constants pertaining to the vario page
  //
  #define   c_radius_vario_scale      c_canvas_half_height
  #define   c_circle_center_x         c_canvas_half_height + 1
  #define   c_marker_width            3
  #define   c_long_scale_mark         9
  #define   c_small_scale_mark        5

  #define   c_scale_width             42

  #define   c_Scale_Resolution        100
  #define   c_FSDEG                   125   // Half scale angle in degrees

  //
  //  boxes at the center of the vario rim
  //
  #define   c_rite_variobox           c_rite_most_x
  #define   c_left_variobox           ( c_circle_center_x - 53 )

  #define   c_variobox_width          c_rite_variobox - c_left_variobox

  #define   c_top_variobox            73

  #define   c_course_offset_x         58
  #define   c_upper_course_offset_y   52
  #define   c_lower_course_offset_y   38
  #define   c_arrow_offset_x          70
  #define   c_arrow_offset_y          19
  #define   c_arrow_height            28
  #define   c_arrow_width             20

  #define   c_max_no_vario_fields     6

  #define   c_max_no_of_vario_field_options   43

  #define   c_time_offset_x           c_canvas_half_width - 12
  #define   c_time_offset_y           c_canvas_half_height + 74

  #define   c_heading_offset_x        c_left_variobox + 29
  #define   c_heading_offset_y        c_top_variobox - 25

  #define   c_cgmode_circle_offset_x  c_left_variobox + 15
  #define   c_cgmode_circle_offset_y  c_top_variobox - 10
  #define   c_cgmode_circle_radius    5

  #define   c_cgmode_UL_dwn_offset_x  c_cgmode_circle_offset_x - c_cgmode_circle_radius
  #define   c_cgmode_UL_dwn_offset_y  c_cgmode_circle_offset_y - c_cgmode_circle_radius
  #define   c_cgmode_LR_dwn_offset_x  c_cgmode_circle_offset_x + c_cgmode_circle_radius
  #define   c_cgmode_LR_dwn_offset_y  c_cgmode_circle_offset_y + c_cgmode_circle_radius

  #define   c_cgmode_UL_up_offset_x   c_cgmode_circle_offset_x - c_cgmode_circle_radius
  #define   c_cgmode_UL_up_offset_y   c_cgmode_circle_offset_y + c_cgmode_circle_radius
  #define   c_cgmode_LR_up_offset_x   c_cgmode_circle_offset_x + c_cgmode_circle_radius
  #define   c_cgmode_LR_up_offset_y   c_cgmode_circle_offset_y - c_cgmode_circle_radius

  #define   c_cgmode_UL_lvl_offset_x  c_cgmode_circle_offset_x - c_cgmode_circle_radius
  #define   c_cgmode_UL_lvl_offset_y  c_cgmode_circle_offset_y
  #define   c_cgmode_LR_lvl_offset_x  c_cgmode_circle_offset_x + c_cgmode_circle_radius
  #define   c_cgmode_LR_lvl_offset_y  c_cgmode_circle_offset_y

  #define   c_ball_radius             30
  #define   c_ball_offset             (int16_t)( c_ball_radius / 2 + 5 )
  #define   c_upper_ball_offset_y     c_ball_offset
  #define   c_lower_ball_offset_y     c_btms_most_y - c_ball_offset

  #define   c_step_exp                0.0001F

  // ***************************************************************************
  //
  //  constants specific to horizon page
  //
  #define   c_max_pitch_in_Degrees    50
  #define   c_max_roll_in_Degrees     90


  #define   c_horizontal_box_height   20
  #define   c_horizontal_box_width    c_canvas_width

  #define   c_vertical_box_width      37
  #define   c_vertical_box_height     c_canvas_height

  #define   c_triangle_width          20
  #define   c_triangle_height_half    9

  //  the inner horizon area
  //
  #define   c_horizon_width           c_canvas_width
  #define   c_horizon_half_width      (int16_t)( c_horizon_width / 2 )
  #define   c_horizon_height          c_canvas_width
  #define   c_horizon_half_height     (int16_t)( c_horizon_height / 2 )

  #define   c_left_boundary           c_center_x - c_horizon_half_width
  #define   c_upp_boundary            c_center_y - c_horizon_half_height + 1

  #define   c_rite_boundary           c_center_x + c_horizon_half_width
  #define   c_low_boundary            c_center_y + c_horizon_half_height

  #define   c_radius_horizon          c_horizon_half_width

  #define   c_wing_span_half          (int16_t)( c_center_x / 2 )

  #define   c_no_intersection         0
  #define   c_floor_intersect         1
  #define   c_cieling_intersect       2


  //
  // ***************************************************************************
  //
  //  constants in relation to turn indicator page
  //
  #define c_xx      5
  #define c_radius  175
  #define c_spread  1.7


  //
  // ***************************************************************************
  //  constants in relation to font sizes
  //
  #define   c_box_Font26_height       27
  #define   c_box_Font20_height       23

  #define   c_Pitch20                 20
  #define   c_Pitch26                 26
  // ***************************************************************************
  //
  //  Error Messages
  //  The error messages proper are here : --- ErrorMsgTranslator
  //
  enum  {
        c_EC_MMI_0,
        c_EC_MMI_1,
        c_EC_MMI_2,
        c_EC_MMI_3,
        c_EC_MMI_4,
        c_EC_MMI_5,
        c_EC_MMI_6,
        c_EC_MMI_7,
        c_EC_MMI_8,
        c_EC_MMI_9,
        c_EC_RAW_0,
        c_EC_PNV_0,
        c_EC_PNV_1,
        c_EC_CFG_0,
        cError3,
        cError4,
        cError5,
        cError6,
        cError7,
        //
        c_Max_No_Of_Error_Messages
      };

  // ***************************************************************************
  //
  //  constants for program navigation
  //
  #define  c_max_no_programs              17
  #define  c_max_no_of_fields_in_program  20

  // ***************************************************************************
  //
  //  Field types (each type requires specific dedicated treatment
  //  at increase and/or decrease)
  //
  enum  {
        c_FT_Menue,
        c_FT_Int32,
        c_FT_Int16,
        c_FT_Int8,
        c_FT_Float,
        c_FT_Text,
        c_FT_Hex,
        c_FT_Version,
        c_FT_Date_Time,
        c_FT_Wind,
        c_FT_PlaneType,
        c_FT_Field_Sel,
        c_FT_LatCoordinate,
        c_FT_LonCoordinate,
        c_FT_Frequency,
        //
        c_Max_Field_Types
      };
#endif

#if ( defined BUILD_VARIO ) || ( defined BUILD_AUDIO )
  // ***************************************************************************
  //
  //  constants for flsh control
  //
  #define  c_FlashOneBit1       0
  #define  c_FlashOneBit2       1
  #define  c_FlashPattern1      2
  #define  c_FlashPattern2      3
  #define  c_FlashPatternBoth   4
  #define  c_FlashPatternInvert 5
  #define  c_FlashRowInvert     6

#endif


  //
  // ***************************************************************************
  //
  //  constants pertaining to MMI ( man machine interface)
  //
  //  high level navigation commands
  //

  #define cCmdNothing                 0

  #define cCmdEscape                  1       // On-Off-Button pushed
  #define cCmdSelect                  2       // Enc-Button pushed
  #define cCmdButton3Pushed           3
  #define cCmdButton4Pushed           4
  #define cCmdButton5Pushed           5

#if ( defined BUILD_AUDIO )

  #define cCmdFlapsData               6
  #define cCmdTemperature             7
  #define cCmdHumidity                8
  #define cCmdPressure                9

  #define c_max_frequency           5000.0F
  #define c_min_frequency           300.0F
  #define c_mid_frequency           1225.0F   // ca. sqrt ( min * max )

  #define c_max_duty_cycle          90
  #define c_min_duty_cycle          10

#endif

  #if ( defined BUILD_VARIO ) || ( defined BUILD_BOOTLOADER )
  #define cCmdPushedInnerIncrease     6
  #define cCmdInnerIncrease           7

   #define cCmdPushedInnerDecrease    8
  #define cCmdInnerDecrease           9

  #define cCmdPushedOuterIncrease     10
  #define cCmdOuterIncrease           11

  #define cCmdPushedOuterDecrease     12
  #define cCmdOuterDecrease           13

  #define cCmdCodeMaxNo               14
#endif

#ifdef  BUILD_VARIO
  // ***************************************************************************
  //
  //  Field Indices // should be unique
  //
  //  id-s of all fields in FieldDescriptor
  //
  //
  enum  Field_Indices {
        c_Damping_Setup,                                  // - 330
        c_Vario_Page_SetUp = 1U,
        c_SpeedCmd_Audio_SetUp,
        c_Horizon_Page_SetUp,
        c_Plane_and_Pilot,
        c_Vario_Data,
        c_GPS_Compass_Data,
        c_Wind_Data,
        c_Plane_Status,
        c_Audio_Setup,
        c_VFields_Vario,
        c_VFields_SC,
        c_Debugger,
        c_Max_Menues,
        c_MacCready,
        c_PlaneType,
        c_Ballast,
        c_PilotMass,
        c_Bugs,
        c_WingLoad,
        c_OptAS,
        c_OptASError,
        c_maxLoD,
        c_maxLoDatOAS,
        c_OASatMC,
        c_Audio_Tau,
        c_Vario_Zeiger_Tau,
        c_Mittl_Steigen_Tau,
        c_AMM_Tau,
        c_SpeedCmd_Tau,
        c_Wind_Tau,
        c_Acceleration_Tau,
        c_GPS_ClimbRate_Tau,
        c_SlipAngle,
        c_TurnRate,
        c_IAS,
        c_CAS,
        c_TAS,
        c_AmbDensity,
        c_AmbPressure,
        c_AmbRelHumidity,
        c_QNH,
        c_QNH_Altitude,
        c_QNH_Altitude_Gain,
        c_QFE,
        c_QFE_Altitude,
        c_FL,
        c_PL_SR,
        c_PL_SR_Average,
        c_Sens_SR_Average,
        c_True_Average,
        c_AM_SR,
        c_AM_SR_Average,
        c_WD_Sens,
        c_WS_Sens,
        c_WD_Curr,
        c_WS_Curr,
        c_W_Curr,
        c_WD_Glide,
        c_WS_Glide,
        c_W_Glide,
        c_Heading,
        c_RollAngle,
        c_PitchAngle,
        c_GPS_UTC_Offset,
        c_GPS_Date_Time,
        c_LOC_Date_Time,
        c_GPS_Altitude,
        c_GPS_ClimbRate,
        c_GPS_Latitude,
        c_GPS_Longitude,
        c_GPS_Track,
        c_GPS_GroundSpeed,
        c_GPS_NoSats,
        c_GPS_Condition,
        c_NettoAcceleration,
        c_CurrentFlightStatus,
        c_SensorClimbMode,
        c_IntCircleMode,
        c_FinalGlideMode,
        c_BrakesExtended,
        c_GearExtended,
        c_FlapsPositive,
        c_LoggingOn,
        c_ForceOutPutOfPlaneData,
        c_Vario_Volume,
        c_SC_Volume,
        c_Vario_MutWinUL,
        c_Vario_MutWinLL,
        c_SC_MutWinUL,
        c_SC_MutWinLL,
        c_SysTime_mSecs,
        c_SysTime_Secs,
        c_CAS_Slope,
        c_OAS_Slope,
        c_Audio_On,
        c_Time2SC,
        c_Audio_Frequency,
        c_Audio_On_Interval,
        c_Audio_Off_Interval,
        c_SC_Mute,
        c_SC_Total_Mute,
        c_FSCSR,
        c_FSROOT,
        c_VF_Vario_1,
        c_VF_Vario_2,
        c_VF_Vario_3,
        c_VF_Vario_4,
        c_VF_Vario_5,
        c_VF_Vario_6,
        c_VF_SC_1,
        c_VF_SC_2,
        c_VF_SC_3,
        c_VF_SC_4,
        c_VF_SC_5,
        c_VF_SC_6,
        c_Var_Show_OwnAvrge,
        c_Var_Show_SensorAvrge,
        c_Var_Show_TrueAvrage,
        c_Var_Show_AMSR,
        c_Var_Show_AMSRAvrge,
        c_Var_Show_AM_in_Climb,
        c_Var_Show_Chevron,
        c_ClimbMode_Source_Sel,
        c_Time_Selector,
        c_Pitch_Offset,
        c_ForceSDLoad,
        c_TIScaleSelector,
        c_Average_Source_Sel,
        c_Time2SwitchBack,
        c_Time2Engrave,
        c_Speed,
        c_PolSink,
        c_GlRatio,
        c_Show_Chevron,
        c_SensorSystemState,
        c_ColorSetting,
        c_Version,
        c_UpdDateTime,
        c_Dummy,
        c_Max_Fields,
        //c_Dummy2 = 0xffff,
      };
#endif

#ifdef  BUILD_BOOTLOADER
  enum  Field_Indices {
        c_File_List,
        c_Max_Menues,
        c_List_Item_0,
        c_List_Item_1,
        c_List_Item_2,
        c_List_Item_3,
        c_List_Item_4,
        c_List_Item_5,
        c_List_Item_6,
        c_List_Item_7,
        c_List_Item_8,
        c_List_Item_9,
        c_Dummy,
        c_Max_Fields,
      };

#endif

  // ***************************************************************************
  //
  //  The graphical programs/pages have numeration below 0 (zero).
  //  Menue pages are zero and above
  //
#ifdef  BUILD_VARIO

  #define   c_minGraphPrg   -4
  #define   c_ReBoot        -4
  #define   c_TurnIndicator -3
  #define   c_Horizon       -2
  #define   c_Vario         -1
  #define   c_maxGraphPrg   -1

  #define   c_minProgram    c_minGraphPrg
  #define   c_maxProgram    ( c_Max_Menues - 1 )
#endif

#ifdef  BUILD_BOOTLOADER
  #define   c_LandingPage   -1
  #define   c_Select_Hex1    0
  #define   c_Select_Hex2    1

  #define   c_minProgram    c_LandingPage
  #define   c_maxProgram    c_Select_Hex2
#endif

  enum  {
        c_do_decrease = 0,
        c_do_increase,
  };

  enum  {
        c_IsNotConfigRelevant,
        c_IsConfigRelevant,
  };

  enum  {
        c_Focus_MenueHeader,
        c_Selectable,
        c_Focus_None,
        c_Focussed,
        c_Selected,
  };

  enum  {
        c_NeverMod,
        c_AlwaysMod,
        c_ModInFlight,
        c_ModNOTInFlight,
      };

  // ---------------------------------------------------------------------------
  //
  // Units
  //

  enum  {
        c_Unit_NoUnit,
        c_Unit_ClimbSpeed,
        c_Unit_Pressure,
        c_Unit_FL,
        c_Unit_Altitude,
        c_Unit_Temperature,
        c_Unit_HorizontalSpeed,
        c_Unit_Angle,
        c_Unit_Hours,
        c_Unit_Minutes,
        c_Unit_Seconds,
        c_Unit_Milli_Seconds,
        c_Unit_Hertz,
        c_Unit_AnglePerSecond,
        c_Unit_Percentage,
        c_Unit_Mass,
        c_Unit_LoD,
        c_Unit_WingLoad,
        c_Unit_Density,
        c_Unit_Voltage,
        c_Unit_Distance,
        c_Unit_Acceleration,
        c_Unit_PerSec,

        cMaxDiffUnits,
    };

#ifdef  BUILD_VARIO
//  // ---------------------------------------------------------------------------
//  //
//  // Polar Curve calculations
//  //
//  #define   cMaxQPol                       7
//  #define   cMaxPolItems                   5
//  #define   cRecalNotRequired              0
//  #define   cRecalRequired                 1
//  #define   cPlaneRecalAltitudeThreshold   250
//  #define   cClimbRateLimit                0.0001
//  #define   cJota                          0.0000001
//  #define   cMaxDegradation                25.0
//
  // ---------------------------------------------------------------------------
  //
  // Plane & Flight Situations
  //

  enum  {
        c_onGround,
        //c_duringTakeOff,
        c_AirBorne,
        //c_duringLanding,
      };



//  enum  {
//        cNonWaveMode,
//        cWaveMode,
//
//        cMaxWaveMode,
//      };


  //#define   c_manual_climb_cruise_mask  0x03
  #define   c_manual_climb_mask         0x01
  #define   c_manual_cruise_mask        0x02


#endif

  enum  {
        c_Cruising,         // 0
        c_Transition,       // 1
        c_Climbing,         // 2
      };

  //   *****************************************************************************
//
  //#define   c_max_textbuffer_length             10

  #define   c_Max_No_Of_Log_Messages_in_Wait    10
  #define   c_Max_Log_Messages_Size             100

  #define   c_deferred_action_interval          5
  #define   c_SetTime2SwitchBack                20

  #define   c_conversion_buffer_size            10
  #define   c_small_buffer_size                 80
  #define   c_big_buffer_size                   150

  #define   c_wait_after_vario_mode_change      5

  //
  // ***************************************************************************
  //
  // FreeRTOS task wake periods
  //
  #define   c_WakeIOFrontEnd           10      // 1000 /  10  = 100 Hz
  #define   c_WakeImageBuilder1        40      // 1000 /  40  =  25 Hz
  #define   c_WakeImageBuilder2        100     // 1000 / 100  =  10 Hz
  #define   c_WakeCANBusReceiver       100     // 1000 / 100  =  10 Hz
  #define   c_WakeBackGround           50      // 1000 /  50  =  20 Hz
  #define   c_WakeHeartBeat            500     // 1000 / 500  =   2 Hz
  #define   c_WakeAudio                20      // 1000 /  20  =  50 Hz
  #define   c_WakeNavRad               20      // 1000 /  20  =  50 Hz
  #define   c_WakeFlapSensor           100     // 1000 / 100  =  10 Hz
  #define   c_WakeTempHumSensor        250     // 1000 / 250  =   4 Hz
  #define   c_WakeFlapsLED			       100     // 1000 / 100  =  10 Hz
  #define   c_WakeAudioController      10      // 1000 /  10  = 100 Hz

  //
  // ***************************************************************************
  //
  //  Miscellaneous
  //

#ifdef  BUILD_VARIO
  enum
  {
      GNSS_AVAILABLE          = 1,
      D_GNSS_AVAILABLE        = 2,

      MTI_SENSOR_AVAILABE     = 0x10,
      FXOS_SENSOR_AVAILABLE   = 0x20,
      L3GD20_SENSOR_AVAILABLE = 0x40,
      MS5611_STATIC_AVAILABLE = 0x80,
      MS5611_PITOT_AVAILABLE  = 0x100,

      USART_OUTPUT_ACTIVE     = 0x1000,
      BLUEZ_OUTPUT_ACTIVE     = 0x2000,
      CAN_OUTPUT_ACTIVE       = 0x4000,
  };
#endif

  #define   c_filename_size     20
  #define   c_max_dirlistitems  9


  #define   c_Use_ClimbMode_From_Sensor     0
  #define   c_Use_ClimbMode_Set_By_User     1

  #define   c_ValidOnlyInFlight             0
  #define   c_AlwaysValid                   1

  #define   c_MaxQWaitTime_in_ms            1000

  // ( (float) c_WakeCANBusReceiver / (float) c_WakeImageBuilder1 )
  #define   c_smooth                        5.0F
  #define   c_smooth_2                      ( ( c_smooth - 1.0 ) / c_smooth )

  #define   c_max_no_of_fields_any_program  20  // includes the menue line !!!!!
  #define   c_period_for_logging            10000

  #define   c_max_duration_no_change        100
  #define   c_Ret_BoxHeight                 0
  #define   c_Ret_BoxWidth                  1
  #define   c_Ret_PixWidth                  2

  #define   c_max_no_of_digits              11


  #define   l_TC_CAN_Bus_Receiver           10

  #define   c_NonInverted                   0
  #define   c_Inverted                      1

  #ifdef BUILD_VARIO
    //
    // ***************************************************************************
    //
    // Polar Curve calculations
    //
    #define   cMaxNoOfPlanes                 4
    #define   cMaxQPol                       7
    #define   cMaxPolItems                   5
    #define   cMaxFlapsDescrItems            8
    #define   cRecalNotRequired              0
    #define   cRecalRequired                 1
    #define   cPlaneRecalAltitudeThreshold   250
    #define   cClimbRateLimit                0.0001
    #define   cJota                          0.0000001
    #define   cMaxDegradation                25.0
    #define   cMinAirSpeed                   80
    #define   cMaxAirSpeed                   250
  #endif

  #if ( defined BUILD_VARIO ) || ( defined BUILD_BOOTLOADER )
    #define   c_eeprom_page_size  32
  #endif


#endif    // __Generic_Const_h
//
// ****************************************************************************
// The End
// ****************************************************************************
