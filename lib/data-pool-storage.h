/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	data_pool_storage.h
 * @brief	data pool storage header
 */
#ifndef DATA_POOL_STORAGE_H
#define DATA_POOL_STORAGE_H
//-----------------------------------------------------------------------------
#include "ipc_protocol.h"
#include <stdbool.h>

int data_pool_set_v1(struct S_AGLCLUSTER_SERVICE_DATA_V1 *data);
int data_pool_get_v1(struct S_AGLCLUSTER_SERVICE_DATA_V1 *data);

bool data_pool_lock(void);
bool data_pool_unlock(void);

//-----------------------------------------------------------------------------
#endif //#ifndef DATA_POOL_STORAGE_H
