FROM ubuntu:16.04
MAINTAINER Vic

RUN apt-get -y update

ENV SRC=/var/src
ADD src/* $SRC/
WORKDIR $SRC
RUN dpkg -i $SRC/*.deb

#RUN apt-get -y --fix-missing --no-install-recommends install make
RUN apt-get -y --fix-missing --no-install-recommends install gcc g++ gdb
RUN apt-get -y --fix-missing --no-install-recommends install vim autoconf libtool automake
