# © Copyright 2021 Xilinx, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
PFM = xilinx_vck5000_gen4x8_xdma_2_202210_1

AIE_CC = aiecompiler
AIE_SIM = aiesimulator
X86_SIM = x86simulator

AIE_SRC_DIR = ..
AIE_GRAPH_FILES = ../src/project.cpp 
AIE_OUT_DIR = ./Work
AIE_DATA_DIR = ./data
AIE_HW_DIR = ./hw
AIE_TR_DATA_DIR = ./Traces/.tracecompass/.tracing
AIE_TRACE_DIR = ./Traces
DST_LOG_FILE_PATH = ./build.log

RM = rm -f
RMDIR = rm -rf
