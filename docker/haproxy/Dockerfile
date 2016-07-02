FROM docker_gcc
MAINTAINER Vic

ADD src/haproxy-1.6.5.tar.gz /var/src
ADD src/keepalived-1.2.22.tar.gz /var/src
ADD haproxy.cfg /etc/haproxy/haproxy.cfg

#RUN apt-get -y --no-install-recommends install libssl-dev openssh-server

WORKDIR /var/src/haproxy-1.6.5
RUN ls
RUN make -j TARGET=generic
RUN make install

WORKDIR /var/src/keepalived-1.2.22
RUN ./configure
RUN make -j && make install

RUN rm -rf $SRC/*
