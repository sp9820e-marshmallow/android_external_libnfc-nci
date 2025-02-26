/******************************************************************************
 *
 *  Copyright (C) 2010-2014 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/


/******************************************************************************
 *
 *  This is the public interface file for NFA P2P, Broadcom's NFC
 *  application layer for mobile phones.
 *
 ******************************************************************************/
#ifndef NFA_P2P_API_H
#define NFA_P2P_API_H

#include "llcp_api.h"
#include "nfa_api.h"

/*****************************************************************************
**  Constants and data types
*****************************************************************************/

/* NFA P2P Reason of disconnection */
#define NFA_P2P_DISC_REASON_REMOTE_INITIATE     0x00    /* remote initiated to disconnect  */
#define NFA_P2P_DISC_REASON_LOCAL_INITITATE     0x01    /* local initiated to disconnect   */
#define NFA_P2P_DISC_REASON_NO_SERVICE          0x02    /* no service bound in remote      */
#define NFA_P2P_DISC_REASON_REMOTE_REJECT       0x03    /* remote rejected connection      */
#define NFA_P2P_DISC_REASON_FRAME_ERROR         0x04    /* sending or receiving FRMR PDU   */
#define NFA_P2P_DISC_REASON_LLCP_DEACTIVATED    0x05    /* LLCP link deactivated           */
#define NFA_P2P_DISC_REASON_NO_RESOURCE         0x06    /* Out of resource in local device */
#define NFA_P2P_DISC_REASON_NO_INFORMATION      0x80    /* Without information             */
#if (NFC_SEC_NOT_OPEN_INCLUDED == TRUE) /* START_SLSI [S15112001] */
#define NFA_P2P_DISC_REASON_CO_LINK_NOT_SUPPORTED   0x81    /* Peer doesn't support connection-oriented link         */
#define NFA_P2P_DISC_REASON_SSAP_NOT_REG            0x82    /* SSAP is not registered                                */
#define NFA_P2P_DISC_REASON_SN_TOO_LONG             0x83    /* Service Name is too long                              */
#define NFA_P2P_DISC_REASON_INVALID_MIU             0x84    /* Data link MIU shall not be bigger than local link MIU */
#define NFA_P2P_DISC_REASON_BUSY                    0x85    /* There is pending connect request on this reg_sap      */
#endif

/* NFA P2P callback events */
#define NFA_P2P_REG_SERVER_EVT      0x00    /* Server is registered                         */
#define NFA_P2P_REG_CLIENT_EVT      0x01    /* Client is registered                         */
#define NFA_P2P_ACTIVATED_EVT       0x02    /* LLCP Link has been activated                 */
#define NFA_P2P_DEACTIVATED_EVT     0x03    /* LLCP Link has been deactivated               */
#define NFA_P2P_CONN_REQ_EVT        0x04    /* Data link connection request from peer       */
#define NFA_P2P_CONNECTED_EVT       0x05    /* Data link connection has been established    */
#define NFA_P2P_DISC_EVT            0x06    /* Data link connection has been disconnected   */
#define NFA_P2P_DATA_EVT            0x07    /* Data received from peer                      */
#define NFA_P2P_CONGEST_EVT         0x08    /* Status indication of outgoing data           */
#define NFA_P2P_LINK_INFO_EVT       0x09    /* link MIU and Well-Known Service list         */
#define NFA_P2P_SDP_EVT             0x0A    /* Remote SAP of SDP result                     */

typedef UINT8 tNFA_P2P_EVT;

/* NFA allocates a SAP for server */
#define NFA_P2P_ANY_SAP         LLCP_INVALID_SAP
#define NFA_P2P_INVALID_SAP     LLCP_INVALID_SAP

