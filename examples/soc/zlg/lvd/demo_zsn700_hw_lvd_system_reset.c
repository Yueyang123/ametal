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
 * \brief LVD ϵͳ��λ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *
 *   PIOB_7�����ƽ�������õĻ�׼��ѹ����ϵͳ���ڸ�λ״̬�����ٴθ��ڻ�׼��ѹLED��˸һ�Σ�ϵͳ����������
 *   ����������ӡ "Mcu is running!"��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_zsn700_hw_lvd_int.c src_zsn700_hw_lvd_int
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 20-03-09  yrz, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn700_hw_lvd_int
 * \copydoc demo_zsn700_hw_lvd_int.c
 */

/** [src_zsn700_hw_lvd_int] */
#include "ametal.h"
#include "am_zsn700.h"
#include "am_int.h"
#include "am_board.h"
#include "am_zsn700_lvd.h"
#include "hw/amhw_zsn700_lvd.h"
#include "hw/amhw_zsn700_rcc_reset.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define LVD_TRI_TYPE AMHW_ZSN700_LVD_HTEN                /**< \brief LVD�������� */
#define LVD_DEB_TIME AMHW_ZSN700_LVD_DEB_TIME_7P2_MS     /**< \brief LVD�˲�ʱ�� */
#define LVD_VIDS     AMHW_ZSN700_LVD_VIDS_2P5_V          /**< \brief LVD��׼��ѹ */
#define LVD_SRC      ANHW_ZSN700_LVD_SRC_PB07            /**< \brief LVD���Դ*/
#define LVD_TRI_ACT  ANHW_ZSN700_LVD_TRI_ACT_SYSTEM_RESET /**< \brief LVD��������*/

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/
static amhw_zsn700_lvd_t       *gp_hw_lvd   = NULL;  /**< \brief lvd ���� */

/**
 * \brief LVD��ʼ��
 */
static void lvd_init ()
{
    /* cr�Ĵ������� */
    amhw_zsn700_lvd_cr_clr (gp_hw_lvd);

    /* ��������ʹ�� */
    amhw_zsn700_lvd_tri_enable (gp_hw_lvd, LVD_TRI_TYPE);

    /* �����˲�ʱ��ѡ�� */
    amhw_zsn700_lvd_deb_time_sel (gp_hw_lvd, LVD_DEB_TIME);

    /* ʹ�������˲� */
    amhw_zsn700_lvd_deb_time_enable (gp_hw_lvd);

    /* ��ֵ��ѹѡ�� */
    amhw_zsn700_lvd_vids_sel (gp_hw_lvd, LVD_VIDS);

    /* �����Դѡ�� */
    amhw_zsn700_lvd_src_sel (gp_hw_lvd, LVD_SRC);

    /* ������������ */
    amhw_zsn700_lvd_tri_act_sel (gp_hw_lvd, LVD_TRI_ACT);

}

/**
 * \brief �������
 */
void demo_zsn700_hw_lvd_system_reset_entry (void *p_hw_lvd)
{
    if (p_hw_lvd == NULL)
    {
        return ;
    }

    gp_hw_lvd  = (amhw_zsn700_lvd_t *)p_hw_lvd;

    /* �жϸ�λ��־ */
    if (amhw_zsn700_rcc_reset_flag_check (AMHW_ZSN700_RCC_RESET_FLAG_LVD))
        {
        am_led_on(LED0);
        am_mdelay(1000);
        am_led_off(LED0);
        am_mdelay(1000);
        am_led_on(LED0);

        /* �����λ��־ */
        amhw_zsn700_rcc_reset_flag_clr(AMHW_ZSN700_RCC_RESET_FLAG_LVD);
    }

    /* LVD��ʼ�� */
    lvd_init ();

    /* LVDʹ�� */
    amhw_zsn700_lvd_enable (p_hw_lvd);

    while (1){
        am_kprintf ("Mcu is running!\r\n");
    }
}

/* end of file */