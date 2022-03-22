/**
  * ############################################################################
  * @file     task_Audio_Controller.c
  * @brief    New Vario
  * @author   Horst Rupp
  * @brief    This task controls the audio output to the speaker.
  * ############################################################################
  */
//
// Includes
//
#include  "General_Includes.h"
#include  "Generic_Common.h"
#include  "Generic_Includes.h"

#include  "task_Audio_Controller.h"
#include  "Audio_Lib.h"
#include  "can.h"
#include  "math.h"
#include  "Generic_CAN_Ids.h"

#define   c_max_tschirp_counter   12
#define   c_echo                  3
#define   c_basic_constant        1.0164F
#define   c_tschirp_step          ( 2.0 / ( c_max_tschirp_counter - c_echo + 5 ) )
#define   c_tune_duration         1
#define   c_tschirp_duration      ( c_tune_duration * c_max_tschirp_counter )


//
//  Parameters which control behavior of this task
//    - g_NormedFrequency   int32_t / 10e6      -2 --- 0 ---- +2
//    - g_Interval          uint16_t            ?? -- 200 [msec]
//    - g_Audio_Volume      uint8_t             0 -- 100 [% max Volume]
//    - g_Duty_Cycle        uint8_t             10 - 80
//    - g_climbmode         uint8_t             0 for cruise  / 2 for climb
//
//    - g_Signal_Id         uint8_t             nn
//    - g_Signal_Volume     uint8_t             0 -- 100 [% max Volume]

