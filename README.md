# ddpmopt
Apply some of the filter to input stream.
We can use this for bitsofcotton/i2g filtered images.

N.B. we use only input data streams, so this repository doesn't use external models.

# Context
There exists Denoising Diffusion Probabilistic Models (DDPM; Ho et al. 2020). So this is another try on them but different flavoured one, we only focus to apply each pixel context to color image into monochrome one, which have the structure completely depends on filters' multiple meaning or complexity.

# Tips on malloc options
We need to do ulimit or edit /etc/login.conf for large malloc use cases required by larger than medium sized input.

Using this with mimalloc or so can increase memory usage with multi thread on some systems.

We use at least 2\*((whole input size))\*sizeof(num_t) in heap resource.

# Tips around c++ compilers
Some of the lieonn.hh operator \>\> class doesn't work as expected, might be compilers' bug.

Either, we might be in invariant prediction catched as getting to be invariant result controlled condition.

# Tips on prediction on objected images
We suppose the input image series as some of the functions to effect to or data to be effected by paired images also the pixel contexts in F\_p.
However, instead of using F_2, we need P01 base dimension larger than 4 in such case in fact.
After then, we adjust omitted:in/output ratio on F_2 case. We might need this because only single layered learning needs some of the better reasons to calculate in such algorithms.

# Tips on multiple layers prediction
The plain \[pq\]redg predictor uses first order shallow copying structures but it's saturated by in/output, 3 predictor uses 2nd order enough bits for predictions, 6 predictor is enough for multiple layer algebraic copying structure, 9 predictor is enough for algorithm decomposition including inverse of them, usually they're equivalent to plain predictors from surface looking.

So n-predictor is useful when the problem needs some of the internal bit-wise structure is worse complex case they needs very large accuracy depends on input dimension number, stacking predictor reduces them.

# Tips on prediction base dimensions
Something sparse with jammer input stream effects base dimension we select needs larger dimensions on the base, this condition is defined there's no unique pure functions on the stream the variables dimension they have.
This condition can be eliminated with in/output (de)?compression this condition ask shirks the result of algorithms to some of the upper cardinals with compressing sparsity into dense ones on somewhere usually we should have to increase the base dimensions with or without bitsofcotton/masp from entropy reason.

Usually, the condition larger than 4 dimension is come from some of the jammer like inputs nor brand new data feed input by input stream.
However, we predict the stream with them and continuity after them in pqredg.
So this effects if input stream is enough dense in another words stream is stable for input entropy one by one meaning, the result is reasonable in the continuity meaning.

Some of the PRNG tests causes this valid but there's something new parameters on entropy feeding ratio, they fails with gulfs depends on the range we use in the range.
In some auto tune entropy feeding, we can do goki_check_cc:test.py:qred command or predv nrecur template specification.

# Tips on contexts
We use whole image context to insert context then predict with such each pixel context. So each image consistency is used and applied for the output.

We can use orthogonal context either DFT context insertion, however, this isn't matches our senses, such things are useful to get numerical stability context only and are viewed broken by our senses. This might be because of even 2/3 prediction we have condition, the noise the result have can causes whole graphics spreaded result.

Either we're using goki_check_cc:test.py:qred... commands or monte-carlo methods in lieonn.hh:predv template parameter to complement entropy continuity, we don't need them with some of the slice we gain.

We can use some feature quantity based transforms we can get them by machine learning converted into tan Ax form.
In such case, we use vectorized input image x, y:=tan Ax for feature quantities, weight them by \[x, y\] or only predict the {y} stream, then, invert x=f(y).
This matches our senses on viewing the image.

We can use bitsofcotton/masp detecting such feature quantities.
However, this isn't unveil deep structure they behaves to be operatable in the picture set by itself.
So we need to do bitsofcotton/isolate and match to known algorithms with the handle parameters we want to operate.

Also, we want to decompose some of the meanings by bitsofcotton/specific and backport them into here, however, implementation of them isn't now.

