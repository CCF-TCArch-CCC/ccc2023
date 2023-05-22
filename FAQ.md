# FAQ

1. The xilinx_vck5000_gen4x8_xdma_2_202210_1 platform does not contain the aie_domain, this prevent from using the AIE from the Vitis IDE

It is a bug which has been fixed on the Vitis 2022.2 and VCK5000 QDMA platform. Please download the right platform and tools.

2. So many examples and applications are using the VCK190 platform, are they useful to learn on VCK5000.

The AIE domain has no different between these two platform which means the AIE kernels can be implemented on the two platform without any modification.


3. What's meaning of Full permute (1024x512 shuffle) unit with 32-bit granularity?

A full permute unit with 1024x512 shuffle and 32-bit granularity can be used for data shuffling and reordering operations within a computing system. In this case, the unit is designed to handle a 1024x512 data matrix, where each element is 32 bits in size. This can be useful in various applications, including parallel processing, data transformation, and digital signal processing.

Here is a high-level overview of the full permute unit's functionality:

- Input: The input is a 1024x512 data matrix, where each element is 32 bits in size.
- Data Shuffling: The full permute unit reorders the data elements in the input matrix according to a predefined permutation pattern. This pattern can be determined based on the specific application or algorithm's requirements.
- Output: The output is a new 1024x512 matrix, where the elements have been rearranged based on the permutation pattern.

