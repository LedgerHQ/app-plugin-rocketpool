import "core-js/stable";
import "regenerator-runtime/runtime";
import {nano_models, txFromEtherscan, waitForAppScreen, zemu} from './test.fixture';

// Test from replayed transaction: https://etherscan.io/tx/0xfff1a45bdc8838b165ab12f3b275ccaea9acfeb3cb1724e315fad3e436ea43eb
nano_models.forEach(function (model) {
    jest.setTimeout(20000)
    test('[Nano ' + model.letter + '] Swap ETH to rETH', zemu(model, async (sim, eth) => {

        // The rawTx of the tx up above is accessible through: https://etherscan.io/getRawTx?tx=0xfff1a45bdc8838b165ab12f3b275ccaea9acfeb3cb1724e315fad3e436ea43eb
        const serializedTx = txFromEtherscan("0x02f8fa0180841dcd65008507f4b0d2808309ec839416d5a408e807db8ef7c578279beeee6b228f1c1c8901158e460913d00000b88455362f4d0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000a000000000000000000000000000000000000000000000001011da59c3516120c00000000000000000000000000000000000000000000000103b68314bc164b1fc001a0721ce6748282933aa97554d2fa407d47839ca4b808d55c6236fb4de0dfd029e2a069e9bb493edf8fe9174fab8070df7264dad91b05eb62ef4ab61034e53becd711");

        const tx = eth.signTransaction(
            "44'/60'/0'/0",
            serializedTx,
        );

        const right_clicks = model.letter === 'S' ? 4 : 4;

        // Wait for the application to actually load and parse the transaction
        await waitForAppScreen(sim);
        // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
        await sim.navigateAndCompareSnapshots('.', model.name + '_swap_to', [right_clicks, 0]);

        await tx;
    }));
});

