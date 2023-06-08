# FAQ

1. The xilinx_vck5000_gen4x8_xdma_2_202210_1 platform does not contain the aie_domain, this prevent from using the AIE from the Vitis IDE

It is a bug which has been fixed on the Vitis 2022.2 and VCK5000 QDMA platform. Please download the right platform and tools.

2. So many examples and applications are using the VCK190 platform, are they useful to learn on VCK5000.

The AIE domain has no different between these two platform which means the AIE kernels can be implemented on the two platform without any modification.

3. If you got the following errors, what's the root cause?

```
wenchen@hacc-vck5000-1:~/hacc_demo/ccc2023_submissiom/vadd$ ./template.exe template.xclbin
Open the device
Load the xclbin template.xclbin
./template.exe: symbol lookup error: ./template.exe: undefined symbol: _ZN3xrt6device11load_xclbinERKSs

```
This error is coming because of my server OS is different than the OS where you compiled the host executable. 
Please rebuild the host executable on the same OS. Note that the XCLBIN can be reused.
