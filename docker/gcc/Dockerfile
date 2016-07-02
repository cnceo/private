FROM ubuntu:16.04
MAINTAINER Vic

ENV SRC=/var/data
WORKDIR $SRC/

# install gcc-6,g++6 from packages
ADD src/gcc/* $SRC/gcc/
ADD src/libssl/* $SRC/libssl/
ADD src/make/* $SRC/make/
ADD src/vi/* $SRC/vi/
RUN dpkg -i $SRC/gcc/*.deb \
	&& ln -s /usr/bin/gcc-6 /usr/bin/gcc \
	&& ln -s /usr/bin/g++-6 /usr/bin/g++

# install tools and libs
RUN dpkg -i $SRC/make/*.deb
RUN dpkg -i $SRC/vi/*.deb
RUN dpkg -i $SRC/libssl/*.deb
RUN rm -rf $SRC/*

# gcc installs .so files in /usr/local/lib64...
RUN echo '/usr/local/lib64' > /etc/ld.so.conf.d/local-lib64.conf \
	&& ldconfig -v

# ensure that alternatives are pointing to the new compiler and that old one is no longer used
#RUN set -x \
#	&& dpkg-divert --divert /usr/bin/gcc.orig --rename /usr/bin/gcc \
#	&& dpkg-divert --divert /usr/bin/g++.orig --rename /usr/bin/g++ \
#	&& update-alternatives --install /usr/bin/cc cc /usr/local/bin/gcc 999