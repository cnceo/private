#!/bin/bash

vm=vic

shopt -s expand_aliases
alias doma='docker-machine'
alias doco='docker-compose'

doma start $vm
eval "$(doma env $vm)"