/* Recommanded MIU's for connection-oriented */
#define NFA_P2P_MIU_1           (NCI_NFC_DEP_MAX_DATA - LLCP_PDU_HEADER_SIZE - LLCP_SEQUENCE_SIZE)
#define NFA_P2P_MIU_2           (2*NCI_NFC_DEP_MAX_DATA - LLCP_PDU_HEADER_SIZE - LLCP_SEQUENCE_SIZE)
#define NFA_P2P_MIU_3           (3*NCI_NFC_DEP_MAX_DATA - LLCP_PDU_HEADER_SIZE - LLCP_SEQUENCE_SIZE)
#define NFA_P2P_MIU_8           (8*NCI_NFC_DEP_MAX_DATA - LLCP_PDU_HEADER_SIZE - LLCP_SEQUENCE_SIZE)

#define NFA_P2P_LLINK_TYPE      LLCP_LINK_TYPE_LOGICAL_DATA_LINK
#define NFA_P2P_DLINK_TYPE      LLCP_LINK_TYPE_DATA_LINK_CONNECTION
typedef UINT8 tNFA_P2P_LINK_TYPE;

/* Data for NFA_P2P_REG_SERVER_EVT */
typedef struct
{
    tNFA_HANDLE     server_handle;     /* NFA_HANDLE_INVALID if failed */
    char            service_name[LLCP_MAX_SN_LEN + 1];
    UINT8           server_sap;
} tNFA_P2P_REG_SERVER;

/* Data for NFA_P2P_REG_CLIENT_EVT */
typedef struct
{
    tNFA_HANDLE     client_handle;     /* NFA_HANDLE_INVALID if failed */
} tNFA_P2P_REG_CLIENT;

/* Data for NFA_P2P_ACTIVATED_EVT */
typedef struct
{
    tNFA_HANDLE     handle;
    UINT16          local_link_miu;
    UINT16          remote_link_miu;
} tNFA_P2P_ACTIVATED;

/* Data for NFA_P2P_DEACTIVATED_EVT */
typedef struct
{
    tNFA_HANDLE     handle;
} tNFA_P2P_DEACTIVATED;

/* Data for NFA_P2P_CONN_REQ_EVT */
typedef struct
{
    tNFA_HANDLE     server_handle;
    tNFA_HANDLE     conn_handle;
    UINT8           remote_sap;
    UINT16          remote_miu;
    UINT8           remote_rw;
} tNFA_P2P_CONN_REQ;

/* Data for NFA_P2P_CONNECTED_EVT */
typedef struct
{
    tNFA_HANDLE     client_handle;
    tNFA_HANDLE     conn_handle;
    UINT8           remote_sap;
    UINT16          remote_miu;
    UINT8           remote_rw;
} tNFA_P2P_CONN;

/* Data for NFA_P2P_DISC_EVT */
typedef struct
{
    tNFA_HANDLE     handle;
    UINT8           reason;
} tNFA_P2P_DISC;

/* Data for NFA_P2P_DATA_EVT */
typedef struct
{
    tNFA_HANDLE     handle;
    UINT8           remote_sap;
    tNFA_P2P_LINK_TYPE link_type;
} tNFA_P2P_DATA;

/* Data for NFA_P2P_CONGEST_EVT */
typedef struct
{
    tNFA_HANDLE     handle;
    BOOLEAN         is_congested;
    tNFA_P2P_LINK_TYPE link_type;
} tNFA_P2P_CONGEST;

/* Data for NFA_P2P_LINK_INFO_EVT */
typedef struct
{
    tNFA_HANDLE     handle;
    UINT16          wks;            /* well-known service */
    UINT16          local_link_miu;
    UINT16          remote_link_miu;
} tNFA_P2P_LINK_INFO;

/* Data for NFA_P2P_SDP_EVT */
typedef struct
{
    tNFA_HANDLE     handle;
    UINT8           remote_sap;     /* 0x00 if failed */
} tNFA_P2P_SDP;

