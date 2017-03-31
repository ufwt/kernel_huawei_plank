


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasLmmPubMInclude.h"
/*#include    "IpDhcpv4Server.h"*/
#include    "NasERabmIpFilter.h"
/* lihong00150010 ims begin */
#include    "NasEmmSecuOm.h"
#include    "ImsaNvInterface.h"
/* lihong00150010 ims end */
#include    "SysNvId.h"

#include    "omringbuffer.h"
#include    "omnvinterface.h"
#if (VOS_WIN32 == VOS_OS_VER)
#include    "NasMmPubMTest.h"
#endif
#include    "NasEmmAttDetInclude.h"


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASMMPUBMOM_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASMMPUBMOM_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
NAS_EMM_DRX_CYCLE_LEN_CHANGE_ENUM_UINT32    g_ulDrxCycleLenChange
                                            = NAS_EMM_DRX_CYCLE_LEN_NOT_CHANGED;
/*
static APP_MM_REPORT_MODE_ENUM_UINT32      g_ulMmInfoRptFlag = APP_MM_RM_AUTO;
static APP_EMM_INFO_STRU                   g_stAppEmmInfo = {0};
*/

#if (FEATURE_ON == FEATURE_PTM)
LNAS_ERRLOG_GLO_INFO_STRU  stErrlogGloInfo;
/* LNASģ��Error Log�쳣����� */
LNAS_ERRLOG_ALM_LEVEL_STRU g_astLNasErrAlmLevelTb[] = {
    {LNAS_OM_ERRLOG_ALM_ID_ATTACH_FAIL,         LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_TAU_FAIL,            LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_DETACH_FAIL,         LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_NOR_SERVICE_FAIL,    LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_EXT_SERVICE_FAIL,    LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_PAGING_FAIL,         LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_RAT_FAIL,            LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_ESM_PDN_CONN_FAIL,   LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_ESM_PDN_DISCONN_FAIL,LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_ESM_RES_MOD_FAIL,    LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_ESM_RES_ALLOC_FAIL,  LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_OVERFLOW_FAIL,       LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_LOCAL_DETACH_FAIL,   LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_AUTH_REJ,            LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
};

NAS_LMM_CN_CAUSE_TRANS_STRU          g_astEmmErrlogCnCauseMap[] =
{
    /*------------casue-----------------------------------error id---------------------------*/
    {NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS,                 EMM_OM_ERRLOG_CN_CAUSE_IMSI_UNKNOWN_IN_HSS},
    {NAS_LMM_CAUSE_ILLEGAL_UE,                          EMM_OM_ERRLOG_CN_CAUSE_ILLEGAL_UE},
    {NAS_LMM_CAUSE_IMEI_NOT_ACCEPTED,                   EMM_OM_ERRLOG_CN_CAUSE_IMEI_NOT_ACCEPTED},
    {NAS_LMM_CAUSE_ILLEGAL_ME,                          EMM_OM_ERRLOG_CN_CAUSE_ILLEGAL_ME},
    {NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW,                  EMM_OM_ERRLOG_CN_CAUSE_EPS_SERV_NOT_ALLOW},
    {NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW, EMM_OM_ERRLOG_CN_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW},
    {NAS_LMM_CAUSE_UE_ID_NOT_DERIVED,                   EMM_OM_ERRLOG_CN_CAUSE_UE_ID_NOT_DERIVED},
    {NAS_LMM_CAUSE_IMPLICIT_DETACHED,                   EMM_OM_ERRLOG_CN_CAUSE_IMPLICIT_DETACHED},
    {NAS_LMM_CAUSE_PLMN_NOT_ALLOW,                      EMM_OM_ERRLOG_CN_CAUSE_PLMN_NOT_ALLOW},
    {NAS_LMM_CAUSE_TA_NOT_ALLOW,                        EMM_OM_ERRLOG_CN_CAUSE_TA_NOT_ALLOW},
    {NAS_LMM_CAUSE_ROAM_NOT_ALLOW,                      EMM_OM_ERRLOG_CN_CAUSE_ROAM_NOT_ALLOW},
    {NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,          EMM_OM_ERRLOG_CN_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN},
    {NAS_LMM_CAUSE_NO_SUITABL_CELL,                     EMM_OM_ERRLOG_CN_CAUSE_NO_SUITABL_CELL},
    {NAS_LMM_CAUSE_MSC_UNREACHABLE,                     EMM_OM_ERRLOG_CN_CAUSE_MSC_UNREACHABLE},
    {NAS_LMM_CAUSE_NETWORK_FAILURE,                     EMM_OM_ERRLOG_CN_CAUSE_NETWORK_FAILURE},
    {NAS_LMM_CAUSE_CS_NOT_AVAIL,                        EMM_OM_ERRLOG_CN_CAUSE_CS_NOT_AVAIL},
    {NAS_LMM_CAUSE_ESM_FAILURE,                         EMM_OM_ERRLOG_CN_CAUSE_ESM_FAILURE},
    {NAS_LMM_CAUSE_MAC_FAILURE,                         EMM_OM_ERRLOG_CN_CAUSE_MAC_FAILURE},
    {NAS_LMM_CAUSE_SYNCH_FAILURE,                       EMM_OM_ERRLOG_CN_CAUSE_SYNCH_FAILURE},
    {NAS_LMM_CAUSE_PROCEDURE_CONGESTION,                EMM_OM_ERRLOG_CN_CAUSE_PROCEDURE_CONGESTION},
    {NAS_LMM_CAUSE_UE_SECU_CAP_MISMATCH,                EMM_OM_ERRLOG_CN_CAUSE_UE_SECU_CAP_MISMATCH},
    {NAS_LMM_CAUSE_SECU_MODE_REJECTED_UNSPECIFIED,      EMM_OM_ERRLOG_CN_CAUSE_SECU_MODE_REJECTED_UNSPECIFIED},
    {NAS_LMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG,         EMM_OM_ERRLOG_CN_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG},
    {NAS_LMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN, EMM_OM_ERRLOG_CN_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN},
    {NAS_LMM_CAUSE_CS_FALLBACK_CALL_EST_NOT_ALLOWED,    EMM_OM_ERRLOG_CN_CAUSE_CS_FALLBACK_CALL_EST_NOT_ALLOWED},
    {NAS_LMM_CAUSE_CS_DOMAIN_TMP_NOT_ALLOWED,           EMM_OM_ERRLOG_CN_CAUSE_CS_DOMAIN_TMP_NOT_ALLOWED},
    {NAS_LMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED,     EMM_OM_ERRLOG_CN_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED},
    {NAS_LMM_CAUSE_SERVICE_NETWORK_FAILURE,             EMM_OM_ERRLOG_CN_CAUSE_SERVER_NETWORK_FAILURE},
    {NAS_LMM_CAUSE_SEMANTICALLY_INCORRECT_MSG,          EMM_OM_ERRLOG_CN_CAUSE_SEMANTICALLY_INCORRECT_MSG},
    {NAS_LMM_CAUSE_INVALID_MANDATORY_INF,               EMM_OM_ERRLOG_CN_CAUSE_INVALID_MANDATORY_INFORMATION},
    {NAS_LMM_CAUSE_IE_NONEXIST_NOTIMPLEMENTED,          EMM_OM_ERRLOG_CN_CAUSE_MSG_TYPE_NON_EXIST_OR_IMPLEMENT},
    {NAS_LMM_CAUSE_MSG_TYPE_NOT_COMPATIBLE,             EMM_OM_ERRLOG_CN_CAUSE_MSG_TYPE_NOT_COMPATIBLE},
    {NAS_LMM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE,          EMM_OM_ERRLOG_CN_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENT},
    {NAS_LMM_CAUSE_CONDITIONAL_IE_ERROR,                EMM_OM_ERRLOG_CN_CAUSE_CONDITIONAL_IE_ERROR},
    {NAS_LMM_CAUSE_MSG_NOT_COMPATIBLE,                  EMM_OM_ERRLOG_CN_CAUSE_MSG_NOT_COMPATIBLE},
    {NAS_LMM_CAUSE_PROTOCOL_ERROR,                      EMM_OM_ERRLOG_CN_CAUSE_PROTOCOL_ERROR},
};

static VOS_UINT32   g_astEmmErrlogCnCauseNum
        = sizeof(g_astEmmErrlogCnCauseMap)/sizeof(NAS_LMM_CN_CAUSE_TRANS_STRU);
#endif


static NAS_EMM_PROTOCOL_STATE_MAP_STRU g_astProtocolStateMap[] =
{
    /* ��״̬ */
    { EMM_MS_NULL               ,     MM_SS_BUTT,      \
      APP_EMM_MS_NULL           ,     APP_EMM_SS_NULL                       },

    /* ȥע��״̬ */
    { EMM_MS_DEREG              ,     EMM_SS_DEREG_NORMAL_SERVICE,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_NORMAL_SERVICE       },

    { EMM_MS_DEREG              ,     EMM_SS_DEREG_LIMITED_SERVICE,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_LIMITED_SERVICE      },

    { EMM_MS_DEREG              ,     EMM_SS_DEREG_ATTEMPTING_TO_ATTACH,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_ATTEMPT_TO_ATTACH    },

    { EMM_MS_DEREG              ,     EMM_SS_DEREG_PLMN_SEARCH,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_PLMN_SEARCH          },

    { EMM_MS_DEREG              ,     EMM_SS_DEREG_NO_IMSI,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_NO_IMSI              },

    { EMM_MS_DEREG              ,     EMM_SS_DEREG_ATTACH_NEEDED,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_ATTACH_NEEDED        },

    { EMM_MS_DEREG              ,     EMM_SS_DEREG_NO_CELL_AVAILABLE,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_NO_CELL_AVAILABLE    },



    /* ע��״̬ */
    { EMM_MS_REG                ,     EMM_SS_REG_NORMAL_SERVICE,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_NORMAL_SERVICE         },

    { EMM_MS_REG                ,     EMM_SS_REG_ATTEMPTING_TO_UPDATE,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_ATTEMPTING_TO_UPDATE   },

    { EMM_MS_REG                ,     EMM_SS_REG_LIMITED_SERVICE,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_LIMITED_SERVICE        },

    { EMM_MS_REG                ,     EMM_SS_REG_PLMN_SEARCH,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_PLMN_SEARCH            },

    { EMM_MS_REG                ,     EMM_SS_REG_WAIT_ACCESS_GRANT_IND,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_WAIT_ACCESS_GRANT_IND},

    { EMM_MS_REG                ,     EMM_SS_REG_NO_CELL_AVAILABLE,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_NO_CELL_AVAILABLE      },

    { EMM_MS_REG                ,     EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_ATTEMPT_TO_UPDATE_MM      },

    { EMM_MS_REG                ,     EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_IMSI_DETACH_WAIT_CN_DETACH_CNF      },



    /* ע������� */
    { EMM_MS_REG_INIT           ,     MM_SS_BUTT,      \
      APP_EMM_MS_REG_INIT       ,     APP_EMM_SS_NULL                       },

    /* TAU������  */
    { EMM_MS_TAU_INIT           ,     MM_SS_BUTT,      \
      APP_EMM_MS_TAU_INIT       ,     APP_EMM_SS_NULL                       },

    /* SERVICE������ */
    { EMM_MS_SER_INIT           ,     MM_SS_BUTT,      \
      APP_EMM_MS_SER_INIT       ,     APP_EMM_SS_NULL                       },

    /* ȥע������� */
    { EMM_MS_DEREG_INIT         ,     MM_SS_BUTT,      \
      APP_EMM_MS_DEREG_INIT     ,     APP_EMM_SS_NULL                       }
};

static VOS_UINT32   g_ulProtocolStateMapNum
        = sizeof(g_astProtocolStateMap)/sizeof(NAS_EMM_PROTOCOL_STATE_MAP_STRU);

static  NAS_LMM_OM_ACT_STRU  g_astOmDataMap[] =
{
    /* APP_MM_MSG_TYPE_ENUM_UINT32      NAS_LMM_OM_ACTION_FUN */

    #if 0
    {ID_APP_MM_SET_PH_RA_MODE_REQ,      NAS_LMM_PubmDaSetRaMode},
    {ID_APP_MM_INQ_PH_RA_MODE_REQ,      NAS_LMM_PubmDaInqRaMode},
    #endif

    #if 0
    {ID_APP_MM_SET_MS_NET_CAP_REQ,      NAS_LMM_PubmDaSetMsNetCap},
    {ID_APP_MM_INQ_MS_NET_CAP_REQ,      NAS_LMM_PubmDaInqMsNetCap},
    #endif


    {ID_APP_MM_INQ_LTE_CS_REQ,         NAS_LMM_PubmDaInqLteCs},

    {ID_APP_MM_INQ_UE_MODE_REQ,         NAS_LMM_PubmDaInqUeMode},

    /* niuxiufan DT begin */
    {ID_APP_MM_INQ_LTE_GUTI_REQ,         NAS_LMM_PubmDaInqGuti},
    {ID_APP_MM_INQ_IMSI_REQ,             NAS_LMM_PubmDaInqImsi},
    {ID_APP_MM_INQ_EMM_STATE_REQ,        NAS_LMM_PubmDaInqEmmState},
    /* niuxiufan DT end */
};

static VOS_UINT32   g_astOmDataMapNum
        = sizeof(g_astOmDataMap)/sizeof(NAS_LMM_OM_ACT_STRU);


NAS_LMM_OM_MSG_ID_CHANGE_STRU g_stMmOmMsgIdStru[] =
{
    {0,NAS_EMM_CN_MT_ATTACH_ACP,    NAS_EMM_ATTACH_ACP,     EMM_OMT_KE_ATTACH_ACP},
    {0,NAS_EMM_CN_MT_ATTACH_REJ,    NAS_EMM_ATTACH_REJ,     EMM_OMT_KE_ATTACH_REJ},
    {0,NAS_EMM_CN_MT_DETACH_REQ_MT, NAS_EMM_DETACH_REQ_MT,  EMM_OMT_KE_DETACH_REQ_MT},
    {0,NAS_EMM_CN_MT_DETACH_ACP_MO, NAS_EMM_DETACH_ACP_MO,  EMM_OMT_KE_DETACH_ACP_MO},
    {0,NAS_EMM_CN_MT_TAU_ACP,       NAS_EMM_TAU_ACP,        EMM_OMT_KE_TAU_ACP},
    {0,NAS_EMM_CN_MT_TAU_REJ,       NAS_EMM_TAU_REJ,        EMM_OMT_KE_TAU_REJ},
    {0,NAS_EMM_CN_MT_SER_REJ,       NAS_EMM_SER_REJ,        EMM_OMT_KE_SER_REJ},
    {0,NAS_EMM_CN_MT_GUTI_CMD,      NAS_EMM_GUTI_CMD,       EMM_OMT_KE_GUTI_CMD},
    {0,NAS_EMM_CN_MT_AUTH_REQ,      NAS_EMM_AUTH_REQ,       EMM_OMT_KE_AUTH_REQ},
    {0,NAS_EMM_CN_MT_AUTH_RSP,      NAS_EMM_AUTH_RSP,       EMM_OMT_KE_AUTH_RSP},
    {0,NAS_EMM_CN_MT_AUTH_REJ,      NAS_EMM_AUTH_REJ,       EMM_OMT_KE_AUTH_REJ},
    {0,NAS_EMM_CN_MT_IDEN_REQ,      NAS_EMM_IDEN_REQ,       EMM_OMT_KE_IDEN_REQ},
    {0,NAS_EMM_CN_MT_SMC_CMD,       NAS_EMM_SECU_CMD,       EMM_OMT_KE_SECU_CMD},
    {0,NAS_EMM_CN_MT_SMC_CMP,       NAS_EMM_SECU_CMP,       EMM_OMT_KE_SECU_CMP},
    {0,NAS_EMM_CN_MT_EMM_STATUS,    NAS_EMM_STATUS,         EMM_OMT_KE_EMM_STATUS},
    {0,NAS_EMM_CN_MT_EMM_INFO,      NAS_EMM_INFO,           EMM_OMT_KE_EMM_INFO},
    {0,NAS_EMM_CN_MT_DOWNLINK_NAS_TRANSPORT, NAS_EMM_DOWNLINK_NAS_TRANSPORT, EMM_OMT_KE_EMM_DOWNLINK_NAS_TRANSPORT},
    {0,NAS_EMM_CN_CS_SER_NOTIFICATION, NAS_EMM_CS_SER_NOTIFICATION, EMM_OMT_KE_CS_SER_NOTIFICATION}
};
VOS_UINT32 g_ulSzieof_g_stMmOmMsgIdStru = sizeof(g_stMmOmMsgIdStru);

/*niuxiufan DT begin */
APP_MM_DT_REPORT_CTRL_STRU  gastNasDtRptCtrlTbl[NAS_DT_RPT_CTRL_MAX_ITEM_NUM] = {{0}};
VOS_UINT32                  g_ulNasEmmOmMsgHookFlag = 0;
/*niuxiufan DT end */

VOS_UINT32                  g_NasEmmOmInfoIndFlag = 0;

/* xiongxianghui00253310 modify for ftmerrlog begin */
EMM_FTM_INFO_MANAGE_STRU             g_astEmmFtmInfoManage;
EMM_DATABASE_INFO_STRU               g_astEmmInfo;
/* xiongxianghui00253310 modify for ftmerrlog end   */

APP_MM_DT_STRU                    g_stEmmDtInfo;

/*****************************************************************************
  3 Function
*****************************************************************************/




NAS_LMM_OM_ACTION_FUN  NAS_LMM_OmFindFun( VOS_UINT32          ulMsgId)
{
    VOS_UINT32                          i;
    NAS_LMM_OM_ACTION_FUN                pActFun = NAS_LMM_NULL_PTR;

    /* ��g_astNvDataMap�в��Ҷ�Ӧ��NV TYPE*/
    for(i = 0; i < g_astOmDataMapNum; i++)
    {
        /* ��NV������ͬ,���ҵ���,���ص�ǰ��NV�����������˳�ѭ�� */
        if(ulMsgId == g_astOmDataMap[i].ulMsgId)
        {
            pActFun            = g_astOmDataMap[i].pfFun;
            break;
        }
    }

    return  pActFun;
}


NAS_LMM_OM_ACTION_FUN  NAS_LMM_OmCommFindFun
(
    const NAS_LMM_OM_ACT_STRU           *aucActMap,
    VOS_UINT32                          ulMapElementNum,
    VOS_UINT32                          ulMsgId
)
{
    VOS_UINT32                          i;
    NAS_LMM_OM_ACTION_FUN                pActFun = NAS_LMM_NULL_PTR;

    /* ��aucActMap�в��Ҷ�Ӧ�� ulMsgId */
    for(i = 0; i < ulMapElementNum; i++)
    {
        /* ��ulMsgId������ͬ,���ҵ���,���ص�ǰ��ulMsgId�����������˳�ѭ�� */
        if(ulMsgId == aucActMap[i].ulMsgId)
        {
            pActFun = aucActMap[i].pfFun;
            break;
        }
    }

    return  pActFun;
}

/*****************************************************************************
 Function Name   : NAS_LMM_OmMaintain
 Description     : OM����ά����Ϣ�����
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.  qilili00145085  2008-10-30  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_OmMaintain( MsgBlock            *pMsg)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSrcMsgId;
    NAS_EMM_GENERAL_MSG_HEADER_STRU    *pstSrcMsg;
    NAS_LMM_OM_ACTION_FUN                pActFun = NAS_LMM_NULL_PTR;


    ulRet                               = NAS_LMM_MSG_DISCARD;
    pstSrcMsg                           = (NAS_EMM_GENERAL_MSG_HEADER_STRU*)pMsg;
    ulSrcMsgId                          = pstSrcMsg->ulMsgId;


    pActFun = NAS_LMM_OmFindFun(ulSrcMsgId);
    if (NAS_LMM_NULL_PTR != pActFun)
    {   /* �������ҵ��ˣ���������ִ��APP������ */
        (*pActFun)(pMsg);
        ulRet = NAS_LMM_MSG_HANDLED;
    }
    else
    {
        /* ����Ҳ���������������ʾ��ǰû�иô������� */
/*        NAS_LMM_PUBM_LOG_INFO("in NAS_LMM_OmFindFun, Action functin is NOT FOUND. ");*/

        #if 0
        /*�������ͨ�����е�����������*/
        if( (ulSrcMsgId > (ID_APP_MM_CMD_SET_START)) &&
            (ulSrcMsgId < (ID_APP_MM_CMD_SET_END  )))
        {
            ulRet = NAS_LMM_PubmDaSet(pMsg, ulSrcMsgId);
        }

         /*�������ͨ�����еĲ�ѯ������*/
        if( (ulSrcMsgId > (ID_APP_MM_CMD_INQ_START)) &&
            (ulSrcMsgId < (ID_APP_MM_CMD_INQ_END  )))
        {
            ulRet = NAS_LMM_PubmDaInq(pMsg, ulSrcMsgId);
        }
        #endif
    }

    return  ulRet;

}
VOS_UINT32 NAS_EMM_OmInfoIndMsgProc( MsgBlock    *pMsg )
{
    OM_EMM_INFO_REPORT_REQ_STRU           *pMmOmInfoReqMsg;
    OM_EMM_INFO_REPORT_CNF_STRU           *pMmOmInfoCnfMsg;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_OmInfoIndMsgProc: enter !!");

    pMmOmInfoReqMsg = (OM_EMM_INFO_REPORT_REQ_STRU *)pMsg;

    if (OM_EMM_INFO_REPORT_OPEN == pMmOmInfoReqMsg->enRptCtrl)
    {
        g_NasEmmOmInfoIndFlag = OM_EMM_REPORT_INFO_OPEN;
    }
    else
    {
        g_NasEmmOmInfoIndFlag = OM_EMM_REPORT_INFO_CLOSE;

    }
    /* �������ϱ���Ϣ��ȫ�ֱ������ */
    NAS_LMM_MEM_SET(&g_stEmmOmInfo, 0, sizeof(OM_EMM_STATE_INFO_STRU));

    /* Ϊ��Ϣ�����ַ */
    pMmOmInfoCnfMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(OM_EMM_INFO_REPORT_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pMmOmInfoCnfMsg)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_OmInfoIndMsgProc: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        return NAS_LMM_MSG_HANDLED;
    }


    /* �ṹ��ʼ�� */
    NAS_LMM_MEM_SET(pMmOmInfoCnfMsg, 0, sizeof(OM_EMM_INFO_REPORT_CNF_STRU));


    /* �����Ϣͷ */
    pMmOmInfoCnfMsg->ulSenderCpuId = pMmOmInfoReqMsg->ulReceiverCpuId;
    pMmOmInfoCnfMsg->ulSenderPid     = pMmOmInfoReqMsg->ulReceiverPid;
    pMmOmInfoCnfMsg->ulReceiverPid   = pMmOmInfoReqMsg->ulSenderPid;
    pMmOmInfoCnfMsg->ulReceiverCpuId  = pMmOmInfoReqMsg->ulSenderCpuId;
    pMmOmInfoCnfMsg->ulLength = EMM_MSG_LENTH_NO_HEADER(OM_EMM_INFO_REPORT_CNF_STRU);
    pMmOmInfoCnfMsg->usOriginalId    = pMmOmInfoReqMsg->usTerminalId;
    pMmOmInfoCnfMsg->usTerminalId    = pMmOmInfoReqMsg->usOriginalId;
    pMmOmInfoCnfMsg->ulTimeStamp     = pMmOmInfoReqMsg->ulTimeStamp;
    pMmOmInfoCnfMsg->ulSN            = pMmOmInfoReqMsg->ulSN;


    /*����OPID*/
    pMmOmInfoCnfMsg->ulOpId      = pMmOmInfoReqMsg->ulOpId;

    /*������Ϣ����*/
    pMmOmInfoCnfMsg->ulMsgId     = ID_OM_EMM_INFO_REPORT_CNF;

    pMmOmInfoCnfMsg->ulRslt      = APP_SUCCESS;

    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pMmOmInfoCnfMsg);

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_LMM_CompareEmmInfo( VOS_VOID )
{
    VOS_UINT32                          ulRst = NAS_EMM_SUCC;
    EMM_MAIN_STATE_ENUM_UINT16      ulProtoclMainState;
    EMM_SUB_STATE_ENUM_UINT16       ulProtoclSubState;
    EMM_UPDATE_STATE_ENUM_UINT32    enEmmUpState;

    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_CompareEmmInfo: enter !!");

    /* ��EMM��ǰ״̬��ȡЭ��״̬ */
    NAS_LMM_PubmGetEmmState(&ulProtoclMainState,
                            &ulProtoclSubState,
                            NAS_LMM_GetEmmCurFsmMS(),
                            NAS_LMM_GetEmmCurFsmSS());
    /* ��ȡEUֵ */
    NAS_LMM_PubmGetEmmUpdateState(&enEmmUpState);

    if ((ulProtoclMainState != g_stEmmOmInfo.enMainState)
        || (ulProtoclSubState != g_stEmmOmInfo.enSubState))
    {
        g_stEmmOmInfo.enMainState = ulProtoclMainState;
        g_stEmmOmInfo.enSubState = ulProtoclSubState;
        ulRst = NAS_EMM_FAIL;
    }



    if (enEmmUpState != g_stEmmOmInfo.enEmmUpState)
    {
        g_stEmmOmInfo.enEmmUpState = enEmmUpState;
        ulRst = NAS_EMM_FAIL;
    }

    /* �Ƚ�GUTI��Ϣ */
    if (NAS_LMM_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(&g_stEmmOmInfo.stGuti,
                                                    NAS_LMM_GetEmmInfoUeidGutiAddr(),
                                                    sizeof(NAS_MM_GUTI_STRU)))
    {
        NAS_LMM_MEM_CPY(&g_stEmmOmInfo.stGuti,
                        NAS_LMM_GetEmmInfoUeidGutiAddr(),
                        sizeof(NAS_MM_GUTI_STRU));
        ulRst = NAS_EMM_FAIL;
    }

    /* �Ƚϼ��ܺ������Ա����㷨 */
    if ((NAS_EMM_GetSecuEca() != g_stEmmOmInfo.enAlgSecurity)
        || (NAS_EMM_GetSecuEia() != g_stEmmOmInfo.enAlgIntegrity))
    {
        g_stEmmOmInfo.enAlgSecurity = NAS_EMM_GetSecuEca();
        g_stEmmOmInfo.enAlgIntegrity = NAS_EMM_GetSecuEia();
        ulRst = NAS_EMM_FAIL;
    }

    /* �Ƚ�UE����ģʽ */
    if (NAS_LMM_GetEmmInfoUeOperationMode() != g_stEmmOmInfo.enLteUeMode)
    {
        g_stEmmOmInfo.enLteUeMode = NAS_LMM_GetEmmInfoUeOperationMode();
        ulRst = NAS_EMM_FAIL;
    }

    return ulRst;
}
VOS_UINT32 NAS_LMM_DtCompareGuti(VOS_VOID)
{
    NAS_MM_GUTI_STRU                  *pstEmmCurGuti;
    VOS_UINT32                          ulRst = NAS_EMM_SUCC;
    pstEmmCurGuti                       = NAS_LMM_GetEmmInfoUeidGutiAddr();

    if(NAS_LMM_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(&g_stEmmDtInfo.stGuti,pstEmmCurGuti,
                                                 sizeof(NAS_MM_GUTI_STRU)))
    {
       ulRst = NAS_EMM_FAIL;
    }

    return ulRst;

}


