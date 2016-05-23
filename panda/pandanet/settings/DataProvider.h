// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: DataProvider.h
 *Desc		: 
 *Version	: 1.0
 *Program	: Vic
 *Date		: 2016-4-25
 */
// --------------------------------------------------------
#ifndef _DataProvider_h_
#define _DataProvider_h_
// --------------------------------------------------------
class PANDA_API DataProvider{
#define DECL(var)	keye::csv_file var
#define LOAD(var)	var.load(#var".csv")
#define PRINT(var)	var.print()

public:
	void initialize();

	DECL(character);
	DECL(exp);
	DECL(dungeon);
	DECL(quest);
};
// --------------------------------------------------------
#endif // _DataProvider_h_
