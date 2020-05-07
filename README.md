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
To get this data, some PRNGs pseudo-makes this chain on some ranges, then, accelerate numerical patterns so to avoid
range-dependant vulnerabilities.

# General Tips
If there exists correctly predict next one step with \[...,x_n,f(...,x_n),f(f(...,x_n)),..\], f should be linear because \[...,a\*x_n+b,a\*f(...,x_n)+b,a\*f(f(...,x_n))+b,...\]. This concludes the structure of f is f(x):=(\<a,x\>). So p0 and p1 is reasonable in this meaning. But, if there exists predictor function, there is able to be non-predictable function on the meaning to them. (because there exists the stream that flip the predicted ones.)
And, one of linear-space or exp-space or log-space, tetration-space or inverse-tetration-space is unpredictable in that meaning, others can be exists by some numerical tests.

# General Tips 2
If there exists correctly expanded f s.t. f(x):=sum a_k\*x^k+O(\epsilon), exp(f(x))=Pi exp(a_k\*x^k+O(\epsilon))=Pi_k Sum_l (a_k\*x_k)^l/l!)\*exp(O(\epsilon))=Sum_K x^K\*Sum_(K=Sum_i k_i\*l_i) a_(k_i)^(l_i)/((l_i)!)\*exp(O(\epsilon)), this concludes the coefficient matrix needs in f: \[a_0, ..., a_n\] to exp(f) : \[, ..., Sum_(K=Sum_i k_i\*l_i) a_(k_i)^(l_i)/((l_i)!), ...\] so this shifts some frequency space conditions in DFT meaning. If one of exp recursive-log recursive space is able to be predictable, one of the frequency space is valid for the prediction. <!-- and if f(x) and f(1/x) needs to be almost same condition, since f(x) -&gt; f(1/x) needs exchange LPF condition to HPF condition original f needs some flat coefficient vector condition nor, one of them is predictable. Nor, some extra randomization method had to be applied to the differs. And, if that extra randomization method is stable to fail the prediction, some waiting method with such prediction will gain better results.  -->
