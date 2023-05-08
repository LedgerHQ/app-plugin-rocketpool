import "core-js/stable";
import "regenerator-runtime/runtime";
import {nano_models, txFromEtherscan, waitForAppScreen, zemu} from './test.fixture';

// Test from replayed transaction: https://etherscan.io/tx/0x6e83c505679cb6a504130efc699d827f00a20f57453360a8400e15904e16e233
nano_models.forEach(function (model) {
    jest.setTimeout(20000)
    test('[Nano ' + model.letter + '] Deposit ETH', zemu(model, async (sim, eth) => {

        // The rawTx of the tx up above is accessible through: https://etherscan.io/getRawTx?tx=0x6e83c505679cb6a504130efc699d827f00a20f57453360a8400e15904e16e233
        const serializedTx = txFromEtherscan("0x02f87801488405f5e10085234b0934d18304b8fb94dd3f50f8a6cafbe9b31a427582963f465e745af8884f850ca422fd000084d0e30db0c001a03b0a35db319b1837ebc0545a9d6e42c632a3f1d1eb6a0763729d7b93d693b465a0314ba7d7696eea274cba6c62f0eb42a2f23c73a5ae2b5316060c1daeca04a9ec");

        const tx = eth.signTransaction(
            "44'/60'/0'/0",
            serializedTx,
        );

        const right_clicks = model.letter === 'S' ? 6 : 4;

        // Wait for the application to actually load and parse the transaction
        await waitForAppScreen(sim);
        // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
        await sim.navigateAndCompareSnapshots('.', model.name + '_deposit', [right_clicks, 0]);

        await tx;
    }));
});

