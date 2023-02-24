# p2
Generic predictor on expectation value mediumly depends data itself.
Also, integrated generic predictor they slices some dimension of input stream.

# Description:
If we don't have better prediction with p0, p1, we categorize series of input and predict with them by catgp.
In this case, if there's pattenizable jamming into data series, we can correct them.

The integrated predictor and the parts targets only a finite inner status condition and we must suppose input stream internal state dimension size. If the supposed size is smaller than input stream, this fails.

Also, they suppose input stream some average slide is one of the 3 case mainly: (i) Lebesgue measurable (ii) calculatible by accuracy limited register computer (iii) stream is the result of some multiple valued output that can rationaly to categorize.
Also, sub of the method is: (iv) return to average on some of the range or whole input (v) the structure average describes enough input structure (vi) flip last.
p.cc status \< 0 for implicit copycat prediction, otherwise, explicit prediction.

# XXX
We cannot predict via these predictors on saw tooth or triangular or similar wave which depends on unobserved inner status in sliding window. However, such PRNGs must have inner status bit larger than lg(x_trigger_place).
Also p.cc depends on walk accuracy theirselves. So to continue prediction, we need better accuracy if walk has enough distance from origin point.

# Known Bug
If we use cr.py with lieonn.hh description, we should pass the parameter reasonable (output to be less than INT_MAX), otherwise, periodical clipping will occur causes broken result.

# General Tips
If there exists correctly predict next one step with \[...,x_n,f(...,x_n),f(...,f(...,x_n)),..\], we can suppose f as a linear with \[...,a\*x_n+b,a\*f(...,x_n)+b,a\*f(...,f(...,x_n))+b,...\] if (some range)-markov with below and the finite accuracy condition, some range skipped series. This concludes the structure of f is f(x):=(\<a,x\>). So p0 and p1 is reasonable in this meaning. But, if there exists predictor function, there is able to be non-predictable function on the meaning to them. (because there exists the stream that flip the predicted ones.) The dimension of a vector depends on original f nonlinear part threshold.

Converting monotone nonlinear function causes some taylor coefficients conversion, but with p0 and p1 and catgp, it's also in their condition.

# Important General Tips
With 2^x:=\[1,x_0, ..., x_n, x_0 and x_1, ..., x_{n-1} and x_n, ..., x_0 and ... and x_n\] form, the operation 'and' and 'not' can be described as each taylor series that is also in y:=A\*2^x, A in R^{N\*N}, 2^x in {0, 1}^N.  
With this, randtools's counter diagonal method concludes the structure of f(...f(y)...) =: f^x(y) is Sum exp(a_k(y)\*x) = Sum cis(i\*a_k(y)\*x) = Sum cos(i\*a_k(y)\*x) + i \* sin(i\*a_k(y)\*x) (== cosh(a_k(y)\*x)+sinh(a_k(y)\*x)).

If we predict with p1, it depends f(x)'s complexity on status bit, if we average a.row(k), it's stable.

# Tips on p0:
If input stream has a jamming to p0, p0 fails. In such case, we can change input argument.

# Tips on p1:
P1 often returns overlearned result, this causes unstable result. But they're valid with finite register finite accuracy condition and toeplitz of them are max rank on status linear independence block meaning.

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

N.B. The status that PRNG have is often larger than 1000, this is because of the period and complexity itself.

# Tips on p1, p2 (2)
p1, p2 has a little glitch to randtools description (make period on y-axis be ignored).
So to hack this, we can do cr.py L command described in p0 twice.

# Tips on continuous:
We suppose all of {p0, p1, p2}: some middle point, left part and right part is the SAME structure (continuous). If there isn't all ranges on them, the structure is: \[rand, f(rand), rand, g(rand), ...\], f != g. But rand itself has the structure if they are PRNG, so it's with new f, g, h: \[(1,) f(1), ..., f(f(...f(1)...)), g(last), g(last), ..., h(1), ..., \]. So this is categorizable by catg AFTER all data is received.  
If we should make rand() points before and feed it some function, but this is also in p1 if data stream has enough length with deterministic PRNG rand.  
Beating this with small enough length, it's \[f_0(1), ..., f_n(1), ...\], but this is also described as turing computer with 0, ..., n for switch case description (if then description), so it's \[f(1, 1), ..., f(n, 1), ...\]. This status length bits depends maximum of original f_0, ..., f_n size. (AFTER all data is received.)  
If we predict with some prediction method and bet with them, satistification on the hypothesis continuous condition causes continuous result,
otherwise, uncontinuous result and statistical illegal value encounted. So first hypothesis on the data is the matter.)

