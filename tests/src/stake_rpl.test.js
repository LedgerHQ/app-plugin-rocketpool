import "core-js/stable";
import "regenerator-runtime/runtime";
import {nano_models, txFromEtherscan, waitForAppScreen, zemu} from './test.fixture';

// Test from replayed transaction: https://etherscan.io/tx/0x105b5ad98833877296690fd941b8e3deacab5ed87a76c5c8a295cf033fe110d4
nano_models.forEach(function (model) {
    jest.setTimeout(20000)
    test('[Nano ' + model.letter + '] Stake RPL', zemu(model, async (sim, eth) => {

        // The rawTx of the tx up above is accessible through: https://etherscan.io/getRawTx?tx=0x105b5ad98833877296690fd941b8e3deacab5ed87a76c5c8a295cf033fe110d4
        const serializedTx = txFromEtherscan("0x02f89001078477359400852bc5ac580083038138940d8d8f8541b12a0e1194b7cc4b6d954b90ab82ec80a43e200d4b0000000000000000000000000000000000000000000000037c9e8b37d1200000c080a047bf8d39390dcaf729f6337b82b52c9b3f9f847a3247e1103889312a8356d847a02e39f55d67183f2b2cdc04b1bc2a88e3900027134e900d623cbca1e46515d231");

        const tx = eth.signTransaction(
            "44'/60'/0'/0",
            serializedTx,
        );

        const right_clicks = model.letter === 'S' ? 4 : 4;

        // Wait for the application to actually load and parse the transaction
        await waitForAppScreen(sim);
        // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
        await sim.navigateAndCompareSnapshots('.', model.name + '_stake_rpl', [right_clicks, 0]);

        await tx;
    }));
});
