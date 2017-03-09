#include <msp430.h>
#include "system/fonts.h"
#include "interface/spi.h"
#include "driver/ssd1331.h"
/*
 * --------SSD1331--------
 * PORT		TYPE	PIN
 * RES		OUT		P3.6
 * DC		OUT		P3.7
 * CS		OUT		P1.4
 * SCK		OUT		P1.5(SPI)
 * MOSI		OUT		P1.7(SPI)
 * -----------------------
 */
#define abs(x) ((x)>0?(x):-(x))
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

#define SSD1331_PIN_SET()	P3DIR |= BIT6; P3DIR |= BIT7; P1DIR |= BIT4

#define SSD1331_RES_SET()	P3OUT |= BIT6
#define SSD1331_RES_CLR()	P3OUT &=~BIT6
#define SSD1331_DC_SET()	P3OUT |= BIT7
#define SSD1331_DC_CLR()	P3OUT &=~BIT7
#define SSD1331_CS_SET()	P1OUT |= BIT4
#define SSD1331_CS_CLR()	P1OUT &=~BIT4
#define SSD1331_WRITE_BYTE(__DATA)	spi_transmit_frame(__DATA, 1)

#define SSD1331_CMD                     0
#define SSD1331_DATA                    1
                 
#define OLED_WIDTH                      96
#define OLED_HEIGHT                     64

#define DRAW_LINE                       0x21
#define DRAW_RECTANGLE                  0x22
#define COPY_WINDOW                     0x23
#define DIM_WINDOW                      0x24
#define CLEAR_WINDOW                    0x25
#define FILL_WINDOW                     0x26
#define DISABLE_FILL                    0x00
#define ENABLE_FILL                     0x01
#define CONTINUOUS_SCROLLING_SETUP      0x27
#define DEACTIVE_SCROLLING              0x2E
#define ACTIVE_SCROLLING                0x2F

#define SET_COLUMN_ADDRESS              0x15
#define SET_ROW_ADDRESS                 0x75
#define SET_CONTRAST_A                  0x81
#define SET_CONTRAST_B                  0x82
#define SET_CONTRAST_C                  0x83
#define MASTER_CURRENT_CONTROL          0x87
#define SET_PRECHARGE_SPEED_A           0x8A
#define SET_PRECHARGE_SPEED_B           0x8B
#define SET_PRECHARGE_SPEED_C           0x8C
#define SET_REMAP                       0xA0
#define SET_DISPLAY_START_LINE          0xA1
#define SET_DISPLAY_OFFSET              0xA2
#define NORMAL_DISPLAY                  0xA4
#define ENTIRE_DISPLAY_ON               0xA5
#define ENTIRE_DISPLAY_OFF              0xA6
#define INVERSE_DISPLAY                 0xA7
#define SET_MULTIPLEX_RATIO             0xA8
#define DIM_MODE_SETTING                0xAB
#define SET_MASTER_CONFIGURE            0xAD
#define DIM_MODE_DISPLAY_ON             0xAC
#define DISPLAY_OFF                     0xAE
#define NORMAL_BRIGHTNESS_DISPLAY_ON    0xAF
#define POWER_SAVE_MODE                 0xB0
#define PHASE_PERIOD_ADJUSTMENT         0xB1
#define DISPLAY_CLOCK_DIV               0xB3
#define SET_GRAY_SCALE_TABLE            0xB8
#define ENABLE_LINEAR_GRAY_SCALE_TABLE  0xB9
#define SET_PRECHARGE_VOLTAGE           0xBB
#define SET_V_VOLTAGE                   0xBE

static void ssd1331_write_byte(unsigned char chData, unsigned char chCmd)
{
	if (chCmd) {
	 	SSD1331_DC_SET();
	} else {
	 	SSD1331_DC_CLR();
	}
	
	SSD1331_CS_CLR();
	SSD1331_WRITE_BYTE(&chData);
	
	SSD1331_CS_SET();
	SSD1331_DC_SET();
}

void ssd1331_draw_point(unsigned char chXpos, unsigned char chYpos, unsigned int hwColor)
{
	if (chXpos >= OLED_WIDTH || chYpos >= OLED_HEIGHT) {
		return;
	}

    //set column point
    ssd1331_write_byte(SET_COLUMN_ADDRESS, SSD1331_CMD);
    ssd1331_write_byte(chXpos, SSD1331_CMD);
    ssd1331_write_byte(OLED_WIDTH - 1, SSD1331_CMD);
    //set row point
    ssd1331_write_byte(SET_ROW_ADDRESS, SSD1331_CMD);
    ssd1331_write_byte(chYpos, SSD1331_CMD);
    ssd1331_write_byte(OLED_HEIGHT - 1, SSD1331_CMD);
    
    //fill 16bit colour
	ssd1331_write_byte(hwColor >> 8, SSD1331_DATA);
	ssd1331_write_byte(hwColor, SSD1331_DATA);   
}

