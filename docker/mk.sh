#!/bin/bash

vm=vic

alias doma='docker-machine'
alias doco='docker-compose'

docker-machine start $vm
eval "$(docker-machine env $vm)"

docker run -it -v /Users/vliu/Project/public:/var/src -v /Users/vliu/docker/data:/var/data buildpack-deps:xenial
