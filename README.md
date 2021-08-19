# p2
Categorize input stream and predict with them.

# Description:
If we don't have better prediction with p0, p1, we categorize series of input and predict with them by catgp.
In this case, if there's pattenizable jamming into data series, we can correct them.

# General Tips
If there exists correctly predict next one step with \[...,x_n,f(...,x_n),f(...,f(...,x_n)),..\], f should be linear because \[...,a\*x_n+b,a\*f(...,x_n)+b,a\*f(...,f(...,x_n))+b,...\]. This concludes the structure of f is f(x):=(\<a,x\>). So p0 and p1 is reasonable in this meaning. But, if there exists predictor function, there is able to be non-predictable function on the meaning to them. (because there exists the stream that flip the predicted ones.)

Converting monotone nonlinear function causes some taylor coefficients conversion, but with p0 and p1, it's also in their condition.

# Important General Tips
With 2^x:=\[1,x_0, ..., x_n, x_0 and x_1, ..., x_{n-1} and x_n, ..., x_0 and ... and x_n\] form, the operation 'and' and 'not' can be described as each taylor series that is also in y:=A\*2^x, A in R^{N\*N}, 2^x in {0, 1}^N.  
With this, randtools's counter diagonal method concludes the structure of f(...f(y)...) =: f^x(y) is Sum exp(a_k(y)\*x) = Sum cis(i\*a_k(y)\*x) = Sum cos(i\*a_k(y)\*x) + i \* sin(i\*a_k(y)\*x) (== cosh(a_k(y)\*x)+sinh(a_k(y)\*x)).

If we predict with p0, what we treat L2(R) is this hyperbolic cosine and hyperbolic sine value with some coefficient.
If we predict with p1, it depends f(x)'s complexity on status bit, if we average a.row(k), it's stable.

# Tips on p0:
If there exists ||f|\_(&lt; x_0)||&lt;|&Delta;f(x_0)| gulf or similar things, it's not C_0. Even integrate on them either. In this case, please transfer some original points distribution into arctan projected ones.

A p0 predicts opposite between f < 0 case and 0 < f case. This is because of linear function. So to avoid this, please add offset.

# Tips on p1:
After p1 subtract invariant with enough variable length, next predictor p1's variable length is decreased.
This is an analogy to QR decomposition.

P1 often returns overlearned result, this causes unstable result.

# General Tips:
The vector size to predict depends on the dimension the original functions have on infinite accuracy. This is because of P1 representation on the program on full rank input. So if there's creation or destruction or no concern or concern on the dimension that we have, catgp behaves as if calculation dimension is smaller than original function.

If we input finite exponent and finite mantissa bits, with infinite accuracy computer, we can make the status dimension into 1 dimension at all, so in this case, varlen == 2 on p1 and catg. So make some valid prediction twice causes vanish variant from output in infinite accuracy input and there's finite status bits and dimensions. This causes the range of jamming itself is smaller or equal to 2, so average every input pair and skip covered them causes a little predictable ones, this is because every input pair is jammed related to whole input. So otherwise, we should predict a little better if jamming range is longer than them or multiple jamming range we have (because in that case, whole prediction has to have bias).

N.B. if the accuracy we have is not enough to structure, varlen == 2 isn't represents whole of the function.

# Tips on continuous:
We suppose all of {p0, p1, p2}: some middle point, left part and right part is the SAME structure (continuous). If there isn't all ranges on them, the structure is: \[rand, f(rand), rand, g(rand), ...\], f != g. But rand itself has the structure if they are PRNG, so it's with new f, g, h: \[(1,) f(1), ..., f(f(...f(1)...)), g(last), g(last), ..., h(1), ..., \]. So this is categorizable by catg AFTER all data is received.  
If we should make rand() points before and feed it some function, but this is also in p1 if data stream has enough length with deterministic PRNG rand.  
Beating this with small enough length, it's \[f_0(1), ..., f_n(1), ...\], but this is also described as turing computer with 0, ..., n for switch case description (if then description), so it's \[f(1, 1), ..., f(n, 1), ...\]. This status length bits depends maximum of original f_0, ..., f_n size. (AFTER all data is received.)  
A p2 is standing on hypothesis there exists a function that extends small region makes no difference from before. And, catgp prediction needs the context on the range we categorize, so varlen == 2 cannot be used to them.
cut.py 'f' nor 'F' adds a little amount of continuous ones without attaching delta if the original function isn't continuous at all. And if it's continuous enough in C1 meaning, just flip one step before can correct with enough stablility.

# General Tips:
If we predict with some prediction method and bet with them, satistification on the hypothesis continuous condition causes continuous result,
otherwise, uncontinuous result and statistical illegal value encounted. So first hypothesis on the data is the matter.

# General Tips:
A p1 and catgp complement length is depends on variables and calculation depths whole. So in general, n variables whole input output, if we can use one variable only once in them (if we can reduce two operand operators on them whole), the extra dimension size is ceil(n / 2) + ceil(ceil(n / 2) / 2) + ... + 1, for n == whole variable + 1.
The reductions on two operand operator is obscure because there exists any tensor that to describe relations. If hypothesis is true, two operand operator describes each matrix slices, three operand operator's third operand itself switches for each matrix itself, not the operator itself, but, if first two operand opeartor produces them with indices, it's ok.
But with complement dimension, below is optimal case, so non optimal case, the dimension we complement with linear should larger than them, not just them.

# General Tips:
p0 returns the matrix size limit to infinity on p1, because of this, p0 is often stable enough.

# General Tips
If we set catgp to shorter range relative from PRG itself, the result can be triangular wave or so on. The modern PRNGs have the techniques to enlarge original PRNG matrix size as block diagonal ones or so on....

# Another Download Sites
* https://drive.google.com/drive/folders/1B71X1BMttL6yyi76REeOTNRrpopO8EAR?usp=sharing
* https://1drv.ms/u/s!AnqkwcwMjB_PaDIfXya_M3-aLXw?e=qzfKcU
* https://ja.osdn.net/users/bitsofcotton/

# Refresh Archived
This repository is close state without external library.
