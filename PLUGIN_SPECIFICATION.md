# Technical Specification



## About

This documentation describes the smart contracts and functions supported by the `wormhole-eth-ledger-plugin`.

## Smart Contracts

Smart contracts covered by the plugin shall be described here:

|  Network | Version | Smart Contract | Address |
|   ----   |   ---   |      ----      |   ---   |
| Mainnet   | V1  | Wormhole Portal Token Bridge  | `0x3ee18B2214AFF97000D974cf647E7C347E8fa585` |

## Functions

For the smart contracts implemented, the functions covered by the plugin shall be described here:

| Contract     | Function                                    | Selector   | Displayed Parameters |
| ------------ | ------------------------------------------- | ---------- | ------------------- |
| Wormhole Portal Token Bridge | attestToken                                | `0xc48fa115` | <table><tbody> <tr><td><code>address tokenAddress</code></td></tr><tr><td><code>uint32 nonce</code></td></tr> </tbody></table> |
| Wormhole Portal Token Bridge | wrapAndTransferETH                         | `0x9981509f` | <table><tbody> <tr><td><code>uint16 recipientChain</code></td></tr><tr><td><code>bytes32 recipient</code></td></tr><tr><td><code>uint256 arbiterFee</code></td></tr><tr><td><code>uint32 nonce</code></td></tr> </tbody></table> |
| Wormhole Portal Token Bridge | transferTokens                             | `0x0f5287b0` | <table><tbody> <tr><td><code>address token</code></td></tr><tr><td><code>uint256 amount</code></td></tr><tr><td><code>uint16 recipientChain</code></td></tr><tr><td><code>bytes32 recipient</code></td></tr><tr><td><code>uint256 arbiterFee</code></td></tr><tr><td><code>uint32 nonce</code></td></tr> </tbody></table> |
| Wormhole Portal Token Bridge | completeTransferWithPayload                | `0xc3f511c1` | <table><tbody> <tr><td><code>None*</code></td></tr> </tbody></table> |
| Wormhole Portal Token Bridge | completeTransferAndUnwrapETHWithPayload    | `0x1c8475e4` | <table><tbody> <tr><td><code>None*</code></td></tr> </tbody></table> |
| Wormhole Portal Token Bridge | completeTransfer                           | `0xc6878519` | <table><tbody> <tr><td><code>None*</code></td></tr> </tbody></table> |
| Wormhole Portal Token Bridge | completeTransferAndUnwrapETH               | `0xff200cde` | <table><tbody> <tr><td><code>None*</code></td></tr> </tbody></table> |

\* `encodedVm` parameters are not parsed because they are encoded in byte-packed and variable-length form, and the Ethereum Ledger app sends the data to the plugin in 32-byte chunks, which makes it difficult to handle those parameters that cross a chunk boundary.
