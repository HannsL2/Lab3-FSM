module lfsr(
    input   logic       clk,
    input   logic       rst,
    input   logic       en,
    output  logic [3:0] data_out
);

always_ff @(posedge clk or posedge rst) begin
    if (rst)
        data_out <= 4'b0001;
    else if (en)
        data_out <= {data_out[2:0], data_out[3] ^ data_out[2]};
end

endmodule
