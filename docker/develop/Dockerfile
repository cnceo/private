FROM centos:7
MAINTAINER Vic

#ADD epel.repo /etc/yum.repos.d/epel.repo
#yum clean all && yum update

ADD redis-3.2.0.tar.gz /var/src
#ADD boost_1_59_0.tar.gz /var/src

RUN yum -y update
#RUN yum -y upgrade
RUN yum -y install vim git svn
RUN yum -y install automake autoconf libtool make
RUN yum -y install gcc gcc-c++
RUN yum -y install openssl-devel openssh-server

WORKDIR /var/src/redis-3.2.0
make && make install

#WORKDIR /var/src/boost_1_59_0
#RUN ./bootstrap.sh
#RUN b2 --help
#RUN b2 address-model=64 link=static variant=release --with-thread --with-date_time --with-regex --with-system

