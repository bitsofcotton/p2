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
	@rm -rf catgp catgp32 pr4 pr4-32 pr4c pr4c-32
all:	catgp catgp32 pr4 pr4-32 pr4c pr4c-32
catgp:
	${CXX} ${CXXFLAGS} -static -o catgp catgp.cc
catgp32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o catgp32 catgp.cc
pr4:
	${CXX} ${CXXFLAGS} -static -o pr4 pr4.cc
pr4-32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o pr4-32 pr4.cc
pr4-64:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=64 -o pr4-64 pr4.cc
pr4c:
	${CXX} ${CXXFLAGS} -static -o pr4c pr4c.cc
pr4c-32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o pr4c-32 pr4c.cc
pr4c-64:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=64 -o pr4c-64 pr4c.cc

