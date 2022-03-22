/**
  * ###########################################################################
  * @file     Generic_Types.h
  * @brief    New Vario
  * @author   Horst Rupp
  * @brief    Collection of geral types used throughout this project.
  * ###########################################################################
  */

#include  "General_Const.h"
#include  "General_Types.h"

#ifndef __Generic_Types_H
  #define  __Generic_Types_H

  // ***************************************************************************
  //
  // Bit Pattern Queue  definition
  //
  // ***************************************************************************
  //
  typedef struct
  {
    uint8_t   Key;
    int16_t   ThinIncrement;
    int16_t   OuterIncrement;

  } BitPatQItem_t;

  #define    c_MaxElementsBitPatQ 25      // 100 items in Q should be enough
  #define    c_SizeBitPatQ        1024
  #define    c_Size_BitPatQItem   sizeof ( BitPatQItem_t )

  //
  // ***************************************************************************
  //
  // Event Queue definition
  //
  typedef struct
  {
    uint8_t   Command;
    uint16_t  FlapsPosition;
    uint8_t   SwitchPattern;
    uint32_t  SensedValue;

  } EventQItem_t;

  #define    c_MaxElementsEventQ  25      // 100 items in Q should be enough
  #define    c_SizeEventQ         128
  #define    c_Size_EventQItem    sizeof ( EventQItem_t )
  //
  // ***************************************************************************
  //
  // SignalQueue definition
  //
  typedef struct
  {
    uint16_t  Signal_Id;
    uint16_t  Signal_Volume;

  } SignalQItem_t;

  #define    c_MaxElementsSignalQ   25      // 25 items in Q should be enough
  #define    c_SizeSignalQ          128
  #define    c_Size_SignalQItem     sizeof ( SignalQItem_t )
  //
  // ***************************************************************************
  //
  // Audio Queue definition
  //
  typedef struct
  {
    uint8_t   Signal_Id;
    uint16_t  Signal_Volume;
    uint16_t  Audio_Volume;
    float     Audio_Frequency;
    uint16_t  Audio_On_IntVal;
    uint16_t  Audio_Off_IntVal;

  } AudioQItem_t;

  #define    c_MaxElementsAudioQ   25      // 100 items in Q should be enough
  #define    c_SizeAudioQ          128
  #define    c_Size_AudioQItem     sizeof ( AudioQItem_t )
  //
  // ***************************************************************************
  //
  // Radio Queue definition
  //
  typedef struct
  {
    uint8_t Frequency[8];

  } RadioQItem_t;

  #define    c_MaxElementsRadioQ  5      //
  #define    c_SizeRadioQ         128
  #define    c_Size_RadioQItem    sizeof ( RadioQItem_t )

  //
  // ***************************************************************************
  //
  // Signal Queue definition
  typedef struct
  {
    uint16_t  Signal_Id;
    uint16_t  Signal_Volume;

  } BuzzerQItem_t;

  #define     c_MaxElementsBuzzerQ  25      // 100 items in Q should be enough
  #define     c_SizeBuzzerQ         128
  #define     c_Size_BuzzerQItem    sizeof ( BuzzerQItem_t )

  //
  // ***************************************************************************
  //
  // Debug Logger Queue definition
  //
  typedef struct
  {
    uint32_t  Time;
    uint8_t   Name[5];
    uint8_t   Text[100];

  } DBGLoggerQItem_t;

  #define    c_MaxElementsDBGLoggerQ  25      // 100 items in Q should be enough
  #define    c_Size_DBGLoggerQ        128
  #define    c_Size_DBGLoggerQItem    sizeof ( DBGLoggerQItem_t )

  //
  // ***************************************************************************
  //
  // SD Card Logger Queue definition
  //
  typedef struct
  {
    uint32_t  Time;
    uint8_t   Name[5];
    uint8_t   Text[c_big_buffer_size];

  } SDCLoggerQItem_t;

  #define    c_MaxElementsSDCLoggerQ  25      // 100 items in Q should be enough
  #define    c_Size_SDCLoggerQ        128
  #define    c_Size_SDCLoggerQItem    sizeof ( SDCLoggerQItem_t )

#ifdef RUN_EMULATOR
  //
  // ***************************************************************************
  //
  // Sensor_Out Queue definition
  //
  typedef struct
  {
    uint16_t  CAN_Id;
    int16_t   value1;
    int16_t   value2;
    int16_t   value3;
    int16_t   value4;

  } SensorOutQItem_t;

  #define    c_MaxElementsSensorOutQ    5      //
  #define    c_Size_SensorOutQItem      sizeof ( SensorOutQItem_t )
