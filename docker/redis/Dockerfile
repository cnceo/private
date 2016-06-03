FROM ubuntu:16.04
MAINTAINER Vic

RUN apt-get -y update
RUN apt-get -y upgrade
RUN apt-get -y install vim
RUN apt-get -y install redis-server
RUN apt-get -y install ruby ruby-dev

EXPOSE 443

RUN gem install redis
