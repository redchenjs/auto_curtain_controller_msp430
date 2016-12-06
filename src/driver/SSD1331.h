/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SSD1331_H_
#define _SSD1331_H_

/* Includes ------------------------------------------------------------------*/
#include "config.h"
/*
 * --------SSD1331------
 * PORT		TYPE	PIN
 * RES		OUT		P2.2
 * DC		OUT		P1.4
 * CS		OUT		P1.5
 * SCK		OUT		SPI
 * MOSI		OUT		SPI
 * ---------------------
 */
#define SSD1331_PIN_SET		P2DIR |= BIT1; P2DIR |= BIT2; P1DIR |= BIT5

#define SSD1331_RES_SET()	P2OUT |= BIT1
#define SSD1331_RES_CLR()	P2OUT &=~BIT1

#define SSD1331_DC_SET()	P2OUT |= BIT2
#define SSD1331_DC_CLR()	P2OUT &=~BIT2

#define SSD1331_CS_SET()	P1OUT |= BIT5
#define SSD1331_CS_CLR()	P1OUT &=~BIT5

#define SSD1331_WRITE_BYTE(__DATA)	spi_txFrame(__DATA, 1)

#define FONT_1206    12
#define FONT_1608    16

#define RGB(R,G,B)  (((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3))
enum Color{
    BLACK     = RGB(  0,  0,  0), // black
    GREY      = RGB(192,192,192), // grey
    WHITE     = RGB(255,255,255), // white
    RED       = RGB(255,  0,  0), // red
    PINK      = RGB(255,192,203), // pink
    YELLOW    = RGB(255,255,  0), // yellow
    GOLDEN    = RGB(255,215,  0), // golden
    BROWN     = RGB(128, 42, 42), // brown
    BLUE      = RGB(  0,  0,255), // blue
    CYAN      = RGB(  0,255,255), // cyan
    GREEN     = RGB(  0,255,  0), // green
    PURPLE    = RGB(160, 32,240) // purple
};

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/                    

/* Exported functions ------------------------------------------------------- */
extern void ssd1331_draw_point(uint8_t chXpos, uint8_t chYpos, uint16_t hwColor);
extern void ssd1331_draw_line(uint8_t chXpos0, uint8_t chYpos0, uint8_t chXpos1, uint8_t chYpos1, uint16_t hwColor);
extern void ssd1331_draw_v_line(uint8_t chXpos, uint8_t chYpos, uint8_t chHeight, uint16_t hwColor);
extern void ssd1331_draw_h_line(uint8_t chXpos, uint8_t chYpos, uint8_t chWidth, uint16_t hwColor);
extern void ssd1331_draw_rect(uint8_t chXpos, uint8_t chYpos, uint8_t chWidth, uint8_t chHeight, uint16_t hwColor);
extern void ssd1331_fill_rect(uint8_t chXpos, uint8_t chYpos, uint8_t chWidth, uint8_t chHeight, uint16_t hwColor);
extern void ssd1331_draw_circle(uint8_t chXpos, uint8_t chYpos, uint8_t chRadius, uint16_t hwColor);
extern void ssd1331_display_char(uint8_t chXpos, uint8_t chYpos, uint8_t chChr, uint8_t chSize, uint16_t hwColor);
extern void ssd1331_display_num(uint8_t chXpos, uint8_t chYpos, uint32_t chNum, uint8_t chLen, uint8_t chSize, uint16_t hwColor);
extern void ssd1331_display_string(uint8_t chXpos, uint8_t chYpos, const char *pchString, uint8_t chSize, uint16_t hwColor);
extern void ssd1331_draw_1616char(uint8_t chXpos, uint8_t chYpos, uint8_t chChar, uint16_t hwColor);
extern void ssd1331_draw_3216char(uint8_t chXpos, uint8_t chYpos, uint8_t chChar, uint16_t hwColor);
extern void ssd1331_draw_bitmap(uint8_t chXpos, uint8_t chYpos, const uint8_t *pchBmp, uint8_t chWidth, uint8_t chHeight, uint16_t hwColor);
extern void ssd1331_clear_screen(uint16_t hwColor);

extern void ssd1331_init(void);


#endif
/*-------------------------------END OF FILE-------------------------------*/

