#include <stdbool.h>
#include "rocketpool_plugin.h"

bool handle_deposit_ui(ethQueryContractUI_t *msg) {
    bool ret = false;

    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Amount", msg->titleLength);

            const uint8_t *eth_amount = msg->pluginSharedRO->txContent->value.value;
            uint8_t eth_amount_size = msg->pluginSharedRO->txContent->value.length;

            // Converts the uint256 number located in `eth_amount` to its string representation and
            // copies this to `msg->msg`.
            ret = amountToString(eth_amount,
                                 eth_amount_size,
                                 WEI_TO_ETHER,
                                 "ETH",
                                 msg->msg,
                                 msg->msgLength);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
    }
    return ret;
}

bool handle_burn_ui(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Amount", msg->titleLength);

            const uint8_t *reth_amount = context->selector.burn.amount;
            ret = amountToString(reth_amount,
                                 INT256_LENGTH,
                                 WEI_TO_ETHER,
                                 "rETH",
                                 msg->msg,
                                 msg->msgLength);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
    }
    return ret;
}

bool handle_set_withdrawal_address_ui(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    // Ensure buffer is big enough to write address prefixed with 0x
    if (msg->msgLength < ETHEREUM_ADDRESS_LENGTH) {
        PRINTF("Buffer too small\n");
        return false;
    }

    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Node Addr", msg->titleLength);

            // Prefix the address with `0x`.
            msg->msg[0] = '0';
            msg->msg[1] = 'x';

            ret = getEthAddressStringFromBinary(
                context->selector.set_withdrawal_address.node_address,
                msg->msg + 2,  // +2 here because we've already prefixed with '0x'.
                0);
            break;
        case 1:
            strlcpy(msg->title, "New Withdr Addr", msg->titleLength);

            // Prefix the address with `0x`.
            msg->msg[0] = '0';
            msg->msg[1] = 'x';

            ret = getEthAddressStringFromBinary(
                context->selector.set_withdrawal_address.new_withdrawal_address,
                msg->msg + 2,  // +2 here because we've already prefixed with '0x'.
                0);
            break;
        case 2:
            strlcpy(msg->title, "Confirm", msg->titleLength);

            if (context->selector.set_withdrawal_address.confirm) {
                strlcpy(msg->msg, "Yes", msg->titleLength);
            } else {
                strlcpy(msg->msg, "No", msg->titleLength);
            }
            ret = true;
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
    }
    return ret;
}

bool handle_confirm_withdrawal_address_ui(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    // Ensure buffer is big enough to write address prefixed with 0x
    if (msg->msgLength < ETHEREUM_ADDRESS_LENGTH) {
        PRINTF("Buffer too small\n");
        return false;
    }

    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Node Addr", msg->titleLength);

            // Prefix the address with `0x`.
            msg->msg[0] = '0';
            msg->msg[1] = 'x';

            ret = getEthAddressStringFromBinary(
                context->selector.confirm_withdrawal_address.node_address,
                msg->msg + 2,  // +2 here because we've already prefixed with '0x'.
                0);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
    }
    return ret;
}

bool handle_stake_rpl_for_ui(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    // Ensure buffer is big enough to write address prefixed with 0x
    if (msg->msgLength < ETHEREUM_ADDRESS_LENGTH) {
        PRINTF("Buffer too small\n");
        return false;
    }

    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Node Addr", msg->titleLength);

            // Prefix the address with `0x`.
            msg->msg[0] = '0';
            msg->msg[1] = 'x';

            ret = getEthAddressStringFromBinary(
                context->selector.confirm_withdrawal_address.node_address,
                msg->msg + 2,  // +2 here because we've already prefixed with '0x'.
                0);
            break;
        case 1:
            strlcpy(msg->title, "Amount", msg->titleLength);

            const uint8_t *rpl_amount = context->selector.stake_rpl_for.amount;
            ret = amountToString(rpl_amount,
                                 INT256_LENGTH,
                                 WEI_TO_ETHER,
                                 "RPL",
                                 msg->msg,
                                 msg->msgLength);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
    }
    return ret;
}

bool handle_stake_rpl_ui(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Amount", msg->titleLength);

            const uint8_t *rpl_amount = context->selector.stake_rpl.amount;
            ret = amountToString(rpl_amount,
                                 INT256_LENGTH,
                                 WEI_TO_ETHER,
                                 "RPL",
                                 msg->msg,
                                 msg->msgLength);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
    }
    return ret;
}

bool handle_unstake_rpl_ui(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Amount", msg->titleLength);

            const uint8_t *rpl_amount = context->selector.unstake_rpl.amount;
            ret = amountToString(rpl_amount,
                                 INT256_LENGTH,
                                 WEI_TO_ETHER,
                                 "RPL",
                                 msg->msg,
                                 msg->msgLength);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
    }
    return ret;
}

bool handle_swap_tokens_ui(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Amount", msg->titleLength);

            const uint8_t *rpl_amount = context->selector.swap_tokens.amount;
            ret = amountToString(rpl_amount,
                                 INT256_LENGTH,
                                 WEI_TO_ETHER,
                                 "RPL",
                                 msg->msg,
                                 msg->msgLength);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
    }
    return ret;
}

bool handle_swap_to_ui(ethQueryContractUI_t *msg) {
    bool ret = false;

    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Amount", msg->titleLength);

            const uint8_t *eth_amount = msg->pluginSharedRO->txContent->value.value;
            uint8_t eth_amount_size = msg->pluginSharedRO->txContent->value.length;

            // Converts the uint256 number located in `eth_amount` to its string representation and
            // copies this to `msg->msg`.
            ret = amountToString(eth_amount,
                                 eth_amount_size,
                                 WEI_TO_ETHER,
                                 "ETH",
                                 msg->msg,
                                 msg->msgLength);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
    }
    return ret;
}

bool handle_swap_from_ui(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Amount", msg->titleLength);

            const uint8_t *reth_amount = context->selector.swap_from.amount;
            ret = amountToString(reth_amount,
                                 INT256_LENGTH,
                                 WEI_TO_ETHER,
                                 "rETH",
                                 msg->msg,
                                 msg->msgLength);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
    }
    return ret;
}

void handle_query_contract_ui(ethQueryContractUI_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    bool ret = false;

    // msg->title is the upper line displayed on the device.
    // msg->msg is the lower line displayed on the device.

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    switch (context->selectorIndex) {
        case DEPOSIT:
            ret = handle_deposit_ui(msg);
            break;
        case BURN:
            ret = handle_burn_ui(msg, context);
            break;
        case SET_WITHDRAWAL_ADDRESS:
            ret = handle_set_withdrawal_address_ui(msg, context);
            break;
        case CONFIRM_WITHDRAWAL_ADDRESS:
            ret = handle_confirm_withdrawal_address_ui(msg, context);
            break;
        case STAKE_RPL_FOR:
            ret = handle_stake_rpl_for_ui(msg, context);
            break;
        case STAKE_RPL:
            ret = handle_stake_rpl_ui(msg, context);
            break;
        case UNSTAKE_RPL:
            ret = handle_unstake_rpl_ui(msg, context);
            break;
        case SWAP_TOKENS:
            ret = handle_swap_tokens_ui(msg, context);
            break;
        case SWAP_TO:
            ret = handle_swap_to_ui(msg);
            break;
        case SWAP_FROM:
            ret = handle_swap_from_ui(msg, context);
            break;
        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
    }
    msg->result = ret ? ETH_PLUGIN_RESULT_OK : ETH_PLUGIN_RESULT_ERROR;
}
