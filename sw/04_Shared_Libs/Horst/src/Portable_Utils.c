/**
  * ############################################################################
  * @file     Portable_Utils.c
  * @brief    New Vario
  * @author   Horst Rupp
  * @brief    This library contains all portable basic functions.
  * ############################################################################
  */

//
//  Includes
//
#include  "Generic_Includes.h"


// *****************************************************************************
//  Returns 1 if x is in range [low..high], else 0
// *****************************************************************************
//
uint8_t  inRange ( int32_t  low, int32_t high, int32_t x)
{
  uint8_t   y = ((x-low) <= (high-low));
    return  y;
}

// *****************************************************************************
// count bits in 8 bit word
// *****************************************************************************
//
uint8_t Count_8_Bits ( uint8_t bit_pattern )
{
  uint8_t count = 0;
  for ( uint8_t i = 0; i < 8; i++ )
  {
    if ( ( bit_pattern & 1 ) == 1 )
      count++;
    bit_pattern = bit_pattern >> 1;
  }
  return count;
}

// *****************************************************************************
// count bits in 16 bit word
// *****************************************************************************
//
uint8_t Count_16_Bits ( uint16_t bit_pattern )
{
  uint8_t count = 0;
  for ( uint8_t i = 0; i < 16; i++ )
  {
    if ( ( bit_pattern & 1 ) == 1 )
      count++;
    bit_pattern = bit_pattern >> 1;
  }
  return count;
}

// *****************************************************************************
// portable_isspace
// *****************************************************************************
//
uint8_t  portable_isspace  ( char x )
{
  if ( x == ' ' || x == 9 )
    return 1;
  else
    return 0;
}

// *****************************************************************************
// portable_isdigit
// *****************************************************************************
//
uint8_t  portable_isdigit ( char x )
{
  if ( x >= '0' || x <= '9' )
    return 1;
  else
    return 0;
}


// *****************************************************************************
// portable_islowcasechar
// *****************************************************************************
//
uint8_t  portable_islowcasechar ( char x )
{
  if ( x >= 'a' || x <= 'z' )
    return 1;
  else
    return 0;
}


// *****************************************************************************
// portable_isuppcasechar
// *****************************************************************************
//
uint8_t  portable_isuppcasechar ( char x )
{
  if ( x >= 'A' || x <= 'Z' )
    return 1;
  else
    return 0;
}


// *****************************************************************************
// portable_isprintablechar
// *****************************************************************************
//
uint8_t  portable_isprintablechar ( char x )
{
  if ( x >= 20 || x <= 126 )
    return 1;
  else
    return 0;
}


// *****************************************************************************
// portable_skipleadchar
// *****************************************************************************
//
void portable_skipleadchar ( char * dest, uint8_t drop_count )
{
  uint16_t i;

  while ( ( drop_count-- > 0 ) && ( dest[0] != 0 ) )
  {
    for ( i = 0; i < portable_strlen ( dest ); i++ )
    {
      dest[i] = dest[i+1];
    }
    dest[i+1] = 0;
  }
  i = 1;
}


// ****************************************************************************
uint16_t portable_strlen ( const char * ValText )
// ****************************************************************************
{
  uint16_t  i;

  i = 0;
  while ( ValText[i++] != 0 )
  {
    ;
  }
  return --i;

} // portable_strlen


// *****************************************************************************
// strcpy replacement
// *****************************************************************************
//
char * portable_strcpy ( char * dest, const char * source )
{
  uint16_t    l_size = portable_strlen ( source );
  uint16_t   i;
  for ( i = 0; i < l_size; i++ )
  {
    dest[i] = source[i];
  }
  dest[i] = 0;
  return dest;
}

// *****************************************************************************
// strcpy replacement
// *****************************************************************************
//
char * portable_strcpy_safe ( char * dest, const char * source, uint8_t dest_size )
{
  uint16_t    l_size = portable_strlen ( source );
  if ( l_size > dest_size )
    l_size = dest_size;
  uint16_t   i;
  for ( i = 0; i < l_size; i++ )
  {
    dest[i] = source[i];
  }
  dest[i] = 0;
  return dest;
}

// *****************************************************************************
// portable_strcat replacement
// *****************************************************************************
//
char * portable_strcat ( char * dest, const char * source )
{

  uint16_t  j;
  uint16_t  b = portable_strlen(dest);

  for ( j = 0; j < portable_strlen(source) ; j++ )
  {
    dest[b+j] = source[j];
  }
  dest[b+j] = 0;
  return dest;
}


// *****************************************************************************
// portable_strcmp
// *****************************************************************************
//
#define  StringOneIsLesser  -1
#define  StringOneIsGreater  1
#define  StringsAreEqual     0