VOS_UINT32 NAS_LMM_DtCompareImsi(VOS_VOID)
{
    VOS_UINT32                          ulRst = NAS_EMM_SUCC;
    NAS_OM_IMSI_INFO_STRU              stImsiInfo;
    VOS_UINT8                          ucIndex;

    PS_MEM_SET(&stImsiInfo, 0, sizeof(NAS_OM_IMSI_INFO_STRU));

    /*�����ǰ�޿�,��OM�ظ���ѯIMSIΪ��*/
    if (NAS_LMM_SIM_STATUS_AVAILABLE == NAS_LMM_GetSimState())
    {

        /* ��ȡIMSI */
        stImsiInfo.ucImsiLen = (VOS_UINT8)((g_stEmmInfo.stMmUeId.aucImsi[0])*2 - 1);

        /*���һ���ֽ����4λΪF,�����IMSIΪż���� */
        if (0xF0 == (g_stEmmInfo.stMmUeId.aucImsi[g_stEmmInfo.stMmUeId.aucImsi[0]] & 0xF0))
        {
            stImsiInfo.ucImsiLen -= 1;
        }

        for(ucIndex= 0; ucIndex< stImsiInfo.ucImsiLen; ucIndex++)
        {
            if (0 == (ucIndex+1)%2)
            {
                stImsiInfo.ucImsi[ucIndex] = 0x0F & (g_stEmmInfo.stMmUeId.aucImsi[(ucIndex+1)/2 + 1]);
            }
            else
            {
                stImsiInfo.ucImsi[ucIndex] = 0x0F & (g_stEmmInfo.stMmUeId.aucImsi[(ucIndex+1)/2 + 1] >> 4);
            }
        }
    }


    if(NAS_LMM_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(&g_stEmmDtInfo.stImsi,&stImsiInfo,
                                                 sizeof(NAS_OM_IMSI_INFO_STRU)))
    {
       ulRst = NAS_EMM_FAIL;
    }

    return ulRst;

}
VOS_UINT32 NAS_LMM_DtCompareEmmState(VOS_VOID)
{
    VOS_UINT32                          ulRst = NAS_EMM_SUCC;
    EMM_MAIN_STATE_ENUM_UINT16      ulProtoclMainState;
    EMM_SUB_STATE_ENUM_UINT16       ulProtoclSubState;
    VOS_UINT16                           usStaTId;           /* ��ʱ����Ϣ*/

    /* ��EMM��ǰ״̬��ȡЭ��״̬ */
    NAS_LMM_PubmGetEmmState(&ulProtoclMainState,
                            &ulProtoclSubState,
                            NAS_LMM_GetEmmCurFsmMS(),
                            NAS_LMM_GetEmmCurFsmSS());
    /* ��ȡ��ʱ����Ϣ */
    usStaTId = (VOS_UINT16)NAS_LMM_GetEmmCurTimer();

    if ((ulProtoclMainState != g_stEmmDtInfo.stEmmState.enMainState)
        || (ulProtoclSubState != g_stEmmDtInfo.stEmmState.enSubState)
        || (usStaTId != g_stEmmDtInfo.stEmmState.usStaTId))
    {
        ulRst = NAS_EMM_FAIL;
    }

    return ulRst;

}
VOS_VOID NAS_LMM_DtJudgeifNeedRpt(VOS_VOID)
{

    /*�ж��Ƿ���Ҫ�ϱ�GUTI*/
    if (NAS_DT_RPT_START== NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_GUTI)->enRptStatus)
    {
        if(NAS_EMM_FAIL == NAS_LMM_DtCompareGuti())
        {
        #if (VOS_WIN32 != VOS_OS_VER)
           /*�ϱ�GUTI��Ϣ*/
           NAS_LMM_PubmIndGuti();
        #endif

        }
    }
     /*�ж��Ƿ���Ҫ�ϱ�IMSI*/
    if (NAS_DT_RPT_START== NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_IMSI)->enRptStatus)
    {
        if(NAS_EMM_FAIL == NAS_LMM_DtCompareImsi())
        {
        #if (VOS_WIN32 != VOS_OS_VER)
           /*�ϱ�Imsi��Ϣ*/
           NAS_LMM_PubmIndImsi();
        #endif

        }
    }

    /* �ж��Ƿ���Ҫ�ϱ�EMM״̬*/
    if(NAS_DT_RPT_START== NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_EMM_STATE)->enRptStatus)
    {
        if(NAS_EMM_FAIL == NAS_LMM_DtCompareEmmState())
        {
        #if(VOS_WIN32 != VOS_OS_VER)
           /*�ϱ�EMM״̬*/
           NAS_LMM_PubmIndEmmState();
        #endif
        }
    }
    return;
}



VOS_VOID  NAS_LMM_SetAppParaValue
(
    NAS_LMM_APP_PARA_SET_RESLT_STRU      *pstParaInfo,
    const NAS_LMM_APP_PARA_SET_HEAD_STRU       *pstAppMsg
)
{
    pstParaInfo->ulOpId                 = pstAppMsg->ulOpId;

    /*����MID����*/
    pstParaInfo->usOriginalId = pstAppMsg->usOriginalId;
    pstParaInfo->usTerminalId = pstAppMsg->usTerminalId;
    pstParaInfo->ulTimeStamp  = pstAppMsg->ulTimeStamp;

    /*����SN����*/
    pstParaInfo->ulSN = pstAppMsg->ulSN;
    return;
}


VOS_VOID NAS_EMM_SendIntraTauReq
(
    APP_MM_MSG_TYPE_ENUM_UINT32         ulOmMmMsgType,
    NAS_LMM_INTRA_TAU_TYPE_ENUM_UINT32  enIntraTauType
)
{
    VOS_UINT32                          ulMsgLenthNoHeader;
    NAS_LMM_INTRA_TAU_REQ_STRU           *pEmmIntraTauReq;
/*    VOS_UINT32                          ulRst;*/

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_SendIntraTauReq is entered");

     /* ����EMMҪ����OM����Ϣ����, ������VOSͷ */
    ulMsgLenthNoHeader = EMM_MSG_LENTH_NO_HEADER(NAS_LMM_INTRA_TAU_REQ_STRU);

    /* ����DOPRA��Ϣ */
    /*lint -e433 -e826*/
    pEmmIntraTauReq = (VOS_VOID *)NAS_LMM_GetSendIntraMsgBuffAddr(ulMsgLenthNoHeader);
    /*lint +e433 +e826*/

    if(NAS_LMM_NULL_PTR  == pEmmIntraTauReq)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_SendIntraTauReq: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        return;
    }

    /* �����Ϣͷ */
    NAS_EMM_COMP_INTRA_MSG_HEADER(      pEmmIntraTauReq,
                                        ulMsgLenthNoHeader);


    /* ��д��ϢID */
    pEmmIntraTauReq->ulMsgId            = ID_NAS_LMM_INTRA_TAU_REQ;

    pEmmIntraTauReq->ulOmMsgType        = ulOmMmMsgType;

    pEmmIntraTauReq->enIntraTauType     = enIntraTauType;

    /* ������Ϣ */
    /*
    ulRst = NAS_LMM_SendIntraMsg(        pEmmIntraTauReq);
    if(NAS_EMM_SUCC != ulRst)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_SendIntraTauReq: SendIntraMsg ERR !!");
    }
    */
    NAS_EMM_SEND_INTRA_MSG(             pEmmIntraTauReq);

    return;

}

