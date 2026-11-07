#!/bin/sh
set -e

# Translate the FSM and include the C++ testbench.
verilator -Wall --cc --trace --top-module f1_fsm \
    f1_fsm.sv --exe f1_fsm_tb.cpp

# Compile the simulation executable.
make -j -C obj_dir -f Vf1_fsm.mk Vf1_fsm

# Run the simulation.
./obj_dir/Vf1_fsm