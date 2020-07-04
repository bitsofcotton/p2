# p2
Generic predictor corrector with random. This suppose the random stream we make is better than original random source and the one we made is a little predictable with some prediction method. If so, this slices a little amount of random entropy. This is because short length of original prediction method divides 3 parts, bet ok, bet ng, or no bet. So with blending no periodical datas, it flatten 33%, 33%, 33% of them idealy, but with a little predictable part, it shifts original to a little predictable parts. But in fact, this only changes sliding window distribution.

# How to use
Change p2.py getrand functions and pp subprocess initializer.

# Tips
N.B. d_k + d_{k-1} part is almost in L2(R) in sampling meaning. And, one of the d_k part or
d_k - d_{k-1} part might be in L2(R) part in that meaning according to some numerical tests.
This might be because of differential-integral space norm conditions.  
And if so, p2-unpredictable method should be the one like the chain:
d_k unpredictable then d_k inverse sign then d_k-d_{k-1} unpredictable then d_k-d_{k-1} inverse sign and so on.
(But in fact, p0 needs to treat d_k and delta d_k as the same condition, this means whole d_k and delta d_k unpredictable -> d_k and delta d_k inverse sign chain is needed, but inverse sign cannot be the meaning of the one in that condition.)  
To get this data, some PRNGs pseudo-makes this chain on some ranges, then, accelerate numerical patterns so to avoid
range-dependant vulnerabilities.

# General Tips
If there exists correctly predict next one step with \[...,x_n,f(...,x_n),f(f(...,x_n)),..\], f should be linear because \[...,a\*x_n+b,a\*f(...,x_n)+b,a\*f(f(...,x_n))+b,...\]. This concludes the structure of f is f(x):=(\<a,x\>). So p0 and p1 is reasonable in this meaning. But, if there exists predictor function, there is able to be non-predictable function on the meaning to them. (because there exists the stream that flip the predicted ones.)
And, one of linear-space or exp-space or log-space, tetration-space or inverse-tetration-space is unpredictable in that meaning, others can be exists by some numerical tests.

# Important General Tips
With bitsofcotton/randtools, any fixed operations on N is described as fixed A in F_2^{n\*n} with the form y in F_2^n, y := A \* x. So with such A into R^{n\*n}, A=IDFT\*A'\*DFT, recursive frequency condition should be IDFT\*A'^n\*DFT. we can make A' into symmetric with some tricks with lagrange multipliers, so recursive makes y = (A'')^n*\[1, x, 1, x\] = (U L U^t)^n\[1, x, 1, x\] = U L^n U^t \[1, x, 1, x\]. So with DFT meaning, if there goes to fixed points, freq:= DFT \* x, x_k = IDFT \* recursive series of A \* x, abs value on freq_k needs to be near the fixed point from first prediction. this concludes: x -> IDFT * \[..., \pm a_k \* cis(x_\k\*k + x'\_k), ...\]. If we predict with p0, what we treat L2(R) and m + 1 bits steps is L matrix multiply on the space : the rotation on the frequency space, if we predict with original functions, it's on same prediction because the taylor series exists. If we predict with p1 it depends: A \* x_nows 's a.row(k) is stable for any k on each steps, this is not a better condition but, if we calculate x_next with x_now and average the status steps, it is not a worse condition.
