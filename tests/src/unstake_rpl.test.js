import "core-js/stable";
import "regenerator-runtime/runtime";
import {nano_models, txFromEtherscan, waitForAppScreen, zemu} from './test.fixture';

// Test from replayed transaction: https://etherscan.io/tx/0xb291302f6c270448153da6094e0c0a463a0dd8440b6ce2b24278fe200247ef03
nano_models.forEach(function (model) {
    jest.setTimeout(20000)
    test('[Nano ' + model.letter + '] Unstake RPL', zemu(model, async (sim, eth) => {

        // The rawTx of the tx up above is accessible through: https://etherscan.io/getRawTx?tx=0xb291302f6c270448153da6094e0c0a463a0dd8440b6ce2b24278fe200247ef03
        const serializedTx = txFromEtherscan("0x02f8910181dd8477359400851bf08eb00083044c71940d8d8f8541b12a0e1194b7cc4b6d954b90ab82ec80a46b088d5c00000000000000000000000000000000000000000000005f14d5a8be0c0c1825c001a0fa88df495e13b50709faf13cf50366ac05cf46dea29ec1cfa4cec6abb606dc6ca02905a97f8cee48bc6879f7ae21a1adf2a9d969a4e4d356186af4c7f06ebb92cd");

        const tx = eth.signTransaction(
            "44'/60'/0'/0",
            serializedTx,
        );

        const right_clicks = model.letter === 'S' ? 6 : 4;

        // Wait for the application to actually load and parse the transaction
        await waitForAppScreen(sim);
        // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
        await sim.navigateAndCompareSnapshots('.', model.name + '_unstake_rpl', [right_clicks, 0]);

        await tx;
    }));
});
