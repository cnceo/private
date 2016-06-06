// --------------------------------------------------------
//
// --------------------------------------------------------
#ifndef _Panda_Item_h_
#define _Panda_Item_h_



class Item
{
public:
	size_t itemId;
	size_t itemDataId;
};
class PandaItem
{
public:
	void synItemInfo(keye::svc_handler& sh);
	void loadPlayerItem(size_t playerId);
	bool removeItem(size_t playerId, size_t itemId);
	bool removePlayerAllItem(size_t playerId);
	bool addItem(size_t playerId, Item* myItem);
	Item* createItem(size_t locItemId);
public:
	PandaItem();
	std::vector< Item*> getPlayItem(size_t playerId);
	Item* getItem(size_t playerId, size_t itemId);
private:
	size_t createGameItemId();
	// p1:playerId    p3:item
	std::map<size_t, std::vector<Item*> > m_playerItem;
	size_t gameItemId;
};
// --------------------------------------------------------
#endif // _DB_Manage_h_
