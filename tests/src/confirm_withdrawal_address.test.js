import "core-js/stable";
import "regenerator-runtime/runtime";
import {nano_models, txFromEtherscan, waitForAppScreen, zemu} from './test.fixture';

// Test from replayed transaction: https://etherscan.io/tx/0xc2d6730f16d60e357fbd2125a8d94a76c7458a527da3696392a9823741976234
nano_models.forEach(function (model) {
    jest.setTimeout(20000)
    test('[Nano ' + model.letter + '] Confirm Withdrawal Address', zemu(model, async (sim, eth) => {

        // The rawTx of the tx up above is accessible through: https://etherscan.io/getRawTx?tx=0xc2d6730f16d60e357fbd2125a8d94a76c7458a527da3696392a9823741976234
        const serializedTx = txFromEtherscan("0x02f88f01038405f5e100851dfa1272b982c781941d8f8f00cfa6758d7be78336684788fb0ee0fa4680a4bd439126000000000000000000000000cf082b0967cd526667973da4a1fbcec29fa1c090c080a004ae36214ea8d54367abbbacb40c20232897051a1153724aeb18a448dbc6df74a05957a09d7949f1f56eb55754f50de24972ecca51532ae5ec19580b289a1cd532");

        const tx = eth.signTransaction(
            "44'/60'/0'/0",
            serializedTx,
        );

        const right_clicks = model.letter === 'S' ? 8 : 4;

        // Wait for the application to actually load and parse the transaction
        await waitForAppScreen(sim);
        // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
        await sim.navigateAndCompareSnapshots('.', model.name + '_confirm_withdrawal_address', [right_clicks, 0]);

        await tx;
    }));
});

