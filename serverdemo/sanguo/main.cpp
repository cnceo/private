#include "stdafx.h"

#include "game/fwd.h"

int main(int argc,char* argv[]){
	int ret=Game::instance()->run(argc,argv);
	return ret;
}
