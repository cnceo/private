FROM ubuntu:16.04
MAINTAINER Vic

ENV SRC=/var/src
ADD src/* $SRC/
WORKDIR $SRC/

RUN dpkg -i *.deb
RUN cp /etc/apt/sources.list /etc/apt/sources.list.bak
RUN cp -rf $SRC/sources.list /etc/apt/sources.list
RUN apt-get update
RUN apt-get install gcc-6 g++6 vim make automake
RUN rm -rf $/SRC/*