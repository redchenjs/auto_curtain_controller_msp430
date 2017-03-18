#include <stdlib.h>
#include <string.h>
#include "user/senser.h"
#include "user/terminal.h"
#include "interface/uart.h"
/*
 * terminal.c
 *
 *  Created on: 2017-2-19
 *      Author: redchenjs
 */
#define SIZE 32

enum operate {
    SET = 0x00,
    GET = 0x01
};

enum func {
    MODE     = 0x00,
    STAT     = 0x01,
    LUX      = 0x02,
    POSITION = 0x03
};

unsigned char mode_now  = AUTO;
unsigned char mode_past = AUTO;

static unsigned char read_buff[SIZE] = {0};
static unsigned char read_buff_num = 0;

void terminal_value_to_string(unsigned int value, char *p_string)
{
    char i;

    for (i=5; i>0; i--) {
        p_string[i-1] = '0' + value % 10;
        value /= 10;
    }
    p_string[5] = '\0';
    for (i=0; i<4; i++) {
        if (p_string[i] == '0')
            p_string[i] = ' ';
        else
            break;
    }
}

char* terminal_sub_string(char* p_string, unsigned char position, unsigned char length)
{
    unsigned int i;
    char *sub_string = (char*)calloc(sizeof(char), length+1);

    p_string += position;

    for (i=0; i<length; i++) {
        sub_string[i] = *p_string++;
    }

    sub_string[length] = '\0';

    return sub_string;
}

unsigned char terminal_match(void)
{
    unsigned char i;
    char string[32] = {0};
    char *p_string = string;
    unsigned char operate, func;
    unsigned int value = 0;

    p_string = terminal_sub_string((char *)read_buff, 0, 3);
    if (strcmp(p_string, "set") == 0) {
        operate = SET;
    }
    else if (strcmp(p_string, "get") == 0) {
        operate = GET;
    }
    else {
        return 0;
    }

    p_string = terminal_sub_string((char *)read_buff, 4, 3);
    if (strcmp(p_string, "mod") == 0) {
        func = MODE;
    }
    else if (strcmp(p_string, "sta") == 0) {
        func = STAT;
    }
    else if (strcmp(p_string, "lux") == 0) {
        func = LUX;
    }
    else if (strcmp(p_string, "pos") == 0) {
        func = POSITION;
    }
    else {
        return 0;
    }

    p_string = terminal_sub_string((char *)read_buff, 8, 5);
    for (i=0; i<5; i++) {
        if (p_string[i] >= '0' && p_string[i] <= '9') {
            value = p_string[i] - '0' + value * 10;
        }
        else if (p_string[i] == '\n'){
            break;
        }
        else {
            return 0;
        }
    }

    if (operate == SET) {
        switch (func) {
            case MODE:
                break;
            case STAT:
                break;
            case LUX:
                senser_set_lux(value);
                break;
            case POSITION:
                break;
            default:
                break;
        }
    }
    else if (operate == GET) {
        switch (func) {
            case MODE:
                break;
            case STAT:
                break;
            case LUX:
                break;
            case POSITION:
                break;
            default:
                break;
        }
    }

//    sprintf(p_string, "%u\n", value);
//    uart_transmit_frame((unsigned char*)p_string, 6);

    return 1;
}

void terminal_update(void)
{
    read_buff_num = uart_receive_frame(read_buff, SIZE);
    if (read_buff_num) {
        if (!terminal_match())
            uart_transmit_frame(read_buff, read_buff_num);
        read_buff_num = 0;
    }
}

void terminal_init(void)
{
    uart_transmit_frame("msp430g2553 terminal initialized.\n", 34);
}
