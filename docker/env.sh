vm=vic

alias doma='docker-machine'
alias doco='docker-compose'

docker-machine start $vm
eval "$(docker-machine env $vm)"
