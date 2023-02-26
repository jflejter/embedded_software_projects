//
// COMP-GENG 421 - Tom Lupfer
//
// LCD module header file
//

#ifndef LCD_H_
#define LCD_H_

#define LCD_PIXEL_WIDTH		128		// width of the LCD, in pixels
#define LCD_PIXEL_HEIGHT	32		// height of the LCD, in pixels

#define LCD_CHAR_HEIGHT		4		// height of the LCD, in characters
#define LCD_CHAR_WIDTH		21		// width of the LCD, in characters


void LcdInit(void);
void LcdClear(void);
void LcdReverse(Bool ReverseDisplay);
int LcdPrintf(int CharRow, int CharCol, char * FmtStrPtr, ...);

#endif	// LCD_H_
