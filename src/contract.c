/*******************************************************************************
 *   Ethereum 2 Deposit Application
 *   (c) 2020 Ledger
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#include <stdint.h>
#include "rocketpool_plugin.h"

// List of selectors supported by this plugin.
static const uint32_t DEPOSIT_SELECTOR = 0xd0e30db0;
static const uint32_t BURN_SELECTOR = 0x42966c68;
static const uint32_t SET_WITHDRAWAL_ADDRESS_SELECTOR = 0xa543ccea;
static const uint32_t CONFIRM_WITHDRAWAL_ADDRESS_SELECTOR = 0xbd439126;
static const uint32_t STAKE_RPL_FOR_SELECTOR = 0xcb1c8321;
static const uint32_t STAKE_RPL_SELECTOR = 0x3e200d4b;
static const uint32_t UNSTAKE_RPL_SELECTOR = 0x6b088d5c;
static const uint32_t SWAP_TOKENS_SELECTOR = 0xfe784eaa;
static const uint32_t SWAP_TO_SELECTOR = 0x55362f4d;
static const uint32_t SWAP_FROM_SELECTOR = 0xa824ae8b;

// Array of all the different Rocket Pool selectors. Make sure this follows the same order as the
// enum defined in `rocketpool_plugin.h`
const uint32_t ROCKETPOOL_SELECTORS[NUM_SELECTORS] = {DEPOSIT_SELECTOR,
                                                      BURN_SELECTOR,
                                                      SET_WITHDRAWAL_ADDRESS_SELECTOR,
                                                      CONFIRM_WITHDRAWAL_ADDRESS_SELECTOR,
                                                      STAKE_RPL_FOR_SELECTOR,
                                                      STAKE_RPL_SELECTOR,
                                                      UNSTAKE_RPL_SELECTOR,
                                                      SWAP_TOKENS_SELECTOR,
                                                      SWAP_TO_SELECTOR,
                                                      SWAP_FROM_SELECTOR};
