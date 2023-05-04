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
	@rm -rf catgp catgp32 rand rand32 p p32 pp pp32 prand prand32 pheavy pheavy32
all:	catgp catgp32 rand rand32 p p32 pp pp32 prand prand32 pheavy pheavy32
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
p32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o p32 p.cc
p64:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=64 -o p64 p.cc
p128:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=128 -o p128 p.cc
pp:
	${CXX} ${CXXFLAGS} -static -O0 -o pp pp.cc
pp32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o pp32 pp.cc
pp64:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=64 -o pp64 pp.cc
prand:
	${CXX} ${CXXFLAGS} -static -O0 -o prand pr.cc
prand32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o prand32 pr.cc
pheavy:
	${CXX} ${CXXFLAGS} -static -O0 -o pheavy pheavy.cc
pheavy32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o pheavy32 pheavy.cc

