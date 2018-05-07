/*
 * flash.c
 *
 *  Created on: 2016-03-22
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include <msp430.h>

static unsigned int seg_addr = 0;    // 全局变量
static unsigned int seg_pre  = 0;    // 全局变量 当前信息段

/******************************************************************************************************
* 名    称：flash_init()
* 功    能：对Flash时钟进行初始化设置
* 入口参数：div：根据SMCLK频率计算的所需分频值，可设定为1-64
*         seg：段号，可设为"0"-"31"或”"A"、"B"、"C"、"D"
* 出口参数：1：配置成功
*         0：配置失败
* 说    明：操作Flash其他函数前，需要调用该初始化函数设置时钟分频和待操作段首地址。
*          其他函数中均不出现绝对地址，防止误操作。
* 范    例：flash_init(3,'B') 3分频、对Info B段操作
 ******************************************************************************************************/
unsigned char flash_init(unsigned char div, unsigned char seg)
{
//-----设置Flash的时钟和分频，分频为恰好为最低位，直接用div-1即可-----
    if (div <  1) div =  1;
    if (div > 64) div = 64;
    FCTL2 = FWKEY + FSSEL_2 + div - 1;              // 默认使用SMCLK，分频系数参数传入
//-----操作对象为主Flash段的情况，可通过512的倍数设置段起始地址-----
    seg_pre = seg;                                  // 获取当前段
    if (seg <= 31) {                                // 判断是否处于主Flash段
        seg_addr = 0xFFFF - (seg + 1) * 512 + 1;    // 计算段起始地址
        return 1;                                   // 赋值成功后即可退出并返回成功标志”1“
    }
//-----操作对象为信息Flash段的情况，穷举即可-----
    switch (seg) {                                  // 判断是否处于信息Flash段
        case 'A':   case 'a':    seg_addr = 0x10C0;    break;
        case 'B':   case 'b':    seg_addr = 0x1080;    break;
        case 'C':   case 'c':    seg_addr = 0x1040;    break;
        case 'D':   case 'd':    seg_addr = 0x1000;    break;
        default:                 seg_addr = 0x20FF;    return 0;   // 0x20FF地址为空白区，保护Flash
    }
    return 1;
}

/******************************************************************************************************
* 名    称：flash_erase()
* 功    能：擦除Flash的一个数据块，擦写段由初始化函数flash_init()的seg_addr变量决定
* 入口参数：无
* 出口参数：无
* 说    明：无
* 范    例：无
 ******************************************************************************************************/
void flash_erase(void)
{
    unsigned char *p_seg_addr;                  // segment pointer
    p_seg_addr = (unsigned char *)seg_addr;     // Initialize Flash pointer
    FCTL1 = FWKEY + ERASE;                      // 段擦除模式
    FCTL3 = FWKEY;                              // 解锁
    __disable_interrupt();
    *p_seg_addr = 0;                            // 擦除待操作段
    while (FCTL3 & BUSY);                       // Busy
    __enable_interrupt();
    FCTL1 = FWKEY;                              // 取消擦模式
    FCTL3 = FWKEY+LOCK;                         // 上锁
}

/******************************************************************************************************
* 名    称：flash_read_char()
* 功    能：从Flash中读取一个字节
* 入口参数：addr：存放数据的偏移地址
* 出口参数：读回的数据；当偏移溢出时返回0
* 说    明：无
* 范    例：无
 ******************************************************************************************************/
unsigned char flash_read_char(unsigned int addr)
{
    unsigned char data = 0;
    unsigned int *p_seg_addr, temp = 0;     // segment pointer
//----- 段范围限定。为了内存管理安全，只允许本段操作-----
    if ((seg_pre <= 31 && addr >= 512) || (seg_pre > 31 && addr >= 64)) {
        return 0;
    }
    temp = seg_addr + addr;
    p_seg_addr = (unsigned int *)temp;      // Initialize Flash pointer
    data = *(p_seg_addr);
    return data;
}

/******************************************************************************************************
* 名    称：flash_read_word()
* 功    能：从FlashROM读回一个整型变量，地址应为偶数
* 入口参数：addr：存放数据的偏移地址，仍按字节计算，需为偶数
* 出口参数：读回的整型变量值；当偏移溢出时返回0
* 说    明：无
* 范    例：无
 ******************************************************************************************************/
unsigned int flash_read_word(unsigned int addr)
{
    unsigned int *p_seg_addr;
    unsigned int temp = 0, data = 0;        // segment pointer
//----- 段范围限定。为了内存管理安全，只允许本段操作-----
    if ((seg_pre <= 31 && addr >= 512) || (seg_pre > 31 && addr >= 64)) {
        return 0;
    }
    temp = seg_addr + addr;
    p_seg_addr = (unsigned int *)temp;      // Initialize Flash pointer
    data = *(p_seg_addr);
    return data;
}

