/*******************************************************************************
 *   Plugin Boilerplate
 *   (c) 2023 Ledger
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#pragma once

#include <string.h>
#include "eth_internals.h"
#include "eth_plugin_interface.h"

// All possible selectors of your plugin.
// EDIT THIS: Enter your selectors here, in the format X(NAME, value)
// A Xmacro below will create for you:
//     - an enum named selector_t with every NAME
//     - a map named SELECTORS associating each NAME with it's value
#define SELECTORS_LIST(X)                                          \
    X(REGISTER_CHAIN,                                  0xa5799f93) \
    X(SUBMIT_RECOVER_CHAIN_ID,                         0x178149e7) \
    X(UPGRADE,                                         0x25394645) \
    X(ATTEST_TOKEN,                                    0xc48fa115) \
    X(WRAP_AND_TRANSFER_E_T_H,                         0x9981509f) \
    X(WRAP_AND_TRANSFER_E_T_H_WITH_PAYLOAD,            0xbee9cdfc) \
    X(TRANSFER_TOKENS,                                 0x0f5287b0) \
    X(TRANSFER_TOKENS_WITH_PAYLOAD,                    0xc5a5ebda) \
    X(UPDATE_WRAPPED,                                  0xf768441f) \
    X(CREATE_WRAPPED,                                  0xe8059810) \
    X(COMPLETE_TRANSFER_WITH_PAYLOAD,                  0xc3f511c1) \
    X(COMPLETE_TRANSFER_AND_UNWRAP_E_T_H_WITH_PAYLOAD, 0x1c8475e4) \
    X(COMPLETE_TRANSFER,                               0xc6878519) \
    X(COMPLETE_TRANSFER_AND_UNWRAP_E_T_H,              0xff200cde)

// Xmacro helpers to define the enum and map
// Do not modify !
#define TO_ENUM(selector_name, selector_id)  selector_name,
#define TO_VALUE(selector_name, selector_id) selector_id,

// This enum will be automatically expanded to hold all selector names.
// The value SELECTOR_COUNT can be used to get the number of defined selectors
// Do not modify !
typedef enum selector_e {
    SELECTORS_LIST(TO_ENUM) SELECTOR_COUNT,
} selector_t;

// This array will be automatically expanded to map all selector_t names with the correct value.
// Do not modify !
extern const uint32_t SELECTORS[SELECTOR_COUNT];

// Enumeration used to parse the smart contract data.
typedef enum {
    ENCODED_V_M = 0, // bytes
    TOKEN_ADDRESS,   // address
    NONCE,           // uint32
    RECIPIENT_CHAIN, // uint16
    RECIPIENT,       // bytes32
    ARBITER_FEE,     // uint256
    PAYLOAD,         // bytes
    TOKEN,           // address
    AMOUNT,          // uint256
    ENCODED_VM,      // bytes
    UNEXPECTED_PARAMETER,
} parameter;

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct context_s {
    // For display.
    union{
        struct{
            uint16_t recipient_chain;
            uint8_t recipient[INT256_LENGTH];
            uint8_t arbiter_fee[INT256_LENGTH];
            uint32_t nonce;
        } handle_wrap_and_transfer_e_t_h_data;
        struct{
            uint8_t token_address[INT256_LENGTH];
            uint32_t nonce;
        } handle_attest_token_data;
        struct{
            uint8_t token[INT256_LENGTH];
            uint8_t amount[INT256_LENGTH];
            uint16_t recipient_chain;
            uint8_t recipient[INT256_LENGTH];
            uint8_t arbiter_fee[INT256_LENGTH];
            uint32_t nonce;
        } handle_transfer_tokens_data;
    } data;
    //uint8_t amount_received[INT256_LENGTH];
    //uint8_t beneficiary[ADDRESS_LENGTH];
    //uint8_t token_received[ADDRESS_LENGTH];
    //char ticker[MAX_TICKER_LEN];
    //uint8_t decimals;
    //uint8_t token_found;

    // For parsing data.
    uint8_t next_param;  // Set to be the next param we expect to parse.
    uint16_t offset;     // Offset at which the array or struct starts.
    bool go_to_offset;   // If set, will force the parsing to iterate through parameters until
                         // `offset` is reached.

    // For both parsing and display.
    selector_t selectorIndex;
} context_t;

// Check if the context structure will fit in the RAM section ETH will prepare for us
// Do not remove!
ASSERT_SIZEOF_PLUGIN_CONTEXT(context_t);
