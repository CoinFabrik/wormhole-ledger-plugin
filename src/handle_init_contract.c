#include "plugin_utils.h"
#include "plugin.h"

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

    context->selectorIndex = WRAP_AND_TRANSFER_E_T_H;
    context->next_param = RECIPIENT_CHAIN;
    msg->result = ETH_PLUGIN_RESULT_OK;
    return;


    size_t index;
    if (!find_selector(U4BE(msg->selector, 0), SELECTORS, SELECTOR_COUNT, &index)) {
        PRINTF("Error: selector not found!\n");
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }
    context->selectorIndex = index;
    // check for overflow
    if ((size_t) context->selectorIndex != index) {
        PRINTF("Error: overflow detected on selector index!\n");
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    // Set `next_param` to be the first field we expect to parse.
    switch (context->selectorIndex) {
        /*case REGISTER_CHAIN:
            context->next_param = ENCODED_V_M;
            break;
        case SUBMIT_RECOVER_CHAIN_ID:
            context->next_param = ENCODED_V_M;
            break;
        case UPGRADE:
            context->next_param = ENCODED_V_M;
            break;*/
        case ATTEST_TOKEN:
            context->next_param = TOKEN_ADDRESS;
            break;
        case WRAP_AND_TRANSFER_E_T_H:
            context->next_param = RECIPIENT_CHAIN;
            break;
        /*case WRAP_AND_TRANSFER_E_T_H_WITH_PAYLOAD:
            context->next_param = RECIPIENT_CHAIN;
            break;*/
        case TRANSFER_TOKENS:
            context->next_param = TOKEN;
            break;
        /*case TRANSFER_TOKENS_WITH_PAYLOAD:
            context->next_param = TOKEN;
            break;
        case UPDATE_WRAPPED:
            context->next_param = ENCODED_VM;
            break;
        case CREATE_WRAPPED:
            context->next_param = ENCODED_VM;
            break;*/
        case COMPLETE_TRANSFER_WITH_PAYLOAD:
            context->next_param = ENCODED_VM;
            break;
        case COMPLETE_TRANSFER_AND_UNWRAP_E_T_H_WITH_PAYLOAD:
            context->next_param = ENCODED_VM;
            break;
        case COMPLETE_TRANSFER:
            context->next_param = ENCODED_VM;
            break;
        case COMPLETE_TRANSFER_AND_UNWRAP_E_T_H:
            context->next_param = ENCODED_VM;
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
