# p2
Generic predictor on expectation value mediumly depends data itself.
Also, one of a predictor for being controlled stream.

# XXX
The p\*-series makes the hypothesis the function is unique and how to use internal status is completely only unique.

So if there's a slow variable they're hidden by counter or so on, our first hypothesis fails on such time counter place, however, after combine the state some of the steps, our first hypothesis fullfilled on some range, however, the jammer can attack to the sign of the result even in such cases.

# Description:
If we don't have better prediction with p0, p1, we categorize series of input and predict with them by catgp.
In this case, if there's pattenizable jamming into data series, we can correct them.

# Description2:
pr4.cc is for being controlled condition. However, this cannot get better result if this is counter measured. eg. somerange raw step, somerange random step on the stream.

# Known Bug
If we use cr.py with lieonn.hh description, we should pass the parameter reasonable (output to be less than INT_MAX), otherwise, periodical clipping will occur causes broken result.

# General Tips
If there exists correctly predict next one step with \[...,x_n,f(...,x_n),f(...,f(...,x_n)),..\], we can suppose f as a linear with \[...,a\*x_n+b,a\*f(...,x_n)+b,a\*f(...,f(...,x_n))+b,...\] if (some range)-markov with below and the finite accuracy condition, some range skipped series. This concludes the structure of f is f(x):=(\<a,x\>). So p0 and p1 is reasonable in this meaning. But, if there exists predictor function, there is able to be non-predictable function on the meaning to them. (because there exists the stream that flip the predicted ones.) The dimension of a vector depends on original f nonlinear part threshold.

Converting monotone nonlinear function causes some taylor coefficients conversion, but with p0 and p1 and catgp, it's also in their condition.

# Important General Tips
With 2^x:=\[1,x_0, ..., x_n, x_0 and x_1, ..., x_{n-1} and x_n, ..., x_0 and ... and x_n\] form, the operation 'and' and 'not' can be described as each taylor series that is also in y:=A\*2^x, A in R^{N\*N}, 2^x in {0, 1}^N.  
With this, randtools's counter diagonal method concludes the structure of f(...f(y)...) =: f^x(y) is Sum exp(a_k(y)\*x) = Sum cis(i\*a_k(y)\*x) = Sum cos(i\*a_k(y)\*x) + i \* sin(i\*a_k(y)\*x) (== cosh(a_k(y)\*x)+sinh(a_k(y)\*x)).

If we predict with p1, it depends f(x)'s complexity on status bit, if we average a.row(k), it's stable.

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

# Tips on chasing invariant size
If the jammer correctly jam out input stream, it begins the chase of invariant size. So in this case, we only can enlarge input argument in each, so the case concludes the larger computing power, the larger span.

# Tips:
python3 cr.py 1 ... ... R | (catg|catgr) ... | head -n ... | tail -n ... | python3 op2.py e | ... | tail -n ... | python3 op2.py m; only for phrase on rhythm.

N.B. Re-categorize categorized part is same categorize as original with some input threadshold if dimension is the same one.

N.B. we take original/~ as x~rx, r in R when they doesn't normalized by the method like conv_check/nand.cc.

# Tips on multiple of collateral
There also exists non Lebesgue measurable based method starting on the fixed data (multiples of invariant insertion to the dimension we cannot divide) whether which matches or not, however, literally in bad luck, this can always fail because of multiple of the prediction makes nonsense prediction even they makes a sense after all data is received condition with the predictor in short range.

<strike>If such non Lebesgue measurable function is consistent in locally and works well as expected to, argv\[1\] of any of the input has a finite upper bound, however, we think we can create a jammer to such predictor(s) in rational, so this concludes below. But if the calculation itself can be tangled to such structures, the hypothesis jammer exists can fail in such case. (when being tangled embryonic with such tangling or only the argv\[1\] is not enough for rational structure, original stream is seen as the jammer, when inverse tangled, reverse direction walk output.)</strike>

In such case, if non Lebesgue measurable function is consistent in locally and works well, even so, we need the hierarchy structure on prediction on \{compress\} and the status we observe needs to be in the observation observed and passed points into the execution binary. So we cannot omit in such case because the states can be selected in arbitrary way including jammer itself.

# Reducing sparsity who effects long status length
We take x\^2/3 scale in virtually in p.cc. This causes some of the numerical test valid.

This is because taylor series of f(x,k):=f(...f(x)...) (k times f) concludes Sum_m ... (cbrt(k))^2m series.
Also, scale breaks the original stream period by irrational period causes rich of inner states on the stream we stuck. So in this case, a little stable result until we met around gulf point the inner states strongly affect.

