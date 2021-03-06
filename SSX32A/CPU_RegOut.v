
module T_NMOS (D,S,G);
input G;
inout D,S;
endmodule
module ROMHCell8_000 (W, B);
output  [31:0] B;
input [63:0]  W;

T_NMOS NW0_0_0_( B[0], gnd, W[0]);
T_NMOS NW0_1_0_( B[1], gnd, W[0]);
T_NMOS NW0_2_0_( B[2], gnd, W[0]);
T_NMOS NW0_1_1_( B[1], gnd, W[1]);
T_NMOS NW0_0_2_( B[0], gnd, W[2]);
T_NMOS NW0_2_2_( B[2], gnd, W[2]);
T_NMOS NW0_3_2_( B[3], gnd, W[2]);
T_NMOS NW0_0_3_( B[0], gnd, W[3]);
T_NMOS NW0_1_4_( B[1], gnd, W[4]);
T_NMOS NW0_2_4_( B[2], gnd, W[4]);
T_NMOS NW0_0_5_( B[0], gnd, W[5]);
T_NMOS NW0_2_5_( B[2], gnd, W[5]);
T_NMOS NW0_0_6_( B[0], gnd, W[6]);
T_NMOS NW0_0_7_( B[0], gnd, W[7]);
T_NMOS NW0_2_7_( B[2], gnd, W[7]);
T_NMOS NW0_0_9_( B[0], gnd, W[9]);
T_NMOS NW0_1_9_( B[1], gnd, W[9]);
T_NMOS NW0_2_9_( B[2], gnd, W[9]);
T_NMOS NW0_3_9_( B[3], gnd, W[9]);
T_NMOS NW0_0_10_( B[0], gnd, W[10]);
T_NMOS NW0_0_11_( B[0], gnd, W[11]);
T_NMOS NW0_1_11_( B[1], gnd, W[11]);
T_NMOS NW0_2_11_( B[2], gnd, W[11]);
T_NMOS NW0_3_11_( B[3], gnd, W[11]);
T_NMOS NW0_1_12_( B[1], gnd, W[12]);
T_NMOS NW0_3_12_( B[3], gnd, W[12]);
T_NMOS NW0_0_13_( B[0], gnd, W[13]);
T_NMOS NW0_1_13_( B[1], gnd, W[13]);
T_NMOS NW0_2_13_( B[2], gnd, W[13]);
T_NMOS NW0_3_13_( B[3], gnd, W[13]);
T_NMOS NW0_0_14_( B[0], gnd, W[14]);
T_NMOS NW0_1_14_( B[1], gnd, W[14]);
T_NMOS NW0_2_14_( B[2], gnd, W[14]);
T_NMOS NW0_3_14_( B[3], gnd, W[14]);
T_NMOS NW0_2_15_( B[2], gnd, W[15]);
T_NMOS NW0_1_16_( B[1], gnd, W[16]);
T_NMOS NW0_1_17_( B[1], gnd, W[17]);
T_NMOS NW0_2_17_( B[2], gnd, W[17]);
T_NMOS NW0_0_18_( B[0], gnd, W[18]);
T_NMOS NW0_2_18_( B[2], gnd, W[18]);
T_NMOS NW0_3_18_( B[3], gnd, W[18]);
T_NMOS NW0_0_19_( B[0], gnd, W[19]);
T_NMOS NW0_1_19_( B[1], gnd, W[19]);
T_NMOS NW0_0_21_( B[0], gnd, W[21]);
T_NMOS NW0_3_21_( B[3], gnd, W[21]);
T_NMOS NW0_0_22_( B[0], gnd, W[22]);
T_NMOS NW0_1_22_( B[1], gnd, W[22]);
T_NMOS NW0_1_23_( B[1], gnd, W[23]);
T_NMOS NW0_0_24_( B[0], gnd, W[24]);
T_NMOS NW0_3_24_( B[3], gnd, W[24]);
T_NMOS NW0_1_25_( B[1], gnd, W[25]);
T_NMOS NW0_3_25_( B[3], gnd, W[25]);
T_NMOS NW0_3_26_( B[3], gnd, W[26]);
T_NMOS NW0_0_27_( B[0], gnd, W[27]);
T_NMOS NW0_1_27_( B[1], gnd, W[27]);
T_NMOS NW0_3_27_( B[3], gnd, W[27]);
T_NMOS NW0_3_29_( B[3], gnd, W[29]);
T_NMOS NW0_2_30_( B[2], gnd, W[30]);
T_NMOS NW0_3_30_( B[3], gnd, W[30]);
T_NMOS NW0_1_31_( B[1], gnd, W[31]);
T_NMOS NW0_2_31_( B[2], gnd, W[31]);
T_NMOS NW0_0_32_( B[0], gnd, W[32]);
T_NMOS NW0_3_32_( B[3], gnd, W[32]);
T_NMOS NW0_0_33_( B[0], gnd, W[33]);
T_NMOS NW0_1_33_( B[1], gnd, W[33]);
T_NMOS NW0_0_34_( B[0], gnd, W[34]);
T_NMOS NW0_1_35_( B[1], gnd, W[35]);
T_NMOS NW0_3_35_( B[3], gnd, W[35]);
T_NMOS NW0_1_36_( B[1], gnd, W[36]);
T_NMOS NW0_2_36_( B[2], gnd, W[36]);
T_NMOS NW0_3_36_( B[3], gnd, W[36]);
T_NMOS NW0_0_37_( B[0], gnd, W[37]);
T_NMOS NW0_1_37_( B[1], gnd, W[37]);
T_NMOS NW0_3_37_( B[3], gnd, W[37]);
T_NMOS NW0_0_38_( B[0], gnd, W[38]);
T_NMOS NW0_1_38_( B[1], gnd, W[38]);
T_NMOS NW0_1_39_( B[1], gnd, W[39]);
T_NMOS NW0_1_40_( B[1], gnd, W[40]);
T_NMOS NW0_3_40_( B[3], gnd, W[40]);
T_NMOS NW0_0_41_( B[0], gnd, W[41]);
T_NMOS NW0_1_41_( B[1], gnd, W[41]);
T_NMOS NW0_2_41_( B[2], gnd, W[41]);
T_NMOS NW0_0_42_( B[0], gnd, W[42]);
T_NMOS NW0_3_42_( B[3], gnd, W[42]);
T_NMOS NW0_0_43_( B[0], gnd, W[43]);
T_NMOS NW0_1_43_( B[1], gnd, W[43]);
T_NMOS NW0_3_43_( B[3], gnd, W[43]);
T_NMOS NW0_0_44_( B[0], gnd, W[44]);
T_NMOS NW0_2_44_( B[2], gnd, W[44]);
T_NMOS NW0_2_45_( B[2], gnd, W[45]);
T_NMOS NW0_3_45_( B[3], gnd, W[45]);
T_NMOS NW0_0_46_( B[0], gnd, W[46]);
T_NMOS NW0_1_46_( B[1], gnd, W[46]);
T_NMOS NW0_0_47_( B[0], gnd, W[47]);
T_NMOS NW0_2_47_( B[2], gnd, W[47]);
T_NMOS NW0_3_47_( B[3], gnd, W[47]);
T_NMOS NW0_1_48_( B[1], gnd, W[48]);
T_NMOS NW0_2_48_( B[2], gnd, W[48]);
T_NMOS NW0_0_49_( B[0], gnd, W[49]);
T_NMOS NW0_1_49_( B[1], gnd, W[49]);
T_NMOS NW0_3_49_( B[3], gnd, W[49]);
T_NMOS NW0_0_50_( B[0], gnd, W[50]);
T_NMOS NW0_2_50_( B[2], gnd, W[50]);
T_NMOS NW0_3_50_( B[3], gnd, W[50]);
T_NMOS NW0_0_51_( B[0], gnd, W[51]);
T_NMOS NW0_1_51_( B[1], gnd, W[51]);
T_NMOS NW0_2_51_( B[2], gnd, W[51]);
T_NMOS NW0_3_51_( B[3], gnd, W[51]);
T_NMOS NW0_2_52_( B[2], gnd, W[52]);
T_NMOS NW0_3_52_( B[3], gnd, W[52]);
T_NMOS NW0_1_53_( B[1], gnd, W[53]);
T_NMOS NW0_2_53_( B[2], gnd, W[53]);
T_NMOS NW0_0_54_( B[0], gnd, W[54]);
T_NMOS NW0_1_55_( B[1], gnd, W[55]);
T_NMOS NW0_2_55_( B[2], gnd, W[55]);
T_NMOS NW0_0_56_( B[0], gnd, W[56]);
T_NMOS NW0_3_56_( B[3], gnd, W[56]);
T_NMOS NW0_3_57_( B[3], gnd, W[57]);
T_NMOS NW0_3_58_( B[3], gnd, W[58]);
T_NMOS NW0_1_59_( B[1], gnd, W[59]);
T_NMOS NW0_3_59_( B[3], gnd, W[59]);
T_NMOS NW0_0_60_( B[0], gnd, W[60]);
T_NMOS NW0_2_60_( B[2], gnd, W[60]);
T_NMOS NW0_0_61_( B[0], gnd, W[61]);
T_NMOS NW0_1_61_( B[1], gnd, W[61]);
T_NMOS NW0_1_62_( B[1], gnd, W[62]);
T_NMOS NW0_3_62_( B[3], gnd, W[62]);
T_NMOS NW0_0_63_( B[0], gnd, W[63]);
T_NMOS NW1_0_0_( B[4], gnd, W[0]);
T_NMOS NW1_3_0_( B[7], gnd, W[0]);
T_NMOS NW1_1_1_( B[5], gnd, W[1]);
T_NMOS NW1_0_2_( B[4], gnd, W[2]);
T_NMOS NW1_2_2_( B[6], gnd, W[2]);
T_NMOS NW1_0_3_( B[4], gnd, W[3]);
T_NMOS NW1_1_3_( B[5], gnd, W[3]);
T_NMOS NW1_3_3_( B[7], gnd, W[3]);
T_NMOS NW1_0_4_( B[4], gnd, W[4]);
T_NMOS NW1_1_4_( B[5], gnd, W[4]);
T_NMOS NW1_2_4_( B[6], gnd, W[4]);
T_NMOS NW1_0_5_( B[4], gnd, W[5]);
T_NMOS NW1_1_5_( B[5], gnd, W[5]);
T_NMOS NW1_2_5_( B[6], gnd, W[5]);
T_NMOS NW1_3_5_( B[7], gnd, W[5]);
T_NMOS NW1_0_6_( B[4], gnd, W[6]);
T_NMOS NW1_1_6_( B[5], gnd, W[6]);
T_NMOS NW1_2_7_( B[6], gnd, W[7]);
T_NMOS NW1_3_7_( B[7], gnd, W[7]);
T_NMOS NW1_1_8_( B[5], gnd, W[8]);
T_NMOS NW1_1_9_( B[5], gnd, W[9]);
T_NMOS NW1_2_9_( B[6], gnd, W[9]);
T_NMOS NW1_0_10_( B[4], gnd, W[10]);
T_NMOS NW1_1_10_( B[5], gnd, W[10]);
T_NMOS NW1_2_10_( B[6], gnd, W[10]);
T_NMOS NW1_0_11_( B[4], gnd, W[11]);
T_NMOS NW1_1_11_( B[5], gnd, W[11]);
T_NMOS NW1_3_11_( B[7], gnd, W[11]);
T_NMOS NW1_0_12_( B[4], gnd, W[12]);
T_NMOS NW1_3_12_( B[7], gnd, W[12]);
T_NMOS NW1_0_13_( B[4], gnd, W[13]);
T_NMOS NW1_1_13_( B[5], gnd, W[13]);
T_NMOS NW1_0_14_( B[4], gnd, W[14]);
T_NMOS NW1_1_14_( B[5], gnd, W[14]);
T_NMOS NW1_3_14_( B[7], gnd, W[14]);
T_NMOS NW1_0_15_( B[4], gnd, W[15]);
T_NMOS NW1_2_15_( B[6], gnd, W[15]);
T_NMOS NW1_3_15_( B[7], gnd, W[15]);
T_NMOS NW1_0_16_( B[4], gnd, W[16]);
T_NMOS NW1_1_16_( B[5], gnd, W[16]);
T_NMOS NW1_0_17_( B[4], gnd, W[17]);
T_NMOS NW1_3_17_( B[7], gnd, W[17]);
T_NMOS NW1_2_18_( B[6], gnd, W[18]);
T_NMOS NW1_3_19_( B[7], gnd, W[19]);
T_NMOS NW1_0_20_( B[4], gnd, W[20]);
T_NMOS NW1_2_20_( B[6], gnd, W[20]);
T_NMOS NW1_2_21_( B[6], gnd, W[21]);
T_NMOS NW1_3_21_( B[7], gnd, W[21]);
T_NMOS NW1_0_22_( B[4], gnd, W[22]);
T_NMOS NW1_3_22_( B[7], gnd, W[22]);
T_NMOS NW1_1_23_( B[5], gnd, W[23]);
T_NMOS NW1_3_23_( B[7], gnd, W[23]);
T_NMOS NW1_1_24_( B[5], gnd, W[24]);
T_NMOS NW1_2_24_( B[6], gnd, W[24]);
T_NMOS NW1_1_25_( B[5], gnd, W[25]);
T_NMOS NW1_2_25_( B[6], gnd, W[25]);
T_NMOS NW1_0_26_( B[4], gnd, W[26]);
T_NMOS NW1_1_26_( B[5], gnd, W[26]);
T_NMOS NW1_3_26_( B[7], gnd, W[26]);
T_NMOS NW1_0_27_( B[4], gnd, W[27]);
T_NMOS NW1_1_28_( B[5], gnd, W[28]);
T_NMOS NW1_2_28_( B[6], gnd, W[28]);
T_NMOS NW1_3_28_( B[7], gnd, W[28]);
T_NMOS NW1_2_29_( B[6], gnd, W[29]);
T_NMOS NW1_0_30_( B[4], gnd, W[30]);
T_NMOS NW1_2_30_( B[6], gnd, W[30]);
T_NMOS NW1_1_31_( B[5], gnd, W[31]);
T_NMOS NW1_2_31_( B[6], gnd, W[31]);
T_NMOS NW1_3_31_( B[7], gnd, W[31]);
T_NMOS NW1_0_32_( B[4], gnd, W[32]);
T_NMOS NW1_1_33_( B[5], gnd, W[33]);
T_NMOS NW1_2_33_( B[6], gnd, W[33]);
T_NMOS NW1_0_34_( B[4], gnd, W[34]);
T_NMOS NW1_1_34_( B[5], gnd, W[34]);
T_NMOS NW1_2_34_( B[6], gnd, W[34]);
T_NMOS NW1_0_35_( B[4], gnd, W[35]);
T_NMOS NW1_1_35_( B[5], gnd, W[35]);
T_NMOS NW1_2_35_( B[6], gnd, W[35]);
T_NMOS NW1_0_36_( B[4], gnd, W[36]);
T_NMOS NW1_1_36_( B[5], gnd, W[36]);
T_NMOS NW1_0_37_( B[4], gnd, W[37]);
T_NMOS NW1_2_37_( B[6], gnd, W[37]);
T_NMOS NW1_0_38_( B[4], gnd, W[38]);
T_NMOS NW1_1_38_( B[5], gnd, W[38]);
T_NMOS NW1_3_38_( B[7], gnd, W[38]);
T_NMOS NW1_2_40_( B[6], gnd, W[40]);
T_NMOS NW1_3_40_( B[7], gnd, W[40]);
T_NMOS NW1_2_41_( B[6], gnd, W[41]);
T_NMOS NW1_3_41_( B[7], gnd, W[41]);
T_NMOS NW1_1_42_( B[5], gnd, W[42]);
T_NMOS NW1_3_42_( B[7], gnd, W[42]);
T_NMOS NW1_1_43_( B[5], gnd, W[43]);
T_NMOS NW1_2_43_( B[6], gnd, W[43]);
T_NMOS NW1_3_44_( B[7], gnd, W[44]);
T_NMOS NW1_1_46_( B[5], gnd, W[46]);
T_NMOS NW1_3_47_( B[7], gnd, W[47]);
T_NMOS NW1_2_48_( B[6], gnd, W[48]);
T_NMOS NW1_0_49_( B[4], gnd, W[49]);
T_NMOS NW1_1_49_( B[5], gnd, W[49]);
T_NMOS NW1_0_50_( B[4], gnd, W[50]);
T_NMOS NW1_2_50_( B[6], gnd, W[50]);
T_NMOS NW1_0_51_( B[4], gnd, W[51]);
T_NMOS NW1_1_51_( B[5], gnd, W[51]);
T_NMOS NW1_1_52_( B[5], gnd, W[52]);
T_NMOS NW1_3_52_( B[7], gnd, W[52]);
T_NMOS NW1_0_53_( B[4], gnd, W[53]);
T_NMOS NW1_3_53_( B[7], gnd, W[53]);
T_NMOS NW1_2_54_( B[6], gnd, W[54]);
T_NMOS NW1_3_54_( B[7], gnd, W[54]);
T_NMOS NW1_0_55_( B[4], gnd, W[55]);
T_NMOS NW1_0_56_( B[4], gnd, W[56]);
T_NMOS NW1_0_57_( B[4], gnd, W[57]);
T_NMOS NW1_1_57_( B[5], gnd, W[57]);
T_NMOS NW1_2_57_( B[6], gnd, W[57]);
T_NMOS NW1_1_58_( B[5], gnd, W[58]);
T_NMOS NW1_0_59_( B[4], gnd, W[59]);
T_NMOS NW1_2_59_( B[6], gnd, W[59]);
T_NMOS NW1_3_59_( B[7], gnd, W[59]);
T_NMOS NW1_0_60_( B[4], gnd, W[60]);
T_NMOS NW1_0_61_( B[4], gnd, W[61]);
T_NMOS NW1_1_61_( B[5], gnd, W[61]);
T_NMOS NW1_2_61_( B[6], gnd, W[61]);
T_NMOS NW1_0_62_( B[4], gnd, W[62]);
T_NMOS NW1_1_62_( B[5], gnd, W[62]);
T_NMOS NW1_2_62_( B[6], gnd, W[62]);
T_NMOS NW1_3_62_( B[7], gnd, W[62]);
T_NMOS NW1_1_63_( B[5], gnd, W[63]);
T_NMOS NW1_3_63_( B[7], gnd, W[63]);
T_NMOS NW2_2_0_( B[10], gnd, W[0]);
T_NMOS NW2_0_1_( B[8], gnd, W[1]);
T_NMOS NW2_2_1_( B[10], gnd, W[1]);
T_NMOS NW2_0_2_( B[8], gnd, W[2]);
T_NMOS NW2_1_2_( B[9], gnd, W[2]);
T_NMOS NW2_3_2_( B[11], gnd, W[2]);
T_NMOS NW2_2_3_( B[10], gnd, W[3]);
T_NMOS NW2_3_3_( B[11], gnd, W[3]);
T_NMOS NW2_2_4_( B[10], gnd, W[4]);
T_NMOS NW2_3_4_( B[11], gnd, W[4]);
T_NMOS NW2_1_5_( B[9], gnd, W[5]);
T_NMOS NW2_2_5_( B[10], gnd, W[5]);
T_NMOS NW2_3_5_( B[11], gnd, W[5]);
T_NMOS NW2_0_6_( B[8], gnd, W[6]);
T_NMOS NW2_2_6_( B[10], gnd, W[6]);
T_NMOS NW2_3_6_( B[11], gnd, W[6]);
T_NMOS NW2_0_7_( B[8], gnd, W[7]);
T_NMOS NW2_2_7_( B[10], gnd, W[7]);
T_NMOS NW2_3_7_( B[11], gnd, W[7]);
T_NMOS NW2_2_8_( B[10], gnd, W[8]);
T_NMOS NW2_2_9_( B[10], gnd, W[9]);
T_NMOS NW2_3_9_( B[11], gnd, W[9]);
T_NMOS NW2_0_10_( B[8], gnd, W[10]);
T_NMOS NW2_1_10_( B[9], gnd, W[10]);
T_NMOS NW2_2_10_( B[10], gnd, W[10]);
T_NMOS NW2_3_10_( B[11], gnd, W[10]);
T_NMOS NW2_2_11_( B[10], gnd, W[11]);
T_NMOS NW2_3_11_( B[11], gnd, W[11]);
T_NMOS NW2_0_12_( B[8], gnd, W[12]);
T_NMOS NW2_2_12_( B[10], gnd, W[12]);
T_NMOS NW2_0_13_( B[8], gnd, W[13]);
T_NMOS NW2_2_13_( B[10], gnd, W[13]);
T_NMOS NW2_3_13_( B[11], gnd, W[13]);
T_NMOS NW2_1_14_( B[9], gnd, W[14]);
T_NMOS NW2_0_15_( B[8], gnd, W[15]);
T_NMOS NW2_1_15_( B[9], gnd, W[15]);
T_NMOS NW2_3_17_( B[11], gnd, W[17]);
T_NMOS NW2_2_18_( B[10], gnd, W[18]);
T_NMOS NW2_3_18_( B[11], gnd, W[18]);
T_NMOS NW2_0_19_( B[8], gnd, W[19]);
T_NMOS NW2_1_19_( B[9], gnd, W[19]);
T_NMOS NW2_2_19_( B[10], gnd, W[19]);
T_NMOS NW2_3_19_( B[11], gnd, W[19]);
T_NMOS NW2_1_21_( B[9], gnd, W[21]);
T_NMOS NW2_0_22_( B[8], gnd, W[22]);
T_NMOS NW2_3_22_( B[11], gnd, W[22]);
T_NMOS NW2_3_23_( B[11], gnd, W[23]);
T_NMOS NW2_0_24_( B[8], gnd, W[24]);
T_NMOS NW2_2_24_( B[10], gnd, W[24]);
T_NMOS NW2_0_25_( B[8], gnd, W[25]);
T_NMOS NW2_2_25_( B[10], gnd, W[25]);
T_NMOS NW2_3_25_( B[11], gnd, W[25]);
T_NMOS NW2_1_26_( B[9], gnd, W[26]);
T_NMOS NW2_3_26_( B[11], gnd, W[26]);
T_NMOS NW2_0_27_( B[8], gnd, W[27]);
T_NMOS NW2_2_27_( B[10], gnd, W[27]);
T_NMOS NW2_0_28_( B[8], gnd, W[28]);
T_NMOS NW2_2_28_( B[10], gnd, W[28]);
T_NMOS NW2_3_28_( B[11], gnd, W[28]);
T_NMOS NW2_0_29_( B[8], gnd, W[29]);
T_NMOS NW2_1_29_( B[9], gnd, W[29]);
T_NMOS NW2_2_29_( B[10], gnd, W[29]);
T_NMOS NW2_3_30_( B[11], gnd, W[30]);
T_NMOS NW2_1_31_( B[9], gnd, W[31]);
T_NMOS NW2_3_31_( B[11], gnd, W[31]);
T_NMOS NW2_0_32_( B[8], gnd, W[32]);
T_NMOS NW2_0_33_( B[8], gnd, W[33]);
T_NMOS NW2_1_33_( B[9], gnd, W[33]);
T_NMOS NW2_0_35_( B[8], gnd, W[35]);
T_NMOS NW2_0_36_( B[8], gnd, W[36]);
T_NMOS NW2_0_37_( B[8], gnd, W[37]);
T_NMOS NW2_1_37_( B[9], gnd, W[37]);
T_NMOS NW2_2_37_( B[10], gnd, W[37]);
T_NMOS NW2_0_38_( B[8], gnd, W[38]);
T_NMOS NW2_2_38_( B[10], gnd, W[38]);
T_NMOS NW2_3_38_( B[11], gnd, W[38]);
T_NMOS NW2_0_39_( B[8], gnd, W[39]);
T_NMOS NW2_1_39_( B[9], gnd, W[39]);
T_NMOS NW2_2_39_( B[10], gnd, W[39]);
T_NMOS NW2_3_39_( B[11], gnd, W[39]);
T_NMOS NW2_0_40_( B[8], gnd, W[40]);
T_NMOS NW2_1_40_( B[9], gnd, W[40]);
T_NMOS NW2_0_41_( B[8], gnd, W[41]);
T_NMOS NW2_3_41_( B[11], gnd, W[41]);
T_NMOS NW2_0_42_( B[8], gnd, W[42]);
T_NMOS NW2_2_42_( B[10], gnd, W[42]);
T_NMOS NW2_3_42_( B[11], gnd, W[42]);
T_NMOS NW2_1_43_( B[9], gnd, W[43]);
T_NMOS NW2_3_44_( B[11], gnd, W[44]);
T_NMOS NW2_1_45_( B[9], gnd, W[45]);
T_NMOS NW2_2_45_( B[10], gnd, W[45]);
T_NMOS NW2_3_45_( B[11], gnd, W[45]);
T_NMOS NW2_1_46_( B[9], gnd, W[46]);
T_NMOS NW2_2_46_( B[10], gnd, W[46]);
T_NMOS NW2_0_47_( B[8], gnd, W[47]);
T_NMOS NW2_3_47_( B[11], gnd, W[47]);
T_NMOS NW2_0_48_( B[8], gnd, W[48]);
T_NMOS NW2_2_48_( B[10], gnd, W[48]);
T_NMOS NW2_3_48_( B[11], gnd, W[48]);
T_NMOS NW2_0_49_( B[8], gnd, W[49]);
T_NMOS NW2_2_50_( B[10], gnd, W[50]);
T_NMOS NW2_1_51_( B[9], gnd, W[51]);
T_NMOS NW2_2_51_( B[10], gnd, W[51]);
T_NMOS NW2_3_51_( B[11], gnd, W[51]);
T_NMOS NW2_2_52_( B[10], gnd, W[52]);
T_NMOS NW2_3_52_( B[11], gnd, W[52]);
T_NMOS NW2_0_53_( B[8], gnd, W[53]);
T_NMOS NW2_1_53_( B[9], gnd, W[53]);
T_NMOS NW2_2_53_( B[10], gnd, W[53]);
T_NMOS NW2_3_53_( B[11], gnd, W[53]);
T_NMOS NW2_0_54_( B[8], gnd, W[54]);
T_NMOS NW2_2_54_( B[10], gnd, W[54]);
T_NMOS NW2_1_55_( B[9], gnd, W[55]);
T_NMOS NW2_0_56_( B[8], gnd, W[56]);
T_NMOS NW2_1_56_( B[9], gnd, W[56]);
T_NMOS NW2_2_56_( B[10], gnd, W[56]);
T_NMOS NW2_1_57_( B[9], gnd, W[57]);
T_NMOS NW2_2_57_( B[10], gnd, W[57]);
T_NMOS NW2_2_58_( B[10], gnd, W[58]);
T_NMOS NW2_3_58_( B[11], gnd, W[58]);
T_NMOS NW2_3_59_( B[11], gnd, W[59]);
T_NMOS NW2_2_60_( B[10], gnd, W[60]);
T_NMOS NW2_0_61_( B[8], gnd, W[61]);
T_NMOS NW2_1_61_( B[9], gnd, W[61]);
T_NMOS NW2_3_61_( B[11], gnd, W[61]);
T_NMOS NW2_2_62_( B[10], gnd, W[62]);
T_NMOS NW2_0_63_( B[8], gnd, W[63]);
T_NMOS NW2_3_63_( B[11], gnd, W[63]);
T_NMOS NW3_1_0_( B[13], gnd, W[0]);
T_NMOS NW3_2_0_( B[14], gnd, W[0]);
T_NMOS NW3_3_0_( B[15], gnd, W[0]);
T_NMOS NW3_0_1_( B[12], gnd, W[1]);
T_NMOS NW3_2_1_( B[14], gnd, W[1]);
T_NMOS NW3_3_1_( B[15], gnd, W[1]);
T_NMOS NW3_1_2_( B[13], gnd, W[2]);
T_NMOS NW3_0_3_( B[12], gnd, W[3]);
T_NMOS NW3_1_3_( B[13], gnd, W[3]);
T_NMOS NW3_2_3_( B[14], gnd, W[3]);
T_NMOS NW3_3_3_( B[15], gnd, W[3]);
T_NMOS NW3_1_4_( B[13], gnd, W[4]);
T_NMOS NW3_2_4_( B[14], gnd, W[4]);
T_NMOS NW3_3_4_( B[15], gnd, W[4]);
T_NMOS NW3_0_5_( B[12], gnd, W[5]);
T_NMOS NW3_1_5_( B[13], gnd, W[5]);
T_NMOS NW3_0_6_( B[12], gnd, W[6]);
T_NMOS NW3_1_6_( B[13], gnd, W[6]);
T_NMOS NW3_3_8_( B[15], gnd, W[8]);
T_NMOS NW3_1_9_( B[13], gnd, W[9]);
T_NMOS NW3_3_9_( B[15], gnd, W[9]);
T_NMOS NW3_2_10_( B[14], gnd, W[10]);
T_NMOS NW3_0_11_( B[12], gnd, W[11]);
T_NMOS NW3_2_11_( B[14], gnd, W[11]);
T_NMOS NW3_3_11_( B[15], gnd, W[11]);
T_NMOS NW3_0_12_( B[12], gnd, W[12]);
T_NMOS NW3_1_12_( B[13], gnd, W[12]);
T_NMOS NW3_3_12_( B[15], gnd, W[12]);
T_NMOS NW3_2_13_( B[14], gnd, W[13]);
T_NMOS NW3_3_13_( B[15], gnd, W[13]);
T_NMOS NW3_0_14_( B[12], gnd, W[14]);
T_NMOS NW3_1_14_( B[13], gnd, W[14]);
T_NMOS NW3_2_14_( B[14], gnd, W[14]);
T_NMOS NW3_3_14_( B[15], gnd, W[14]);
T_NMOS NW3_3_15_( B[15], gnd, W[15]);
T_NMOS NW3_0_16_( B[12], gnd, W[16]);
T_NMOS NW3_3_17_( B[15], gnd, W[17]);
T_NMOS NW3_0_18_( B[12], gnd, W[18]);
T_NMOS NW3_2_18_( B[14], gnd, W[18]);
T_NMOS NW3_0_19_( B[12], gnd, W[19]);
T_NMOS NW3_1_19_( B[13], gnd, W[19]);
T_NMOS NW3_2_19_( B[14], gnd, W[19]);
T_NMOS NW3_0_20_( B[12], gnd, W[20]);
T_NMOS NW3_3_20_( B[15], gnd, W[20]);
T_NMOS NW3_0_21_( B[12], gnd, W[21]);
T_NMOS NW3_1_21_( B[13], gnd, W[21]);
T_NMOS NW3_2_21_( B[14], gnd, W[21]);
T_NMOS NW3_1_23_( B[13], gnd, W[23]);
T_NMOS NW3_2_23_( B[14], gnd, W[23]);
T_NMOS NW3_3_23_( B[15], gnd, W[23]);
T_NMOS NW3_0_24_( B[12], gnd, W[24]);
T_NMOS NW3_1_24_( B[13], gnd, W[24]);
T_NMOS NW3_1_25_( B[13], gnd, W[25]);
T_NMOS NW3_2_25_( B[14], gnd, W[25]);
T_NMOS NW3_1_26_( B[13], gnd, W[26]);
T_NMOS NW3_2_26_( B[14], gnd, W[26]);
T_NMOS NW3_0_27_( B[12], gnd, W[27]);
T_NMOS NW3_1_27_( B[13], gnd, W[27]);
T_NMOS NW3_3_27_( B[15], gnd, W[27]);
T_NMOS NW3_0_28_( B[12], gnd, W[28]);
T_NMOS NW3_1_28_( B[13], gnd, W[28]);
T_NMOS NW3_2_28_( B[14], gnd, W[28]);
T_NMOS NW3_1_29_( B[13], gnd, W[29]);
T_NMOS NW3_2_29_( B[14], gnd, W[29]);
T_NMOS NW3_1_30_( B[13], gnd, W[30]);
T_NMOS NW3_2_30_( B[14], gnd, W[30]);
T_NMOS NW3_3_30_( B[15], gnd, W[30]);
T_NMOS NW3_1_31_( B[13], gnd, W[31]);
T_NMOS NW3_2_31_( B[14], gnd, W[31]);
T_NMOS NW3_3_31_( B[15], gnd, W[31]);
T_NMOS NW3_0_33_( B[12], gnd, W[33]);
T_NMOS NW3_1_33_( B[13], gnd, W[33]);
T_NMOS NW3_3_33_( B[15], gnd, W[33]);
T_NMOS NW3_1_34_( B[13], gnd, W[34]);
T_NMOS NW3_2_34_( B[14], gnd, W[34]);
T_NMOS NW3_3_34_( B[15], gnd, W[34]);
T_NMOS NW3_1_35_( B[13], gnd, W[35]);
T_NMOS NW3_2_35_( B[14], gnd, W[35]);
T_NMOS NW3_2_36_( B[14], gnd, W[36]);
T_NMOS NW3_3_36_( B[15], gnd, W[36]);
T_NMOS NW3_0_37_( B[12], gnd, W[37]);
T_NMOS NW3_1_37_( B[13], gnd, W[37]);
T_NMOS NW3_3_37_( B[15], gnd, W[37]);
T_NMOS NW3_3_38_( B[15], gnd, W[38]);
T_NMOS NW3_0_39_( B[12], gnd, W[39]);
T_NMOS NW3_2_39_( B[14], gnd, W[39]);
T_NMOS NW3_3_40_( B[15], gnd, W[40]);
T_NMOS NW3_1_41_( B[13], gnd, W[41]);
T_NMOS NW3_3_41_( B[15], gnd, W[41]);
T_NMOS NW3_2_42_( B[14], gnd, W[42]);
T_NMOS NW3_1_43_( B[13], gnd, W[43]);
T_NMOS NW3_3_43_( B[15], gnd, W[43]);
T_NMOS NW3_3_44_( B[15], gnd, W[44]);
T_NMOS NW3_0_45_( B[12], gnd, W[45]);
T_NMOS NW3_1_45_( B[13], gnd, W[45]);
T_NMOS NW3_1_46_( B[13], gnd, W[46]);
T_NMOS NW3_3_46_( B[15], gnd, W[46]);
T_NMOS NW3_1_47_( B[13], gnd, W[47]);
T_NMOS NW3_2_47_( B[14], gnd, W[47]);
T_NMOS NW3_3_47_( B[15], gnd, W[47]);
T_NMOS NW3_3_48_( B[15], gnd, W[48]);
T_NMOS NW3_2_49_( B[14], gnd, W[49]);
T_NMOS NW3_3_50_( B[15], gnd, W[50]);
T_NMOS NW3_1_51_( B[13], gnd, W[51]);
T_NMOS NW3_2_51_( B[14], gnd, W[51]);
T_NMOS NW3_3_51_( B[15], gnd, W[51]);
T_NMOS NW3_0_52_( B[12], gnd, W[52]);
T_NMOS NW3_2_52_( B[14], gnd, W[52]);
T_NMOS NW3_3_52_( B[15], gnd, W[52]);
T_NMOS NW3_1_53_( B[13], gnd, W[53]);
T_NMOS NW3_1_54_( B[13], gnd, W[54]);
T_NMOS NW3_2_54_( B[14], gnd, W[54]);
T_NMOS NW3_0_55_( B[12], gnd, W[55]);
T_NMOS NW3_2_55_( B[14], gnd, W[55]);
T_NMOS NW3_3_55_( B[15], gnd, W[55]);
T_NMOS NW3_1_56_( B[13], gnd, W[56]);
T_NMOS NW3_2_56_( B[14], gnd, W[56]);
T_NMOS NW3_3_57_( B[15], gnd, W[57]);
T_NMOS NW3_1_58_( B[13], gnd, W[58]);
T_NMOS NW3_3_58_( B[15], gnd, W[58]);
T_NMOS NW3_2_59_( B[14], gnd, W[59]);
T_NMOS NW3_3_59_( B[15], gnd, W[59]);
T_NMOS NW3_0_60_( B[12], gnd, W[60]);
T_NMOS NW3_1_61_( B[13], gnd, W[61]);
T_NMOS NW3_2_61_( B[14], gnd, W[61]);
T_NMOS NW3_2_62_( B[14], gnd, W[62]);
T_NMOS NW3_3_62_( B[15], gnd, W[62]);
T_NMOS NW3_2_63_( B[14], gnd, W[63]);
T_NMOS NW4_3_0_( B[19], gnd, W[0]);
T_NMOS NW4_0_1_( B[16], gnd, W[1]);
T_NMOS NW4_3_1_( B[19], gnd, W[1]);
T_NMOS NW4_0_2_( B[16], gnd, W[2]);
T_NMOS NW4_2_2_( B[18], gnd, W[2]);
T_NMOS NW4_0_3_( B[16], gnd, W[3]);
T_NMOS NW4_1_3_( B[17], gnd, W[3]);
T_NMOS NW4_0_4_( B[16], gnd, W[4]);
T_NMOS NW4_1_4_( B[17], gnd, W[4]);
T_NMOS NW4_2_4_( B[18], gnd, W[4]);
T_NMOS NW4_3_4_( B[19], gnd, W[4]);
T_NMOS NW4_2_5_( B[18], gnd, W[5]);
T_NMOS NW4_1_6_( B[17], gnd, W[6]);
T_NMOS NW4_3_6_( B[19], gnd, W[6]);
T_NMOS NW4_2_7_( B[18], gnd, W[7]);
T_NMOS NW4_0_8_( B[16], gnd, W[8]);
T_NMOS NW4_1_8_( B[17], gnd, W[8]);
T_NMOS NW4_1_9_( B[17], gnd, W[9]);
T_NMOS NW4_3_9_( B[19], gnd, W[9]);
T_NMOS NW4_1_10_( B[17], gnd, W[10]);
T_NMOS NW4_2_10_( B[18], gnd, W[10]);
T_NMOS NW4_3_10_( B[19], gnd, W[10]);
T_NMOS NW4_1_11_( B[17], gnd, W[11]);
T_NMOS NW4_2_11_( B[18], gnd, W[11]);
T_NMOS NW4_3_11_( B[19], gnd, W[11]);
T_NMOS NW4_0_12_( B[16], gnd, W[12]);
T_NMOS NW4_0_13_( B[16], gnd, W[13]);
T_NMOS NW4_2_13_( B[18], gnd, W[13]);
T_NMOS NW4_3_13_( B[19], gnd, W[13]);
T_NMOS NW4_2_14_( B[18], gnd, W[14]);
T_NMOS NW4_0_15_( B[16], gnd, W[15]);
T_NMOS NW4_2_15_( B[18], gnd, W[15]);
T_NMOS NW4_1_16_( B[17], gnd, W[16]);
T_NMOS NW4_3_16_( B[19], gnd, W[16]);
T_NMOS NW4_1_17_( B[17], gnd, W[17]);
T_NMOS NW4_3_17_( B[19], gnd, W[17]);
T_NMOS NW4_3_18_( B[19], gnd, W[18]);
T_NMOS NW4_0_19_( B[16], gnd, W[19]);
T_NMOS NW4_2_19_( B[18], gnd, W[19]);
T_NMOS NW4_0_20_( B[16], gnd, W[20]);
T_NMOS NW4_0_21_( B[16], gnd, W[21]);
T_NMOS NW4_1_21_( B[17], gnd, W[21]);
T_NMOS NW4_1_22_( B[17], gnd, W[22]);
T_NMOS NW4_2_22_( B[18], gnd, W[22]);
T_NMOS NW4_3_22_( B[19], gnd, W[22]);
T_NMOS NW4_0_23_( B[16], gnd, W[23]);
T_NMOS NW4_1_23_( B[17], gnd, W[23]);
T_NMOS NW4_0_25_( B[16], gnd, W[25]);
T_NMOS NW4_3_25_( B[19], gnd, W[25]);
T_NMOS NW4_1_26_( B[17], gnd, W[26]);
T_NMOS NW4_2_26_( B[18], gnd, W[26]);
T_NMOS NW4_3_26_( B[19], gnd, W[26]);
T_NMOS NW4_1_27_( B[17], gnd, W[27]);
T_NMOS NW4_2_27_( B[18], gnd, W[27]);
T_NMOS NW4_3_27_( B[19], gnd, W[27]);
T_NMOS NW4_0_28_( B[16], gnd, W[28]);
T_NMOS NW4_2_28_( B[18], gnd, W[28]);
T_NMOS NW4_2_29_( B[18], gnd, W[29]);
T_NMOS NW4_0_30_( B[16], gnd, W[30]);
T_NMOS NW4_1_30_( B[17], gnd, W[30]);
T_NMOS NW4_3_30_( B[19], gnd, W[30]);
T_NMOS NW4_2_31_( B[18], gnd, W[31]);
T_NMOS NW4_3_31_( B[19], gnd, W[31]);
T_NMOS NW4_0_32_( B[16], gnd, W[32]);
T_NMOS NW4_1_32_( B[17], gnd, W[32]);
T_NMOS NW4_0_33_( B[16], gnd, W[33]);
T_NMOS NW4_2_33_( B[18], gnd, W[33]);
T_NMOS NW4_3_33_( B[19], gnd, W[33]);
T_NMOS NW4_0_34_( B[16], gnd, W[34]);
T_NMOS NW4_2_34_( B[18], gnd, W[34]);
T_NMOS NW4_3_34_( B[19], gnd, W[34]);
T_NMOS NW4_1_35_( B[17], gnd, W[35]);
T_NMOS NW4_3_35_( B[19], gnd, W[35]);
T_NMOS NW4_0_36_( B[16], gnd, W[36]);
T_NMOS NW4_0_37_( B[16], gnd, W[37]);
T_NMOS NW4_3_37_( B[19], gnd, W[37]);
T_NMOS NW4_0_38_( B[16], gnd, W[38]);
T_NMOS NW4_1_38_( B[17], gnd, W[38]);
T_NMOS NW4_2_39_( B[18], gnd, W[39]);
T_NMOS NW4_3_39_( B[19], gnd, W[39]);
T_NMOS NW4_0_40_( B[16], gnd, W[40]);
T_NMOS NW4_3_40_( B[19], gnd, W[40]);
T_NMOS NW4_1_41_( B[17], gnd, W[41]);
T_NMOS NW4_2_41_( B[18], gnd, W[41]);
T_NMOS NW4_3_41_( B[19], gnd, W[41]);
T_NMOS NW4_0_43_( B[16], gnd, W[43]);
T_NMOS NW4_1_43_( B[17], gnd, W[43]);
T_NMOS NW4_0_44_( B[16], gnd, W[44]);
T_NMOS NW4_1_44_( B[17], gnd, W[44]);
T_NMOS NW4_2_44_( B[18], gnd, W[44]);
T_NMOS NW4_0_45_( B[16], gnd, W[45]);
T_NMOS NW4_1_45_( B[17], gnd, W[45]);
T_NMOS NW4_2_45_( B[18], gnd, W[45]);
T_NMOS NW4_3_45_( B[19], gnd, W[45]);
T_NMOS NW4_0_46_( B[16], gnd, W[46]);
T_NMOS NW4_1_46_( B[17], gnd, W[46]);
T_NMOS NW4_0_47_( B[16], gnd, W[47]);
T_NMOS NW4_2_47_( B[18], gnd, W[47]);
T_NMOS NW4_3_47_( B[19], gnd, W[47]);
T_NMOS NW4_1_48_( B[17], gnd, W[48]);
T_NMOS NW4_2_50_( B[18], gnd, W[50]);
T_NMOS NW4_0_52_( B[16], gnd, W[52]);
T_NMOS NW4_1_52_( B[17], gnd, W[52]);
T_NMOS NW4_3_52_( B[19], gnd, W[52]);
T_NMOS NW4_0_53_( B[16], gnd, W[53]);
T_NMOS NW4_1_53_( B[17], gnd, W[53]);
T_NMOS NW4_2_53_( B[18], gnd, W[53]);
T_NMOS NW4_1_54_( B[17], gnd, W[54]);
T_NMOS NW4_0_55_( B[16], gnd, W[55]);
T_NMOS NW4_1_55_( B[17], gnd, W[55]);
T_NMOS NW4_1_56_( B[17], gnd, W[56]);
T_NMOS NW4_0_57_( B[16], gnd, W[57]);
T_NMOS NW4_1_57_( B[17], gnd, W[57]);
T_NMOS NW4_2_57_( B[18], gnd, W[57]);
T_NMOS NW4_3_57_( B[19], gnd, W[57]);
T_NMOS NW4_1_58_( B[17], gnd, W[58]);
T_NMOS NW4_2_58_( B[18], gnd, W[58]);
T_NMOS NW4_1_60_( B[17], gnd, W[60]);
T_NMOS NW4_3_60_( B[19], gnd, W[60]);
T_NMOS NW4_1_61_( B[17], gnd, W[61]);
T_NMOS NW4_2_61_( B[18], gnd, W[61]);
T_NMOS NW4_3_61_( B[19], gnd, W[61]);
T_NMOS NW4_0_62_( B[16], gnd, W[62]);
T_NMOS NW4_1_62_( B[17], gnd, W[62]);
T_NMOS NW4_3_62_( B[19], gnd, W[62]);
T_NMOS NW4_0_63_( B[16], gnd, W[63]);
T_NMOS NW4_1_63_( B[17], gnd, W[63]);
T_NMOS NW4_3_63_( B[19], gnd, W[63]);
T_NMOS NW5_0_0_( B[20], gnd, W[0]);
T_NMOS NW5_3_0_( B[23], gnd, W[0]);
T_NMOS NW5_0_1_( B[20], gnd, W[1]);
T_NMOS NW5_3_1_( B[23], gnd, W[1]);
T_NMOS NW5_0_2_( B[20], gnd, W[2]);
T_NMOS NW5_1_2_( B[21], gnd, W[2]);
T_NMOS NW5_3_2_( B[23], gnd, W[2]);
T_NMOS NW5_0_3_( B[20], gnd, W[3]);
T_NMOS NW5_2_3_( B[22], gnd, W[3]);
T_NMOS NW5_3_3_( B[23], gnd, W[3]);
T_NMOS NW5_0_4_( B[20], gnd, W[4]);
T_NMOS NW5_0_5_( B[20], gnd, W[5]);
T_NMOS NW5_1_5_( B[21], gnd, W[5]);
T_NMOS NW5_3_5_( B[23], gnd, W[5]);
T_NMOS NW5_0_6_( B[20], gnd, W[6]);
T_NMOS NW5_3_6_( B[23], gnd, W[6]);
T_NMOS NW5_1_7_( B[21], gnd, W[7]);
T_NMOS NW5_0_8_( B[20], gnd, W[8]);
T_NMOS NW5_3_8_( B[23], gnd, W[8]);
T_NMOS NW5_1_9_( B[21], gnd, W[9]);
T_NMOS NW5_2_9_( B[22], gnd, W[9]);
T_NMOS NW5_0_10_( B[20], gnd, W[10]);
T_NMOS NW5_2_10_( B[22], gnd, W[10]);
T_NMOS NW5_3_10_( B[23], gnd, W[10]);
T_NMOS NW5_0_11_( B[20], gnd, W[11]);
T_NMOS NW5_1_11_( B[21], gnd, W[11]);
T_NMOS NW5_2_11_( B[22], gnd, W[11]);
T_NMOS NW5_0_12_( B[20], gnd, W[12]);
T_NMOS NW5_1_12_( B[21], gnd, W[12]);
T_NMOS NW5_2_12_( B[22], gnd, W[12]);
T_NMOS NW5_1_13_( B[21], gnd, W[13]);
T_NMOS NW5_3_13_( B[23], gnd, W[13]);
T_NMOS NW5_0_14_( B[20], gnd, W[14]);
T_NMOS NW5_1_14_( B[21], gnd, W[14]);
T_NMOS NW5_0_15_( B[20], gnd, W[15]);
T_NMOS NW5_2_15_( B[22], gnd, W[15]);
T_NMOS NW5_2_16_( B[22], gnd, W[16]);
T_NMOS NW5_3_16_( B[23], gnd, W[16]);
T_NMOS NW5_3_17_( B[23], gnd, W[17]);
T_NMOS NW5_3_18_( B[23], gnd, W[18]);
T_NMOS NW5_0_19_( B[20], gnd, W[19]);
T_NMOS NW5_1_19_( B[21], gnd, W[19]);
T_NMOS NW5_3_19_( B[23], gnd, W[19]);
T_NMOS NW5_0_20_( B[20], gnd, W[20]);
T_NMOS NW5_1_20_( B[21], gnd, W[20]);
T_NMOS NW5_2_20_( B[22], gnd, W[20]);
T_NMOS NW5_1_21_( B[21], gnd, W[21]);
T_NMOS NW5_2_21_( B[22], gnd, W[21]);
T_NMOS NW5_1_22_( B[21], gnd, W[22]);
T_NMOS NW5_3_22_( B[23], gnd, W[22]);
T_NMOS NW5_0_23_( B[20], gnd, W[23]);
T_NMOS NW5_0_24_( B[20], gnd, W[24]);
T_NMOS NW5_1_24_( B[21], gnd, W[24]);
T_NMOS NW5_3_24_( B[23], gnd, W[24]);
T_NMOS NW5_2_25_( B[22], gnd, W[25]);
T_NMOS NW5_3_25_( B[23], gnd, W[25]);
T_NMOS NW5_0_26_( B[20], gnd, W[26]);
T_NMOS NW5_1_26_( B[21], gnd, W[26]);
T_NMOS NW5_2_26_( B[22], gnd, W[26]);
T_NMOS NW5_0_27_( B[20], gnd, W[27]);
T_NMOS NW5_1_27_( B[21], gnd, W[27]);
T_NMOS NW5_3_27_( B[23], gnd, W[27]);
T_NMOS NW5_0_29_( B[20], gnd, W[29]);
T_NMOS NW5_0_30_( B[20], gnd, W[30]);
T_NMOS NW5_0_32_( B[20], gnd, W[32]);
T_NMOS NW5_2_32_( B[22], gnd, W[32]);
T_NMOS NW5_3_32_( B[23], gnd, W[32]);
T_NMOS NW5_0_33_( B[20], gnd, W[33]);
T_NMOS NW5_1_33_( B[21], gnd, W[33]);
T_NMOS NW5_2_33_( B[22], gnd, W[33]);
T_NMOS NW5_3_33_( B[23], gnd, W[33]);
T_NMOS NW5_1_34_( B[21], gnd, W[34]);
T_NMOS NW5_2_34_( B[22], gnd, W[34]);
T_NMOS NW5_0_35_( B[20], gnd, W[35]);
T_NMOS NW5_1_35_( B[21], gnd, W[35]);
T_NMOS NW5_0_36_( B[20], gnd, W[36]);
T_NMOS NW5_3_36_( B[23], gnd, W[36]);
T_NMOS NW5_0_37_( B[20], gnd, W[37]);
T_NMOS NW5_0_38_( B[20], gnd, W[38]);
T_NMOS NW5_1_38_( B[21], gnd, W[38]);
T_NMOS NW5_2_38_( B[22], gnd, W[38]);
T_NMOS NW5_0_40_( B[20], gnd, W[40]);
T_NMOS NW5_0_41_( B[20], gnd, W[41]);
T_NMOS NW5_1_41_( B[21], gnd, W[41]);
T_NMOS NW5_0_42_( B[20], gnd, W[42]);
T_NMOS NW5_2_42_( B[22], gnd, W[42]);
T_NMOS NW5_0_43_( B[20], gnd, W[43]);
T_NMOS NW5_1_43_( B[21], gnd, W[43]);
T_NMOS NW5_2_43_( B[22], gnd, W[43]);
T_NMOS NW5_3_43_( B[23], gnd, W[43]);
T_NMOS NW5_0_44_( B[20], gnd, W[44]);
T_NMOS NW5_1_45_( B[21], gnd, W[45]);
T_NMOS NW5_0_46_( B[20], gnd, W[46]);
T_NMOS NW5_2_46_( B[22], gnd, W[46]);
T_NMOS NW5_3_46_( B[23], gnd, W[46]);
T_NMOS NW5_1_47_( B[21], gnd, W[47]);
T_NMOS NW5_2_47_( B[22], gnd, W[47]);
T_NMOS NW5_2_48_( B[22], gnd, W[48]);
T_NMOS NW5_1_49_( B[21], gnd, W[49]);
T_NMOS NW5_3_49_( B[23], gnd, W[49]);
T_NMOS NW5_0_50_( B[20], gnd, W[50]);
T_NMOS NW5_2_50_( B[22], gnd, W[50]);
T_NMOS NW5_2_51_( B[22], gnd, W[51]);
T_NMOS NW5_3_52_( B[23], gnd, W[52]);
T_NMOS NW5_3_53_( B[23], gnd, W[53]);
T_NMOS NW5_1_54_( B[21], gnd, W[54]);
T_NMOS NW5_1_55_( B[21], gnd, W[55]);
T_NMOS NW5_2_55_( B[22], gnd, W[55]);
T_NMOS NW5_3_55_( B[23], gnd, W[55]);
T_NMOS NW5_1_56_( B[21], gnd, W[56]);
T_NMOS NW5_2_56_( B[22], gnd, W[56]);
T_NMOS NW5_1_57_( B[21], gnd, W[57]);
T_NMOS NW5_2_58_( B[22], gnd, W[58]);
T_NMOS NW5_3_58_( B[23], gnd, W[58]);
T_NMOS NW5_0_59_( B[20], gnd, W[59]);
T_NMOS NW5_1_59_( B[21], gnd, W[59]);
T_NMOS NW5_2_59_( B[22], gnd, W[59]);
T_NMOS NW5_0_60_( B[20], gnd, W[60]);
T_NMOS NW5_2_60_( B[22], gnd, W[60]);
T_NMOS NW5_3_60_( B[23], gnd, W[60]);
T_NMOS NW5_0_61_( B[20], gnd, W[61]);
T_NMOS NW5_1_61_( B[21], gnd, W[61]);
T_NMOS NW5_2_61_( B[22], gnd, W[61]);
T_NMOS NW5_0_62_( B[20], gnd, W[62]);
T_NMOS NW5_1_62_( B[21], gnd, W[62]);
T_NMOS NW5_2_62_( B[22], gnd, W[62]);
T_NMOS NW5_3_62_( B[23], gnd, W[62]);
T_NMOS NW5_0_63_( B[20], gnd, W[63]);
T_NMOS NW6_0_0_( B[24], gnd, W[0]);
T_NMOS NW6_2_0_( B[26], gnd, W[0]);
T_NMOS NW6_0_1_( B[24], gnd, W[1]);
T_NMOS NW6_3_1_( B[27], gnd, W[1]);
T_NMOS NW6_0_2_( B[24], gnd, W[2]);
T_NMOS NW6_0_3_( B[24], gnd, W[3]);
T_NMOS NW6_2_3_( B[26], gnd, W[3]);
T_NMOS NW6_0_4_( B[24], gnd, W[4]);
T_NMOS NW6_2_4_( B[26], gnd, W[4]);
T_NMOS NW6_0_5_( B[24], gnd, W[5]);
T_NMOS NW6_1_5_( B[25], gnd, W[5]);
T_NMOS NW6_0_6_( B[24], gnd, W[6]);
T_NMOS NW6_1_6_( B[25], gnd, W[6]);
T_NMOS NW6_2_6_( B[26], gnd, W[6]);
T_NMOS NW6_0_7_( B[24], gnd, W[7]);
T_NMOS NW6_3_7_( B[27], gnd, W[7]);
T_NMOS NW6_1_8_( B[25], gnd, W[8]);
T_NMOS NW6_2_8_( B[26], gnd, W[8]);
T_NMOS NW6_3_8_( B[27], gnd, W[8]);
T_NMOS NW6_3_9_( B[27], gnd, W[9]);
T_NMOS NW6_0_10_( B[24], gnd, W[10]);
T_NMOS NW6_1_10_( B[25], gnd, W[10]);
T_NMOS NW6_2_10_( B[26], gnd, W[10]);
T_NMOS NW6_3_10_( B[27], gnd, W[10]);
T_NMOS NW6_0_12_( B[24], gnd, W[12]);
T_NMOS NW6_2_12_( B[26], gnd, W[12]);
T_NMOS NW6_3_12_( B[27], gnd, W[12]);
T_NMOS NW6_0_13_( B[24], gnd, W[13]);
T_NMOS NW6_1_13_( B[25], gnd, W[13]);
T_NMOS NW6_2_13_( B[26], gnd, W[13]);
T_NMOS NW6_0_15_( B[24], gnd, W[15]);
T_NMOS NW6_2_15_( B[26], gnd, W[15]);
T_NMOS NW6_0_16_( B[24], gnd, W[16]);
T_NMOS NW6_1_16_( B[25], gnd, W[16]);
T_NMOS NW6_2_16_( B[26], gnd, W[16]);
T_NMOS NW6_3_16_( B[27], gnd, W[16]);
T_NMOS NW6_1_17_( B[25], gnd, W[17]);
T_NMOS NW6_0_18_( B[24], gnd, W[18]);
T_NMOS NW6_2_18_( B[26], gnd, W[18]);
T_NMOS NW6_0_19_( B[24], gnd, W[19]);
T_NMOS NW6_1_19_( B[25], gnd, W[19]);
T_NMOS NW6_2_19_( B[26], gnd, W[19]);
T_NMOS NW6_3_19_( B[27], gnd, W[19]);
T_NMOS NW6_0_20_( B[24], gnd, W[20]);
T_NMOS NW6_3_20_( B[27], gnd, W[20]);
T_NMOS NW6_0_21_( B[24], gnd, W[21]);
T_NMOS NW6_1_21_( B[25], gnd, W[21]);
T_NMOS NW6_0_22_( B[24], gnd, W[22]);
T_NMOS NW6_3_22_( B[27], gnd, W[22]);
T_NMOS NW6_0_23_( B[24], gnd, W[23]);
T_NMOS NW6_1_23_( B[25], gnd, W[23]);
T_NMOS NW6_1_24_( B[25], gnd, W[24]);
T_NMOS NW6_2_24_( B[26], gnd, W[24]);
T_NMOS NW6_3_24_( B[27], gnd, W[24]);
T_NMOS NW6_0_25_( B[24], gnd, W[25]);
T_NMOS NW6_1_25_( B[25], gnd, W[25]);
T_NMOS NW6_2_25_( B[26], gnd, W[25]);
T_NMOS NW6_3_26_( B[27], gnd, W[26]);
T_NMOS NW6_1_28_( B[25], gnd, W[28]);
T_NMOS NW6_2_28_( B[26], gnd, W[28]);
T_NMOS NW6_1_29_( B[25], gnd, W[29]);
T_NMOS NW6_2_29_( B[26], gnd, W[29]);
T_NMOS NW6_3_29_( B[27], gnd, W[29]);
T_NMOS NW6_0_30_( B[24], gnd, W[30]);
T_NMOS NW6_1_30_( B[25], gnd, W[30]);
T_NMOS NW6_0_31_( B[24], gnd, W[31]);
T_NMOS NW6_1_31_( B[25], gnd, W[31]);
T_NMOS NW6_2_31_( B[26], gnd, W[31]);
T_NMOS NW6_1_32_( B[25], gnd, W[32]);
T_NMOS NW6_2_32_( B[26], gnd, W[32]);
T_NMOS NW6_3_32_( B[27], gnd, W[32]);
T_NMOS NW6_0_33_( B[24], gnd, W[33]);
T_NMOS NW6_1_33_( B[25], gnd, W[33]);
T_NMOS NW6_3_33_( B[27], gnd, W[33]);
T_NMOS NW6_1_35_( B[25], gnd, W[35]);
T_NMOS NW6_1_36_( B[25], gnd, W[36]);
T_NMOS NW6_2_36_( B[26], gnd, W[36]);
T_NMOS NW6_3_36_( B[27], gnd, W[36]);
T_NMOS NW6_1_37_( B[25], gnd, W[37]);
T_NMOS NW6_3_37_( B[27], gnd, W[37]);
T_NMOS NW6_0_38_( B[24], gnd, W[38]);
T_NMOS NW6_0_39_( B[24], gnd, W[39]);
T_NMOS NW6_2_39_( B[26], gnd, W[39]);
T_NMOS NW6_1_40_( B[25], gnd, W[40]);
T_NMOS NW6_2_40_( B[26], gnd, W[40]);
T_NMOS NW6_1_41_( B[25], gnd, W[41]);
T_NMOS NW6_2_41_( B[26], gnd, W[41]);
T_NMOS NW6_0_42_( B[24], gnd, W[42]);
T_NMOS NW6_0_43_( B[24], gnd, W[43]);
T_NMOS NW6_1_43_( B[25], gnd, W[43]);
T_NMOS NW6_2_43_( B[26], gnd, W[43]);
T_NMOS NW6_3_43_( B[27], gnd, W[43]);
T_NMOS NW6_0_44_( B[24], gnd, W[44]);
T_NMOS NW6_1_44_( B[25], gnd, W[44]);
T_NMOS NW6_3_44_( B[27], gnd, W[44]);
T_NMOS NW6_0_45_( B[24], gnd, W[45]);
T_NMOS NW6_3_45_( B[27], gnd, W[45]);
T_NMOS NW6_2_46_( B[26], gnd, W[46]);
T_NMOS NW6_2_47_( B[26], gnd, W[47]);
T_NMOS NW6_3_47_( B[27], gnd, W[47]);
T_NMOS NW6_1_48_( B[25], gnd, W[48]);
T_NMOS NW6_2_48_( B[26], gnd, W[48]);
T_NMOS NW6_0_49_( B[24], gnd, W[49]);
T_NMOS NW6_2_49_( B[26], gnd, W[49]);
T_NMOS NW6_1_50_( B[25], gnd, W[50]);
T_NMOS NW6_0_51_( B[24], gnd, W[51]);
T_NMOS NW6_2_51_( B[26], gnd, W[51]);
T_NMOS NW6_2_53_( B[26], gnd, W[53]);
T_NMOS NW6_3_53_( B[27], gnd, W[53]);
T_NMOS NW6_2_54_( B[26], gnd, W[54]);
T_NMOS NW6_3_54_( B[27], gnd, W[54]);
T_NMOS NW6_1_55_( B[25], gnd, W[55]);
T_NMOS NW6_3_55_( B[27], gnd, W[55]);
T_NMOS NW6_2_56_( B[26], gnd, W[56]);
T_NMOS NW6_3_56_( B[27], gnd, W[56]);
T_NMOS NW6_2_57_( B[26], gnd, W[57]);
T_NMOS NW6_1_58_( B[25], gnd, W[58]);
T_NMOS NW6_2_58_( B[26], gnd, W[58]);
T_NMOS NW6_0_59_( B[24], gnd, W[59]);
T_NMOS NW6_2_59_( B[26], gnd, W[59]);
T_NMOS NW6_0_60_( B[24], gnd, W[60]);
T_NMOS NW6_2_60_( B[26], gnd, W[60]);
T_NMOS NW6_1_61_( B[25], gnd, W[61]);
T_NMOS NW6_2_61_( B[26], gnd, W[61]);
T_NMOS NW6_3_61_( B[27], gnd, W[61]);
T_NMOS NW6_1_62_( B[25], gnd, W[62]);
T_NMOS NW6_0_63_( B[24], gnd, W[63]);
T_NMOS NW6_1_63_( B[25], gnd, W[63]);
T_NMOS NW7_2_0_( B[30], gnd, W[0]);
T_NMOS NW7_3_0_( B[31], gnd, W[0]);
T_NMOS NW7_1_1_( B[29], gnd, W[1]);
T_NMOS NW7_2_3_( B[30], gnd, W[3]);
T_NMOS NW7_0_4_( B[28], gnd, W[4]);
T_NMOS NW7_2_5_( B[30], gnd, W[5]);
T_NMOS NW7_3_5_( B[31], gnd, W[5]);
T_NMOS NW7_3_6_( B[31], gnd, W[6]);
T_NMOS NW7_0_7_( B[28], gnd, W[7]);
T_NMOS NW7_1_7_( B[29], gnd, W[7]);
T_NMOS NW7_3_7_( B[31], gnd, W[7]);
T_NMOS NW7_2_8_( B[30], gnd, W[8]);
T_NMOS NW7_3_8_( B[31], gnd, W[8]);
T_NMOS NW7_2_9_( B[30], gnd, W[9]);
T_NMOS NW7_3_9_( B[31], gnd, W[9]);
T_NMOS NW7_1_10_( B[29], gnd, W[10]);
T_NMOS NW7_1_11_( B[29], gnd, W[11]);
T_NMOS NW7_0_12_( B[28], gnd, W[12]);
T_NMOS NW7_0_13_( B[28], gnd, W[13]);
T_NMOS NW7_1_13_( B[29], gnd, W[13]);
T_NMOS NW7_3_13_( B[31], gnd, W[13]);
T_NMOS NW7_0_14_( B[28], gnd, W[14]);
T_NMOS NW7_3_14_( B[31], gnd, W[14]);
T_NMOS NW7_1_15_( B[29], gnd, W[15]);
T_NMOS NW7_3_15_( B[31], gnd, W[15]);
T_NMOS NW7_0_16_( B[28], gnd, W[16]);
T_NMOS NW7_0_17_( B[28], gnd, W[17]);
T_NMOS NW7_1_17_( B[29], gnd, W[17]);
T_NMOS NW7_2_17_( B[30], gnd, W[17]);
T_NMOS NW7_0_18_( B[28], gnd, W[18]);
T_NMOS NW7_3_18_( B[31], gnd, W[18]);
T_NMOS NW7_1_19_( B[29], gnd, W[19]);
T_NMOS NW7_2_19_( B[30], gnd, W[19]);
T_NMOS NW7_0_20_( B[28], gnd, W[20]);
T_NMOS NW7_1_21_( B[29], gnd, W[21]);
T_NMOS NW7_1_22_( B[29], gnd, W[22]);
T_NMOS NW7_2_22_( B[30], gnd, W[22]);
T_NMOS NW7_3_22_( B[31], gnd, W[22]);
T_NMOS NW7_0_23_( B[28], gnd, W[23]);
T_NMOS NW7_2_23_( B[30], gnd, W[23]);
T_NMOS NW7_0_24_( B[28], gnd, W[24]);
T_NMOS NW7_0_25_( B[28], gnd, W[25]);
T_NMOS NW7_1_25_( B[29], gnd, W[25]);
T_NMOS NW7_2_25_( B[30], gnd, W[25]);
T_NMOS NW7_0_26_( B[28], gnd, W[26]);
T_NMOS NW7_1_26_( B[29], gnd, W[26]);
T_NMOS NW7_2_26_( B[30], gnd, W[26]);
T_NMOS NW7_0_27_( B[28], gnd, W[27]);
T_NMOS NW7_3_27_( B[31], gnd, W[27]);
T_NMOS NW7_0_28_( B[28], gnd, W[28]);
T_NMOS NW7_2_28_( B[30], gnd, W[28]);
T_NMOS NW7_3_28_( B[31], gnd, W[28]);
T_NMOS NW7_0_29_( B[28], gnd, W[29]);
T_NMOS NW7_3_29_( B[31], gnd, W[29]);
T_NMOS NW7_0_31_( B[28], gnd, W[31]);
T_NMOS NW7_1_31_( B[29], gnd, W[31]);
T_NMOS NW7_2_31_( B[30], gnd, W[31]);
T_NMOS NW7_3_31_( B[31], gnd, W[31]);
T_NMOS NW7_0_32_( B[28], gnd, W[32]);
T_NMOS NW7_1_32_( B[29], gnd, W[32]);
T_NMOS NW7_2_32_( B[30], gnd, W[32]);
T_NMOS NW7_3_32_( B[31], gnd, W[32]);
T_NMOS NW7_0_33_( B[28], gnd, W[33]);
T_NMOS NW7_1_33_( B[29], gnd, W[33]);
T_NMOS NW7_3_33_( B[31], gnd, W[33]);
T_NMOS NW7_0_34_( B[28], gnd, W[34]);
T_NMOS NW7_1_34_( B[29], gnd, W[34]);
T_NMOS NW7_3_34_( B[31], gnd, W[34]);
T_NMOS NW7_1_35_( B[29], gnd, W[35]);
T_NMOS NW7_3_37_( B[31], gnd, W[37]);
T_NMOS NW7_0_38_( B[28], gnd, W[38]);
T_NMOS NW7_3_38_( B[31], gnd, W[38]);
T_NMOS NW7_0_39_( B[28], gnd, W[39]);
T_NMOS NW7_1_39_( B[29], gnd, W[39]);
T_NMOS NW7_3_39_( B[31], gnd, W[39]);
T_NMOS NW7_2_40_( B[30], gnd, W[40]);
T_NMOS NW7_3_40_( B[31], gnd, W[40]);
T_NMOS NW7_0_41_( B[28], gnd, W[41]);
T_NMOS NW7_1_41_( B[29], gnd, W[41]);
T_NMOS NW7_2_41_( B[30], gnd, W[41]);
T_NMOS NW7_0_42_( B[28], gnd, W[42]);
T_NMOS NW7_2_42_( B[30], gnd, W[42]);
T_NMOS NW7_3_42_( B[31], gnd, W[42]);
T_NMOS NW7_0_43_( B[28], gnd, W[43]);
T_NMOS NW7_3_43_( B[31], gnd, W[43]);
T_NMOS NW7_2_44_( B[30], gnd, W[44]);
T_NMOS NW7_3_44_( B[31], gnd, W[44]);
T_NMOS NW7_0_45_( B[28], gnd, W[45]);
T_NMOS NW7_2_45_( B[30], gnd, W[45]);
T_NMOS NW7_1_46_( B[29], gnd, W[46]);
T_NMOS NW7_2_46_( B[30], gnd, W[46]);
T_NMOS NW7_1_47_( B[29], gnd, W[47]);
T_NMOS NW7_3_47_( B[31], gnd, W[47]);
T_NMOS NW7_2_48_( B[30], gnd, W[48]);
T_NMOS NW7_3_48_( B[31], gnd, W[48]);
T_NMOS NW7_0_49_( B[28], gnd, W[49]);
T_NMOS NW7_1_49_( B[29], gnd, W[49]);
T_NMOS NW7_2_49_( B[30], gnd, W[49]);
T_NMOS NW7_3_49_( B[31], gnd, W[49]);
T_NMOS NW7_3_50_( B[31], gnd, W[50]);
T_NMOS NW7_0_51_( B[28], gnd, W[51]);
T_NMOS NW7_1_51_( B[29], gnd, W[51]);
T_NMOS NW7_1_52_( B[29], gnd, W[52]);
T_NMOS NW7_2_52_( B[30], gnd, W[52]);
T_NMOS NW7_3_52_( B[31], gnd, W[52]);
T_NMOS NW7_0_53_( B[28], gnd, W[53]);
T_NMOS NW7_1_53_( B[29], gnd, W[53]);
T_NMOS NW7_2_53_( B[30], gnd, W[53]);
T_NMOS NW7_3_53_( B[31], gnd, W[53]);
T_NMOS NW7_0_55_( B[28], gnd, W[55]);
T_NMOS NW7_1_55_( B[29], gnd, W[55]);
T_NMOS NW7_2_55_( B[30], gnd, W[55]);
T_NMOS NW7_1_56_( B[29], gnd, W[56]);
T_NMOS NW7_1_57_( B[29], gnd, W[57]);
T_NMOS NW7_3_57_( B[31], gnd, W[57]);
T_NMOS NW7_0_58_( B[28], gnd, W[58]);
T_NMOS NW7_1_58_( B[29], gnd, W[58]);
T_NMOS NW7_2_58_( B[30], gnd, W[58]);
T_NMOS NW7_0_59_( B[28], gnd, W[59]);
T_NMOS NW7_2_59_( B[30], gnd, W[59]);
T_NMOS NW7_0_60_( B[28], gnd, W[60]);
T_NMOS NW7_3_60_( B[31], gnd, W[60]);
T_NMOS NW7_1_61_( B[29], gnd, W[61]);
T_NMOS NW7_0_62_( B[28], gnd, W[62]);
T_NMOS NW7_1_62_( B[29], gnd, W[62]);
T_NMOS NW7_2_62_( B[30], gnd, W[62]);
T_NMOS NW7_3_62_( B[31], gnd, W[62]);
T_NMOS NW7_1_63_( B[29], gnd, W[63]);
endmodule


module ROMHCell8_001 (W, B);
output  [31:0] B;
input [63:0]  W;

T_NMOS NW1_0_0_( B[4], gnd, W[0]);
T_NMOS NW2_0_0_( B[8], gnd, W[0]);
T_NMOS NW3_0_0_( B[12], gnd, W[0]);
T_NMOS NW5_0_0_( B[20], gnd, W[0]);
T_NMOS NW6_0_0_( B[24], gnd, W[0]);
T_NMOS NW7_0_0_( B[28], gnd, W[0]);
endmodule


