#!/bin/bash

# Copyright (C) 2023 Xilinx, Inc
#
# SPDX-License-Identifier: MIT

cat > /opt/xilinx/platforms/xilinx_vck5000_gen4x8_xdma_2_202210_1/sw/sw.spfm <<EOT
<?xml version="1.0" encoding="UTF-8"?>
<sdx:platform xmlns:sdx="http://www.xilinx.com/sdx" sdx:vendor="xilinx" sdx:library="vck5000" sdx:name="gen4x8_xdma_2" sdx:version="202210.1" sdx:schemaVersion="1.0">
   <sdx:description>This platform targets the Versal VCK5000 Alveo Developer Kit. This high-performance acceleration platform features four channels of DDR4-3200 SDRAM, and Xilinx XDMA for PCI Express with PCIe Gen4x8 connectivity.</sdx:description>
   <sdx:systemConfigurations sdx:defaultConfiguration="config0_0">
      <sdx:configuration sdx:name="config0_0" sdx:displayName="Linux" sdx:defaultProcessorGroup="x86_0" sdx:runtimes="ocl">
         <sdx:description>config0_0 Linux OS on x86_0</sdx:description>
         <sdx:processorGroup sdx:name="x86_0" sdx:displayName="x86_0" sdx:cpuType="x86" sdx:cpuInstance="x86_0">
            <sdx:os sdx:name="linux" sdx:displayName="Linux OS" />
         </sdx:processorGroup>
         <sdx:processorGroup sdx:name="aie_domain" sdx:displayName="aie_domain" sdx:cpuType="ai_engine" sdx:cpuInstance="ai_engine">
            <sdx:os sdx:name="aie_runtime" sdx:displayName="aie_runtime" />
         </sdx:processorGroup>
      </sdx:configuration>
   </sdx:systemConfigurations>
</sdx:platform>
EOT