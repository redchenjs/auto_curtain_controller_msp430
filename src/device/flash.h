/*
 * Flash.h
 *
 *  Created on: 2013-2-20
 *      Author: Administrator
 */

#ifndef FLASH_H_
#define FLASH_H_

extern unsigned char flash_init(unsigned char Div,unsigned char Seg);
extern void flash_erase();
extern unsigned char flash_read_char(unsigned int Addr);
extern unsigned int flash_read_word(unsigned int Addr);
extern char flash_read_seg(unsigned int Addr, unsigned int SegSize,unsigned char * Array);
extern char flash_direct_write_char(unsigned int Addr,unsigned char Data);
extern char flash_direct_write_word(unsigned int Addr,unsigned int Data);
extern char flash_bak_write_char(unsigned int Addr,unsigned char Data);
extern char flash_bak_write_word(unsigned int Addr,unsigned int Data);
extern unsigned char flash_seg_a_read_char(unsigned int Addr);

#endif /* FLASH_H_ */
