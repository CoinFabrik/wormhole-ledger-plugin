#include "plugin.h"

// Sets the first screen to display.
void handle_query_contract_id(ethQueryContractID_t *msg) {
    const context_t *context = (const context_t *) msg->pluginContext;
    // msg->name will be the upper sentence displayed on the screen.
    // msg->version will be the lower sentence displayed on the screen.

    // For the first screen, display the plugin name.
    strlcpy(msg->name, APPNAME, msg->nameLength);

    switch (context->selectorIndex){
        case WRAP_AND_TRANSFER_E_T_H:
            strlcpy(msg->version, "Wrap and Transfer ETH", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case ATTEST_TOKEN:
            strlcpy(msg->version, "Attest token", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case TRANSFER_TOKENS:
            strlcpy(msg->version, "Transfer tokens", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case COMPLETE_TRANSFER:
        case COMPLETE_TRANSFER_WITH_PAYLOAD:
            strlcpy(msg->version, "Complete transfer", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        case COMPLETE_TRANSFER_AND_UNWRAP_E_T_H:
        case COMPLETE_TRANSFER_AND_UNWRAP_E_T_H_WITH_PAYLOAD:
            strlcpy(msg->version, "Complete transfer unwrapping", msg->versionLength);
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        default:
            //PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
    }
}
