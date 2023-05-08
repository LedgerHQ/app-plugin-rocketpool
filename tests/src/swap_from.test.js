import "core-js/stable";
import "regenerator-runtime/runtime";
import {nano_models, txFromEtherscan, waitForAppScreen, zemu} from './test.fixture';

// Test from replayed transaction: https://etherscan.io/tx/0xf363c8d1eeaa974e85f4032e95fd2a29124e0a41cccba523b135b8892aaee8fc
nano_models.forEach(function (model) {
    jest.setTimeout(20000)
    test('[Nano ' + model.letter + '] Swap rETH to ETH', zemu(model, async (sim, eth) => {

        // The rawTx of the tx up above is accessible through: https://etherscan.io/getRawTx?tx=0xf363c8d1eeaa974e85f4032e95fd2a29124e0a41cccba523b135b8892aaee8fc
        const serializedTx = txFromEtherscan("0x02f901120181a1841dcd65008508085c3900830665c89416d5a408e807db8ef7c578279beeee6b228f1c1c80b8a4a824ae8b0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000a000000000000000000000000000000000000000000000000367b3bf601624bf500000000000000000000000000000000000000000000000037081d894c634a24000000000000000000000000000000000000000000000000338aa0826306ed33c001a0d35bbc9682f4d70e8c5db536c7173de403edd245ec3b04e5f470f721973aae2ca05d77bd2fc16db3b0edca2ae2ab33922548c726dcc6ac939f4b6306c6b694b901");

        const tx = eth.signTransaction(
            "44'/60'/0'/0",
            serializedTx,
        );

        const right_clicks = model.letter === 'S' ? 6 : 4;

        // Wait for the application to actually load and parse the transaction
        await waitForAppScreen(sim);
        // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
        await sim.navigateAndCompareSnapshots('.', model.name + '_swap_from', [right_clicks, 0]);

        await tx;
    }));
});

