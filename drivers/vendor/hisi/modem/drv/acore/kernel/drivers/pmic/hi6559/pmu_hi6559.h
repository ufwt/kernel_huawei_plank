#ifndef __PMU_HI6559_H
#define __PMU_HI6559_H
#ifdef __cplusplus
extern "C"
{
#endif

#if defined(__VXWORKS__)

#include <drv_dpm.h>

/*****************************************************************************
 函 数 名  : bsp_pmu_hi6559_pa_rf_init
 功能描述  : pa/rf供电部分初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 0:成功；else - 失败。失败时返回值的bit0~bit4对应获取失败的regulator_pmu id
*****************************************************************************/
s32 bsp_pmu_hi6559_pa_rf_init(void);

/*****************************************************************************
 函 数 名  : bsp_pmu_hi6559_rf_poweroff
 功能描述  : 给rf下电
 输入参数  : @modem_id - 主卡or副卡(6559只支持单卡，此参数无用)
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
s32 bsp_pmu_hi6559_rf_poweroff(PWC_COMM_MODEM_E modem_id);

/*****************************************************************************
 函 数 名  : bsp_pmu_hi6559_rf_poweron
 功能描述  : 给rf上电
 输入参数  : @modem_id - 主卡or副卡(6559只支持单卡，此参数无用)
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
s32 bsp_pmu_hi6559_rf_poweron(PWC_COMM_MODEM_E modem_id);

/*****************************************************************************
 函 数 名  : bsp_pmu_hi6559_get_rf_powerstatus
 功能描述  : 获取rf上下电状态
 输入参数  : @modem_id - 主卡or副卡(6559只支持单卡，此参数无用)
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
PWC_COMM_STATUS_E bsp_pmu_hi6559_get_rf_powerstatus(PWC_COMM_MODEM_E modem_id);

/*****************************************************************************
 函 数 名  : bsp_pmu_hi6559_pa_poweroff
 功能描述  : 给pa下电
 输入参数  : @modem_id - 主卡or副卡(6559只支持单卡，此参数无用)
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
s32 bsp_pmu_hi6559_pa_poweroff(PWC_COMM_MODEM_E modem_id);

/*****************************************************************************
 函 数 名  : bsp_pmu_hi6559_pa_poweron
 功能描述  : 给pa上电
 输入参数  : @modem_id - 主卡or副卡(6559只支持单卡，此参数无用)
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
s32 bsp_pmu_hi6559_pa_poweron(PWC_COMM_MODEM_E modem_id);

/*****************************************************************************
 函 数 名  : bsp_pmu_hi6559_get_pa_powerstatus
 功能描述  : 获取pa上下电状态
 输入参数  : @modem_id - 主卡or副卡(6559只支持单卡，此参数无用)
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
PWC_COMM_STATUS_E bsp_pmu_hi6559_get_pa_powerstatus(PWC_COMM_MODEM_E modem_id);

/*****************************************************************************
 函 数 名  : bsp_hi6559_parf_reg_save
 功能描述  : 进入深睡时保存寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
u32 bsp_hi6559_parf_reg_save(void);

/*****************************************************************************
 函 数 名  : bsp_hi6559_parf_reg_resume
 功能描述  : 退出深睡时恢复寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 0 - 成功，非0 - 失败
*****************************************************************************/
u32 bsp_hi6559_parf_reg_resume(void);

#endif /* #if defined(__VXWORKS__) */
#ifdef __cplusplus
}
#endif

#endif /* #ifndef __PMU_HI6559_H */

