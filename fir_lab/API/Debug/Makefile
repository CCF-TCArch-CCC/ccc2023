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

include ../../common.mk

# AIE compiler settings
AIE_FLAGS = -v -dataflow -include="$(XILINX_VITIS)/aietools/include" \
		-include="../src" -include="../data" \
		-target=hw -xlopt=0 \
		-platform=$(PLATFORM_REPO_PATHS)/$(PFM)/$(PFM).xpfm \
		-workdir=$(AIE_OUT_DIR)
#
# primary build targets
#

all: build sim

build:
	-$(AIE_CC) $(AIE_FLAGS) $(AIE_GRAPH_FILES) 2>&1 | tee $(DST_LOG_FILE_PATH)
	
print_errors:
	if [ $(shell grep -c Error $(DST_LOG_FILE_PATH)) -gt 0 ] || [ $(shell grep -c ERROR $(DST_LOG_FILE_PATH)) -gt 0 ]; \
		then echo "Build Failed with following errors:";\
		grep Error $(DST_LOG_FILE_PATH); grep ERROR $(DST_LOG_FILE_PATH); grep error $(DST_LOG_FILE_PATH);\
	fi;
	
sim:
	-$(AIE_SIM) --pkg-dir=./$(AIE_OUT_DIR) --i=.. --profile

clean:
	$(RMDIR) $(AIE_OUT_DIR) $(AIE_DATA_DIR) $(AIE_TR_DATA_DIR) $(AIE_TRACE_DIR) ./aiesim* ./ess* ./profile* ../data/out* ./xnwOut ./.Xil
	find ./ -type f | grep -v Makefile | xargs rm -Rf

.PHONY: all clean 