/* Union of all P2P callback structures */
typedef union
{
    tNFA_P2P_REG_SERVER     reg_server;     /* NFA_P2P_REG_SERVER_EVT   */
    tNFA_P2P_REG_CLIENT     reg_client;     /* NFA_P2P_REG_CLIENT_EVT   */
    tNFA_P2P_ACTIVATED      activated;      /* NFA_P2P_ACTIVATED_EVT    */
    tNFA_P2P_DEACTIVATED    deactivated;    /* NFA_P2P_DEACTIVATED_EVT  */
    tNFA_P2P_CONN_REQ       conn_req;       /* NFA_P2P_CONN_REQ_EVT     */
    tNFA_P2P_CONN           connected;      /* NFA_P2P_CONNECTED_EVT    */
    tNFA_P2P_DISC           disc;           /* NFA_P2P_DISC_EVT         */
    tNFA_P2P_DATA           data;           /* NFA_P2P_DATA_EVT         */
    tNFA_P2P_CONGEST        congest;        /* NFA_P2P_CONGEST_EVT      */
    tNFA_P2P_LINK_INFO      link_info;      /* NFA_P2P_LINK_INFO_EVT    */
    tNFA_P2P_SDP            sdp;            /* NFA_P2P_SDP_EVT          */
} tNFA_P2P_EVT_DATA;

/* NFA P2P callback */
typedef void (tNFA_P2P_CBACK)(tNFA_P2P_EVT event, tNFA_P2P_EVT_DATA *p_data);

/*****************************************************************************
**  External Function Declarations
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**
** Function         NFA_P2pRegisterServer
**
** Description      This function is called to listen to a SAP as server on LLCP.
**
**                  NFA_P2P_REG_SERVER_EVT will be returned with status and handle.
**
**                  If server_sap is set to NFA_P2P_ANY_SAP, then NFA will allocate
**                  a SAP between LLCP_LOWER_BOUND_SDP_SAP and LLCP_UPPER_BOUND_SDP_SAP
**                  Otherwise, server_sap must be between (LLCP_SDP_SAP + 1) and
**                  LLCP_UPPER_BOUND_SDP_SAP
**
**                  link_type : NFA_P2P_LLINK_TYPE and/or NFA_P2P_DLINK_TYPE
**
** Note:            If RF discovery is started, NFA_StopRfDiscovery()/NFA_RF_DISCOVERY_STOPPED_EVT
**                  should happen before calling this function
**
** Returns          NFA_STATUS_OK if successfully initiated
**                  NFA_STATUS_FAILED otherwise
**
*******************************************************************************/
NFC_API extern tNFA_STATUS NFA_P2pRegisterServer (UINT8              server_sap,
                                                  tNFA_P2P_LINK_TYPE link_type,
                                                  char              *p_service_name,
                                                  tNFA_P2P_CBACK    *p_cback);

/*******************************************************************************
**
** Function         NFA_P2pRegisterClient
**
** Description      This function is called to register a client service on LLCP.
**
**                  NFA_P2P_REG_CLIENT_EVT will be returned with status and handle.
**
**                  link_type : NFA_P2P_LLINK_TYPE and/or NFA_P2P_DLINK_TYPE
**
** Returns          NFA_STATUS_OK if successfully initiated
**                  NFA_STATUS_FAILED otherwise
**
*******************************************************************************/
NFC_API extern tNFA_STATUS NFA_P2pRegisterClient (tNFA_P2P_LINK_TYPE link_type,
                                                  tNFA_P2P_CBACK *p_cback);

/*******************************************************************************
**
** Function         NFA_P2pDeregister
**
** Description      This function is called to stop listening to a SAP as server
**                  or stop client service on LLCP.
**
** Note:            If this function is called to de-register a server and RF discovery
**                  is started, NFA_StopRfDiscovery()/NFA_RF_DISCOVERY_STOPPED_EVT
**                  should happen before calling this function
**
** Returns          NFA_STATUS_OK if successfully initiated
**                  NFA_STATUS_BAD_HANDLE if handle is not valid
**                  NFA_STATUS_FAILED otherwise
**
*******************************************************************************/
NFC_API extern tNFA_STATUS NFA_P2pDeregister (tNFA_HANDLE handle);

