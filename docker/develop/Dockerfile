FROM centos:7
MAINTAINER Vic

#ADD epel.repo /etc/yum.repos.d/epel.repo
#yum clean all && yum update

#ENV SRC /var/src
#VOLUME 

ADD src/boost_1_59_0.tar.gz /var/src
ADD src/redis-3.2.0.tar.gz /var/src
ADD src/mysql-5.7.13.tar.gz /var/src

RUN yum -y update
#RUN yum -y upgrade
RUN yum -y install vim git svn wget
RUN yum -y install automake autoconf libtool make cmake ncurses-devel
RUN yum -y install gcc gcc-c++
RUN yum -y install openssl-devel openssh-server

WORKDIR /var/src/boost_1_59_0
RUN ./bootstrap.sh
RUN ./b2 address-model=64 link=static variant=release --with-thread --with-date_time --with-regex --with-system

WORKDIR /var/src/redis-3.2.0
RUN make -j && make install

WORKDIR /var/src/mysql-5.7.13
RUN cmake . -DWITH_DEBUG=0 -DWITH_BOOST=/var/src/boost_1_59_0
#RUN make && make install
