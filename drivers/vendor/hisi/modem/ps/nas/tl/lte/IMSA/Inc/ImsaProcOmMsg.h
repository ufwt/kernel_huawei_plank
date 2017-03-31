

#ifndef __IMSAPROCOMMSG_H__
#define __IMSAPROCOMMSG_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "omerrorlog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/



/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/



/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_VOID IMSA_RcvAcpuOmErrLogCtrlInd
(
    VOS_VOID                           *pMsg
);

extern VOS_VOID IMSA_SndAcpuOmErrLogRptCnf
(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulBufUseLen
);

extern VOS_VOID IMSA_RcvAcpuOmErrLogRptReq
(
    VOS_VOID                           *pMsg
);

extern VOS_VOID IMSA_ReadErrlogCtrlInfoNvim(VOS_VOID);
#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasErrorLog.h */

