

#include "stdafx.h"
#include "ZoneServerFwd.h"
#include "PandaItem.h"
using namespace proto3;

PandaItem::PandaItem()
{
	gameItemId = 0;
}
void PandaItem::loadPlayerItem(size_t playerId)
{
	Item* itm2 = createItem(1);
	Item* itm = createItem(2);
	Item* itm3 = createItem(3);
	Item* itm4 = createItem(3);
	std::vector<Item*> items;
	items.push_back(itm);
	items.push_back(itm2);
	items.push_back(itm3);
	items.push_back(itm4);

	m_playerItem.insert(std::make_pair(playerId, items));
}
void PandaItem::synItemInfo(keye::svc_handler& sh)
{
	auto& pi = Server::instance->clientService.find(sh.id())->player;
	std::vector<Item*> items = getPlayItem(pi.id());
	game_itemInfos nitemInfos;
	nitemInfos.set_mid(eMsg::MSG_ZC_SYN_ITEM);
	for (auto ite : items)
	{
		game_ItemInfo msg;
		msg.set_itemid(ite->itemId);
		msg.set_itemdataid(ite->itemDataId);
		*nitemInfos.add_iteminfos() = msg;
	}

	PBHelper::Send(sh, nitemInfos);
}
bool PandaItem::removeItem(size_t playerId, size_t itemId)
{
	std::map<size_t, std::vector< Item*> >::iterator it = m_playerItem.find(playerId);
	if (it != m_playerItem.end())
	{
		auto ItemIt = it->second.begin();
		while (ItemIt != it->second.end())
		{
			if ((*ItemIt)->itemId == itemId)
			{
				delete (*ItemIt);
				it->second.erase(ItemIt);
				return true;
			}
		}
	}
	return false;
}
bool PandaItem::addItem(size_t playerId, Item* myItem)
{
	auto it = m_playerItem.find(playerId);
	if (it != m_playerItem.end())
	{
		it->second.push_back(myItem);
		return true;
	}
	else
	{
		std::vector<Item*> items;
		items.push_back(myItem);
		m_playerItem.insert(make_pair(playerId, items));
		return true;
	}
	return false;
}
Item* PandaItem::createItem(size_t locItemId)
{
	Item* itm = new Item;
	itm->itemDataId = locItemId;
	itm->itemId = createGameItemId();
	return itm;
}
std::vector< Item*> PandaItem::getPlayItem(size_t playerId)
{
	std::vector< Item*> items;
	std::map<size_t, std::vector< Item*> >::iterator it = m_playerItem.find(playerId);
	if (it != m_playerItem.end())
	{
		return it->second;
	}
	return items;
}

Item* PandaItem::getItem(size_t playerId, size_t itemId)
{
	std::map<size_t, std::vector< Item*> >::iterator it = m_playerItem.find(playerId);
	if (it != m_playerItem.end())
	{

		for (Item* ite : it->second)
		{
			if (ite->itemId == itemId)
			{
				return ite;
			}
		}
	}
	return nullptr;
}
bool PandaItem::removePlayerAllItem(size_t playerId)
{
	auto it = m_playerItem.find(playerId);
	if (it != m_playerItem.end())
	{
		while (it->second.size() != 0)
		{
			delete it->second[it->second.size()-1];
			it->second.pop_back();
		}
		m_playerItem.erase(it);
		return true;
	}
	return false;
}
size_t  PandaItem::createGameItemId()
{
	return gameItemId += 1;
}