void ssd1331_draw_line(unsigned char chXpos0, unsigned char chYpos0, unsigned char chXpos1, unsigned char chYpos1, unsigned int hwColor)
{
	int x = chXpos1 - chXpos0;
    int y = chYpos1 - chYpos0;
    int dx = abs(x), sx = chXpos0 < chXpos1 ? 1 : -1;
    int dy = -abs(y), sy = chYpos0 < chYpos1 ? 1 : -1;
    int err = dx + dy, e2;

	if (chXpos0 >= OLED_WIDTH || chYpos0 >= OLED_HEIGHT || chXpos1 >= OLED_WIDTH || chYpos1 >= OLED_HEIGHT) {
		return;
	}
    
    for (;;){
        ssd1331_draw_point(chXpos0, chYpos0 , hwColor);
        e2 = 2 * err;
        if (e2 >= dy) {     
            if (chXpos0 == chXpos1) break;
            err += dy; chXpos0 += sx;
        }
        if (e2 <= dx) {
            if (chYpos0 == chYpos1) break;
            err += dx; chYpos0 += sy;
        }
    }
}

void ssd1331_draw_v_line(unsigned char chXpos, unsigned char chYpos, unsigned char chHeight, unsigned int hwColor)
{	
	unsigned int i, y1 = min(chYpos + chHeight, OLED_HEIGHT - 1);

	if (chXpos >= OLED_WIDTH || chYpos >= OLED_HEIGHT) {
		return;
	}
	
    for (i = chYpos; i < y1; i++) {
        ssd1331_draw_point(chXpos, i, hwColor);
    }
}

void ssd1331_draw_h_line(unsigned char chXpos, unsigned char chYpos, unsigned char chWidth, unsigned int hwColor)
{	
	unsigned int i, x1 = min(chXpos + chWidth, OLED_WIDTH- 1);

	if (chXpos >= OLED_WIDTH || chYpos >= OLED_HEIGHT) {
		return;
	}
	
    for (i = chXpos; i < x1; i++) {
        ssd1331_draw_point(i, chYpos, hwColor);
    }
}

void ssd1331_draw_rect(unsigned char chXpos, unsigned char chYpos, unsigned char chWidth, unsigned char chHeight, unsigned int hwColor)
{
	if (chXpos >= OLED_WIDTH || chYpos >= OLED_HEIGHT) {
		return;
	}

	ssd1331_draw_h_line(chXpos, chYpos, chWidth, hwColor);
	ssd1331_draw_h_line(chXpos, chYpos + chHeight, chWidth, hwColor);
	ssd1331_draw_v_line(chXpos, chYpos, chHeight, hwColor);
	ssd1331_draw_v_line(chXpos + chWidth, chYpos, chHeight + 1, hwColor);
}

void ssd1331_fill_rect(unsigned char chXpos, unsigned char chYpos, unsigned char chWidth, unsigned char chHeight, unsigned int hwColor)
{
	unsigned int i, j;

	if (chXpos >= OLED_WIDTH || chYpos >= OLED_HEIGHT) {
		return;
	}
	
	for(i = 0; i < chHeight; i++){
		for(j = 0; j < chWidth; j++){
			ssd1331_draw_point(chXpos + j, chYpos + i, hwColor);
		}
	}
}

void ssd1331_draw_circle(unsigned char chXpos, unsigned char chYpos, unsigned char chRadius, unsigned int hwColor)
{
	int x = -chRadius, y = 0, err = 2 - 2 * chRadius, e2;

	if (chXpos >= OLED_WIDTH || chYpos >= OLED_HEIGHT) {
		return;
	}
	
    do {
        ssd1331_draw_point(chXpos - x, chYpos + y, hwColor);
        ssd1331_draw_point(chXpos + x, chYpos + y, hwColor);
        ssd1331_draw_point(chXpos + x, chYpos - y, hwColor);
        ssd1331_draw_point(chXpos - x, chYpos - y, hwColor);
        e2 = err;
        if (e2 <= y) {
            err += ++y * 2 + 1;
            if(-x == y && e2 <= x) e2 = 0;
        }
        if(e2 > x) err += ++x * 2 + 1;
    } while(x <= 0);
}

