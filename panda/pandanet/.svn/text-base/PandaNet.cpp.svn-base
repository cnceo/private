// test_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "pandanet_fwd.h"

using namespace keye;

void PandaNet::initialize(const char* ini){
	if(ini)config.load(ini);
}

keye::logger& PandaNet::log(){
	const char* logFile=nullptr;
	if(!spLogger)spLogger.reset(new logger(logFile));
	return *spLogger;
}

PandaNet* PandaNet::_instance=nullptr;
PandaNet& PandaNet::instance(){
	if(!_instance)_instance=new PandaNet;
	return *_instance;
}