#if 0
/*****************************************************************************
 Function Name  : NAS_LMM_MtTpSetOptNetCap
 Discription    : ͸�������·�
 Input          : pMsg
 Output         : None
 Return         : None
 History:
      1.  qilili00145085  2008-10-30  Draft Enact
*****************************************************************************/
VOS_VOID    NAS_LMM_MtTpSetOptMsNetCap(    MsgBlock    *pMsg)
{
    (VOS_VOID)(pMsg);
#if 0
    OMT_EMM_TP_OPT_MS_NET_CAP_REQ_STRU    *pEmmTpOptNetCap;
    OMT_MM_TP_CMD_CNF_STRU    *pEmmTpOptNetCapCnf;

    VOS_UINT32                          ulMsgLenthNoHeader;

    pEmmTpOptNetCap                     = (OMT_EMM_TP_OPT_MS_NET_CAP_REQ_STRU *)pMsg;

    /* ����EMMҪ����OM����Ϣ����, ������VOSͷ */
    ulMsgLenthNoHeader = EMM_MSG_LENTH_NO_HEADER(OMT_MM_TP_CMD_CNF_STRU);

    /* ����DOPRA��Ϣ */
    pEmmTpOptNetCapCnf = (OMT_MM_TP_CMD_CNF_STRU *)NAS_LMM_ALLOC_MSG(ulMsgLenthNoHeader);
    if(NAS_LMM_NULL_PTR  == pEmmTpOptNetCapCnf)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_MtTpSetOptMsNetCap: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        return;
    }

    /* �����Ϣͷ */
    EMM_COMP_APP_MSG_VOS_HEADER(            pEmmTpOptNetCapCnf,
                                        ulMsgLenthNoHeader);

    /*���APP��Ϣͷ*/
    EMM_COMP_MM_APP_MSG_HEADER(     pEmmTpOptNetCapCnf,
                                        pEmmTpOptNetCap);

    /* ��д��ϢID */
    EMM_COMP_OMT_TP_CNF_MSGID(          pEmmTpOptNetCapCnf,
                                        ID_APP_MM_TRANSPARENT_CMD_CNF);


    /* ��д͸����������� */
    pEmmTpOptNetCapCnf->ucMmTpCmdType = NAS_EMM_TP_SET_MS_NET_CAP_REQ;

     /* ���õĲ�����ԭ������ͬ */
    if(0 == NAS_LMM_MEM_CMP(             &(pEmmTpOptNetCap->stMmNetCap),
                                        &(NAS_LMM_PUBM_GLOBAL.stMsNetCap),
                                        NAS_EMM_MS_NET_CAP_MAX_SIZE))
    {
        /* ͸������ִ�гɹ� */
        pEmmTpOptNetCapCnf->ucMmTpCmdRst
                                        = NAS_EMM_OMT_MAINTAIN_RST_SUCC;
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_MtTpSetOptNetCap: Parameter, stMsNetCap, same as before !!");
    }
    else
    {
        NAS_LMM_MEM_CPY(                 &(NAS_LMM_PUBM_GLOBAL.stMsNetCap),
                                        &(pEmmTpOptNetCap->stMmNetCap),
                                        sizeof(NAS_EMM_MS_NET_CAP_STRU));

        /* ͸������ִ�гɹ� */
        pEmmTpOptNetCapCnf->ucMmTpCmdRst
                                        = NAS_EMM_OMT_MAINTAIN_RST_SUCC;
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_MtTpSetOptNetCap: pEmmTpOptNetCapCnf is set succ.");
    }

    /* ������Ϣ */
    NAS_LMM_SendOuterMsg(pEmmTpOptNetCapCnf);
#endif
    return;
}
#endif

#if 0

VOS_UINT32  NAS_LMM_PubmSetEplmn(APP_MM_SET_PLMN_REQ_STRU *pstSetPlmnReq)
{
    LNAS_LMM_NV_EPLMN_LIST_STRU         stNvEplmnList;
    VOS_VOID                            *pData;
    VOS_UINT16                          usDataLen;
    VOS_UINT32                          ulRslt;
    NAS_LMM_NETWORK_INFO_STRU            *pstNetInfo;

    pstNetInfo                          = NAS_LMM_GetEmmInfoNetInfoAddr();

     /*��� NV PLMN �ṹ*/
    NAS_LMM_MEM_SET(&stNvEplmnList, 0, sizeof(LNAS_LMM_NV_EPLMN_LIST_STRU));

    if (APP_MM_SET_TYPE_SETTING == pstSetPlmnReq->enSetType)
    {
        if (NAS_LMM_MAX_EQU_PLMN_NUM < pstSetPlmnReq->stPlmnList.ulPlmnNum)
        {
            NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PubmSetEplmn: set plmn num is 16 ");
            pstSetPlmnReq->stPlmnList.ulPlmnNum = NAS_LMM_MAX_EQU_PLMN_NUM;
        }
        stNvEplmnList.bitOpNvPlmn       = NAS_EMM_BIT_SLCT;
        stNvEplmnList.stPlmnList.ulPlmnNum = pstSetPlmnReq->stPlmnList.ulPlmnNum;
        NAS_LMM_MEM_CPY(                 (stNvEplmnList.stPlmnList.astPlmnId),
                                        (pstSetPlmnReq->stPlmnList.astPlmnId),
                                        sizeof(APP_PLMN_ID_STRU) * pstSetPlmnReq->stPlmnList.ulPlmnNum);

        /*����ȫ�ֱ���*/
        pstNetInfo->bitOpEPlmnList      = NAS_EMM_BIT_SLCT;
        pstNetInfo->stEPlmnList.ulPlmnNum = pstSetPlmnReq->stPlmnList.ulPlmnNum;
        NAS_LMM_MEM_CPY(                 (pstNetInfo->stEPlmnList.astPlmnId),
                                        (pstSetPlmnReq->stPlmnList.astPlmnId),
                                        sizeof(APP_PLMN_ID_STRU) * pstSetPlmnReq->stPlmnList.ulPlmnNum);

    }
    else if (APP_MM_SET_TYPE_DELETE == pstSetPlmnReq->enSetType)
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PubmSetEplmn: Delete Eplmn ");

        /*��������ΪDELETE*/
        stNvEplmnList.bitOpNvPlmn       = NAS_EMM_BIT_NO_SLCT;
        NAS_LMM_MEM_SET(                 &stNvEplmnList.stPlmnList,
                                        0,
                                        sizeof(stNvEplmnList.stPlmnList));

        /*����ȫ�ֱ���*/
        pstNetInfo->bitOpEPlmnList      = NAS_EMM_BIT_NO_SLCT;
        NAS_LMM_MEM_SET(                 &(pstNetInfo->stEPlmnList),
                                        0,
                                        sizeof(pstNetInfo->stEPlmnList));
    }
    else
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_PubmSetEplmn: set type is err !");
        ulRslt = NAS_LMM_NVIM_FAIL;
        return ulRslt;
    }

    /*д�� NVIM*/
    pData                           = &(stNvEplmnList);
    usDataLen                       = sizeof(LNAS_LMM_NV_EPLMN_LIST_STRU);

    ulRslt = NAS_LMM_NvimWrite(EN_NV_ID_EQUIVALENTPLMN, pData, usDataLen);

    return ulRslt;
}
#endif

#if 0
VOS_VOID    NAS_LMM_PubmDaSetRaMode(       MsgBlock    *pMsg )
{
    APP_MM_SET_PH_RA_MODE_REQ_STRU     *pstEmmSetRaModeReq;
    LNAS_LMM_NV_RAMOD_STRU              stNvRaMod;
    VOS_VOID                            *pData;
    VOS_UINT16                          usDataLen;
    VOS_UINT32                          ulRslt;
    NAS_LMM_APP_PARA_SET_RESLT_STRU      stAppParaInfo;

    /* ����ת�� */
    pstEmmSetRaModeReq                  =  (VOS_VOID *)pMsg;

    /*���ûظ���Ϣ�Ĳ�������*/
    stAppParaInfo.ulMsgId   = ID_APP_MM_SET_PH_RA_MODE_CNF;
    NAS_LMM_SetAppParaValue(&stAppParaInfo,(NAS_LMM_APP_PARA_SET_HEAD_STRU *)pstEmmSetRaModeReq);

    /*��� NV RaMod �ṹ*/
    NAS_LMM_MEM_SET(&stNvRaMod, 0, sizeof(LNAS_LMM_NV_RAMOD_STRU));

    if (APP_MM_SET_TYPE_SETTING == pstEmmSetRaModeReq->enSetType)
    {
        if (APP_PH_RAT_LTE_TDD < pstEmmSetRaModeReq->enAccessMode)
        {
            NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PubmDaSetRaMode:Input value is Invalid!");
            stAppParaInfo.ulRslt            = APP_FAILURE;

            /*�ظ�CNF��Ϣ*/
            NAS_LMM_PubmDaSendSetCnf(&stAppParaInfo);
            return;
        }

        stNvRaMod.bitOpRaMod            = NAS_EMM_BIT_SLCT;
        stNvRaMod.enRaMod               = pstEmmSetRaModeReq->enAccessMode;

        /* ���±��ز��� */
        g_stEmmInfo.bitOpRaMod          = NAS_EMM_BIT_SLCT;
        g_stEmmInfo.enRaMod             = pstEmmSetRaModeReq->enAccessMode;
    }
    else
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_PubmDaSetRaMode:No suppor delete or  set type is err !");
        stAppParaInfo.ulRslt            = APP_FAILURE;

        /*�ظ�CNF��Ϣ*/
        NAS_LMM_PubmDaSendSetCnf(&stAppParaInfo);
        return;
    }

    /*д�� NVIM*/
    pData                               = &(stNvRaMod);
    usDataLen                           = sizeof(LNAS_LMM_NV_RAMOD_STRU);
    ulRslt = NAS_LMM_NvimWrite(EN_NV_ID_UE_RAMOD, pData, usDataLen);

     /*�ظ� CNF ��Ϣ*/
    if (NAS_LMM_NVIM_OK == ulRslt)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PubmDaSetRaMode: SUCC");
        stAppParaInfo.ulRslt            = APP_SUCCESS;

    }
    else
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_PubmDaSetRaMode: FAIL");
        stAppParaInfo.ulRslt            = APP_FAILURE;
    }

    /*�ظ�CNF��Ϣ*/
    NAS_LMM_PubmDaSendSetCnf(&stAppParaInfo);
    return;
}
#endif

#if 0
VOS_VOID NAS_LMM_PubmDaSetMsNetCap(    MsgBlock    *pMsg)
{
    APP_MM_SET_MS_NET_CAP_REQ_STRU     *pstEmmSetMsNetCapReq;
    LNAS_LMM_NV_MS_NET_CAP_STRU         stNvMsNetCap;
    VOS_VOID                            *pData;
    VOS_UINT16                          usDataLen;
    VOS_UINT32                          ulRslt;
    NAS_LMM_APP_PARA_SET_RESLT_STRU      stAppParaInfo;

    /* ����ת�� */
    pstEmmSetMsNetCapReq                =  (VOS_VOID *)pMsg;

    /*���ûظ���Ϣ�Ĳ�������*/
    stAppParaInfo.ulMsgId   = ID_APP_MM_SET_MS_NET_CAP_CNF;
    NAS_LMM_SetAppParaValue(&stAppParaInfo,(NAS_LMM_APP_PARA_SET_HEAD_STRU *)pstEmmSetMsNetCapReq);

    /*��� NV HPLMN �ṹ*/
    NAS_LMM_MEM_SET(&stNvMsNetCap, 0, sizeof(LNAS_LMM_NV_MS_NET_CAP_STRU));

    if (APP_MM_SET_TYPE_SETTING == pstEmmSetMsNetCapReq->enSetType)
    {
        stNvMsNetCap.bitOpMsNetCap      = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY(                 &(stNvMsNetCap.stMsNetCap),
                                        &(pstEmmSetMsNetCapReq->stMsNetCap),
                                        sizeof(APP_MS_NET_CAP_STRU));
    }
    else if (APP_MM_SET_TYPE_DELETE == pstEmmSetMsNetCapReq->enSetType)
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PubmDaSetMsNetCap:Delete Ms Net Cap");
        stNvMsNetCap.bitOpMsNetCap      = NAS_EMM_BIT_NO_SLCT;
        NAS_LMM_GetEmmInfoAddr()->bitOpMsNetCap       = NAS_EMM_BIT_NO_SLCT;
        NAS_LMM_MEM_SET(                 &(stNvMsNetCap.stMsNetCap),
                                        0,
                                        sizeof(APP_MS_NET_CAP_STRU));
    }
    else
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_PubmDaSetMsNetCap: set type is err !");
        stAppParaInfo.ulRslt            = APP_FAILURE;

        /*�ظ�CNF��Ϣ*/
        NAS_LMM_PubmDaSendSetCnf(&stAppParaInfo);
        return;
    }

    /*д�� NVIM*/
    pData                               = (VOS_VOID *)&(stNvMsNetCap);
    usDataLen                           = sizeof(LNAS_LMM_NV_MS_NET_CAP_STRU);
    ulRslt = NAS_LMM_NvimWrite(EN_NV_ID_MS_NET_CAPABILITY, pData, usDataLen);

    /*�ظ� CNF ��Ϣ*/
    if (NAS_LMM_NVIM_OK == ulRslt)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PubmDaSetMsNetCap: SUCC");
        stAppParaInfo.ulRslt            = APP_SUCCESS;
    }
    else
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_PubmDaSetMsNetCap: FAIL");
        stAppParaInfo.ulRslt            = APP_FAILURE;
    }

    /*�ظ�CNF��Ϣ*/
    NAS_LMM_PubmDaSendSetCnf(&stAppParaInfo);

    return;
}
#endif

#if 0
VOS_VOID    NAS_LMM_PubmDaInqRaMode(     MsgBlock    *pMsg )
{
    APP_MM_INQ_PH_RA_MODE_REQ_STRU     *pstEmmInqRaModReq;
    APP_MM_INQ_PH_RA_MODE_CNF_STRU     *pstEmmInqRaModCnf;
    LNAS_LMM_NV_RAMOD_STRU              stNvRaMod;
    VOS_VOID                           *pData;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usDataLen;

    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PubmDaInqRaMode enter !!");
    pstEmmInqRaModReq                  = (VOS_VOID *)pMsg;

    /* ����DOPRA��Ϣ */
    pstEmmInqRaModCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_PH_RA_MODE_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstEmmInqRaModCnf)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqRaMode: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        return;
    }

    NAS_LMM_MEM_SET(pstEmmInqRaModCnf, 0, sizeof(APP_MM_INQ_PH_RA_MODE_CNF_STRU));

    /* �����Ϣͷ */
    EMM_COMP_APP_MSG_VOS_HEADER(pstEmmInqRaModCnf,
                                EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_PH_RA_MODE_CNF_STRU),
                                pstEmmInqRaModReq);

    pstEmmInqRaModCnf->ulMsgId          = ID_APP_MM_INQ_PH_RA_MODE_CNF;
    pstEmmInqRaModCnf->ulOpId           = pstEmmInqRaModReq->ulOpId;

    /*read HPLMN from NVIM*/
    pData = (VOS_VOID *)&(stNvRaMod);
    usDataLen = sizeof(LNAS_LMM_NV_RAMOD_STRU);
    ulRslt = NAS_LMM_NvimRead(EN_NV_ID_UE_RAMOD, pData, &usDataLen);

    if((ulRslt == EN_NV_OK) && (NAS_EMM_BIT_SLCT == stNvRaMod.bitOpRaMod))
    {   /* ��ȡ�ɹ� */
        pstEmmInqRaModCnf->enAccessMode = stNvRaMod.enRaMod;
    }
    else
    {   /* ��ȡʧ�� */
        pstEmmInqRaModCnf->enAccessMode = APP_PH_RAT_TYPE_BUTT;
    }

    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pstEmmInqRaModCnf);

    return;
}
#endif
#if 0

VOS_VOID    NAS_LMM_PubmDaInqMsNetCap(     MsgBlock    *pMsg )
{
    APP_MM_INQ_MS_NET_CAP_REQ_STRU     *pstAppInqMsetCapReq;
    APP_MM_INQ_MS_NET_CAP_CNF_STRU     *pstAppInqMsNetCapCnf;
    LNAS_LMM_NV_MS_NET_CAP_STRU         stNvMsNetCap;
    VOS_VOID                           *pData;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usDataLen;


    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_PubmDaInqMsNetCap: enter!!");
    pstAppInqMsetCapReq                = (VOS_VOID *)pMsg;

    /* ����DOPRA��Ϣ */
    pstAppInqMsNetCapCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_MS_NET_CAP_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppInqMsNetCapCnf)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqMsNetCap: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        return;
    }

    NAS_LMM_MEM_SET(pstAppInqMsNetCapCnf, 0, sizeof(APP_MM_INQ_MS_NET_CAP_CNF_STRU));

    /* �����Ϣͷ */
    EMM_COMP_APP_MSG_VOS_HEADER(pstAppInqMsNetCapCnf,
                                EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_MS_NET_CAP_CNF_STRU),
                                pstAppInqMsetCapReq);

    pstAppInqMsNetCapCnf->ulMsgId       = ID_APP_MM_INQ_MS_NET_CAP_CNF;
    pstAppInqMsNetCapCnf->ulOpId        = pstAppInqMsetCapReq->ulOpId;

    /*read UE NET CAP from NVIM*/
    pData = (VOS_VOID *)&(stNvMsNetCap);
    usDataLen = sizeof(LNAS_LMM_NV_MS_NET_CAP_STRU);

    ulRslt = NAS_LMM_NvimRead(EN_NV_ID_MS_NET_CAPABILITY, pData, &usDataLen);
    if((EN_NV_OK == ulRslt) && (NAS_EMM_BIT_SLCT == stNvMsNetCap.bitOpMsNetCap))
    {   /* ��ȡ�ɹ� */
        NAS_LMM_MEM_CPY(&(pstAppInqMsNetCapCnf->stMsNetCap),
                        &(stNvMsNetCap.stMsNetCap),
                        sizeof(APP_MS_NET_CAP_STRU));
    }
    else
    {   /* ��ȡʧ�� */
        NAS_LMM_MEM_SET(&(pstAppInqMsNetCapCnf->stMsNetCap),
                         0,
                         sizeof(APP_MS_NET_CAP_STRU));
    }

    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pstAppInqMsNetCapCnf);

    return;
}
#endif

/* lihong00150010 ims begin */

VOS_VOID  NAS_LMM_ReadImsaNvImsCapability( VOS_UINT8 *pucSmsOverIms, VOS_UINT8 *pucSrvcc)
{
    IMS_NV_IMS_CAP_STRU             stNvImsCapability;
    VOS_UINT32                      ulRslt;
    /*lint -e718*/
    /*lint -e732*/
    /*lint -e516*/
    ulRslt = LPs_NvimItem_Read(EN_NV_ID_IMS_CAPABILITY,&stNvImsCapability,\
                 sizeof(IMS_NV_IMS_CAP_STRU));
    /*lint +e516*/
    /*lint +e732*/
    /*lint +e718*/

    if(ulRslt == VOS_OK)
    {
        /*����NV��������*/
        *pucSmsOverIms = stNvImsCapability.ucSmsOnImsSupportFlag;
        *pucSrvcc = stNvImsCapability.ucSrvccOnImsSupportFlag;

    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("IMSA_ReadImsaNvImsCapability: read NV err!");

        /*���ó�ʼֵ*/
        *pucSmsOverIms = VOS_TRUE;
        *pucSrvcc = VOS_TRUE;
    }

}
/* lihong00150010 ims end */