/******************************************************************************************************
* 名    称：flash_read_seg()
* 功    能：将Flash段内一串数据拷贝到RAM的array数组
* 入口参数：addr：起始偏移地址
*         seg_size：数据个数
*         *array：RAM中数组的头指针
* 出口参数：返回出错信息 0：偏移溢出；1：正常工作
* 说    明：无
* 范    例：无
 ******************************************************************************************************/
char flash_read_seg(unsigned int addr, unsigned int seg_size, unsigned char *array)
{
    unsigned int i = 0, temp = 0;
    unsigned char *p_seg_addr;                  // segment pointer
//----- 段范围限定。为了内存管理安全，只允许本段操作-----
    if ((seg_pre <= 31 && (addr + seg_size) > 512) || (seg_pre > 31 && (addr + seg_size) > 64)) {
        return 0;
    }
    for (i=0; i<seg_size; i++) {
        temp = seg_addr + addr + i;             // 防止编译器处理指针偏移出错
        p_seg_addr = (unsigned char *)temp;     // Initialize Flash pointer
        array[i] = *p_seg_addr;                 // 指针移位方法赋值
    }
    return 1;
}

/******************************************************************************************************
* 名    称：flash_direct_write_char()
* 功    能：强行向Flash中写入一个字节(Char型变量)，而不管是否为空
* 入口参数：addr:存放数据的偏移地址
*         data:待写入的数据
* 出口参数：返回出错信息 0：偏移溢出；1：正常工作
* 范    例：flash_direct_write_char(0,123);将常数123写入0单元
*          flash_direct_write_char(1,a);将整型变量a写入1单元
 ******************************************************************************************************/
char flash_direct_write_char(unsigned int addr, unsigned char data)
{
    unsigned int temp = 0;
    unsigned char *p_seg_addr;              // segment pointer
//----- 段范围限定。为了内存管理安全，只允许本段操作-----
    if ((seg_pre <= 31 && addr >= 512) || (seg_pre > 31 && addr >= 64)) {
        return 0;
    }
    temp = seg_addr + addr;
    p_seg_addr = (unsigned char *)temp;     // Initialize Flash pointer
    FCTL1 = FWKEY+WRT;                      // 正常写状态
    FCTL3 = FWKEY;                          // 解除锁定
    __disable_interrupt();                  // 关总中断
    *p_seg_addr = data;                     // 指定地址，写1字节
    while (FCTL3 & BUSY);                   // 等待操作完成
    __enable_interrupt();                   // 开总中断
    FCTL1 = FWKEY;                          // 退出写状态
    FCTL3 = FWKEY+LOCK;                     // 恢复锁定，保护数据
    return 1;
}

/******************************************************************************************************
* 名    称：flash_direct_write_word()
* 功    能：强行向Flash中写入一个字型变量，而不管存储位置是否事先擦除
* 入口参数：addr：存放数据的偏移地址，仍按字节计算，需为偶数
*         data：待写入的数据
* 出口参数：返回出错信息 0：偏移溢出；1：正常工作
* 范    例：flash_direct_write_word(0,123);将常数123写入0单元
*          flash_direct_write_word(2,a);将整型变量a写入2单元
 ******************************************************************************************************/
char flash_direct_write_word(unsigned int addr, unsigned int data)
{
    unsigned int temp = 0;
    unsigned int *p_seg_addr;               // segment pointer
//----- 段范围限定。为了内存管理安全，只允许本段操作-----
    if ((seg_pre <= 31 && addr >= 512) || (seg_pre > 31 && addr >= 64)) {
        return 0;
    }
    temp = seg_addr + addr;
    p_seg_addr = (unsigned int *)temp;      // Initialize Flash pointer
    FCTL1 = FWKEY + WRT;                    // 正常写状态
    FCTL3 = FWKEY;                          // 解除锁定
    __disable_interrupt();                  // 关总中断
    *p_seg_addr = data;                     // 写16位字
    while (FCTL3 & BUSY);                   // 等待操作完成
    __enable_interrupt();                   // 开总中断
    FCTL1 = FWKEY;                          // 退出写状态
    FCTL3 = FWKEY + LOCK;                   // 恢复锁定，保护数据
    return 1;
}

/******************************************************************************************************
* 名    称：flash_bak_write_char()
* 功    能：不破坏段内其他数据，向Flash中写入一个字节(char型变量)
* 入口参数：addr：存放数据的地址
*         data：待写入的数据
* 出口参数：返回出错信息 0：偏移溢出；1：正常工作
* 范    例：flash_bak_write_char(0,123);将常数123写入0单元
*          flash_bak_write_char(1,a);将变量a写入1单元
 ******************************************************************************************************/