The pred command (curdir)w...-bit.ppm output is omitter on shortcut for decomposing and apply to the predictions, this might includes specific -&gt; {y} prediction -&gt; reverse chain by finding some of the patterns but they doesn't have handles what information to omit for predictions.

Also, these predictors doesn't handle what meaning to omit on next image, so is composition around collection of predictions.

The goki_check_cc:test.py:\[pq\]red\+\+ command shrink image into reasonable parameters on surface condition they includes some omitting meanings.
We looked some of the graphics set result, they might be what we wanted to get but not the actually one but ok for us, so we close this repository with this condition.

We get pPqQ command to get 4 of the candidates from original stream or PRNG mixed stream.
If we're lucky, one of the candidates can be used for next predicted images.
However, PQ command returns pseudo next one they doesn't be added delta start point in another words offset, however we select this method because of output glance.
Either, in the invariant controlled condition in any of the inputs, outputting 4 of the candidates should work well, however, we only calculate a paired candidates at once, so 3 of candidates are upper bound of pPqQ output, this is enough in because of representation of combination of binary tree condition.

# T command
We have T command for gokibin bit preprocessed graphics stream testing.
If output is better than .5 probability and stable for some of the shrinked size, the gokibin bit reversed outputs' shrinked image can have some of the meanings for them.

Either, T command uses raw predictions but it can be being attacked, so \[pPqQw\] command outputs uses second one if the condition is true but we need at least 4 of them.

# Infection
We're in prediction result controlled condition, so we don't get actual output images to confirm result, so we need to implement this repository only with the hypothesis we firstly have and their implementation is correct or not one.

Since bitsofcotton/p2 result seems their internal-states-rich 3-way output is correct but we don't have their strategy because we only target the graphics stream they have non shrinked or non regression stories.

Even so, we should have the counter measure to result is controlled condition, however we have T command output, so we applied them into second one outputs, so we close with this.

However, if we find some of the bug on the hypothesis and implementation is differ, we return and fix here.

# Usage:
    # copy color structure
    ./ddpmopt(32|64)?(mp)? + <in0out.pgm> <in0in.ppm> ... > cache.txt
    # apply color structure
    ./ddpmopt(32|64)?(mp)? - <in0.ppm> ... < cache.txt
    # predict following image (each bit input)
    ./ddpmopt(32|64)?(mp)? \[pP\] <in0.ppm> ...
    # predict with whole pixel context (each bit input)
    ./ddpmopt(32|64)?(mp)? w <in0.ppm> <in0-4.ppm> ...
    # predict down scanlines. (each bit input)
    ./ddpmopt(32|64)?(mp)? \[qQ\] <in0out.ppm> ...
    # show continuity
    ./ddpmopt(32|64)?(mp)? [xyit] <in0.ppm> ...
    # some of the volume curvature like transform
    ./ddpmopt(32|64)?(mp)? c <in0.ppm> ...
    # test input series of graphics predictable or not (each bit input)
    ./ddpmopt(32|64)?(mp)? T <in0.ppm> ...
    cp `./ddpmopt(32|64)?(mp)? i <in0.ppm> ... | sort | head -n ... | tr '\n' ' '` outdir

# Re5-Leave
We might re5-leave this repository with this update except for lieonn.hh updates.

Leave here but might return here after another implementations.