/*leili modify for isr begin*/
/*****************************************************************************
 Function Name   : NAS_LMM_PubmDaInqLteCs
 Description     :
 Input           : MsgBlock    *pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.FTY        2012-02-17    Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_PubmDaInqLteCs(MsgBlock *pMsg)
{
    APP_MM_INQ_LTE_CS_REQ_STRU      *pstAppInqReq;
    APP_MM_INQ_LTE_CS_CNF_STRU      *pstAppInqCnf;

    NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqLteCs: enter");

    pstAppInqReq                       = (VOS_VOID *)pMsg;

    /* Ϊ��Ϣ�����ַ */
    pstAppInqCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_LTE_CS_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppInqCnf)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqLteCs: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        return;
    }


    /* �ṹ��ʼ�� */
    NAS_LMM_MEM_SET(pstAppInqCnf, 0, sizeof(APP_MM_INQ_LTE_CS_CNF_STRU));

    /* �����Ϣͷ */
    EMM_COMP_APP_MSG_VOS_HEADER(pstAppInqCnf,
                                EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_LTE_CS_CNF_STRU),
                                pstAppInqReq);

    /*����OPID*/
    pstAppInqCnf->ulOpId      = pstAppInqReq->ulOpId;

    /*������Ϣ����*/
    pstAppInqCnf->ulMsgId     = ID_APP_MM_INQ_LTE_CS_CNF;

    pstAppInqCnf->ulRslt      = APP_SUCCESS;

    if(NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PubmDaInqLteCs: REG domain  NAS_LMM_REG_DOMAIN_CS_PS!!");
        pstAppInqCnf->stLtecsInfo.ucSmsOverSGs = NAS_LMM_LTE_CS_SERVICE_SUPPORT;

        if(NAS_LMM_ADDITIONAL_UPDATE_BUTT == NAS_EMM_GetAddUpdateRslt())
        {
            NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PubmDaInqLteCs: Addition Update Result not exist!!");
            pstAppInqCnf->stLtecsInfo.ucCSFB = NAS_LMM_LTE_CS_SERVICE_SUPPORT;
        }
        else
        {
            NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PubmDaInqLteCs: Addition Update Resultsexist!!");
            /*lint -e960*/
            if((NAS_LMM_ADDITIONAL_UPDATE_CSFB_NOT_PREFERED == NAS_EMM_GetAddUpdateRslt()) || (NAS_LMM_ADDITIONAL_UPDATE_NO_INFO == NAS_EMM_GetAddUpdateRslt()))
            /*lint +e960*/
            {
                NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PubmDaInqLteCs: Addition Update Result is NO_INFO or CSFB_NOT_PREFERED!!");
                pstAppInqCnf->stLtecsInfo.ucCSFB = NAS_LMM_LTE_CS_SERVICE_SUPPORT;
            }
        }
    }
	/* lihong00150010 ims begin */
    NAS_LMM_ReadImsaNvImsCapability(&pstAppInqCnf->stLtecsInfo.ucSmsOverIMS,&pstAppInqCnf->stLtecsInfo.ucSrVcc);
	/* lihong00150010 ims end */

    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pstAppInqCnf);

    return;
}
/*leili modify for isr end*/


/* niuxiufan DT begin */

VOS_VOID  NAS_LMM_PubmDaInqGuti(MsgBlock *pMsg)
{
    APP_MM_INQ_LTE_GUTI_REQ_STRU      *pstAppInqReq;
    APP_MM_INQ_LTE_GUTI_CNF_STRU      *pstAppInqCnf;

    pstAppInqReq                       = (VOS_VOID *)pMsg;


    /* ���������ж��Ƿ�ֹͣGUTI�ϱ� */
    if (DT_CMD_STOP == pstAppInqReq->enCmd)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqGuti: START");
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_GUTI)->enRptStatus = NAS_DT_RPT_STOP;
    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqGuti: STOP");
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_GUTI)->enDtRptItem = NAS_DT_REPORT_TYPE_GUTI;
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_GUTI)->enRptStatus = NAS_DT_RPT_START;
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_GUTI)->enRptType = APP_MM_RM_AUTO;
    }

    /* Ϊ��Ϣ�����ַ */
    pstAppInqCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_LTE_GUTI_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppInqCnf)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqGuti: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        return;
    }


    /* �ṹ��ʼ�� */
    NAS_LMM_MEM_SET(pstAppInqCnf, 0, sizeof(APP_MM_INQ_LTE_GUTI_CNF_STRU));

    /* �����Ϣͷ */
    EMM_COMP_APP_DT_CNF_MSG_VOS_HEADER(pstAppInqCnf,
                                EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_LTE_GUTI_CNF_STRU),
                                pstAppInqReq);

    /*����OPID*/
    pstAppInqCnf->ulOpId      = pstAppInqReq->ulOpId;

    /*������Ϣ����*/
    pstAppInqCnf->ulMsgId     = ID_APP_MM_INQ_LTE_GUTI_CNF;

    pstAppInqCnf->ulRslt      = APP_SUCCESS;

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEmmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAppInqCnf);
    }
#endif


    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pstAppInqCnf);

    NAS_LMM_PubmIndGuti();

    return;
}
VOS_VOID  NAS_LMM_PubmDaInqImsi(MsgBlock *pMsg)
{
    APP_MM_INQ_IMSI_REQ_STRU      *pstAppInqReq;
    APP_MM_INQ_IMSI_CNF_STRU      *pstAppInqCnf;

     pstAppInqReq                       = (VOS_VOID *)pMsg;

    /* ���������ж��Ƿ�ֹͣIMSI�ϱ� */
    if (DT_CMD_STOP == pstAppInqReq->enCmd)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqImsi: STOP");
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_IMSI)->enRptStatus = NAS_DT_RPT_STOP;
    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqImsi: START");
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_IMSI)->enDtRptItem = NAS_DT_REPORT_TYPE_IMSI;
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_IMSI)->enRptStatus = NAS_DT_RPT_START;
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_IMSI)->enRptType = APP_MM_RM_AUTO;
    }

    /* Ϊ��Ϣ�����ַ */
    pstAppInqCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_IMSI_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppInqCnf)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqImsi: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        return;
    }


    /* �ṹ��ʼ�� */
    NAS_LMM_MEM_SET(pstAppInqCnf, 0, sizeof(APP_MM_INQ_IMSI_CNF_STRU));

    /* �����Ϣͷ */
    EMM_COMP_APP_DT_CNF_MSG_VOS_HEADER(pstAppInqCnf,
                                EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_IMSI_CNF_STRU),
                                pstAppInqReq);

    /*����OPID*/
    pstAppInqCnf->ulOpId      = pstAppInqReq->ulOpId;

    /*������Ϣ����*/
    pstAppInqCnf->ulMsgId     = ID_APP_MM_INQ_IMSI_CNF;
    pstAppInqCnf->ulRslt      = APP_SUCCESS;

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEmmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAppInqCnf);
    }
#endif
    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pstAppInqCnf);

    NAS_LMM_PubmIndImsi();

    return;
}
VOS_VOID  NAS_LMM_PubmDaInqEmmState(MsgBlock *pMsg)
{
    APP_MM_INQ_EMM_STATE_REQ_STRU      *pstAppInqReq;
    APP_MM_INQ_EMM_STATE_CNF_STRU      *pstAppInqCnf;

    NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqEmmState: enter");

    pstAppInqReq                       = (VOS_VOID *)pMsg;

    /* ���������ж��Ƿ�ֹͣEMM State�ϱ� */
    if (DT_CMD_STOP == pstAppInqReq->enCmd)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqEmmState: STOP");
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_EMM_STATE)->enRptStatus = NAS_DT_RPT_STOP;
    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqEmmState: START");
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_EMM_STATE)->enDtRptItem = NAS_DT_REPORT_TYPE_EMM_STATE;
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_EMM_STATE)->enRptStatus = NAS_DT_RPT_START;
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_EMM_STATE)->enRptType = APP_MM_RM_AUTO;
    }

    /* Ϊ��Ϣ�����ַ */
    pstAppInqCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_EMM_STATE_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppInqCnf)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqEmmState: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        return;
    }


    /* �ṹ��ʼ�� */
    NAS_LMM_MEM_SET(pstAppInqCnf, 0, sizeof(APP_MM_INQ_EMM_STATE_CNF_STRU));

    /* �����Ϣͷ */
    EMM_COMP_APP_DT_CNF_MSG_VOS_HEADER(pstAppInqCnf,
                                EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_EMM_STATE_CNF_STRU),
                                pstAppInqReq);

    /*����OPID*/
    pstAppInqCnf->ulOpId      = pstAppInqReq->ulOpId;

    /*������Ϣ����*/
    pstAppInqCnf->ulMsgId     = ID_APP_MM_INQ_EMM_STATE_CNF;

    pstAppInqCnf->ulRslt      = APP_SUCCESS;

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEmmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAppInqCnf);
    }
#endif

    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pstAppInqCnf);

    NAS_LMM_PubmIndEmmState();

    return;
}
VOS_VOID  NAS_LMM_PubmIndGuti(VOS_VOID)
{
    APP_MM_INQ_LTE_GUTI_IND_STRU      *pstAppGutiInd;
    NAS_MM_GUTI_STRU                  *pstEmmCurGuti;

    NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndGuti: enter");

    /* ���������ж��Ƿ�ֹͣGUTI�ϱ� */
    if (NAS_DT_RPT_STOP == NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_GUTI)->enRptStatus)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndGuti: STOP");
        return;
    }

    /* Ϊ��Ϣ�����ַ */
    pstAppGutiInd = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_LTE_GUTI_IND_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppGutiInd)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqGuti: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        return;
    }


    /* �ṹ��ʼ�� */
    NAS_LMM_MEM_SET(pstAppGutiInd, 0, sizeof(APP_MM_INQ_LTE_GUTI_IND_STRU));

    /* �����Ϣͷ */
    EMM_COMP_APP_DT_IND_MSG_HEADER( pstAppGutiInd,
                                 EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_LTE_GUTI_IND_STRU));

    /*���APP��Ϣͷ*/
    EMM_COMP_OMT_APP_MSG_HEADER( pstAppGutiInd);

    /*������Ϣ����*/
    pstAppGutiInd->ulMsgId     = ID_APP_MM_INQ_LTE_GUTI_IND;
    pstAppGutiInd->ulOpId      = DIAG_CMD_EMM_APP_GUTI_INFO_IND;


    /* ��ȡGUTI */
    pstEmmCurGuti                       = NAS_LMM_GetEmmInfoUeidGutiAddr();
    NAS_LMM_MEM_CPY( &pstAppGutiInd->stGuti,
                    pstEmmCurGuti,
                    sizeof(NAS_LMM_GUTI_STRU));

    /*����GUTI��Ϣ��ȫ�ֱ���*/
    NAS_LMM_MEM_CPY(&g_stEmmDtInfo.stGuti,
                        pstEmmCurGuti,
                        sizeof(NAS_MM_GUTI_STRU));

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEmmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAppGutiInd);
    }
#endif
    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pstAppGutiInd);
    return;
}
VOS_VOID  NAS_LMM_PubmIndImsi(VOS_VOID)
{
    APP_MM_INQ_IMSI_IND_STRU      *pstAppImsiInd;
    NAS_OM_IMSI_INFO_STRU          stImsiInfo;
    VOS_UINT8                      i;

    NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndImsi: enter");


    /* ���������ж��Ƿ�ֹͣIMSI�ϱ� */
    if (NAS_DT_RPT_STOP == NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_IMSI)->enRptStatus)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndImsi: STOP");
        return;
    }

    /* Ϊ��Ϣ�����ַ */
    pstAppImsiInd = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_IMSI_IND_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppImsiInd)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndImsi: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        return;
    }


    /* �ṹ��ʼ�� */
    NAS_LMM_MEM_SET(pstAppImsiInd, 0, sizeof(APP_MM_INQ_IMSI_IND_STRU));

    /* �����Ϣͷ */
    EMM_COMP_APP_DT_IND_MSG_HEADER( pstAppImsiInd,
                                 EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_IMSI_IND_STRU));

    /*���APP��Ϣͷ*/
    EMM_COMP_OMT_APP_MSG_HEADER( pstAppImsiInd);

    /*������Ϣ����*/
    pstAppImsiInd->ulMsgId     = ID_APP_MM_INQ_IMSI_IND;
    pstAppImsiInd->ulOpId      = DIAG_CMD_EMM_APP_IMSI_INFO_IND;


    NAS_LMM_MEM_SET(&stImsiInfo, 0, sizeof(NAS_OM_IMSI_INFO_STRU));

    /*�����ǰ�޿�,��OM�ظ���ѯIMSIΪ��*/
    if (NAS_LMM_SIM_STATUS_AVAILABLE == NAS_LMM_GetSimState())
    {

        /* ��ȡIMSI */
        stImsiInfo.ucImsiLen = (VOS_UINT8)((g_stEmmInfo.stMmUeId.aucImsi[0])*2 - 1);

        /*���һ���ֽ����4λΪF,�����IMSIΪż���� */
        if (0xF0 == (g_stEmmInfo.stMmUeId.aucImsi[g_stEmmInfo.stMmUeId.aucImsi[0]] & 0xF0))
        {
            stImsiInfo.ucImsiLen -= 1;
        }

        for(i = 0; i < stImsiInfo.ucImsiLen; i++)
        {
            if (0 == (i+1)%2)
            {
                stImsiInfo.ucImsi[i] = 0x0F & (g_stEmmInfo.stMmUeId.aucImsi[(i+1)/2 + 1]);
            }
            else
            {
                stImsiInfo.ucImsi[i] = 0x0F & (g_stEmmInfo.stMmUeId.aucImsi[(i+1)/2 + 1] >> 4);
            }
        }
    }

    NAS_LMM_MEM_CPY( &pstAppImsiInd->stImsi,
                    &stImsiInfo,
                    sizeof(NAS_OM_IMSI_INFO_STRU));

    /*����IMSI��Ϣ��ȫ�ֱ���*/
    NAS_LMM_MEM_CPY(&g_stEmmDtInfo.stImsi,
                        &stImsiInfo,
                        sizeof(NAS_OM_IMSI_INFO_STRU));

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEmmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAppImsiInd);
    }
#endif
    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pstAppImsiInd);

    return;
}
VOS_VOID  NAS_LMM_PubmIndEmmState(VOS_VOID)
{
    APP_MM_INQ_EMM_STATE_IND_STRU      *pstAppEmmStateInd;
    NAS_OM_EMM_STATE_STRU              stEmmPtlState    = {0};

    NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndEmmState: enter");


    /* ���������ж��Ƿ�ֹͣEMM State�ϱ� */
    if (NAS_DT_RPT_STOP == NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_EMM_STATE)->enRptStatus)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndEmmState: STOP");
        return;
    }


    /* Ϊ��Ϣ�����ַ */
    pstAppEmmStateInd = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_EMM_STATE_IND_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppEmmStateInd)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndEmmState: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        return;
    }


    /* �ṹ��ʼ�� */
    NAS_LMM_MEM_SET(pstAppEmmStateInd, 0, sizeof(APP_MM_INQ_EMM_STATE_IND_STRU));

    /* �����Ϣͷ */
    EMM_COMP_APP_DT_IND_MSG_HEADER( pstAppEmmStateInd,
                                 EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_EMM_STATE_IND_STRU));

    /*���APP��Ϣͷ*/
    EMM_COMP_OMT_APP_MSG_HEADER( pstAppEmmStateInd);


    /*������Ϣ����*/
    pstAppEmmStateInd->ulMsgId     = ID_APP_MM_INQ_EMM_STATE_IND;
    pstAppEmmStateInd->ulOpId      = DIAG_CMD_EMM_APP_EMM_STATE_IND;

    /* ��ȡЭ��״̬��Ϣ */
    NAS_LMM_PubmGetEmmState(&(stEmmPtlState.enMainState),
                           &(stEmmPtlState.enSubState),
                            NAS_LMM_GetEmmCurFsmMS(),
                            NAS_LMM_GetEmmCurFsmSS());

    stEmmPtlState.usStaTId = (VOS_UINT16)NAS_LMM_GetEmmCurTimer();

    NAS_LMM_MEM_CPY( &pstAppEmmStateInd->stEmmState,
                    &stEmmPtlState,
                    sizeof(NAS_OM_EMM_STATE_STRU));

    /*Э��״̬��Ϣ������ȫ�ֱ���*/
    NAS_LMM_MEM_CPY(&g_stEmmDtInfo.stEmmState,
                    &stEmmPtlState,
                    sizeof(NAS_OM_EMM_STATE_STRU));

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEmmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAppEmmStateInd);
    }
#endif
    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pstAppEmmStateInd);
    return;
}

/* niuxiufan DT end */



