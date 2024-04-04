#include "plugin.h"

void handle_finalize(ethPluginFinalize_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;

    msg->uiType = ETH_UI_TYPE_GENERIC;

    switch (context->selectorIndex){
        case WRAP_AND_TRANSFER_E_T_H:
            msg->numScreens = 4;
            msg->tokenLookup1 = NULL;
            msg->tokenLookup2 = NULL;
            break;
        case ATTEST_TOKEN:
            msg->numScreens = 2;
            msg->tokenLookup1 = NULL;
            msg->tokenLookup2 = NULL;
            break;
        case TRANSFER_TOKENS:
            msg->numScreens = 6;
            msg->tokenLookup1 = NULL;
            msg->tokenLookup2 = NULL;
            break;
        case COMPLETE_TRANSFER_WITH_PAYLOAD:
        case COMPLETE_TRANSFER_AND_UNWRAP_E_T_H_WITH_PAYLOAD:
        case COMPLETE_TRANSFER:
        case COMPLETE_TRANSFER_AND_UNWRAP_E_T_H:
            msg->numScreens = 0;
            msg->tokenLookup1 = NULL;
            msg->tokenLookup2 = NULL;
            break;
    }
    msg->result = ETH_PLUGIN_RESULT_OK;
}
