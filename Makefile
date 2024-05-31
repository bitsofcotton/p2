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
	@rm -rf catgp catgp32 catgpj catgpj32 pr4 pr4-32 pr4j pr4j32
all:	catgp catgp32 catgpj catgpj32 pr4 pr4-32 pr4j pr4j32
catgp:
	${CXX} ${CXXFLAGS} -static -o catgp catgp.cc
catgp32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o catgp32 catgp.cc
catgp64:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=64 -o catgp64 catgp.cc
catgpj:
	${CXX} ${CXXFLAGS} -static -D_JAM_ -o catgpj catgp.cc
catgpj32:
	${CXX} ${CXXFLAGS} -static -D_JAM_ -D_FLOAT_BITS_=32 -o catgpj32 catgp.cc
catgpj64:
	${CXX} ${CXXFLAGS} -static -D_JAM_ -D_FLOAT_BITS_=64 -o catgpj64 catgp.cc
pr4:
	${CXX} ${CXXFLAGS} -static -o pr4 pr4.cc
pr4-32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o pr4-32 pr4.cc
pr4-64:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=64 -o pr4-64 pr4.cc
pr4j:
	${CXX} ${CXXFLAGS} -static -D_JAM_ -o pr4j pr4.cc
pr4j32:
	${CXX} ${CXXFLAGS} -static -D_JAM_ -D_FLOAT_BITS_=32 -o pr4j32 pr4.cc
pr4j64:
	${CXX} ${CXXFLAGS} -static -D_JAM_ -D_FLOAT_BITS_=64 -o pr4j64 pr4.cc

