#include "plugin.h"

void handle_wrap_and_transfer_e_t_h(ethPluginProvideParameter_t *msg, context_t *context){
    switch (context->next_param){
        case RECIPIENT_CHAIN:
            context->data.handle_wrap_and_transfer_e_t_h_data.recipient_chain = U2BE(msg->parameter, PARAMETER_LENGTH - 2);
            context->next_param = RECIPIENT;
            break;
        case RECIPIENT:
            {
                uint8_t *dst = context->data.handle_wrap_and_transfer_e_t_h_data.recipient;
                copy_parameter(dst, msg->parameter, INT256_LENGTH);
                context->next_param = ARBITER_FEE;
            }
            break;
        case ARBITER_FEE:
            {
                uint8_t *dst = context->data.handle_wrap_and_transfer_e_t_h_data.arbiter_fee;
                copy_parameter(dst, msg->parameter, INT256_LENGTH);
                context->next_param = NONCE;
            }
            break;
        case NONCE:
            context->data.handle_wrap_and_transfer_e_t_h_data.nonce = U4BE(msg->parameter, PARAMETER_LENGTH - 4);
            context->next_param = UNEXPECTED_PARAMETER;
            break;
    }
}

void handle_attest_token(ethPluginProvideParameter_t *msg, context_t *context){
    switch (context->next_param){
        case TOKEN_ADDRESS:
            {
                uint8_t *dst = context->data.handle_attest_token_data.recipient;
                copy_parameter(dst, msg->parameter, INT256_LENGTH);
                context->next_param = NONCE;
            }
            break;
        case NONCE:
            context->data.handle_attest_token_data.nonce = U4BE(msg->parameter, PARAMETER_LENGTH - 4);
            context->next_param = UNEXPECTED_PARAMETER;
            break;
    }
}

void handle_transfer_tokens(ethPluginProvideParameter_t *msg, context_t *context){
    switch (context->next_param){
        case TOKEN:
            {
                uint8_t *dst = context->data.handle_transfer_tokens_data.token;
                copy_parameter(dst, msg->parameter, INT256_LENGTH);
                context->next_param = AMOUNT;
            }
            break;
        case AMOUNT:
            {
                uint8_t *dst = context->data.handle_transfer_tokens_data.amount;
                copy_parameter(dst, msg->parameter, INT256_LENGTH);
                context->next_param = RECIPIENT_CHAIN;
            }
        case RECIPIENT_CHAIN:
            context->data.handle_transfer_tokens_data.recipient_chain = U2BE(msg->parameter, PARAMETER_LENGTH - 2);
            context->next_param = RECIPIENT;
            break;
        case RECIPIENT:
            {
                uint8_t *dst = context->data.handle_transfer_tokens_data.recipient;
                copy_parameter(dst, msg->parameter, INT256_LENGTH);
                context->next_param = ARBITER_FEE;
            }
            break;
        case ARBITER_FEE:
            {
                uint8_t *dst = context->data.handle_transfer_tokens_data.arbiter_fee;
                copy_parameter(dst, msg->parameter, INT256_LENGTH);
                context->next_param = NONCE;
            }
            break;
        case NONCE:
            context->data.handle_transfer_tokens_data.nonce = U4BE(msg->parameter, PARAMETER_LENGTH - 4);
            context->next_param = UNEXPECTED_PARAMETER;
            break;
    }
}

void handle_provide_parameter_switch(ethPluginProvideParameter_t *msg, context_t *context){
    switch (context->selectorIndex) {
        /*case REGISTER_CHAIN:
            handle_register_chain(msg, context);
            break;
        case SUBMIT_RECOVER_CHAIN_ID:
            handle_submit_recover_chain_id(msg, context);
            break;
        case UPGRADE:
            handle_upgrade(msg, context);
            break;*/
        case ATTEST_TOKEN:
            handle_attest_token(msg, context);
            break;
        case WRAP_AND_TRANSFER_E_T_H:
            handle_wrap_and_transfer_e_t_h(msg, context);
            break;
        /*case WRAP_AND_TRANSFER_E_T_H_WITH_PAYLOAD:
            handle_wrap_and_transfer_e_t_h_with_payload(msg, context);
            break;*/
        case TRANSFER_TOKENS:
            handle_transfer_tokens(msg, context);
            break;
        /*case TRANSFER_TOKENS_WITH_PAYLOAD:
            handle_transfer_tokens_with_payload(msg, context);
            break;
        case UPDATE_WRAPPED:
            handle_update_wrapped(msg, context);
            break;
        case CREATE_WRAPPED:
            handle_create_wrapped(msg, context);
            break;*/
        case COMPLETE_TRANSFER_WITH_PAYLOAD:
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        case COMPLETE_TRANSFER_AND_UNWRAP_E_T_H_WITH_PAYLOAD:
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        case COMPLETE_TRANSFER:
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        case COMPLETE_TRANSFER_AND_UNWRAP_E_T_H:
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            //PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_provide_parameter(ethPluginProvideParameter_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    // We use `%.*H`: it's a utility function to print bytes. You first give
    // the number of bytes you wish to print (in this case, `PARAMETER_LENGTH`) and then
    // the address (here `msg->parameter`).
    /*PRINTF("plugin provide parameter: offset %d\nBytes: %.*H\n",
           msg->parameterOffset,
           PARAMETER_LENGTH,
           msg->parameter);*/

    msg->result = ETH_PLUGIN_RESULT_OK;

    handle_provide_parameter_switch(msg, context);
}
