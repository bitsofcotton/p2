CXX=	clang++
#CXX=	eg++

# compiler flags.
CXXFLAGS+=	-std=c++11
CXXFLAGS+=	-I..
CXXFLAGS+=	-D_LIBCPP_ENABLE_ASSERTIONS
MPFLAGS=	-fopenmp -I/usr/local/include -L/usr/local/lib -lomp
#MPFLAGS=	-fopenmp -I/usr/local/include -L/usr/local/lib -lgomp
#CXXFLAGS+=	-pg
CXXFLAGS+=	-O2 -mtune=native -gfull
#CXXFLAGS+=	-Ofast -mtune=native -gfull
#CXXFLAGS+=	-Oz -mtune=native -gfull
#CXXFLAGS+=	-O0 -mtune=native -gfull
#CXXFLAGS+=	-Ofast -mno-sse2 -mno-sse -mno-3dnow -mno-mmx -msoft-float -gfull -g0
LDFLAGS+=	-lc++
#LDFLAGS+=	-lestdc++

# lieonn.hh flags
CXXFLAGS+=	-D_ARCFOUR_

clean:
	@rm -rf catgp catgp32 p2prng p2prng32 p2prngb p2prngb32 p2 p2-32 p2nl p2nl32 p2qt p2qt32
all:	catgp catgp32 p2prng p2prng32 p2prngb p2prngb32 p2 p2-32 p2nl p2nl32 p2qt p2qt32
catgp:
	${CXX} ${CXXFLAGS} -static -o catgp catgp.cc
catgp32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o catgp32 catgp.cc
catgp64:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=64 -o catgp64 catgp.cc
catgpc:
	${CXX} ${CXXFLAGS} -static -D_CHAIN_ -o catgpc catgp.cc
catgpc32:
	${CXX} ${CXXFLAGS} -static -D_CHAIN_ -D_FLOAT_BITS_=32 -o catgpc32 catgp.cc
p2prng:
	${CXX} ${CXXFLAGS} -static -o p2prng p2prng.cc
p2prng32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o p2prng32 p2prng.cc
p2prngb:
	${CXX} ${CXXFLAGS} -static -D_BIT_ -o p2prngb p2prng.cc
p2prngb32:
	${CXX} ${CXXFLAGS} -static -D_BIT_ -D_FLOAT_BITS_=32 -o p2prngb32 p2prng.cc
p2nl:
	${CXX} ${CXXFLAGS} -static -D_NONLINEAR_X_ -o p2nl p2.cc
p2nl32:
	${CXX} ${CXXFLAGS} -static -D_NONLINEAR_X_ -D_FLOAT_BITS_=32 -o p2nl32 p2.cc
p2:
	${CXX} ${CXXFLAGS} -static -o p2 p2.cc
p2-32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o p2-32 p2.cc
p2qt:
	${CXX} ${CXXFLAGS} -static -o p2qt p2qt.cc
p2qt32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o p2qt32 p2qt.cc
# XXX: crashes (around mem region operation?)
p2qtmp:
	${CXX} ${CXXFLAGS} ${MPFLAGS} -o p2qtmp p2qt.cc
p2qt32mp:
	${CXX} ${CXXFLAGS} ${MPFLAGS} -D_FLOAT_BITS_=32 -o p2qt32mp p2qt.cc