# Any of the predictor, they have the jammer.
If the jammer only targets first order predicton, we can avoid them by multiple of range average causes jammer needs least common multiply period.
However, any of the predictor, they have the jammer to them, so jammer retargets them, the condition of the period are ignored.
So this is which is latter effect one chase, so deterministic prediction (includes PRNG ones) cannot avoid jammer from lower layer level.
So we conclude once prediction done, then, repredict with another similar ones, one of them seems ok, we did best for them.

# Integer calculation jamming from single to multiple to single funciton.
If our calculator is being jammed from some existence, we cannot avoid them at all if the jammer seriously jame out us. This is in theoretical if we cannot fix such s2m2s calculation glitch.

# Any of the predictor, any of the jammer (n times).
We choose the predictor as simple enough.
This is because when we're in being jammed condition, to make counter measure to them causes worse predictable (saved) input as well.
This is also with the condition catgp as well.
So whether or not we choose satate out of the length we treat, it's the same condition. So we only target strict on the states on fixed length in p.cc.

So all we can do the best is to re-predict with another argv after saving the input and close the connection to PRNG which generates suspicious stream.

# Any of the predictor, any of the jammer (n+1 times).
However, if the jammer retargets us including argv or some another binaries, the jammer needs to run with supremum of argv antecedent to predictor.
In the case, jammer only needs internal status such size predictor needs + some alpha.
So we can compete them with applying predictor argv with upper bound of the states the cache exists, then, also we need to check in/output speed.

In theoretical, the jammer can always jam out us if jammer is latter one to predictor. So we absent this repository.

So if we have non infected computers or when we exclude all of the infection, we can re construct these programs (p0, p1, p2) with some advances. Otherwise, the jammer gains all of the result to make us exclude.

# Non analytical input
We suppose the one we input is analytical function delta sampled series.
Even invariants do so, because of randtools General Tips K, L.
We avoid small part of them by limiting invariant dimension, but utterly, we cannot in general.
So this often fails with some of the artificial created streams.
So with such case, we need to deal with some of the average on input.

# Tips around catgp.
A catgp treats input data as clustered parts combination on status length.
This permits some larger dimension invariants differed from the dimension cdot we apply in blur.
However, this also has trivial upper bounds as status length.

# The series {p0, p1, p2, p3} cannot predict:
We firstly suppose internal state size to predict some of the series.
In them, we make some of the linear inner product to predict.
So if input stream has the structure \<a,x\> with jamming a by internal states, they causes which is larger state length race.
So if we make the input stream as: \<\[PRNG(0), ..., PRNG(m)\], x\> with all of the history, to some point, we cannot predict them by our predictor.
We could use PRNG as sin(A*x)*B however, we should have the restriction to make return to average invariant by PRNGs.
So in the worst case, O(2^(internal state bit length)/((internal state bit length)^2)) steps the jammer can produce.

However, in the upper bound of the invariant complexity, even in such case, O(internal state bit length) can be the upper bound when we believe large dimension invariant works well. This is status and structure is veiled or unveiled on the stream race.
They causes: \<Ax,x\> each next stream causes randtools meaning \<a,x\>\*(x_1...x_n)^m or tan\<a,x\>, this causes which is larger race again.

# PRNG with seeded.
If we suppose initial entropy is on the input stream as extra small accuracy bits condition, we can suppose any of the PRNG who have finite states as 1-markov in first 2 steps.
Around them, we can make the continue of them as 2-markov, ..., n-markov with the same condition.
So first 2 step condition, 2^1^2 pattern as the upper bound of one program could make, so it floods with 2^2^2 order the original program could have without entropy theirselves.
We could say some of the labeling to such flooded program causes some of the language expression, however, we need to input each bit apply and applied by clear structure function theirselves.

# PRNG with first some small walk.
If we predict some first small walk when initialize PRNGs by some small bit number, they causes first some steps seems ok for statistics because all the state the predictor have includes the veiled seed data.
However, after some long steps passed, predict again with some small steps, we cannot unveil small bit number of seed they causes some start point description with small enough bit number, so they often fails.

# Touching input.
If original series is hard enough, the inverse walk condition nor delta inverse inverse walk condition might works.
This might because of same as p0 condition readme.md.
In p1, they might because of high frequency or low frequency continuous part causes some of the original calculation structure continuous condition hard.

# Concat PRNG
Bitwise xor causes original matrix addition.
This causes maximum of matrix size will be selected.
Smaller matrixes effects some of the result, but if the distribution
isn't harmful and has non small orthogonal parts norm,
they shouldn't harms.

