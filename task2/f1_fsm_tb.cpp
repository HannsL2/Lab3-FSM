#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vf1_fsm.h"

#include "vbuddy.cpp"

#define MAX_SIM_CYC 1000000

int main (int argc, char **argv){
    Verilated::commandArgs(argc, argv);

    Vf1_fsm* top = new Vf1_fsm;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("f1_fsm.vcd");

    if (vbdOpen() != 1) {
        tfp->close();
        delete tfp;
        delete top;
        return -1;
    }

    vbdHeader("L3T2: F1 Lights");
    vbdSetMode(1);

    top->clk = 0;
    top->rst = 1;
    top->en = 0;
    top->eval();

    for (int simcyc = 0; simcyc < MAX_SIM_CYC; simcyc++) {
        top->rst = (simcyc < 2);
        top->en = vbdFlag();

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