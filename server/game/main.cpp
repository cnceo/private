#include <string>
#include <memory>
#include <gamelib.h>
#include <autobot.h>

int main(int argc,char* argv[]){
	GameLib game;
	game.run(argc,argv);

	bool server_only=false;
	if(!server_only){
		Autobot robot;
		robot.run(argc,argv);
		robot.stop();
	}else{
		printf("press x to exit.\n");
		bool exit=false;
		while(!exit||!game.stopped())
		switch(std::getchar()){
		case 'x':
			game.stop();
			exit=true;
			break;
		}
	}
	return 0;
}
