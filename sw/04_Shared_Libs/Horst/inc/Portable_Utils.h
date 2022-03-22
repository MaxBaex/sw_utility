/**
  * ###########################################################################
  * @file     Portable_Utils.h
  * @brief    New Vario
  * @author   Horst Rupp
  * @brief    Header for library containing all portable basic functions.
  * ###########################################################################
  */

  #include  "General_Includes.h"


#ifndef _Utils_H
  #define _Utils_H

  //
  // ****************************************************************************

  #define   c_len_coord_buffer         11

  //
  // ***************************************************************************

  #ifdef __cplusplus
    extern "C" {
  #endif

  uint8_t   inRange                   ( int32_t  low, int32_t high, int32_t x );
  uint8_t   Count_8_Bits              ( uint8_t bit_pattern );
  uint8_t   Count_16_Bits             ( uint16_t bit_pattern );
  uint8_t   portable_isspace          ( char x );
  uint8_t   portable_isdigit          ( char x );
  uint8_t   portable_islowcasechar    ( char x );
  uint8_t   portable_isuppcasechar    ( char x );
  uint8_t   portable_isprintablechar  ( char x );
  void      portable_skipleadchar     ( char * dest, uint8_t drop_count );
  uint16_t  portable_strlen           ( const char * ValText );
  char *    portable_strcpy           ( char * dest, const char * source );
  char *    portable_strcpy_safe      ( char * dest, const char * source,
                                        uint8_t dest_size );
  char *    portable_strcat           ( char * dest, const char * source );
  int8_t    portable_strcmp           ( const char * dest, const char * source );
  char *    portable_strtoupper       ( char * thestring );
  char *    portable_strtolower       ( char * thestring );
  char *    portable_trimtrailing     ( char *input, char chartotrim );
  char *    portable_trimleading      ( char *input, char chartotrim );
  char *    portable_trimanywhere     ( char *input, char chartotrim );
  char *    portable_compress         ( char *input );
  void      portable_streverse        ( char* str, int len );
  char *    portable_strstr           ( const char* str, const char* needle );

  char *    portable_charreplace      ( char* str, char find, char replace);
  char *    portable_strreplace       ( char *search , char *replace ,
                                        char *subject);
  uint16_t  portable_strpos           ( char *haystack, char *needle);
  uint16_t  portable_strsplit         ( char* portable_String, char** Items,
                                        char Delimiter, char EOT);

  void      portable_memcpy           ( uint8_t * dest, uint8_t * source,
                                        uint32_t size );
  void      portable_memset           ( uint8_t * dest, uint8_t   value,
                                        uint32_t size );
  uint16_t  portable_memcmp           ( uint8_t * dest, uint8_t * source,
                                        uint32_t size );

  void      portable_ftoa             ( float n, char* res, uint8_t afterpoint,
                                        uint8_t len );
  uint8_t   portable_itoa2            ( int32_t n, char* res, uint8_t res_len,
                                        uint8_t prefix_pad_req,
                                        char prefix_pad_char );
  uint8_t   portable_itoa             ( int32_t n, char* res, uint8_t res_len );
  int       portable_max              ( int Val1, int Val2 );
  int       portable_min              ( int Val1, int Val2 ) ;
  float     portable_fmax             ( float Val1, float Val2 );
  float     portable_fmin             ( float Val1, float Val2 ) ;
  double    portable_fmod             ( float Val1, float Val2 );
  float     portable_round_2_n_decmls ( float Val1, int Val2 );
  int32_t   portable_round_2wards_zero( float Val1 );
  int		    sign_int				          ( int value );
  int		    sign_long				          ( long value );
  int		    sign_float				        ( float value );
  int		    sign_double				        ( double value );
  float     portable_safe_tan         ( float Val );
  float     portable_atof             ( const char * ValText );
  int16_t   portable_atoi             ( const char * ValText );
  int32_t   portable_atol             ( const char * ValText );
  uint8_t   byte_2_hex                ( uint8_t byteval );
  void      portable_uint32_2_hex_str ( uint32_t n, char* res );
  uint8_t * portable_Decimal_to_Binary (  uint32_t Data, uint8_t NoOfBits,
                                          uint8_t * outbuffer );

  uint8_t   portable_Binary_2_BCD     ( uint8_t input );
  uint8_t   portable_BCD_2_Binary     ( uint8_t input );

  void      lat_rad_2_NS_DDMMSS       ( float latitude_rad, uint8_t * buffer );
  void      lon_rad_2_EW_DDDMMSS      ( float longitude_rad, uint8_t * buffer );
  void      lat_dec_deg_2_NS_DDMMSS   ( float latitude_deg, uint8_t * buffer );
  void      lon_dec_deg_2_EW_DDDMMSS  ( float longitude_deg, uint8_t * buffer );

  void      MapCoordinates2Canvas     ( point_i16_t * StartPoint );
  void      OffsetCoordinates         ( point_i16_t * Offset,
                                        point_i16_t * StartPoint );
  void      RotateFlatCoordinates     ( point_i16_t * StartPoint,
                                        point_i16_t * TargetPoint,
                                        float angle );

  void      Counted_PreFix_Char       ( char x, char* res, uint8_t res_len );
  void      PreFix_Char               ( char x, char* res );
  void      Counted_PostFix_Char      ( char x, char* res, uint8_t max_len );
  void      PostFix_Char              ( char x, char* res );

  float     ARMA2O                    ( float input );

  uint32_t  SetDateTime           ( uint16_t year, uint16_t mon, uint16_t day,
                                    uint16_t hour, uint16_t min, uint16_t sec );
  uint32_t  GetLocDateTime        ( uint32_t GPS_date_time, int8_t  UTC_Offset );
  void      DateTimeReConvert     ( uint32_t date_time,
                                    int16_t * year, int16_t * month,
                                    int16_t * day,
                                    int16_t * hour, int16_t * minute,
                                    int16_t * second );

  #ifdef __cplusplus
  }
  #endif


#endif // _Utils_H

// ****************************************************************************
// End of File
