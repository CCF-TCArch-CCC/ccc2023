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
#include "project.h"

using namespace adf;

fir_asym_8t_16int_graph mygraph;
simulation::platform<1,1> platform("../data/input.txt", "data/output_vectorized.txt");
connect<> net0(platform.src[0], mygraph.in);
connect<> net1(mygraph.out, platform.sink[0]);

int main(void) {
  mygraph.init();
  mygraph.run(1);
  mygraph.end();
  return 0;
}
