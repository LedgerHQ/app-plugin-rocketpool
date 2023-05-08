import "core-js/stable";
import "regenerator-runtime/runtime";
import {nano_models, txFromEtherscan, waitForAppScreen, zemu} from './test.fixture';

// Test from replayed transaction: https://etherscan.io/tx/0x278d60eaeba08f001c0ebe0eb4f06f83647fc98c31fc5f76d80f2456eb944cf2
nano_models.forEach(function (model) {
    jest.setTimeout(20000)
    test('[Nano ' + model.letter + '] Swap RPL v1 -> v2', zemu(model, async (sim, eth) => {

        // The rawTx of the tx up above is accessible through: https://etherscan.io/getRawTx?tx=0x278d60eaeba08f001c0ebe0eb4f06f83647fc98c31fc5f76d80f2456eb944cf2
        const serializedTx = txFromEtherscan("0x02f8910182016c8405f5e1008505ecdee44982fe5494d33526068d116ce69f19a9ee46f0bd304f21a51f80a4fe784eaa00000000000000000000000000000000000000000000010f0cf064dd59200000c001a0b3c8c7eedb7862b8f9a0a6f8d7f4fb4dc9356feab27fa364de03f9954c2bcaf2a050ccb8f121603c6c0c969b2c3f6e361493204f7972145bfee58701b75deca0de");

        const tx = eth.signTransaction(
            "44'/60'/0'/0",
            serializedTx,
        );

        const right_clicks = model.letter === 'S' ? 6 : 4;

        // Wait for the application to actually load and parse the transaction
        await waitForAppScreen(sim);
        // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
        await sim.navigateAndCompareSnapshots('.', model.name + '_swap_tokens', [right_clicks, 0]);

        await tx;
    }));
});

