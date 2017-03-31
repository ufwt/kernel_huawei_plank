
#include <string.h>
#include "bsp_om_api.h"
#include "bsp_om.h"
#include "drv_comm.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef ENABLE_BUILD_OM
/*****************************************************************************
* �� �� ��  : DRV_OM_SET_HSO_CONN_FLAG
*
* ��������  : flag :���ӱ�־��1��ʾ���ӣ�0��ʾ�Ͽ�
*
* �������  :��
*
*
* �������  :��
*
* �� �� ֵ  :��
*****************************************************************************/

BSP_VOID DRV_OM_SET_HSO_CONN_FLAG(BSP_U32 flag)
{
    return;
}

/*****************************************************************************
* �� �� ��  : DRV_SYSVIEW_SWT_SET
*
* ��������  :sysview�ϱ��������ã���װ�������ṩ��MSPʹ��
*
* �������  :tarce_type :trace����
*                        set_swt  :����ֵ
*                       period  :�ϱ�����
*
* �������  : ��
*
* �� �� ֵ  : BSP_OK
*****************************************************************************/

BSP_U32 DRV_SYSVIEW_SWT_SET(BSP_U32 set_type,BSP_U32 set_swt,BSP_U32 period)
{
    return 0;
}

/*****************************************************************************
* �� �� ��  : DRV_GET_ALL_TASK_ID_NAME
*
* ��������  :��ȡ��ǰ���������ID������
*
* �������  :p_task_stru:�������ƺ�ID����Ľṹ��
*                       param_len:����1�ĳ��ȣ���λ�ֽ�
*
*
* �������  : ��
*
* �� �� ֵ  : BSP_OK/������
*****************************************************************************/
BSP_U32 DRV_GET_ALL_TASK_ID_NAME(BSP_VOID *p_task_stru,u32 param_len)
{
    return 0;
}


/*****************************************************************************
* �� �� ��  : DRV_INT_LOCK
*
* ��������  :���жϽӿڣ��������ж�ͳ��
*
* �������  :��
*
* �������  : ��
*
* �� �� ֵ  : ���жϺ��õ�key
*****************************************************************************/
BSP_S32 DRV_INT_LOCK(BSP_VOID)
{
    return 0;
}


/*****************************************************************************
* �� �� ��  : DRV_INT_UNLOCK
*
* ��������  : �����жϽӿڣ��������ж�ͳ��
*
* �������  : ���жϺ��õ�key
*
* �������  : ��
*
* �� �� ֵ  : ��
*****************************************************************************/
BSP_VOID DRV_INT_UNLOCK(BSP_S32 LockKey)
{
    return;
}


/*****************************************************************************
* �� �� ��  : DRV_SOCP_CHAN_ENABLE
*
* ��������  : ����SOCPͨ��ʹ�ܲ���
*
* �������  : ��
*
*
* �������  :��
*
* �� �� ֵ  :��
*****************************************************************************/

BSP_VOID DRV_SOCP_CHAN_ENABLE(BSP_VOID)
{
    return;
}

int DRV_GET_FS_ROOT_DIRECTORY(char * data, unsigned int len)
{
	strncpy(data, "/modem_log", len);

    return 0;
}

/*****************************************************************************
* �� �� ��  : DRV_LOG_BIN_IND
*
* ��������  : ���������ϱ��ӿ�
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  :��
*****************************************************************************/
BSP_VOID DRV_LOG_BIN_IND(BSP_S32 str_id, BSP_VOID* ind_data, BSP_S32 ind_data_size)
{
	return;
}

/*****************************************************************************
* �� �� ��  : DRV_LOG_BIN_IND_REGISTER
*
* ��������  : ���������ϱ�ע��ӿ�
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  :��
*****************************************************************************/
BSP_VOID DRV_LOG_BIN_IND_REGISTER(log_bin_ind_cb log_ind_cb)
{
	return;
}


#else
/*****************************************************************************
* �� �� ��  : DRV_OM_SET_HSO_CONN_FLAG
*
* ��������  : flag :���ӱ�־��1��ʾ���ӣ�0��ʾ�Ͽ�
*
* �������  :��
*
*
* �������  :��
*
* �� �� ֵ  :��
*****************************************************************************/

