CXX=	clang++

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

clean:
	@rm -rf catgp catgp32 rand rand32 pr pr32
all:	catgp catgp32 rand rand32 pr pr32
catgp:
	${CXX} ${CXXFLAGS} -static -o catgp catgp.cc
catgp32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o catgp32 catgp.cc
rand:
	${CXX} ${CXXFLAGS} -static -o rand rand.cc
rand32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o rand32 rand.cc
p:
	${CXX} ${CXXFLAGS} -static -O0 -o p p.cc
p16:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=16 -o p16 p.cc
p32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o p32 p.cc
p64:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=64 -o p64 p.cc

