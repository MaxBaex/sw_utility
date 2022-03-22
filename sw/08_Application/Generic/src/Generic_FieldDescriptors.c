/**
  * ############################################################################
  * @file     FieldDescriptors.c
  * @brief    New Vario
  * @author   Horst Rupp
  * @brief    This file contains the data structures used to control of the
  * *         New Vario system.
  * @brief    This is the  central part of the "C" part of the
  * *         New Vario MVC structure.
  * ############################################################################
  */
//******************************************************************************
//
// Includes
//
#include "memory.h"
//#include "common.h"
#include  "Generic_Common.h"
#include "Generic_Includes.h"

#ifdef  BUILD_VARIO
  #include "Plane.h"
#endif

#if  ( defined BUILD_VARIO ) || ( defined BUILD_BOOTLOADER )

  //******************************************************************************
  //
  ROM uint8_t txt_Changed_Value_Saved[] = ">> Changed value is saved";
  ROM uint8_t txt_GradPerSec[]          = "Turning ~/sec";
  ROM uint8_t txt_MinPerTurn[]          = "min/sec per Full Turn";
  ROM uint8_t txt_L_Blank[]             = "L ";
  ROM uint8_t txt_U_Blank[]             = "U ";
  ROM uint8_t txt_SlashCRLF[]           =  "//\r\n";
  ROM uint8_t txt_StartUp[]             = "// New Vario Startup.cfg ************\r\n";
  ROM uint8_t txt_Equal[]               = " = ";
  ROM uint8_t txt_CRLF[]                = "\r\n";
  ROM uint8_t txt_EOF[]                 = "// *** EOF ********\r\n";
  ROM uint8_t txt_Grad_Slash[]          = "~/ ";
  ROM uint8_t txt_Calc_PolCurve[]       = "Calculation Polar Curve for ";
  ROM uint8_t txt_PLN[]                 = "PLN";
  ROM uint8_t txt_Start_Recalc_1[]      = " : Start Recalculation 1 -------------------";
  ROM uint8_t txt_End_Recalc_1[]        = " : End Recalculation 1 -------------------";
  ROM uint8_t txt_Start_Recalc_2[]      = " : Start Recalculation 2 -------------------";
  ROM uint8_t txt_End_Recalc_2[]        = " : End Recalculation 2 -------------------";
  ROM uint8_t txt_Start_Recalc_3[]      = " : Start Recalculation 3 -------------------";
  ROM uint8_t txt_End_Recalc_3[]        = " : End Recalculation 3 -------------------";
  ROM uint8_t txt_Start_Recalc_4[]      = " : Start Recalculation 4 -------------------";
  ROM uint8_t txt_End_Recalc_4[]        = " : End Recalculation 4 -------------------";
  ROM uint8_t txt_Q_Send_Fail[]         = ">> Failure of xQueueReceive on EventQ | Command =";
  ROM uint8_t txt_Q_Receive_Success[]   = ">> Success of xQueueReceive on EventQ | Command =";
  ROM uint8_t txt_MMI[]                 = "MMI";
  ROM uint8_t txt_Next_Program[]        = ">> Next Program =";
  ROM uint8_t txt_Prev_Program[]        = ">> Previous Program =";
  ROM uint8_t txt_Obs_Command[]         = " obsolete command :";
  ROM uint8_t txt_Carets[]              = ">>";
  ROM uint8_t txt_PSG[]                 = "PSG";
  ROM uint8_t txt_Push_Signal[]         = "Push Signal";
  ROM uint8_t txt_Fail_Q_Send[]         = ">> Failure of QueueSend on EventQ";
  ROM uint8_t txt_FRE[]                 = "FRE";

  //  ****************************************************************************
  //

  ROM UnitItem_t  Units[cMaxDiffUnits] =
    {
      "",       // c_Unit_NoUnit
      "m/s",    // c_Unit_ClimbSpeed
      "hPa",    // c_Unit_Pressure
      "FL",     // c_Unit_FL
      "m",      // c_Unit_Altitude
      "~ C",    // c_Unit_Temperature
      "km/h",   // c_Unit_HorizontalSpeed
      "~",      // c_Unit_Angle
      "hour",   // c_Unit_Hours
      "min",    // c_Unit_Minutes
      "sec",    // c_Unit_Seconds
      "msec",   // c_Unit_Milli_Seconds
      "Hz",     // c_Unit_Hertz
      "~/sc",   // c_Unit_AnglePerSecond
      "%",      // c_Unit_Percentage
      "kg",     // c_Unit_Mass
      "LoD",    // c_Unit_LoD
      "kg/m^2", // c_Unit_WingLoad
      "kg/m^3", // c_Unit_Density
      "Volt",   // c_Unit_Voltage
      "km",     // c_Unit_Distance
      "m/s^2",  // c_Unit_Acceleration
      "/sec"    // c_Unit_PerSec
    };

  //  ****************************************************************************
  //
  ROM ErrorMsgTranslator_t    ErrorMsgTranslator[c_Max_No_Of_Error_Messages]  =
    {
      {  c_EC_MMI_0,  "0 - Cursor low limit reached" },      // max 20 chars
      {  c_EC_MMI_1,  "1 - Cursor high limit reached" },
      {  c_EC_MMI_2,  "2 - Field cannot be modified, select not possible" },
      {  c_EC_MMI_3,  "3 - In this program select is not possible" },
      {  c_EC_MMI_4,  "4 - Field cannot be modified, select not possible" },
      {  c_EC_MMI_5,  "5 - In this program select is not possible" },
      {  c_EC_MMI_6,  "6 - High value limit reached" },
      {  c_EC_MMI_7,  "7 - High value limit reached" },
      {  c_EC_MMI_8,  "8 - Low value limit reached" },
      {  c_EC_MMI_9,  "9 - Low value limit reached" },
      {  c_EC_RAW_0,  "0 - Command code illegal" },
      {  c_EC_PNV_0,  "0 - Cursor Move Up Limit Reached" },
      {  c_EC_PNV_1,  "1 - Cursor Move Down Limit Reached" },
      {  c_EC_CFG_0,  "0 - Cannot Open Config Data File" },
      {  cError4,     "Error4" },
      {  cError5,     "Error5" },
      {  cError6,     "Error6" },
      {  cError7,     "Error7" }
    };

  //  ****************************************************************************

  ROM CmdCodeTranslator_t    CmdCodeTranslator[cCmdCodeMaxNo]  =
    {

      { cCmdNothing,              "Nothing" },
      { cCmdSelect,               "Select" },
      { cCmdEscape,               "Escape" },
      { cCmdButton3Pushed,        "Button3Pushed" },
      { cCmdButton4Pushed,        "Button4Pushed" },
      { cCmdButton5Pushed,        "Button5Pushed" },
      { cCmdPushedInnerIncrease,  "PushedInnerIncrease" },
      { cCmdInnerIncrease,        "InnerIncrease" },
      { cCmdPushedInnerDecrease,  "PushedInnerDecrease" },
      { cCmdInnerDecrease,        "InnerDecrease" },
      { cCmdPushedOuterIncrease,  "PushedOuterIncrease" },
      { cCmdOuterIncrease,        "OuterIncrease" },
      { cCmdPushedOuterDecrease,  "PushedOuterDecrease" },
      { cCmdOuterDecrease,        "OuterDecrease" }

    };