void ssd1331_display_char(unsigned char chXpos, unsigned char chYpos, unsigned char chChr, unsigned char chSize, unsigned int hwColor)
{      	
	unsigned char i, j, chTemp;
	unsigned char chYpos0 = chYpos;

	if (chXpos >= OLED_WIDTH || chYpos >= OLED_HEIGHT) {
		return;
	}
					   
    for (i = 0; i < chSize; i++) {
		if (FONT_1206 == chSize) {
			chTemp = c_chFont1206[chChr - 0x20][i];  
		} else if (FONT_1608 == chSize) { 
			chTemp = c_chFont1608[chChr - 0x20][i];
		}
		
        for (j = 0; j < 8; j++) {
    		if (chTemp & 0x80) {
				ssd1331_draw_point(chXpos, chYpos, hwColor);
    		}			
			chTemp <<= 1;
			chYpos++;
			if ((chYpos - chYpos0) == chSize) {
				chYpos = chYpos0;
				chXpos++;
				break;
			}
		}  	 
    } 
}

static unsigned long _pow(unsigned char m, unsigned char n)
{
	unsigned long result = 1;
	
	while(n --) result *= m;    
	return result;
}


void ssd1331_display_num(unsigned char chXpos, unsigned char chYpos, unsigned long chNum, unsigned char chLen, unsigned char chSize, unsigned int hwColor)
{         	
	unsigned char i;
	unsigned char chTemp, chShow = 0;

	if (chXpos >= OLED_WIDTH || chYpos >= OLED_HEIGHT) {
		return;
	}
	
	for(i = 0; i < chLen; i++) {
		chTemp = (chNum / _pow(10, chLen - i - 1)) % 10;
		if(chShow == 0 && i < (chLen - 1)) {
			if(chTemp == 0) {
				ssd1331_display_char(chXpos + (chSize / 2) * i, chYpos, ' ', chSize, hwColor);
				continue;
			} else {
				chShow = 1;
			}	 
		}
	 	ssd1331_display_char(chXpos + (chSize / 2) * i, chYpos, chTemp + '0', chSize, hwColor); 
	}
} 

void ssd1331_display_string(unsigned char chXpos, unsigned char chYpos, const char *pchString, unsigned char chSize, unsigned int hwColor)
{
	if (chXpos >= OLED_WIDTH || chYpos >= OLED_HEIGHT) {
		return;
	}
	
    while (*pchString != '\0') {       
        if (chXpos > (OLED_WIDTH - chSize / 2)) {
			chXpos = 0;
			chYpos += chSize;
			if (chYpos > (OLED_HEIGHT - chSize)) {
				chYpos = chXpos = 0;
				ssd1331_clear_screen(0x00);
			}
		}
		
        ssd1331_display_char(chXpos, chYpos, *pchString, chSize, hwColor);
        chXpos += chSize / 2;
        pchString++;
    } 
}

void ssd1331_draw_1612char(unsigned char chXpos, unsigned char chYpos, unsigned char chChar, unsigned int hwColor)
{
	unsigned char i, j;
	unsigned char chTemp = 0, chYpos0 = chYpos;

	for (i = 0; i < 32; i++) {
		chTemp = c_chFont1612[chChar - 0x30][i];
		for (j = 0; j < 8; j++) {
			if (chTemp & 0x80) {
				ssd1331_draw_point(chXpos, chYpos, hwColor);
    		}
			chTemp <<= 1;
			chYpos++;
			if ((chYpos - chYpos0) == 16) {
				chYpos = chYpos0;
				chXpos++;
				break;
			}
		}
	}
}

void ssd1331_draw_3216char(unsigned char chXpos, unsigned char chYpos, unsigned char chChar, unsigned int hwColor)
{
	unsigned char i, j;
	unsigned char chTemp = 0, chYpos0 = chYpos;

	for (i = 0; i < 64; i++) {
		chTemp = c_chFont3216[chChar - 0x30][i];
		for (j = 0; j < 8; j++) {
			if (chTemp & 0x80) {
				ssd1331_draw_point(chXpos, chYpos, hwColor);
    		}
			chTemp <<= 1;
			chYpos++;
			if ((chYpos - chYpos0) == 32) {
				chYpos = chYpos0;
				chXpos++;
				break;
			}
		}
	}
}

void ssd1331_draw_bitmap(unsigned char chXpos, unsigned char chYpos, const unsigned char *pchBmp, unsigned char chWidth, unsigned char chHeight, unsigned int hwColor)
{
	unsigned int i, j, byteWidth = (chWidth + 7) / 8;
	
    for(j = 0; j < chHeight; j++){
        for(i = 0; i < chWidth; i++) {
            if(*(pchBmp + j * byteWidth + i / 8) & (128 >> (i & 7))) {
                ssd1331_draw_point(chXpos + i, chYpos + j, hwColor);
            }
        }
    }
}

