# Fast-Fourier-Transform-using-Cooley-Tukey-algorithm
The most common fast Fourier transform (FFT) algorithm
Cooley–Tukey re-expresses the discrete Fourier transform (DFT) of an arbitrary composite size $N = N_1N_2$ in terms of smaller DFTs of sizes $N_1$ and $N_2$, recursively, in order to reduce the computation time to $O(N log N)$ for highly composite N (smooth numbers).

## The radix-2 DIT case
A radix-2 decimation-in-time (DIT) FFT is the simplest and most common form of the Cooley–Tukey algorithm, although highly optimized Cooley–Tukey implementations typically use other forms of the algorithm as described below. Radix-2 DIT divides a DFT of size N into two interleaved DFTs (hence the name "radix-2") of size $N/2$ with each recursive stage.

The discrete Fourier transform (DFT) is defined by the formula:

$$
X_k = \sum_{n=0}^{N-1} x_n e^{-\frac{2\pi i}{N} nk},
$$

where $k$ is an integer ranging from $0 to N-1$.

Radix-2 DIT first computes the DFTs of the even-indexed inputs $(x_{2m}=x_0, x_2, \ldots, x_{N-2})$ and of the odd-indexed inputs $(x_{2m+1}=x_1, x_3, \ldots, x_{N-1})$, and then combines those two results to produce the DFT of the whole sequence. This idea can then be performed recursively to reduce the overall runtime to $O(N log N)$. This simplified form assumes that N is a power of two; since the number of sample points $N$ can usually be chosen freely by the application, this is often not an important restriction.

The Radix-2 DIT algorithm rearranges the DFT of the function $x_n$ into two parts: a sum over the even-numbered indices $n={2m}$ and a sum over the odd-numbered indices $n={2m+1}$:

$$
  \begin{matrix} X_k & =
& \sum \limits_{m=0}^{N/2-1} x_{2m}e^{-\frac{2\pi i}{N} (2m)k}   +   \sum \limits_{m=0}^{N/2-1} x_{2m+1} e^{-\frac{2\pi i}{N} (2m+1)k}
  \end{matrix}
$$

One can factor a common multiplier $e^{-\frac{2\pi i}{N}k}$ out of the second sum, as shown in the equation below. It is then clear that the two sums are the DFT of the even-indexed part $x_{2m}$ and the DFT of odd-indexed part $x_{2m+1}$ of the function $x_n$. Denote the DFT of the Even-indexed inputs $x_{2m}$ by $E_k$ and the DFT of the Odd-indexed inputs $x_{2m + 1}$ by $O_k$ and we obtain:

$$
\begin{matrix} X_k= \underbrace{\sum \limits_{m=0}^{N/2-1} x_{2m}   e^{-\frac{2\pi i}{N/2} mk}}_{\mathrm{DFT\;of\;even-indexed\;part\;of\;} x_m} {} +  e^{-\frac{2\pi i}{N}k}
 \underbrace{\sum \limits_{m=0}^{N/2-1} x_{2m+1} e^{-\frac{2\pi i}{N/2} mk}}_{\mathrm{DFT\;of\;odd-indexed\;part\;of\;} x_m} =  E_k + e^{-\frac{2\pi i}{N}k} O_k.
\end{matrix}
$$

Thanks to the periodicity of the DFT, we know that

$$
E_{{k} + \frac{N}{2}} = E_k
$$

and

$$
O_{{k} + \frac{N}{2}} = O_k. 
$$

Therefore, we can rewrite the above equation as

