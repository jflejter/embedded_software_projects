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

#define LCD_OBJ_PADDLE		0
#define LCD_OBJ_BALL		1
#define LCD_OBJ_ERASE		2


void LcdInit(void);
void LcdClear(void);
void LcdReverse(Bool ReverseDisplay);
void LcdRenderObject(int Object, int PosX, int PosY);
int LcdPrintf(int CharRow, int CharCol, char * FmtStrPtr, ...);

#endif	// LCD_H_
