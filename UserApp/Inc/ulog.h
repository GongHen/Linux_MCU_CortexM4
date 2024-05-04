/*
 * @file:ulog.h
 * @brief:
 * @Date: 2024年5月1日
 * @Author: iTuring
 * //
//@文件说明:
//
//ulog    微型的日志调试工具
//支持日志记录级别设置
//G_DEBUG -- 调试级别，记录非常详细的步骤信息
//G_TRACE -- 跟踪级别，记录重要的跟踪信息
//G_WARNG -- 警告级别，记录警告信息
//G_ERROR -- 错误级别，记录错误信息
//ulog支持基于宏和函数的两种实现方式
//
//@修订说明:
 */


#ifndef INC_ULOG_H_
#define INC_ULOG_H_

// **************************************************************************
// 头文件

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include "usart.h"

// **************************************************************************
// 用户配置

// log级别
#define LOG_CFG_LEVEL   (G_DEBUG)
// 字符输出函数
#define LOG_PUT_CHAR(C) putchar(C)
// 日志记录接口
#define LOG_PRINTF(format, ...) print_console(format, ##__VA_ARGS__)

// **************************************************************************
// 宏定义

//日志记录级别
#define	G_DEBUG (0)     /* 信息用来显示详细的执行信息和步骤 */
#define	G_TRACE (1)     /* 用来跟踪特定的主要信息 */
#define G_WARNG (2)     /* 警告级别 */
#define	G_ERROR (3)     /* 错误级别 */
#define	G_NONE  (4)     /* 关闭LOG */

// 定义打印样式
#define LOG_FUN(LEVESTR,format, ...)       \
    LOG_PRINTF("["LEVESTR"] <"__FILE__": %d"">: " format "\r\n",__LINE__,##__VA_ARGS__)

// **************************************************************************
// 接口定义

//兼容C C++混合编程
#ifdef __cplusplus
extern "C" {
#endif

void log_printmem(void* buff, uint32_t size, uint32_t addr, uint8_t linsize);

#ifdef __cplusplus
}
#endif

#if LOG_CFG_LEVEL>=G_NONE
/* 关闭LOG */
#define uLOG(LEVE,format, ...)   /*(0)*/
#define uLOG_MEM(aLEVE,ADDRESS,LEN) (0)
#else
/* 使用宏实现 */
#define uLOG(aLEVE,format, ...)         \
    do {                                \
        if (aLEVE>=LOG_CFG_LEVEL) {     \
            LOG_FUN(#aLEVE,format,##__VA_ARGS__); \
        }                               \
    } while(0)

#define uLOG_MEM(aLEVE,ADDRESS,LEN,format, ...) \
    do {                                        \
        if (aLEVE>=LOG_CFG_LEVEL) {             \
            LOG_FUN(#aLEVE,format,##__VA_ARGS__); \
            log_printmem(ADDRESS,LEN,0,16);     \
        }   \
    } while(0)

#endif


#endif /* INC_ULOG_H_ */
