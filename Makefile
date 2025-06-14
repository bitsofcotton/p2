CXX=	clang++
#CXX=	eg++
#CXX=	c++

# compiler flags.
CXXFLAGS+=	-std=c++11
#CXXFLAGS+=	-std=gnu++98
CXXFLAGS+=	-I..
CXXFLAGS+=	-D_LIBCPP_ENABLE_ASSERTIONS
#MPFLAGS=	-fopenmp -I/usr/local/include -L/usr/local/lib -lomp
MPFLAGS=	-fopenmp -I/usr/local/include -L/usr/local/lib -lgomp
#CXXFLAGS+=	-pg
#CXXFLAGS+=	-O2 -g3
CXXFLAGS+=	-O2 -mtune=native -gfull
#CXXFLAGS+=	-Ofast -mtune=native -gfull
#CXXFLAGS+=	-Oz -mtune=native -gfull
#CXXFLAGS+=	-O0 -mtune=native -gfull
#CXXFLAGS+=	-Ofast -mno-sse2 -mno-sse -mno-3dnow -mno-mmx -msoft-float -gfull -g0
LDFLAGS+=	-lc++
#LDFLAGS+=	-lestdc++

# lieonn.hh flags
CXXFLAGS+=	-D_ARCFOUR_
CXXFLAGS+=	-D_GETENTROPY_

# N.B. sed -e s/static\ inline//g | sed -e s/inline//g
#CXXFLAGS+=	-D_OLDCPP_ -ftemplate-depth-99

clean:
	@rm -rf p2 p2-32 pp
all:	p2 p2-32 pp
p2:
	${CXX} ${CXXFLAGS} -static -o p2 p2.cc
p2-32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o p2-32 p2.cc
p:
	${CXX} ${CXXFLAGS} -static -D_ONEBINARY_ -o p p2.cc
p32:
	${CXX} ${CXXFLAGS} -static -D_ONEBINARY_ -D_FLOAT_BITS_=32 -o p32 p2.cc
pp:
	${CXX} ${CXXFLAGS} -static -D_ONEBINARY_ -D_FLOAT_BITS_=64 -D_PERSISTENT_ -o pp p2.cc