//
// *****************************************************************************
//
void Audio_Controller ( void * nix )
{

  uint16_t  l_Audio_Volume;
  float     l_Audio_Frequency;
  float     l_NormedFrequency = 0.0;
  float     l_exp;
  float     l_frequency_factor;
  int16_t   l_intval_counter          = 0;
  uint16_t  l_intval_off_switch_value = 50,
            l_intval_on_switch_value  = 50;
  uint8_t   ix;
  float     l_frq_Signal[c_max_tschirp_counter];
  uint8_t   l_cycle_index = 0;
  uint16_t  l_old_signal_count = 0;
  uint16_t  l_Interval;
  int16_t   l_Inv_Interval;
  //
  //  **************************************************************************
  //
  g_HeartBeat_Count = 0;
  g_Signal_Count    = 0;
  Start_Audio ( 0, c_mid_frequency );

  // the works
  //
  while( 1 )  // ******************* LOOP **************************************
  {
    vTaskDelay ( c_WakeAudioController );

    g_Time_in_Ticks   = xTaskGetTickCount( );   // Laut Klaus in msec  !!??!!##
    g_SystemTime_ms   = g_Time_in_Ticks;
    g_SystemTime_sec  = g_Time_in_Ticks / 1000;

    //
    // stop audio as soon as connection to Vario is interrupted
    //
    if ( g_HeartBeat_Count > 0 )    //
    {
      g_HeartBeat_Count--;
      //
      //  if we have an active signal ID
      //  this signal processing precedes to any tune processing
      //
      //  if signal Q not empty, send data
      //
      if ( ( g_Signal_ID == 0 ) && ( uxQueueMessagesWaiting( SignalQId ) > 0 ) )
      {
        if ( xQueueReceive ( SignalQId, &SignalQItem, 200 ) == 1 )
        {
          g_Signal_ID     = SignalQItem.Signal_Id;
          g_Signal_Volume = SignalQItem.Signal_Volume;
          g_Signal_Count  = 0;
        }
      }


      if ( g_Signal_ID != 0 )
      {
        //
        //  start signal process
        //
        //l_Audio_Volume = g_Signal_Volume;

        switch ( g_Signal_ID  )
        {
          case cAlarm :
            {
              switch ( g_Signal_Count )
              {
                case 0 :
                  l_Audio_Volume = g_Signal_Volume;
                  l_Audio_Frequency = 2200;
                  break;
                case 10 :
                  l_Audio_Frequency = 5500;
                  break;
                case 20 :
                  l_Audio_Frequency = 2200;
                  break;
                case 30 :
                  l_Audio_Frequency = 5500;
                  break;
                case 50 :
                  l_Audio_Volume = 0;
                  break;
                case 55 :
                  g_Signal_ID = 0;
                  g_Signal_Count = 0;
                  break;
              } // switch g_Signal_Count
            }
            break;

          case cTransfer :
            {
              switch ( g_Signal_Count )
              {
                case 0 :
                  l_Audio_Volume = g_Signal_Volume;
                  l_Audio_Frequency = 2200;
                  break;
                case 5 :
                  l_Audio_Frequency = 3300;
                  break;
                case 10 :
                  l_Audio_Frequency = 4400;
                  break;
                case 15 :
                  l_Audio_Frequency = 5500;
                  break;
                case 20 :
                  l_Audio_Frequency = 2200;
                  break;
                case 25 :
                  l_Audio_Frequency = 3300;
                  break;
                case 30 :
                  l_Audio_Frequency = 4400;
                  break;
                case 35 :
                  l_Audio_Frequency = 5500;
                  break;
                case 40 :
                  l_Audio_Frequency = 2200;
                  break;
                case 45 :
                  l_Audio_Frequency = 3300;
                  break;
                case 50 :
                  l_Audio_Frequency = 4400;
                  break;
                case 55 :
                  l_Audio_Frequency = 5500;
                  break;
                case 60 :
                  l_Audio_Volume = 0;
                  break;
                case 65 :
                  g_Signal_ID = 0;
                  g_Signal_Count = 0;
                  break;
              } // switch g_Signal_Count
            }
            break;

          case cAutoChange :
            {
              switch ( g_Signal_Count )
              {
                case 0 :
                  l_Audio_Volume = g_Signal_Volume;
                  l_Audio_Frequency = 2200;
                  break;
                case 8 :
                  l_Audio_Frequency = 3300;
                  break;
                case 16 :
                  l_Audio_Frequency = 4400;
                  break;
                case 26 :
                  l_Audio_Frequency = 6600;
                  break;
                case 38 :
                  l_Audio_Volume = 0;
                  break;
                case 43 :
                  g_Signal_ID = 0;
                  g_Signal_Count = 0;
                  break;
              } // switch g_Signal_Count
            }
            break;

          case cInvAutoChange :
            {
              switch ( g_Signal_Count )
              {
                case 0 :
                  l_Audio_Volume = g_Signal_Volume;
                  l_Audio_Frequency = 6600;
                  break;
                case 8 :
                  l_Audio_Frequency = 4400;
                  break;
                case 16 :
                  l_Audio_Frequency = 3300;
                  break;
                case 26 :
                  l_Audio_Frequency = 2200;
                  break;
                case 38 :
                  l_Audio_Volume = 0;
                  break;
                case 43 :
                  g_Signal_ID = 0;
                  g_Signal_Count = 0;
                  break;
              } // switch g_Signal_Count
            }
            break;

          case cBeep :
            {
              switch ( g_Signal_Count )
              {
                case 0 :
                  l_Audio_Volume = g_Signal_Volume;
                  l_Audio_Frequency = 5000;
                  break;
                case 20 :
                  l_Audio_Volume = 0;
                  break;
                case 25 :
                  g_Signal_ID = 0;
                  g_Signal_Count = 0;
                  break;
              } // switch g_Signal_Count
            }
            break;

          case cClick :
            {
              switch ( g_Signal_Count )
              {
                case 0 :
                  l_Audio_Volume = g_Signal_Volume;
                  l_Audio_Frequency = 7000;
                  break;
                case 2 :
                  l_Audio_Volume = 0;
                  break;
                case 7 :
                  g_Signal_ID = 0;
                  break;
              } // switch g_Signal_Count
            }
            break;

        }; // switch m_CurrentSignal
        g_Signal_Count++;
        //
        //  *** End of SIGNAL processing ********************************************
        //
      }
      else
      //
      //  no signal processing required --> just tune for vario or speed command
      //  as from here on every loop : every 10 msec
      //
      {
        if ( g_NormedFrequency < -2.0 )
          g_NormedFrequency = -2.0;
        if ( g_NormedFrequency > +2.0 )
          g_NormedFrequency = +2.0;

        if ( g_Duty_Cycle < c_min_duty_cycle )
          g_Duty_Cycle = c_min_duty_cycle;
        if ( g_Duty_Cycle > c_max_duty_cycle )
          g_Duty_Cycle = c_max_duty_cycle;

        if ( g_Interval > 500 )
          g_Interval = 500;

        l_Audio_Frequency = 880;     // Kammerton A
        l_Audio_Volume    = g_Audio_Volume;

        if ( l_Audio_Volume != 0 )
        {
          //
          // Further actions depend on flight mode
          //
          if ( g_climbmode == c_Climbing )  // if climb  *************************************
          {
            l_NormedFrequency = g_NormedFrequency;
            //
            //  Translation of Normed-Frequency into real frequency
            //  Exponential function
            //
            l_exp = ( g_NormedFrequency + 2.0 ) / 4.0 * 100.0;
            //acquire_privileges();
            l_Audio_Frequency = pow ( c_basic_constant, l_exp ) * c_min_frequency;
            //drop_privileges();

            //
            //  When g_NormedFrequency signals CLIMB
            //
            //  Controlling the beep by manipulation of volume
            //  g_Interval < 10 --> no interval
            //
            if  (
                  ( g_NormedFrequency > 0.0 )
                &&
                  ( g_Interval >= 10 )
                )
            {
              if ( l_intval_counter <= 0 )
              {
                l_intval_counter = g_Interval / c_WakeAudioController;  // cycles per interval
                l_intval_on_switch_value = floor ( (float) g_Duty_Cycle / 100.0 * l_intval_counter );
                l_intval_off_switch_value = l_intval_counter - l_intval_on_switch_value;
              }

              if  (
                    ( l_intval_counter > 0 )
                  &&
                    ( l_intval_counter-- <= l_intval_off_switch_value )
                  )
              {
                l_Audio_Volume = 0.0;
              }
            }
          }

          else                //  if cruise ************************************
          {
            if ( g_NormedFrequency <= 0.0 )    // fly slower signal
            {
              l_NormedFrequency = g_NormedFrequency;  // steady signal
              g_Signal_Count = 0;
            }
            else
            {
              //
              // setting up the signal array happens only on the first cycle of g_Signal_Count
              //
              l_Interval = floor ( 100.0 / g_Duty_Cycle * c_tschirp_duration );
              l_Inv_Interval = l_Interval - c_tschirp_duration;
              if ( g_Signal_Count == 0 )
              {
                l_old_signal_count  = 0;
                //
                //  Build the signal sequence for the tschirp
                //
                for ( ix = 0; ix < c_max_tschirp_counter - c_echo; ix++ )
                {
                  l_frq_Signal[ix] = g_NormedFrequency + c_tschirp_step * ix;
                }
                for ( ix = c_max_tschirp_counter - c_echo; ix < c_max_tschirp_counter; ix++ )
                {
                  l_frq_Signal[ix] = l_frq_Signal[ix-1];
                }
                l_intval_counter = l_Interval;
                l_cycle_index = 0;
              }

              if  ( l_intval_counter-- < l_Inv_Interval )
              {
                l_Audio_Volume = 0.0;
              }
              else
              {
                //
                // freq change
                //
                l_NormedFrequency = l_frq_Signal[l_cycle_index];
                if ( g_Signal_Count > l_old_signal_count + c_tune_duration )
                {
                  l_NormedFrequency = l_frq_Signal[l_cycle_index];
                  l_cycle_index++;
                  l_old_signal_count = g_Signal_Count - 1;
                }
              }
            }

            if ( l_NormedFrequency > 2.0 ) l_NormedFrequency = 2.0;
            if ( l_NormedFrequency < -2.0 ) l_NormedFrequency = -2.0;
            l_exp = ( l_NormedFrequency + 2.0 ) / 4.0 * 100.0;
            //acquire_privileges();
            l_Audio_Frequency = pow ( c_basic_constant, l_exp ) * c_min_frequency;
            //drop_privileges();
            if ( l_cycle_index >= c_max_tschirp_counter )
            {
              l_Audio_Volume = 0;
              l_cycle_index = 0;
            }

            g_Signal_Count++;

            if  ( l_intval_counter <= 0 )
              g_Signal_Count = 0;
          }

          //
          //  ******************************************************************
          //
          //  Physiologically,
          //  higher frequencies are perceived louder than lower frequencies
          //  This is to compensate this effect
          //
          l_frequency_factor = ( ( - g_NormedFrequency / 2.0 * 0.7 ) + 1.0 );
          if ( l_frequency_factor > 1.0 )
            l_Audio_Volume *= l_frequency_factor;

          if ( l_Audio_Volume > 100 )
            l_Audio_Volume = 100;
        }
      }
    }
    else
    {
      l_Audio_Volume     = 5;       // leise
      l_Audio_Frequency  = 880;     // Kammerton A
    }
    g_Next_Volume     = l_Audio_Volume;       // controlling device
    g_Next_Frequency  = l_Audio_Frequency;

    //
    //  *** End of AUDIO processing ********************************************
    //
  } // while ( 1 )
}

//
// *******************************************************************************
// The End
// *******************************************************************************

