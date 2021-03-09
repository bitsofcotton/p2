CXX=	clang++
#CXX=	/usr/local/opt/llvm/bin/clang++
LD=	${CXX}

# compiler flags.
CXXFLAGS+=	-fopenmp -L/usr/local/lib -lomp
CXXFLAGS+=	-std=c++11 -Ofast -g0 -mtune=native
#CXXFLAGS+=	-std=c++11 -Ofast -gfull -mtune=native
#CXXFLAGS+=	-std=c++11 -O0 -gfull -mtune=native
#CXXFLAGS+=	-D_FLOAT_BITS_=64
LDFLAGS+=	-lc++
#LDFLAGS+=	-static

CLEANFILES= *.o *.dSYM p01

all:		p01
clean:
	@rm -rf ${CLEANFILES}

