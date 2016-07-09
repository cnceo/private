FROM ubuntu:16.04
MAINTAINER Vic

ENV SRC /var/src

ADD src/apache-tomcat-9.0.0.M8.tar.gz $SRC
ADD src/jre-8u91-linux-x64.tar.gz $SRC
ADD src/run.sh $SRC

WORKDIR $SRC/
RUN mv apache-tomcat-9.0.0.M8 tomcat
RUN mv jre1.8.0_91 jdk
