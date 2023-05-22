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
#include "kernels.h"

int16_t taps[FIR_TAPS] = { 18, 44, 54, 29, -3, -16, -7, 0};

void fir_asym_8t_16int_scalar(input_window_int16 * in, output_window_int16 * out)
{
	int16 data[FIR_TAPS];
	int16 acc;
	
	int i, j;
	
	//Initialize the data array
	for( i = 0; i<FIR_TAPS; i++)
	{
		data[i] = 0;
	}
	
	//Main loop
	for( i = 0; i<NUM_SAMPLES; i++)
	{
		acc = 0;
		
		data[0] = window_readincr(in);
		
		//Multiply the samples with the coefficient
		for( j = 0; j<FIR_TAPS; j++)
		{
			acc += data[j] * taps[j];
		}
		
		window_writeincr(out, acc);
		
		//Shift the element of the data array
		for( j = FIR_TAPS-1; j>=0; j--)
		{
			data[j] = data[j-1];
		}		
	}
	
}
	