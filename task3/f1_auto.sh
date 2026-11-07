#!/bin/sh
set -e

# Translate the top-level module and both submodules.
verilator -Wall --cc --trace --top-module f1_auto \
    f1_auto.sv clktick.sv f1_fsm.sv --exe f1_auto_tb.cpp

# Build the simulation.
make -j -C obj_dir -f Vf1_auto.mk Vf1_auto

# Run it.
./obj_dir/Vf1_auto