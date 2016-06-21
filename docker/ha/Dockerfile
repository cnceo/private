FROM docker_develop
MAINTAINER Vic

ADD haproxy-1.6.5.tar.gz /var/src
ADD keepalived-1.2.22.tar.gz /var/src
ADD haproxy.cfg /etc/haproxy/haproxy.cfg

WORKDIR /var/src/haproxy-1.6.5
RUN ls
RUN make TARGET=generic
RUN make install

WORKDIR /var/src/keepalived-1.2.22
RUN ./configure
RUN make && make install
