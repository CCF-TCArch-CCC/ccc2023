# Local Environment Setup

## 2022.2 QDMA Platform
1.	Click on the following link and request access to the VCK5000 Versal Development Card for AI Engine Secure Site. This will take one or two days.
https://www.xilinx.com/products/boards-and-kits/vck5000.html
 
2.	Download the Vitis 2022.2 version, XRT, Deployment Target Platform and Development Platform according to your OS vision
https://www.xilinx.com/member/vck5000-aie.html#vitis-flow

![setup_vck5000](/image/VCK5000_qdma.png)

3. Please install the **VCK5000 Gen4x8 qdma platform** platform by following the steps here: https://docs.xilinx.com/r/en-US/ug1531-vck5000-install/XRT-and-Deployment-Platform-Installation-Procedures-on-RedHat-and-CentOS

4. Generating Vitis AI Engine Tools License
[Log in](https://www.xilinx.com/member/forms/license-form.html) with your Xilinx account to activate the Vitis AI Engine Tools license

Load the license in your local machine referring to this [AR](https://support.xilinx.com/s/article/42513?language=en_US)

5.	Once you have got the access to VCK5000 tutorial, please refer to the following website to download the Mixed kernel example lab files the tutorials and run the example.
https://www.xilinx.com/member/vck5000-aie.html#tutorials

## 2022.2 XDMA Platform
 
This Competition uses the QDMA platform. But if you want to run some labs using XDMA platform. please run the following patch to enable AIE domain displayed on the platform page.

1. Patch the xilinx_vck5000_gen4x8_xdma_2_202210_1 platform

To be able to use the AI Engine on the VCK5000 from the Vitis IDE, please apply this change

```sh
sudo ./env/patch_vck5000_gen4x8_xdma/aie_domain_patch.sh
```

# HACC Getting Started With VCK5000

## Login HACC@NUS

Please setup 2FA following the instructions in the email of registration. After that, you can use SSH with the given username and 2FA key to login HACC@NUS.

```
ssh username@xacchead.d2.comp.nus.edu.sg
```

you will login to the node __hacchead__

After getting into __hacchead__, please clone this repository so that you can use the script tools provided by HACC@NUS.

```
git clone https://github.com/XACCNUS/hacc_demo.git
```

## Demo: VCK5000 Exploration

Please refer to [this tutorial](https://github.com/Xtra-Computing/hacc_demo/blob/main/doc/4-VCK5000.md) to make a hardware run on VCK5000。
