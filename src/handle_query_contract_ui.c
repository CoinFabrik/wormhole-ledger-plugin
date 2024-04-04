#include "plugin.h"

static const char * const chain_names1[] = {
    "UNUSED",        //  0
    "Solana",        //  1
    "Ethereum",      //  2
    "Terra Classic", //  3
    "Bsc",           //  4
    "Polygon",       //  5
    "Avalanche",     //  6
    "Oasis",         //  7
    "Algorand",      //  8
    "Aurora",        //  9
    "Fantom",        // 10
    "Karura",        // 11
    "Acala",         // 12
    "Klaytn",        // 13
    "Celo",          // 14
    "Near",          // 15
    "Moonbeam",      // 16
    "Neon",          // 17
    "Terra2",        // 18
    "Injective",     // 19
    "Osmosis",       // 20
    "Sui",           // 21
    "Aptos",         // 22
    "Arbitrum",      // 23
    "Optimism",      // 24
    "Gnosis",        // 25
    "Pythnet",       // 26
    "UNUSED",        // 27
    "XPLA",          // 28
    "Bitcoin",       // 29
    "Base",          // 30
    "UNUSED",        // 31
    "Sei",           // 32
    "Rootstock",     // 33
    "Scroll",        // 34
    "Mantle",        // 35
};

static const char * const chain_names2[] = {
    "Cosmos Hub", // 4000
    "Evmos",      // 4001
    "Kujira",     // 4002
    "Neutron",    // 4003
    "Celestia",   // 4004
};

static const char * const chain_names3[] = {
    "Sepolia",          // 10002
    "Arbitrum Sepolia", // 10003
    "Base Sepolia",     // 10004
    "Optimism Sepolia", // 10005
    "Holesky",          // 10006
};

static const char *chain_id_to_name(uint16_t id){
    if (id == 3104)
        return "Wormhole";
    if (id < 36)
        return chain_names1[id];
    if (id >= 4000 && id < 4005)
        return chain_names2[id - 4000];
    if (id >= 10002 && id < 10007)
        return chain_names3[id - 10002];
    return NULL;
}

//------------------------------------------------------------------------

static bool set_recipient_chain(ethQueryContractUI_t *msg, context_t *context) {
    const char *name = chain_id_to_name(context->data.handle_wrap_and_transfer_e_t_h_data.recipient_chain);
    if (!name)
        return false;
    strlcpy(msg->title, "Dst Chain", msg->titleLength);
    strlcpy(msg->msg, name, msg->msgLength);
    return true;
}

static bool set_recipient(ethQueryContractUI_t *msg, context_t *context){
    strlcpy(msg->title, "Recipient", msg->titleLength);
    int start = 0;
    if (msg->msgLength >= 2){
        msg->msg[0] = '0';
        msg->msg[1] = 'x';
        start += 2;
    }
    return getEthAddressStringFromBinary(
        context->data.handle_wrap_and_transfer_e_t_h_data.recipient,
        msg->msg + start,
        msg->pluginSharedRW->sha3,
        0
    );
}

static bool set_arbiter_fee(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Arbiter Fee", msg->titleLength);
    return amountToString(context->data.handle_wrap_and_transfer_e_t_h_data.arbiter_fee,
                          sizeof(context->data.handle_wrap_and_transfer_e_t_h_data.arbiter_fee),
                          WEI_TO_ETHER,
                          "ETH",
                          msg->msg,
                          msg->msgLength);
}

static bool set_nonce(ethQueryContractUI_t *msg, context_t *context){
    strlcpy(msg->title, "Nonce", msg->titleLength);
    return u64_to_string(context->data.handle_wrap_and_transfer_e_t_h_data.nonce, msg->msg, msg->msgLength);
}

//------------------------------------------------------------------------

static bool set_token_address(ethQueryContractUI_t *msg, context_t *context){
    strlcpy(msg->title, "Token Address", msg->titleLength);
    int start = 0;
    if (msg->msgLength >= 2){
        msg->msg[0] = '0';
        msg->msg[1] = 'x';
        start += 2;
    }
    return getEthAddressStringFromBinary(
        context->data.handle_attest_token_data.recipient,
        msg->msg + start,
        msg->pluginSharedRW->sha3,
        0
    );
}

static bool set_nonce2(ethQueryContractUI_t *msg, context_t *context){
    strlcpy(msg->title, "Nonce", msg->titleLength);
    return u64_to_string(context->data.handle_attest_token_data.nonce, msg->msg, msg->msgLength);
}

//------------------------------------------------------------------------

static bool set_token(ethQueryContractUI_t *msg, context_t *context){
    strlcpy(msg->title, "Token", msg->titleLength);
    int start = 0;
    if (msg->msgLength >= 2){
        msg->msg[0] = '0';
        msg->msg[1] = 'x';
        start += 2;
    }
    return getEthAddressStringFromBinary(
        context->data.handle_transfer_tokens_data.recipient,
        msg->msg + start,
        msg->pluginSharedRW->sha3,
        0
    );
}