/*******************************************************************************
**
** Function         NFA_P2pAcceptConn
**
** Description      This function is called to accept a request of data link
**                  connection to a listening SAP on LLCP after receiving
**                  NFA_P2P_CONN_REQ_EVT.
**
** Returns          NFA_STATUS_OK if successfully initiated
**                  NFA_STATUS_BAD_HANDLE if handle is not valid
**                  NFA_STATUS_FAILED otherwise
**
*******************************************************************************/
NFC_API extern tNFA_STATUS NFA_P2pAcceptConn (tNFA_HANDLE conn_handle,
                                              UINT16      miu,
                                              UINT8       rw);

/*******************************************************************************
**
** Function         NFA_P2pRejectConn
**
** Description      This function is called to reject a request of data link
**                  connection to a listening SAP on LLCP after receiving
**                  NFA_P2P_CONN_REQ_EVT.
**
** Returns          NFA_STATUS_OK if successfully initiated
**                  NFA_STATUS_BAD_HANDLE if handle is not valid
**                  NFA_STATUS_FAILED otherwise
**
*******************************************************************************/
NFC_API extern tNFA_STATUS NFA_P2pRejectConn (tNFA_HANDLE conn_handle);

/*******************************************************************************
**
** Function         NFA_P2pDisconnect
**
** Description      This function is called to disconnect an existing or
**                  connecting data link connection.
**
**                  discard any pending data on data link connection if flush is set to TRUE
**
**                  NFA_P2P_DISC_EVT will be returned after data link connection is disconnected
**
** Returns          NFA_STATUS_OK if successfully initiated
**                  NFA_STATUS_BAD_HANDLE if handle is not valid
**                  NFA_STATUS_FAILED otherwise
**
*******************************************************************************/
NFC_API extern tNFA_STATUS NFA_P2pDisconnect (tNFA_HANDLE conn_handle,
                                              BOOLEAN     flush);

/*******************************************************************************
**
** Function         NFA_P2pConnectByName
**
** Description      This function is called to create a connection-oriented transport
**                  by a service name.
**                  NFA_P2P_CONNECTED_EVT if success
**                  NFA_P2P_DISC_EVT if failed
**
** Returns          NFA_STATUS_OK if successfully initiated
**                  NFA_STATUS_BAD_HANDLE if client is not registered
**                  NFA_STATUS_FAILED otherwise
**
*******************************************************************************/
NFC_API extern tNFA_STATUS NFA_P2pConnectByName (tNFA_HANDLE client_handle,
                                                 char       *p_service_name,
                                                 UINT16      miu,
                                                 UINT8       rw);

/*******************************************************************************
**
** Function         NFA_P2pConnectBySap
**
** Description      This function is called to create a connection-oriented transport
**                  by a SAP.
**                  NFA_P2P_CONNECTED_EVT if success
**                  NFA_P2P_DISC_EVT if failed
**
** Returns          NFA_STATUS_OK if successfully initiated
**                  NFA_STATUS_BAD_HANDLE if client is not registered
**                  NFA_STATUS_FAILED otherwise
**
*******************************************************************************/
NFC_API extern tNFA_STATUS NFA_P2pConnectBySap (tNFA_HANDLE client_handle,
                                                UINT8       dsap,
                                                UINT16      miu,
                                                UINT8       rw);

/*******************************************************************************
**
** Function         NFA_P2pSendUI
**
** Description      This function is called to send data on connectionless
**                  transport.
**
** Returns          NFA_STATUS_OK if successfully initiated
**                  NFA_STATUS_BAD_HANDLE if handle is not valid
**                  NFA_STATUS_BAD_LENGTH if data length is more than remote link MIU
**                  NFA_STATUS_CONGESTED  if congested
**                  NFA_STATUS_FAILED otherwise
**
*******************************************************************************/
NFC_API extern tNFA_STATUS NFA_P2pSendUI (tNFA_HANDLE handle,
                                          UINT8       dsap,
                                          UINT16      length,
                                          UINT8      *p_data);

