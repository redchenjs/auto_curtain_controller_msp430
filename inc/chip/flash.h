/*
 * flash.h
 *
 *  Created on: 2016-03-22
 *      Author: Jack Chen <redchenjs@live.com>
 */

#ifndef INC_CHIP_FLASH_H_
#define INC_CHIP_FLASH_H_

extern unsigned char flash_init(unsigned char div, unsigned char seg);
extern void flash_erase(void);
extern unsigned char flash_read_char(unsigned int addr);
extern unsigned int flash_read_word(unsigned int addr);
extern char flash_read_seg(unsigned int addr, unsigned int seg_size, unsigned char *array);
extern char flash_direct_write_char(unsigned int addr, unsigned char data);
extern char flash_direct_write_word(unsigned int addr, unsigned int data);
extern char flash_bak_write_char(unsigned int addr, unsigned char data);
extern char flash_bak_write_word(unsigned int addr, unsigned int data);
extern unsigned char flash_seg_a_read_char(unsigned int addr);

#endif /* INC_CHIP_FLASH_H_ */
