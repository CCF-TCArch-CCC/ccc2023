// Copyright (C) 2023 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#pragma once

#include <adf.h>
#include "fir_sr_sym_graph.hpp"

#define FIR129_LENGTH 129
#define FIR129_SHIFT 15
#define FIR129_ROUND_MODE 0
#define FIR129_INPUT_SAMPLES 2048

class FIR_129_sym : public graph {
    private:
        // FIR coefficients
        std::vector<int16> bp_taps = std::vector<int16>{
            99,  -97,  -94, -149, -201, -164,   -27,   132,   216,   197,  117,   38,   -3,   -1,  37,  84, 94,
            26, -115, -261, -321, -254,  -98,    53,   118,    80,   -11,  -66,  -16,  145,  348, 475, 431, 208,
            -94, -325, -373, -246,  -66,    8,  -115,  -387,  -635,  -660, -365,  169,  705,  979, 865, 462,  56,
            -53,  241,  749, 1051,  729, -360, -1926, -3307, -3758, -2831, -651, 2070, 4307, 5169};

        xf::dsp::aie::fir::sr_sym::fir_sr_sym_graph<cint16, int16, FIR129_LENGTH, FIR129_SHIFT, FIR129_ROUND_MODE, FIR129_INPUT_SAMPLES> firGraph;

    public:
        adf::port<input> in;
        adf::port<output> out;
        FIR_129_sym() : firGraph(bp_taps) {
            // Margin gets automatically added within the FIR graph class.
            // Margin equals to FIR length rounded up to nearest multiple of 32 Bytes.
            adf::connect<>(in, firGraph.in);
            adf::connect<>(firGraph.out, out);
        };
};