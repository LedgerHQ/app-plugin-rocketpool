#include "rocketpool_plugin.h"

// Called once to init.
void handle_init_contract(ethPluginInitContract_t *msg) {
    // Make sure we are running a compatible version.
    if (msg->interfaceVersion != ETH_PLUGIN_INTERFACE_VERSION_LATEST) {
        // If not the case, return the `UNAVAILABLE` status.
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }

    // Double check that the `context_t` struct is not bigger than the maximum size (defined by
    // `msg->pluginContextLength`).
    if (msg->pluginContextLength < sizeof(context_t)) {
        PRINTF("Plugin parameters structure is bigger than allowed size\n");
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    context_t *context = (context_t *) msg->pluginContext;

    // Initialize the context (to 0).
    memset(context, 0, sizeof(*context));

    uint32_t selector = U4BE(msg->selector, 0);
    if (!find_selector(selector, ROCKETPOOL_SELECTORS, NUM_SELECTORS, &context->selectorIndex)) {
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }

    // Set `next_param` to be the first field we expect to parse.
    switch (context->selectorIndex) {
        case DEPOSIT:
            context->next_param = UNEXPECTED_PARAMETER;
            context->num_screens = 1;
            break;
        case BURN:
            context->next_param = BURN__AMOUNT;
            context->num_screens = 1;
            break;
        case SET_WITHDRAWAL_ADDRESS:
            context->next_param = SET_WITHDRAWAL_ADDRESS__NODE_ADDRESS;
            context->num_screens = 3;
            break;
        case CONFIRM_WITHDRAWAL_ADDRESS:
            context->next_param = CONFIRM_WITHDRAWAL_ADDRESS__NODE_ADDRESS;
            context->num_screens = 1;
            break;
        case STAKE_RPL_FOR:
            context->next_param = STAKE_RPL_FOR__NODE_ADDRESS;
            context->num_screens = 2;
            break;
        case STAKE_RPL:
            context->next_param = STAKE_RPL__AMOUNT;
            context->num_screens = 1;
            break;
        case UNSTAKE_RPL:
            context->next_param = UNSTAKE_RPL__AMOUNT;
            context->num_screens = 1;
            break;
        case SWAP_TOKENS:
            context->next_param = SWAP_TOKENS__AMOUNT;
            context->num_screens = 1;
            break;
        case SWAP_TO:
            context->next_param = SWAP_TO__UNISWAP_PORTION;
            context->num_screens = 1;
            break;
        case SWAP_FROM:
            context->next_param = SWAP_FROM__UNISWAP_PORTION;
            context->num_screens = 1;
            break;
        // Keep this
        default:
            PRINTF("Missing selectorIndex: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    // Return valid status.
    msg->result = ETH_PLUGIN_RESULT_OK;
}