/*****************************************************************************
 Function Name   : NAS_LMM_PubmDaInqUeMode
 Description     :
 Input           : MsgBlock    *pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.FTY        2012-02-17    Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_PubmDaInqUeMode(MsgBlock *pMsg)
{
    APP_MM_INQ_UE_MODE_REQ_STRU      *pstAppInqReq;
    APP_MM_INQ_UE_MODE_CNF_STRU      *pstAppInqCnf;

    pstAppInqReq                       = (VOS_VOID *)pMsg;

    /* Ϊ��Ϣ�����ַ */
    pstAppInqCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_UE_MODE_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppInqCnf)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqUeMode: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        return;
    }


    /* �ṹ��ʼ�� */
    NAS_LMM_MEM_SET(pstAppInqCnf, 0, sizeof(APP_MM_INQ_UE_MODE_CNF_STRU));

    /* �����Ϣͷ */
    EMM_COMP_APP_MSG_VOS_HEADER(pstAppInqCnf,
                                EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_UE_MODE_CNF_STRU),
                                pstAppInqReq);

    /*������Ϣ��*/
    pstAppInqCnf->ulOpId      = pstAppInqReq->ulOpId;
    pstAppInqCnf->ulMsgId     = ID_APP_MM_INQ_UE_MODE_CNF;
    pstAppInqCnf->ulRslt      = APP_SUCCESS;
    pstAppInqCnf->enCurrentUeMode = NAS_LMM_GetEmmInfoUeOperationMode();
    /*��ǰUE֧��CS\PS��PSģʽ����������Ϊ2*/
    pstAppInqCnf->ulSupportModeCnt = 2;
    if(EMM_SETTING_DATA_CENTRIC == NAS_LMM_GetEmmInfoUeCenter())
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqUeMode: UE Center is DATA_CENTRIC!!");
        pstAppInqCnf->aenSupportModeList[0] = NAS_LMM_UE_PS_MODE_2;
        pstAppInqCnf->aenSupportModeList[1] = NAS_LMM_UE_CS_PS_MODE_2;

    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqUeMode: UE Center is VOICE_CENTRIC!!");
        pstAppInqCnf->aenSupportModeList[0] = NAS_LMM_UE_PS_MODE_1;
        pstAppInqCnf->aenSupportModeList[1] = NAS_LMM_UE_CS_PS_MODE_1;
    }

    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pstAppInqCnf);

    return;
}



VOS_VOID    NAS_LMM_PubmGetEmmState
(
    APP_EMM_MAIN_STATE_ENUM_UINT16      *pulProtoclMainState,
    APP_EMM_SUB_STATE_ENUM_UINT16       *pulProtoclSubState,
    NAS_LMM_MAIN_STATE_ENUM_UINT16      enMainState,
    NAS_LMM_SUB_STATE_ENUM_UINT16       enSubState
)
{
    APP_EMM_MAIN_STATE_ENUM_UINT16      ulProtoclMainState;
    APP_EMM_SUB_STATE_ENUM_UINT16       ulProtoclSubState;
    VOS_UINT32                          ulLoop;

    NAS_LMM_FSM_STATE_STACK_STRU         *pstFsmStack;        /* ״̬��ջ��ַ */
    NAS_LMM_FSM_STATE_STRU               *pstFsmStackTop;     /* ָ��ջ��״̬ */


    /* ��ʼ��Э��״̬ */
    ulProtoclMainState                  = APP_EMM_MS_NULL;
    ulProtoclSubState                   = APP_EMM_SS_NULL;


    /* ���ӽ�������,�ͷŹ���,��Ȩ���� ��Ҫ��״̬ջ��ȡ״̬ */
    if ((EMM_MS_RRC_CONN_REL_INIT == enMainState)
        ||(EMM_MS_AUTH_INIT == enMainState) )
    {
        /* ��ȡ״̬ջջ����ַ */
        pstFsmStack
            =  NAS_LMM_GetFsmStackAddr(NAS_LMM_PARALLEL_FSM_EMM);
        pstFsmStackTop
            = &((pstFsmStack->astFsmStack)[pstFsmStack->ucStackDepth - 1]);

        /* ��״̬ջ��ȡ״̬ */
        enMainState                     = pstFsmStackTop->enMainState;
        enSubState                      = pstFsmStackTop->enSubState;
    }

    /*��������� */
    if (EMM_MS_SUSPEND == enMainState)
    {
        enMainState = NAS_EMM_GetMsBefSuspend();
        enSubState = NAS_EMM_GetSsBefSuspend();
    }

    if (EMM_MS_RESUME == enMainState)
    {
        if (EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND == enSubState)
        {
            enMainState = NAS_EMM_GetMsBefResume();
            enSubState = NAS_EMM_GetSsBefResume();
        }
        else
        {
            if ((NAS_LMM_SYS_CHNG_TYPE_REVERSE_RSL == NAS_EMM_GetResumeType())
                || (NAS_LMM_SYS_CHNG_TYPE_REVERSE_HO == NAS_EMM_GetResumeType())
                || (NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO == NAS_EMM_GetResumeType())
                || (NAS_LMM_SYS_CHNG_TYPE_REVERSE_REDIR == NAS_EMM_GetResumeType()))
            {
                enMainState = NAS_EMM_GetMsBefSuspend();
                enSubState = NAS_EMM_GetSsBefSuspend();
            }
            else
            {
                enMainState = NAS_EMM_GetMsBefResume();
                enSubState = NAS_EMM_GetSsBefResume();
            }
        }
    }

    /* ����״̬ӳ�����ȡЭ��״̬ */
    for (ulLoop = 0; ulLoop< g_ulProtocolStateMapNum; ulLoop++)
    {
        if ( (enMainState == g_astProtocolStateMap[ulLoop].enMainState)
            &&((enSubState == g_astProtocolStateMap[ulLoop].enSubState)
              || (MM_SS_BUTT == g_astProtocolStateMap[ulLoop].enSubState)) )
        {
            ulProtoclMainState
                = g_astProtocolStateMap[ulLoop].ulProtoclMainState;
            ulProtoclSubState
                = g_astProtocolStateMap[ulLoop].ulProtoclSubState;
            break;
        }
    }

    /* ��ֵ��� */
    *pulProtoclMainState                = ulProtoclMainState;
    *pulProtoclSubState                 = ulProtoclSubState;

    return;
}


VOS_VOID    NAS_LMM_PubmGetEmmUpdateState
(
    APP_EMM_UPDATE_STATE_ENUM_UINT32    *pulEmmUpState
)
{
    *pulEmmUpState                      =  NAS_EMM_UPDATE_STAE;

    return;
}



VOS_VOID    NAS_LMM_PubmGetAreaInfo
(
    APP_GUTI_STRU                       *pstGuti,
    APP_TA_LIST_STRU                    *pstTaiList,
    APP_TA_STRU                         *pstLastTa
)
{
    NAS_MM_GUTI_STRU                    *pstEmmCurGuti;
    NAS_MM_TA_LIST_STRU                 *pstEmmCurTaiList;
    NAS_MM_NETWORK_ID_STRU              *pstEmmCurNetId;

    /* ��ȡGUTI */
    pstEmmCurGuti                       = NAS_LMM_GetEmmInfoUeidGutiAddr();
    NAS_LMM_MEM_CPY( pstGuti,
                    pstEmmCurGuti,
                    sizeof(NAS_LMM_GUTI_STRU));

    /* ��ȡTAI�б� */
    pstEmmCurTaiList                    = NAS_LMM_GetEmmInfoNetInfoTaiListAddr();
    NAS_LMM_MEM_CPY( pstTaiList,
                    pstEmmCurTaiList,
                    sizeof(NAS_MM_TA_LIST_STRU));

    /* ��ȡTA */
    pstEmmCurNetId                      = NAS_LMM_GetEmmInfoNetInfoLastRegNetAddr();
    NAS_LMM_MEM_CPY( &pstLastTa->stPlmnId,
                    &pstEmmCurNetId->stPlmnId,
                    sizeof(NAS_MM_PLMN_ID_STRU));
    NAS_LMM_MEM_CPY( &pstLastTa->stTac,
                    &pstEmmCurNetId->stTac,
                    sizeof(NAS_MM_TAC_STRU));

    return;

}
VOS_VOID    NAS_LMM_PubmGetEmmInfo
(
    APP_EMM_INFO_STRU                   *pstEmmInfoCnf
)
{
    /* ��ȡЭ��״̬��Ϣ */
    NAS_LMM_PubmGetEmmState(&(pstEmmInfoCnf->ulMainState),
                           &(pstEmmInfoCnf->ulSubState),
                            NAS_LMM_GetEmmCurFsmMS(),
                            NAS_LMM_GetEmmCurFsmSS());
    /* ��ȡEMM update״̬ */
    NAS_LMM_PubmGetEmmUpdateState(&(pstEmmInfoCnf->ulEmmUpState));

    /* ��ȡ GUTI,TaiList,Last Ta */
    NAS_LMM_PubmGetAreaInfo(&(pstEmmInfoCnf->stGuti),
                           &(pstEmmInfoCnf->stTaiList),
                           &(pstEmmInfoCnf->stLastTa));

}
VOS_VOID    NAS_LMM_SendOmtKeyEvent(     PS_EMM_OMT_KEY_EVENT_TYPE_ENUM_UINT8
                                        ucEmmOmtKeyEvent  )
{
#ifndef PS_ITT_PC_TEST
    /*lint -e778*/
    /*lint -e648*/
    if(ERR_MSP_SUCCESS != DIAG_ReportEventLog(MODID(UE_MODULE_MM_ID, LOG_TYPE_INFO),\
                    (VOS_UINT32)ucEmmOmtKeyEvent+OM_PS_KEY_EVENT_BASE_ID))
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_SendOmtKeyEvent: Send Msg Fail!");
        return;
    }
    /*lint +e648*/
    /*lint +e778*/
#endif

}



VOS_VOID    NAS_LMM_SendOmtAirMsg(       NAS_LMM_OM_AIR_MSG_UP_DOWN_ENUM_UINT8  ucDir,
                                        NAS_LMM_OM_AIR_MSG_ID_ENUM_UINT8       ucAirMsgId,
                                        NAS_MSG_STRU                       *pstNasMsg)
{
#ifndef PS_ITT_PC_TEST

    DIAG_AIR_MSG_LOG_STRU        stAirMsg;
    VOS_UINT8                   *pucTmpData = VOS_NULL_PTR;

    /*����տ���Ϣ�ռ�*/
    pucTmpData = (VOS_UINT8*)
                        NAS_LMM_MEM_ALLOC(pstNasMsg->ulNasMsgSize);

    if(VOS_NULL_PTR== pucTmpData)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SendOmtAirMsg: MEM_ALLOC ERR!");
        return;
    }

    NAS_LMM_MEM_CPY( (pucTmpData),(pstNasMsg->aucNasMsg),(pstNasMsg->ulNasMsgSize));

    /*�տ���Ϣ��ֵ*/
    if(NAS_EMM_OMT_AIR_MSG_UP == ucDir)
    {
        stAirMsg.ulId = DIAG_AIR_MSG_LOG_ID(PS_PID_MM, OS_MSG_UL);
        stAirMsg.ulSideId = DIAG_SIDE_NET;
    }
    else
    {
        stAirMsg.ulId = DIAG_AIR_MSG_LOG_ID(PS_PID_MM, OS_MSG_DL);
        stAirMsg.ulSideId = DIAG_SIDE_UE;
    }
    stAirMsg.ulMessageID = (VOS_UINT32)(ucAirMsgId+ PS_MSG_ID_AIR_BASE);
    stAirMsg.ulDestMod = 0;
    stAirMsg.ulDataSize = pstNasMsg->ulNasMsgSize;
    stAirMsg.pData = (void*)pucTmpData;

    /*�ϱ��տ���Ϣ*/
    if(ERR_MSP_SUCCESS != DIAG_ReportAirMessageLog(&stAirMsg))
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_SendOmtAirMsg: Send Msg Fail!");
    }

    /*�ͷ��ڴ�ռ�*/
    NAS_LMM_MEM_FREE(pucTmpData);

#endif
    (VOS_VOID)(pstNasMsg);
}


VOS_VOID   NAS_LMM_FindAirMsgId( VOS_UINT8 ucCnMsgType,
                                VOS_UINT8 *pucAirMsg,
                                VOS_UINT8 *pucKeyEvent)
{
    VOS_UINT8 i;
    VOS_UINT8 ucLen;
    ucLen = sizeof(g_stMmOmMsgIdStru)/(sizeof(NAS_LMM_OM_MSG_ID_CHANGE_STRU));
    for(i = 0;i < ucLen;i++)
    {
        if (ucCnMsgType == g_stMmOmMsgIdStru[i].enCnMsgType)
        {
            *pucAirMsg   = g_stMmOmMsgIdStru[i].enAirMsg;
            *pucKeyEvent = g_stMmOmMsgIdStru[i].enKeyEvent;
            break;
        }
    }
    return;
}


VOS_VOID    NAS_LMM_PubmDaSendSetCnf( const NAS_LMM_APP_PARA_SET_RESLT_STRU *pstAppRslt )
{

    APP_MM_SET_CMD_CNF_STRU            *pstEmmSetCnf;

    NAS_LMM_PUBM_LOG3_NORM("NAS_LMM_PubmDaSetCnf:  ulMsgId =, ulRslt =, ulOpId = ",
                                        pstAppRslt->ulMsgId,
                                        pstAppRslt->ulRslt,
                                        pstAppRslt->ulOpId);

    /* ����DOPRA��Ϣ */
    pstEmmSetCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(
                                        sizeof(APP_MM_SET_CMD_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstEmmSetCnf)
    {
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PubmDaSetCnf: alloc NULL_PTR !! ulMsgId = ",
                                        pstAppRslt->ulMsgId);
        return;
    }

    NAS_LMM_MEM_SET(pstEmmSetCnf, 0, sizeof(APP_MM_SET_CMD_CNF_STRU));


    /* �����Ϣͷ */
    EMM_COMP_APP_MSG_VOS_HEADER( pstEmmSetCnf,
                                 EMM_MSG_LENTH_NO_HEADER(APP_MM_SET_CMD_CNF_STRU),
                                 pstAppRslt);

    /* ��д��Ϣ�� */
    pstEmmSetCnf->ulMsgId               = pstAppRslt->ulMsgId;
    pstEmmSetCnf->ulOpId                = pstAppRslt->ulOpId;
    pstEmmSetCnf->ulRslt                = pstAppRslt->ulRslt;

    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pstEmmSetCnf);

    return;

}


VOS_UINT32  NAS_LMM_CheckAppDrxParam( CONST APP_DRX_STRU *pstAppDrxParam )
{
    /*������ָ��*/
    if (VOS_NULL_PTR == pstAppDrxParam)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckAppDrxParam: Input NULL PTR.");
        return NAS_EMM_PARA_INVALID;
    }

    /*SPLIT on CCCH��Ч����֤*/
    if (NAS_EMM_PARA_INVALID == NAS_LMM_IsDrxSplitOnCcchValid(pstAppDrxParam->ucSplitOnCcch))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckAppDrxParam: SplitOnCcch InValid.");
        return NAS_EMM_PARA_INVALID;
    }

    /*non_DRX Timer��Ч����֤*/
    if (NAS_EMM_PARA_INVALID == NAS_LMM_IsDrxNonDrxTimerValid(pstAppDrxParam->ucNonDrxTimer))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckAppDrxParam: NonDrxTimer InValid.");
        return NAS_EMM_PARA_INVALID;
    }

    /*SPLIT PG CYCLE CODE��Ч����֤*/
    if (NAS_EMM_PARA_INVALID == NAS_LMM_IsDrxPgCycleCodeValid(pstAppDrxParam->ucSplitPgCode))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckAppDrxParam: SplitPgCycleCode InValid.");
        return NAS_EMM_PARA_INVALID;
    }

    /* DRX Valude for S1 Mode��Ч����֤*/
    if (NAS_EMM_PARA_INVALID == NAS_LMM_IsUeDrxCycleValid(pstAppDrxParam->ucPsDrxLen))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckAppDrxParam: UeSpecDrxCycle InValid.");
        return NAS_EMM_PARA_INVALID;
    }

    return NAS_EMM_PARA_VALID;

}
VOS_UINT32  NAS_LMM_IsDrxSplitOnCcchValid( VOS_UINT8 ucSplitOnCcch )
{
    /*ucSplitOnCcchȡֵ:0 or 1*/
    if ((NAS_LMM_SPLIT_ON_CCCH_NOT_SUPPORT != ucSplitOnCcch)
      &&(NAS_LMM_SPLIT_ON_CCCH_SUPPORT != ucSplitOnCcch))
    {
        return NAS_EMM_PARA_INVALID;
    }
    return NAS_EMM_PARA_VALID;
}
VOS_UINT32  NAS_LMM_IsDrxNonDrxTimerValid( VOS_UINT8 ucNonDrxTimer )
{
    /*ucNonDrxTimerȡֵ��Χ:[0,7]*/
    if (NAS_LMM_MAX_NON_DRX_TIMER < ucNonDrxTimer)
    {
        return NAS_EMM_PARA_INVALID;
    }
    return NAS_EMM_PARA_VALID;
}
VOS_UINT32  NAS_LMM_IsDrxPgCycleCodeValid( VOS_UINT8 ucSplitPgCode )
{
    /*ucSplitPgCodeȡֵ��Χ:[0,98]*/
    if (NAS_LMM_MAX_SPLIT_PG_CYCLE_CODE < ucSplitPgCode)
    {
        return NAS_EMM_PARA_INVALID;
    }
    return NAS_EMM_PARA_VALID;
}
VOS_UINT32  NAS_LMM_IsUeDrxCycleValid( VOS_UINT8 ucPsDrxLen )
{
    /*Drx Value for S1 Mode: 24008-930 10.5.5.6*/
    CONST VOS_UINT32 aulUeSpecDrxValue[NAS_LMM_UE_SPEC_DRX_VALUE_NUM] = {0,6,7,8,9};
    VOS_UINT32                          i;

    for(i = 0; i < NAS_LMM_UE_SPEC_DRX_VALUE_NUM; i++)
    {
        if(aulUeSpecDrxValue[i] == ucPsDrxLen)
        {
           return NAS_EMM_PARA_VALID;
        }
    }

    return NAS_EMM_PARA_INVALID;
}


/* xiongxianghui00253310 modify for ftmerrlog begin */

VOS_VOID NAS_LMM_OmInfoIndProc(VOS_VOID)
{
    VOS_UINT32 ulFtmRst = NAS_EMM_FAIL;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_OmInfoIndProc!");

    if(NAS_EMM_FTM_ACTION_FLAG_OPEN == NAS_EMM_GetFtmInfoActionFlag())
    {
        ulFtmRst = NAS_LMM_CompareEmmDatabaseInfo();
    }

    NAS_LMM_UpdateEmmDatabaseInfo();

    if(NAS_EMM_SUCC == ulFtmRst)
    {
        NAS_LMM_SendOmFtmMsg();
    }
}



