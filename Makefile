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
	@rm -rf catgp catgp32 p2cr p2cr32 p2sg p2sg32
all:	catgp catgp32 p2cr p2cr32 p2sg p2sg32
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
p2cr:
	${CXX} ${CXXFLAGS} -static -o p2cr p2cr.cc
p2cr32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o p2cr32 p2cr.cc
p2sg:
	${CXX} ${CXXFLAGS} -static -o p2sg p2sg.cc
p2sg32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o p2sg32 p2sg.cc

