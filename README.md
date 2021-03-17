# p2
(i)  Subtract little stable invariant from the series by p1, then, predict with p0.  
(ii) Categorize input stream and predict with them.  

# Description:
If we don't have better prediction with p0 nor p1, p01 handles differ on each of them that causes noise that we can handle with p0. This is for dummy adopted jamming.
Command line option on p01 is same as p1.

# Description:
If we don't have better prediction with p01, we categorize series of input and predict with them by catgp.
In this case, if there's pattenizable jamming into data series, we can correct them.

# General Tips
If there exists correctly predict next one step with \[...,x_n,f(...,x_n),f(...,f(...,x_n)),..\], f should be linear because \[...,a\*x_n+b,a\*f(...,x_n)+b,a\*f(...,f(...,x_n))+b,...\]. This concludes the structure of f is f(x):=(\<a,x\>). So p0 and p1 is reasonable in this meaning. But, if there exists predictor function, there is able to be non-predictable function on the meaning to them. (because there exists the stream that flip the predicted ones.)

Converting monotone nonlinear function causes some taylor coefficients conversion, but with p0 and p1, it's also in their condition.

# Important General Tips
With 2^x:=\[1,x_0, ..., x_n, x_0 and x_1, ..., x_{n-1} and x_n, ..., x_0 and ... and x_n\] form, the operation 'and' and 'not' can be described as each taylor series that is also in y:=A\*2^x, A in R^{N\*N}, 2^x in {0, 1}^N.  
With this, randtools's counter diagonal method concludes the structure of f(...f(y)...) =: f^x(y) is Sum exp(a_k(y)\*x) = Sum cis(i\*a_k(y)\*x) = Sum cos(i\*a_k(y)\*x) + i \* sin(i\*a_k(y)\*x).

If we predict with p0, what we treat L2(R) is this cosine and sine imaginary value with some coefficient.
If we predict with p1, it depends f(x)'s complexity on status bit, if we average a.row(k), it's stable.

# Tips:
If there exists ||f|\_(&lt; x_0)||&lt;|&Delta;f(x_0)| gulf or similar things, it's not C_0. Even integrate on them either. In this case, please transfer some original points distribution into arctan projected ones.

A p0 predicts opposite between f < 0 case and 0 < f case. This is because of linear function. So to avoid this, please add offset.

# Tips:
After p1 subtract invariant with enough variable length, next predictor p1's variable length is decreased.
This is an analogy to QR decomposition.

# Tips:
We suppose all of {p0, p1, p2}: some middle point, left part and right part is the SAME structure (continuous). If there isn't all ranges on them, the structure is: \[rand, f(rand), rand, g(rand), ...\], f != g. But rand itself has the structure if they are PRNG, so it's with new f, g, h: \[(1,) f(1), ..., f(f(...f(1)...)), g(last), g(last), ..., h(1), ..., \]. So this is categorizable by catg AFTER all data is received.  
If we should make rand() points before and feed it some function, but this is also in p1 if data stream has enough length with deterministic PRNG rand.  
Beating this with small enough length, it's \[f_0(1), ..., f_n(1), ...\], but this is also described as turing computer with 0, ..., n for switch case description (if then description), so it's \[f(1, 1), ..., f(n, 1), ...\]. This status length bits depends maximum of original f_0, ..., f_n size.  
So they means deterministic PRNG that fast enough and has small enough status length cannot be exist if we have any better length.

# Another Download Sites
* https://drive.google.com/drive/folders/1B71X1BMttL6yyi76REeOTNRrpopO8EAR?usp=sharing
* https://1drv.ms/u/s!AnqkwcwMjB_PaDIfXya_M3-aLXw?e=qzfKcU
* https://ja.osdn.net/users/bitsofcotton/

# Archive
This repository is archived, so without bugreport, will no change.

