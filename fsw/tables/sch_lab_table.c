/************************************************************************
 * NASA Docket No. GSC-19,200-1, and identified as "cFS Draco"
 *
 * Copyright (c) 2023 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

#include "cfe_tbl_filedef.h"
#include "sch_lab_tbl.h"
#include "cfe_sb_api_typedefs.h"

/* cFE core services */
#include "cfe_msgids.h"

/* Mission application message IDs (conditionally included) */
#ifdef HAVE_TO_LAB
#include "to_lab_msgids.h"
#endif

#ifdef HAVE_CI_LAB
#include "ci_lab_msgids.h"
#endif

#ifdef HAVE_CF
#include "cf_msgids.h"
#endif

#ifdef HAVE_APQS_APP
#include "apqs_app_msgids.h"
#endif

/*
** SCH Lab schedule table
**
** TickRate = 100  =>  one tick every 10 ms  =>  PacketRate = 100 means 1 Hz.
** Entries are staggered slightly so the messages don't all burst in the
** same tick.
**
** Entry format: { MsgID, PacketRate, FcnCode }
**   PayloadLength and MessageBuffer default to 0 (no extra payload).
*/
SCH_LAB_ScheduleTable_t Schedule = {
    .TickRate = 100,
    .Config   = {

        /* --- cFE core housekeeping requests (1 Hz, staggered) --- */
        {CFE_SB_MSGID_WRAP_VALUE(CFE_ES_SEND_HK_MID),   100, 0},
        {CFE_SB_MSGID_WRAP_VALUE(CFE_EVS_SEND_HK_MID),   96, 0},
        {CFE_SB_MSGID_WRAP_VALUE(CFE_SB_SEND_HK_MID),    97, 0},
        {CFE_SB_MSGID_WRAP_VALUE(CFE_TBL_SEND_HK_MID),   98, 0},
        {CFE_SB_MSGID_WRAP_VALUE(CFE_TIME_SEND_HK_MID),  99, 0},

        /* --- Application housekeeping requests (1 Hz) --- */
#ifdef HAVE_TO_LAB
        {CFE_SB_MSGID_WRAP_VALUE(TO_LAB_SEND_HK_MID),   100, 0},
#endif

#ifdef HAVE_CI_LAB
        {CFE_SB_MSGID_WRAP_VALUE(CI_LAB_SEND_HK_MID),   100, 0},
#endif

#ifdef HAVE_CF
        {CFE_SB_MSGID_WRAP_VALUE(CF_SEND_HK_MID),       100, 0},
        {CFE_SB_MSGID_WRAP_VALUE(CF_WAKE_UP_MID),        10, 0},
#endif

        /* Sentinel entry — marks end of active entries */
        {CFE_SB_MSGID_RESERVED, 0, 0},
    }
};

CFE_TBL_FILEDEF(Schedule, SCH_LAB.Schedule, Schedule Lab MsgID Table, sch_lab_table.tbl)