//  ****************************************************************************
//
// sequence must fit to NV_Const.h --Programs / Pages SEQUENCE
//

  #ifdef	BUILD_VARIO
    ROM  ProgramDescItem_t    Programs[c_Max_Menues] =
      {
        { 9,                                                      // program 0
          {
            { c_Damping_Setup,          c_NeverMod },
            { c_Vario_Zeiger_Tau,       c_AlwaysMod },
            { c_Mittl_Steigen_Tau,      c_AlwaysMod },
            { c_AMM_Tau,                c_AlwaysMod },
            { c_Wind_Tau,               c_AlwaysMod },
            { c_SpeedCmd_Tau,           c_AlwaysMod },
            { c_Audio_Tau,              c_AlwaysMod },
            { c_Acceleration_Tau,       c_AlwaysMod },
            { c_GPS_ClimbRate_Tau,      c_AlwaysMod }

          }
        },
        { 12,                                                      // program 1
          {
            { c_Vario_Page_SetUp,       c_NeverMod },
            { c_MacCready,              c_AlwaysMod },
            { c_Var_Show_OwnAvrge,      c_AlwaysMod },
            { c_Var_Show_SensorAvrge,   c_AlwaysMod },
            { c_Var_Show_TrueAvrage,    c_AlwaysMod },
            { c_Var_Show_AMSR,          c_AlwaysMod },
            { c_Var_Show_AMSRAvrge,     c_AlwaysMod },
            { c_Var_Show_Chevron,       c_AlwaysMod },
            { c_ClimbMode_Source_Sel,   c_AlwaysMod },
            { c_Time_Selector,          c_AlwaysMod },
            { c_Time2SwitchBack,        c_AlwaysMod },
            { c_Time2Engrave,           c_AlwaysMod }
          }
        },
        { 7,                                                      // program 1
          {
            { c_Horizon_Page_SetUp,     c_NeverMod },
            { c_Pitch_Offset,           c_AlwaysMod },
            { c_Average_Source_Sel,     c_AlwaysMod },
            { c_Time2SwitchBack,        c_AlwaysMod },
            { c_Time2Engrave,           c_AlwaysMod },
            { c_TIScaleSelector,        c_AlwaysMod },
            { c_ColorSetting,           c_AlwaysMod }
          }
        },
        { 6,                                                      // program 2
          {
            { c_SpeedCmd_Audio_SetUp,   c_NeverMod },
            { c_MacCready,              c_AlwaysMod },
            { c_PlaneType,              c_AlwaysMod },
            { c_Audio_On,               c_NeverMod },
            { c_CAS_Slope,              c_NeverMod },
            { c_OAS_Slope,              c_NeverMod }
          }
        },
        { 10,                                                     // program 3
          {
            { c_Plane_and_Pilot,        c_NeverMod },
            { c_PlaneType,              c_AlwaysMod },
            { c_PilotMass,              c_AlwaysMod },
            { c_Ballast,                c_AlwaysMod },
            { c_Bugs,                   c_AlwaysMod },
            { c_MacCready,              c_AlwaysMod },
            { c_WingLoad,               c_NeverMod },
            { c_maxLoD,                 c_NeverMod },
            { c_maxLoDatOAS,            c_NeverMod },
            { c_OASatMC,                c_NeverMod }
          }
        },
        { 10,                                                      // program 4
          {
            { c_Audio_Setup,            c_NeverMod },
            { c_Vario_Volume,           c_AlwaysMod },
            { c_SC_Volume,              c_AlwaysMod },
            { c_Vario_MutWinUL,         c_AlwaysMod },
            { c_Vario_MutWinLL,         c_AlwaysMod },
            { c_SC_MutWinUL,            c_AlwaysMod },
            { c_SC_MutWinLL,            c_AlwaysMod },
            { c_SpeedCmd_Tau,           c_AlwaysMod },
            { c_Audio_Tau,              c_AlwaysMod },
            { c_SC_Mute,                c_AlwaysMod }
          }
        },
        { 13,                                                     // program 5
          {

            { c_GPS_Compass_Data,       c_NeverMod },
            { c_Pitch_Offset,           c_AlwaysMod },
            { c_GPS_UTC_Offset,         c_AlwaysMod },
            { c_GPS_Date_Time,          c_NeverMod },
            { c_LOC_Date_Time,          c_NeverMod },
            { c_GPS_Latitude,           c_NeverMod },
            { c_GPS_Longitude,          c_NeverMod },
            { c_GPS_Track,              c_NeverMod },
            { c_GPS_GroundSpeed,        c_NeverMod },
            { c_GPS_Condition,          c_NeverMod },
            { c_Heading,                c_NeverMod },
            { c_RollAngle,              c_NeverMod },
            { c_PitchAngle,             c_NeverMod }
          }
        },
        { 3,                                                      // program 6
          {
            { c_Wind_Data,              c_NeverMod },
            { c_W_Curr,                 c_NeverMod },
            { c_W_Glide,                c_NeverMod }
          }
        },
        { 19,                                                     // program 7
          {
            { c_Vario_Data,             c_NeverMod },
            { c_OptAS,                  c_NeverMod },
            { c_IAS,                    c_NeverMod },
            { c_CAS,                    c_NeverMod },
            { c_TAS,                    c_NeverMod },
            { c_AmbDensity,             c_NeverMod },
            { c_AmbPressure,            c_NeverMod },
            { c_QFE,                    c_NeverMod },
            { c_QFE_Altitude,           c_ModNOTInFlight },
            { c_QNH,                    c_ModInFlight },
            { c_QNH_Altitude,           c_NeverMod },
            { c_QNH_Altitude_Gain,      c_NeverMod },
            { c_FL,                     c_NeverMod },
            { c_PL_SR,                  c_NeverMod },
            { c_PL_SR_Average,          c_NeverMod },
            { c_Sens_SR_Average,        c_NeverMod },
            { c_True_Average,           c_NeverMod },
            { c_AM_SR,                  c_NeverMod },
            { c_AM_SR_Average,          c_NeverMod }
          }
        },
        { 7,                                                      // program 8
          {
            { c_Plane_Status,           c_NeverMod },
            { c_CurrentFlightStatus,    c_NeverMod },
            { c_OptAS,                  c_NeverMod },
            { c_IntCircleMode,          c_NeverMod },
            { c_BrakesExtended,         c_NeverMod },
            { c_GearExtended,           c_NeverMod },
            { c_FlapsPositive,          c_NeverMod }
          }
        },
        { 7,                                                      // program 9
          {
            { c_VFields_Vario,          c_NeverMod },
            { c_VF_Vario_1,             c_AlwaysMod },
            { c_VF_Vario_2,             c_AlwaysMod },
            { c_VF_Vario_3,             c_AlwaysMod },
            { c_VF_Vario_4,             c_AlwaysMod },
            { c_VF_Vario_5,             c_AlwaysMod },
            { c_VF_Vario_6,             c_AlwaysMod }
          }
        },
        { 7,                                                      // program 10
          {
            { c_VFields_SC,             c_NeverMod },
            { c_VF_SC_1,                c_AlwaysMod },
            { c_VF_SC_2,                c_AlwaysMod },
            { c_VF_SC_3,                c_AlwaysMod },
            { c_VF_SC_4,                c_AlwaysMod },
            { c_VF_SC_5,                c_AlwaysMod },
            { c_VF_SC_6,                c_AlwaysMod }
          }
        },
        { 12,                                                      // program 11
          {
            { c_Debugger,               c_NeverMod },
            { c_Version,                c_NeverMod },
            { c_SensorSystemState,      c_NeverMod },
            { c_PlaneType,              c_AlwaysMod },
            { c_Speed,                  c_AlwaysMod },
            { c_PolSink,                c_NeverMod },
            { c_GlRatio,                c_NeverMod },
            { c_SysTime_Secs,           c_NeverMod },
            { c_SysTime_mSecs,          c_NeverMod },
            { c_ForceOutPutOfPlaneData, c_AlwaysMod },
            { c_LoggingOn,              c_AlwaysMod },
            { c_ForceSDLoad,            c_AlwaysMod }

          }
        }
      };
  #endif

  #ifdef BUILD_BOOTLOADER
    ROM  ProgramDescItem_t    Programs[c_Max_Menues] =
      {
        { 10,                                                      // program 0
          {
            { c_Select_Hex1,              c_NeverMod },
            { c_List_Item_0,              c_NeverMod },
            { c_List_Item_1,              c_NeverMod },
            { c_List_Item_2,              c_NeverMod },
            { c_List_Item_3,              c_NeverMod },
            { c_List_Item_4,              c_NeverMod },
            { c_List_Item_5,              c_NeverMod },
            { c_List_Item_6,              c_NeverMod },
            { c_List_Item_7,              c_NeverMod },
            { c_List_Item_8,              c_NeverMod }

          }
        }
      };

  #endif

  #ifdef	BUILD_VARIO
    ROM  uint8_t    VarioFieldOptions[c_max_no_of_vario_field_options] =
      {
        c_MacCready,          // - 280
        c_Ballast,
        c_PilotMass,
        c_Bugs,
        c_OASatMC,
        c_OptAS,
        c_OptASError,
        c_maxLoDatOAS,
        c_GPS_Date_Time,
        c_LOC_Date_Time,
        c_GPS_Track,
        c_GPS_GroundSpeed,
        c_GPS_Altitude,
        c_GPS_ClimbRate,
        c_SlipAngle,
        c_TurnRate,
        c_NettoAcceleration,
        c_RollAngle,
        c_PitchAngle,
        c_W_Curr,
        c_W_Glide,
        c_IAS,
        c_CAS,
        c_TAS,
        c_CAS_Slope,
        c_OAS_Slope,
        c_QFE,
        c_QFE_Altitude,
        c_QNH,
        c_QNH_Altitude,
        c_QNH_Altitude_Gain,
        c_FL,
        c_PL_SR,
        c_PL_SR_Average,
        c_Sens_SR_Average,
        c_True_Average,
        c_AM_SR,
        c_AM_SR_Average,
        c_Vario_Volume,
        c_SC_Volume,
        c_Audio_On,
        c_Time2SC,
        c_SensorSystemState

      }; // <<-- c_max_no_of_vario_field_options -->> Zeilennummer - 280 !!!!!!!!!!!!!!!!
    //
  #endif

