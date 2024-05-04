/*
 * @file:ulog.c
 * @brief:
 * @Date: 2024年5月1日
 * @Author: iTuring
 */


// **************************************************************************
// 头文件

#include "ulog.h"

static const char UCode[] = "0123456789ABCDEFX";

// **************************************************************************
// 接口函数

/******************************************************************************************
说明: 打印内存数据 分别以十六进制和字符模式打印
00000000: 01 02 03 04 05 06 07 08 01 02 03 04 05 06 07 08 ................
支持
%s	--打印字符串	%c打印字符
参数:
// @pbuff           内存指针
// @size            数量
// @addr            打印显示地址
// @linsize         每行打印数量
返回值:	void
******************************************************************************************/
void log_printmem(void* buff, uint32_t size, uint32_t addr, uint8_t linsize)
{
    uint32_t temp;
    register uint8_t c;
    register uint32_t i;
    uint8_t* pbuff = (uint8_t*)buff;

    //参数检查
    if (!pbuff || !linsize)
        return;

    for (; size; size -= temp, addr += temp)
    {
        //打印地址
        temp = addr;
        for (i = 0; i < 8; ++i)
        {
            LOG_PUT_CHAR(UCode[temp >> 28]);	/* 先打印高HEX字符 */
            temp <<= 4;				            /* 为下次打印做准备 */
        }
        LOG_PUT_CHAR(':');
        LOG_PUT_CHAR(' ');

        //按hex格式打印数据
        temp = size < linsize ? size : linsize; /* 计算所需打印字符数量 */
        for (i = 0; i < temp; ++i)
        {
            c = pbuff[i];
            LOG_PUT_CHAR(UCode[c >> 4]);
            LOG_PUT_CHAR(UCode[c & 0x0f]);
            LOG_PUT_CHAR(' ');
        }
        //打印对齐空白
        for (i = linsize - temp; i; --i)
        {
            LOG_PUT_CHAR(' '); LOG_PUT_CHAR(' '); LOG_PUT_CHAR(' ');
        }

        //按ASCII码打印数据
        LOG_PUT_CHAR(' ');
        for (i = temp; i; --i)
        {
            c = *pbuff++;
            if (c<' ' || c>'\x7f') c = '.';
            LOG_PUT_CHAR(c);	    /* 打印字符 */
        }
        LOG_PUT_CHAR('\n');
    }
}
