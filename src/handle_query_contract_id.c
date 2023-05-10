#include "rocketpool_plugin.h"

// Sets the first screen to display.
void handle_query_contract_id(void *parameters) {
    ethQueryContractID_t *msg = (ethQueryContractID_t *) parameters;
    const context_t *context = (const context_t *) msg->pluginContext;

    // msg->name will be the upper sentence displayed on the screen.
    // msg->version will be the lower sentence displayed on the screen.

    // For the first screen, display the plugin name.
    strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);

    switch (context->selectorIndex) {
        case DEPOSIT:
        case SWAP_TO:
            strlcpy(msg->version, "Stake", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case BURN:
        case SWAP_FROM:
            strlcpy(msg->version, "Unstake", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case SET_WITHDRAWAL_ADDRESS:
            strlcpy(msg->version, "Set Withdr Addr", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case CONFIRM_WITHDRAWAL_ADDRESS:
            strlcpy(msg->version, "Conf Withdr Addr", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case STAKE_RPL_FOR:
            strlcpy(msg->version, "Stake RPL For", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case STAKE_RPL:
            strlcpy(msg->version, "Stake RPL", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case UNSTAKE_RPL:
            strlcpy(msg->version, "Unstake RPL", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case SWAP_TOKENS:
            strlcpy(msg->version, "Swap RPL v1 -> v2", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
    }
}