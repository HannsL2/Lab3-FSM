module f1_auto (
    input logic clk,
    input logic rst,
    output logic [7:0] data_out
);

    logic tick;

    //Generate tick every 30 clock cycles (base on my personal testing)
    clktick timer (
        .clk(clk),
        .rst(rst),
        .en(1'b1),
        .N(16'd29),
        .tick(tick)
    );

    // Advance the f1 sequence whenever tick is high
    f1_fsm lights(
        .clk(clk),
        .rst(rst),
        .en(tick),
        .data_out(data_out)
    );

endmodule
