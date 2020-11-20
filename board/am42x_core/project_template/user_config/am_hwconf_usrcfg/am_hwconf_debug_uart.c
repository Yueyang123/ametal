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
 * \brief ���Դ����û������ļ�
 * \sa am_hwconf_debug_uart.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-20  pea, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_uart.h"
#include "am_vdebug.h"
#include "am_zsl42x_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_debug_uart
 * \copydoc am_hwconf_debug_uart.c
 * @{
 */

/**
 * \brief ʹ�õĵ��Դ��ڣ�Ĭ�� LPUART0
 * 1 - UART1; 2 - UART2; 3 - UART3;  4 - LPUART0
 */
#define __DEBUG_UART            4

/** \brief ���õ��Դ�������Ĳ����� */
#define __DEBUG_BAUDRATE        115200

/** \brief ���Դ���ʵ����ʼ�� */
am_uart_handle_t am_debug_uart_inst_init (void)
{
    am_uart_handle_t handle = NULL;

#if (__DEBUG_UART == 0)

    handle = am_zsl42x_uart0_inst_init();

    /* ���Գ�ʼ�� */
    am_debug_init(handle, __DEBUG_BAUDRATE);

#endif /* (__DEBUG_UART == 0) */

#if (__DEBUG_UART == 1)

    handle = am_zsl42x_uart1_inst_init();

    /* ���Գ�ʼ�� */
    am_debug_init(handle, __DEBUG_BAUDRATE);

#endif /* (__DEBUG_UART == 1) */

#if (__DEBUG_UART == 2)

    handle = am_zsl42x_uart2_inst_init();

    /* ���Գ�ʼ�� */
    am_debug_init(handle, __DEBUG_BAUDRATE);

#endif /* (__DEBUG_UART == 2) */

#if (__DEBUG_UART == 3)

    handle = am_zsl42x_uart3_inst_init();

    /* ���Գ�ʼ�� */
    am_debug_init(handle, __DEBUG_BAUDRATE);

#endif /* (__DEBUG_UART == 3) */

#if (__DEBUG_UART == 4)

    handle = am_zsl42x_lpuart0_inst_init();

    /* ���Գ�ʼ�� */
    am_debug_init(handle, __DEBUG_BAUDRATE);

#endif /* (__DEBUG_UART == 3) */

    return handle;
}

/**
 * @}
 */

/* end of file */