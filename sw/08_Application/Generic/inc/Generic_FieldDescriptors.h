/**
  * ###########################################################################
  * @file     Generic_FieldDescriptors.h
  * @brief    New Vario
  * @author   Horst Rupp
  * @brief    Header file for a file containing the data structures used
  *           to control of the New Vario system.
  * @brief    This is one part of the "C" part of the New Vario MVC structure.
  * ###########################################################################
  */

#include  "Generic_Types.h"

#ifndef __Generic_FieldDescriptors_H
  #define __Generic_FieldDescriptors_H

  extern const UnitItem_t                 Units[];
  extern const ErrorMsgTranslator_t       ErrorMsgTranslator[];
  extern const CmdCodeTranslator_t        CmdCodeTranslator[];
  extern const ProgramDescItem_t          Programs[];
  extern const LongFieldDescriptorItem_t  FieldDescriptors[];
  extern const uint8_t                    VarioFieldOptions[];

  extern const uint8_t txt_Changed_Value_Saved[];
  extern const uint8_t txt_GradPerSec[];
  extern const uint8_t txt_MinPerTurn[];
  extern const uint8_t txt_L_Blank[];
  extern const uint8_t txt_U_Blank[];
  extern const uint8_t txt_SlashCRLF[];
  extern const uint8_t txt_StartUp[];
  extern const uint8_t txt_Equal[];
  extern const uint8_t txt_CRLF[];
  extern const uint8_t txt_EOF[];
  extern const uint8_t txt_Grad_Slash[];
  extern const uint8_t txt_Calc_PolCurve[];
  extern const uint8_t txt_PLN[];
  extern const uint8_t txt_Start_Recalc_1[];
  extern const uint8_t txt_End_Recalc_1[];
  extern const uint8_t txt_Start_Recalc_2[];
  extern const uint8_t txt_End_Recalc_2[];
  extern const uint8_t txt_Start_Recalc_3[];
  extern const uint8_t txt_End_Recalc_3[];
  extern const uint8_t txt_Start_Recalc_4[];
  extern const uint8_t txt_End_Recalc_4[];
  extern const uint8_t txt_Q_Send_Fail[];
  extern const uint8_t txt_Q_Receive_Success[];
  extern const uint8_t txt_MMI[];
  extern const uint8_t txt_Next_Program[];
  extern const uint8_t txt_Prev_Program[];
  extern const uint8_t txt_Obs_Command[];
  extern const uint8_t txt_Carets[];
  extern const uint8_t txt_PSG[];
  extern const uint8_t txt_Push_Signal[];
  extern const uint8_t txt_Fail_Q_Send[];
  extern const uint8_t txt_FRE[];

#endif /* __Generic_FieldDescriptors_H */
