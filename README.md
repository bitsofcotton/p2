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
To get this data, some PRNGS pseudo-makes this chain on some ranges, then, accelerate numerical patterns so to avoid
range-dependant vulnerabilities.
