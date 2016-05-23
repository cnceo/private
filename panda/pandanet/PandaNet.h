// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: PandaNet.h
 *Desc		: 
 *Version	: 1.0
 *Program	: Vic
 *Date		: 2016-4-25
 */
// --------------------------------------------------------
#ifndef _PandaNet_h_
#define _PandaNet_h_
// --------------------------------------------------------
class PANDA_API PandaNet{
public:
	static PandaNet& instance();

	void			initialize(const char* ini="panda.ini");
	keye::logger&	log();

	keye::ini_cfg_file	config;
private:
	std::shared_ptr<keye::logger>	spLogger;
	static PandaNet*				_instance;
};

#ifndef PDLOG
#define PDLOG PandaNet::instance().log()
#endif // !PDLOG

// --------------------------------------------------------
#endif // _PandaNet_h_
