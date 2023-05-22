// © Copyright 2021 Xilinx, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <adf.h>
#include "aie_api/aie.hpp"
#include "aie_api/aie_adf.hpp"
#include "kernels.h"

static constexpr int16_t taps[FIR_TAPS] = { 0, -7, -16, -3, 29, 54, 44, 18};

void fir_asym_8t_16int_vectorized(input_window_int16 * in, output_window_int16 * out)
{
	aie::vector<int16, 16> data;
	const aie::vector<int16, 8> coeff = aie::load_v<8>(taps);
	aie::accum<acc48, AIE_MUL_LANES> acc0;
	
    constexpr unsigned CoeffStep   	= 1;
    constexpr unsigned DataStepXY   = 1;
    constexpr unsigned CoeffStart 	= 0;
	
	
	using mul_ops = aie::sliding_mul_xy_ops<AIE_MUL_LANES, FIR_TAPS, CoeffStep,DataStepXY, FIR_T_COEFF , FIR_T_DATA>;
	
	data = aie::zeros<int16, 16>();
	
	//Main loop
	for(int i = 0; i<LOOP_CYCLES; i++)
	{
		// Read 8 samples and insert then in the second part of the data vector
		data.insert(1, window_readincr_v<8>(in));		// 0...0 | d0..d7 
		//Run multiply operation
		acc0 = mul_ops::mul(coeff,CoeffStart,data,1) ;
		//Output 8 samples
		window_writeincr(out, acc0.to_vector<int16>()); 

		// Read the next 8 samples and insert them in the first part of the data vector
		data.insert(0, window_readincr_v<8>(in));		// d8...d15 | d0..d7
		//Run multiply operation
		acc0 = mul_ops::mul(coeff,CoeffStart,data,9) ;
		//Output the next 8 samples
		window_writeincr(out, acc0.to_vector<int16>());
	}
	
}