$$
\begin{matrix} X_k & = & \left\{
\begin{matrix}
E_k + e^{-\frac{2\pi i}{N}k} O_k & \mbox{for } 0 \leq k < N/2 \\ \\
E_{k-N/2} + e^{-\frac{2\pi i}{N}k} O_{k-N/2} & \mbox{for } N/2 \leq k < N . \\
\end{matrix}
\right. \end{matrix}
$$

We also know that the twiddle factor $e^{-2\pi i k/ N}$ obeys the following relation:

$$
\begin{matrix} e^{\frac{-2\pi i}{N} (k + N/2)} & = & e^{\frac{-2\pi i k}{N} - {\pi i}} \\
& = & e^{-\pi i} e^{\frac{-2\pi i k}{N}} \\
& = & -e^{\frac{-2\pi i k}{N}}
\end{matrix}
$$

This allows us to cut the number of "twiddle factor" calculations in half also. For  $0 \leq k < \frac{N}{2}$, we have

$$
\begin{matrix}
X_k & =
& E_k + e^{-\frac{2\pi i}{N}k} O_k \\
X_{k+\frac{N}{2}} & =
& E_k - e^{-\frac{2\pi i}{N}k} O_k
\end{matrix}
$$

This result, expressing the DFT of length $N$ recursively in terms of two DFTs of size $N/2$, is the core of the radix-2 DIT fast Fourier transform. The algorithm gains its speed by re-using the results of intermediate computations to compute multiple DFT outputs. Note that final outputs are obtained by a +/− combination of $E_k$ and $O_k \exp(-2\pi i k/N)$, which is simply a size-2 DFT (sometimes called a butterfly in this context); when this is generalized to larger radices below, the size-2 DFT is replaced by a larger DFT (which itself can be evaluated with an FFT).

This process is an example of the general technique of divide and conquer algorithms; in many traditional implementations, however, the explicit recursion is avoided, and instead one traverses the computational tree in breadth-first fashion.

---
## AIE FFT Intrinsic

### Overview

These are the intrinsics functions used for implementing FFT functionality.

For intrinsics used for addressing related to FFT please see FFT addressing.
The FFT algorithm works by executing these functions a number of times in different stages.

The number of stages is the log of the number of points in the FFT with the radix as the base of the log. For instance for a 256 point radix 2 FFT the process is split into 8 stages. The first 6 stages are the same and consist of calling the butterfly function on every input value that is supplied to it, these input values depend on the radix. In this instance (radix 2) means that every second block is processed. The input pointer is determined by by an incrementation function fft_data_incr. The twiddle values are determined by the use of two functions fft_permute_incr which determines which values within the register to use and fft_twiddle_incr which increments the pointer to the twiddle factors, thereby providing a fresh set of twiddle values.

The output of each stage becomes the input of the next stage.

The last two stages differ from the initial 6 stages in the way that the inputs are twiddles are mapped from the registers and how often the twiddles are updated from the registers.

In the case of radix 2, 256 point FFT with 32bit data, a stage will consist of 32 butterfly calls, each consuming 8 samples, 64 store operations and 64 AIE cycles total.

1. FFT scalar functions
```
unsigned 	fft_zoffs (umod_t cntwrap, int step, bool wide_twiddle, bool wide_data)
 	Change twiddle factor selectors. More...
 
umod_t 	fft_mod_delay (umod_t cntwrap)
 	Delay the count/wrap parameter. More...

```
 
2. FFT butterfly intrinsics

The butterfly function is the central calculation of the FFT algorithm. It takes two inputs that are to be acted upon as well as a set of twiddle values and performs the decimation-in-time (dit) FFT operation upon them. The offset values (aoffsets,boffsets,zoffsets) determine which inputs will interact with which twiddle values.

The butterfly function performs the following pseudocode:
```
o = a + b*func(z)
p = a - b*func(z)
return p::o
```
Alternatively, the following pseudo-code can be performed. The intrinsic will be prefixed with half_ in this case:
```
o =     b*func(z)
p = a + b*func(z)
return p::o
```
Where func(z) can be:
```
func(z) = z: the normal mode
func(z) = conj(z): conjugate twiddles for inverse fft applications
func(z) = -j*z: multiply twiddles with minus imaginary number. Used in radix-4 kernels.
func(z) = -j*conj(z): combination of the two above.
```

3. Function Documentation

```
v8cacc48 butterfly_dit	(	v8cint32 	x,
v8cint32 	y,
unsigned int 	aoffsets,
unsigned int 	boffsets,
v8cint16 	z,
unsigned int 	zstart,
unsigned int 	zoffsets,
int 	shft 
)	

```
The butterfly function is the central calculation of the FFT algorithm. It takes two inputs that are to be acted upon as well as a set of twiddle values and performs the decimation-in-time (dit) FFT operation upon them. The offset values (aoffsets,boffsets,zoffsets) determine which inputs will interact with which twiddle values. This butterfly function performs the following pseudocode:
```
o0  =  ups(x::y(aoffsets0 ),shift) +  x::y(boffsets0 )*( z *( zoffsets0 ));  
o1  =  ups(x::y(aoffsets1 ),shift) +  x::y(boffsets1 )*( z *( zoffsets1 ));  
o2  =  ups(x::y(aoffsets2 ),shift) +  x::y(boffsets2 )*( z *( zoffsets2 ));  
o3  =  ups(x::y(aoffsets3 ),shift) +  x::y(boffsets3 )*( z *( zoffsets3 ));  

p0  =  ups(x::y(aoffsets0 ),shift) -  x::y(boffsets0 )*( z *( zoffsets0 ));  
p1  =  ups(x::y(aoffsets1 ),shift) -  x::y(boffsets1 )*( z *( zoffsets1 ));  
p2  =  ups(x::y(aoffsets2 ),shift) -  x::y(boffsets2 )*( z *( zoffsets2 ));  
p3  =  ups(x::y(aoffsets3 ),shift) -  x::y(boffsets3 )*( z *( zoffsets3 ));  
```
For more information, see FFT intrinsics

**Returns**
Output accumulator register.
**Parameters**
```
[in]	x	First input buffer for FFT values.
[in]	y	Second input buffer for FFT values.
[in]	boffsets	Selects the values for b from x::y.
[in]	z	Buffer of twiddle values.
[in]	zstart	Fixed offset to the twiddle value selectors. This must be a compile time constant.
[in]	zoffsets	Selects the twiddle values from z.
[in]	zconj	(Optional) twiddle values are conjugated befor multiplication.
[in]	aoffsets	Selects the values for a from x::y.
[in]	shft	Upshift value for the values from a before accumulation.
```

```C++
// -------------------------------------------------------------
// Radix 2 FFT 32-bit Input, Interval=2, 16-bit Output
// -------------------------------------------------------------
inline __attribute__((always_inline)) void stage1_radix2_down_dit ( cint32_t * restrict x, 
                                     cint16_t * restrict tw, 
                                     unsigned int n, unsigned int shift, 
                                     cint16_t * restrict y, bool isIFFT)
{
  set_rdx(2);

  v4cint16 * restrict po1 = (v4cint16 * restrict) y;
  v4cint16 * restrict po2 = (v4cint16 * restrict) (y + n/2);  
  v4cint32 * restrict pi1 = (v4cint32 * restrict) x;  
  v4cint32 * restrict pi2 = (v4cint32 * restrict) (x+4);  
  v4cint32 * restrict px1 = (v4cint32 * restrict) (x+4);  
  v8cint16 * restrict ptw = (v8cint16 * restrict) tw;
     
  int zoffs = 0x1100;
  umod_t cnt = 0;

  for (int j = 0; j < n/8; ++j)
    chess_prepare_for_pipelining
    chess_loop_range(4,)
  {
    v8cint32 chess_storage(xa) xbuf = undef_v8cint32();
    xbuf = upd_w(xbuf,0,pi1[0]);
    xbuf = upd_w(xbuf,1,pi2[0]);
    
    v8cacc48 o = butterfly_dit(xbuf,undef_v8cint32(),0x5410,0x7632,ptw[0],0,zoffs,isIFFT,15);
    *po1++ = srs(ext_lo(o),shift);
    *po2++ = srs(ext_hi(o),shift); 

    pi1   = fft_data_incr(pi1,1,px1,cnt);    
    pi2  += 2;
    ptw   = fft_twiddle_incr(ptw,cnt,2);    
    zoffs = fft_zoffs(cnt,2,1,0);    
  }
}
```
---
## AIE FFT API

Overview
The AIE API offers the aie::fft_dit class template that provides the building blocks to implement all the stages of the FFT decimation-in-time computation. This class template is parametrized with the data type, the radix to be used and the vectorization of the FFT stage to be computed. The resulting class defines a stage iterator that contains the state of the computation (pointers to the input and twiddle arrays), and a function that performs the decimation in time.

By default the input and output type are the same, but you can optionally specify a second type for a different output type.

The following snippet shows the sample implementation of a radix-2 FFT stage for any vectorization value.

```C++
template <unsigned Vectorization>
void radix2_dit(const cint32 * __restrict x,
                const cint16 * __restrict tw,
                unsigned n,  unsigned shift_tw, unsigned shift, bool inv,
                cint32 * __restrict y)
{
    using FFT = aie::fft_dit<Vectorization, 2, cint32>; // radix = 2, input_type = cint32, output_type = cint32 (output defaults to input)
 
    FFT fft;
 
    auto it_stage  = fft.begin_stage(x, tw);
    auto it_out0 = aie::begin_vector<FFT::out_vector_size>(y);
    auto it_out1 = aie::begin_vector<FFT::out_vector_size>(y + n / 2);
 
    for (int j = 0; j < n / (2 * FFT::out_vector_size); ++j)
        chess_prepare_for_pipelining
        chess_loop_range(1,)
    {
        const auto out = fft.dit(*it_stage++, shift_tw, shift, inv);
        *it_out0++ = out[0];
        *it_out1++ = out[1];
    }
}
```
### Typedefs
template<unsigned Vectorization, unsigned Radix, typename T1 , typename T2 = T1>
using 	aie::fft_dit = detail::fft_dit< Vectorization, detail::fft_get_stage< Vectorization, Radix, T1, T2 >(), Radix, T1, T2 >
 	More...
 
**Supported Fast Fourier Transform Modes**

- Supported FFT/IFFT Modes

|Input Type	|Output Type|Radix
|---------|---------|----------|
|c16b	|c16b	|2
|c16b	|c32b	|2 3 4 5
|c32b	|c16b	|2 4
|c32b	|c32b	|2 3 4 5
|cfloat	|cfloat	|2


For a given radix R with n number of points, there will be R number of outputs spaced by n/R. The above example shows 2 outputs for a radix 2, for radix 4 we would have:

```C++
template <unsigned Vectorization>
void radix4_dit(const cint32 * __restrict x,
                const cint16 * __restrict tw1,
                const cint16 * __restrict tw2,
                unsigned n, unsigned shift_tw, unsigned shift, bool inv,
                cint32 * __restrict y)
{
    using FFT = aie::fft_dit<Vectorization, 4, cint32>;
 
    FFT fft;
 
    auto it_stage  = fft.begin_stage(x, tw1, tw2);
 
    auto it_out0 = aie::begin_restrict_vector<FFT::out_vector_size>(y);
    auto it_out1 = aie::begin_restrict_vector<FFT::out_vector_size>(y +   n / 4);
    auto it_out2 = aie::begin_restrict_vector<FFT::out_vector_size>(y + 2*n / 4);
    auto it_out3 = aie::begin_restrict_vector<FFT::out_vector_size>(y + 3*n / 4);
 
    for (int j = 0; j < n / (4 * FFT::out_vector_size); ++j)
        chess_prepare_for_pipelining
        chess_loop_range(1,)
    {
        const auto out = fft.dit(*it_stage++, shift_tw, shift, inv);
        *it_out0++ = out[0];
        *it_out1++ = out[1];
        *it_out2++ = out[2];
        *it_out3++ = out[3];
    }
}
```

Typedef Documentation

◆ fft_dit

```
template<unsigned Vectorization, unsigned Radix, typename T1 , typename T2 = T1>

using aie::fft_dit = typedef detail::fft_dit<Vectorization, detail::fft_get_stage<Vectorization, Radix, T1, T2>(), Radix, T1, T2>

```
Type that encapsulates the functionality for decimation-in-time FFTs.

**Template Parameters**

|Vectorization	|Vectorization of the FFT stage
|--------------|---------|
|Radix	|Number which selects the FFT radix.
|T1	|Type of the input elements.
|T2	|Type of the output elements, defaults to input type.