# Real close
2023/03/01
2023/03/09 bug fix after close #1.
2023/03/13 bug fix after close #2.
2023/03/13 integrate all files into lieonn.hh after close #3.
2023/03/18 merge latest p0, after close #4.
2023/03/20 qred makes only row-direction prediction, after close #5.
2023/03/24 ddpmopt.cc +0 00 -0 command fix, code clean, after close #6.
2023/03/29 merge p0 pnext, after close #7.
2023/03/31 persistent prediction to get average 1/2 * 2/3 pixels.
2023/04/02 merge p2 result.
2023/04/03 better simple predv.
2023/04/04 update readme.
2023/04/05 fix makeProgramInvariant scale accuracy stability.
2023/04/19 add topt.cc.
2023/04/21 shape up around makeProgramInvariant/revertProgramInvariant, algorithm changed.
2023/04/23 qredg.cc prediction/original norm fix.
2023/05/18 predv function change to better analytical, update README.md.
2023/06/08 predv normalization fix.
2023/06/11 topt.cc output normalization fix. update readme.
2023/06/13 update readme. ddpmopt.cc large change.
2023/06/14 ddpmopt.cc fix now works, update readme.
2023/06/15 update readme, some fixes around predg, qredg, ddpmopt.
2023/06/24 fix qredg.cc autoLevel in lieonn.
2023/06/27 ddpmopt.cc sz 3 to 2 change, update readme.
2023/07/07 [pq]redg predict along with middle image/line.
2023/07/08 invariant causes +1. qredg.cc fix crash.
2023/07/12 update readme.
2023/08/02 update topt, lieonn as crush to the last.
2023/08/03 topt, ddpmopt fix on apply. update readme.
2023/08/04 update readme. fix predv result norm.
2023/08/26 ddpmopt - option calculation change, update readme. update [pq]redg for recursive ones to beat with geometric average limit.
2023/09/04 auto configure predg/qredg param, conservative.
2023/09/11 auto configure predg/qredg size, aggressive ga param.
2023/09/12 fix last broken predv func and qredg.cc.
2023/09/13 change ddpmopt retry and retry on geometric average.
2023/09/19 autogamma after doing predg. update readme.
2023/09/19 predvResizeMat resize size fix to most reasonable one.
2023/09/22 ddpmopt change not to use crush but with linearInvariant.
2023/09/24 fix last up, don't know why they worked well without crash on last debug.
2023/09/25 change output size strategy, not using resize, preferring complement to predict.
2023/10/03 update readme.
2023/10/05 update readme, should close except for some of the ddpmopt for pairs of the images.
2023/10/18 update readme.
2023/10/19 mipmap impl, update readme.
2023/10/20 revert, mipmap doesn't work well.
2023/10/22 instead of complement trace of input, we should do shrink after output is done. This is from some of the numerical tests, so whole image orthogonality isn't matter even when input data is small enough, instead of them, we try to vanish some prediction errors with geometric mean.
2023/10/23 ddpmopt strategy algorithm in/output large change.
2023/10/26 update readme.
2023/10/27 update readme. close.
2023/10/30 copy structure reliably with randtools meaning.
2023/11/13 update readme.
2023/11/19 revert each line complement condition, force to use complement.
2023/11/20 only complement with 2, they smoothes output enough with our measure (&gt; 2/3).
2023/11/21 update readme.
2023/11/23 fix known tips, there was at most double error.
2023/11/25 implement and revert the test to complement before to revertProgramInvariant, they doesn't improve well differed to shrinking.
2023/12/06 fix ddpmopt.cc as makeProgramInvariant, revertProgramInvariant to better compatible with [0,1].
2023/12/07 fix ddpmopt.cc makeProgramInvariant double apply serious bug in crush. Also, update readme as compatible with in/output. realclose.
2023/12/15 use the tactics not to apply twice make/revertProgramInvariant on prediction, the invariant is already taken, however, this can causes P^t 1 == 0 condition on linearInvariant, we don't fix them.
2024/03/19 half p8 compatible change on prediction P1I to P01 with predg... qredg... binary.
2024/04/02 fix P01, vanish predvc.
2024/04/04 only use large accuracy on calculating pnextcache, but this is broken with cache naming.
2024/04/07 rgb2xyz, xyz2rgb on first/last of predg/qredg if color is 3ch.
2024/04/09 fix maeProgramInvariant x_k==0 to wrap into x_k:=1, refix pnext with lower digits.
2024/04/10 we count the function entropy enough beat with in/output on [pq]redg.
2024/04/12 update readme.
2024/04/14 take a median after predv before revertProgramInvariant.
2024/04/15 update readme, it is the specification of this some output to be broken.
2024/04/17 update readme.
2024/04/18 add tcont.cc, real close with omake.
2024/04/18 won't update without lieonn.hh change.
2024/04/29 update readme.
2024/05/05 p01 class fix step-step to 1-step correction.
2024/05/07 correct output depth limit to have a meaning. update readme.
2024/06/01 add predg0... qredg0... compile option, these using latest results on \{p0,p1,p2\}.
2024/06/02 revert. it's nonsense.
2024/06/05 fix p01 crash in rare cases.
2024/06/07 fix number of predictions to reasonable one. add another implementation on python predg.cc, only QR decomposition is differ but this has a better results?? update readme.
2024/06/09 factorize into each bit and predict with them. leave with this but this have color intensity == {0,1} confusion bug.
2024/06/09 fix last bug. average step skips. add readme.
2024/06/11 update readme.
2024/06/12 update readme.
2024/06/13 update readme.
2024/06/14 update readme.
2024/06/15 conclude 2024/06/11-2024/06/14 conditions readme.
2024/06/16 revert P210 to original, then, P01, P0 pred temporarily, update readme.
2024/06/17 merge p2 logic with p10 class.
2024/06/18 code cleaning, update readme.
2024/06/18 speed remedy.
2024/06/19 add restriction for getting average on PprogressionOnce010n.
2024/06/20 our machine is infected, take a most logically valid in our program predictions.
2024/06/21 fix fatal error on PprogressionOnce::next, they doesn't use predictors.
2024/06/21 revert and brush up, add fiocursed.cc series, brush readme.
2024/06/22 update readme, updates around pprogression causes only 1 step after/before prediction.
2024/06/22 p01 fatal fix. make/revert program invariant change friendly to predictions.
2024/06/23 large change around class instance initializer, also have progression short range fix.
2024/06/23 fatal fix around last update.
2024/06/24 fatal fix around last update, rotate predMat sloppy case.
2024/06/26 some of the assertion fix, update readme.
2024/06/26 update readme, fix around Ppersistent buf.full condition.
2024/06/27 fix predv last norm condition calculations. predMat bugs might be fixed.
2024/06/29 update readme and comments.
2024/06/30 re-insert periods with better stable method. update readme.
2024/07/06 Ppersistent now use maximum length for predictions. Also readme update.
2024/07/07 code cleaning. merge Pprogression improve but no affects.
2024/07/08 internal state range strategy change, use all of the input to reduce. update readme.
2024/07/09 revert bitwise prediction causes whole image invariant works same as theoretical ones, however, each pixel context isn't enough on prediction but is enough on whole image condition information amount as better weighted. update readme.
2024/07/10 revert [pq]redg.cc as no each bit condition, instead of this, use goki_check_cc:test.py:bit command.
2024/07/20 update readme, might our system is infected.
2024/08/18 update -\[369\] predictors for recursive but equivalent.
2024/09/03 update \[pq\]redg...p.. for auto tuned recursive but for tiny images.
2024/09/04 update last up with proper recursive value.
2024/09/05 omit error output in zeroFix.
2024/09/06 update and fix readme.
2024/09/09 merge p1/pp3.cc result, change only output forward pred ones.
2024/09/10 merge p1/pp3.cc result, re-re-leave.
2024/09/10 fix pnoise meaning. update readme, re-re-re-leave.
2024/09/12 update readme. leave.
2024/09/22 append dft hack, add readme, releave.
2024/09/23 fix _PREDV_==3 _PREDV_DFT_ case unit value. Changed preddg... to predfg... to make some readability. Fix around comments and readme.md.
2024/09/24 brush up, eliminate exhaust of the resource to get tiny output improve in finite and up to aleph_0 condition.
2024/09/25 elim dead code, update readme. leave.
2024/09/26 improve heap resource efficiency.
2024/09/27 refactoring predv, predvp0. the target stream we predict is now concrete, so PP0 type changed.
2024/09/28 add step after predictions.
2024/09/29 update readme. leave the repository really.
2024/10/05 add predga.cc and compile option.
2024/10/26 fix predvall meaning after p2/README.md:Tips on reseed.
2024/10/31 add predgs.cc.
2024/11/01 fix last predgs.cc index map, update readme, accuracy is not enough for SVD.
2024/11/02 update readme. elim predgs.cc, predga.cc.
2024/11/03 update readme. rerere-leave here. predg.cc a cmd list up fix.
2024/11/12 delete tips on reseeding, reseeding is not so harder. replaced flip, flop template function in lieonn suitable with gcc however 128bit long double isn't compile on our main pc environment.
2024/11/14 integreate all commands on this repository into ddpmopt.cc but the binary is very fat.
2024/11/17 add w command.
2024/11/19 improved lieonn.hh:taylor command speed and accuracy this causes q command better works. update readme. something error occured first upload of this change on github.com. this change leads us to pnext r variable doubles.
2024/11/20 update readme for recent knowns.
2024/11/20 update readme.
2024/11/30 add c command. update readme.
2024/12/02 taylor improvement, taylor function reclose with this.
2024/12/03 w command fix also readme.md update.
2024/12/04 fix w command output, backward had a glitch, so eliminated. update readme.
2024/12/05 backport p1 | p0 results, brush up code, replace [0a] command to p command, update readme.
2024/12/07 c command fix.
2024/12/09 changed to output only a single prediction. w command crash fix, memory efficiency improve. q command crash fix.
2024/12/11 fix readme w command usage.
2024/12/13 leave here, might return here.
2024/12/26 use montecarlo method instead of doing each step average on prediction.
2024/12/28 fix 'q', 'w' commands with last change.
2024/12/29 update 'w' commands suitable with predv1 method impementation is predv4.
2024/12/30 update readme.
2025/01/06 eliminate condorcet's jury method, they've no effects.
2025/01/06 update readme for compatible with latest goki_check_cc.
2025/01/27 improve pred... memory usage without predv4.
2025/02/01 fix readme memory usage notation.
2025/02/05 predv function to get better prediction - real value distribution by PRNG tests.
2025/02/15 add PP0 as PSVD ... as a dead code, they doesn't improve output enough on our machines with small number of inputs.
2025/02/16 fix predv4 alignments affects all of outputs w command.
2025/02/18 revert using predvp0 to using predv, they might come from infection.
2025/02/20 move include comments into lieonn.hh . update reamde.md fix meaning on predictions we will re freeze with this.
2025/02/22 not optimal but better looking q command output size with specifying step to predictor.
2025/02/23 add readme.md notes.
2025/03/01 add readme.md note around DFT.
2025/03/03 add T command for test. revert subtraction to multiplication and sgn method to have gokibin bit preprocessed inputs.
2025/03/04 apply T command tests into original p, w, q command. either revert to original p, w, q commands with renewing T command test.
2025/03/05 our invariant condition is being attacked, we use 2 of dimension output but in fact we need at least 4 dimension output for all.
2025/03/06 yellow output is lead by small input number, also some readme fix we often don't need entropy feeding control.
2025/03/09 brush up lieonn.hh phase periodical jamming matters. we only make hypothesis PRNG we use isn't match the predictor/original stream phase period they have.
2025/03/11 add and fix readme. close.
2025/03/12 brush up readme, freeze.
2025/03/13 add PQ command, update readme around 4 of candidate results.
2025/03/22 close with this Readme.md.
2025/04/01 add readme.md because we're in infected condition, also close because of the condition.
2025/04/17 auto tune dimension in F_2 case other than 4 dimension to target.
2025/04/18 qQ command strategy change.