int8_t  portable_strcmp ( const char *StringOne, const char *StringTwo )
{
  // Evaluates if both strings have the same length.
  if  ( portable_strlen ( StringOne ) != portable_strlen ( StringTwo ) ) {
    // Given that the strings have an unequal length, it compares between both
    // lengths.
    if  ( portable_strlen ( StringOne ) < portable_strlen ( StringTwo ) ) {
      return ( StringOneIsLesser );
    }
    if  ( portable_strlen ( StringOne ) > portable_strlen ( StringTwo ) ) {
      return ( StringOneIsGreater );
    }
  }

  int i;

  // Since both strings are equal in length...
  for ( i = 0; i < portable_strlen ( StringOne ); i++ ) {
    // It goes comparing letter per letter.
    if  ( StringOne [ i ] != StringTwo [ i ] ) {
      if  ( StringOne [ i ] < StringTwo [ i ] ) {
        return ( StringOneIsLesser );
      }
      if  ( StringOne [ i ] > StringTwo [ i ] ) {
        return ( StringOneIsGreater );
      }
    }
  }
  // If it ever reaches this part, it means they are equal.
  return ( StringsAreEqual );
}

// *****************************************************************************
// portable_strtoupper replacement
// *****************************************************************************
//
char * portable_strtoupper ( char * thestring )
{
   uint16_t i;
   for (i = 0; thestring[i]!='\0'; i++) {
      if(thestring[i] >= 'a' && thestring[i] <= 'z')
      {
        thestring[i] = thestring[i] -32;
      }
   }
   return thestring;
}


// *****************************************************************************
// portable_strtolower replacement
// *****************************************************************************
//
char * portable_strtolower ( char * thestring )
{
   int i;
   for (i = 0; thestring[i]!='\0'; i++)
   {
      if(thestring[i] >= 'A' && thestring[i] <= 'Z')
      {
        thestring[i] = thestring[i] + 32;
      }
   }
   return thestring;
}

// *****************************************************************************
// trim trailing character
// *****************************************************************************
//
char * portable_trimtrailing (char *input, char chartotrim )
{
  while ( input[portable_strlen(input)] == chartotrim )
  {
    input[portable_strlen(input)] = 0;
  }
  return input;
}

// *****************************************************************************
// trim leading character
// *****************************************************************************
//
char * portable_trimleading ( char *input, char chartotrim )
{
  while ( input[0] == chartotrim )
  {
    portable_skipleadchar ( input, 1 );
  }
  return input;
}

// *****************************************************************************
// trimanywhere
// *****************************************************************************
//
char * portable_trimanywhere ( char *input, char chartotrim )
{
  int32_t   i, j;

  for (i = 0; input[i] != '\0'; i++) {
    if ( input[i] == chartotrim )
    {
      for ( j = i; j < portable_strlen(input); j++ )
      {
        input[j] = input[j+1];
      }
      input[j+1] = 0;
    }
  }
  return input;
}

// *****************************************************************************
// portable_compress
// *****************************************************************************
//
char * portable_compress ( char *input )
{
  int16_t   i, j, k;

  i = 0;
  while ( input[i] != '\0')
  {
    if ( ( input[i] == ' ' ) || ( input[i] == 9 ) )
    {
      k = portable_strlen(input);
      for ( j = i; j < k ; j++ )
      {
        input[j] = input[j+1];
      }
      input[j+1] = 0;
      i--;
    }
    i++;
  }
  return input;
}

// ****************************************************************************
// Reverses a string 'str' of length 'len'
// ****************************************************************************
//
void portable_strreverse(char* str, int len)
{
  int i = 0, j = len - 1, temp;
  while (i < j)
  {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    i++;
    j--;
  }
  i = 1;
}

// ****************************************************************************
// bumps charS <x> into a char array <res>
//  until portable_strlen(res) == res_len is reached
// ****************************************************************************
//
void Counted_PreFix_Char ( char x, char* res, uint8_t max_len )
{
  uint8_t  i, l;

  l = portable_strlen ( res );

  for ( i = max_len - l; i > 0 ; i-- )
  {
    PreFix_Char ( x, ( char *) res );
  }
}

// ****************************************************************************
// bumps char <x> into a char array <res>
// assumption <res> contains a zero terminated char string
// CAUTION : No size checking !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// ****************************************************************************
//
void PreFix_Char ( char x, char* res )
{
  uint8_t  i;

  for ( i = portable_strlen(res); i >= 1 ; i-- )
  {
    res[i] = res[i-1];
  }
  res[i] = x;
}

// ****************************************************************************
// concats so many char <x> at the end of char array <res>
// that portable_strlen is == res_len
//  does nothing if res_len already reached
// assumption <res> contains a zero terminated char string
// ****************************************************************************
//
void Counted_PostFix_Char ( char x, char* res, uint8_t max_len )
{
  uint8_t  ll;
  ll = portable_strlen ( res );

  while ( ll < max_len )
  {
    PostFix_Char ( x, res  );
    ll = portable_strlen ( res );
  }
}

