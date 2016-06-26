FROM buildpack-deps:xenial
#FROM docker_compiler
MAINTAINER Vic

RUN apt-get -y update
RUN apt-get -y install libmysql++-dev
#RUN apt-get -y install redis-server
#libmysqlclient-dev

ENV SRC /var/src

ADD src/boost_1_59_0.tar.gz $SRC
WORKDIR $SRC/boost_1_59_0
RUN ./bootstrap.sh
RUN ./b2 address-model=64 variant=release --with-thread --with-date_time --with-regex --with-system install
#RUN ./b2 address-model=64 link=static variant=release --with-thread --with-date_time --with-regex --with-system install
RUN cp -rf /usr/local/include/boost/ /var/data/thirdparts/include/
RUN cp -rf /usr/local/lib/libboost_* /var/data/thirdparts/libs/
RUN cp -rf /usr/include/mysql /var/data/thirdparts/include/
RUN cp -rf /usr/lib/x86_64-linux-gnu/libmysqlclient* /var/data/thirdparts/libs/
