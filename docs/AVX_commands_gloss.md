
### Arithmetic
#### Packed Integer
```text
vpadd[b|w|d|q]: signed and unsigned packed addition  
vpadds[b|w]:    signed addition with saturation  
vpaddus[b|w]:   unsigned addition with saturation  

vpsub[b|w|d|q]: signed/unsigned packed subtraction  
vpsubs[b|w]:    signed subtraction with saturation  
vpsubus[b|w]:   unsigned subtraction with saturation  

vpmuldq: signed dword multiply, writes full product qwords to destination

vpmulh[w|uw]:  signed|unsigned word multiply, writes high product to destination
vpmull[w|d|q]: signed word/double/quad multiply, write low product to destination

vpmin[s|u][b|w|d|q]:  perform packed signed|unsigned integer minimum compares
vpmax[s|u][b|w|d|q]:  perform packed signed|unsigned integer maximum compares

```

#### Packed Float
```text
vaddp[s|d]:  add,       a + b,    SP|DP
vsubp[s|d]:  subtract,  a - b,    SP|DP
vmulp[s|d]:  multiply,  a * b,    SP|DP
vdivp[s|d]:  divide,    a / b,    SP|DP
vmaxp[s|d]:  max,       max(a,b), SF|DP
vminp[s|d]:  min,       min(a,b), SF|DP
vsqrtp[s|d]: sqrt,      sqrt(a),  SF|DP
```
#### Scalar
Basic double-precision and single-precision scalar floating-point arithmetic:
```text
vadds[d|s]
vsubs[d|s]
vmuls[d|s]
vdivs[d|s]
vsqrts[d|s]
```

### Bitwise compares
#### Packed
```text
vandps: packed SPFP & (and)

vpand, vpor, vpxor: uses all bits in the source operands
vpand[d|q]: bitwise & (and) of each dword|qword in the source operands
```

### Broadcast
    vbroadcasts[s|d]: broadcast a scalar SP|DP FP value to multiple SP|DP values in destination

### Clearing bits
```text
vzeroupper: Clears all but the lowest octword of YMM0–15/ZMM0–15 registers. XMM registers unaffected.
vzeroall:   Clears YMM0–15/ZMM0–15 registers.
```
### Compare

#### Scalar
The UCOMISS instruction differs from the COMISS instruction in that it signals a SIMD floating-point invalid operation exception (#I) only if a source operand is an SNaN. The COMISS instruction signals an invalid operation exception when a source operand is either a QNaN or SNaN.
```text
vcomis[d|s]:  ordered compare two scalar fp values, set RFLAGS
vucomis[d|s]: unordered compare two scalar fp values, set RFLAGS

vcmps[d|s]: compare two scalar fp values using a compare predicate. Sets destination to all 0|1 for false|true
```
#### Packed
```text
vcmpp[d|s]: compare two packed FP values using a compare predicate. Sets destination to all 0|1 for false|true
```
### Convert

#### Scalar
```text
vcvts[d|s]2si: convert fp value to signed integer value
vcvtsi2s[d|s]: convert signed integer value to fp value
vcvtsd2ss:     convert double fp value to single-precision fp value
vcvtss2sd:     convert single-precision fp to double fp
```
### Extract
>vpextr[b|w|d|q]: extract an element value by index from a packed integer

### Move

#### Packed
```text
vmovap[s|d]: move aligned   SP|DP floating-point values
vmovup[s|d]: move unaligned SP|DP floating-point values

vmovdqa: must be properly aligned to 16,32, or 64 based on register
vmovdqu: unaligned packed moves
```
#### Scalar
>vmovs[d|s|h]: copy a scalar floating-point value

### MXCSR
```text
vldmxcsr: loads a value into the MXCSR register
vstmxcsr: saves the current contents of the MXCSR register.
```
### Shifts
```text
vpsll[w|d|q]: packed shift left logical
vpsrl[w|d|q]: packed shift right logical
vpsra[w|d|q]: packed shift fight arithmetic
vps[l|r]dq:   packed shift left|right logical qwords
```

### Unpack

These instructions unpack and interleave the contents of their two source operands.
They are frequently used to size-promote packed integer operands.
```text
vpunpckl[bw|dw|dq]
vpunpckh[bw|dw|dq]
```