# Tips on jamming
If some of the pipe/prng generator/original stream has a jamming from output by auto parameter configurer or so on, we can only say one of a triplet is ok.
This is because the jammer jams predictors as to be 0 output in expectation value, since (x, f(x), status) has 3 dimension in literally in the invariant meaning (cf. randtools, cf. constant is described as x\_k - x\_(k - 1)), jammer cannot jam all of them other than 0 expectation value input if the 3 of the predictor is correct. (if they stands on some different invariants.)
Even with so, jammer also is able to change sgn(x) they causes backward generation on PRNG, but this is equivalent to -(-x, f(x), status) == (x, -f(x), -status) but jammer can do this (e.g. re-seed).

# Tips on jamming in short range
But with (x, status) pair can be treated with (status(status, x)) variable in literally in short range. So short range related to use of status length in predictor, only pair of predictors can work.

# Tips on jamming in finite accuracy input/status/counter.
However, with appending the status/counter into out of accuracy bits, literally only one dimension they can jam out. So pair of predictors can work.

# Tips on prng with initial steps / medium walked steps.
Initializing PRNGs by short and non heavy method causes only shuffles the short input entropy into initialized states. This causes to predict initial steps needs small number of status bits because of deterministic and shadowed, short span in the long period status change. So they might need some larger bits to predict when some of PRNGs are enough walked. But with simpler PRNGs, they're equivalent to initial small number of status bits because of non large number of status in them does not timing related change.

-&gt; It's rather from p0's measurable condition.

# Tips on jammer on my machine
once we get p0 +... \| p1 ... \| p0 -... \| cr.py 0 1 1 A \| p0 -1 works well, but after then, the jammer jam outs input as gulf only nor the attacker gets p1 compiler error as lldb backtrace infinite loop.

# Tips on chasing invariant size
If the jammer correctly jam out input stream, it begins the chase of invariant size. So in this case, we only can enlarge input argument in each, so the case concludes the larger computing power, the larger span.

# Tips:
python3 cr.py 1 ... ... R | (catg|catgr) ... | head -n ... | tail -n ... | python3 op2.py e | ... | tail -n ... | python3 op2.py m; only for phrase on rhythm.

N.B. Re-categorize categorized part is same categorize as original with some input threadshold if dimension is the same one.

N.B. we take original/~ as x~rx, r in R when they doesn't normalized by the method like conv_check/nand.cc.

# Tips on original stream status dimension and prediction dimension:
We are estimating it might enough p.cc argv[1] larger than input stream status dimension to calculate in average. We might need to do twice if p.cc is being jammed condition. We normally need first unstable run with argv[1] \* 3 input steps (see above).

# Tips on speed - accuracy trade off.
A p.cc is using sqrt(argv[1]) for calculating status and use pad sqrt(argv[1]) length. So from this, the accuracy of originals can slips.

# Tips on predicting rand.cc
If we predict some PRNG, the separatable computing block number and its block size is the matter.
If calculating accuracy is not enough, we need to enlarge block number supposed to pass into argv[1] in p.cc.

If we're predicting from initialized point the plain PRNGs without timing hack initialized with fixed-size entropy without loss of the points, we only need the status size the original entropy bit size, however, we should use all of the point the PRNGs produce to predict with.
If there's the some loss point from first point out of the status we concern in such case, the prediction might fails after the point.

# Tips on multiple of collateral
There also exists non Lebesgue measurable based method starting on the fixed data (multiples of invariant insertion to the dimension we cannot divide) whether which matches or not, however, literally in bad luck, this can always fail because of multiple of the prediction makes nonsense prediction even they makes a sense after all data is received condition with the predictor in short range.

<strike>If such non Lebesgue measurable function is consistent in locally and works well as expected to, argv\[1\] of any of the input has a finite upper bound, however, we think we can create a jammer to such predictor(s) in rational, so this concludes below. But if the calculation itself can be tangled to such structures, the hypothesis jammer exists can fail in such case. (when being tangled embryonic with such tangling or only the argv\[1\] is not enough for rational structure, original stream is seen as the jammer, when inverse tangled, reverse direction walk output.)</strike>

In such case, if non Lebesgue measurable function is consistent in locally and works well, even so, we need the hierarchy structure on prediction on \{compress\} and the status we observe needs to be in the observation observed and passed points into the execution binary. So we cannot omit in such case because the states can be selected in arbitrary way including jammer itself.

# Reducing sparsity who effects long status length
We take x\^2/3 scale in virtually in p.cc. This causes numerical test valid.

# Retry met jammer jamming
In the worst case on p2.cc:Ppretry, the jammer causes p.cc output 0 prediction.
In this case, we can only argv\[1\] += 1.

However, we might meet worse than this jammer some another day.

# Another Download Sites (Closed)
* https://drive.google.com/drive/folders/1B71X1BMttL6yyi76REeOTNRrpopO8EAR?usp=sharing
* https://1drv.ms/u/s!AnqkwcwMjB_PaDIfXya_M3-aLXw?e=qzfKcU
* https://ja.osdn.net/users/bitsofcotton/

