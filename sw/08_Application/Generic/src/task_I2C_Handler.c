/**
 * ###########################################################################
 * @file     task_I2C_Handler.c
 * @brief    New Vario
 * @author   Horst Rupp
 * @brief
 * ############################################################################
 */
//
//  ****************************************************************************
//
// Includes
//

#include  "task_I2C_Handler.h"

extern    AppSignature_t        ThisApplicationsSignature;

#define c_divider 100
//
// *****************************************************************************
// *****************************************************************************

uint8_t   Int_Read_Appl_Data_from_EEProm (void)
{
  uint8_t   status      = true;
  uint16_t  page_no     = c_1st_page_boot_data;


  //I2C HAL driver causes MPU Fault!
  acquire_privileges();
  // Access to a single page with 32 Bytes .
  status = EEProm_ReadPageBytes
        ( page_no, 0, 2, (uint8_t*) &g_CurrEEPromData, sizeof ( AppSignature_t ) );
  drop_privileges();
  if ( ! status )
    I2C1_Init ( );
  //
  return status;
}
//
// ***************************************************************************
//
uint8_t   Int_Clear_Appl_Data_in_EEProm (void)
{
  uint8_t      status      = true;
  uint16_t  page_no     = c_1st_page_boot_data;
  AppSignature_t  LocalApplicationsSignature;


  //I2C HAL driver causes MPU Fault!
  acquire_privileges();
  // Access to a single page with 32 Bytes .

  memset ( (uint8_t*) &LocalApplicationsSignature, 0, sizeof ( AppSignature_t ) );
  status = EEProm_WriteBytes
      ( page_no, 0, 2, (uint8_t*) &LocalApplicationsSignature, sizeof ( AppSignature_t ) );
  if ( status )
  {
    memset ( (uint8_t*) &LocalApplicationsSignature, 0, sizeof ( AppSignature_t ) );
    status = EEProm_ReadPageBytes
        ( page_no, 0, 2, (uint8_t*) &LocalApplicationsSignature, sizeof ( AppSignature_t ) );
  }
  drop_privileges();
  if ( ! status )
    I2C1_Init ( );
  //
  return status;
}
//
// ***************************************************************************
//
uint8_t Int_Save_Appl_Data_to_EEProm ( void )
{
  uint8_t   status      = true;
  uint16_t  page_no     = c_1st_page_boot_data;
  //uint8_t   buffer[c_eeprom_page_size]  = {0};
  AppSignature_t  LocalApplicationsSignature;


  //I2C HAL driver causes MPU Fault!
  acquire_privileges();
  // Access to a single page with 32 Bytes .
  status = EEProm_WriteBytes
          ( page_no, 0, 2, (uint8_t*) &ThisApplicationsSignature, sizeof ( AppSignature_t ) );
  if ( status )
  {
    // just to check
    status = EEProm_ReadPageBytes
        ( page_no, 0, 2, (uint8_t*) &LocalApplicationsSignature, sizeof ( AppSignature_t ) );
  }
  drop_privileges();//
  if ( ! status )
    I2C1_Init ( );
  return status;

}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************
//
#ifdef  BUILD_VARIO
  uint8_t Int_Read_Config_Data_from_EEProm ( void )
  {
    uint8_t     status;
    uint32_t    data_address;
    uint16_t    page_no, max_page_no;

    data_address  = (uint32_t) &g_ConfigData;
    page_no       = c_1st_page_config_data;
    max_page_no   = c_1st_page_config_data + c_cnt_of_config_pages;
    status        = true;

    while ( status && ( page_no < max_page_no ) )
    {
      acquire_privileges();
      // Access to a single page with 32 Bytes .
      status = EEProm_ReadPageBytes
            ( page_no, 0, 2, (uint8_t*) data_address, c_eeprom_page_size );
      drop_privileges();//
      //
      //  advance page_no and data_address and do it again
      //
      page_no++;
      data_address += c_eeprom_page_size;
    }
    //
    if ( ! status )
      I2C1_Init ( );
    return status;
  }