VOS_VOID NAS_LMM_FtmInfoInit( VOS_VOID )
{
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_FtmInfoInit!");

    NAS_LMM_MEM_SET(NAS_EMM_GetFtmInfoManageAddr(), 0, sizeof(EMM_FTM_INFO_MANAGE_STRU));

    NAS_LMM_MEM_SET(NAS_EMM_GetEmmInfoAddr(), 0, sizeof(EMM_DATABASE_INFO_STRU));

    NAS_EMM_GetFtmInfoActionFlag() = NAS_EMM_FTM_ACTION_FLAG_CLOSE;

    return;
}



VOS_UINT32 NAS_LMM_CompareEmmDatabaseInfo( VOS_VOID )
{
    NAS_LMM_TIMER_CTRL_STRU             *pstPtlTimer;
    APP_EMM_MAIN_STATE_ENUM_UINT16      ulProtoclMainState;
    APP_EMM_SUB_STATE_ENUM_UINT16       ulProtoclSubState;


    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_CompareEmmDatabaseInfo!");

    /* ��EMM��ǰ״̬��ȡЭ��״̬ */
    NAS_LMM_PubmGetEmmState(&ulProtoclMainState,
                            &ulProtoclSubState,
                            NAS_LMM_GetEmmCurFsmMS(),
                            NAS_LMM_GetEmmCurFsmSS());

    if((ulProtoclMainState != NAS_EMM_GetEmmInfoAddr()->enMainState)
        || (ulProtoclSubState != NAS_EMM_GetEmmInfoAddr()->enSubState))
    {
        return NAS_EMM_SUCC;
    }

    if(NAS_LMM_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(&NAS_EMM_GetEmmInfoAddr()->stGuti,
                                                    NAS_LMM_GetEmmInfoUeidGutiAddr(),
                                                    sizeof(NAS_MM_GUTI_STRU)))
    {
        return NAS_EMM_SUCC;
    }

    if(NAS_LMM_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(&NAS_EMM_GetEmmInfoAddr()->stPlmnId,
                                                    NAS_LMM_GetEmmInfoLastRegPlmnAddr(),
                                                    sizeof(NAS_MM_PLMN_ID_STRU)))
    {
        return NAS_EMM_SUCC;
    }

    if((NAS_EMM_GetEmmInfoAddr()->enEmmCnRejCause) != NAS_EMM_GetFtmInfoCnRej())
    {
        return NAS_EMM_SUCC;
    }

    if(NAS_LMM_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(&NAS_EMM_GetEmmInfoAddr()->stTac,
                                                    NAS_LMM_GetEmmInfoLastRegTacAddr(),
                                                    sizeof(NAS_MM_TAC_STRU)))
    {
        return NAS_EMM_SUCC;
    }

    /*lint -e506 -e944*/
    pstPtlTimer = NAS_LMM_GetPtlTimerAddr(TI_NAS_EMM_PTL_T3412);
    /*lint +e506 +e944*/
    if(NAS_EMM_GetEmmInfoAddr()->ulTimerLen3412 != pstPtlTimer->ulTimerLen)
    {
        return NAS_EMM_SUCC;
    }

    return NAS_EMM_FAIL;
}
 VOS_VOID NAS_LMM_UpdateEmmDatabaseInfo(VOS_VOID)
 {
    NAS_LMM_TIMER_CTRL_STRU             *pstPtlTimer;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_UpdateEmmDatabaseInfo!");

    /* ����EMM״̬ */
    NAS_LMM_PubmGetEmmState(&NAS_EMM_GetEmmInfoAddr()->enMainState,
                            &NAS_EMM_GetEmmInfoAddr()->enSubState,
                            NAS_LMM_GetEmmCurFsmMS(),
                            NAS_LMM_GetEmmCurFsmSS());

    /* ����GUTI��Ϣ */
    NAS_LMM_MEM_CPY(&NAS_EMM_GetEmmInfoAddr()->stGuti,
                    NAS_LMM_GetEmmInfoUeidGutiAddr(),
                    sizeof(NAS_MM_GUTI_STRU));

    /* ����PlmnId��Ϣ */
    NAS_LMM_MEM_CPY(&NAS_EMM_GetEmmInfoAddr()->stPlmnId,
                    NAS_LMM_GetEmmInfoLastRegPlmnAddr(),
                    sizeof(NAS_MM_PLMN_ID_STRU));

    /* ����TAC��Ϣ */
    NAS_LMM_MEM_CPY(&NAS_EMM_GetEmmInfoAddr()->stTac,
                    NAS_LMM_GetEmmInfoLastRegTacAddr(),
                    sizeof(NAS_MM_TAC_STRU));


    /* ����CN�ܾ�ԭ�� */
    NAS_EMM_GetEmmInfoAddr()->enEmmCnRejCause = NAS_EMM_GetFtmInfoCnRej();

    /* ����TimerLen3412 */
    /*lint -e506 -e944*/
    pstPtlTimer = NAS_LMM_GetPtlTimerAddr(TI_NAS_EMM_PTL_T3412);
    /*lint +e506 +e944*/
    NAS_EMM_GetEmmInfoAddr()->ulTimerLen3412 = pstPtlTimer->ulTimerLen;

    return;
 }


 VOS_UINT32   NAS_LMM_RevOmFtmCtrlMsg(MsgBlock   *pMsgStru)
 {
     OM_FTM_CTRL_IND_STRU  *pstOmFtmCtlInfo;

     NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevOmFtmCtrlMsg!");

     if (VOS_NULL_PTR == pMsgStru)
     {
         NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevOmFtmCtrlMsg, input point is null!");

         return NAS_LMM_MSG_DISCARD;
     }

     pstOmFtmCtlInfo = (OM_FTM_CTRL_IND_STRU *)(VOS_VOID *)pMsgStru;

     if(1 == pstOmFtmCtlInfo->ucActionFlag)
     {
        /*���ù���ģʽ�ϱ����ܴ�*/
         NAS_EMM_SetFtmOmManageFtmActionFlag(NAS_EMM_FTM_ACTION_FLAG_OPEN);

        /*�ϱ���ǰ��Ϣ */
         NAS_LMM_SendOmFtmMsg();
     }
     else
     {
         /*�رչ���ģʽ�ϱ���*/
          NAS_EMM_SetFtmOmManageFtmActionFlag(NAS_EMM_FTM_ACTION_FLAG_CLOSE);
     }

     return NAS_LMM_MSG_HANDLED;

 }
 VOS_VOID     NAS_LMM_SendOmFtmMsg(VOS_VOID)
 {
     LNAS_OM_FTM_REPROT_IND_STRU *pFtmMsg;

     NAS_LMM_PUBM_LOG1_INFO("LMM_OM_SendOmFtmMsg: ActionFlag = ", NAS_EMM_GetFtmInfoActionFlag());

     /* ������ģʽ�رգ��򲻷��� */
     if(NAS_EMM_FTM_ACTION_FLAG_OPEN != NAS_EMM_GetFtmInfoActionFlag())
     {
         return;
     }

     /*������Ϣ�ڴ�*/
     pFtmMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LNAS_OM_FTM_REPROT_IND_STRU));

     /*�ж�����������ʧ���˳�*/
     if (VOS_NULL_PTR == pFtmMsg)
     {
         return;
     }

     /*����ID_EMM_ESM_PDN_CON_IND��Ϣ*/
     /*�����Ϣͷ*/
     NAS_LMM_COMP_OM_MSG_HEADER(         pFtmMsg,
                                         (sizeof(LNAS_OM_FTM_REPROT_IND_STRU)-
                                         NAS_EMM_LEN_VOS_MSG_HEADER));

     /*�����ϢID*/
     pFtmMsg->ulMsgName                  = ID_OM_FTM_REPROT_IND;

     /*�����Ϣ����*/
     pFtmMsg->ulMsgType                  = OM_ERR_LOG_MSG_FTM_REPORT;
     pFtmMsg->ulMsgSN                    = NAS_EMM_GetFtmInfoMsgSN();
     NAS_EMM_GetFtmInfoMsgSN()++;
     pFtmMsg->ulRptlen                   = sizeof(LNAS_OM_FTM_REPROT_CONTENT_STRU);

     pFtmMsg->stLnasFtmContent.ulMsgModuleID  = OM_ERR_LOG_MOUDLE_ID_LMM;
     pFtmMsg->stLnasFtmContent.usModemId      = 0;
     pFtmMsg->stLnasFtmContent.usProjectID    = 0;
     pFtmMsg->stLnasFtmContent.ulLength       = sizeof(LNAS_LMM_FTM_INFO_STRU);

    /*���ܾ�ԭ��*/
     pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.ucEmmCnRejCause =
         g_astEmmFtmInfoManage.enEmmCnRejCause;

    /*���PlmnID*/
     pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stPlmnId.aucPlmnId[0] =
         g_astEmmInfo.stPlmnId.aucPlmnId[0];
     pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stPlmnId.aucPlmnId[1] =
         g_astEmmInfo.stPlmnId.aucPlmnId[1];
     pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stPlmnId.aucPlmnId[2] =
         g_astEmmInfo.stPlmnId.aucPlmnId[2];

    /*���Guti*/
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMmeCode.ucMmeCode =
        g_astEmmInfo.stGuti.stMmeCode.ucMmeCode;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMmeGroupId.ucGroupId =
        g_astEmmInfo.stGuti.stMmeGroupId.ucGroupId;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMmeGroupId.ucGroupIdCnt =
        g_astEmmInfo.stGuti.stMmeGroupId.ucGroupIdCnt;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMTmsi.ucMTmsi =
        g_astEmmInfo.stGuti.stMTmsi.ucMTmsi;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMTmsi.ucMTmsiCnt1 =
        g_astEmmInfo.stGuti.stMTmsi.ucMTmsiCnt1;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMTmsi.ucMTmsiCnt2 =
        g_astEmmInfo.stGuti.stMTmsi.ucMTmsiCnt2;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMTmsi.ucMTmsiCnt3 =
        g_astEmmInfo.stGuti.stMTmsi.ucMTmsiCnt3;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stPlmnId.aucPlmnId[0] =
        g_astEmmInfo.stGuti.stPlmnId.aucPlmnId[0];
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stPlmnId.aucPlmnId[1] =
        g_astEmmInfo.stGuti.stPlmnId.aucPlmnId[1];
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stPlmnId.aucPlmnId[2] =
        g_astEmmInfo.stGuti.stPlmnId.aucPlmnId[2];

    /*���Timer3412*/
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.ulTimerLen3412 =
        g_astEmmInfo.ulTimerLen3412;

    /*���Tac*/
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stTac.ucTac =
        g_astEmmInfo.stTac.ucTac;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stTac.ucTacCnt =
        g_astEmmInfo.stTac.ucTacCnt;

    /*���mainstate, substate*/
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stEmmState.ulLmmMainState =
        g_astEmmInfo.enMainState;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stEmmState.ulLmmSubState =
        g_astEmmInfo.enSubState;


     /*��OMģ�鷢��״̬�仯��Ϣ*/
     NAS_LMM_SEND_MSG( pFtmMsg);

     return;

 }

#if (FEATURE_ON == FEATURE_PTM)

/*lint -e826*/
VOS_UINT32 NAS_LMM_PreProcMsgEsmSaveErrlogInd(MsgBlock *     pMsg)
{
    EMM_ESM_SAVE_ERRLOG_IND_STRU        *pstSaveEsmErrMsg = VOS_NULL;
    VOS_VOID                            *pstEsmErrlogRslt = VOS_NULL;
    VOS_UINT32                          ulLength = 0;
    VOS_UINT32                          ulResult = 0;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcMsgEsmSaveErrlogInd Enter.");

    /*ȡ��buffer�е�ESM errlog����*/
    pstSaveEsmErrMsg = (EMM_ESM_SAVE_ERRLOG_IND_STRU*)pMsg;
    pstEsmErrlogRslt = (VOS_VOID*)pstSaveEsmErrMsg->stEmmEsmErrlog.aucEsmMsg;
    ulLength = pstSaveEsmErrMsg->stEmmEsmErrlog.ulEsmMsgSize;

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)pstEsmErrlogRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_LMM_PreProcMsgEsmSaveErrlogInd: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
    }

    return NAS_LMM_MSG_HANDLED;
}
/*lint +e826*/

VOS_VOID NAS_LMM_RevNvCtrl(VOS_VOID)
{
    VOS_UINT32                              ulRslt;
    NV_ID_ERR_LOG_CTRL_INFO_STRU            stOMErrLogCtrlInfo;
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevNvCtrl!!!");

    PS_MEM_SET(&stOMErrLogCtrlInfo, 0x00, sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU));

    ulRslt = LPs_NvimItem_Read(en_NV_Item_ErrLogCtrlInfo, &stOMErrLogCtrlInfo, sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU) );
    if(PS_SUCC != ulRslt)
    {
        return;
    }

    /* ����ERRLOG���Ʊ�ʶ, 0��ʾ�ر�errlog�� 1��ʾ����errlog*/
    if ((VOS_FALSE == stOMErrLogCtrlInfo.ucAlmStatus)
     || (VOS_TRUE  == stOMErrLogCtrlInfo.ucAlmStatus))
    {
        NAS_EMM_SetErrlogCtrlInfoCtrlFlag(stOMErrLogCtrlInfo.ucAlmStatus);
    }

    /*�����·���errlog�ȼ�ȥ�����Ƿ�洢log��Ϣ*/
    if ((stOMErrLogCtrlInfo.ucAlmLevel >= LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL)
     && (stOMErrLogCtrlInfo.ucAlmLevel <= LNAS_ERR_LOG_CTRL_LEVEL_WARNING))
    {
        NAS_EMM_SetErrlogCtrlInfoALMLevel(stOMErrLogCtrlInfo.ucAlmLevel);
    }

    return;
}


VOS_UINT32 NAS_LMM_RevOmErrlogCtrlMsg(MsgBlock   *pMsgStru)
{
    OM_ERROR_LOG_CTRL_IND_STRU  *pstOmErrlogCtlInfo;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevOmErrlogCtrlMsg!");

    if (VOS_NULL_PTR == pMsgStru)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevOmErrlogCtrlMsg, input point is null!");

        return NAS_LMM_MSG_DISCARD;
    }

    pstOmErrlogCtlInfo = (OM_ERROR_LOG_CTRL_IND_STRU *)(VOS_VOID *)pMsgStru;

    /* ����ERRLOG���Ʊ�ʶ, 0��ʾ�ر�errlog�� 1��ʾ����errlog*/
    if ((VOS_FALSE == pstOmErrlogCtlInfo->ucAlmStatus)
     || (VOS_TRUE  == pstOmErrlogCtlInfo->ucAlmStatus))
    {
        NAS_EMM_SetErrlogCtrlInfoCtrlFlag(pstOmErrlogCtlInfo->ucAlmStatus);
    }

    /*�����·���errlog�ȼ�ȥ�����Ƿ�洢log��Ϣ*/
    if ((pstOmErrlogCtlInfo->ucAlmLevel >= LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL)
     && (pstOmErrlogCtlInfo->ucAlmLevel <= LNAS_ERR_LOG_CTRL_LEVEL_WARNING))
    {
        NAS_EMM_SetErrlogCtrlInfoALMLevel(pstOmErrlogCtlInfo->ucAlmLevel);
    }

    return NAS_LMM_MSG_HANDLED;
}




VOS_UINT32 NAS_EMM_GetErrLogRingBufUseBytes(VOS_VOID)
{
    return (VOS_UINT32)OM_RingBufferNBytes(NAS_EMM_GetErrlogBufferInfoRingBuffer());
}


 VOS_UINT32 NAS_EMM_GetErrLogRingBufContent(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    return (VOS_UINT32)OM_RingBufferGet(NAS_EMM_GetErrlogBufferInfoRingBuffer(), pbuffer, (VOS_INT)ulbytes);
}


VOS_VOID NAS_EMM_CleanErrLogRingBuf(VOS_VOID)
{
    OM_RingBufferFlush(NAS_EMM_GetErrlogBufferInfoRingBuffer());

    return;
}


VOS_UINT16 NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_ENUM_UINT16 enAlmId)
{
     VOS_UINT16                          usTableLen;
     VOS_UINT16                          usStep;

     /* ��ȡTab������ */
     usTableLen = sizeof(g_astLNasErrAlmLevelTb)/sizeof(g_astLNasErrAlmLevelTb[0]);

     /* ������ض�ӦAlm ID��log�ȼ� */
     for (usStep = 0; usStep < usTableLen; usStep++)
     {
         if (g_astLNasErrAlmLevelTb[usStep].enAlmID == enAlmId)
         {
             return g_astLNasErrAlmLevelTb[usStep].usLogLevel;
         }
     }

 /* δ�鵽������δ����ȼ� */
 return LNAS_ERR_LOG_CTRL_LEVEL_NULL;
}
VOS_VOID NAS_EMM_SndAcpuOmErrLogReportCnf(
 VOS_CHAR                           *pbuffer,
 VOS_UINT32                          ulBufUseLen
)
{
     LNAS_OM_ERR_LOG_REPORT_CNF_STRU     *pstReqErrlogCnf = VOS_NULL_PTR;
     VOS_UINT32                          ulMsgLen;

     /* �ϱ�����Ϣ�ܳ��� */
     ulMsgLen  = sizeof(LNAS_OM_ERR_LOG_REPORT_CNF_STRU) - 4 + ulBufUseLen;

     /* ��Ϣ�ռ����� */
     pstReqErrlogCnf = (VOS_VOID*)NAS_LMM_ALLOC_MSG(ulMsgLen);
     if (VOS_NULL_PTR == pstReqErrlogCnf)
     {
         NAS_LMM_PUBM_LOG_INFO("NAS_EMM_SndAcpuOmErrLogReportCnf, Alloc mem error!");
         return;
     }

     pstReqErrlogCnf->ulReceiverCpuId  = VOS_LOCAL_CPUID;
     pstReqErrlogCnf->ulSenderCpuId    = VOS_LOCAL_CPUID;
     pstReqErrlogCnf->ulReceiverPid    = ACPU_PID_OM;
     pstReqErrlogCnf->ulSenderPid      = PS_PID_MM;
     pstReqErrlogCnf->ulMsgName        = ID_LNAS_OM_ERR_LOG_REPORT_CNF;
     pstReqErrlogCnf->ulMsgType        = OM_ERR_LOG_MSG_ERR_REPORT;
     pstReqErrlogCnf->ulMsgSN          = 0;
     pstReqErrlogCnf->ulRptlen         = ulBufUseLen;

     if (VOS_NULL_PTR != pbuffer)
     {
         PS_MEM_CPY(pstReqErrlogCnf->aucContent, pbuffer, ulBufUseLen);
     }

     NAS_LMM_SEND_MSG(pstReqErrlogCnf);

     return;
}


