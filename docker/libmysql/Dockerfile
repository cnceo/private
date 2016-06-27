FROM buildpack-deps:xenial
#FROM docker_compiler
MAINTAINER Vic

ENV DATA /var/data

RUN apt-get -y update
RUN apt-get -y install libmysql++-dev
#libmysqlclient-dev

#RUN cp -rf /usr/include/mysql $(DATA)/thirdparts/include/
#RUN cp -rf /usr/lib/x86_64-linux-gnu/libmysqlclient* $(DATA)/thirdparts/libs/