# Recursive prediction
Doing thirds on the stream causes (f(x), x, status) elimination.
This is to make hypothesis () - structure itself is continuous.
However, we can make also (f(x)) elimination also causes continuous () structures.
There's differences between them the dimension original structure should have,
however, if the original prediction is fair enough on counting prediction structure, we can bet only 1 dim.

# P0DFT
P0DFT eliminates number of the hyper torus hole, this is not needed in P0maxRank sub class because they treats beter way them with semi-ordered field, also P1I, P012L because they treats any of the F_p register (non-)linear calculation.

# Bothside walk
We need bothside walk condition when a_-1 is being attacked condition.
Even so, if the attacker attacks both a_-1 and reverse(a_-1), half ot the prediction fails in best effort, but whole of the case, one of the function estimation remains, so in whole in long range, it's ok in feeding one by one sliding window meaning.

# PRNG first stage scattering
If we scatter first entropy with first prng call loop prng number count, they should small or no effect to the prediction theirselves because it has also same small entropy we append into the initializer.

Also, we can use prediction with some 2x step or so, so if the attacker can use all of the point the PRNG produce without slip, they could better to have some of the attack surfaces.

However, on the numerical calculation test, sliding some prediction (this can also have same meanings to scattering) often fails.
In their case, we should use larger and larger argv\[1\] for the prediction and larger and larger skip step if argv\[1\] is going to be huge ones.

# Simple controller
With predicting not one step after, especially two step after can controls the stream on the which is better condition if predictor is reliable enough.
However, the opposite controller can pretend as random step effect and both of them and us observes possible same point as same value, the behavior can be undefined, however, this also could concludes which has the larger internal states race even in this condition.

However, these are only from theoretical reason, so we don't test because they're harmful enough with our environment.

# The bothside controller condition
If there's controllers on the stream bothside and the both predictors' algorithm is open (or not), we need the condition for internal PRNG depend correct-fail better ratio on predictions. If the predictors doesn't worse sensitive on the internal PRNG ones, the jammer can jam out us easily.

So the best of our effort could be: to select better condition after the stream and the predictor often returns correct result better than failed result on some better ratio depends on internal PRNG.