/*******************************************************************************
**
** Function         NFA_P2pReadUI
**
** Description      This function is called to read data on connectionless
**                  transport when receiving NFA_P2P_DATA_EVT with NFA_P2P_LLINK_TYPE.
**
**                  - Remote SAP who sent UI PDU is returned.
**                  - Information of UI PDU up to max_data_len is copied into p_data.
**                  - If more information of UI PDU or more UI PDU in queue then more
**                    is returned to TRUE.
**                  - Information of next UI PDU is not concatenated.
**
** Returns          NFA_STATUS_OK if successfully initiated
**                  NFA_STATUS_BAD_HANDLE if handle is not valid
**
*******************************************************************************/
NFC_API extern tNFA_STATUS NFA_P2pReadUI (tNFA_HANDLE handle,
                                          UINT32      max_data_len,
                                          UINT8       *p_remote_sap,
                                          UINT32      *p_data_len,
                                          UINT8       *p_data,
                                          BOOLEAN     *p_more);

/*******************************************************************************
**
** Function         NFA_P2pFlushUI
**
** Description      This function is called to flush data on connectionless
**                  transport.
**
** Returns          NFA_STATUS_OK if successfully initiated
**                  NFA_STATUS_BAD_HANDLE if handle is not valid
**
*******************************************************************************/
NFC_API extern tNFA_STATUS NFA_P2pFlushUI (tNFA_HANDLE handle,
                                           UINT32      *p_length);

/*******************************************************************************
**
** Function         NFA_P2pSendData
**
** Description      This function is called to send data on connection-oriented
**                  transport.
**
** Returns          NFA_STATUS_OK if successfully initiated
**                  NFA_STATUS_BAD_HANDLE if handle is not valid
**                  NFA_STATUS_BAD_LENGTH if data length is more than remote MIU
**                  NFA_STATUS_CONGESTED  if congested
**                  NFA_STATUS_FAILED otherwise
**
*******************************************************************************/
NFC_API extern tNFA_STATUS NFA_P2pSendData (tNFA_HANDLE conn_handle,
                                            UINT16      length,
                                            UINT8      *p_data);

/*******************************************************************************
**
** Function         NFA_P2pReadData
**
** Description      This function is called to read data on connection-oriented
**                  transport when receiving NFA_P2P_DATA_EVT with NFA_P2P_DLINK_TYPE.
**
**                  - Information of I PDU is copied into p_data up to max_data_len.
**                  - If more information of I PDU or more I PDU in queue, then more
**                    is returned to TRUE.
**                  - Information of next I PDU is not concatenated.
**
** Returns          NFA_STATUS_OK if successfully initiated
**                  NFA_STATUS_BAD_HANDLE if handle is not valid
**
*******************************************************************************/
NFC_API extern tNFA_STATUS NFA_P2pReadData (tNFA_HANDLE handle,
                                            UINT32      max_data_len,
                                            UINT32      *p_data_len,
                                            UINT8       *p_data,
                                            BOOLEAN     *p_more);

/*******************************************************************************
**
** Function         NFA_P2pFlushData
**
** Description      This function is called to flush data on connection-oriented
**                  transport.
**
** Returns          NFA_STATUS_OK if successfully initiated
**                  NFA_STATUS_BAD_HANDLE if handle is not valid
**
*******************************************************************************/
NFC_API extern tNFA_STATUS NFA_P2pFlushData (tNFA_HANDLE handle,
                                             UINT32      *p_length);

/*******************************************************************************
**
** Function         NFA_P2pSetLocalBusy
**
** Description      This function is called to stop or resume incoming data on
**                  connection-oriented transport.
**
** Returns          NFA_STATUS_OK if successfully initiated
**                  NFA_STATUS_BAD_HANDLE if handle is not valid
**                  NFA_STATUS_FAILED otherwise
**
*******************************************************************************/
NFC_API extern tNFA_STATUS NFA_P2pSetLocalBusy (tNFA_HANDLE conn_handle,
                                                BOOLEAN     is_busy);

/*******************************************************************************
**
** Function         NFA_P2pGetLinkInfo
**
** Description      This function is called to get local/remote link MIU and
**                  Well-Known Service list encoded as a 16-bit field of connected LLCP.
**                  NFA_P2P_LINK_INFO_EVT will be returned.
**
** Returns          NFA_STATUS_OK if successfully initiated
**                  NFA_STATUS_BAD_HANDLE if server or client is not registered
**                  NFA_STATUS_FAILED otherwise
**
*******************************************************************************/
NFC_API extern tNFA_STATUS NFA_P2pGetLinkInfo (tNFA_HANDLE handle);

