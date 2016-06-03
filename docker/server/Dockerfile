FROM ubuntu:16.04
MAINTAINER Vic

#RUN apt-get install software-properties-common
#RUN add-apt-repository ppa:ubuntu-toolchain-r/test
RUN apt-get -y update
RUN apt-get -y upgrade
RUN apt-get -y install gcc-5
RUN apt-get -y install g++-5

ADD src /var/src
