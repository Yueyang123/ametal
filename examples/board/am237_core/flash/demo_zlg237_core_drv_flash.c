/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief FLASH 例程，通过驱动层接口实现
 *
 * - 实验现象：
 *   1. 擦除出错：串口打印"erase error!"；
 *   2. 写入出错：串口打印"program error!"；
 *   3. 写入成功：串口打印 55 扇区的(1024/4)个 32bit 十六进制数据。
 *
 * \note
 *    如需观察串口打印的调试信息，需要将 PIOA_10 引脚连接 PC 串口的 TXD，
 *    PIOA_9 引脚连接 PC 串口的 RXD。
 *
 * \par 源代码
 * \snippet demo_zlg237_drv_flash.c src_zlg237_drv_flash
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-27  ari, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg237_drv_flash
 * \copydoc demo_zlg237_drv_flash.c
 */

/** [src_zlg237_drv_flash] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_zlg237_flash.h"
#include "am_zlg237.h"
#include "demo_zlg_entries.h"
#include "demo_am237_core_entries.h"

#define FLASH_PAGE           50    /**< \brief 页区 */

void __zlg237_drv_flash_entry (amhw_zlg237_flash_t *p_hw_flash, uint8_t page_num)
{
    int             i;
    uint32_t        status;         /* FLASH 命令执行状态 */
    static uint32_t data[1024 / 4]; /* 要写入 FLASH 的数据 */
    static uint32_t temp[1024 / 4]; /* 从 FLASH 中读出的数据 */

    /* 数据初始化 */
    for (i = 0; i < 1024 / 4; i++) {
        data[i] = i;
    }

    /* FLASH 初始化 */
    am_zlg237_flash_init(p_hw_flash);

    /* 擦除扇区 */
    status = am_zlg237_flash_page_erase(p_hw_flash, page_num * 1024);

    /* 扇区擦除出错， 程序停在此处 */
    if (0 != status) {
        AM_DBG_INFO("erase error!\r\n");

        AM_FOREVER;
    }

    /* 向扇区中写入数据 */
    status = am_zlg237_flash_sector_program(p_hw_flash,
                                            page_num * 1024,
                                            data,
                                            1024 / 4);

    /* 扇区写入出错，程序停在此处 */
    if ((1024 / 4) != status) {
        AM_DBG_INFO("program error!\r\n");

        AM_FOREVER;
    }

    /* 从扇区读取数据 */
    for (i = 0; i < 1024 / 4; i++) {
        temp[i] = *(uint32_t *)((i * 4) + (page_num * 1024));

        /* 校验数据，校验失败，程序停在此处 */
        if (temp[i] != data[i]) {
            AM_DBG_INFO("verify error!\r\n");
            AM_FOREVER;
        }
    }

    AM_DBG_INFO("\r\nflash test success!\r\n");

    AM_FOREVER {
        ; /* VOID */
    }
}

/**
 * \brief 例程入口
 */
void demo_zlg237_core_drv_flash_entry (void)
{
    AM_DBG_INFO("demo am237_core drv flash!\r\n");

    __zlg237_drv_flash_entry(ZLG237_FLASH, FLASH_PAGE);
}

/** [src_zlg237_drv_flash] */

/* end of file */