static bool set_amount(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Amount", msg->titleLength);
    return amountToString(context->data.handle_transfer_tokens_data.arbiter_fee,
                          sizeof(context->data.handle_transfer_tokens_data.arbiter_fee),
                          WEI_TO_ETHER,
                          "",
                          msg->msg,
                          msg->msgLength);
}

static bool set_recipient_chain2(ethQueryContractUI_t *msg, context_t *context) {
    const char *name = chain_id_to_name(context->data.handle_transfer_tokens_data.recipient_chain);
    if (!name)
        return false;
    strlcpy(msg->title, "Dst Chain", msg->titleLength);
    strlcpy(msg->msg, name, msg->msgLength);
    return true;
}

static bool set_recipient2(ethQueryContractUI_t *msg, context_t *context){
    strlcpy(msg->title, "Recipient", msg->titleLength);
    int start = 0;
    if (msg->msgLength >= 2){
        msg->msg[0] = '0';
        msg->msg[1] = 'x';
        start += 2;
    }
    return getEthAddressStringFromBinary(
        context->data.handle_transfer_tokens_data.recipient,
        msg->msg + start,
        msg->pluginSharedRW->sha3,
        0
    );
}

static bool set_arbiter_fee2(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Arbiter Fee", msg->titleLength);
    return amountToString(context->data.handle_transfer_tokens_data.arbiter_fee,
                          sizeof(context->data.handle_transfer_tokens_data.arbiter_fee),
                          WEI_TO_ETHER,
                          "ETH",
                          msg->msg,
                          msg->msgLength);
}

static bool set_nonce3(ethQueryContractUI_t *msg, context_t *context){
    strlcpy(msg->title, "Nonce", msg->titleLength);
    return u64_to_string(context->data.handle_transfer_tokens_data.nonce, msg->msg, msg->msgLength);
}

//------------------------------------------------------------------------

static void handle_wrap_and_transfer_e_t_h(ethQueryContractUI_t *msg, context_t *context){
    bool ret = false;

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    switch (msg->screenIndex) {
        case 0:
            ret = set_recipient_chain(msg, context);
            break;
        case 1:
            ret = set_recipient(msg, context);
            break;
        case 2:
            ret = set_arbiter_fee(msg, context);
            break;
        case 3:
            ret = set_nonce(msg, context);
            break;
        default:
            //PRINTF("Received an invalid screenIndex\n");
            break;
    }
    msg->result = ret ? ETH_PLUGIN_RESULT_OK : ETH_PLUGIN_RESULT_ERROR;
}

static void handle_attest_token(ethQueryContractUI_t *msg, context_t *context){
    bool ret = false;

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    switch (msg->screenIndex) {
        case 0:
            ret = set_token_address(msg, context);
            break;
        case 1:
            ret = set_nonce2(msg, context);
            break;
        default:
            //PRINTF("Received an invalid screenIndex\n");
            break;
    }
    msg->result = ret ? ETH_PLUGIN_RESULT_OK : ETH_PLUGIN_RESULT_ERROR;
}

static void handle_transfer_tokens(ethQueryContractUI_t *msg, context_t *context){
    bool ret = false;

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    switch (msg->screenIndex) {
        case 0:
            ret = set_token(msg, context);
            break;
        case 1:
            ret = set_amount(msg, context);
            break;
        case 2:
            ret = set_recipient_chain2(msg, context);
            break;
        case 3:
            ret = set_recipient2(msg, context);
            break;
        case 4:
            ret = set_arbiter_fee2(msg, context);
            break;
        case 5:
            ret = set_nonce3(msg, context);
            break;
        default:
            //PRINTF("Received an invalid screenIndex\n");
            break;
    }
    msg->result = ret ? ETH_PLUGIN_RESULT_OK : ETH_PLUGIN_RESULT_ERROR;
}

void handle_query_contract_ui(ethQueryContractUI_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    switch (context->selectorIndex){
        case WRAP_AND_TRANSFER_E_T_H:
            handle_wrap_and_transfer_e_t_h(msg, context);
            break;
        case ATTEST_TOKEN:
            handle_attest_token(msg, context);
            break;
        case TRANSFER_TOKENS:
            handle_transfer_tokens(msg, context);
            break;
        case COMPLETE_TRANSFER:
        case COMPLETE_TRANSFER_WITH_PAYLOAD:
        case COMPLETE_TRANSFER_AND_UNWRAP_E_T_H:
        case COMPLETE_TRANSFER_AND_UNWRAP_E_T_H_WITH_PAYLOAD:
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;
        default:
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
