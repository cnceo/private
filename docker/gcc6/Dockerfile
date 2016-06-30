FROM buildpack-deps:xenial
MAINTAINER Vic

ENV SRC=/var/src
ADD src/gcc-6.1.0.tar.bz2 $SRC/
WORKDIR $SRC/gcc-6.1.0

RUN ./contrib/download_prerequisites
RUN export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib:/usr/local/lib 
RUN mkdir build
WORKDIR $SRC/gcc-6.1.0/build
RUN ../configure --disable-checking --disable-multilib --enable-languages=c,c++ --prefix=/usr
RUN make -j 2
RUN make install
