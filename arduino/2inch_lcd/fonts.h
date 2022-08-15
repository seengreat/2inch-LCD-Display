
#ifndef __FONTS_H
#define __FONTS_H
   
#include <stdint.h>
#include <avr/pgmspace.h>

#ifdef __cplusplus
 extern "C" {
#endif

//ASCII
typedef struct tFont
{    
  const char *table;
  uint16_t fsize;
  uint16_t w; //width
  uint16_t h; //height
  
}FONT;

typedef struct
{
const char context[2];
const char pix[72];  
}CH_CN24;

//CN
typedef struct tCN_Font
{    
  const CH_CN24 *table;
  uint16_t fsize;
  uint16_t w; //width
  uint16_t h; //height
  
}CN_FONT;

extern FONT Font24;
extern CN_FONT CN_Font24;

#ifdef __cplusplus
}
#endif

#endif 
 
