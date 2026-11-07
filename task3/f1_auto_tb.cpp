#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vf1_auto.h"

#include "../vbuddy.cpp"

#define MAX_SIM_CYC 1000000

int main (int argc, char **argv){
    Verilated::commandArgs(argc, argv);

    Vf1_auto* top = new Vf1_auto;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("f1_auto.vcd");

    if (vbdOpen() != 1) {
        tfp->close();
        delete tfp;
        delete top;
        return -1;
    }

    vbdHeader("L3T3: F1 Lights");

    top->clk = 0;
    top->rst = 1;
    top->eval();

    for (int simcyc = 0; simcyc < MAX_SIM_CYC; simcyc++) {
        top->rst = (simcyc < 2);

        // Generate one complete clock cycle.
        for (int tick = 0; tick < 2; tick++) {
            top->clk = !top->clk;
            top->eval();
            tfp->dump(2ULL * simcyc + tick);
        }

        // Display the FSM output and cycle count.
        vbdBar(top->data_out);
        vbdCycle(simcyc);

        // Press q in the terminal to stop.
        if (Verilated::gotFinish() || vbdGetkey() == 'q')
            break;
    }

    vbdClose();

    top->final();
    tfp->close();
    delete tfp;
    delete top;

    return 0;
}