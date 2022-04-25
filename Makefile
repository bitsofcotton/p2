CXX=	clang++

# compiler flags.
CXXFLAGS+=	-std=c++11
#CXXFLAGS+=	-fopenmp -I/usr/local/include -L/usr/local/lib -lomp
#CXXFLAGS+=	-pg
#CXXFLAGS+=	-Ofast -mtune=native -gfull
CXXFLAGS+=	-Oz -mtune=native -gfull
#CXXFLAGS+=	-Ofast -mno-sse2 -mno-sse -mno-3dnow -mno-mmx -msoft-float -gfull -g0
LDFLAGS+=	-lc++

clean:
	@rm -rf catgp catgp32 rand
all:	catgp catgp32 rand
catgp:
	${CXX} ${CXXFLAGS} -static -o catgp catgp.cc
catgp32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o catgp32 catgp.cc
catgp64:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=64 -o catgp64 catgp.cc
catgp128:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=128 -o catgp128 catgp.cc
rand:
	${CXX} ${CXXFLAGS} -static -o rand rand.cc
rand32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o rand32 rand.cc
