#include "rocketpool_plugin.h"

static void handle_burn(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case BURN__AMOUNT:
            copy_parameter(context->selector.burn.amount,
                           msg->parameter,
                           sizeof(context->selector.burn.amount));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_set_withdrawal_address(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case SET_WITHDRAWAL_ADDRESS__NODE_ADDRESS:
            copy_address(context->selector.set_withdrawal_address.node_address,
                         msg->parameter,
                         sizeof(context->selector.set_withdrawal_address.node_address));
            context->next_param = SET_WITHDRAWAL_ADDRESS__NEW_WITHDRAWAL_ADDRESS;
            break;
        case SET_WITHDRAWAL_ADDRESS__NEW_WITHDRAWAL_ADDRESS:
            copy_address(context->selector.set_withdrawal_address.new_withdrawal_address,
                         msg->parameter,
                         sizeof(context->selector.set_withdrawal_address.new_withdrawal_address));
            context->next_param = SET_WITHDRAWAL_ADDRESS__CONFIRM;
            break;
        case SET_WITHDRAWAL_ADDRESS__CONFIRM:
            copy_parameter(context->selector.set_withdrawal_address.confirm,
                           msg->parameter,
                           sizeof(context->selector.set_withdrawal_address.confirm));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_confirm_withdrawal_address(ethPluginProvideParameter_t *msg,
                                              context_t *context) {
    switch (context->next_param) {
        case CONFIRM_WITHDRAWAL_ADDRESS__NODE_ADDRESS:
            copy_address(context->selector.confirm_withdrawal_address.node_address,
                         msg->parameter,
                         sizeof(context->selector.confirm_withdrawal_address.node_address));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_stake_rpl_for(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case STAKE_RPL_FOR__NODE_ADDRESS:
            copy_address(context->selector.stake_rpl_for.node_address,
                         msg->parameter,
                         sizeof(context->selector.stake_rpl_for.node_address));
            context->next_param = STAKE_RPL_FOR__AMOUNT;
            break;
        case STAKE_RPL_FOR__AMOUNT:
            copy_parameter(context->selector.stake_rpl_for.amount,
                           msg->parameter,
                           sizeof(context->selector.stake_rpl_for.amount));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_stake_rpl(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case STAKE_RPL__AMOUNT:
            copy_parameter(context->selector.stake_rpl.amount,
                           msg->parameter,
                           sizeof(context->selector.stake_rpl.amount));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_unstake_rpl(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case UNSTAKE_RPL__AMOUNT:
            copy_parameter(context->selector.unstake_rpl.amount,
                           msg->parameter,
                           sizeof(context->selector.unstake_rpl.amount));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_swap_tokens(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case SWAP_TOKENS__AMOUNT:
            copy_parameter(context->selector.swap_tokens.amount,
                           msg->parameter,
                           sizeof(context->selector.swap_tokens.amount));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_swap_to(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case SWAP_TO__UNISWAP_PORTION:
        case SWAP_TO__BALANCER_PORTION:
        case SWAP_TO__MIN_TOKENS_OUT:
        case SWAP_TO__IDEAL_TOKENS_OUT:
            // Skip all these
            context->next_param++;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_swap_from(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case SWAP_FROM__UNISWAP_PORTION:
        case SWAP_FROM__BALANCER_PORTION:
        case SWAP_FROM__MIN_TOKENS_OUT:
        case SWAP_FROM__IDEAL_TOKENS_OUT:
            // Skip all these
            context->next_param++;
            break;
        case SWAP_FROM__TOKENS_IN:
            copy_parameter(context->selector.swap_from.amount,
                           msg->parameter,
                           sizeof(context->selector.swap_from.amount));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_provide_parameter(void *parameters) {
    ethPluginProvideParameter_t *msg = (ethPluginProvideParameter_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    // We use `%.*H`: it's a utility function to print bytes. You first give
    // the number of bytes you wish to print (in this case, `PARAMETER_LENGTH`) and then
    // the address (here `msg->parameter`).
    PRINTF("plugin provide parameter: offset %d\nBytes: %.*H\n",
           msg->parameterOffset,
           PARAMETER_LENGTH,
           msg->parameter);

    msg->result = ETH_PLUGIN_RESULT_OK;

    switch (context->selectorIndex) {
        case DEPOSIT:
            // No parameters for deposit
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
        case BURN:
            handle_burn(msg, context);
            break;
        case SET_WITHDRAWAL_ADDRESS:
            handle_set_withdrawal_address(msg, context);
            break;
        case CONFIRM_WITHDRAWAL_ADDRESS:
            handle_confirm_withdrawal_address(msg, context);
            break;
        case STAKE_RPL_FOR:
            handle_stake_rpl_for(msg, context);
            break;
        case STAKE_RPL:
            handle_stake_rpl(msg, context);
            break;
        case UNSTAKE_RPL:
            handle_unstake_rpl(msg, context);
            break;
        case SWAP_TOKENS:
            handle_swap_tokens(msg, context);
            break;
        case SWAP_TO:
            handle_swap_to(msg, context);
            break;
        case SWAP_FROM:
            handle_swap_from(msg, context);
            break;
        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}