/*******************************************************************************
**
** Function         NFA_P2pGetRemoteSap
**
** Description      This function is called to get SAP associated by service name
**                  on connected remote LLCP.
**                  NFA_P2P_SDP_EVT will be returned.
**
** Returns          NFA_STATUS_OK if successfully initiated
**                  NFA_STATUS_BAD_HANDLE if server or client is not registered
**                  NFA_STATUS_FAILED otherwise
**
*******************************************************************************/
NFC_API extern tNFA_STATUS NFA_P2pGetRemoteSap (tNFA_HANDLE handle,
                                                char       *p_service_name);

/*******************************************************************************
**
** Function         NFA_P2pSetLLCPConfig
**
** Description      This function is called to change LLCP config parameters.
**                  Application must call while LLCP is not activated.
**
**                  Parameters descriptions (default value)
**                  - Local Link MIU (LLCP_MIU)
**                  - Option parameter (LLCP_OPT_VALUE)
**                  - Response Waiting Time Index (LLCP_WAITING_TIME)
**                  - Local Link Timeout (LLCP_LTO_VALUE)
**                  - Inactivity Timeout as initiator role (LLCP_INIT_INACTIVITY_TIMEOUT)
**                  - Inactivity Timeout as target role (LLCP_TARGET_INACTIVITY_TIMEOUT)
**                  - Delay SYMM response (LLCP_DELAY_RESP_TIME)
**                  - Data link connection timeout (LLCP_DATA_LINK_CONNECTION_TOUT)
**                  - Delay timeout to send first PDU as initiator (LLCP_DELAY_TIME_TO_SEND_FIRST_PDU)
**
** Returns          NFA_STATUS_OK if successfully initiated
**                  NFA_STATUS_FAILED otherwise
**
*******************************************************************************/
NFC_API extern tNFA_STATUS NFA_P2pSetLLCPConfig (UINT16 link_miu,
                                                 UINT8  opt,
                                                 UINT8  wt,
                                                 UINT16 link_timeout,
                                                 UINT16 inact_timeout_init,
                                                 UINT16 inact_timeout_target,
                                                 UINT16 symm_delay,
                                                 UINT16 data_link_timeout,
                                                 UINT16 delay_first_pdu_timeout);

/*******************************************************************************
**
** Function         NFA_P2pGetLLCPConfig
**
** Description      This function is called to read LLCP config parameters.
**
**                  Parameters descriptions
**                  - Local Link MIU
**                  - Option parameter
**                  - Response Waiting Time Index
**                  - Local Link Timeout
**                  - Inactivity Timeout as initiator role
**                  - Inactivity Timeout as target role
**                  - Delay SYMM response
**                  - Data link connection timeout
**                  - Delay timeout to send first PDU as initiator
**
** Returns          None
**
*******************************************************************************/
NFC_API extern void NFA_P2pGetLLCPConfig (UINT16 *p_link_miu,
                                          UINT8  *p_opt,
                                          UINT8  *p_wt,
                                          UINT16 *p_link_timeout,
                                          UINT16 *p_inact_timeout_init,
                                          UINT16 *p_inact_timeout_target,
                                          UINT16 *p_symm_delay,
                                          UINT16 *p_data_link_timeout,
                                          UINT16 *p_delay_first_pdu_timeout);

/*******************************************************************************
**
** Function         NFA_P2pSetTraceLevel
**
** Description      This function sets the trace level for P2P.  If called with
**                  a value of 0xFF, it simply returns the current trace level.
**
** Returns          The new or current trace level
**
*******************************************************************************/
NFC_API extern UINT8 NFA_P2pSetTraceLevel (UINT8 new_level);

#ifdef __cplusplus
}
#endif

#endif /* NFA_P2P_API_H */
