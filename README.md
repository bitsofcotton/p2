# p2
Generic predictor corrector with random. This suppose the random stream we make is better than original random source and the one we made is a little predictable with some prediction method. If so, this slices a little amount of random entropy. This is because short length of original prediction method divides 3 parts, bet ok, bet ng, or no bet. So with blending no periodical datas, it flatten 33%, 33%, 33% of them idealy, but with a little predictable part, it shifts original to a little predictable parts. But in fact, this only changes sliding window distribution.

# How to use
Change p2.py getrand functions and pp subprocess initializer.

# Tips
If we use original better predictor with divice and conquer method like:
p0:=p(d_k), pp:=p(d_k + d_{k-1}), pm:=p(d_k - d_{k-1}),
and then concat them with p0 + pp + pm, it shouldn't works becacuse when pp != pm, ||(pp - pm)(d_k - d_{k-1})||
part increases constantly. And when we pick with 0 < pp * pm only, it makes cherry picking ones.
But with p0, the method can be used as recursive ones.
