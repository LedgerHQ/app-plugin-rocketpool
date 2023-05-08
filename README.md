# ledger-app-plugin-rocketpool

This repo contains a Ledger Ethereum plugin to support the various Rocket Pool interactions.

Instructions on plugin development can be found in the
[plugin guide](https://developers.ledger.com/docs/dapp/nano-plugin/overview/).

## Installation

Clone this repository and it's dependencies into the same directory:

```bash
git clone https://github.com/rocket-pool/ledger-app-plugin-rocketpool.git
git clone https://github.com/LedgerHQ/plugin-tools.git
git clone --recurse-submodules https://github.com/LedgerHQ/app-ethereum.git
```

Your directory should look like this:

```
app-ethereum
ledger-app-plugin-rocketpool
plugin-tools
```

## Building

Navigate into the `plugin-tools` directory and run the `./start.sh` shell script:

```bash
cd plugin-tools
./start.sh
```

This script setups up a docker container with everything required to build the plugin. You will be dropped into an
interactive shell when the script completes.

Navigate into the `ledger-app-plugin-rocketpool` directory and run `make`:

```bash
cd ledger-app-plugin-rocketpool
make
```

The build artifacts will be placed in the `build/` directory.

## Testing

Navigate into the `plugin-tools` directory and run the `./start.sh` shell script:

```bash
cd plugin-tools
./start.sh
```

This script setups up a docker container with everything required to build the plugin. You will be dropped into an
interactive shell when the script completes.

Navigate into the `ledger-app-plugin-rocketpool/test` directory and run `./build_local_test_elfs.sh`:

```bash
cd ledger-app-plugin-rocketpool/test
./build_local_test_elfs.sh
```

This will generate test binaries that can be run on the Speculos emulator.

In another terminal, navigate to the same `test` directory and run `yarn test`. 

```bash
cd ledger-app-plugin-rocketpool/test
yarn install                      # On the first run of the test suite, install dependencies first
yarn test
```

