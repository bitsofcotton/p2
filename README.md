# p2
Generic predictor corrector with random. This suppose the random stream we make is better than original random source and the one we made is a little predictable with some prediction method. If so, this slices a little amount of random entropy. This is because short length of original prediction method divides 3 parts, bet ok, bet ng, or no bet. So with blending no periodical datas, it flatten 33%, 33%, 33% of them idealy, but with a little predictable part, it shifts original to a little predictable parts. But in fact, this only changes sliding window distribution.

# How to use
Change p2.py getrand functions and pp subprocess initializer.

# General Tips
If there exists correctly predict next one step with \[...,x_n,f(...,x_n),f(f(...,x_n)),..\], f should be linear because \[...,a\*x_n+b,a\*f(...,x_n)+b,a\*f(f(...,x_n))+b,...\]. This concludes the structure of f is f(x):=(\<a,x\>). So p0 and p1 is reasonable in this meaning. But, if there exists predictor function, there is able to be non-predictable function on the meaning to them. (because there exists the stream that flip the predicted ones.)
And, one of linear-space or exp-space or log-space, tetration-space or inverse-tetration-space is unpredictable in that meaning, others can be exists by some numerical tests.

# Important General Tips
With bitsofcotton/randtools, any fixed operations on N is described as fixed A_k in F_p_k^{n\*n} chain, large enough p_k in P, and p_k is increasingly function, with the form x_k in each, x_{k+1} := A_k\* x_k. So the result is y=...\*((A_k\*...) mod p_k).  
Alternate to this, with good a_k=a_k-1\*...\*a_0 chain and large enough each a_k (this change log space scales), so with 2^x := \[x_0, ..., x_n, x_0 and x_1, ..., x_0 and x_1 and x_2, ..., x_0 and ... x_n\] vector (each x_k is in {0, 1}), <a, 2^x>^k recursive is also in them.  
Or we can only say 'a and b' := a \* b, 'a xor b' := a + b, and so on, recursive, they also in A\* 2^x.  
convert A into R^{n\*n}, IDFT \* A'^k \* DFT \* 2^x = IDFT\* (U L U^t)^k\[1, x', 1, x'\] = IDFT \* U L^k U^t \[1, x', 1, x'\]. So with DFT meaning, freq:= DFT \* x'', x_k = IDFT \* U \* L^large num\* U^t \* freq, abs value on freq_k needs to be near the fixed point from first. this concludes: 2^x -> IDFT * \[..., a_k \* cis(x_k\*(2^x)' + x'\_k), ...\] = B\*\[..., cis(x_k\*(2^x)'\_k + x'\_k), ...\] mod a_n then mod 2.  
If we predict with p0, what we treat L2(R) and m + 1 bits steps is L matrix multiply on the space : the rotation on the frequency space with bit table opreation, (and with fixed startpoint and no change algorithm, this is valid), and if we predict with original functions, it's on same prediction because the taylor series exists.  
If we predict with p1 it depends: A \* x_nows 's a.row(k) is stable for any k on each steps, and if we average the status length, this is valid for them.

# General Tips:
If we convert original R^n series {f(x)} to {exp(exists a \* f(x))} in R^+n, what the expansion of below is described as: {exp(a\* sum b_k\*cos(c_k\*x'+d_k))} (Re cis(x) == cos(x)), and this is also {exp(a\*(sum b_k'\*cos(c_k\*x')) + d').
