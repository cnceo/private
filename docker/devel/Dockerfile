FROM ubuntu:16.04
MAINTAINER Vic

RUN apt-get -y update
RUN apt-get -y install vim automake autoconf libtool make

ENV SRC=/var/src
ADD src/* $SRC/
WORKDIR $SRC
RUN dpkg -i $SRC/*.deb
RUN apt-get -y install gcc-5 g++-5 gdb
