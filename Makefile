CXX=	clang++
#CXX=	eg++

# compiler flags.
CXXFLAGS+=	-std=c++11
CXXFLAGS+=	-I..
#CXXFLAGS+=	-fopenmp -I/usr/local/include -L/usr/local/lib -lomp
#CXXFLAGS+=	-pg
#CXXFLAGS+=	-Ofast -mtune=native -gfull
CXXFLAGS+=	-Oz -mtune=native -gfull
#CXXFLAGS+=	-O0 -mtune=native -gfull
#CXXFLAGS+=	-Ofast -mno-sse2 -mno-sse -mno-3dnow -mno-mmx -msoft-float -gfull -g0
LDFLAGS+=	-lc++
#LDFLAGS+=	-lestdc++

clean:
	@rm -rf catgp catgp32
all:	catgp catgp32
catgp:
	${CXX} ${CXXFLAGS} -static -o catgp catgp.cc
catgp32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o catgp32 catgp.cc

