FROM ubuntu:16.04
MAINTAINER Vic

# install gcc-6,g++6 from packages
ENV SRC=/var/src
ADD src/* $SRC/
WORKDIR $SRC/
RUN dpkg -i *.deb \
	&& rm -rf *.deb \
	&& ln -s /usr/bin/gcc-6 /usr/bin/gcc \
	&& ln -s /usr/bin/g++-6 /usr/bin/g++

# install tools and libs
WORKDIR $SRC/
RUN cp /etc/apt/sources.list /etc/apt/sources.list.bak \
	&& cp sources.list /etc/apt/sources.list \
	&& buildDeps='vim autoconf libtool automake make gdb libssl-dev' \
	&& set -x \
	&& apt-get update && apt-get install -y $buildDeps --fix-missing --no-install-recommends \
	&& rm -r /var/lib/apt/lists/* \
	&& apt-get purge -y --auto-remove $buildDeps

# gcc installs .so files in /usr/local/lib64...
#RUN echo '/usr/local/lib64' > /etc/ld.so.conf.d/local-lib64.conf \
#	&& ldconfig -v

# ensure that alternatives are pointing to the new compiler and that old one is no longer used
#RUN set -x \
#	&& dpkg-divert --divert /usr/bin/gcc.orig --rename /usr/bin/gcc \
#	&& dpkg-divert --divert /usr/bin/g++.orig --rename /usr/bin/g++ \
#	&& update-alternatives --install /usr/bin/cc cc /usr/local/bin/gcc 999