So in ideal case, ./predictor argv\[1\] case, argv\[1\] : \[0,alpha\[ : returns almost correct prediction, argv\[1\] : \[alpha,beta\[ : returns non better prediction, which alpha:(beta-alpha) == 2:1 .
If ./predictor is deterministic, the jammer can jam out us, so argv\[1\] distribution is unknown in the best case depends on the state entropy internal PRNG have.

So internal PRNG state length is important for them.

Otherwise, if we code some of the best chosen algorithm for prediction and commit to open places, the otherside controller can controls us easily if there's no PRNG depend internal states on them.
Either, if we code normalize such PRNG depend codes, they only causes the jammer knowledge increases on the heuristics algorithm.

The pr4.cc is balanced as to depend expectation of probability based structure as to be unique on the stream and stable enough only. If we normalize them, the jammer can worse jam out us.

# Tips on jammer
Basically, our opposite jammer makes the PRNG on some of our predictors.

So if our predictor correctly reduces some of the heat on the stream, the jammer also outputs hot result they can cause return to the origin point can often works well.

However, the jammer also switches our predictor combinations, so all we can do them is for non hot result, predict some low number of ours and bet return to the origin point.

So stacking some of the predictor causes the jammer easily jam out us with some of the gulf on handle points.

Also, if we stack nor implement some another predictors, they only causes the jammer gains the result of ours. So we freeze p\*-series with this repository. Or, we need to do this on VMs but this isn't able to do for us because we're in watched (stucked) condition.

Also, the generic jammer often jam out us with changing target predictors range to range.

# Tips when being targetted
If some of the predictor(s) are being targetted and the computer resource they use can have better than the one we have, we cannot avoid them because some long and long range (hidden) internal states behaves as they're suddenly appears into the stream first look.

If our predictor is not only one predictor but some of the predictor series, the result often seems to have being oscillated concern with the predictors we have. This is from theoretical.

However, the result can be controlled to any if the jammer have any of our codes and states as to be mistaken the result switch case types.

# Tips on PRNGs
Tips on XXX means we can produce some of the PRNGs by separated time counter and separated algorithms.

This is to make them as: \[0,t\_0\[ : tan(A\_0\*\[s\_0,...,s\_t\_0\]), \[t\_0,t\_1\[ : tan(A\_1\*\[s\_0,...,s\_t\_0,...s\_t\_1\]), ... .

Also, to predict them, we suppose only no time counter and all of the internal state shuffle appears on the stream condition, we need the #{internal state bit} steps, however, if they hides some of the states from the stream condition, we need the 2\^#{internal state bit} steps to predict them.
So to produce some resilience, we need to hide some of the states from the output stream the PRNGs produces.

So the #{output accuracy \* step number} directly affects to the predictors.

# Tips on prediction sub jammer
We can jam out input of ourself as to be sign of the series randomized in predictors' meaning.
This can add some stability on prediction and getting better long range on prediction.
However, the jamming from original stream can hit the chain of the prediction fails even in this condition. So if we're targetted, either this cannot work well.

<strike>(However, we are doubting the integrity on inputs on our machines even this repository's history in special cases.)</strike> -&gt; The input/output integrity shouldn't be broken however PRNGs outputs some suspiciouses we can observe s.t. the distribution of outputs.

# Tips on progression
We predict with \{delta(d_k)\}, \{delta(delta(d_k))\}, ... . This results better stable result for us on plain hypothesises.

Also, Pprogression class feeds new states into the plain predictor as a new dimension of linear sum.

p\[012\]'s progression arguments takes the prime number multiplication to avoid some of the period depend jammers in first order.
So if there's multiple path of same period jammers on input stream, they fails.

# Another Download Sites (Closed)
* https://drive.google.com/drive/folders/1B71X1BMttL6yyi76REeOTNRrpopO8EAR?usp=sharing
* https://1drv.ms/u/s!AnqkwcwMjB_PaDIfXya_M3-aLXw?e=qzfKcU
* https://ja.osdn.net/users/bitsofcotton/

# Real close
2023/02/28
2023/03/09 bug fix after close #1.
2023/03/13 valid only short range bug fix after close #2.
2023/03/13 integrate all files into lieonn.hh after close #3.
2023/03/18 merge latest p0, after close #4.
2023/03/22 update README from osdn.net, after close #5.
2023/03/24 code clean, after close #6.
2023/03/31 persistent resistance to integer calculation jamming, after close #7.
2023/04/01 source code comment remedy from osdn.jp generic-p2 summary, after close #8.
2023/04/02 balance between jammer and predictor.
2023/04/03 merge.
2023/04/05 update readme.
2023/04/14 additional closed .cc files.
2023/04/21 make/revert ProgramInvariant algorithm change.
2023/05/18 single multiple single fix, so input y-axis ratio is the matter. also fix rand.cc for MAX_RAND range for knuth_b.
2023/05/18 cr.py rewrote to per single command.
2023/06/07 delete pfork.py, add pchain.sh, update readme.
2023/06/18 update readme, p.cc comment (no logic change), cr.py p command.
2023/06/24 fix to avoid observation matters.
2023/07/01 op2.py m command relative change, fix indent on p.cc.
2023/07/07 update readme.md, update comment in .cc files.
2023/07/08 delete rand.cc, cr.py r is enough to use. invariant causes +1. update readme, eliminate rand.cc, p.cc, comments are moved into readme. op2.py integrated into cr.py.
2023/08/02 update cr.py, readme, lieonn.hh P012L::next.
2023/09/20 update cr.py e command.
2023/09/25 some prng improvement test and update readme.
2023/10/26 update cr.py v command use with m command.
2023/10/30 copy structure reliably with randtools meaning.
2024/04/25 add tips on simple controller.
2024/04/29 add pr4.cc .
2024/04/30 add tips on bothside controller condition. brush up readme.md.
2024/05/05 add pr4c.cc update readme, pr4.cc .
2024/05/06 add tips on jammer, fix some of the readme. eliminate unused commands in cr.py. fix pr4.cc, integrate pr4c.cc into pr4.cc with definition. add tips when being targetted. BRUSH UP README.MD, so some of the description had be DELETED.
2024/05/07 fix XXX, add tips on PRNGs. really close.
2024/05/31 compile jammer.
2024/06/01 fix JAM, also our system is infected because of the test.
2024/06/02 fix readme, it's from p0.cc:_JAM mis spell.
2024/06/02 add cr.py j command, elim _JAM.
2024/06/14 fix cr.py l command, add cr.py 0, - command.
2024/06/15 add progression and readme.
2024/06/16 add progression \<0 argv.
2024/06/17 add readme, something goes well with some of the PRNGs with static, absent repository with this. also fix progression.
2024/06/19 merge latest lieonn.
2024/06/21 merge latest lieonn.
2024/06/21 add p2prng.cc, update readme, merge latest lieonn. INCLUDES command line argument change.
2024/06/22 update readme, p01 fatal fix. make/revert program invariants change friendly to predictors.
2024/06/23 large change around class instance initializer, also have progression short range fix.

