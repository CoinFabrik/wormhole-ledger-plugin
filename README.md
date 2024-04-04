# Wormhole Ethereum Transactions Ledger Plugin

This repository hosts a Ledger plugin designed to facilitate Ethereum transactions via the [Wormhole network](https://wormhole.com/) for the [Wormhole Portal Token Bridge](https://etherscan.io/address/0x3ee18b2214aff97000d974cf647e7c347e8fa585). This plugin enhances the Ledger device's capability to interact securely with smart contracts, focusing on transactions that bridge assets involving ethereum.

## Plugin Features

- **Dynamic UI Screens**: Dynamically adjusts the number of UI screens based on the transaction type, providing a streamlined and user-friendly interface.
- **Smart Contract Interaction**: Facilitates interaction with specific smart contract functions related to wrapping, unwrapping, attesting, and transferring tokens.
- **Chain Identification**: Implements functionality to display information about the destination chain in a human-readable format, improving clarity and understanding of cross-chain transactions.
- **Parameter Handling**: Efficiently manages different parameters associated with each supported transaction type, such as recipient chain, recipient address, arbiter fee, nonce, token address, and amount, ensuring accurate transaction execution.
- **Custom Data Structures**: Uses customized data structures to manage and display transaction details, allowing for a flexible and scalable plugin architecture that can easily adapt to new features or additional transaction types.

## Supported Smart Contract and Transactions

This plugin provides support for the following transactions of the [Wormhole Portal Token Bridge](https://etherscan.io/address/0x3ee18b2214aff97000d974cf647e7c347e8fa585):

- **Wrap and Transfer ETH**: Allows users to wrap ETH and transfer it across different blockchain networks, enhancing the flexibility of asset movement.
- **Attest Token**: Supports the attestation of tokens, a crucial step in the token bridging process, facilitating the verification and transfer of asset information.
- **Transfer Tokens**: Enables the transfer of tokens from one blockchain to another, supporting a broader range of asset mobility with enhanced user experience.
- **Complete Transfer (with and without payload)**: Handles the final steps of the token transfer process, including unwrapping ETH if necessary, ensuring the secure completion of cross-chain transactions.

For a detailed specification of the supported functions check the included `PLUGIN_SPECIFICATION.md`



## Usage

To build and test the ledger plugin, follow these steps with the [Ledger's VSCode developer tools extension](https://marketplace.visualstudio.com/items?itemName=LedgerHQ.ledger-dev-tools):
1. Copy the Ethereum plugin builds inside the `tests/ethereum_build` directory, as described in the `README` file in the tests folder.
2. Use the Ledger extension in VSCode to run the `Build` command.
3. Run the `Run tests` command to test your plugin.

Detailed instructions on building, testing and loading ledger plugins can be found in the [Ledger Developer Documentation](https://developers.ledger.com/docs/device-app/develop).


## Acknowledgements

This repository is a fork from Ledger's [app-plugin-boilerplate](https://github.com/LedgerHQ/app-plugin-boilerplate) and was created following the [plugin guide](https://developers.ledger.com/docs/dapp/embedded-plugin/code-overview/).

## About CoinFabrik

We - [CoinFabrik](https://www.coinfabrik.com/) - are a research and development company specialized in Web3, with a strong background in cybersecurity. Founded in 2014, we have worked on over 200 blockchain-related projects, EVM based and also for Solana, Algorand, and Polkadot. Beyond development, we offer security audits through a dedicated in-house team of senior cybersecurity professionals, currently working on code in Substrate, Solidity, Clarity, Rust, and TEAL.

Our team has an academic background in computer science and mathematics, with work experience focused on cybersecurity and software development, including academic publications, patents turned into products, and conference presentations. Furthermore, we have an ongoing collaboration on knowledge transfer and open-source projects with the University of Buenos Aires.


## License

This project is licensed under the Apache License 2.0. See the `LICENSE` file for more details.