VOS_UINT32   NAS_LMM_RevOmReadErrlogReq(MsgBlock   *pMsgStru)
{
    VOS_CHAR                                       *pbuffer   = VOS_NULL_PTR;
    VOS_UINT32                                     ulBufUseLen;
    VOS_UINT32                                     ulRealLen;
    VOS_UINT32                                     ulTotalLen;
    LNAS_ERR_INFO_OVERFLOW_COUNT_EVENT_STRU        stLnasErrLogOverflowEvent;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevOmReadErrlogReq!");

    if (VOS_NULL_PTR == pMsgStru)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevOmReadErrlogReq, input point is null!");

        return NAS_LMM_MSG_DISCARD;
    }

    /* RING BUFFER���ݳ��� */
    ulBufUseLen = NAS_EMM_GetErrLogRingBufUseBytes();

    ulTotalLen = ulBufUseLen + sizeof(LNAS_ERR_INFO_OVERFLOW_COUNT_EVENT_STRU);

    pbuffer = (VOS_CHAR *)NAS_LMM_MEM_ALLOC(ulTotalLen);
    if (VOS_NULL_PTR == pbuffer)
    {
        /* ����ID_OM_ERR_LOG_REPORT_CNF����Ϊ�յ���Ϣ��OM */
        NAS_EMM_SndAcpuOmErrLogReportCnf(VOS_NULL_PTR, 0);
        return VOS_TRUE;
    }

    PS_MEM_SET(pbuffer, 0, ulTotalLen);

    /* ��ȡRING BUFFER������ */
    ulRealLen = NAS_EMM_GetErrLogRingBufContent(pbuffer, ulBufUseLen);
    if (ulRealLen != ulBufUseLen)
    {
        /* ����ID_OM_ERR_LOG_REPORT_CNF����Ϊ�յ���Ϣ��OM */
        NAS_EMM_SndAcpuOmErrLogReportCnf(VOS_NULL_PTR, 0);
        NAS_LMM_MEM_FREE(pbuffer);
        return VOS_TRUE;
    }

    /* �����������������Ϣ׷����RingBuf���� */
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stLnasErrLogOverflowEvent.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_OVERFLOW_FAIL,
                                      NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_OVERFLOW_FAIL),
                                      VOS_GetSlice(),
                                      (sizeof(LNAS_ERR_INFO_OVERFLOW_COUNT_EVENT_STRU) - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stLnasErrLogOverflowEvent.ulOverflowCount = NAS_EMM_GetErrlogBufferInfoOverflowCnt();

    PS_MEM_CPY(pbuffer + ulBufUseLen, &stLnasErrLogOverflowEvent, sizeof(stLnasErrLogOverflowEvent));

    /* ��ȡ���˺���Ҫ��RINGBUFFER��� */
    NAS_EMM_CleanErrLogRingBuf();

    /* ����������� */
    NAS_EMM_SetErrlogBufferInfoOverflowCnt(0);

    /* ����ID_OM_ERR_LOG_REPORT_CNF��Ϣ��ACPU OM */
    NAS_EMM_SndAcpuOmErrLogReportCnf(pbuffer, ulTotalLen);

    NAS_LMM_MEM_FREE(pbuffer);

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32 NAS_EMM_IsErrLogNeedRecord(VOS_UINT16 usLevel)
{
     /* Log���عرգ�����Ҫ�ϱ� */
     if (0 == NAS_EMM_GetErrlogCtrlInfoCtrlFlag())
     {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsErrLogNeedRecord1");
        return VOS_FALSE;
     }

     /* ģ��log����usLevel�����û����õ�log�ϱ������usLevel��Ч������Ҫ�ϱ� */
     if ((NAS_EMM_GetErrlogCtrlInfoALMLevel() < usLevel)
      || (LNAS_ERR_LOG_CTRL_LEVEL_NULL == usLevel))
     {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsErrLogNeedRecord2");
        return VOS_FALSE;
     }

     return VOS_TRUE;
}


EMM_OM_ERRLOG_CN_CAUSE_ENUM_UINT16  NAS_LMM_CnCauseProc(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucCnCause)
{
    EMM_OM_ERRLOG_CN_CAUSE_ENUM_UINT16   ulErrId = 0;
    VOS_UINT32 i;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_CnCauseProc!");

    for(i = 0; i < g_astEmmErrlogCnCauseNum; i++)
    {
        if(ucCnCause == g_astEmmErrlogCnCauseMap[i].ulCauseId)
        {
            ulErrId = g_astEmmErrlogCnCauseMap[i].ulErrorlogID;
            break;
        }
    }
    if(g_astEmmErrlogCnCauseNum == i)
    {
        ulErrId = EMM_OM_ERRLOG_CN_CAUSE_OTHERS;
    }

    return ulErrId;
}


VOS_UINT32 NAS_EMM_PutErrLogRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    VOS_UINT32                          ulFreeSize;
    VOS_UINT32                          ulCount;
    OM_RING_ID                          pLnasRingBuffer;

    pLnasRingBuffer = NAS_EMM_GetErrlogBufferInfoRingBuffer();
    if (VOS_NULL_PTR == pLnasRingBuffer)
    {
        return 0;
    }

    /* ���д���RING BUFFER������д�� */
    if (ulbytes > LNAS_RING_BUFFER_SIZE)
    {
        return 0;
    }

    /* ��ȡRING BUFFERʣ��ռ��С */
    ulFreeSize = (VOS_UINT32)OM_RingBufferFreeBytes(pLnasRingBuffer);

    ulCount = NAS_EMM_GetErrlogBufferInfoOverflowCnt();
    /* ���ʣ��ռ䲻��д��Ĵ�С�������RING BUFFER */
    if (ulFreeSize < ulbytes)
    {
        ulCount++;
        NAS_EMM_SetErrlogBufferInfoOverflowCnt(ulCount);

        OM_RingBufferFlush(pLnasRingBuffer);
    }

    /* д��RING BUFFER */
    return (VOS_UINT32)OM_RingBufferPut(pLnasRingBuffer, pbuffer, (VOS_INT)ulbytes);
}




EMM_OM_ERRLOG_EST_RESULT_ENUM_UINT32  NAS_LMM_EstCnfFailRsltProc(LRRC_LNAS_EST_RESULT_ENUM_UINT32 ulLrrcEstCnfRslt)
{
    EMM_OM_ERRLOG_EST_RESULT_ENUM_UINT32   ulErrlogEstRslt = 0;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_EstCnfFailRsltProc!");

    switch(ulLrrcEstCnfRslt)
    {
        case LRRC_EST_DELING:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_DELING;
            break;
        case LRRC_EST_ACCESS_BARRED_MO_CALL:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_ACCESS_BARRED_MO_CALL;
            break;
        case LRRC_EST_ACCESS_BARRED_MO_SIGNAL:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_ACCESS_BARRED_MO_SIGNAL;
            break;
        case LRRC_EST_ACCESS_BARRED_ALL:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_ACCESS_BARRED_ALL;
            break;
        case LRRC_EST_EST_CONN_FAIL:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_EST_CONN_FAIL;
            break;
        case LRRC_EST_CELL_SEARCHING:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_CELL_SEARCHING;
            break;
        case LRRC_EST_ACCESS_BARRED_MT_CALL:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_ACCESS_BARRED_MT_CALL;
            break;
        case LRRC_EST_ACCESS_BARRED_MO_CSFB:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_ACCESS_BARRED_MO_CSFB;
            break;
        case LRRC_EST_ACCESS_BARRED_MO_CALL_AND_CSFB:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_ACCESS_BARRED_MO_CALL_AND_CSFB;
            break;
        default:
             ulErrlogEstRslt = EMM_OM_ERRLOG_EST_RESULT_BUTT;
            break;
    }

    return ulErrlogEstRslt;
}


EMM_OM_ERRLOG_SEND_RSLT_ENUM_UINT32  NAS_LMM_DataCnfFailRsltProc(LRRC_LMM_SEND_RSLT_ENUM_UINT32 ulLrrcDataCnfRslt)
{
    EMM_OM_ERRLOG_SEND_RSLT_ENUM_UINT32   ulErrlogDataCnfRslt = 0;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_DataCnfFailRsltProc!");

    switch(ulLrrcDataCnfRslt)
    {
        case LRRC_LMM_SEND_RSLT_FAILURE_HO:
            ulErrlogDataCnfRslt = EMM_OM_ERRLOG_SEND_RSLT_FAILURE_HO;
            break;
        case LRRC_LMM_SEND_RSLT_FAILURE_CONN_REL:
            ulErrlogDataCnfRslt = EMM_OM_ERRLOG_SEND_RSLT_FAILURE_CONN_REL;
            break;
        case LRRC_LMM_SEND_RSLT_FAILURE_CTRL_NOT_CONN:
            ulErrlogDataCnfRslt = EMM_OM_ERRLOG_SEND_RSLT_FAILURE_CTRL_NOT_CONN;
            break;
        case LRRC_LMM_SEND_RSLT_FAILURE_TXN:
            ulErrlogDataCnfRslt = EMM_OM_ERRLOG_SEND_RSLT_FAILURE_TXN;
            break;
        case LRRC_LMM_SEND_RSLT_FAILURE_RLF:
            ulErrlogDataCnfRslt = EMM_OM_ERRLOG_SEND_RSLT_FAILURE_RLF;
            break;
        default:
            ulErrlogDataCnfRslt = EMM_OM_ERRLOG_SEND_RSLT_BUTT;
            break;
    }

    return ulErrlogDataCnfRslt;
}

VOS_VOID NAS_EMM_AttachErrRecord(
         VOS_VOID*                         pstAttachFail,
         EMM_OM_ERRLOG_TYPE_ENUM_UINT16    enErrType)
{
    EMM_ERR_INFO_ATTACH_RESULT_EVENT_STRU                   stAttachRslt;
    NAS_EMM_CN_ATTACH_REJ_STRU                              *pstCnAttachRej = VOS_NULL_PTR;
    LRRC_LMM_EST_CNF_STRU                                   *pstEstCnfMsg = VOS_NULL_PTR;
    LRRC_LMM_DATA_CNF_STRU                                  *pRrcDataCnf = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_AttachErrRecord!!");
    if(VOS_NULL_PTR == pstAttachFail)
    {
        return;
    }

    /*����attach��ͬ��fail���;�������Ľṹ����*/
    switch(enErrType)
    {
        case EMM_OM_ERRLOG_TYPE_CN_REJ:
            pstCnAttachRej = (NAS_EMM_CN_ATTACH_REJ_STRU*)(VOS_VOID*)pstAttachFail;
            break;
        case EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL:
            pstEstCnfMsg = (LRRC_LMM_EST_CNF_STRU*)(VOS_VOID*)pstAttachFail;
            break;
        case EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL:
            pRrcDataCnf = (LRRC_LMM_DATA_CNF_STRU*)(VOS_VOID*)pstAttachFail;
            break;
        case EMM_OM_ERRLOG_TYPE_TIMEOUT:
        case EMM_OM_ERRLOG_TYPE_LRRC_REL:
            break;
        default:
            NAS_LMM_PUBM_LOG_ERR("NAS_EMM_AttachErrRecord: Err Type");
            return;
    }

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_ATTACH_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_ATTACH_RESULT_EVENT_STRU);

    PS_MEM_SET(&stAttachRslt, 0x00, ulLength);

    /*���attach fail�쳣����ͷ*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stAttachRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_ATTACH_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));
    stAttachRslt.enErrType = enErrType;

    /*lint -e613*/
    /*������attach rej�����attach fail�쳣��ص���Ϣ��Ŀǰ���ܾ�ԭ��ֵ���Լ�attach����*/
    if(EMM_OM_ERRLOG_TYPE_CN_REJ == stAttachRslt.enErrType)
    {
        stAttachRslt.stAttachCnRej.enCnRejCause = NAS_LMM_CnCauseProc(pstCnAttachRej->ucCause);
        stAttachRslt.stAttachCnRej.enReqType = (VOS_UINT16)NAS_EMM_GLO_GetCnAttReqType();
    }
    else if(EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL == stAttachRslt.enErrType)
    {
        stAttachRslt.enEstCnfRslt = NAS_LMM_EstCnfFailRsltProc(pstEstCnfMsg->enResult);
    }
    else if(EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL == stAttachRslt.enErrType)
    {
        stAttachRslt.enDataCnfRslt = NAS_LMM_DataCnfFailRsltProc(pRrcDataCnf->enSendRslt);
    }
    else
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_AttachErrRecord: No item to Save!");
    }
    /*lint +e613*/


    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stAttachRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_AttachErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
    }

    return;
}


EMM_ERR_LOG_TAU_TYPE_ENUM_UINT16  NAS_LMM_TauTypeTrans(NAS_EMM_CN_TAU_TYPE_ENUM_UINT32 ulTauType)
{
    EMM_ERR_LOG_TAU_TYPE_ENUM_UINT16   ulErrTauType = 0;

    switch(ulTauType)
    {
        case NAS_EMM_CN_TAU_TYPE_TA_UPDATING:
            ulErrTauType = EMM_ERR_LOG_TA_UPDATING;
            break;

        case NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING:
            ulErrTauType = EMM_ERR_LOG_COMBINED_TA_LA_UPDATING;
            break;

        case NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI:
            ulErrTauType = EMM_ERR_LOG_COMBINED_TA_LA_WITH_IMSI;
            break;

        case NAS_EMM_CN_TAU_TYPE_PERIODIC_UPDATING:
            if(NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
            {
                ulErrTauType = EMM_ERR_LOG_PS_PERIODIC_UPDATING;
            }
            else if(NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
            {
                ulErrTauType = EMM_ERR_LOG_CS_PS_PERIODIC_UPDATING;
            }
            else
            {

            }
            break;

        default:
            break;
    }

    return ulErrTauType;
}



VOS_VOID NAS_EMM_TAUErrRecord(
         VOS_VOID*                         pstTAUFail,
         EMM_OM_ERRLOG_TYPE_ENUM_UINT16    enErrType)
{
    EMM_ERR_INFO_TAU_RESULT_EVENT_STRU                      stTAURslt;
    NAS_EMM_CN_TAU_REJ_STRU                                 *pstCnTAURej = VOS_NULL_PTR;
    LRRC_LMM_EST_CNF_STRU                                   *pstEstCnfMsg = VOS_NULL_PTR;
    LRRC_LMM_DATA_CNF_STRU                                  *pRrcDataCnf = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_TAUErrRecord!!");
    if(VOS_NULL_PTR == pstTAUFail)
    {
        return;
    }

    /*����attach��ͬ��fail���;�������Ľṹ����*/
    switch(enErrType)
    {
        case EMM_OM_ERRLOG_TYPE_CN_REJ:
            pstCnTAURej = (NAS_EMM_CN_TAU_REJ_STRU*)(VOS_VOID*)pstTAUFail;
            break;
        case EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL:
            pstEstCnfMsg = (LRRC_LMM_EST_CNF_STRU*)(VOS_VOID*)pstTAUFail;
            break;
        case EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL:
            pRrcDataCnf = (LRRC_LMM_DATA_CNF_STRU*)(VOS_VOID*)pstTAUFail;
            break;
        case EMM_OM_ERRLOG_TYPE_TIMEOUT:
        case EMM_OM_ERRLOG_TYPE_LRRC_REL:
            break;
        default:
            NAS_LMM_PUBM_LOG_ERR("NAS_EMM_TAUErrRecord: Err Type");
            return;
    }

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_TAU_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_TAU_RESULT_EVENT_STRU);

    PS_MEM_SET(&stTAURslt, 0x00, ulLength);

    /*���TAU fail�쳣����ͷ*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stTAURslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_TAU_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));
    stTAURslt.enErrType = enErrType;

    /*lint -e613*/
    /*������TAU rej�����TAU fail�쳣��ص���Ϣ��Ŀǰ���ܾ�ԭ��ֵ���Լ�TAU����*/
    if(EMM_OM_ERRLOG_TYPE_CN_REJ == stTAURslt.enErrType)
    {
        stTAURslt.stTauCnRej.enCnRejCause = NAS_LMM_CnCauseProc(pstCnTAURej->ucEMMCause);
        stTAURslt.stTauCnRej.enReqType = NAS_LMM_TauTypeTrans(NAS_EMM_TAU_GetTAUtype());
    }
    else if(EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL == stTAURslt.enErrType)
    {
        stTAURslt.enEstCnfRslt = NAS_LMM_EstCnfFailRsltProc(pstEstCnfMsg->enResult);
    }
    else if(EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL == stTAURslt.enErrType)
    {
        stTAURslt.enDataCnfRslt = NAS_LMM_DataCnfFailRsltProc(pRrcDataCnf->enSendRslt);
    }
    else
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_TAUErrRecord: No item to Save!");
    }
    /*lint +e613*/

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stTAURslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_TAUErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
    }

    return;
}



