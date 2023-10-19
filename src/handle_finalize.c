#include "rocketpool_plugin.h"

void handle_finalize(ethPluginFinalize_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;

    msg->uiType = ETH_UI_TYPE_GENERIC;
    msg->numScreens = context->num_screens;
    msg->result = ETH_PLUGIN_RESULT_OK;
}
