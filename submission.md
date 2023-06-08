# Submission
You can optionally submit your design for the preliminary submissions (see [schedule]({% link _pages/schedule.md %})). This allows you to check that your solutions is working on our evaluation platform. 

## Preliminary Submission 

1. Prepare the files according to the submission file tree.
1. Add appropriate code comments to increase code readability.
1. Do not hardcode any file paths. 

1. Create a GitHub account and create a private repository to upload the code you need to submit.

2. Grant access to **CCC_CCF@outlook.com** to access the private repository.

3. Use the VCK5000 platform on the HACC NUS cluster for code testing and execution.

4. Refer to the provided repository at https://github.com/ccfsys-ccc/ccc2023 for submission format.

## Final Submission

For the final submission, follow the instructions above. In addition:

1. Submit all source files for your design, in a zip archive.
1. Set the private repository as public
    1. Your design must be available, open-source, and in working condition in order to be considered for an award. You are permitted to use publicly available closed source library, tools and IP; however, all of your work (any modifications and configurations to commercial, closed-source tools), must be accessible.

## Submission file tree

Every problem of this competition has two requirement level: basic and advanced. 
In the basic flow, a successful AIE emulation run is the only requirement. In the advanced flow, the connection with PL and host must be considered to ensure a successful hardware run on VCK5000. Following are critical components in making a kernel work on VCK5000 platform using Vitis™ Tool 2022.2:

### Basic Flow

- Development Steps
    - Prepare the AIE Kernels
    - Data Flow Graph construction
    - Setting up platform ports
    - Makefile to compile the kernel for aie simulation

The Versal® ACAP AI Engine SystemC simulator (aiesimulator) includes the modeling of the global memory (DDR memory) and the network on chip (NoC) in addition to the AI Engine array. When the application is compiled using the SystemC simulation target.

- Submission File Tree
```
├── notebook     // application
│   └── fir.ipynb
├── data
│   └── input.txt
├── Makefile
└── src
    ├── aie_kernels
    │   └── fir_asym_8t_16int_vectorized.cpp
    ├── aie_kernels.h
    ├── graph.cpp
    └── graph.h
```

### Advanced Flow

- Development Steps

    - Prepare the AIE Kernels
    - Data Flow Graph construction
    - Setting up platform ports
    - Makefile to compile the kernel for aie simulation
    - Prepare the PL Kernels
    - Host code integration
    - Makefile to compile the system for hw-emulation / hw runs

- Submission File Tree

```
├── notebook     // application
│   └── fir.ipynb
├── execution 
│   ├── vadd.xclbin
│   ├── input_files
│   └── host.exe
├── aie
│   ├── data
│   │   ├── inputa_float.txt
│   │   ├── ref_outputc_float.txt
│   ├── Makefile
│   └── src
│       ├── aie_kernels
│       ├── aie_kernels.h
│       ├── graph.cpp
│       ├── graph.h
│       └── system_settings.h
├── host
│   ├── host.cpp
│   ├── Makefile
│   └── matmult.py
├── hw_link
│   └── config.cfg
├── Makefile
└── pl
    ├── Makefile
    └── src
        ├── config.hpp
        ├── mm2s.cpp
        └── s2mm.cpp
```