VOS_VOID NAS_EMM_DetachErrRecord(
        NAS_EMM_CN_DETACH_REQ_MT_STRU       *pstCnDetach)
{
    EMM_ERR_INFO_MT_DETACH_RESULT_EVENT_STRU                stDetachRslt;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_DetachErrRecord!!");
    if(VOS_NULL_PTR == pstCnDetach)
    {
       return;
    }

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_DETACH_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_MT_DETACH_RESULT_EVENT_STRU);

    PS_MEM_SET(&stDetachRslt, 0x00, ulLength);

    /*���Cn Detach fail�쳣����ͷ*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stDetachRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_DETACH_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /*���Cn Detach����ϱ���*/
    /*���������ԭ��ֵ����ֱ����䣬�������ԭ��ֵ�������ó�NULL*/
    if(NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
    {
        stDetachRslt.enCnDetCause = NAS_LMM_CnCauseProc(NAS_EMM_GLO_AD_GetDetEmmCau());
    }
    else
    {
        stDetachRslt.enCnDetCause = EMM_OM_ERRLOG_CN_CAUSE_NULL;
    }
    stDetachRslt.enCnDetReqType = pstCnDetach->ucDetType;

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stDetachRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_DetachErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
    }

    return;
}


VOS_VOID NAS_EMM_NorServiceErrRecord(
            VOS_VOID*                         pstNorServiceFail,
            EMM_OM_ERRLOG_TYPE_ENUM_UINT16    enErrType)

{
    EMM_ERR_INFO_NOR_SERVICE_RESULT_EVENT_STRU              stNorServerRslt;
    NAS_EMM_CN_SER_REJ_STRU                                 *pstCnSerRej = VOS_NULL_PTR;
    LRRC_LMM_EST_CNF_STRU                                   *pstEstCnfMsg = VOS_NULL_PTR;
    LRRC_LMM_DATA_CNF_STRU                                  *pRrcDataCnf = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_NorServiceErrRecord!!");
    if(VOS_NULL_PTR == pstNorServiceFail)
    {
        return;
    }

    /*����service��ͬ��fail���;�������Ľṹ����*/
    switch(enErrType)
    {
        case EMM_OM_ERRLOG_TYPE_CN_REJ:
            pstCnSerRej = (NAS_EMM_CN_SER_REJ_STRU*)(VOS_VOID*)pstNorServiceFail;
            break;
        case EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL:
            pstEstCnfMsg = (LRRC_LMM_EST_CNF_STRU*)(VOS_VOID*)pstNorServiceFail;
            break;
        case EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL:
            pRrcDataCnf = (LRRC_LMM_DATA_CNF_STRU*)(VOS_VOID*)pstNorServiceFail;
            break;
        case EMM_OM_ERRLOG_TYPE_TIMEOUT:
        case EMM_OM_ERRLOG_TYPE_LRRC_REL:
            break;
        default:
            NAS_LMM_PUBM_LOG_ERR("NAS_EMM_NorServiceErrRecord: Err Type");
            return;
    }

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_NOR_SERVICE_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_NOR_SERVICE_RESULT_EVENT_STRU);

    PS_MEM_SET(&stNorServerRslt, 0x00, ulLength);

    /*���Service�쳣����ͷ*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stNorServerRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_NOR_SERVICE_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stNorServerRslt.enErrType = enErrType;

    /*lint -e613*/
    if(EMM_OM_ERRLOG_TYPE_CN_REJ == stNorServerRslt.enErrType)
    {
        stNorServerRslt.stNorServiceCnRej.enCnRejCause =
                                        NAS_LMM_CnCauseProc(pstCnSerRej->ucEMMCause);
    }
    else if(EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL == stNorServerRslt.enErrType)
    {
        stNorServerRslt.enEstCnfRslt = NAS_LMM_EstCnfFailRsltProc(pstEstCnfMsg->enResult);
    }
    else if(EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL == stNorServerRslt.enErrType)
    {
        stNorServerRslt.enDataCnfRslt = NAS_LMM_DataCnfFailRsltProc(pRrcDataCnf->enSendRslt);
    }
    else
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_NorServiceErrRecord: No item need to Save!");
    }
    /*lint +e613*/

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stNorServerRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_NorServiceErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
    }

    return;
}


VOS_VOID NAS_EMM_ExtServiceErrRecord(
        NAS_EMM_CN_CAUSE_ENUM_UINT8                 enCnRejCause,
        EMM_OM_LMM_CSFB_FAIL_CAUSE_ENUM_UINT8       enCsfbFailCause)
{
    EMM_ERR_INFO_EXT_SERVICE_RESULT_EVENT_STRU              stExtServerRslt;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_ExtServiceErrRecord!!");

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_EXT_SERVICE_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_EXT_SERVICE_RESULT_EVENT_STRU);

    PS_MEM_SET(&stExtServerRslt, 0x00, ulLength);

    /*���Service�쳣����ͷ*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stExtServerRslt.stHeader,
                                    VOS_GetModemIDFromPid(PS_PID_MM),
                                    LNAS_OM_ERRLOG_ALM_ID_EXT_SERVICE_FAIL,
                                    usLevel,
                                    VOS_GetSlice(),
                                    (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stExtServerRslt.enCsfbFailCause = enCsfbFailCause;
    stExtServerRslt.enCnRejCause = NAS_LMM_CnCauseProc(enCnRejCause);

    /*
     ���쳣��Ϣд��Buffer��
     ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
    */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stExtServerRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_ExtServiceErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
    }

    return;
}


VOS_VOID NAS_EMM_PagingErrRecord(
        EMM_OM_ERRLOG_PAGING_ENUM_UINT16  enPagingType)
{
    EMM_ERR_INFO_PAGING_RESULT_EVENT_STRU                   stPagingRslt;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PagingErrRecord!!");

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_PAGING_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_PAGING_RESULT_EVENT_STRU);

    PS_MEM_SET(&stPagingRslt, 0x00, ulLength);

    /*���PS IMSI PAGING fail�쳣����ͷ*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stPagingRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_PAGING_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /*���IMSI PAGING����ϱ���*/
    stPagingRslt.enPagingProcess = enPagingType;

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stPagingRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_PagingErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
    }

    return;
}


VOS_VOID NAS_EMM_RatErrRecord(
            EMM_OM_ERRLOG_RAT_ENUM_UINT16           enRatType)
{
    EMM_ERR_INFO_RAT_RESULT_EVENT_STRU                      stRatRslt;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_RatErrRecord!!");

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_PAGING_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_RAT_RESULT_EVENT_STRU);

    PS_MEM_SET(&stRatRslt, 0x00, ulLength);

    /*���rat�쳣����ͷ*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stRatRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_RAT_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /*���RAT����ϱ���*/
    stRatRslt.enRatProcess = enRatType;

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stRatRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_RatErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
    }

    return;
}


VOS_VOID NAS_EMM_LocalDetachErrRecord(
        EMM_ERR_LOG_LOCAL_DETACH_TYPE_ENUM_UINT16       enLocalDetType)
{
    EMM_ERR_INFO_LOCAL_DETACH_RESULT_EVENT_STRU             stLocalDetRslt;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_LocalDetachErrRecord!!");

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_LOCAL_DETACH_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_LOCAL_DETACH_RESULT_EVENT_STRU);

    PS_MEM_SET(&stLocalDetRslt, 0x00, ulLength);

    /*���Cn Detach fail�쳣����ͷ*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stLocalDetRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_LOCAL_DETACH_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /*���Cn Detach����ϱ���*/
    stLocalDetRslt.enLocalDetType = enLocalDetType;
    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stLocalDetRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_LocalDetachErrRecord: Push buffer error.");
    }

    return;
}


VOS_VOID NAS_EMM_AuthCnFailErrRecord(
        EMM_OM_ERRLOG_AUTH_FAIL_ENUM_UINT16       enErrAuthFail)
{
    EMM_ERR_INFO_AUTH_FAIL_RESULT_EVENT_STRU                stAuthCnFailRslt;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_AuthCnFailErrRecord!!");

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_AUTH_REJ);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_AUTH_FAIL_RESULT_EVENT_STRU);

    PS_MEM_SET(&stAuthCnFailRslt, 0x00, ulLength);

    /*���Cn Detach fail�쳣����ͷ*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stAuthCnFailRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_AUTH_REJ,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /*���Cn Detach����ϱ���*/
    stAuthCnFailRslt.enAuthFail = enErrAuthFail;
    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stAuthCnFailRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_AuthCnFailErrRecord: Push buffer error.");
    }

    return;
}
#endif

/*lint +e826*/
/*leixiantiao fix pclint error 826 end*/


VOS_UINT32 NAS_LMM_ExportEmmInfoExcLog(VOS_UINT32* pulExcLogAddr, VOS_UINT32 *pulLeftSpace)
{
    VOS_UINT32                     *pulSaveAddr = pulExcLogAddr;
    VOS_UINT32                      ulSaveSize = 0;
    VOS_UINT32                      ulstNasInfoSize = 0;
    LNAS_EXC_LOG_STRU               stNasInfo;
    VOS_UINT32                      ulLoop;

    if((0 == *pulLeftSpace)||(NAS_EMM_NULL_PTR == pulExcLogAddr))
    {
        return ulSaveSize;
    }
    NAS_LMM_MEM_SET(&stNasInfo, 0, sizeof(LNAS_EXC_LOG_STRU));
    /* �����Ҫ��������Ϣ */
    for(ulLoop = 0; ulLoop < NAS_LMM_PARALLEL_FSM_BUTT; ulLoop++)
    {
        stNasInfo.astCurFsm[ulLoop].enFsmId = NAS_LMM_GetCurFsmAddr(ulLoop)->enFsmId;
        stNasInfo.astCurFsm[ulLoop].enMainState = NAS_LMM_GetCurFsmAddr(ulLoop)->enMainState;
        stNasInfo.astCurFsm[ulLoop].enStaTId = NAS_LMM_GetCurFsmAddr(ulLoop)->enStaTId;
        stNasInfo.astCurFsm[ulLoop].enSubState = NAS_LMM_GetCurFsmAddr(ulLoop)->enSubState;
    }
    stNasInfo.ucRrcConnState = NAS_EMM_GetConnState();
    stNasInfo.ulCurLteState = NAS_EMM_GetCurLteState();
    /*��ȡ��������*/
    ulstNasInfoSize = sizeof(LNAS_EXC_LOG_STRU);
    /* ����EMM״̬���Ͱ�ȫ״̬�� */
    if(ulstNasInfoSize < *pulLeftSpace)
    {
        NAS_LMM_MEM_CPY((VOS_VOID *)pulSaveAddr, &stNasInfo,ulstNasInfoSize);
        ulSaveSize = ulstNasInfoSize;
        *pulLeftSpace -= ulstNasInfoSize;
    }
    else
    {
        NAS_LMM_MEM_CPY((VOS_VOID *)pulSaveAddr, &stNasInfo, *pulLeftSpace);
        ulSaveSize = *pulLeftSpace;
        *pulLeftSpace = 0;
    }
    return ulSaveSize;
}
VOS_VOID  NAS_LMM_SndOmDamPara(VOS_VOID)
{
    NAS_EMM_OM_DAM_PARA_LOG_STRU            *pstMsg = VOS_NULL_PTR;
    NAS_MM_NETWORK_ID_STRU                  *pstAreaInfo;
    NAS_MM_DAM_PLMN_LIST_STRU               *pstDamPlmnList;
    NAS_DAM_IMSI_PLMN_LIST                  *pstImsiPlmnList;

    pstDamPlmnList  = NAS_EMM_GetEmmInfoDamParaPlmnListAddr();
    pstImsiPlmnList = NAS_EMM_GetEmmInfoDamParaImsiPlmnListAddr();
    pstAreaInfo    = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PRESENT_NET_ID);

    pstMsg = (NAS_EMM_OM_DAM_PARA_LOG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_EMM_OM_DAM_PARA_LOG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SndOmDamPara: mem alloc fail!.");
        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_EMM_OM_DAM_PARA_LOG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;

    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_EMM_OM_DAM_PARA_LOG;

    /* CService���ֵ�͵�ǰ���� */
    pstMsg->ulCServiceMax               = NAS_EMM_GetEmmInfoDamParaCserviceMax();
    pstMsg->ulCService                  = NAS_EMM_GetEmmInfoDamParaCserviceCnt();

    /* ��ǰפ����PLMN ID��DAM PLMN LIST */
    NAS_LMM_MEM_SET(&pstMsg->stCampPlmnId, 0, sizeof(NAS_MM_PLMN_ID_STRU));

    if(NAS_EMM_BIT_SLCT == pstAreaInfo->bitOpPlmnId)
    {
        NAS_LMM_MEM_CPY(&pstMsg->stCampPlmnId, &pstAreaInfo->stPlmnId, sizeof(NAS_MM_PLMN_ID_STRU));
    }

    NAS_LMM_MEM_CPY(&pstMsg->stImsiPlmnList, pstImsiPlmnList, sizeof(NAS_DAM_IMSI_PLMN_LIST));

    NAS_LMM_MEM_CPY(&pstMsg->stDamPlmnList, pstDamPlmnList, sizeof(NAS_MM_DAM_PLMN_LIST_STRU));

    /* ���巢�ͣ�PC�����׮�޲������ᷢ����Ϣ������Ӱ��PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;

}
VOS_VOID  NAS_LMM_SndOmCommConfigPara
(
    LNAS_LMM_NV_COMM_CONFIG_PARA_STRU   *pstNvCommPara
)
{
    NAS_EMM_OM_COMM_CONFIG_PARA_LOG_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_EMM_OM_COMM_CONFIG_PARA_LOG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_EMM_OM_COMM_CONFIG_PARA_LOG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_EMM_OM_COMM_CONFIG_PARA_LOG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;

    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_EMM_OM_COMM_CONFIG_PARA_LOG;

    NAS_LMM_MEM_CPY(&pstMsg->stNvCommPara, pstNvCommPara, sizeof(LNAS_LMM_NV_COMM_CONFIG_PARA_STRU));

    /* ���巢�ͣ�PC�����׮�޲������ᷢ����Ϣ������Ӱ��PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;

}
VOS_VOID  NAS_LMM_SndOmRej19Cnt(VOS_VOID)
{
    NAS_EMM_OM_REJ19_CNT_LOG_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_EMM_OM_REJ19_CNT_LOG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_EMM_OM_REJ19_CNT_LOG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_EMM_OM_REJ19_CNT_LOG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;

    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_EMM_OM_REJ19_CNT_LOG;

    /* ��䵱ǰ�ﵽ�ĳ��Դ��� */
    pstMsg->ulRej19AtmptCnt = NAS_EMM_GLO_AD_GetAttRej19AtmpCnt();

    /* ���NV�����õ�����Դ�����ʶ */
    pstMsg->ulRej19AtmptCntFlag = NAS_EMM_GetEmmInfoRej19AtmptCntFlag();

    /* ���巢�ͣ�PC�����׮�޲������ᷢ����Ϣ������Ӱ��PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;

}


/*****************************************************************************
 Function Name   :NAS_LMM_SndDebugInfoInd
 Description     : EMM��ά�ɲ⣬������ǰ״̬
 Input           :
 Output          : None
 Return          :

 History         :
    1.leixiantiao     2014-10-17  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_SndDebugInfoInd(VOS_UINT32 ulFileName, VOS_UINT32 ulLineNo, VOS_UINT16 ucPara1, VOS_UINT16 ucPara2, VOS_UINT16 ucPara3, VOS_UINT16 ucPara4)
{
    NAS_EMM_DBG_INFO_IND_STRU            stMsg = {0};
    NAS_LMM_FSM_STATE_STRU               *pstEmmCurState  = NAS_LMM_GetEmmCurFsmAddr();
    NAS_LMM_FSM_STATE_STRU               *pstSecuCurState = NAS_LMM_GetSecuFsmAddr();

    stMsg.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stMsg.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stMsg.ulSenderPid         = PS_PID_MM;
    stMsg.ulReceiverPid       = PS_PID_MM;
    stMsg.ulLength            = sizeof(NAS_EMM_DBG_INFO_IND_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;

    stMsg.ulMsgId             = ID_NAS_EMM_OM_DEBUG_INFO_LOG;
    stMsg.ulFileName          = ulFileName;
    stMsg.ulLineNo            = ulLineNo;
    stMsg.enEmmMainState      = pstEmmCurState->enMainState ;
    stMsg.enEmmSubState       = pstEmmCurState->enSubState;
    stMsg.enSecuMainState     = pstSecuCurState->enMainState ;
    stMsg.enSecuSubState      = pstSecuCurState->enSubState;
    stMsg.ucPara1             = ucPara1;
    stMsg.ucPara2             = ucPara2;
    stMsg.ucPara3             = ucPara3;
    stMsg.ucPara4             = ucPara4;

    #if (VOS_WIN32 != VOS_OS_VER)
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)&stMsg);
    #endif

        return;
}

#if (FEATURE_ON == FEATURE_PTM)

/*lint -e593*/
VOS_VOID  LNAS_InitErrLogGloInfo(LNAS_ERRLOG_GLO_INFO_STRU *pstErrlogGloInfo)
{
    VOS_CHAR                               *pbuffer;
    OM_RING_ID                              pRingbuffer;

    pstErrlogGloInfo->stCtrlInfo.ucErrLogCtrlFlag         = VOS_FALSE;
    pstErrlogGloInfo->stCtrlInfo.usAlmLevel               = LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL;

    /* ����cache�Ķ�̬�ڴ� , ���ȼ�1����Ϊ����дָ��֮����д��ʱ�����һ���ֽ� */
    pbuffer = (char *)NAS_LMM_MEM_ALLOC(LNAS_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pbuffer)
    {
         pstErrlogGloInfo->stBuffInfo.pstRingBuffer = VOS_NULL_PTR;
         return;
    }

    /* ����OM�Ľӿڣ�������Ķ�̬�ڴ洴��ΪRING BUFFER */
    pRingbuffer = OM_RingBufferCreateEx(pbuffer, LNAS_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pRingbuffer)
    {
        NAS_LMM_MEM_FREE(pbuffer);
    }

    /* ����ringbufferָ�� */
    pstErrlogGloInfo->stBuffInfo.pstRingBuffer = pRingbuffer;

    pstErrlogGloInfo->stBuffInfo.ulOverflowCnt = 0;

    NAS_LMM_RevNvCtrl();

    return;
}
/*lint +e593*/
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

/* end of ��ϵͳ+ģ��+�ļ���.c */