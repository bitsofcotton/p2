# p2
(i)  Subtract little stable invariant from the series by p1, then, predict with p0.  
(ii) Categorize input stream and predict with them.  

# Description:
If we don't have better prediction with p0 nor p1, p01 handles differ on each of them that causes noise that we can handle with p0.  
N.B. the structure we subtract by p01 depends status length, so if status length is enough, the invariant found first is subtracted, this causes the most part that effects prediction itself, and if status length is not enough, this also subtract partial invariant that effects prediction itself.  
Command line option on p01 is same as p1.

# Description:
If we don't have better prediction with p01, we categorize series of input and predict with them by catgp.
In this case, if there's pattenizable jamming into data series, we can correct them.

# General Tips
If there exists correctly predict next one step with \[...,x_n,f(...,x_n),f(...,f(...,x_n)),..\], f should be linear because \[...,a\*x_n+b,a\*f(...,x_n)+b,a\*f(...,f(...,x_n))+b,...\]. This concludes the structure of f is f(x):=(\<a,x\>). So p0 and p1 is reasonable in this meaning. But, if there exists predictor function, there is able to be non-predictable function on the meaning to them. (because there exists the stream that flip the predicted ones.)

Converting monotone nonlinear function causes some taylor coefficients conversion, but with p0 and p1, it's also in their condition.

# Important General Tips
With 2^x:=\[1,x_0, ..., x_n, x_0 and x_1, ..., x_{n-1} and x_n, ..., x_0 and ... and x_n\] form, the operation 'and' and 'not' can be described as each taylor series that is also in y:=A\*2^x, A in R^{N\*N}, 2^x in {0, 1}^N.  
With this A, A'^k \* 2^x = (U L U^t)^k\[1, x', 1, x'\] = U L^k U^t \[1, x', 1, x'\]. So with, x_k = U \* L^large num\* U^t \* \[1, x', 1, x'\] 's value on U^t\[..., x\'\_k, ...\] needs to be near the fixed point from first. this concludes: 2^x -> Re \[..., a_k \* cis(x\*(2^x)'\_k + x'\_k), ...\] = B\*\[..., cos(&alpha;\_k\*x), ...\], &alpha;\_k in \[-&pi;,&pi;].  

If we predict with p0, what we treat L2(R) is cosine value with bit table opreation, (with fixed startpoint and no change algorithm, this is valid, and if the series have the long periods and circular results, this also valid.), but there still exists sampling theorem.  
If we predict with p1, it depends: A \* x_nows 's a.row(k) is stable for any k on each steps, and if we average the status length, this is valid for them from first meaning (x_next = A \* x).

# Tips:
If there exists ||f|\_(&lt; x_0)||&lt;|&Delta;f(x_0)| gulf or similar things, it's not C_0. Even integrate on them either. In this case, please transfer some original points distribution into arctan projected ones.

A p0 predicts opposite between f < 0 case and 0 < f case. This is because of linear function. So to avoid this, please add offset.

# Tips:
After p1 subtract invariant with enough variable length, next predictor p1's variable length is decreased.
This is an analogy to QR decomposition.

# Tips:
If we can't statistically predict original stream by {p2, p1, p0}, the original data stream is data seed itself meaning to {p2, p1, p0}.
This means the given data stream doesn't have rational stable inner structure. So it is random stream itself in the meaning of given argument range.
This doesn't mean there's no correlation on the data because we can categorize them by catg itself after all data received (not before).  
This is checked by perverse.py with some range modifications. So taking another ranges, we may have another results.

# Another Download Sites
* https://drive.google.com/drive/folders/1B71X1BMttL6yyi76REeOTNRrpopO8EAR?usp=sharing
* https://1drv.ms/u/s!AnqkwcwMjB_PaDIfXya_M3-aLXw?e=qzfKcU
* https://ja.osdn.net/users/bitsofcotton/

# Archive
This repository is archived, so without bugreport, will no change.

