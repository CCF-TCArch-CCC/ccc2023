
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


using namespace adf;

class fir_asym_8t_16int_graph : public adf::graph {
private:
  kernel fir_asym_8t_vect_k_1;
public:
  input_port in;
  output_port out;
  
  fir_asym_8t_16int_graph(){

    fir_asym_8t_vect_k_1 = kernel::create(fir_asym_8t_16int_vectorized);
	
	connect< window<NUM_SAMPLES*2> > net0 (in, fir_asym_8t_vect_k_1.in[0]);
    connect< window<NUM_SAMPLES*2> > net1 (fir_asym_8t_vect_k_1.out[0], out);

    source(fir_asym_8t_vect_k_1) = "kernels/fir_asym_8t_16int_vectorized.cpp";

    runtime<ratio>(fir_asym_8t_vect_k_1) = 0.99;

  }
};