void ssd1331_clear_screen(unsigned int hwColor)
{
	unsigned int i, j;
	
	for(i = 0; i < OLED_HEIGHT; i++){
		for(j = 0; j < OLED_WIDTH; j++){
			ssd1331_draw_point(j, i, hwColor);
		}
	}
}


void ssd1331_init(void)
{
	SSD1331_PIN_SET();
	SSD1331_RES_SET();  //RES set
	SSD1331_CS_SET();
	
	ssd1331_write_byte(DISPLAY_OFF, SSD1331_CMD);          //Display Off
    ssd1331_write_byte(SET_CONTRAST_A, SSD1331_CMD);       //Set contrast for color A
    ssd1331_write_byte(0xFF, SSD1331_CMD);                     //145 0x91
    ssd1331_write_byte(SET_CONTRAST_B, SSD1331_CMD);       //Set contrast for color B
    ssd1331_write_byte(0xFF, SSD1331_CMD);                     //80 0x50
    ssd1331_write_byte(SET_CONTRAST_C, SSD1331_CMD);       //Set contrast for color C
    ssd1331_write_byte(0xFF, SSD1331_CMD);                     //125 0x7D
    ssd1331_write_byte(MASTER_CURRENT_CONTROL, SSD1331_CMD);//master current control
    ssd1331_write_byte(0x06, SSD1331_CMD);                     //6
    ssd1331_write_byte(SET_PRECHARGE_SPEED_A, SSD1331_CMD);//Set Second Pre-change Speed For ColorA
    ssd1331_write_byte(0x64, SSD1331_CMD);                     //100
    ssd1331_write_byte(SET_PRECHARGE_SPEED_B, SSD1331_CMD);//Set Second Pre-change Speed For ColorB
    ssd1331_write_byte(0x78, SSD1331_CMD);                     //120
    ssd1331_write_byte(SET_PRECHARGE_SPEED_C, SSD1331_CMD);//Set Second Pre-change Speed For ColorC
    ssd1331_write_byte(0x64, SSD1331_CMD);                     //100
    ssd1331_write_byte(SET_REMAP, SSD1331_CMD);            //set remap & data format
    ssd1331_write_byte(0x72, SSD1331_CMD);                     //0x72              
    ssd1331_write_byte(SET_DISPLAY_START_LINE, SSD1331_CMD);//Set display Start Line
    ssd1331_write_byte(0x0, SSD1331_CMD);
    ssd1331_write_byte(SET_DISPLAY_OFFSET, SSD1331_CMD);   //Set display offset
    ssd1331_write_byte(0x0, SSD1331_CMD);
    ssd1331_write_byte(NORMAL_DISPLAY, SSD1331_CMD);       //Set display mode
    ssd1331_write_byte(SET_MULTIPLEX_RATIO, SSD1331_CMD);  //Set multiplex ratio
    ssd1331_write_byte(0x3F, SSD1331_CMD);
    ssd1331_write_byte(SET_MASTER_CONFIGURE, SSD1331_CMD); //Set master configuration
    ssd1331_write_byte(0x8E, SSD1331_CMD);
    ssd1331_write_byte(POWER_SAVE_MODE, SSD1331_CMD);      //Set Power Save Mode
    ssd1331_write_byte(0x00, SSD1331_CMD);                     //0x00
    ssd1331_write_byte(PHASE_PERIOD_ADJUSTMENT, SSD1331_CMD);//phase 1 and 2 period adjustment
    ssd1331_write_byte(0x31, SSD1331_CMD);                     //0x31
    ssd1331_write_byte(DISPLAY_CLOCK_DIV, SSD1331_CMD);    //display clock divider/oscillator frequency
    ssd1331_write_byte(0xF0, SSD1331_CMD);
    ssd1331_write_byte(SET_PRECHARGE_VOLTAGE, SSD1331_CMD);//Set Pre-Change Level
    ssd1331_write_byte(0x3A, SSD1331_CMD);
    ssd1331_write_byte(SET_V_VOLTAGE, SSD1331_CMD);        //Set vcomH
    ssd1331_write_byte(0x3E, SSD1331_CMD);
    ssd1331_write_byte(DEACTIVE_SCROLLING, SSD1331_CMD);   //disable scrolling
    ssd1331_write_byte(NORMAL_BRIGHTNESS_DISPLAY_ON, SSD1331_CMD);//set display on

//    ssd1331_fill_rect(0, 0, 96, 64, 0x0000);
    ssd1331_clear_screen(0x0000);
}
