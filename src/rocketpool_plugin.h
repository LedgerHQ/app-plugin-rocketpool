#pragma once

#include "eth_internals.h"
#include "eth_plugin_interface.h"
#include <string.h>

// Number of selectors defined in this plugin. Should match the enum `selector_t`.
#define NUM_SELECTORS 10

// Name of the plugin.
#define PLUGIN_NAME "Rocket Pool"

#define UNEXPECTED_PARAMETER 0xFF

// Enumeration of the different selectors possible.
// Should follow the exact same order as the array declared in main.c
typedef enum {
    DEPOSIT = 0,
    BURN,
    SET_WITHDRAWAL_ADDRESS,
    CONFIRM_WITHDRAWAL_ADDRESS,
    STAKE_RPL_FOR,
    STAKE_RPL,
    UNSTAKE_RPL,
    SWAP_TOKENS,
    SWAP_TO,
    SWAP_FROM
} selector_t;

enum {
    BURN__AMOUNT = 0,
};

enum {
    SET_WITHDRAWAL_ADDRESS__NODE_ADDRESS = 0,
    SET_WITHDRAWAL_ADDRESS__NEW_WITHDRAWAL_ADDRESS,
    SET_WITHDRAWAL_ADDRESS__CONFIRM
};

enum {
    CONFIRM_WITHDRAWAL_ADDRESS__NODE_ADDRESS = 0,
};

enum {
    STAKE_RPL_FOR__NODE_ADDRESS = 0,
    STAKE_RPL_FOR__AMOUNT,
};

enum {
    STAKE_RPL__AMOUNT = 0,
};

enum {
    UNSTAKE_RPL__AMOUNT = 0,
};

enum {
    SWAP_TOKENS__AMOUNT = 0,
};

enum {
    SWAP_TO__UNISWAP_PORTION = 0,
    SWAP_TO__BALANCER_PORTION,
    SWAP_TO__MIN_TOKENS_OUT,
    SWAP_TO__IDEAL_TOKENS_OUT
};

enum {
    SWAP_FROM__UNISWAP_PORTION = 0,
    SWAP_FROM__BALANCER_PORTION,
    SWAP_FROM__MIN_TOKENS_OUT,
    SWAP_FROM__IDEAL_TOKENS_OUT,
    SWAP_FROM__TOKENS_IN
};

extern const uint32_t ROCKETPOOL_SELECTORS[NUM_SELECTORS];

typedef struct burn_context_t {
    uint8_t amount[INT256_LENGTH];
} burn_context_t;

typedef struct set_withdrawal_address_context_t {
    uint8_t node_address[ADDRESS_LENGTH];
    uint8_t new_withdrawal_address[ADDRESS_LENGTH];
    bool confirm;
} set_withdrawal_address_context_t;

typedef struct confirm_withdrawal_address_context_t {
    uint8_t node_address[ADDRESS_LENGTH];
} confirm_withdrawal_address_context_t;

typedef struct stake_rpl_for_context_t {
    uint8_t node_address[ADDRESS_LENGTH];
    uint8_t amount[INT256_LENGTH];
} stake_rpl_for_context_t;

typedef struct stake_rpl_context_t {
    uint8_t amount[INT256_LENGTH];
} stake_rpl_context_t;

typedef struct unstake_rpl_context_t {
    uint8_t amount[INT256_LENGTH];
} unstake_rpl_context_t;

typedef struct swap_tokens_context_t {
    uint8_t amount[INT256_LENGTH];
} swap_tokens_context_t;

typedef struct swap_from_context_t {
    uint8_t amount[INT256_LENGTH];
} swap_from_context_t;

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct context_t {
    // Common context
    selector_t selectorIndex;
    uint8_t num_screens;
    uint8_t next_param;  // Set to be the next param we expect to parse.
    uint16_t offset;     // Offset at which the array or struct starts.
    bool go_to_offset;   // If set, will force the parsing to iterate through parameters until `offset` is reached.

    // Selector specific context
    union {
        struct burn_context_t burn;
        struct set_withdrawal_address_context_t set_withdrawal_address;
        struct confirm_withdrawal_address_context_t confirm_withdrawal_address;
        struct stake_rpl_for_context_t stake_rpl_for;
        struct stake_rpl_context_t stake_rpl;
        struct unstake_rpl_context_t unstake_rpl;
        struct swap_tokens_context_t swap_tokens;
        struct swap_from_context_t swap_from;
    } selector;

} context_t;

// Piece of code that will check that the above structure is not bigger than 5 * 32. Do not remove this check.
_Static_assert(sizeof(context_t) <= 5 * 32, "Structure of parameters too big.");

void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_init_contract(void *parameters);
void handle_finalize(void *parameters);
void handle_provide_token(void *parameters);
void handle_query_contract_id(void *parameters);