#endif
  // ***************************************************************************
  //
  //  structures for program control
  //
#if ( defined BUILD_VARIO ) || ( defined BUILD_BOOTLOADER )

  typedef  struct
  {
    uint8_t   Idx_Parameter;
    uint8_t   Config;
    uint8_t   TextLeft[c_size_TextLeft];
    uint8_t   TextShort[c_size_TextShort];
    uint8_t   Explanation1[c_size_Explanation];
    uint8_t   Explanation2[c_size_Explanation];
    uint8_t   FieldType;
    uint8_t   ValidInFlight;
    uint8_t   UnitSpec;
    uint8_t   Decimals;
    int32_t*  iPtrToValue;
    int16_t   iLowLim;                //  TODO
    int16_t   iUpLim;
    int16_t   iStepWidth;
    float*    fPtrToValue;
    float     fLowLim;
    float     fUpLim;
    float     fStepWidth;

  }  LongFieldDescriptorItem_t;
  // ***************************************************************************
  // The physical output page
  //
  typedef struct
  {
    uint8_t   TextLeft[c_size_TextWholeLine];
    uint8_t   TextValue[c_size_TextValue];
    uint8_t   TextUnits[c_size_TextUnits];
    uint8_t   Focus;
    uint8_t   CurrFldIdx;
    union
    {
      float   FloatValue;
      int32_t IntValue;
    };

  }  MenueLine_t;

  // ***************************************************************************

  typedef  struct
  {
    uint8_t   TextLeft[c_size_TextLeft];
    uint8_t   TextValue[c_size_TextValue];
    uint8_t   TextUnits[c_size_TextUnits];
    uint8_t   Line1[c_size_Explanation];
    uint8_t   Line2[c_size_Explanation];
  }
  explanation_t;

  // ***************************************************************************

  typedef  struct UnitItem_t
  {
    char      TextUnits[c_size_TextUnits];
  }  UnitItem_t;

  // ***************************************************************************

  typedef  struct
  {
    uint8_t   Idx_Parameter;
    uint8_t   CanBeModified;

  }  ShortFieldDescItem_t;

  // ***************************************************************************

  typedef  struct
  {
    uint8_t               NoOfFields;
                          // includes the menue line of this actual program
    ShortFieldDescItem_t  ShortFieldDesc[c_max_no_of_fields_any_program];

  }  ProgramDescItem_t;

  // ***************************************************************************

  typedef  struct
  {
    uint8_t    err_code_by_value;
    uint8_t    err_code_by_text[50];

  } ErrorMsgTranslator_t;

  // ***************************************************************************

  typedef  struct
  {
    uint8_t    cmd_code_by_value;
    uint8_t    cmd_code_by_text[25];

  } CmdCodeTranslator_t;

  // ***************************************************************************
  //
  // Program Status structure
  //
  typedef struct  ProgramStatusCommon
  {
    int8_t    CurrentProgram; // -3,-2,-1, 0 - c_Max_Menues
    int8_t    CursorOnScreen; //  0 - c_max_no_menue_lines
    int8_t    Focus;          //  enum
                              //  c_Focus_MenueHeader, c_Selectable,
                              //  c_Focus_None, c_Focussed, c_Selected
    int8_t    CurrentOffset;  //  offset of a window of c_max_no_menue_lines
                              //  lines over all lines of the program
    int8_t    MaxOffset;      //
    int8_t    MaxLines;       //  Max no of lines in a program
    uint8_t   IsInitialized;  //  Indicates that the value under a selected
                              //  line has already been moved to the visible
                              //  output value
                              //  This must only happen once,
                              //  as any changes by the user happen directly
                              //  on the visible output value
    int32_t   ClimbMode;      //  Current status
                              //  Climb = 2 / Transient = 1 / Glide = 0
  } Program_t;


  // ***************************************************************************
  // Sensor Data Common structure
  //
  typedef struct  SensorDataCommon
  {
    //
    //  These data items are read from CAN Bus
    //

    float     PL_SR;                  // plane sinkrate im m/s
    float     Sens_SR_Average;        // plane sinkrate im m/s as found in sensor ( 1 circle )
    int32_t   IAS;                    // Indicated Air Speed in km/h
    int32_t   TAS;                    // True Air Speed in km/h
    int32_t   Heading;                // in degrees
    float     RollAngle;              // in decimal degrees
    float     PitchAngle;             // in decimal degrees
    float     LateralAcceleration;    // in multiples of g
    float     TotalAcceleration;      // in multiples of g        experimental
    float     NettoAcceleration;      // in multiples of g        experimental
    int32_t   WD_Sens;                // wind direction in degrees
    int32_t   WS_Sens;                // wind speed in km(h

    int32_t   QFE_Altitude;           // in Meters
    int32_t   QNH_Altitude;           // in Meters
    float     QNH;                    // in hPa
    float     QFE;                    // in hPa
    float     AmbPressure;            // in hPa
    float     AmbDensity;             // in km/m**3
    float     AmbRelHumidity;         // in %

    int32_t   GPS_Date_Time;          // internes gepacktes Format

    int32_t   GPS_GroundSpeed;        // in km/h
    int32_t   GPS_Altitude;           // in Meters
    int32_t   GPS_Track;              // in decimal degrees

    float     GPS_Latitude;           // in Rad
    float     GPS_Longitude;          // in Rad

    int32_t   GPS_Condition;          // 0 - No GPS, 1 - GPS aktive, 2 - 2-D-Fix, 3 - 3-D-Fix
    int32_t   GPS_NoSats;             // 0 - ??

    float     GPS_ClimbRate;          // in m/s

    float     SlipAngle;              // in degree/s
    float     TurnRate;               // in degree/s

    int32_t   SensorClimbMode;        //

    uint32_t  SensorSystemState;      // Status of sensor units


    //
    //  The following data items and values are derived from the above
    //  input values.
    //  The neccessary calculations are performed in task CAN_Bus_Digester,
    //

    int32_t   CAS;                    // derived in CAN-Bus_Receiver
                                      // Calibrated Air Speed in km/h

    float     PL_SR_Average;          // derived in CAN-Bus_Receiver
    float     True_Average;           // derived in CAN-Bus_Receiver

    float     AM_SR;                  // derived in CAN-Bus_Receiver
    float     AM_SR_Average;          // derived in CAN-Bus_Receiver

    int32_t   OAS;                    // derived in CAN-Bus_Receiver
    float     OAS_Average;            // derived in CAN-Bus_Receiver
    float     OAS_Error;              // derived in CAN-Bus_Receiver

    float     OAS_Slope;              // derived in CAN-Bus_Receiver
    float     CAS_Slope;              // derived in CAN-Bus_Receiver

    int32_t   FL;                     // derived in CAN-Bus_Receiver
    int32_t   QNH_Altitude_Gain;      // derived in CAN-Bus_Receiver

    int32_t   WS_Curr;                // derived in CAN-Bus_Receiver
    int32_t   WD_Curr;                // derived in CAN-Bus_Receiver
    int32_t   WD_Curr_Rel;            // derived in CAN-Bus_Receiver
    uint32_t  W_Curr;                 // derived in CAN-Bus_Receiver
                                      // solely for display purpose

    int32_t   WS_Glide;               // derived in CAN-Bus_Receiver
    int32_t   WD_Glide;               // derived in CAN-Bus_Receiver
    int32_t   WD_Glide_Rel;           // derived in CAN-Bus_Receiver
    uint32_t  W_Glide;                // derived in CAN-Bus_Receiver
                                      // solely for display purpose

  } SDC_t;    // Sensor_Data_Structure


  // ***************************************************************************
  //
  // Config Data Common structure
  //
  typedef struct ConfigDataCommon
  {
    uint32_t  Version;
    uint32_t  UpdDateTime;
    uint8_t   ForceSDLoad;
    float     MacCready;
    int32_t   PlaneType;
    int32_t   Ballast;
    int32_t   PilotMass;
    float     Bugs;
    float     Audio_Tau;
    float     Vario_Zeiger_Tau;
    float     Mittl_Steigen_Tau;
    float     SpeedCmd_Tau;
    float     AMM_Tau;
    float     Wind_Tau;
    float     Acceleration_Tau;
    float     GPS_ClimbRate_Tau;
    int32_t   IAS_LL;
    int32_t   IAS_UL;
    int32_t   CAS_LL;
    int32_t   CAS_UL;
    int32_t   Vario_Volume;
    int32_t   Vario_MuteWinUL;
    int32_t   Vario_MuteWinLL;
    int32_t   SC_Volume;
    int32_t   SC_MuteWinUL;
    int32_t   SC_MuteWinLL;
    int32_t   GPS_UTC_Offset;
    int32_t   LoggingOn;
    int32_t   ForceOutPutOfPlaneData;
    int32_t   Total_Mute;
    int32_t   SC_Mute;
    int32_t   CurrentFlightStatus;
    float     FSCSR;
    float     FSROOT;
    int32_t   VMC;
    int32_t   VMO;
    int32_t   VNE;
    uint8_t   VF_Vario_1;
    uint8_t   VF_Vario_2;
    uint8_t   VF_Vario_3;
    uint8_t   VF_Vario_4;
    uint8_t   VF_Vario_5;
    uint8_t   VF_Vario_6;
    uint8_t   VF_SC_1;
    uint8_t   VF_SC_2;
    uint8_t   VF_SC_3;
    uint8_t   VF_SC_4;
    uint8_t   VF_SC_5;
    uint8_t   VF_SC_6;
    uint8_t   Var_Show_OwnAvrge;
    int32_t   Var_Show_SensorAvrge;
    int32_t   Var_Show_TrueAvrage;
    int32_t   Var_Show_AMSR;
    int32_t   Var_Show_AMSRAvrge;
    int32_t   Var_Show_AM_in_Climb;
    int32_t   Var_Show_Chevron;
    int32_t   Time_Selector;
    int32_t   TIScaleSelector;
    int32_t   ClimbMode_Source_Sel;
    int32_t   Pitch_Offset;
    int32_t   Time2SwitchBack;
    int32_t   Time2Engrave;
    int32_t   Average_Source_Sel;
    int32_t   ColorSetting;
    int32_t   CurrentProgram;     // Must be last value !!!
  } CDC_t;

  // ***************************************************************************
  //
  // FrontEnd Data Common structure
  //

  typedef struct FrontEndDataCommon
  {
    float     PL_SR;
    float     PL_SR_Average;
    float     Sens_SR_Average;
    float     True_Average;

    float     AM_SR;
    float     AM_SR_Average;

    int32_t   CAS;
    int32_t   TAS;

    int32_t   OAS;
    float     OAS_Average;
    int32_t   OAS_Error;

    int32_t   QNH_Altitude;
    int32_t   QNH_Altitude_Gain;
    int32_t   QFE_Altitude;
    int32_t   GPS_Altitude;
    int32_t   FL;

    float     Heading;
    float     RollAngle;
    float     PitchAngle;
    float     SlipAngle;
    float     TurnRate;
    int32_t   GPS_Track;
    int32_t   GPS_GroundSpeed;

    int32_t   WD_Curr;
    int32_t   WD_Curr_Rel;
    int32_t   WS_Curr;
    int32_t   W_Curr;

    int32_t   WD_Glide;
    int32_t   WD_Glide_Rel;
    int32_t   WS_Glide;
    int32_t   W_Glide;

    float     MaxLoD;
    int32_t   MaxLoDatOAS;
    int32_t   OASatMC;

    int32_t   LOC_Date_Time;

    int32_t   IntCircleMode;
    int32_t   FinalGlideMode;
    int32_t   FlapsPositive;
    int32_t   GearExtended;
    int32_t   BrakesExtended;

    float     CurrentWingLoad;
    int32_t   PlaneRecalRequired;
    float     Q_Factor;
    float     CAS_Steigung;
    int32_t   CAS_Offset;

    int32_t   Audio_On;
    int32_t   Audio_Frequency;
    int32_t   Audio_On_Interval;
    int32_t   Audio_Off_Interval;
    int32_t   Time2SC;

    int32_t   Speed;
    float     PolSink;
    float     GlRatio;

    int32_t   Show_Chevron;

    uint32_t  SensorSystemState;

  } PDC_t;
