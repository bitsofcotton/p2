CXX=	clang++
#CXX=	eg++

# compiler flags.
CXXFLAGS+=	-std=c++11
CXXFLAGS+=	-I..
#CXXFLAGS+=	-fopenmp -I/usr/local/include -L/usr/local/lib -lomp
#CXXFLAGS+=	-pg
CXXFLAGS+=	-Ofast -mtune=native -gfull
#CXXFLAGS+=	-Oz -mtune=native -gfull
#CXXFLAGS+=	-O0 -mtune=native -gfull
#CXXFLAGS+=	-Ofast -mno-sse2 -mno-sse -mno-3dnow -mno-mmx -msoft-float -gfull -g0
LDFLAGS+=	-lc++
#LDFLAGS+=	-lestdc++

clean:
	@rm -rf catgp catgp32 pp3dft pp3dft32 p2prng p2prng32
all:	catgp catgp32 pp3dft pp3dft32 p2prng p2prng32
catgp:
	${CXX} ${CXXFLAGS} -static -o catgp catgp.cc
catgp32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o catgp32 catgp.cc
catgp64:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=64 -o catgp64 catgp.cc
pp3dft:
	${CXX} ${CXXFLAGS} -static -o pp3dft pp3dft.cc
pp3dft32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o pp3dft32 pp3dft.cc
p2prng:
	${CXX} ${CXXFLAGS} -static -o p2prng p2prng.cc
p2prng32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o p2prng32 p2prng.cc

