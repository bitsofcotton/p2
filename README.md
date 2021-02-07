# p2
Generic predictor corrector with random. This suppose the random stream we make is better than original random source and the one we made is a little predictable with some prediction method. If so, this slices a little amount of random entropy. This is because short length of original prediction method divides 3 parts, bet ok, bet ng, or no bet. So with blending no periodical datas, it flatten 33%, 33%, 33% of them idealy, but with a little predictable part, it shifts original to a little predictable parts. But in fact, this only changes sliding window distribution.

# General Tips
If there exists correctly predict next one step with \[...,x_n,f(...,x_n),f(...,f(...,x_n)),..\], f should be linear because \[...,a\*x_n+b,a\*f(...,x_n)+b,a\*f(...,f(...,x_n))+b,...\]. This concludes the structure of f is f(x):=(\<a,x\>). So p0 and p1 is reasonable in this meaning. But, if there exists predictor function, there is able to be non-predictable function on the meaning to them. (because there exists the stream that flip the predicted ones.)

# Important General Tips
With 2^x:=\[1,x_0, ..., x_n, x_0 and x_1, ..., x_{n-1} and x_n, ..., x_0 and ... and x_n\] form, the operation 'and' and 'not' can be described as each taylor series that is also in y:=A\*2^x, A in R^{N\*N}, 2^x in {0, 1}^N.  
With this A, A'^k \* 2^x = (U L U^t)^k\[1, x', 1, x'\] = U L^k U^t \[1, x', 1, x'\]. So with, x_k = U \* L^large num\* U^t \* \[1, x', 1, x'\] 's value on U^t\[..., x\'\_k, ...\] needs to be near the fixed point from first. this concludes: 2^x -> Re \[..., a_k \* cis(x\*(2^x)'\_k + x'\_k), ...\] = B\*\[..., cos(&alpha;\_k\*x), ...\], &alpha;\_k in \[-&pi;,&pi;].  

If we predict with p0, what we treat L2(R) is cosine value with bit table opreation, (with fixed startpoint and no change algorithm, this is valid, and if the series have the long periods and circular results, this also valid.), but there still exists sampling theorem.  
If we predict with p1, it depends: A \* x_nows 's a.row(k) is stable for any k on each steps, and if we average the status length, this is valid for them from first meaning (x_next = A \* x).

# Tips:
If there exists ||f|\_(&lt; x_0)||&lt;|&Delta;f(x_0)| gulf or similar things, it's not C_0. Even integrate on them either. In this case, please transfer some original points distribution into arctan projected ones.

# Tips:
Both p0 and p1 predicts opposite between f < 0 case and 0 < f case. This is because of linear function. So to avoid this, please place offset.

# Tips:
With p2 beat option, we can test whether original function is one function recursion function.
If prediction after p2 beat option (which has &Delta;x\_apply:=&Delta;x/||&Delta;x||\_1 on each) doesn't have contraction function,
it might be non one function recursion C0 function in that range.

# Another Download Sites
* https://drive.google.com/drive/folders/1B71X1BMttL6yyi76REeOTNRrpopO8EAR?usp=sharing
* https://1drv.ms/u/s!AnqkwcwMjB_PaDIfXya_M3-aLXw?e=qzfKcU

# Archive
This repository is archived, so without bugreport, will no change.

