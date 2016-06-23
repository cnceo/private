FROM docker_compiler
MAINTAINER Vic

ENV SRC /var/src

ADD src/boost_1_59_0.tar.gz $SRC
WORKDIR $SRC/boost_1_59_0
#RUN ./bootstrap.sh
#RUN ./b2 address-model=64 link=static variant=release --with-thread --with-date_time --with-regex --with-system

RUN apt-get -y update
RUN apt-get -y install libmysql++-dev redis-server
#libmysqlclient-dev
