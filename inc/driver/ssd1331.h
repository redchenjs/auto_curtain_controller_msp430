#ifndef SSD1331_H_
#define SSD1331_H_

#define RGB(R,G,B)  (((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3))
enum rgb_color{
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
    PURPLE    = RGB(160, 32,240)  // purple
};

extern void ssd1331_draw_point(unsigned char chXpos, unsigned char chYpos, unsigned int hwColor);
extern void ssd1331_draw_line(unsigned char chXpos0, unsigned char chYpos0, unsigned char chXpos1, unsigned char chYpos1, unsigned int hwColor);
extern void ssd1331_draw_v_line(unsigned char chXpos, unsigned char chYpos, unsigned char chHeight, unsigned int hwColor);
extern void ssd1331_draw_h_line(unsigned char chXpos, unsigned char chYpos, unsigned char chWidth, unsigned int hwColor);
extern void ssd1331_draw_rect(unsigned char chXpos, unsigned char chYpos, unsigned char chWidth, unsigned char chHeight, unsigned int hwColor);
extern void ssd1331_fill_rect(unsigned char chXpos, unsigned char chYpos, unsigned char chWidth, unsigned char chHeight, unsigned int hwColor);
extern void ssd1331_draw_circle(unsigned char chXpos, unsigned char chYpos, unsigned char chRadius, unsigned int hwColor);
extern void ssd1331_display_char(unsigned char chXpos, unsigned char chYpos, unsigned char chChr, unsigned char chSize, unsigned int hwColor);
extern void ssd1331_display_num(unsigned char chXpos, unsigned char chYpos, unsigned long chNum, unsigned char chLen, unsigned char chSize, unsigned int hwColor);
extern void ssd1331_display_string(unsigned char chXpos, unsigned char chYpos, const char *pchString, unsigned char chSize, unsigned int hwColor);
extern void ssd1331_draw_1612char(unsigned char chXpos, unsigned char chYpos, unsigned char chChar, unsigned int hwColor);
extern void ssd1331_draw_3216char(unsigned char chXpos, unsigned char chYpos, unsigned char chChar, unsigned int hwColor);
extern void ssd1331_draw_bitmap(unsigned char chXpos, unsigned char chYpos, const unsigned char *pchBmp, unsigned char chWidth, unsigned char chHeight, unsigned int hwColor);
extern void ssd1331_clear_screen(unsigned int hwColor);

extern void ssd1331_init(void);

#endif