char flash_bak_write_char(unsigned int addr, unsigned char data)
{
    unsigned int temp = 0;
    unsigned char *p_seg_addr;                      // segment pointer
    unsigned char backup_array[64];                 // 开辟64字节的临时RAM备份seg
    unsigned char i = 0;
//----- 段范围限定。为了内存管理安全，只允许本段操作-----
    if ((seg_pre <= 31 && addr >= 512) || (seg_pre > 31 && addr > 64)) {
        return 0;
    }
    for (i=0; i<64; i++) {
        temp = seg_addr + i;
        p_seg_addr = (unsigned char *)temp;         // Initialize Flash pointer
        backup_array[i] = *p_seg_addr;              // 指针移位方法赋值
    }
    flash_erase();                                  // 擦除待操作段
    FCTL1 = FWKEY + WRT;                            // 正常写入（非块写）
    FCTL3 = FWKEY;                                  // 解锁
    for (i=0; i<64; i++) {
        __disable_interrupt();                      // 关总中断
        if (i == addr) {
            temp = seg_addr + addr;
            p_seg_addr = (unsigned char *)temp;     // Initialize Flash pointer
            *p_seg_addr = data;                     // 写数据
            while (FCTL3 & BUSY);                   // 等待写操作完成
        } else {
            temp = seg_addr + i;
            p_seg_addr = (unsigned char *)temp;     // Initialize Flash pointer
            *p_seg_addr = backup_array[i];          // 恢复Flash内的其他数据
            while (FCTL3 & BUSY);                   // 等待写操作完成
        }
        __enable_interrupt();                       // 开总中断
    }
    FCTL1 = FWKEY;                                  // 清除写
    FCTL3 = FWKEY + LOCK;                           // 上锁
    return 1;
}

/******************************************************************************************************
* 名    称：flash_bak_write_word()
* 功    能：不破坏段内其他数据，向Flash中写入一个字(int型变量)
* 入口参数：addr：存放数据的地址，仍然是以字节为单位的偏移地址，需为偶数
*         data：待写入的数据
* 出口参数：返回出错信息 0：偏移溢出；1：正常工作
* 说    明：MSP430单片机可以对16位数据直接操作，所以为了加快速度，
*          函数中均直接对word进行操作。
* 范    例：flash_bak_write_word(0,123);将常数123写入0单元
*          flash_bak_write_word(1,a);将变量a写入1单元
 ******************************************************************************************************/
char flash_bak_write_word(unsigned int addr, unsigned int data)
{
    unsigned int *p_seg_addr;                       // segment pointer
    p_seg_addr = (unsigned int *)seg_addr;          // Initialize Flash pointer
//-----注意：以下操作数全部为word16位数据类型-----
    unsigned int backup_array[32];                  // 开辟32字（64字节）的临时RAM备份seg
    unsigned int i = 0;
//----- 段范围限定。为了内存管理安全，只允许本段操作-----
    if ((seg_pre <= 31 && addr >= 512) || (seg_pre > 31 && addr > 64)) {
        return 0;
    }
    for (i=0; i<32; i++) {                          // word型占两个字节
        backup_array[i] = *(p_seg_addr + i);        // 指针移位方法对字赋值
    }
    flash_erase();                                  // 擦除待操作段
    FCTL1 = FWKEY + WRT;                            // 正常写入（非块写）
    FCTL3 = FWKEY;                                  // 解锁
    for (i=0; i<32; i++) {                          // word型占两个字节，需跳过奇数地址
        __disable_interrupt();                      // 关总中断
        if (i == addr) {
            *(p_seg_addr + addr) = data;            // 写字型数据
            while (FCTL3 & BUSY);                   // 等待写操作完成
        } else {
            *(p_seg_addr + i) = backup_array[i];    // 恢复Flash内的其他数据，按字恢复
            while (FCTL3 & BUSY);                   // 等待写操作完成
        }
        __enable_interrupt();                       // 开总中断
    }
    FCTL1 = FWKEY;                                  // 清除写
    FCTL3 = FWKEY + LOCK;                           // 上锁
    return 1;
}

/******************************************************************************************************
* 名    称：flash_seg_a_read_char()
* 功    能：从InfoA中读取一个字节
* 入口参数：addr：存放数据的偏移地址
* 出口参数：读回的数据；偏移溢出时，返回0
 ******************************************************************************************************/
unsigned char flash_seg_a_read_char(unsigned int addr)
{
    unsigned int temp = 0;
    unsigned char data;
//----- 段范围限定。为了内存管理安全，只允许本段操作-----
    if (addr >= 64) {
        return 0;
    }
    unsigned char *p_seg_addr;              // segment pointer
    temp = 0x10c0 + addr;
    p_seg_addr = (unsigned char *)temp;     // Initialize Flash pointer
    data = *p_seg_addr;                     // 直接为InfoA首地址，未使用全局变量seg_addr
    return data;
}
