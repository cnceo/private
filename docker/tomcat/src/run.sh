#!/bin/bash

export JAVA_HOME=/var/src/jdk
export PATH=$PATH:$JAVA_HOME

sh /var/src/tomcat/bin/catalina.sh run
