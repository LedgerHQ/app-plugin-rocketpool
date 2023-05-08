import "core-js/stable";
import "regenerator-runtime/runtime";
import {nano_models, txFromEtherscan, waitForAppScreen, zemu} from './test.fixture';

// Test from replayed transaction: https://etherscan.io/tx/0xa9691a660542225f408bbe595c53c1f14cbee128c8efc014ee9a2f6b02ad7e2f
nano_models.forEach(function (model) {
    jest.setTimeout(20000)
    test('[Nano ' + model.letter + '] Set Withdrawal Address', zemu(model, async (sim, eth) => {

        // The rawTx of the tx up above is accessible through: https://etherscan.io/getRawTx?tx=0xa9691a660542225f408bbe595c53c1f14cbee128c8efc014ee9a2f6b02ad7e2f
        const serializedTx = txFromEtherscan("0x02f8d101018477359400851176592e0083011208941d8f8f00cfa6758d7be78336684788fb0ee0fa4680b864a543ccea000000000000000000000000aa664f418d3b4a7b49a1b2c91e940773b8656a9f000000000000000000000000c9dab658b568cfa31562383afdc274367ba3026c0000000000000000000000000000000000000000000000000000000000000000c080a0d7693af5cd1d647366b8c953a79401dff0302e2ea9e70c9760c310a43b9a137ca00e034de2c2063be8b31681c851dcb57049c323decf0cbc740fdb6b1e5d732560");

        const tx = eth.signTransaction(
            "44'/60'/0'/0",
            serializedTx,
        );

        const right_clicks = model.letter === 'S' ? 10 : 6;

        // Wait for the application to actually load and parse the transaction
        await waitForAppScreen(sim);
        // Navigate the display by pressing the right button `right_clicks` times, then pressing both buttons to accept the transaction.
        await sim.navigateAndCompareSnapshots('.', model.name + '_set_withdrawal_address', [right_clicks, 0]);

        await tx;
    }));
});