#ifdef	BUILD_VARIO
  ROM  LongFieldDescriptorItem_t    FieldDescriptors[c_Max_Fields] =
      {

        // count                             0
        {
          c_Damping_Setup,
          c_IsNotConfigRelevant,
  //      "012345567890123"
          "Time Constants",
          "TCs",
  //      "12345678901234567890"
          "XXXXXXXXXXXXXXXXXXXX",

          "YYYYYYYYYYYYYYYYYYYY",
          c_FT_Menue,
          c_AlwaysValid,
          c_Unit_NoUnit,
          0,
          0,  0,    0,    0,
          0,  0.0,  0.0,  0.0
        },
        // count                             1
        {
          c_Vario_Page_SetUp,
          c_IsNotConfigRelevant,
  //      "012345567890123"
          "VarioPage SetUp",
  //      "012345567890123"
          "VarioPage",
  //      "12345678901234567890"
          "XXXXXXXXXXXXXXXXXXXX",
          "YYYYYYYYYYYYYYYYYYYY",
          c_FT_Menue,
          c_AlwaysValid,
          c_Unit_NoUnit,
          0,
          0,  0,    0,    0,
          0,  0.0,  0.0,  0.0
        },
        // count                             2
        {
          c_SpeedCmd_Audio_SetUp,
          c_IsNotConfigRelevant,
  //      "012345567890123"
          "SC Audio SetUp",
  //      "012345567890"
          "SC Audio SUp",
  //      "12345678901234567890"
          "XXXXXXXXXXXXXXXXXXXX",
          "YYYYYYYYYYYYYYYYYYYY",
          c_FT_Menue,
          c_AlwaysValid,
          c_Unit_NoUnit,
          0,
          0,  0,    0,    0,
          0,  0.0,  0.0,  0.0
        },
        // count                             3
        {
          c_Horizon_Page_SetUp,
          c_IsNotConfigRelevant,
  //      "012345567890123"
          "Horizon SetUp",
          "Hor SUp",
  //      "12345678901234567890"
          "XXXXXXXXXXXXXXXXXXXX",
          "YYYYYYYYYYYYYYYYYYYY",
          c_FT_Menue,
          c_AlwaysValid,
          c_Unit_NoUnit,
          0,
          0,  0,    0,    0,
          0,  0.0,  0.0,  0.0
        },
        // count                             4
        {
          c_Plane_and_Pilot,
          c_IsNotConfigRelevant,
  //      "012345567890123"
          "Plane and Pilot",
  //      "012345567890"
          "Plane Pilot",
  //      "12345678901234567890"
          "XXXXXXXXXXXXXXXXXXXX",
          "YYYYYYYYYYYYYYYYYYYY",
          c_FT_Menue,
          c_AlwaysValid,
          c_Unit_NoUnit,
          0,
          0,  0,    0,    0,
          0,  0.0,  0.0,  0.0
        },
        // count                             5
        {
          c_Vario_Data,
          c_IsNotConfigRelevant,
  //      "012345567890123"
          "Vario Data",
          "VData",
  //      "12345678901234567890"
          "XXXXXXXXXXXXXXXXXXXX",
          "YYYYYYYYYYYYYYYYYYYY",
          c_FT_Menue,
          c_AlwaysValid,
          c_Unit_NoUnit,
          0,
          0,  0,    0,    0,
          0,  0.0,  0.0,  0.0
        },
        // count                             6
        {
          c_GPS_Compass_Data,
          c_IsNotConfigRelevant,
  //      "012345567890123"
          "GPS & Compass",
          "GPSCpss",
  //      "12345678901234567890"
          "XXXXXXXXXXXXXXXXXXXX",
          "YYYYYYYYYYYYYYYYYYYY",
          c_FT_Menue,
          c_AlwaysValid,
          c_Unit_NoUnit,
          0,
          0,  0,    0,    0,
          0,  0.0,  0.0,  0.0
        },
        // count                             7
        {
          c_Wind_Data,
          c_IsNotConfigRelevant,
  //      "012345567890123"
          "Wind Data",
          "Wind",
  //      "12345678901234567890"
          "XXXXXXXXXXXXXXXXXXXX",
          "YYYYYYYYYYYYYYYYYYYY",
          c_FT_Menue,
          c_AlwaysValid,
          c_Unit_NoUnit,
          0,
          0,  0,    0,    0,
          0,  0.0,  0.0,  0.0
        },
        // count                             8
        {
          c_Plane_Status,
          c_IsNotConfigRelevant,
  //      "012345567890123"
          "Plane Status",
          "Plane",
  //      "12345678901234567890"
          "XXXXXXXXXXXXXXXXXXXX",
          "YYYYYYYYYYYYYYYYYYYY",
          c_FT_Menue,
          c_AlwaysValid,
          c_Unit_NoUnit,
          0,
          0,  0,    0,    0,
          0,  0.0,  0.0,  0.0
        },
        // count                             9
        {
          c_Audio_Setup,
          c_IsNotConfigRelevant,
  //      "012345567890123"
          "Audio Setup",
          "Audio",
  //      "12345678901234567890"
          "XXXXXXXXXXXXXXXXXXXX",
          "YYYYYYYYYYYYYYYYYYYY",
          c_FT_Menue,
          c_AlwaysValid,
          c_Unit_NoUnit,
          0,
          0,  0,    0,    0,
          0,  0.0,  0.0,  0.0
        },
        // count                             10
        {
          c_VFields_Vario,
          c_IsNotConfigRelevant,
  //      "012345567890123"
          "VarioField Sel",
          "VFSel",
  //      "12345678901234567890"
          "XXXXXXXXXXXXXXXXXXXX",
          "YYYYYYYYYYYYYYYYYYYY",
          c_FT_Menue,
          c_AlwaysValid,
          c_Unit_NoUnit,
          0,
          0,  0,    0,    0,
          0,  0.0,  0.0,  0.0
        },
        // count                             11
        {
          c_VFields_SC,
          c_IsNotConfigRelevant,
  //      "012345567890123"
          "S/C Fields Sel",
          "SCFSel",
  //      "12345678901234567890"
          "XXXXXXXXXXXXXXXXXXXX",
          "YYYYYYYYYYYYYYYYYYYY",
          c_FT_Menue,
          c_AlwaysValid,
          c_Unit_NoUnit,
          0,
          0,  0,    0,    0,
          0,  0.0,  0.0,  0.0
        },
        // count                             12
        {
          c_Debugger,
          c_IsNotConfigRelevant,
  //      "012345567890123"
          "Debugger",
          "Debug",
  //      "12345678901234567890"
          "XXXXXXXXXXXXXXXXXXXX",
          "YYYYYYYYYYYYYYYYYYYY",
          c_FT_Menue,
          c_AlwaysValid,
          c_Unit_NoUnit,
          0,
          0,  0,    0,    0,
          0,  0.0,  0.0,  0.0
        },
        // count                             13
        {
          c_Max_Menues,
          c_IsNotConfigRelevant,
  //      "012345567890123"
          "MaxMenueDummy",
          "Dummy",
  //      "12345678901234567890"
          "XXXXXXXXXXXXXXXXXXXX",
          "YYYYYYYYYYYYYYYYYYYY",
          c_FT_Menue,
          c_AlwaysValid,
          c_Unit_NoUnit,
          0,
          0,    0,    0,    0,
          0,    0.0,  0.0,  0.0
        },
        // count                             14
        {
          c_MacCready,
          c_IsConfigRelevant,
  //      "1234567890123456"
          "MacCready",
  //      "1234567890"
          "MC",
  //      "123456789012345678901234"
          "MacCready-Setting",
          "",
          c_FT_Float,
          c_AlwaysValid,
          c_Unit_ClimbSpeed,
          1,
          0,    0,    0,    0,
          (float*)&(g_ConfigData.MacCready),  0,  15.0,  0.1
        },
        // count                             15
        {
          c_PlaneType,
          c_IsConfigRelevant,
  //      "1234567890123456"
          "PlaneType",
  //      "1234567890"
          "PlaneType",
  //      "12345678901234567890"
          "akt. programmierter",
          "Flugzeugtyp",
          c_FT_PlaneType,
          c_AlwaysValid,
          c_Unit_NoUnit,
          0,
          (int8_t*)&(g_ConfigData.PlaneType),  0,  cMaxNoOfPlanes-1,  1,
          0,    0,    0,    0
        },
        // count                             16
        {
          c_Ballast,
          c_IsConfigRelevant,
  //      "1234567890123456"
          "Ballast",
  //      "1234567890"
          "Bal",
  //      "12345678901234567890"
          "Einstellung",
        "       Wasserballast",
          c_FT_Int16,
          c_AlwaysValid,
          c_Unit_Mass,
          0,
          (int16_t*)&(g_ConfigData.Ballast),  0,  100,  1,
          0,    0,    0,    0
        },
        // count                             17
        // maximal Gewicht auf 250 kg wegen Doppelsitzer  HMR 17.11.20
        {
          c_PilotMass,
          c_IsConfigRelevant,
  //      "1234567890123456"
          "PilotMass",
  //      "1234567890"
          "PilotMass",
  //      "12345678901234567890"
          "Masse der Zuladung",
          "",
          c_FT_Int16,
          c_AlwaysValid,
          c_Unit_Mass,
          0,
          (int16_t*)&(g_ConfigData.PilotMass),  50,  250,  1,
          0,    0,    0,    0
        },
        // count                             18
        {
          c_Bugs,
          c_IsConfigRelevant,
  //      "1234567890123456"
          "Bugs",
  //      "1234567890"
          "Bugs",
  //      "12345678901234567890"
          "Verschmutzung durch",
          "Muecken",
          c_FT_Float,
          c_AlwaysValid,
          c_Unit_Percentage,
          1,
          0,    0,    0,    0,
          (float*)&(g_ConfigData.Bugs), 0.0, 25.0, 0.1

        },
        // count                             19
        {
          c_WingLoad,
          c_IsNotConfigRelevant,
  //      "1234567890123456"
          "WingLoad",
  //      "1234567890"
          "WingLoad",
  //      "12345678901234567890"
          "aktuelle",
          "Flaechenbelastung",
          c_FT_Float,
          c_AlwaysValid,
          c_Unit_WingLoad,
          1,
          0,    0,    0,    0,
          (float*)&(g_FrontEndData.CurrentWingLoad),  0,  0,  0
        },
        // count                             20
        {
          c_OptAS,
          c_IsNotConfigRelevant,
  //      "1234567890123456"
          "OptAS",
  //      "1234567890"
          "OptAS",
  //      "12345678901234567890"
          "Dynamische Anzeige",
          "der optim. Fahrt/IAS",
          c_FT_Int16,
          c_AlwaysValid,
          c_Unit_HorizontalSpeed,
          0,
          (int16_t*)&(g_FrontEndData.OAS),  0,  0,  0,
          0,    0,    0,    0
        },
        // count                             21
        {
          c_OptASError,
          c_IsNotConfigRelevant,
  //      "012345567890123"
          "OptASError",
  //      "1234567890"
          "OptASError",
  //      "12345678901234567890"
          "Dynamische Anzeige",
          "des akt. SF-Fehlers",
          c_FT_Int16,
          c_AlwaysValid,
          c_Unit_HorizontalSpeed,
          0,
          (int16_t*)&(g_FrontEndData.OAS_Error),  0,  0,  0,
          0,    0,    0,    0
        },
        // count                             22
        {
          c_maxLoD,
          c_IsNotConfigRelevant,
  //      "1234567890123456"
          "max LoD",
  //      "1234567890"
          "maxLoD",
  //      "12345678901234567890"
          "Beste Gleitzahl fuer",
          "dieses Flugzeug/Last",
          c_FT_Float,
          c_AlwaysValid,
          c_Unit_LoD,
          1,
          0,    0,    0,    0,
          (float*)&(g_FrontEndData.MaxLoD), 0.0,  0.0, 0.0
        },
        // count                             23
        {
          c_maxLoDatOAS,
          c_IsNotConfigRelevant,
  //      "1234567890123456"
          "OAS @ maxLoD",
  //      "1234567890"
          "OAS@maxLoD",
  //      "12345678901234567890"
          "Opt. Fahrt fuer",
          "beste Gleitzahl",
          c_FT_Int16,
          c_AlwaysValid,
          c_Unit_HorizontalSpeed,
          0,
          (int16_t*)&(g_FrontEndData.MaxLoDatOAS),  0,  0,  0,
          0,    0,    0,    0

        },
        // count                             24
        {
          c_OASatMC,
          c_IsNotConfigRelevant,
  //      "1234567890123456"
          "OAS @ MC",
  //      "1234567890"
          "OAS @ MC",
  //      "12345678901234567890"
          "Opt. Fahrt bei MC",
          "bei AM Sink 0",
          c_FT_Int16,
          c_AlwaysValid,
          c_Unit_HorizontalSpeed,
          0,
          (int16_t*)&(g_FrontEndData.OASatMC),  0,  0,  0,
          0,    0,    0,    0

        },
        // count                             25
        {
          c_Audio_Tau,
          c_IsConfigRelevant,
  //      "1234567890123456"
          "AudioTau",
  //      "1234567890"
          "Audio_Tau",
  //      "12345678901234567890"
          "Zeitkonstante fuer",
          "das Audio-Signal",
          c_FT_Float,
          c_AlwaysValid,
          c_Unit_Seconds,
          1,
          0,    0,    0,    0,
          (float*)&(g_ConfigData.Audio_Tau),  1.0,  30.0,  0.1
        },
        // count                             26
        {
          c_Vario_Zeiger_Tau,
          c_IsConfigRelevant,
  //      "1234567890123456"
          "ZeigerTau",
  //      "1234567890"
          "Zeiger_Tau",
  //      "12345678901234567890"
          "Zeitkonstante fuer",
          "Variozeiger",
          c_FT_Float,
          c_AlwaysValid,
          c_Unit_Seconds,
          1,
          0,    0,    0,    0,
          (float*)&(g_ConfigData.Vario_Zeiger_Tau),  1.0,  30.0,  0.1
        },
        // count                             27
        {
          c_Mittl_Steigen_Tau,
          c_IsConfigRelevant,
  //      "1234567890123456"
          "SRAVrgeTau",
  //      "1234567890"
          "SRAvrgeTau",
  //      "12345678901234567890"
          "Zeitkonstante fuer",
          "das mittl. Steigen",
          c_FT_Float,
          c_AlwaysValid,
          c_Unit_Seconds,
          1,
          0,    0,    0,    0,
          (float*)&(g_ConfigData.Mittl_Steigen_Tau),  1.0,  30.0,  0.1
        },
        // count                             28
        {
          c_AMM_Tau,
          c_IsConfigRelevant,
  //      "1234567890123456"
          "AMMTau",
  //      "1234567890"
          "AMM Tau",
  //      "12345678901234567890"
          "Zeitkonstante fuer",
          "Luftmassenbewegung",
          c_FT_Float,
          c_AlwaysValid,
          c_Unit_Seconds,
          1,
          0,    0,    0,    0,
          (float*)&(g_ConfigData.AMM_Tau),  1.0,  30.0,  0.1
        },
        // count                             29
        {
          c_SpeedCmd_Tau,
          c_IsConfigRelevant,
  //      "1234567890123456"
          "SCTau",
  //      "1234567890"
          "SC Tau",
  //      "12345678901234567890"
          "Daempfung",
          "Sollfahrt Signal",
          c_FT_Float,
          c_AlwaysValid,
          c_Unit_Seconds,
          1,
          0,    0,    0,    0,
          (float*)&(g_ConfigData.SpeedCmd_Tau),  1.0,  30.0,  0.1
        },
        // count                             30
        {
          c_Wind_Tau,
          c_IsConfigRelevant,
  //      "1234567890123456"
          "WindTau",
  //      "1234567890"
          "Wind Tau",
  //      "12345678901234567890"
          "Daempfung Mittelung",
          "Windgeschwindigkeit",
          c_FT_Float,
          c_AlwaysValid,
          c_Unit_Seconds,
          1,
          0,    0,    0,    0,
          (float*)&(g_ConfigData.Wind_Tau),  1.0,  60.0,  0.1
        },
        // count                             31
        {
          c_Acceleration_Tau,
          c_IsConfigRelevant,
  //      "1234567890123456"
          "AccTau",
  //      "1234567890"
          "Acc Tau",
  //      "12345678901234567890"
          "Daempfung",
          "Beschleunigung",
          c_FT_Float,
          c_AlwaysValid,
          c_Unit_Seconds,
          1,
          0,    0,    0,    0,
          (float*)&(g_ConfigData.Acceleration_Tau),  1.0,  60.0,  0.1
        },
        // count                             32
        {
          c_GPS_ClimbRate_Tau,
          c_IsConfigRelevant,
  //      "1234567890123456"
          "GPS_SR_Tau",
  //      "1234567890"
          "GPSSR Tau",
  //      "12345678901234567890"
          "Daempfung GPS",
          "ClimbRate",
          c_FT_Float,
          c_AlwaysValid,
          c_Unit_Seconds,
          1,
          0,    0,    0,    0,
          (float*)&(g_ConfigData.GPS_ClimbRate_Tau),  1.0,  60.0,  0.1
        },
        // count                             33
        {
          c_SlipAngle,
          c_IsNotConfigRelevant,
  //      "1234567890123456"
          "SlipAngle",
  //      "1234567890"
          "SlipAngle",
  //      "12345678901234567890"
          "Schiebewinkel",
          "",
          c_FT_Float,
          c_AlwaysValid,
          c_Unit_Acceleration,
          1,
          0,    0,    0,    0,
          (float*)&(g_FrontEndData.SlipAngle),  0.0,  0.0,  0.0
        },
        // count                             34
        {
          c_TurnRate,
          c_IsNotConfigRelevant,
  //      "1234567890123456"
          "TurnRate",
  //      "1234567890"
          "TurnRate",
  //      "12345678901234567890"
          "TurnRate",
          "",
          c_FT_Float,
          c_AlwaysValid,
          c_Unit_Acceleration,
          1,
          0,    0,    0,    0,
          (float*)&(g_FrontEndData.TurnRate),  0.0,  0.0,  0.0
        },
        // count                             35
        //
        // Sensor Data
        //
        {
          c_IAS,
          c_IsNotConfigRelevant,
  //      "1234567890123456"
          "IAS",
  //      "1234567890"
          "IAS",
  //      "12345678901234567890"
          "Dynamische Anzeige",
          "Fluggeschw. geg Luft",
          c_FT_Int16,
          c_AlwaysValid,
          c_Unit_HorizontalSpeed,
          1,
          (int16_t*)&(g_SensorData.IAS),    0,    0,    0,
          0,  0,  0,  0
        },
        // count                             36
        {
          c_CAS,
          c_IsNotConfigRelevant,
  //      "1234567890123456"
          "CAS",
  //      "1234567890"
          "CAS",
  //      "12345678901234567890"
          "Dynamische Anzeige",
          "Calibrated AirSpeed",
          c_FT_Int16,
          c_AlwaysValid,
          c_Unit_HorizontalSpeed,
          1,
          (int16_t*)&(g_FrontEndData.CAS),    0,    0,    0,
          0,  0,  0,  0
        },
        // count                             37
        {
          c_TAS,
          c_IsNotConfigRelevant,
  //      "1234567890123456"
          "TAS",
  //      "1234567890"
          "TAS",
  //      "12345678901234567890"
          "Dynamische Anzeige",
          "wahre Fluggeschwind",
          c_FT_Int16,
          c_AlwaysValid,
          c_Unit_HorizontalSpeed,
          0,
          (int16_t*)&(g_FrontEndData.TAS),  0,  0,  0,
          0,    0,    0,    0
        },
        // count                             38
        {
          c_AmbDensity,
          c_IsNotConfigRelevant,
  //      "1234567890123456"
          "AmbDensity",
  //      "1234567890"
          "Dens",
  //      "12345678901234567890"
          "aktuelle Luftdichte",
          "",
          c_FT_Float,
          c_AlwaysValid,
          c_Unit_Density,
          1,
          0,    0,    0,    0,
          (float*)&(g_SensorData.AmbDensity),  0,  0.0,  0.0
        },
        // count                             39
        {
          c_AmbPressure,
          c_IsNotConfigRelevant,
  //      "1234567890123456"
          "AmbPressure",
  //      "1234567890"
          "Press",
  //      "12345678901234567890"
          "aktueller Luftdruck",
          "",
          c_FT_Float,
          c_AlwaysValid,
          c_Unit_Pressure,
          1,
          0,    0,    0,    0,
          (float*)&(g_SensorData.AmbPressure),  0,  0.0,  0.0
        },
        // count                             40
        {
          c_AmbRelHumidity,
          c_IsNotConfigRelevant,
  //      "1234567890123456"
          "AmbRelHumidity",
  //      "1234567890"
          "Humid",
  //      "12345678901234567890"
          "aktuelle rel Feuchte",
          "",
          c_FT_Float,
          c_AlwaysValid,
          c_Unit_Percentage,
          1,
          0,    0,    0,    0,
          (float*)&(g_SensorData.AmbRelHumidity),  0,  0.0,  0.0
        },
          // count                             41
          {
            c_QNH,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "QNH",
    //      "1234567890"
            "QNH",
    //      "12345678901234567890"
            "aktuelles  QNH",
            "",
            c_FT_Float,
            c_AlwaysValid,
            c_Unit_Pressure,
            1,
            0,    0,    0,    0,
            (float*)&(g_SensorData.QNH),  900.0,  1200.0,  0.1
          },
          // count                             42
          {
            c_QNH_Altitude,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "QNH Altitude",
    //      "1234567890"
            "QNH Alt",
    //      "12345678901234567890"
            "Hoehe ueber QNH",
            "",
            c_FT_Int32,
            c_AlwaysValid,
            c_Unit_Altitude,
            0,
            (int32_t*)&(g_FrontEndData.QNH_Altitude),  0,  30000,  1,
            0,    0,    0,    0
          },
          // count                             43
          {
            c_QNH_Altitude_Gain,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "QNH Alt Gain",
    //      "1234567890"
            "QNHAltGain",
    //      "12345678901234567890"
            "Hoehengewinn",
            "",
            c_FT_Int32,
            c_AlwaysValid,
            c_Unit_Altitude,
            0,
            (int32_t*)&(g_FrontEndData.QNH_Altitude_Gain),  -1000,  30000,  1,
            0,    0,    0,    0
          },
          // count                             44
          {
            c_QFE,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "QFE",
    //      "1234567890"
            "QFE",
    //      "12345678901234567890"
            "eingestelltes QFE",
            "",
            c_FT_Float,
            c_AlwaysValid,
            c_Unit_Pressure,
            1,
            0,    0,    0,    0,
            (float*)&(g_SensorData.QFE),  900.0,  1200.0,  0.1
          },
          // count                             45
          {
            c_QFE_Altitude,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "QFE Altitude",
    //      "1234567890"
            "QFE Alt",
    //      "12345678901234567890"
            "Hoehe ueber QFE",
            "",
            c_FT_Int32,
            c_AlwaysValid,
            c_Unit_Altitude,
            0,
            (int32_t*)&(g_FrontEndData.QFE_Altitude),  0,  30000,  1,
            0,    0,    0,    0
          },
          // count                             46
          {
            c_FL,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "FlightLevel",
    //      "1234567890"
            "FL",
    //      "12345678901234567890"
            "FLight Level bezogen",
            "auf 1013.25 hPa",
            c_FT_Int16,
            c_AlwaysValid,
            c_Unit_FL,
            0,
            (int16_t*)&(g_FrontEndData.FL),  0,  10000,  1,
            0,    0,    0,    0
          },
          // count                             47
          {
            c_PL_SR,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "PlaneSinkRate",
    //      "1234567890"
            "PLSinkRate",
    //      "12345678901234567890"
            "aktuelles Flugzeug-",
            "Sinken/Steigen",
            c_FT_Float,
            c_AlwaysValid,
            c_Unit_ClimbSpeed,
            1,
            0,    0,    0,    0,
            (float*)&(g_FrontEndData.PL_SR),  0,  0,  0
          },
          // count                             48
          {
            c_PL_SR_Average,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "PlaneSAverage",
    //      "1234567890"
            "PLSRAvrge",
    //      "12345678901234567890"
            "mittleres",
            "Flugzeug-Sinken",
            c_FT_Float,
            c_AlwaysValid,
            c_Unit_ClimbSpeed,
            1,
            0,    0,    0,    0,
            (float*)&(g_FrontEndData.PL_SR_Average),  0,  0,  0
          },
          // count                             49
          {
            c_Sens_SR_Average,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "SensorSR Average",
    //      "1234567890"
            "SensAvrge",
    //      "12345678901234567890"
            "Vario-Mittel aus dem",
            "letztem Kreis",
            c_FT_Float,
            c_AlwaysValid,
            c_Unit_ClimbSpeed,
            1,
            0,    0,    0,    0,
            (float*)&(g_FrontEndData.Sens_SR_Average),  0,  0,  0
          },
          // count                             50
          {
            c_True_Average,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "True Therm Avrge",
    //      "1234567890"
            "TrueAvrge",
    //      "12345678901234567890"
            "mittl. Steigen ab",
            "Kurbelbeginn",
            c_FT_Float,
            c_AlwaysValid,
            c_Unit_ClimbSpeed,
            1,
            0,    0,    0,    0,
            (float*)&(g_FrontEndData.True_Average),  0,  0,  0
          },
          // count                             51
          {
            c_AM_SR,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "AirMassSinkRate",
    //      "1234567890"
            "AMSinkRate",
    //      "12345678901234567890"
            "aktuelles Luftmassen",
            "Steigen / Sinken",
            c_FT_Float,
            c_AlwaysValid,
            c_Unit_ClimbSpeed,
            1,
            0,    0,    0,    0,
            (float*)&(g_FrontEndData.AM_SR),  0,  0,  0
          },
          // count                             52
          {
            c_AM_SR_Average,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "AirMassAverage",
    //      "1234567890"
            "AMAvrge",
    //      "12345678901234567890"
            "mittleres",
            "Luftmassen-Sinken",
            c_FT_Float,
            c_AlwaysValid,
            c_Unit_ClimbSpeed,
            1,
            0,    0,    0,    0,
            (float*)&(g_FrontEndData.AM_SR_Average),  0,  0,  0
          },
          // count                             53
          {
            c_WD_Sens,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Sens Wind Dir",
    //      "1234567890"
            "SensWinDir",
    //      "12345678901234567890"
            "Sensor Wind aus",
            "dieser Richtung",
            c_FT_Int16,
            c_ValidOnlyInFlight,
            c_Unit_Angle,
            0,
            (int16_t*)&(g_FrontEndData.WD_Glide),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             54
          {
            c_WS_Sens,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Sens Wind Speed",
    //      "1234567890"
            "SensWndSpd",
    //      "12345678901234567890"
            "Sensor",
            "Windgeschwindigkeit",
            c_FT_Int16,
            c_ValidOnlyInFlight,
            c_Unit_HorizontalSpeed,
            0,
            (int16_t*)&(g_FrontEndData.WS_Glide),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             55
          {
            c_WD_Curr,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Curr Wind Dir",
    //      "1234567890"
            "CurrWDir",
    //      "12345678901234567890"
            "aktuell Windrichtung",
            "",
            c_FT_Int16,
            c_ValidOnlyInFlight,
            c_Unit_Angle,
            0,
            (int16_t*)&(g_FrontEndData.WD_Curr),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             56
          {
            c_WS_Curr,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Curr Wind Speed",
    //      "1234567890"
            "CurrWSpd",
    //      "12345678901234567890"
            "aktuelle",
            "Windgeschwindigkeit",
            c_FT_Int16,
            c_ValidOnlyInFlight,
            c_Unit_HorizontalSpeed,
            0,
            (int16_t*)&(g_FrontEndData.WS_Curr),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             57
          {
            c_W_Curr,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Curr Wind",
    //      "1234567890"
            "CWnd",
    //      "12345678901234567890"
            "aktueller Wind",
            "",
            c_FT_Wind,
            c_ValidOnlyInFlight,
            c_Unit_HorizontalSpeed,
            0,
            (int32_t*)&(g_FrontEndData.W_Curr),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             58
          {
            c_WD_Glide,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "MWindDGlide",
    //      "1234567890"
            "MWDGl",
    //      "12345678901234567890"
            "akt. Windrichtung",
            "beim Gleiten",
            c_FT_Int16,
            c_ValidOnlyInFlight,
            c_Unit_Angle,
            0,
            (int16_t*)&(g_FrontEndData.WD_Glide),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             59
          {
            c_WS_Glide,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "MWindSGlide",
    //      "1234567890"
            "MWSGl",
    //      "12345678901234567890"
            "Windgeschwindigkeit",
            "beim Gleiten",
            c_FT_Int16,
            c_ValidOnlyInFlight,
            c_Unit_HorizontalSpeed,
            0,
            (int16_t*)&(g_FrontEndData.WS_Glide),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             60
          {
            c_W_Glide,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Grad Wind",
    //      "1234567890"
            "GWnd",
    //      "12345678901234567890"
            "Gradientenwind",
            "",
            c_FT_Wind,
            c_ValidOnlyInFlight,
            c_Unit_HorizontalSpeed,
            0,
            (int32_t*)&(g_FrontEndData.W_Glide),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             61
          {
            c_Heading,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Heading",
    //      "1234567890"
            "Heading",
    //      "12345678901234567890"
            "Kompass-Richtung",
            "",
            c_FT_Int16,                 // Compass Value field
            c_AlwaysValid,
            c_Unit_Angle,
            0,
            (int16_t*)&(g_FrontEndData.Heading),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             62
          {
            c_RollAngle,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Roll-Angle",
    //      "1234567890"
            "Roll",
    //      "12345678901234567890"
            "Roll-Winkel",
            "",
            c_FT_Float,
            c_AlwaysValid,
            c_Unit_Angle,
            1,
            0,    0,    0,    0,
            (float*)&(g_FrontEndData.RollAngle),  0,  0.0,  0.0
          },
          // count                             63
          {
            c_PitchAngle,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Pitch-Angle",
    //      "1234567890"
            "Pitch",
    //      "12345678901234567890"
            "Nick-Winkel",
            "",
            c_FT_Float,
            c_AlwaysValid,
            c_Unit_Angle,
            1,
            0,    0,    0,    0,
            (float_t*)&(g_FrontEndData.PitchAngle),  0,  0.0,  0.0
          },
          // count                             64
          {
            c_GPS_UTC_Offset,
            c_IsConfigRelevant,
    //      "012345567890123"
            "UTC_Offset",
    //      "1234567890"
            "UTCOffs",
    //      "12345678901234567890"
            "Offset zu UTC in GPS",
            "in Stunden-Schritten",
            c_FT_Int16,
            c_AlwaysValid,
            c_Unit_Hours,
            0,
            (uint16_t*)&(g_ConfigData.GPS_UTC_Offset),  -12,  12,  1,
            0,    0,    0,    0
          },
          // count                             65
          {
            c_GPS_Date_Time,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "UTC Date Time",
    //      "1234567890"
            "UTC",
    //      "12345678901234567890"
            "UTC Datum und Zeit",
            "aus dem GPS",
            c_FT_Date_Time,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int32_t*)&(g_SensorData.GPS_Date_Time),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             66
          {
            c_LOC_Date_Time,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "LOC Date Time",
    //      "1234567890"
            "LOC",
    //      "12345678901234567890"
            "Lokal-Zeit",
            "(UTC-Offset)",
            c_FT_Date_Time,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int32_t*)&(g_FrontEndData.LOC_Date_Time),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             67
          {
            c_GPS_Altitude,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "GPS Altitude",
    //      "1234567890"
            "GPSAlt",
    //      "12345678901234567890"
            "Hoehe aus dem GPS",
            "",
            c_FT_Int16,
            c_AlwaysValid,
            c_Unit_Altitude,
            0,
            (int16_t*)&(g_SensorData.GPS_Altitude),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             68
          {
            c_GPS_ClimbRate,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "GPS ClimbRate",
    //      "1234567890"
            "GPS CR",
    //      "12345678901234567890"
            "GPS Steigen",
            "",
            c_FT_Float,
            c_AlwaysValid,
            c_Unit_ClimbSpeed,
            1,
            0,    0,    0,    0,
            (float*)&(g_SensorData.GPS_ClimbRate),  0,  0,  0
          },
          // count                             69
          {
            c_GPS_Latitude,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Latitude",
    //      "1234567890"
            "Latitude",
    //      "12345678901234567890"
            "Breite aus GPS",
            "",
            c_FT_LatCoordinate,
            c_AlwaysValid,
            c_Unit_Angle,
            0,
            0,    0,    0,    0,
            &(g_SensorData.GPS_Latitude),  0,  0,  0
          },
          // count                             70
          {
            c_GPS_Longitude,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Longitude",
    //      "1234567890"
            "Longitude",
    //      "12345678901234567890"
            "Laenge aus dem GPS",
            "",
            c_FT_LonCoordinate,
            c_AlwaysValid,
            c_Unit_Angle,
            0,
            0,    0,    0,    0,
            &(g_SensorData.GPS_Longitude),  0,  0,  0
          },
          // count                             71
          {
            c_GPS_Track,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "GPS Track",
    //      "1234567890"
            "GPS Track",
    //      "12345678901234567890"
            "Track aus dem GPS",
            "",
            c_FT_Int16,
            c_AlwaysValid,
            c_Unit_Angle,
            0,
            (uint16_t*)&(g_FrontEndData.GPS_Track),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             72
          {
            c_GPS_GroundSpeed,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "GroundSpeed",
    //      "1234567890"
            "GS",
    //      "12345678901234567890"
            "Grundgeschwindigkeit",
            "aus dem GPS",
            c_FT_Int16,
            c_AlwaysValid,
            c_Unit_HorizontalSpeed,
            0,
            (int16_t*)&(g_FrontEndData.GPS_GroundSpeed),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             73
          {
            c_GPS_NoSats,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "GPS No Sats",
    //      "1234567890"
            "No Sats",
    //      "12345678901234567890"
            "GPS-No of Sats",
            "",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_SensorData.GPS_Condition),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             74
          {
            c_GPS_Condition,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "GPS Condition",
    //      "1234567890"
            "GPS Con",
    //      "12345678901234567890"
            "GPS-Pos Status",
            "0 / 1 / 2 / 3",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_SensorData.GPS_Condition),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             75
          {
            c_NettoAcceleration,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Acceleration",
    //      "1234567890"
            "Accl",
    //      "12345678901234567890"
            "Netto",
            "Acceleration",
            c_FT_Float,
            c_AlwaysValid,
            c_Unit_Acceleration,
            3,
            0,    0,    0,    0,
            (float*)&(g_SensorData.NettoAcceleration),  0,  0,  0
          },
          // count                             76
          {
            c_CurrentFlightStatus,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "PlaneSituation",
    //      "1234567890"
            "PlSit",
    //      "12345678901234567890"
            "Plane on Ground or",
            "airborne",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.CurrentFlightStatus),  0,  1,  1,
            0,    0,    0,    0
          },
          // count                             77
          {
            c_SensorClimbMode,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "SensorClimbMode"  ,
    //      "1234567890"
            "SF-Mode"  ,
    //      "12345678901234567890"
            "Steigen / Sinken",
            "",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_SensorData.SensorClimbMode),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                            78
          {
            c_IntCircleMode,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "IntCircleMode"  ,
    //      "1234567890"
            "SF-Mode"  ,
    //      "12345678901234567890"
            "Steigen - Kreisen",
            "oder Sinken   0 / 1",
            c_FT_Int32,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ProgramStatus.ClimbMode),  0,  2,  2,
            0,    0,    0,    0
          },
          // count                             79
          {
            c_FinalGlideMode,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "FinalGlide",
    //      "1234567890"
            "FinGl",
    //      "12345678901234567890"
            "XXXXXXXXXXXXXXXXXXXX",
            "YYYYYYYYYYYYYYYYYYYY",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_FrontEndData.FinalGlideMode),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             80
    //      "12345678901234"
          {
            c_BrakesExtended,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "BrakesExtended",
    //      "1234567890"
            "AirBrakes",
    //      "12345678901234567890"
            "Bremsklappen ein-",
            "oder ausgefahren",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_FrontEndData.BrakesExtended),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             81
          {
            c_GearExtended,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "GearExtended",
    //      "1234567890"
            "GearExtend",
    //      "12345678901234567890"
            "Fahrwerk ein-",
            "oder ausgefahren",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_FrontEndData.GearExtended),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             82
          {
            c_FlapsPositive,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "FlapsPositive",
    //      "1234567890"
            "Flaps",
    //      "12345678901234567890"
            "Woelbklappenosition",
          "(Future use)",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_FrontEndData.FlapsPositive),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             83
          {
            c_LoggingOn,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "LoggingOn",
    //      "1234567890"
            "LogOn",
    //      "12345678901234567890"
            "internes Logging",
            "ein / aus",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.LoggingOn),  0,  1,  1,
            0,    0,    0,    0
          },
          // count                             84
    //      "12345678901234"
          {
            c_ForceOutPutOfPlaneData,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "OutPlaneData",
    //      "1234567890"
            "OutPlData",
    //      "12345678901234567890"
            "intern",
            "",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.ForceOutPutOfPlaneData),  0,  1,  1,
            0,    0,    0,    0
          },
          // count                             85
          {
            c_Vario_Volume,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Vario_Volume",
    //      "1234567890
            "VarVol",
    //      "12345678901234567890"
            "Lautstaerke",
            "beim Kurbeln",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_Percentage,
            0,
            (int8_t*)&(g_ConfigData.Vario_Volume),  0,  100,  1,
            0,    0,    0,    0
          },
          // count                             86
    //      "12345678901234"
          {
            c_SC_Volume,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "SC_Volume",
    //      "1234567890"
            "SC Vol",
    //      "12345678901234567890"
            "Lautstaerke",
            "beim Gleiten",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_Percentage,
            0,
            (int8_t*)&(g_ConfigData.SC_Volume),  0,  100,  1,
            0,    0,    0,    0
          },
          // count                             87
          {
            c_Vario_MutWinUL,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "VarMutWin_ULim",
    //      "1234567890"
            "VMtWinULim",
    //      "12345678901234567890"
            "Vario-Totband",
            "obere  Grenze",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_Percentage,
            0,
            (int8_t*)&(g_ConfigData.Vario_MuteWinUL),  1,  10,  1,
            0,    0,    0,    0
          },
          // count                             88
          {
            c_Vario_MutWinLL,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "VarMutWin_LLim",
    //      "1234567890"
            "VMtWinLLim",
    //      "12345678901234567890"
            "Vario-Totband",
            "untere Grenze",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_Percentage,
            0,
            (int8_t*)&(g_ConfigData.Vario_MuteWinLL),  -1,  -10,  1,
            0,    0,    0,    0
          },
          // count                             89
          {
            c_SC_MutWinUL,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "SC_MutWin_ULim",
    //      "1234567890"
            "SCMtWnULim",
    //      "12345678901234567890"
            "Sollfahrtton-Totband",
            "obere  Grenze",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_Percentage,
            0,
            (int8_t*)&(g_ConfigData.SC_MuteWinUL),  1,  10,  1,
            0,    0,    0,    0
          },
    //      "12345678901234"
          // count                             90
          {
            c_SC_MutWinLL,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "SC_MutWin_LLim",
    //      "1234567890"
            "SCMtWnLLim",
    //      "12345678901234567890"
            "Sollfahrtton-Totband",
            "untere Grenze",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_Percentage,
            0,
            (int8_t*)&(g_ConfigData.SC_MuteWinLL),  -1,  -10,  1,
            0,    0,    0,    0
          },
          // count                             91
          {
            c_SysTime_mSecs,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "SysTime",
    //      "1234567890"
            "SysTime",
    //      "12345678901234567890"
            "intern",
              "",
            c_FT_Int32,
            c_AlwaysValid,
            c_Unit_Milli_Seconds,
            0,
            (int32_t*)&(g_SystemTime_ms),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             92
          {
            c_SysTime_Secs,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "SysTime",
    //      "1234567890"
            "SysTime",
    //      "12345678901234567890"
            "intern",
              "",
            c_FT_Int32,
            c_AlwaysValid,
            c_Unit_Seconds,
            0,
            (int32_t*)&(g_SystemTime_sec),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             93
          {
            c_CAS_Slope,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "IAS_Slope",
    //      "1234567890"
            "IASSlp",
    //      "12345678901234567890"
            "intern",
              "",
            c_FT_Float,
            c_AlwaysValid,
            c_Unit_NoUnit,
            3,
            0,    0,    0,    0,
            (float*)&(g_SensorData.CAS_Slope),  1,  10,  1
          },
          // count                             94
          {
            c_OAS_Slope,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "OAS_Slope",
    //      "1234567890"
            "OASSlp",
    //      "12345678901234567890"
            "intern",
            "",
            c_FT_Float,
            c_AlwaysValid,
            c_Unit_NoUnit,
            3,
            0,    0,    0,    0,
            (float*)&(g_SensorData.OAS_Slope),  1,  10,  1
          },
          // count                             95
          {
            c_Audio_On,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Audio_On",
    //      "1234567890"
            "AudioOn",
    //      "12345678901234567890"
            "Tongeber",
            " ein / aus    0 / 1",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_FrontEndData.Audio_On),  0,  1,  1,
            0,    0,    0,    0
          },
          // count                             96
          {
            c_Time2SC,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Time2SC",
    //      "1234567890"
            "Time2SC",
    //      "12345678901234567890"
            "Zeit bis Tongeber",
            "",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_FrontEndData.Time2SC),  0,  1,  1,
            0,    0,    0,    0
          },
          // count                             97
          {
            c_Audio_Frequency,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Audio Frequency",
    //      "1234567890"
            "Frequency",
    //      "12345678901234567890"
            "Frequenz des",
            "aktuellen Tons",
            c_FT_Int16,
            c_AlwaysValid,
            c_Unit_Hertz,
            0,
            (uint16_t*)&(g_FrontEndData.Audio_Frequency),  800,  6000,  1,
            0,    0,    0,    0
          },
          // count                             98
          {
            c_Audio_On_Interval,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Tune On Interval",
    //      "1234567890"
            "On Interv",
    //      "12345678901234567890"
            "L�nge des Tone EIN",
            "Intervals",
            c_FT_Int16,
            c_AlwaysValid,
            c_Unit_Milli_Seconds,
            0,
            (uint16_t*)&(g_FrontEndData.Audio_On_Interval),  1,  10,  1,
            0,    0,    0,    0
          },
          // count                             99
          {
            c_Audio_Off_Interval,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Tune OffInterval",
    //      "1234567890"
            "OffInterv",
    //      "12345678901234567890"
            "L�nge des Tone AUS",
            "Intervals",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_Milli_Seconds,
            0,
            (int8_t*)&(g_FrontEndData.Audio_Off_Interval),  1,  10,  1,
            0,    0,    0,    0
          },
          // count                             100
          {
            c_SC_Mute,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Speed_Cmd_Mute",
    //      "1234567890"
            "SCCmd Mute",
    //      "12345678901234567890"
            "intern",
            "Muting by SF Algo",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.SC_Mute),  0,  1,  1,
            0,    0,    0,    0
          },
          // count                             101
          {
            c_SC_Total_Mute,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "SC_Total_Mute",
    //      "1234567890"
            "SC Tot Mut",
    //      "12345678901234567890"
            "Sollfahrt stumm",
            "aus / ein     0 / 1",
            c_FT_Int8,
            c_AlwaysValid,
             c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.Total_Mute),  0,  1,  1,
            0,    0,    0,    0
          },
          // count                             102
          {
            c_FSCSR,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "FullScale",
    //      "1234567890"
            "FS m/s",
    //      "12345678901234567890"
            "Vollausschlag",
            "der Vario-Skala",
            c_FT_Float,
            c_AlwaysValid,
            c_Unit_ClimbSpeed,
            1,
            0,    0,    0,    0,
            (float*)&(g_ConfigData.FSCSR),  5.0,  16.0,  1.0
          },
          // count                             103
          {
            c_FSROOT,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Log Root",
    //      "1234567890"
            "LogRt",
    //      "12345678901234567890"
            "Exponent der Anzeige",
            "Funktion",
            c_FT_Float,
            c_AlwaysValid,
             c_Unit_ClimbSpeed,
            1,
            0,    0,    0,    0,
            (float*)&(g_ConfigData.FSROOT),  1.0,  2.0,  0.01
          },
          // count                             104
          {
            c_VF_Vario_1,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Feld_Var_1",
    //      "1234567890"
            "FeldAuswhl",
    //      "12345678901234567890"
            "Selektor fuer Feld 1",
            "in Vario-Mode",
            c_FT_Field_Sel,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.VF_Vario_1),  0,  c_max_no_of_vario_field_options,  1,
            0,    0,    0,    0
          },
          // count                             105
          {
            c_VF_Vario_2,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Feld_Var_2",
    //      "1234567890"
            "FeldAuswhl",
    //      "12345678901234567890"
            "Selektor fuer Feld 2",
            "in Vario-Mode",
            c_FT_Field_Sel,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.VF_Vario_2),  0,  c_max_no_of_vario_field_options,  1,
            0,    0,    0,    0
          },
          // count                             106
          {
            c_VF_Vario_3,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Feld_Var_3",
    //      "1234567890"
            "FeldAuswhl",
    //      "12345678901234567890"
            "Selektor fuer Feld 3",
            "in Vario-Mode",
            c_FT_Field_Sel,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.VF_Vario_3),  0,  c_max_no_of_vario_field_options,  1,
            0,    0,    0,    0
          },
          // count                             107
          {
            c_VF_Vario_4,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Feld_Var_4",
    //      "1234567890"
            "FeldAuswhl",
    //      "12345678901234567890"
            "Selektor fuer Feld 4",
            "in Vario-Mode",
            c_FT_Field_Sel,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.VF_Vario_4),  0,  c_max_no_of_vario_field_options,  1,
            0,    0,    0,    0
          },
          // count                             108
          {
            c_VF_Vario_5,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Feld_Var_5",
    //      "1234567890"
            "FeldAuswhl",
    //      "12345678901234567890"
            "Selektor fuer Feld 5",
            "in Vario-Mode",
            c_FT_Field_Sel,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.VF_Vario_5),  0,  c_max_no_of_vario_field_options,  1,
            0,    0,    0,    0
          },
          // count                             109
          {
            c_VF_Vario_6,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Feld_Var_6",
    //      "1234567890"
            "FeldAuswhl",
    //      "12345678901234567890"
            "Selektor fuer Feld 6",
            "in Vario-Mode",
            c_FT_Field_Sel,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.VF_Vario_6),  0,  c_max_no_of_vario_field_options,  1,
            0,    0,    0,    0
          },
          // count                             110
          {
            c_VF_SC_1,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Feld_SC_1",
    //      "1234567890"
            "FeldAuswhl",
    //      "12345678901234567890"
            "Selektor fuer Feld 1",
            "in Sollfahrt-Mode",
            c_FT_Field_Sel,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.VF_SC_1),  0,  c_max_no_of_vario_field_options,  1,
            0,    0,    0,    0
          },
          // count                             111
          {
            c_VF_SC_2,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Feld_SC_2",
    //      "1234567890"
            "FeldAuswhl",
    //      "12345678901234567890"
            "Selektor fuer Feld 2",
            "in Sollfahrt-Mode",
            c_FT_Field_Sel,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.VF_SC_2),  0,  c_max_no_of_vario_field_options,  1,
            0,    0,    0,    0
          },
          // count                             112
          {
            c_VF_SC_3,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Feld_SC_3",
    //      "1234567890"
            "FeldAuswhl",
    //      "12345678901234567890"
            "Selektor fuer Feld 3",
            "in Sollfahrt-Mode",
            c_FT_Field_Sel,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.VF_SC_3),  0,  c_max_no_of_vario_field_options,  1,
            0,    0,    0,    0
          },
          // count                             113
          {
            c_VF_SC_4,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Feld_SC_4",
    //      "1234567890"
            "FeldAuswhl",
    //      "12345678901234567890"
            "Selektor fuer Feld 4",
            "in Sollfahrt-Mode",
            c_FT_Field_Sel,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.VF_SC_4),  0,  c_max_no_of_vario_field_options,  1,
            0,    0,    0,    0
          },
          // count                             114
          {
            c_VF_SC_5,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Feld_SC_5",
    //      "1234567890"
            "FeldAuswhl",
    //      "12345678901234567890"
            "Selektor fuer Feld 5",
            "in Sollfahrt-Mode",
            c_FT_Field_Sel,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.VF_SC_5),  0,  c_max_no_of_vario_field_options,  1,
            0,    0,    0,    0
          },
          // count                             115
          {
            c_VF_SC_6,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Feld_SC_6",
    //      "1234567890"
            "FeldAuswhl",
    //      "12345678901234567890"
            "Selektor fuer Feld 6",
            "in Sollfahrt-Mode",
            c_FT_Field_Sel,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.VF_SC_6),  0,  c_max_no_of_vario_field_options,  1,
            0,    0,    0,    0
          },
          // count                             116
          {
            c_Var_Show_OwnAvrge,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "OwnSRAV_Pointer",
    //      "1234567890"
            "OwnSRAvgPt"  ,
    //      "12345678901234567890"
            "Mittleres Steigen",
            "aus / ein     0 / 1",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.Var_Show_OwnAvrge),  0,  1,  1,
            0,    0,    0,    0
          },
          // count                             117
          {
            c_Var_Show_SensorAvrge,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "SensMSRAV_Pointr",
    //      "1234567890"
            "SensSRAvPn"  ,
    //      "12345678901234567890"
            "Mittl. Stg. Sensor",
            "aus / ein     0 / 1",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.Var_Show_SensorAvrge),  0,  1,  1,
            0,    0,    0,    0
          },
          // count                             118
          {
            c_Var_Show_TrueAvrage,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "TrueAV_Pointer",
    //      "1234567890"
            "TrueAvgPnt"  ,
    //      "12345678901234567890"
            "Mittl. Stg. im Bart",
            "aus / ein     0 / 1",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.Var_Show_TrueAvrage),  0,  1,  1,
            0,    0,    0,    0
          },
          // count                            119
          {
            c_Var_Show_AMSR,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "AMSR_Pointer",
    //      "1234567890"
            "AMSR Point"  ,
    //      "12345678901234567890"
            "Luftmassensteigen",
            "aus / ein     0 / 1",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.Var_Show_AMSR),  0,  1,  1,
            0,    0,    0,    0
          },
          // count                             120
          {
            c_Var_Show_AMSRAvrge,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "AMSRAV_Pointer",
    //      "1234567890"
            "AMSRAvgPnt"  ,
    //      "12345678901234567890"
            "Mittl. LM-Steigen",
            "aus / ein     0 / 1",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.Var_Show_AMSRAvrge),  0,  1,  1,
            0,    0,    0,    0
          },
          // count                             121
          {
            c_Var_Show_AM_in_Climb,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "AM_in_Climb",
    //      "1234567890"
            "AM Climb",
    //      "12345678901234567890"
            "Anzeige Luftmassen",
            "beim Kreisen 0 / 1",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.Var_Show_AM_in_Climb),  0,  1,  1,
            0,    0,    0,    0
          },
          // count                             122
          {
            c_Var_Show_Chevron,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Chevron_on_off",
    //      "1234567890"
            "Chevron",
    //      "12345678901234567890"
            "Sollfahrtfehler",
            "aus / ein     0 / 1",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.Var_Show_Chevron),  0,  1,  1,
            0,    0,    0,    0
          },
          // count                             123
          {
            c_ClimbMode_Source_Sel,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "VarModeSelector",
    //      "1234567890"
            "VMSel",
    //      "12345678901234567890"
            "Manual Climb Mode",
            "aus / ein     0 / 1",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.ClimbMode_Source_Sel),  0,  1,  1,
            0,    0,    0,    0
          },
          // count                             124
          {
            c_Time_Selector,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Time_Selector",
    //      "1234567890"
            "Time Selct",
    //      "12345678901234567890"
            "Vario Time Selector",
            "LOC / UTC     0 / 1",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.Time_Selector),  0,  1,  1,
            0,    0,    0,    0
          },
          // count                             125
          {
            c_Pitch_Offset,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Pitch_Offset",
    //      "1234567890"
            "PitchOffs",
    //      "12345678901234567890"
            "Pitch Korrektur",
            "-30 ---- +30 �",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_Angle,
            0,
            (int8_t*)&(g_ConfigData.Pitch_Offset),  -30,  30,  1,
            0,    0,    0,    0
          },
          // count                             126
          {
            c_ForceSDLoad,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Force_SD_Load",
    //      "1234567890"
            "ForcSDLoad",
    //      "12345678901234567890"
            "Force load of config",
            "from SD if available",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,                // 0 no save // 1 save //
            (int8_t*)&(g_ConfigData.ForceSDLoad),  0,  1,  1,
            0,    0,    0,    0
          },
          // count                             127
          {
            c_TIScaleSelector,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "TI_ScaleSelector",
    //      "1234567890"
            "TI Scale",
    //      "12345678901234567890"
            "Select Type of Turn",
            "Indicator Scale",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.TIScaleSelector),  0,  2,  1,
            0,    0,    0,    0
          },
          // count                             128
          {
            c_Average_Source_Sel,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Sel_Average",
    //      "1234567890"
            "SelAverage",
    //      "12345678901234567890"
            "Select average srce",
            "for horizon display",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,         // 0 local SR Average// 1 sensor average// 2 true average
            (int8_t*)&(g_ConfigData.Average_Source_Sel),  0,  2,  1,
            0,    0,    0,    0
          },
          // count                             129
          {
            c_Time2SwitchBack,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Time2SwitchBack",
    //      "1234567890"
            "SwitchBack",
    //      "12345678901234567890",
            "Zeit fuer",
            "Programm-Ruecksprung",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.Time2SwitchBack), c_deferred_action_interval,  60,  1,
            0,    0,    0,    0
          },
          // count                             130
          {
            c_Time2Engrave,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Time_2_Engrave",
    //      "1234567890"
            "TimeEngrav",
    //      "12345678901234567890"
            "Time to settle for a",
            "graphic program",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (int8_t*)&(g_ConfigData.Time2Engrave),  3,  30,  1,
            0,    0,    0,    0
          },
          // count                             131
          {
            c_Speed,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Speed",
    //      "1234567890"
            "Speed",
    //      "12345678901234567890"
            "AirSpeed of Plane",
            "",
            c_FT_Int16,
            c_AlwaysValid,
            c_Unit_HorizontalSpeed,
            0,
            (uint16_t*)&(g_FrontEndData.Speed),  80,  250,  1,
            0,    0,    0,    0
          },
          // count                             132
          {
            c_PolSink,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Polar Sink Rate",
    //      "1234567890"
            "PolSink",
    //      "12345678901234567890"
            "Polar Sink Rate at",
            "airspeed above",
            c_FT_Float,
            c_AlwaysValid,
            c_Unit_ClimbSpeed,
            3,
            0,    0,    0,    0,
            (float*)&(g_FrontEndData.PolSink),  0,  0,  0
          },
          // count                             133
          {
            c_GlRatio,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Glide Ratio",
    //      "1234567890"
            "GlideRatio",
    //      "12345678901234567890"
            "Glide Ratio at",
            "airspeed above",
            c_FT_Float,
            c_AlwaysValid,
            c_Unit_NoUnit,
            1,
            0,    0,    0,    0,
            (int8_t*)&(g_FrontEndData.GlRatio),  0,  0,  0
          },
          // count                             134
          {
            c_Show_Chevron,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "ShowChevron",
    //      "1234567890"
            "ShowChev",
    //      "12345678901234567890"
            "Sow Chevron",
            "",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            1,
            (int8_t*)&(g_FrontEndData.Show_Chevron),  0,  1,  1,
            0,    0,    0,    0
          },
          // count                             135
          {
            c_SensorSystemState,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "Sensor Status",
    //      "1234567890"
            "Sensors",
    //      "12345678901234567890"
            "Status der Sensoren",
            "",
            c_FT_Hex,
            c_AlwaysValid,
            c_Unit_NoUnit,
            1,
            (uint32_t*)&(g_SensorData.SensorSystemState),  0,  1,  1,
            0,    0,    0,    0
          },
          // count                             136
          {
            c_ColorSetting,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "ColorSetting",
    //      "1234567890"
            "Colors",
    //      "12345678901234567890"
            "Farbauswahl",
            "",
            c_FT_Int8,
            c_AlwaysValid,
            c_Unit_NoUnit,
            1,
            (uint16_t*)&(g_ConfigData.ColorSetting),  0,  6,  1,
            0,    0,    0,    0
          },
          // count                             137
          {
            c_Version,
            c_IsConfigRelevant,
    //      "1234567890123456"
            "Version",
    //      "1234567890"
            "Version",
    //      "12345678901234567890"
            "Version und Build",
            "des laufenden Codes",
            c_FT_Version,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (uint32_t*)&(g_ConfigData.Version),  0,  0,  0,
            0,    0,    0,    0
          },
          // count                             138
          {
            c_UpdDateTime,
            c_IsNotConfigRelevant,
    //      "1234567890123456"
            "UpdateTime",
    //      "1234567890"
            "UpdTime",
    //      "12345678901234567890"
            "Zeit der Erzeugung  ",
            "der Config-Daten    ",
            c_FT_Date_Time,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            (uint32_t*)&(g_ConfigData.UpdDateTime),  0,  0,  0,
            0,    0,    0,    0
          },
          // =======================================================================
          // count                             139
          {
            c_Dummy,
            c_IsNotConfigRelevant,
    //      "12345567890123456"
            "DummyDummyDummy",
    //      "1234567890"
            "DummyDummy",
    //      "12345678901234567890"
            "DummyXXXXXXXXXXXXXXX",
            "DummyYYYYYYYYYYYYYYY",
            c_FT_Menue,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            0,  0,    0,    0,
            0,  0.0,  0.0,  0.0
          }
        };
  #endif

  #ifdef	BUILD_BOOTLOADER
    ROM  LongFieldDescriptorItem_t    FieldDescriptors[c_Max_Fields] =
        {
          // count                             0
          {
            c_File_List,
            c_IsNotConfigRelevant,
  //        "1234567890123456"
            "List Hex Files",
  //        "1234567890"
            "HexFiles",
  //        "12345678901234567890"
            "",
            "",
            c_FT_Menue,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            0,  0,    0,    0,
            0,  0.0,  0.0,  0.0
          },
          // count                             1
          {
            c_Max_Menues,
            c_IsNotConfigRelevant,
  //        "1234567890123456"
            "MaxMenueDummy",
  //        "1234567890"
            "Dummy",
  //        "12345678901234567890"
            "XXXXXXXXXXXXXXXXXXXX",
            "YYYYYYYYYYYYYYYYYYYY",
            c_FT_Menue,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            0,    0,    0,    0,
            0,    0.0,  0.0,  0.0
          },
          // count                             2
          {
            c_List_Item_0,
            c_IsNotConfigRelevant,
  //        "1234567890123456"
            "ListItem",
  //        "1234567890"
            "ListItem",
  //        "12345678901234567890"
            "",
            "",
            c_FT_Text,
            c_AlwaysValid,
            c_Unit_NoUnit,
            1,
            (char*)&(g_DirListItems[0]),  0,  0,  0,
            0,  0,  0,  0
          },
          // count                             2
          {
            c_List_Item_1,
            c_IsNotConfigRelevant,
  //        "1234567890123456"
            "ListItem",
  //        "1234567890"
            "ListItem",
  //        "12345678901234567890"
            "",
            "",
            c_FT_Text,
            c_AlwaysValid,
            c_Unit_NoUnit,
            1,
            (char*)&(g_DirListItems[1]),  0,  0,  0,
            0,  0,  0,  0
          },
          // count                             2
          {
            c_List_Item_2,
            c_IsNotConfigRelevant,
  //        "1234567890123456"
            "ListItem",
  //        "1234567890"
            "ListItem",
  //        "12345678901234567890"
            "",
            "",
            c_FT_Text,
            c_AlwaysValid,
            c_Unit_NoUnit,
            1,
            (char*)&(g_DirListItems[2]),  0,  0,  0,
            0,  0,  0,  0
          },
          // count                             2
          {
            c_List_Item_3,
            c_IsNotConfigRelevant,
  //        "1234567890123456"
            "ListItem",
  //        "1234567890"
            "ListItem",
  //        "12345678901234567890"
            "",
            "",
            c_FT_Text,
            c_AlwaysValid,
            c_Unit_NoUnit,
            1,
            (char*)&(g_DirListItems[3]),  0,  0,  0,
            0,  0,  0,  0
          },
          // count                             2
          {
            c_List_Item_4,
            c_IsNotConfigRelevant,
  //        "1234567890123456"
            "ListItem",
  //        "1234567890"
            "ListItem",
  //        "12345678901234567890"
            "",
            "",
            c_FT_Text,
            c_AlwaysValid,
            c_Unit_NoUnit,
            1,
            (char*)&(g_DirListItems[4]),  0,  0,  0,
            0,  0,  0,  0
          },
          // count                             2
          {
            c_List_Item_5,
            c_IsNotConfigRelevant,
  //        "1234567890123456"
            "ListItem",
  //        "1234567890"
            "ListItem",
  //        "12345678901234567890"
            "",
            "",
            c_FT_Text,
            c_AlwaysValid,
            c_Unit_NoUnit,
            1,
            (char*)&(g_DirListItems[5]),  0,  0,  0,
            0,  0,  0,  0
          },
          // count                             2
          {
            c_List_Item_6,
            c_IsNotConfigRelevant,
  //        "1234567890123456"
            "ListItem",
  //        "1234567890"
            "ListItem",
  //        "12345678901234567890"
            "",
            "",
            c_FT_Text,
            c_AlwaysValid,
            c_Unit_NoUnit,
            1,
            (char*)&(g_DirListItems[6]),  0,  0,  0,
            0,  0,  0,  0
          },
          // count                             2
          {
            c_List_Item_7,
            c_IsNotConfigRelevant,
  //        "1234567890123456"
            "ListItem",
  //        "1234567890"
            "ListItem",
  //        "12345678901234567890"
            "",
            "",
            c_FT_Text,
            c_AlwaysValid,
            c_Unit_NoUnit,
            1,
            (char*)&(g_DirListItems[7]),  0,  0,  0,
            0,  0,  0,  0
          },
          // count                             2
          {
            c_List_Item_8,
            c_IsNotConfigRelevant,
  //        "1234567890123456"
            "ListItem",
  //        "1234567890"
            "ListItem",
  //        "12345678901234567890"
            "",
            "",
            c_FT_Text,
            c_AlwaysValid,
            c_Unit_NoUnit,
            1,
            (char*)&(g_DirListItems[8]),  0,  0,  0,
            0,  0,  0,  0
          },
          // count                             2
          {
            c_List_Item_9,
            c_IsNotConfigRelevant,
  //        "1234567890123456"
            "ListItem",
  //        "1234567890"
            "ListItem",
  //        "12345678901234567890"
            "",
            "",
            c_FT_Text,
            c_AlwaysValid,
            c_Unit_NoUnit,
            1,
            (char*)&(g_DirListItems[9]),  0,  0,  0,
            0,  0,  0,  0
          },
          // count                             2
          {
            c_Dummy,
            c_IsNotConfigRelevant,
  //        "12345567890123456"
            "DummyDummyDummy",
  //        "1234567890"
            "DummyDummy",
  //        "12345678901234567890"
            "DummyXXXXXXXXXXXXXXX",
            "DummyYYYYYYYYYYYYYYY",
            c_FT_Menue,
            c_AlwaysValid,
            c_Unit_NoUnit,
            0,
            0,  0,    0,    0,
            0,  0.0,  0.0,  0.0
          }
        };

  #endif

#endif
//
// ******************************************************************************************
//  The End
// ******************************************************************************************

