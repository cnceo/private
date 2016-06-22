FROM ubuntu:16.04
MAINTAINER Vic

RUN apt-get -y update
RUN apt-get -y install vim wget
RUN apt-get -y install subversion

ENV SRC=/var/src
ADD src/* $SRC/
WORKDIR $SRC
RUN dpkg -i $SRC/*.deb

RUN apt-get -y install automake autoconf libtool make
RUN apt-get -y install openssl-devel openssh-server
RUN apt-get -y install gcc-5 g++-5 gdb

RUN apt-get -y install mysql-server
RUN apt-get -y install redis-server
RUN apt-get -y install ruby

WORKDIR $SRC/boost_1_59_0
RUN ./bootstrap.sh
RUN b2 address-model=64 link=static variant=release --with-thread --with-date_time --with-regex --with-system

