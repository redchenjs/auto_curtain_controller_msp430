#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user/motor.h"
#include "user/senser.h"
#include "user/record.h"
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

static const unsigned char init_message[] = "msp430g2553 initialized.\n";

static unsigned char read_buff[SIZE] = {0};
static unsigned char read_buff_num = 0;

char* terminal_sub_string(char* p_string, unsigned char position, unsigned char length)
{
    unsigned int i;
    static char sub_string[32] = {0};

    p_string += position;

    for (i=0; i<length; i++) {
        sub_string[i] = *p_string++;
    }

    sub_string[length] = '\0';

    return sub_string;
}

void terminal_set_mode(unsigned int value)
{
    mode_past = mode_now;

    if (value == AUTO) {
        mode_now = AUTO;
    }
    else {
        mode_now = MANUAL;
    }

    record_write_all();
}

unsigned char terminal_match(void)
{
    unsigned char i;
    char string[32] = {0};
    char *p_string = string;
    unsigned char operate, func;
    unsigned int value = 0;

    p_string = terminal_sub_string((char *)read_buff, 0, 4);
    if (strcmp(p_string, "set\x20") == 0) {
        operate = SET;
    }
    else if (strcmp(p_string, "get\x20") == 0) {
        operate = GET;
    }
    else {
        return 0;
    }

    p_string = terminal_sub_string((char *)read_buff, 4, 4);
    if (strcmp(p_string, "mod\x20") == 0) {
        func = MODE;
    }
    else if (strcmp(p_string, "sta\x20") == 0) {
        func = STAT;
    }
    else if (strcmp(p_string, "lux\x20") == 0) {
        func = LUX;
    }
    else if (strcmp(p_string, "pos\x20") == 0) {
        func = POSITION;
    }
    else {
        return 0;
    }

    if (operate == SET) {
        p_string = terminal_sub_string((char *)read_buff, 8, 5);
        switch (func) {
            case MODE:
                if (strcmp(p_string, "auto\n") == 0) {
                    terminal_set_mode(AUTO);
                }
                else if (strcmp(p_string, "manu\n") == 0) {
                    terminal_set_mode(MANUAL);
                }
                else {
                    return 0;
                }

                if (mode_now == AUTO) {
                    uart_transmit_frame("auto\n", 5);
                }
                else {
                    uart_transmit_frame("manual\n", 7);
                }
                break;
            case STAT:
                switch (motor_status_now) {
                    case CLOSED:
                        uart_transmit_frame("closed\n", 7);
                        break;
                    case OPENED:
                        uart_transmit_frame("opened\n", 7);
                        break;
                    case CLOSING:
                        uart_transmit_frame("closing\n", 8);
                        break;
                    case OPENING:
                        uart_transmit_frame("opening\n", 8);
                        break;
                    default:
                        break;
                }
                break;
            case LUX:
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
                senser_set_lux(value);
                sprintf(p_string, "%u\n", senser_set_now);
                uart_transmit_frame((unsigned char *)p_string, strlen(p_string));
                break;
            case POSITION:
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
                terminal_set_mode(MANUAL);
                motor_set_position(value);
                sprintf(p_string, "%u\n", motor_position_now);
                uart_transmit_frame((unsigned char *)p_string, strlen(p_string));
                break;
            default:
                break;
        }
    }
    else if (operate == GET) {
        switch (func) {
            case MODE:
                if (mode_now == AUTO) {
                    uart_transmit_frame("auto\n", 5);
                }
                else {
                    uart_transmit_frame("manual\n", 7);
                }
                break;
            case STAT:
                switch (motor_status_now) {
                    case CLOSED:
                        uart_transmit_frame("closed\n", 7);
                        break;
                    case OPENED:
                        uart_transmit_frame("opened\n", 7);
                        break;
                    case CLOSING:
                        uart_transmit_frame("closing\n", 8);
                        break;
                    case OPENING:
                        uart_transmit_frame("opening\n", 8);
                        break;
                    default:
                        break;
                }
                break;
            case LUX:
                p_string = terminal_sub_string((char *)read_buff, 8, 4);
                if (strcmp(p_string, "now\n") == 0) {
                    sprintf(p_string, "%u\n", senser_lux_now);
                    uart_transmit_frame((unsigned char *)p_string, strlen(p_string));
                }
                else if (strcmp(p_string, "set\n") == 0) {
                    sprintf(p_string, "%u\n", senser_set_now);
                    uart_transmit_frame((unsigned char *)p_string, strlen(p_string));
                }
                else {
                    return 0;
                }
                break;
            case POSITION:
                sprintf(p_string, "%u\n", motor_position_now);
                uart_transmit_frame((unsigned char *)p_string, strlen(p_string));
                break;
            default:
                break;
        }
    }

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
    uart_transmit_frame((unsigned char*)init_message, strlen((char*)init_message));
}
