FROM buildpack-deps:xenial
#FROM docker_compiler
MAINTAINER Vic

ENV SRC /var/src
ENV DATA /var/data

ADD src/boost_1_59_0.tar.gz $SRC
WORKDIR $SRC/boost_1_59_0
RUN ./bootstrap.sh
RUN ./b2 address-model=64 variant=release --with-thread --with-date_time --with-regex --with-system install
#RUN ./b2 address-model=64 link=static variant=release --with-thread --with-date_time --with-regex --with-system install
#RUN cp -rf /usr/local/include/boost/ $(DATA)/thirdparts/include/
#RUN cp -rf /usr/local/lib/libboost_* $(DATA)/thirdparts/libs/