//
// ***************************************************************************
//
  uint8_t Int_Save_Config_Data_to_EEProm ( void )
  {
    uint8_t   status;
    uint32_t  data_address;
    uint16_t    page_no, max_page_no;

    data_address  = (uint32_t) &g_ConfigData;
    page_no       = c_1st_page_config_data;
    max_page_no   = c_1st_page_config_data + c_cnt_of_config_pages;
    status        = true;

    while ( status && ( page_no < max_page_no ) )
    {
      //I2C HAL driver causes MPU Fault!
      acquire_privileges();
      // Access to a single page with 32 Bytes .
      status = EEProm_WriteBytes
              ( page_no, 0, 2, (uint8_t*) data_address, c_eeprom_page_size );
      drop_privileges();//
      page_no++;
      data_address += c_eeprom_page_size;
    }
    if ( ! status )
      I2C1_Init ( );
    return status;
  }
  //
  // ***************************************************************************
  //
  uint8_t Int_Read_LogBook_Data_from_EEProm ( void )
  {
    uint8_t     status;
    uint32_t    data_address;
    uint16_t    page_no, max_page_no;

    data_address  = (uint32_t) &g_LogBook;
    page_no       = c_1st_page_logbook_data;
    max_page_no   = c_1st_page_logbook_data + c_cnt_of_logbook_pages;
    status        = true;

    while ( status && ( page_no < max_page_no ) )
    {
      acquire_privileges();
      // Access to a single page with 32 Bytes .
      status = EEProm_ReadPageBytes
            ( page_no, 0, 2, (uint8_t*) data_address, c_eeprom_page_size );
      drop_privileges();//
      //
      //  advance page_no and data_address and do it again
      //
      page_no++;
      data_address += c_eeprom_page_size;
    }
    //
    if ( ! status )
      I2C1_Init ( );
    return status;
  }

  //
  // ***************************************************************************
  //
  uint8_t Int_Save_LogBook_Data_to_EEProm ( void )
  {
    uint8_t   status;
    uint32_t  data_address;
    uint16_t    page_no, max_page_no;

    data_address  = (uint32_t) &g_LogBook;
    page_no       = c_1st_page_logbook_data;
    max_page_no   = c_1st_page_logbook_data + c_cnt_of_logbook_pages;
    status        = true;

    while ( status && ( page_no < max_page_no ) )
    {
      //I2C HAL driver causes MPU Fault!
      acquire_privileges();
      // Access to a single page with 32 Bytes .
      status = EEProm_WriteBytes
              ( page_no, 0, 2, (uint8_t*) data_address, c_eeprom_page_size );
      drop_privileges();//
      page_no++;
      data_address += c_eeprom_page_size;
    }
    if ( ! status )
      I2C1_Init ( );
    return status;
  }
