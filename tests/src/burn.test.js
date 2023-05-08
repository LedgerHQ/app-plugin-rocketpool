import "core-js/stable";
import "regenerator-runtime/runtime";
import {nano_models, txFromEtherscan, waitForAppScreen, zemu} from './test.fixture';

// Test from replayed transaction: https://etherscan.io/tx/0x42d11302d47b03ad10b1d9406bfc7085e2d39dbbe8874776f357dc832c9a5121
nano_models.forEach(function (model) {
    jest.setTimeout(20000)
    test('[Nano ' + model.letter + '] Burn rETH', zemu(model, async (sim, eth) => {

        // The rawTx of the tx up above is accessible through: https://etherscan.io/getRawTx?tx=0x42d11302d47b03ad10b1d9406bfc7085e2d39dbbe8874776f357dc832c9a5121
        const serializedTx = txFromEtherscan("0x02f890010a8405f5e100851ef51386008302d03a94ae78736cd615f374d3085123a210448e74fc639380a442966c68000000000000000000000000000000000000000000000000016345785d8a0000c001a06fb8bfe47bd04987496ae8f2cf93b9f50e206076bc897788de210e0717d751d8a0455976c38e73390f33e5c45488871107b58ecd1aab0d40cc7be5b3aee57a1ee8");

        const tx = eth.signTransaction(
            "44'/60'/0'/0",
            serializedTx,
        );

        const right_clicks = model.letter === 'S' ? 6 : 4;

        // Wait for the application to actually load and parse the transaction
        await waitForAppScreen(sim);
        // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
        await sim.navigateAndCompareSnapshots('.', model.name + '_burn', [right_clicks, 0]);

        await tx;
    }));
});

