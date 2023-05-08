import "core-js/stable";
import "regenerator-runtime/runtime";
import {nano_models, txFromEtherscan, waitForAppScreen, zemu} from './test.fixture';

// Test from replayed transaction: https://etherscan.io/tx/0x181b8b116c32b6c054b0eb62b1e2e52ac5f39bd126edca955110e7f4dc663e84
nano_models.forEach(function (model) {
    jest.setTimeout(20000)
    test('[Nano ' + model.letter + '] Stake RPL For', zemu(model, async (sim, eth) => {

        // The rawTx of the tx up above is accessible through: https://etherscan.io/getRawTx?tx=0x181b8b116c32b6c054b0eb62b1e2e52ac5f39bd126edca955110e7f4dc663e84
        const serializedTx = txFromEtherscan("0x02f8b101648405f5e100851d47af8d728302812e940d8d8f8541b12a0e1194b7cc4b6d954b90ab82ec80b844cb1c8321000000000000000000000000a5c142e01153b28f5da63cd8c118f59765175bd800000000000000000000000000000000000000000000005c2a5b0d55397a537dc001a0b96885b91a728de640993662b37b201313df8a82c627cddc5a116063959ad4a1a0324378d32a580194fafc0654cbd669256938aef10ad968959f9a86c979e818cc");

        const tx = eth.signTransaction(
            "44'/60'/0'/0",
            serializedTx,
        );

        const right_clicks = model.letter === 'S' ? 11 : 5;

        // Wait for the application to actually load and parse the transaction
        await waitForAppScreen(sim);
        // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
        await sim.navigateAndCompareSnapshots('.', model.name + '_stake_rpl_for', [right_clicks, 0]);

        await tx;
    }));
});