#endif
//
//  ****************************************************************************
//  ****************************************************************************
//  ****************************************************************************
//  ****************************************************************************
//
void I2C_Handler ( void * nix )
{
  uint16_t  l_q_result;
  uint8_t   l_Old_Switch_Setting = 0;
  uint8_t   l_status, l_count;
  uint8_t   l_divider = c_divider;

  //
  // initialize I2C and EEProm access
  //
  I2C1_Init ( );

  //
  // the works
  //
  while(1)
  {
    vTaskDelay( c_WakeIOFrontEnd );              // loop 10 msec

#ifdef  BUILD_VARIO
    //
    // ---------------------------------------------------
    //
    //  Read external switch with each turn
    //
    if ( l_divider-- == 0  )
    {
      g_SensorData.IOExpSwitchClimbMode = c_Transition;
      g_SensorData.IOExpSwitchClimbMode = Read_SC_Switch ( );
      if  (
            ( c_Transition != g_SensorData.IOExpSwitchClimbMode )
          &&
            ( l_Old_Switch_Setting != g_SensorData.IOExpSwitchClimbMode )
          &&
            ( g_switch_cycle_count < 20 )
          &&
            ( g_ProgramStatus.FlightStatus == c_DuringTakeOff )
          )
      {
        g_switch_cycle_count++;
        l_Old_Switch_Setting = g_SensorData.IOExpSwitchClimbMode;
      }
      l_divider = c_divider;
    }
#endif

    //
    //  other function are on call only
    //
    //I2C_Handler_InQItem.FunctionSelector = c_Fct_Do_Nothing;

    l_q_result = xQueueReceive ( I2C_Handler_InQId, &I2C_Handler_InQItem, 200 );
    if ( l_q_result == 1 )
    {
      //
      //  function dispatcher
      //
      l_status  = false;
      l_count   = 3;

      //I2C_Handler_InQItem.FunctionSelector = c_Fct_Do_Nothing; //   debug only

      switch ( I2C_Handler_InQItem.FunctionSelector )
      {
        case c_Fct_Do_Nothing :
          I2C_Handler_OutQItem.Status = true;
          l_q_result = xQueueSend ( I2C_Handler_OutQId, &I2C_Handler_OutQItem, 200 );
          if ( l_q_result != 1 )
            asm("bkpt 0");
          break;

        case c_Fct_Read_Appl_Data_from_EEProm :
          //
          //  Fire and forget
          //
          while ( ( ! l_status ) && ( l_count-- > 0 ) )
            l_status = Int_Read_Appl_Data_from_EEProm ( );
          I2C_Handler_OutQItem.Status = l_status;
          l_q_result = xQueueSend ( I2C_Handler_OutQId, &I2C_Handler_OutQItem, 200 );
          if ( l_q_result != 1 )
            asm("bkpt 0");
          break;

        case c_Fct_Clear_Appl_Data_in_EEProm :
          //
          //  Fire and forget
          //
          while ( ( ! l_status ) && ( l_count-- > 0 ) )
            l_status = Int_Clear_Appl_Data_in_EEProm ( );
          I2C_Handler_OutQItem.Status = l_status;
          l_q_result = xQueueSend ( I2C_Handler_OutQId, &I2C_Handler_OutQItem, 200 );
          if ( l_q_result != 1 )
            asm("bkpt 0");
          break;

        case c_Fct_Save_Appl_Data_to_EEProm :
          //
          //  Fire and forget
          //
          while ( ( ! l_status ) && ( l_count-- > 0 ) )
            l_status = Int_Save_Appl_Data_to_EEProm ( );
          I2C_Handler_OutQItem.Status = l_status;
          l_q_result = xQueueSend ( I2C_Handler_OutQId, &I2C_Handler_OutQItem, 200 );
          if ( l_q_result != 1 )
            asm("bkpt 0");
          break;

#ifdef  BUILD_VARIO
        case c_Fct_Read_Config_Data_from_EEProm :
          //
          //  must be synchronized
          //
          while ( ( ! l_status ) && ( l_count-- > 0 ) )
            l_status = Int_Read_Config_Data_from_EEProm ( );
          I2C_Handler_OutQItem.Status = l_status;
          l_q_result = xQueueSend ( I2C_Handler_OutQId, &I2C_Handler_OutQItem, 200 );
          if ( l_q_result != 1 )
            asm("bkpt 0");
          break;

        case c_Fct_Save_Config_Data_to_EEProm :
          //
          //  must be synchronized
          //
          while ( ( ! l_status ) && ( l_count-- > 0 ) )
            l_status = Int_Save_Config_Data_to_EEProm ( );
          I2C_Handler_OutQItem.Status = l_status;
          l_q_result = xQueueSend ( I2C_Handler_OutQId, &I2C_Handler_OutQItem, 200 );
          if ( l_q_result != 1 )
            asm("bkpt 0");
          break;

        case c_Fct_Read_LogBook_Data_from_EEProm :
          //
          //  must be synchronized
          //
          while ( ( ! l_status ) && ( l_count-- > 0 ) )
            l_status = Int_Read_LogBook_Data_from_EEProm ( );
          I2C_Handler_OutQItem.Status = l_status;
          l_q_result = xQueueSend ( I2C_Handler_OutQId, &I2C_Handler_OutQItem, 200 );
          if ( l_q_result != 1 )
            asm("bkpt 0");
          break;

        case c_Fct_Save_LogBook_Data_to_EEProm :
          //
          //  must be synchronized
          //
          while ( ( ! l_status ) && ( l_count-- > 0 ) )
            l_status = Int_Save_LogBook_Data_to_EEProm ( );
          I2C_Handler_OutQItem.Status = l_status;
          l_q_result = xQueueSend ( I2C_Handler_OutQId, &I2C_Handler_OutQItem, 200 );
          if ( l_q_result != 1 )
            asm("bkpt 0");
          break;
#endif
      }
      if ( l_count == 0 )
        asm("bkpt 0");
    }
  }
}

//
//  ****************************************************************************
//  ****************************************************************************
//

static ROM TaskParameters_t PARAMETER =
{
    I2C_Handler,
    "I2C",
    512,
    0,
    Prio_I2C,
    0,
    {
        { COMMON_BLOCK, COMMON_SIZE, portMPU_REGION_READ_WRITE },
        { 0, 0, 0 },
        { 0, 0, 0 }
    }
};

void create_task_I2C_Handler( void )
{
  (void)create_restricted_task( &PARAMETER);
}

//
// *****************************************************************************
// The End
// *****************************************************************************