BSP_VOID DRV_OM_SET_HSO_CONN_FLAG(BSP_U32 flag)
{
    bsp_om_set_hso_conn_flag(flag);
}

#ifndef ENABLE_BUILD_SYSVIEW
/*****************************************************************************
* �� �� ��  : DRV_SYSVIEW_SWT_SET
*
* ��������  :sysview�ϱ��������ã���װ�������ṩ��MSPʹ��
*
* �������  :tarce_type :trace����
*                        set_swt  :����ֵ
*                       period  :�ϱ�����
*
* �������  : ��
*
* �� �� ֵ  : BSP_OK
*****************************************************************************/

BSP_U32 DRV_SYSVIEW_SWT_SET(BSP_U32 set_type,BSP_U32 set_swt,BSP_U32 period)
{
    return 0;
}

/*****************************************************************************
* �� �� ��  : DRV_GET_ALL_TASK_ID_NAME
*
* ��������  :��ȡ��ǰ���������ID������
*
* �������  :p_task_stru:�������ƺ�ID����Ľṹ��
*                       param_len:����1�ĳ��ȣ���λ�ֽ�
*
*
* �������  : ��
*
* �� �� ֵ  : BSP_OK/������
*****************************************************************************/
BSP_U32 DRV_GET_ALL_TASK_ID_NAME(BSP_VOID *p_task_stru,u32 param_len)
{
    return 0;
}

#else
/*****************************************************************************
* �� �� ��  : DRV_SYSVIEW_SWT_SET
*
* ��������  :sysview�ϱ��������ã���װ�������ṩ��MSPʹ��
*
* �������  :tarce_type :trace����
*                        set_swt  :����ֵ
*                       period  :�ϱ�����
*
* �������  : ��
*
* �� �� ֵ  : BSP_OK
*****************************************************************************/

BSP_U32 DRV_SYSVIEW_SWT_SET(BSP_U32 set_type,BSP_U32 set_swt,BSP_U32 period)
{
    return bsp_sysview_swt_set(set_type,set_swt,period);
}

/*****************************************************************************
* �� �� ��  : DRV_GET_ALL_TASK_ID_NAME
*
* ��������  :��ȡ��ǰ���������ID������
*
* �������  :p_task_stru:�������ƺ�ID����Ľṹ��
*                       param_len:����1�ĳ��ȣ���λ�ֽ�
*
*
* �������  : ��
*
* �� �� ֵ  : BSP_OK/������
*****************************************************************************/
BSP_U32 DRV_GET_ALL_TASK_ID_NAME(BSP_VOID *p_task_stru,u32 param_len)
{
      return sysview_get_all_task_name((void *)p_task_stru,param_len);
}
#endif

/*****************************************************************************
* �� �� ��  : DRV_INT_LOCK
*
* ��������  :���жϽӿڣ��������ж�ͳ��
*
* �������  :��
*
* �������  : ��
*
* �� �� ֵ  : ���жϺ��õ�key
*****************************************************************************/
BSP_S32 DRV_INT_LOCK(BSP_VOID)
{
    BSP_S32 flags;

    flags = (BSP_S32)intLock();

    bsp_int_lock_enter();
    return flags;
}


/*****************************************************************************
* �� �� ��  : DRV_INT_UNLOCK
*
* ��������  : �����жϽӿڣ��������ж�ͳ��
*
* �������  : ���жϺ��õ�key
*
* �������  : ��
*
* �� �� ֵ  : ��
*****************************************************************************/
BSP_VOID DRV_INT_UNLOCK(BSP_S32 LockKey)
{
    bsp_int_lock_out();

    intUnlock(LockKey);
}


/*****************************************************************************
* �� �� ��  : DRV_SOCP_CHAN_ENABLE
*
* ��������  : ����SOCPͨ��ʹ�ܲ���
*
* �������  : ��
*
*
* �������  :��
*
* �� �� ֵ  :��
*****************************************************************************/

BSP_VOID DRV_SOCP_CHAN_ENABLE(BSP_VOID)
{
    bsp_socp_chan_enable();
}

int DRV_GET_FS_ROOT_DIRECTORY(char * data, unsigned int len)
{
	strncpy(data, "/modem_log", len);

    return 0;
}


#endif

#ifdef __cplusplus
}
#endif