// ****************************************************************************
// concats char <x> at the end of char array <res>
// assumption <res> contains a zero terminated char string
// CAUTION : No size checking !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// ****************************************************************************
//
void PostFix_Char ( char x, char* res )
{
  uint8_t  ll;

  ll = portable_strlen ( res );
  res[ll] = x;
  res[ll+1] = 0;
}

// ****************************************************************************
char* portable_charreplace (char* str, char find, char replace)
// ****************************************************************************
//
{
    char *current_pos = strchr(str,find);
    while (current_pos){
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
    return str;
}

// ****************************************************************************
// Search and replace a string with another string , in a string
// ****************************************************************************
char * portable_strreplace(char *search , char *replace , char *subject)
// ****************************************************************************
{
  return 0;
}

// ****************************************************************************
uint16_t portable_strpos(char *haystack, char *needle)
// ****************************************************************************
{
  return 0;
}

//  ****************************************************************************
uint16_t portable_strsplit (char* MyString, char** Items, char Delimiter, char EOT)
//  ****************************************************************************
{
  //
  //  result is an array of pointer which all point into the MyString area
  //
  uint8_t    OneChar;
  uint16_t  n;

  n = 0;
  *Items++ = MyString;

  do {

    OneChar = *MyString;                      //  Next char of string
    if ((OneChar == EOT) || (OneChar == 0))   //  is it the given or the absolute termination character
    {                                         //  then that s the end of text
      *MyString = 0;                          //  replace that char by \0
      return (n);                             //  return no of items
    }
    else
    if (OneChar == Delimiter)                 //  Is this the given delimiter
    {                                         //  yes
      n++;                                    //  increase the item count
      *MyString++ = 0;                        //  replace delimiter by \0
      *Items++ = MyString;                    //  save the pointer to the current item
    }
    else
    {
      MyString++;
    }

  } while (1);

  return (0);

} // str_split


// *****************************************************************************
// memcpy replacement
// *****************************************************************************
//
void portable_memcpy ( uint8_t * dest, uint8_t * source, uint32_t size )
{
  uint32_t i = 0;

  while ( i < size )
  {
    *(dest+i) = *(source+i);
    i++;
  }
  //i = 1;
}

// *****************************************************************************
// memset replacement
// *****************************************************************************
//
void portable_memset ( uint8_t * dest, uint8_t value, uint32_t size )
{
  uint32_t i = 0;

  while ( i < size )
  {
    *(dest+i) = value;
    i++;
  }
  //i = 1;
}

// *****************************************************************************
// memcmp replacement
// *****************************************************************************
//
uint16_t  portable_memcmp ( uint8_t * dest, uint8_t * source, uint32_t size )
{
  uint32_t  i       = 0;
  uint8_t   result  = 0;

  while ( i < size )
  {
    if ( *(dest+i) != *(source+i) )
    {
      result = 1;
      return result;
    }
    i++;
  }
  return result;
}

// ****************************************************************************
// Converts an unsigned byte value to hex char
// ****************************************************************************
uint8_t byte_2_hex ( uint8_t byteval )
{
  if ( byteval < 9U )
    return byteval + 48;
  else
    return byteval + 64;
}

// ****************************************************************************
// Converts an unsigned integer 32 word into a hex string
// ****************************************************************************
void portable_uint32_2_hex_str ( uint32_t n, char* res )
{
  //
  // uint32_t entspricht 4 bytes
  //
  uint32_t  my_n;
  uint8_t   ix, iy;

  portable_memset ( (uint8_t*)res, 0, 5 );
  my_n = n;

  for ( uint8_t i = 0; i < 4; i++ )
  {
    ix = ( my_n & 0x000f );
    iy = byte_2_hex ( ix );
    PreFix_Char ( iy, (char*)res );
    my_n  = my_n >> 4;
  }

  PreFix_Char ( 'x', (char*)res );
  PreFix_Char ( '0', (char*)res );

}

// ****************************************************************************
// Converts a floating-point/float number <n> to a string <res> on base 10
// with length <res_len> with given <no_of_decimals>
// padded with prefixed blanks to reach length "len"
// ****************************************************************************
void portable_ftoa ( float n, char* res, uint8_t no_of_decimals, uint8_t res_len )
{
  int8_t  sign = 1;     // Plus assumed
  int32_t  ipart;
  float    fpart;
  int32_t  i;
  uint8_t  len;

// -------------------

//  while ( *res != 0 )
//    res++;

  portable_memset ( (uint8_t *) res, 0, res_len + 1);            // preset output buffer

  if ( n < 0 )                      // input value is negative
  {
    sign  = -1;
    n     = -n;
  }

  fpart = 0.5;
  for ( i = 0; i < no_of_decimals; i++ )
    fpart = fpart / 10.0;
  n += fpart;

  ipart   = (int)n;                  // Extract integer part
  fpart   = n - (float)ipart;            // Extract floating part
  len     = portable_itoa ( ipart, res, res_len );  // convert integer part to string

  // if negative
  //
  if ( sign == -1 )              // if negative
  {
    PreFix_Char ( '-', res );
    len++;
  }

  // check for display option after point
  if (no_of_decimals != 0) {
    res[portable_strlen(res)] = '.';

    //fpart = fpart + 0.0000001;

    //  Get the value of fraction part up to given no. of decimals.
    //  The third parameter is needed to handle cases like 233.007
    //
    for ( i = 0; i < no_of_decimals; i++ )
      fpart = fpart * 10;
    //fpart += 0.5;
    uint8_t ll = portable_strlen(res);
    len = portable_itoa ( (int)fpart, (char * ) & res[ll], res_len - ll );  // convert integer part to string
    while ( ( no_of_decimals - len++) > 0 )
    {
      PostFix_Char ( '0', res );
    }
  }

//  while ( portable_strlen ( res ) < len )
//  {
//    PreFix_Char ( ' ', res );
//  }
}

// ****************************************************************************
// portable_itoa2
//
//  CAUTION : Calling sequence different from stdlib itoa !!!!!!!!!!!!!!
//
// Converts an integer number <n> to a string <res> with given no of digits
//
//  CAUTION : Buffer res must have length <res_len> to contain all chars plus '-' sign
//
// ****************************************************************************
uint8_t portable_itoa2 ( int32_t n, char* res, uint8_t res_len, uint8_t prefix_pad_req, char prefix_pad_char )
{
  uint8_t   i     = 0;
  int8_t    sign  = 1;
  uint32_t  tmp;

  // ----------------------

  portable_memset ( (uint8_t*) res, 0, res_len+1 );

  if ( n < 0 )                    // check if negative
  {
     n      = -n;                    // make positive
     sign   = -1;                    // remeber sign
  }

  tmp       = n;                    // count required digits, 1 is minimum
  while ( tmp > 0 )
  {
    tmp     = tmp / 10;
    i++;
  }

  if ( i > ( res_len ) )              // error condition
    portable_memset ( (uint8_t * ) res, 'x', res_len );      // preset <res> with 'x'
  else
  {
    portable_memset ( (uint8_t * ) res, 0, res_len );        // preset <res> with all zeros


    if ( n == 0 )                  // easy way out
       PreFix_Char ( '0', res );
    else
    {
      while ( n>0 )                // convert integer to string
      {
         tmp  = n;
         n    %= 10;
         tmp  /= 10;
         PreFix_Char ( ( n + '0'), res );
         n    = tmp;
      }
    }

    if ( sign == -1 )                // if negative, set prefix '-'
       PreFix_Char ( '-', res );

    if ( prefix_pad_req == 1 )
    {
      while ( portable_strlen(res) < res_len )
        PreFix_Char ( prefix_pad_char, res );
    }


  }
  return portable_strlen ( res );
}

// ****************************************************************************
// portable_itoa
//
// CAUTION : Calling sequence different from stdlib itoa !!!!!!!!!!!!!!
//
// Converts an integer number <n> to a string <res> with given no of digits
//
// CAUTION : Buffer res must have length <res_len> to contain all chars plus '-' sign
//
// ****************************************************************************
uint8_t portable_itoa ( int32_t n, char* res, uint8_t res_len )
{
  uint8_t   i    = 0;
  int8_t    sign  = 1;
  uint32_t  tmp;

  // ----------------------

//  while ( *res != 0 )
//    res++;
  portable_memset ( (uint8_t*) res, 0, res_len+1 );

  if ( n < 0 )                    // check if negative
  {
     n    = -n;                    // make positive
     sign  = -1;                    // remember sign
  }

  tmp    = n;                    // count required digits, 1 is minimum
  while ( tmp > 0 )
  {
    tmp  = tmp / 10;
    i++;
  }

  if ( i > ( res_len ) )              // error condition
    portable_memset ( (uint8_t * ) res, 'x', res_len );      // preset <res> with 'x'
  else
  {
    portable_memset ( (uint8_t * ) res, 0, res_len );        // preset <res> with all zeros


    if ( n == 0 )                  // easy way out
       PreFix_Char ( '0', res );
    else
    {
      while ( n>0 )                // convert integer to string
      {
         tmp  = n;
         n    %= 10;
         tmp  /= 10;
         PreFix_Char ( ( n + '0'), res );
         n    = tmp;
      }
    }

    if ( sign == -1 )                // if negative, set prefix '-'
       PreFix_Char ( '-', res );
  }
  return portable_strlen ( res );
}

// ****************************************************************************
int  portable_max ( int Val1, int Val2 )
// ****************************************************************************
{
  if (Val2 > Val1) {
    return(Val2);
  } else {
    return (Val1);
  }
 }
// portable_max


// ****************************************************************************
int  portable_min ( int Val1, int Val2 )
// ****************************************************************************
{
  if (Val2 < Val1) {
    return(Val2);
  } else {
    return (Val1);
  }
 }
// portable_max


// ****************************************************************************
float portable_fmax ( float Val1, float Val2 )
// ****************************************************************************
{
  if (Val2 > Val1) {
    return(Val2);
  } else {
    return (Val1);
  }
 }
// portable_max


// ****************************************************************************
float portable_fmin ( float Val1, float Val2 )
// ****************************************************************************
{
  if (Val2 < Val1) {
    return(Val2);
  } else {
    return (Val1);
  }
 }
// portable_max



// ****************************************************************************
double    portable_fmod             ( float Val1, float Val2 )
// ****************************************************************************
{
  float x, y;
  x = Val1 / Val2;
  y = x * Val2;
  return (Val1 - y);
}



// ****************************************************************************
float  portable_round_2_n_decmls ( float Val1, int Val2 )
// ****************************************************************************
{
  float x = 1.0;
  float y;

  for ( uint8_t i = 0; i < Val2; i++ )
  {
    x *= 10.0;
  }
  if ( Val1 >= 0.0 )
    y = (int)( Val1 * x + 0.5 ) / x;
  else
    y = (int)( Val1 * x - 0.5 ) / x;
  return y;

 }
// portable_round_2_n_decmls


// ****************************************************************************
int32_t portable_round_2wards_zero ( float Val1 )
// ****************************************************************************
{
  //int32_t l_x;
  int8_t  l_sign = sign_float ( Val1 );

  return  l_sign * floor ( fabs ( Val1 ) );
 }
// portable_round_2wards_zero


// ****************************************************************************
int		sign_int				    ( int value )
// ****************************************************************************
{
	return ( ( value > 0.0 ) ? 1 : -1 );
}


// ****************************************************************************
int		sign_long				    ( long value )
// ****************************************************************************
{
  return ( ( value > 0.0 ) ? 1 : -1 );
}

// ****************************************************************************
int		sign_float				  ( float value )
// ****************************************************************************
{
  return ( ( value > 0.0 ) ? 1 : -1 );
}

// ****************************************************************************
int		sign_double				  ( double value )
// ****************************************************************************
{
  return ( ( value > 0.0 ) ? 1 : -1 );
}

// ****************************************************************************
float  portable_safe_tan ( float Val )
// ****************************************************************************
{
  float x = fabs ( fabs ( Val ) - c_PiD2_90Grad );
  if ( x < c_Jota )
  {
    if ( Val >= 0.0 )
      return 1.0 / c_Jota;
    else
      return -1.0 / c_Jota;
  }
  else
    return tan ( Val );
}



// ****************************************************************************
float  portable_atof ( const char * ValText )
// ****************************************************************************
{
  // + or -, digits, with 0 or 1 periods in it.

  uint16_t  decimals  = 0;
  uint32_t  i         = 0;
  uint8_t   got_dot   = 0;    // not dot assumed
  uint8_t   sign      = 1;    // plus assumed
  float     result    = 0;

  //
  // delete all blanks from string
  //
  portable_compress ( (char*)ValText );

  //
  //  check special cases
  //
  while ( ValText[0] == '.' )
  {
    got_dot = 1;
    portable_trimleading ( (char * ) ValText, '.' );
  }

  while ( ValText[0]== '+' )
  {
    portable_trimleading ( (char * ) ValText, '+' );
  }

  while ( ValText[0]== '-' )
  {
    sign = -sign;
    portable_trimleading ( (char * ) ValText, '-' );
  }

  //
  //  normal processing
  //
  for ( i = 0; i < portable_strlen((char*)ValText); i++ )
  {
    if ( ValText[i] == '.' )
    {
      if ( got_dot == 1 )
        return result;    // no second dot
      else
        got_dot = 1;
    }
    else if ( ValText[i] == '+' )
      return result;  // no second +
    else if ( ValText[i] == '-' )
      return result;  // no second -
    else if ( portable_isdigit ( (char)  ValText[i]) )
    {
      //  before dot
      if (got_dot == 1 )
        decimals++;
      result = result * 10 + ( ValText[i] - '0' );
    }
  }

  while (decimals-- > 0)
    result = result / 10;

  result  = sign * result;

  return result;
}


#define uint32_t_max  0xFFFFFFFF
#define uint16_t_max  0x7FFFFFFF

// ****************************************************************************
int16_t portable_atoi ( const char* ValText )
// ****************************************************************************
{
  uint32_t  i         = 0;
  uint8_t   sign      = 1;    // plus assumed
  int16_t   result    = 0;
  //
  //  normal processing
  //
  portable_compress ( (char*)ValText );

  //
  //  check special cases
  //
  while ( ValText[0]== '+' )
  {
    portable_trimleading ( (char * ) ValText, '+' );
  }

  while ( ValText[0]== '-' )
  {
    sign = -sign;
    portable_trimleading ( (char * ) ValText, '-' );
  }

  //
  //  normal processing
  //
  for ( i = 0; i < portable_strlen((char*)ValText); i++ )
  {
    if ( ValText[i] == '.' )
      return result;  // no dot in integer
    else if ( ValText[i] == '+' )
      return result;  // no second +
    else if ( ValText[i] == '-' )
      return result;  // no second -
    else if ( portable_isdigit ( (char)  ValText[i]) )
      result = result * 10 + ( ValText[i] - '0' );
  }

  result  = sign * result;

  return result;

} // portable_atoi

// ****************************************************************************
int32_t portable_atol ( const char* ValText )
// ****************************************************************************
{
  uint32_t  i         = 0;
  uint8_t   sign      = 1;    // plus assumed
  int32_t   result    = 0;
  //
  //  normal processing
  //
  portable_compress ( (char*)ValText );

  //
  //  check special cases
  //
  while ( ValText[0]== '+' )
  {
    portable_trimleading ( (char * ) ValText, '+' );
  }

  while ( ValText[0]== '-' )
  {
    sign = -sign;
    portable_trimleading ( (char * ) ValText, '-' );
  }

  //
  //  normal processing
  //
  for ( i = 0; i < portable_strlen((char*)ValText); i++ )
  {
    if ( ValText[i] == '.' )
      return result;  // no dot in integer
    else if ( ValText[i] == '+' )
      return result;  // no second +
    else if ( ValText[i] == '-' )
      return result;  // no second -
    else if ( portable_isdigit ( (char)  ValText[i]) )
      result = result * 10 + ( ValText[i] - '0' );
  }

  result  = sign * result;

  return result;

} // portable_atol

// ****************************************************************************
// ARMA filter 2nd order    c/o Dr. Klaus Schaefer
// ****************************************************************************
//

float ARMA2O ( float input )
{
  #define Koeff_1  (0.136728735)
  #define Koeff_2  (0.726542528)

  float  old_input = 0.0;
  float  old_output = 0.0;
  float  output;

  output = ( old_input + input ) * Koeff_1 + old_output * Koeff_2;
  old_output = output;
  old_input = input;
  return output;
}


// *****************************************************************************
// decimal to binary string
// *****************************************************************************
//
uint8_t * portable_Decimal_to_Binary ( uint32_t Data, uint8_t NoOfBits, uint8_t * outbuffer )
{
  uint8_t *   MyPtr = outbuffer;
  uint32_t    Mask;
  uint8_t     i;

  Mask = 1L << (NoOfBits-1);

  for (i = NoOfBits ; i > 0 ; i--)
  {
    if (Data & Mask)
      *MyPtr++ = '1';
    else
      *MyPtr++ = '0';

    Mask = Mask >> 1;

    if ( ( ( i & 3 ) == 1 ) && ( i > 1 ) )
    {
      *MyPtr++ = '.';
    }
  }

  *MyPtr = '\0';

  return MyPtr;

}

/// ****************************************************************************
// Binary BCD Conversion
// ****************************************************************************
uint8_t  portable_Binary_2_BCD ( uint8_t input )
// ****************************************************************************
{
  uint8_t    hi_nibble = 0;
  uint8_t    lo_nibble;

  lo_nibble = input;
  while ( lo_nibble > 10 )
  {
    lo_nibble = lo_nibble - 10;
    hi_nibble++;
  }
  return ( ( hi_nibble << 4 ) + lo_nibble );

}

// ****************************************************************************
// BCD Binary Conversion
// ****************************************************************************
uint8_t  portable_BCD_2_Binary ( uint8_t input )
{
  uint8_t    hi_nibble;
  uint8_t    lo_nibble;

  hi_nibble = input >> 4;
  lo_nibble = input & 0x0F;

  return ( hi_nibble * 10 + lo_nibble );

}

// ****************************************************************************
// convert latitude in RAD to string
// ****************************************************************************
//
void lat_rad_2_NS_DDMMSS  ( float latitude_rad, uint8_t * buffer )
{
  char  l_NS;
  //uint8_t  l_buffer[c_len_coord_buffer];

  if ( latitude_rad > 0 )
  {
    l_NS = 'N';
  } else {
    l_NS = 'S';
  }

  float l_deg = latitude_rad * 180.0 / c_Pi_180Grad;
  int8_t  l_units  = floor ( l_deg );
  l_deg -= l_units;
  l_deg *= 60.0;
  uint8_t  l_minutes = floor ( l_deg );
  l_deg -= l_minutes;
  l_deg *= 60.0;
  uint8_t  l_seconds = floor ( l_deg );

  portable_memset ( (uint8_t * ) buffer, 0, c_len_coord_buffer );
  PreFix_Char ( l_NS, (char * )buffer );
  uint8_t ll = portable_strlen( (const char * ) buffer);
  portable_itoa2 ( l_units, (char *) &buffer[ll], 3, 1, '0' );
  PostFix_Char ( ':', (char * )buffer );
  ll = portable_strlen((const char * )buffer);
  portable_itoa2 ( l_minutes, (char *) &buffer[ll], 2, 1, '0' );
  PostFix_Char ( ':', (char * )buffer );
  ll = portable_strlen((const char * )buffer);
  portable_itoa2 ( l_seconds, (char *) &buffer[ll], 2, 1, '0' );
}

// ****************************************************************************
// convert longitude in RAD to string
// ****************************************************************************
//
void lon_rad_2_EW_DDDMMSS  ( float longitude_rad, uint8_t * buffer )
{
  uint8_t  l_EW;

  if ( longitude_rad > 0 )
  {
    l_EW = 'E';
  } else {
    l_EW = 'W';
  }

  float l_deg = longitude_rad * 180.0 / c_Pi_180Grad;
  int8_t  l_units  = floor ( l_deg );
  l_deg -= l_units;
  l_deg *= 60.0;
  uint8_t  l_minutes = floor ( l_deg );
  l_deg -= l_minutes;
  l_deg *= 60.0;
  uint8_t  l_seconds = floor ( l_deg );

  portable_memset ( (uint8_t * ) buffer, 0, c_len_coord_buffer );
  PreFix_Char ( l_EW, (char * )buffer );
  uint8_t ll = portable_strlen((const char * )buffer);
  portable_itoa2 ( l_units, ( char * ) &buffer[ll], 3, 1, '0' );
  PostFix_Char ( ':', (char * )buffer );
  ll = portable_strlen((const char * )buffer);
  portable_itoa2 ( l_minutes, ( char * ) &buffer[ll], 2, 1, '0' );
  PostFix_Char ( ':', (char * )buffer );
  ll = portable_strlen((const char * )buffer);
  portable_itoa2 ( l_seconds, ( char * ) &buffer[ll], 2, 1, '0' );
}

// ****************************************************************************
// convert latitude in decimal degrees to string
// ****************************************************************************
//
void  lat_dec_deg_2_NS_DDMMSS   ( float latitude_deg, uint8_t * buffer )
{
  uint8_t  l_NS;

  if ( latitude_deg > 0 )
  {
    l_NS = 'N';
  } else {
    l_NS = 'S';
  }

  float l_deg = latitude_deg;
  int8_t  l_units  = floor ( l_deg );
  l_deg -= l_units;
  l_deg *= 60.0;
  uint8_t  l_minutes = floor ( l_deg );
  l_deg -= l_minutes;
  l_deg *= 60.0;
  uint8_t  l_seconds = floor ( l_deg );

  portable_memset ( (uint8_t * ) buffer, 0, c_len_coord_buffer );
  PreFix_Char ( l_NS, (char * )buffer );
  uint8_t ll = portable_strlen((const char * )buffer);
  portable_itoa2 ( l_units, ( char * ) &buffer[ll], 3, 1, '0' );
  PostFix_Char ( ':', (char * )buffer );
  ll = portable_strlen((const char * )buffer);
  portable_itoa2 ( l_minutes, ( char * ) &buffer[ll], 2, 1, '0' );
  PostFix_Char ( ':', (char * )buffer );
  ll = portable_strlen((const char * )buffer);
  portable_itoa2 ( l_seconds, ( char * ) &buffer[ll], 2, 1, '0' );
}

// ****************************************************************************
// convert longitude in decimal degrees to string
// ****************************************************************************
//
void  lon_dec_deg_2_EW_DDDMMSS   ( float longitude_deg, uint8_t * buffer )
{
  uint8_t  l_EW;

  if ( longitude_deg > 0 )
  {
    l_EW = 'E';
  } else {
    l_EW = 'W';
  }

  float l_deg = longitude_deg;
  int8_t  l_units  = floor ( l_deg );
  l_deg -= l_units;
  l_deg *= 60.0;
  uint8_t  l_minutes = floor ( l_deg );
  l_deg -= l_minutes;
  l_deg *= 60.0;
  uint8_t  l_seconds = floor ( l_deg );

  portable_memset ( (uint8_t * ) buffer, 0, c_len_coord_buffer );
  PreFix_Char ( l_EW, (char * )buffer );
  uint8_t ll = portable_strlen((const char * )buffer);
  portable_itoa2 ( l_units, ( char * ) &buffer[ll], 3, 1, '0' );
  PostFix_Char ( ':', (char * )buffer );
  ll = portable_strlen((const char * )buffer);
  portable_itoa2 ( l_minutes, ( char * ) &buffer[ll], 2, 1, '0' );
  PostFix_Char ( ':', (char * )buffer );
  ll = portable_strlen((const char * )buffer);
  portable_itoa2 ( l_seconds, ( char * ) &buffer[ll], 2, 1, '0' );
}

#if ( defined BUILD_VARIO ) || ( defined BUILD_BOOTLOADER )
  // ****************************************************************************
  // Transpose coordinates on the canvas AND perform clipping  ToDo
  // ****************************************************************************
  //
  void MapCoordinates2Canvas (  point_i16_t * StartPoint )
  {
  //  if ( StartPoint->x > 113 )  StartPoint->x = 113;
  //  if ( StartPoint->x < -113 ) StartPoint->x = -113;
  //  if ( StartPoint->y > 113 )  StartPoint->y = 113;
  //  if ( StartPoint->y < -113 ) StartPoint->y = -113;

    StartPoint->x = c_center_x + StartPoint->x;
    StartPoint->y = c_center_y - StartPoint->y;
  }
#endif

// ****************************************************************************
// offset coordinates
// ****************************************************************************
//
void OffsetCoordinates ( point_i16_t * Offset ,
                         point_i16_t * StartPoint
                       )
{
  StartPoint->x += Offset->x;
  StartPoint->y += Offset->y;
}

// ****************************************************************************
//  rotation of a vector inside a fixed coord system
// ****************************************************************************
//
void RotateFlatCoordinates (  point_i16_t * StartPoint,
                              point_i16_t * TargetPoint,
                              float angle )
{
  float y_cos, y_sin;

  // --------------------------------------------------------------------

  y_cos = cos ( angle );
  y_sin = sin ( angle );

  TargetPoint->x = portable_round_2wards_zero ( y_cos * StartPoint->x + y_sin * StartPoint->y );
  TargetPoint->y = portable_round_2wards_zero( y_cos * StartPoint->y - y_sin * StartPoint->x ) ;

  return;
}

// ***********************************************************************
// ***********************************************************************
//
// ****************************************************************************
//  own time notation handling
//
//  compact date time elem ents into a 32 bit word
// ****************************************************************************
//
uint32_t  SetDateTime     ( uint16_t year, uint16_t mon, uint16_t day,
                            uint16_t hour, uint16_t min, uint16_t sec )
{
  uint32_t  x = year;
  x = ( x << 4 ) + mon;     // 12 --> 16 --> 4 bit
  x = ( x << 5 ) + day;     // 32 --> 32 --> 5 bit
  x = ( x << 5 ) + hour;    // 24 --> 32 --> 5 bit
  x = ( x << 6 ) + min;     // 60 --> 64 --> 6 bit
  x = ( x << 6 ) + sec;     // 60 --> 64 --> 6 bit
  return x;
}

// ****************************************************************************
//  translate UTC time into local time using an hourly offset
//  This routine is leapyear aware up to the next centenial
// ****************************************************************************
//
uint32_t  GetLocDateTime  ( uint32_t GPS_date_time, int8_t  UTC_Offset )
{
  int16_t  year;
  int16_t  month;
  int16_t  day;
  int16_t  hour;
  int16_t  minute;
  int16_t  second;
  uint32_t  LOC_date_time;
  uint8_t   DaysInThisMonth;
  uint8_t   DaysInPrevMonth;
  int8_t    Day_Offset = 0;

  uint8_t   DaysInMonthNormalYear[12] =
                // Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
                  { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  uint8_t   DaysInMonthLeapYear  [12] =
                // Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
                  { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  DateTimeReConvert ( GPS_date_time,
                      &year, &month, &day, &hour, &minute, &second );

  hour = hour + UTC_Offset;
  if ( hour < 0 )
  {
    hour +=24;
    Day_Offset = -1;
  }
  if ( hour >= 24 )
  {
    Day_Offset = 1;
    hour -= 24;
  }

  if ( year / 4 * 4  == year )
  {
    DaysInPrevMonth = DaysInMonthLeapYear[( month-2 ) % 12];
    DaysInThisMonth = DaysInMonthLeapYear[( month-1 ) % 12];
  }
  else
  {
    DaysInPrevMonth = DaysInMonthNormalYear[( month-2 ) % 12];
    DaysInThisMonth = DaysInMonthNormalYear[( month-1 ) % 12];
  }

  day += Day_Offset;

  if ( day < 0 )
  {
    day = DaysInPrevMonth;
    month--;
    if ( month < 0 )
    {
      month = 12;
      year--;
    }
  }

  if ( day > DaysInThisMonth )
  {
    day = 1;
    month++;
    if ( month > 12 )
    {
      month = 1;
      year++;
    }
  }


  LOC_date_time = SetDateTime ( year, month, day, hour, minute, second );
  return    LOC_date_time;
}

// ****************************************************************************
//  Reconvert packed time from int32_t word into atoms
// ***********************************************************************
//
void DateTimeReConvert (  uint32_t date_time,
                          int16_t * year, int16_t * month, int16_t * day,
                          int16_t * hour, int16_t * minute, int16_t * second )
{

  uint32_t  l_x;
  //uint32_t  l_y;

  l_x = date_time;
  *second = l_x & 0b111111;
  l_x = l_x >> 6;

  *minute = l_x & 0b111111;
  l_x = l_x >> 6;

  *hour = l_x & 0b11111;
  l_x = l_x >> 5;

  *day = l_x & 0b11111;
  l_x = l_x >> 5;

  *month = l_x & 0b1111;
  l_x = l_x >> 4;

  *year  = l_x;

}

// ****************************************************************************
// End of File
// ****************************************************************************
