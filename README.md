# p2
Categorize input stream and predict with them.

# Description:
If we don't have better prediction with p0, p1, we categorize series of input and predict with them by catgp.
In this case, if there's pattenizable jamming into data series, we can correct them.

delta.py predicts with delta, if original is unpredictable but delta is a little predictable, use this.
(This is almost always valid but this delta.py doesn't chains for multiple delta but it should chains in ideally.
The exception occurs when some delta has statistically illegal values, in this case, we should expand feed range.)

# General Tips
If there exists correctly predict next one step with \[...,x_n,f(...,x_n),f(...,f(...,x_n)),..\], f should be linear because \[...,a\*x_n+b,a\*f(...,x_n)+b,a\*f(...,f(...,x_n))+b,...\]. This concludes the structure of f is f(x):=(\<a,x\>). So p0 and p1 is reasonable in this meaning. But, if there exists predictor function, there is able to be non-predictable function on the meaning to them. (because there exists the stream that flip the predicted ones.)

Converting monotone nonlinear function causes some taylor coefficients conversion, but with p0 and p1 and catgp, it's also in their condition.

# Important General Tips
With 2^x:=\[1,x_0, ..., x_n, x_0 and x_1, ..., x_{n-1} and x_n, ..., x_0 and ... and x_n\] form, the operation 'and' and 'not' can be described as each taylor series that is also in y:=A\*2^x, A in R^{N\*N}, 2^x in {0, 1}^N.  
With this, randtools's counter diagonal method concludes the structure of f(...f(y)...) =: f^x(y) is Sum exp(a_k(y)\*x) = Sum cis(i\*a_k(y)\*x) = Sum cos(i\*a_k(y)\*x) + i \* sin(i\*a_k(y)\*x) (== cosh(a_k(y)\*x)+sinh(a_k(y)\*x)).

If we predict with p0, what we treat L2(R) is this hyperbolic cosine and hyperbolic sine value with some coefficient.
If we predict with p1, it depends f(x)'s complexity on status bit, if we average a.row(k), it's stable.

# Tips on p0:
If there exists ||f|\_(&lt; x_0)||&lt;|&Delta;f(x_0)| gulf or similar things, it's not C_0. Even integrate on them either. In this case, please transfer some original points distribution into arctan projected ones.

p0 predicts opposite with some frequency threshold.

p0 returns the matrix size limit to infinity on p1 on C0 condition, because of this, p0 is often stable enough.

# Tips on p1:
P1 often returns overlearned result, this causes unstable result.

We can always choose linear invariant if varlen is larger than status block size and data rank is also larger than them. This is because tan(\<a,\[x, f(x)\]\>) == 0 can be rewrited into the form arccos(cos(\<b,\[x, f(x)\]\>*(x_1...f_n\*f(x))^m0)) == abs(\<c,\[x, f(x)\]\>\*(x_1...x_n\*f(x))^m) == epsilon. Which f is F_2^n to F_2 any combination.

# Tips on p1, p2:
p1, p2 is using makeProgramInvariant and revert... with the form randtools invariant. So it has a little difference on the description itself. Because of them, they has a little glitch on the prediction.

The vector size to predict depends on the dimension the original functions have on infinite accuracy. This is because of P1 representation on the program on full rank input. So if there's creation or destruction or no concern or concern on the dimension that we have, catgp behaves as if calculation dimension is smaller than original function.

The two operand operator is described in R^4 vector, so collect another pairs and symmetrize them, R^8 is enough dimension to calculate. But if there's not enough data on the series, we should skip some steps each. (The case skip smaller than we need causes the gulf, another case skip larger than we need can causes accuracy not enough nor no clear prediction we get.)

This is because we can collect multiple of linear invariants in their dimension because if there exists (x, f(x)) pair, for each f(x) == const. value collection, with lagrange multiplier, (x) has linear invariant (can be 0 vector). So recursive on this, there's multiple of (x in R^8) invariants at all because two operand (x in R, f(x) in R) has the dimension.

The case varlen == 3 is valid in the case all of the status rank is in the each data condition and have some symmetry.
The case varlen == 7 is valid in the case all of the status rank is in the each data condition and doesn't have any symmetry in matrix description meaning. From somewhat, we need this condition on almost all of the PRNGs. (This might be caused by one function depends on the counter we input.)
The case otherwise, we should choose valren \> 7 condition. This is the case clipped status datas on the data series and we can't get max rank on them in varlen == 7. Otherwise, please sum up some each range on input.

N.B. in ideal, x+ := Ax\*(x_1...x_n)^m form, so with eigen decomposition, P^-1 x+ == A' P^-1 x \* (x_1...x_n)^m. if we average \<P 1, x\> form, it's very stable and it has only one form to calculate next one. If we average \<1, x\> form input/output, the form is A' p^-1_k depend vector we have, but it is also a little stable. So predict such with catgp can result continuous ones.

N.B. we need 3 variable on predictor because we get invariant on the data stream. This is because Lanczos transform leads us some average can have 3-term operator. We cannot use eigen decomposition itself because former one and latter one has a different vector.

N.B. If we average enough range on input and if input don't have periods smaller than them, it's better than original prediction because we average original matrix's row sometimes that is larger than average on first any interval scan. Otherwise, if input has a period, we can define pseudo prediction on it's period.

N.B. If original stream doesn't show full status (not enough rank on the data linear dependance), the prediction p1 and catgp fails as the edge clear gulf. This is avoidable with larger average length because of the matrix rank. Skip non period step also causes to avoid them.

N.B. A catgp corrects noise, this is because catgp includes p1 with some random noise index.

N.B. The step that PRNG have is often larger than 1000, this is because of the period and complexity itself.

# Tips on continuous:
We suppose all of {p0, p1, p2}: some middle point, left part and right part is the SAME structure (continuous). If there isn't all ranges on them, the structure is: \[rand, f(rand), rand, g(rand), ...\], f != g. But rand itself has the structure if they are PRNG, so it's with new f, g, h: \[(1,) f(1), ..., f(f(...f(1)...)), g(last), g(last), ..., h(1), ..., \]. So this is categorizable by catg AFTER all data is received.  
If we should make rand() points before and feed it some function, but this is also in p1 if data stream has enough length with deterministic PRNG rand.  
Beating this with small enough length, it's \[f_0(1), ..., f_n(1), ...\], but this is also described as turing computer with 0, ..., n for switch case description (if then description), so it's \[f(1, 1), ..., f(n, 1), ...\]. This status length bits depends maximum of original f_0, ..., f_n size. (AFTER all data is received.)  
If we predict with some prediction method and bet with them, satistification on the hypothesis continuous condition causes continuous result,
otherwise, uncontinuous result and statistical illegal value encounted. So first hypothesis on the data is the matter.)

# Tips:
python3 cr.py 1 ... ... R | (catg|catgr) ... | head -n ... | tail -n ... | python3 op2.py e ... | ... | python3 op2.py m ...?; only for phrase on rhythm.

N.B. Re-categorize categorized part is same categorize as original with some input threadshold if dimension is the same one.

# Another Download Sites
* https://drive.google.com/drive/folders/1B71X1BMttL6yyi76REeOTNRrpopO8EAR?usp=sharing
* https://1drv.ms/u/s!AnqkwcwMjB_PaDIfXya_M3-aLXw?e=qzfKcU
* https://ja.osdn.net/users/bitsofcotton/

