# p2
Generic predictor corrector with random. This suppose the random stream we make is better than original random source and the one we made is a little predictable with some prediction method. If so, this slices a little amount of random entropy. This is because short length of original prediction method divides 3 parts, bet ok, bet ng, or no bet. So with blending no periodical datas, it flatten 33%, 33%, 33% of them idealy, but with a little predictable part, it shifts original to a little predictable parts. But in fact, this only changes sliding window distribution.

# How to use
Change p2.py getrand functions and pp subprocess initializer.

# General Tips
If there exists correctly predict next one step with \[...,x_n,f(...,x_n),f(f(...,x_n)),..\], f should be linear because \[...,a\*x_n+b,a\*f(...,x_n)+b,a\*f(f(...,x_n))+b,...\]. This concludes the structure of f is f(x):=(\<a,x\>). So p0 and p1 is reasonable in this meaning. But, if there exists predictor function, there is able to be non-predictable function on the meaning to them. (because there exists the stream that flip the predicted ones.)
And, one of linear-space or exp-space or log-space, tetration-space or inverse-tetration-space is unpredictable in that meaning, others can be exists by some numerical tests.

# Important General Tips
With bitsofcotton/randtools, any fixed operations on N is described as fixed A_k in F_p_k^{n\*n} chain, large enough p in P, with the form x_k in each, x_{k+1} := A_k\* x_k. So recursive of them is y_recursive=...\*((A_k\*...) mod p_k). Alternate to this, with good a_k=a_k-1\*...\*a_0 chain and large enough each a_k (this change log space scales), with matrix-vector exp and log (<a,x>^k, k in N+, so with sliding space p0 technique), convert A into R^{n\*n}, IDFT \* A'^k \* DFT \* x = IDFT\* (U L U^t)^k\[1, x', 1, x'\] = IDFT \* U L^k U^t \[1, x', 1, x'\]. So with DFT meaning, if there goes to fixed points, freq:= DFT \* x, x_k = IDFT \* U \* L^large num\* U^t \* freq, abs value on freq_k needs to be near the fixed point from first prediction. this concludes: x -> IDFT * \[..., a_k \* cis(x_\k\*k + x'\_k), ...\] = B\*\[..., cis(x_k\*x + x'\_k), ...\] mod a_n. If we predict with p0, what we treat L2(R) and m + 1 bits steps is L matrix multiply on the space : the rotation on the frequency space with bit table opreation, if we predict with original functions, it's on same prediction because the taylor series exists (If original table operation is structured with the arithmetic operators only, and, this is true because first A_k series exists). If we predict with p1 it depends: A \* x_nows 's a.row(k) is stable for any k on each steps, this is not a better condition but, if we calculate x_next with x_now and average the status steps, it is not a worse condition.
