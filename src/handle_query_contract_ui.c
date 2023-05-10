#include "rocketpool_plugin.h"

void handle_deposit_ui(ethQueryContractUI_t *msg, context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Amount", msg->titleLength);

            const uint8_t *eth_amount = msg->pluginSharedRO->txContent->value.value;
            uint8_t eth_amount_size = msg->pluginSharedRO->txContent->value.length;

            // Converts the uint256 number located in `eth_amount` to its string representation and
            // copies this to `msg->msg`.
            amountToString(eth_amount,
                           eth_amount_size,
                           WEI_TO_ETHER,
                           "ETH",
                           msg->msg,
                           msg->msgLength);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}

void handle_burn_ui(ethQueryContractUI_t *msg, context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Amount", msg->titleLength);

            const uint8_t *reth_amount = context->selector.burn.amount;
            amountToString(reth_amount,
                           INT256_LENGTH,
                           WEI_TO_ETHER,
                           "rETH",
                           msg->msg,
                           msg->msgLength);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}

void handle_set_withdrawal_address_ui(ethQueryContractUI_t *msg, context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Node Addr", msg->titleLength);

            // Prefix the address with `0x`.
            msg->msg[0] = '0';
            msg->msg[1] = 'x';

            getEthAddressStringFromBinary(
                context->selector.set_withdrawal_address.node_address,
                msg->msg + 2,  // +2 here because we've already prefixed with '0x'.
                msg->pluginSharedRW->sha3,
                0);
            break;
        case 1:
            strlcpy(msg->title, "New Withdr Addr", msg->titleLength);

            // Prefix the address with `0x`.
            msg->msg[0] = '0';
            msg->msg[1] = 'x';

            getEthAddressStringFromBinary(
                context->selector.set_withdrawal_address.new_withdrawal_address,
                msg->msg + 2,  // +2 here because we've already prefixed with '0x'.
                msg->pluginSharedRW->sha3,
                0);
            break;
        case 2:
            strlcpy(msg->title, "Confirm", msg->titleLength);

            if (context->selector.set_withdrawal_address.confirm) {
                strlcpy(msg->msg, "Yes", msg->titleLength);
            } else {
                strlcpy(msg->msg, "No", msg->titleLength);
            }
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}

void handle_confirm_withdrawal_address_ui(ethQueryContractUI_t *msg, context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Node Addr", msg->titleLength);

            // Prefix the address with `0x`.
            msg->msg[0] = '0';
            msg->msg[1] = 'x';

            getEthAddressStringFromBinary(
                context->selector.confirm_withdrawal_address.node_address,
                msg->msg + 2,  // +2 here because we've already prefixed with '0x'.
                msg->pluginSharedRW->sha3,
                0);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}

void handle_stake_rpl_for_ui(ethQueryContractUI_t *msg, context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Node Addr", msg->titleLength);

            // Prefix the address with `0x`.
            msg->msg[0] = '0';
            msg->msg[1] = 'x';

            getEthAddressStringFromBinary(
                context->selector.confirm_withdrawal_address.node_address,
                msg->msg + 2,  // +2 here because we've already prefixed with '0x'.
                msg->pluginSharedRW->sha3,
                0);
            break;
        case 1:
            strlcpy(msg->title, "Amount", msg->titleLength);

            const uint8_t *rpl_amount = context->selector.stake_rpl_for.amount;
            amountToString(rpl_amount,
                           INT256_LENGTH,
                           WEI_TO_ETHER,
                           "RPL",
                           msg->msg,
                           msg->msgLength);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}

void handle_stake_rpl_ui(ethQueryContractUI_t *msg, context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Amount", msg->titleLength);

            const uint8_t *rpl_amount = context->selector.stake_rpl.amount;
            amountToString(rpl_amount,
                           INT256_LENGTH,
                           WEI_TO_ETHER,
                           "RPL",
                           msg->msg,
                           msg->msgLength);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}

void handle_unstake_rpl_ui(ethQueryContractUI_t *msg, context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Amount", msg->titleLength);

            const uint8_t *rpl_amount = context->selector.unstake_rpl.amount;
            amountToString(rpl_amount,
                           INT256_LENGTH,
                           WEI_TO_ETHER,
                           "RPL",
                           msg->msg,
                           msg->msgLength);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}

void handle_swap_tokens_ui(ethQueryContractUI_t *msg, context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Amount", msg->titleLength);

            const uint8_t *rpl_amount = context->selector.swap_tokens.amount;
            amountToString(rpl_amount,
                           INT256_LENGTH,
                           WEI_TO_ETHER,
                           "RPL",
                           msg->msg,
                           msg->msgLength);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}

void handle_swap_to_ui(ethQueryContractUI_t *msg, context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Amount", msg->titleLength);

            const uint8_t *eth_amount = msg->pluginSharedRO->txContent->value.value;
            uint8_t eth_amount_size = msg->pluginSharedRO->txContent->value.length;

            // Converts the uint256 number located in `eth_amount` to its string representation and
            // copies this to `msg->msg`.
            amountToString(eth_amount,
                           eth_amount_size,
                           WEI_TO_ETHER,
                           "ETH",
                           msg->msg,
                           msg->msgLength);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}

void handle_swap_from_ui(ethQueryContractUI_t *msg, context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Amount", msg->titleLength);

            const uint8_t *reth_amount = context->selector.swap_from.amount;
            amountToString(reth_amount,
                           INT256_LENGTH,
                           WEI_TO_ETHER,
                           "rETH",
                           msg->msg,
                           msg->msgLength);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}

void handle_query_contract_ui(void *parameters) {
    ethQueryContractUI_t *msg = (ethQueryContractUI_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    // msg->title is the upper line displayed on the device.
    // msg->msg is the lower line displayed on the device.

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    switch (context->selectorIndex) {
        case DEPOSIT:
            handle_deposit_ui(msg, context);
            break;
        case BURN:
            handle_burn_ui(msg, context);
            break;
        case SET_WITHDRAWAL_ADDRESS:
            handle_set_withdrawal_address_ui(msg, context);
            break;
        case CONFIRM_WITHDRAWAL_ADDRESS:
            handle_confirm_withdrawal_address_ui(msg, context);
            break;
        case STAKE_RPL_FOR:
            handle_stake_rpl_for_ui(msg, context);
            break;
        case STAKE_RPL:
            handle_stake_rpl_ui(msg, context);
            break;
        case UNSTAKE_RPL:
            handle_unstake_rpl_ui(msg, context);
            break;
        case SWAP_TOKENS:
            handle_swap_tokens_ui(msg, context);
            break;
        case SWAP_TO:
            handle_swap_to_ui(msg, context);
            break;
        case SWAP_FROM:
            handle_swap_from_ui(msg, context);
            break;
        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
    }
}