#endif

  // ***************************************************************************
  // RecordBuffer
  //
  typedef struct
  {
    uint8_t  buffer[150];
    float  distance;

  } recordbuffer_t;


  #if ( defined BUILD_VARIO )
    // ***************************************************************************
    // Plane
    //

    typedef struct
    {
      float  a;
      float  b;
      float  c;

    } xParabel_t;

    // ***************************************************************************

    typedef struct
    {
      float  CAS;
      float  ClimbRate;

    } PolSinkItem_t;

    // ***************************************************************************

    typedef struct
    {
      char    SettingsName[5];
      float   CAS;

    } FlapDescrItem_t;

    // ***************************************************************************

    typedef struct
    {
      char            Plane_Type_Str[20];
      float           NakedWeight;
      float           WingArea;
      uint16_t        CAS_LL;
      uint16_t        CAS_UL;
      uint16_t        IAS_LL;
      uint16_t        IAS_UL;
      uint16_t        Vmc;
      uint16_t        Vmo;
      uint16_t        Vne;

      float           RefWingLoad;
      float           MaxGlideRatio;
      PolSinkItem_t   PolarCurve[cMaxPolItems];

      #ifdef  FLAPS_AVAILABLE
        uint8_t         NoOfFlapSettings;
        float           FlapsRefMass;
        FlapDescrItem_t Flaps[cMaxFlapsDescrItems];
      #endif


    } Planetype_t;
  #endif



#endif
// *****************************************************************************
// End of File
// *****************************************************************************
