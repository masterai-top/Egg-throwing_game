#include "ExchangeDataManager.h"
#include "GameConfig.h"
#include "MainScene.h"
#include "cocos-ext.h"
#include "GameSaveData.h"
//using namespace CSJson;

USING_NS_CC;
using namespace std;

ExchangeDataManager* ExchangeDataManager::instance = NULL;

ExchangeDataManager::ExchangeDataManager()
{

}

ExchangeDataManager::~ExchangeDataManager()
{
	clearCashData();
}

ExchangeDataManager* ExchangeDataManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new ExchangeDataManager();
	}
	return instance;
}

std::map<char, std::vector<ItemData*>*> * ExchangeDataManager::getALLExchangeData()
{
	return &m_itemDataMap;
}

void ExchangeDataManager::sendRequestToWeb()
{
	
	string ChannelId = CCUserDefault::sharedUserDefault()->getStringForKey("default_channel_id", "");
	char siteId[100] = {0};
	ODEInt32 currSiteId = g_pSaveData->ReadParam("default_site_id", ODEUInt32(0));
	sprintf(siteId, "%d", currSiteId);
	string link = "";
	link.append(GetConfig("ExchangeDataFormLink"));
	link.append("channelID=");
	link.append(ChannelId);
	link.append("&siteID=");
	link.append(siteId);
	g_pkGuanDanGame->reqGetExchangeData(link.c_str());
	//g_pkGuanDanGame->reqGetExchangeData("http://mbt.odao.com:8089/7mgw/phoneMall/getMallInfo.do?channelID=100000&siteID=10 ");
}

void ExchangeDataManager::getDataByWeb(std::string result)
{
	/*Reader reader;
	Value val;
	if (reader.parse(result, val))
	{
		int valLen = val["list"].size();
		CCLOG("exhchange data len is %d", valLen);
		for (int i = 0; i < valLen; i++)
		{
			Value node = val["list"][i];
			ItemData *data = new ItemData;
			memset (data->itemName, 0, sizeof (data->itemName));
			memset (data->itemIamgeUrl, 0, sizeof (data->itemIamgeUrl));
			data->itemMainType = node["fatherItemID"].asInt();
			data->itemSubType = node["levelID"].asInt();
			data->itemMoneyType = node["itemMoneyType"].asInt();
			data->itemHotExchange = node["itemHotExchange"].asInt();
			data->itemNeedScoreNum = node["itemNeedNumJF"].asInt();
			data->itemNeedJPQNum = node["itemNeedNumJP"].asInt();
			data->itemId = node["itemID"].asInt();
			data->siteId = node["siteID"].asInt();
			data->channelId = node["channelID"].asInt();
			data->sequence = node["sequence"].asInt();
			strcpy(data->itemName, node["itemName"].asString().c_str());
			strcpy(data->itemIamgeUrl, node["itemImageUrl"].asString().c_str());

			updateCashDataFromExternal(data);
		}
		writeCashDataToLocalFile();
		val.clear();
	}
	val = NULL;*/
}

vector<ItemData*>* ExchangeDataManager::getItemDataListWithItemType(ItemType itemType)
{
	map<char, vector<ItemData*>*>::iterator it = m_itemDataMap.find(itemType);
	vector<ItemData*>* itemdata;
	if (it != m_itemDataMap.end())
	{
		itemdata = it->second;
		return itemdata;
	}
	else
	{
		return NULL;
	}
}

int ExchangeDataManager::getItemdataSubTypeCountByItemType(ItemType itemType)
{
	vector<ItemData*>* subItemDataList = getItemDataListWithItemType(itemType);
	if (!subItemDataList)
	{
		return 0;
	}
	int subcount = 0;
	std::map<int,int> m_subCntMap;
	for (vector<ItemData*>::iterator it = subItemDataList->begin(); it != subItemDataList->end(); ++it)
	{
		std::map<int, int>::iterator it1 = m_subCntMap.find((*it)->itemSubType);
		if (it1 == m_subCntMap.end())
		{
			m_subCntMap[(*it)->itemSubType] = subcount;
			subcount++;
		}
	}
	return subcount;
}

vector<ItemData*>* ExchangeDataManager::getReDuiItemDataListWithItemType(ItemType itemType)
{
	vector<ItemData*>* itemDataList = new vector<ItemData*>;

	vector<ItemData*>* preItemDataList = getItemDataListWithItemType(itemType);

	if (preItemDataList != NULL)
	{
		for (vector<ItemData*>::iterator it = preItemDataList->begin(); it != preItemDataList->end(); ++it)
		{
			if ((*it)->itemHotExchange == 1)
			{
				itemDataList->push_back(*it);
			}
		}
		return itemDataList->size() > 0? itemDataList : NULL;
	}
	else
	{
		return NULL;
	}
}

vector<ItemData*>* ExchangeDataManager::getItemDataListWithItemTypeAndSubItemType(ItemType itemType, int subItemType)
{
	vector<ItemData*>* itemDataList = new vector<ItemData*>;

	vector<ItemData*>* preItemDataList = getItemDataListWithItemType(itemType);

	if (preItemDataList != NULL)
	{
		for (vector<ItemData*>::iterator it = preItemDataList->begin(); it != preItemDataList->end(); ++it)
		{
			if ((*it)->itemSubType == subItemType)
			{
				itemDataList->push_back(*it);
			}
		}

		return itemDataList->size() > 0? itemDataList : NULL;
	}
	else
	{
		return NULL;
	}
}

void ExchangeDataManager::clearCashData()
{
	while (m_itemDataMap.size())
	{
		vector<ItemData*>* subItemDataList = m_itemDataMap.at(0);
		while (subItemDataList->size())
		{
			CC_SAFE_DELETE(subItemDataList->at(0));
			subItemDataList->erase(subItemDataList->begin());
		}
		CC_SAFE_DELETE(subItemDataList);
		m_itemDataMap.erase(m_itemDataMap.begin());
	}
}

void ExchangeDataManager::updateCashDataFromExternal(ItemData* itemData)
{
	if (itemData != NULL)
	{
		map<char, vector<ItemData*>*>::iterator it = m_itemDataMap.find(itemData->itemMainType);

		if (it == m_itemDataMap.end())
		{
			m_itemDataMap.insert(pair<char, vector<ItemData*>*>(itemData->itemMainType, NULL));
		}
		it  = m_itemDataMap.find(itemData->itemMainType);
		vector<ItemData*>* subItemDataList = it->second;
		if (subItemDataList == NULL)
		{
			subItemDataList = new vector<ItemData*>;
			m_itemDataMap[itemData->itemMainType] = subItemDataList;
		}
		bool findItemData = false;
		for (vector<ItemData*>::iterator subIt = subItemDataList->begin(); subIt != subItemDataList->end(); ++subIt)
		{
			if ((*subIt)->itemId == itemData->itemId)
			{
				findItemData = true;

				(*subIt)->itemMainType = itemData->itemMainType;
				(*subIt)->itemSubType = itemData->itemSubType;
				(*subIt)->itemMoneyType = itemData->itemMoneyType;
				(*subIt)->itemHotExchange = itemData->itemHotExchange;
				(*subIt)->sequence = itemData->sequence;
				(*subIt)->itemNeedScoreNum = itemData->itemNeedScoreNum;
				(*subIt)->itemNeedJPQNum = itemData->itemNeedJPQNum;
				(*subIt)->itemId = itemData->itemId;
				(*subIt)->channelId = itemData->channelId;
				(*subIt)->siteId = itemData->siteId;
				strcpy((*subIt)->itemName, itemData->itemName);
				strcpy((*subIt)->itemIamgeUrl, itemData->itemIamgeUrl);

				//delete itemData;
				//itemData = NULL;
				break;
			}
		}
		if (!findItemData)
		{
			subItemDataList->push_back(itemData);
		}
	}
}

void ExchangeDataManager::writeCashDataToLocalFile()
{
	char subItemCountKeyName[40] = {0};

	char itemKey[60] = {0};
	 
	for (int i(ITEM_TYPE_SUI_PIAN_DUI_HUAN); i < ITEM_TYPE_MAX; ++i)
	{
		memset(subItemCountKeyName, 0, sizeof(subItemCountKeyName));
		sprintf(subItemCountKeyName, "exchange_sub_item_%d_count", i);
		
		if (m_itemDataMap.find(i) != m_itemDataMap.end())
		{
			vector<ItemData*>* subItemDataList = m_itemDataMap.find(i)->second;

			if (subItemDataList == NULL)
			{
				CCUserDefault::sharedUserDefault()->setIntegerForKey(subItemCountKeyName, 0);
			}
			else
			{
				int subItemCount = subItemDataList->size();
				CCUserDefault::sharedUserDefault()->setIntegerForKey(subItemCountKeyName, subItemCount);

				for (int j(0); j < subItemCount; ++j)
				{
					ItemData* itemData = subItemDataList->at(j);

					if (itemData == NULL)
					{
						CCLog("FUNCTION [%s] LINE [%d] ERROR EXCHANGE ITEM TYPE [%d] TIEM INDEX [%d] == NULL", __FUNCTION__, __LINE__, i, j);
					}
					else
					{
						memset(itemKey, 0, sizeof(itemKey));
						sprintf(itemKey, "exchange_item_type_%d_%d", i, j);
						CCUserDefault::sharedUserDefault()->setIntegerForKey(itemKey, itemData->itemMainType);

						memset(itemKey, 0, sizeof(itemKey));
						sprintf(itemKey, "exchange_item_sub_type_%d_%d", i, j);
						CCUserDefault::sharedUserDefault()->setIntegerForKey(itemKey, itemData->itemSubType);

						memset(itemKey, 0, sizeof(itemKey));
						sprintf(itemKey, "exchange_item_money_type_%d_%d", i, j);
						CCUserDefault::sharedUserDefault()->setIntegerForKey(itemKey, itemData->itemMoneyType);

						memset(itemKey, 0, sizeof(itemKey));
						sprintf(itemKey, "exchange_item_hot_exchange_%d_%d", i, j);
						CCUserDefault::sharedUserDefault()->setIntegerForKey(itemKey, itemData->itemHotExchange);

						memset(itemKey, 0, sizeof(itemKey));
						sprintf(itemKey, "exchange_item_need_jpq_num_%d_%d", i, j);
						CCUserDefault::sharedUserDefault()->setIntegerForKey(itemKey, itemData->itemNeedJPQNum);

						memset(itemKey, 0, sizeof(itemKey));
						sprintf(itemKey, "exchange_item_need_score_num_%d_%d", i, j);
						CCUserDefault::sharedUserDefault()->setIntegerForKey(itemKey, itemData->itemNeedScoreNum);

						memset(itemKey, 0, sizeof(itemKey));
						sprintf(itemKey, "exchange_item_sequence_%d_%d", i, j);
						CCUserDefault::sharedUserDefault()->setIntegerForKey(itemKey, itemData->sequence);

						memset(itemKey, 0, sizeof(itemKey));
						sprintf(itemKey, "exchange_item_siteID_%d_%d", i, j);
						CCUserDefault::sharedUserDefault()->setIntegerForKey(itemKey, itemData->siteId);

						memset(itemKey, 0, sizeof(itemKey));
						sprintf(itemKey, "exchange_item_channelID_%d_%d", i, j);
						CCUserDefault::sharedUserDefault()->setIntegerForKey(itemKey, itemData->channelId);

						memset(itemKey, 0, sizeof(itemKey));
						sprintf(itemKey, "exchange_item_id_%d_%d", i, j);
						CCUserDefault::sharedUserDefault()->setIntegerForKey(itemKey, itemData->itemId);

						memset(itemKey, 0, sizeof(itemKey));
						sprintf(itemKey, "exchange_item_name_%d_%d", i, j);
						CCUserDefault::sharedUserDefault()->setStringForKey(itemKey, itemData->itemName);

						memset(itemKey, 0, sizeof(itemKey));
						sprintf(itemKey, "exchange_item_picture_name_%d_%d", i, j);
						CCUserDefault::sharedUserDefault()->setStringForKey(itemKey, itemData->itemIamgeUrl);
					}
				}
			}
		}
	}

	CCUserDefault::sharedUserDefault()->flush();
}

void ExchangeDataManager::readCashDataFromLocalFile()
{
	clearCashData();

	char subItemCountKeyName[40] = {0};

	char itemKey[60] = {0};

	for (int i(ITEM_TYPE_SUI_PIAN_DUI_HUAN); i < ITEM_TYPE_MAX; ++i)
	{
		memset(subItemCountKeyName, 0, sizeof(subItemCountKeyName));
		sprintf(subItemCountKeyName, "exchange_sub_item_%d_count", i);

		int subItemCount = CCUserDefault::sharedUserDefault()->getIntegerForKey(subItemCountKeyName, 0);
		if (subItemCount == 0)
		{
			m_itemDataMap.insert(pair<char, vector<ItemData*>*>(i, NULL));
		}
		else
		{
			vector<ItemData*>* subItemDataList = new vector<ItemData*>;
			for (int j(0); j < subItemCount; ++j)
			{
				ItemData* itemData = new ItemData;
				memset(itemData, 0, sizeof(ItemData));

				memset(itemKey, 0, sizeof(itemKey));
				sprintf(itemKey, "exchange_item_type_%d_%d", i, j);
				itemData->itemMainType = CCUserDefault::sharedUserDefault()->getIntegerForKey(itemKey, 0);

				memset(itemKey, 0, sizeof(itemKey));
				sprintf(itemKey, "exchange_item_sub_type_%d_%d", i, j);
				itemData->itemSubType = CCUserDefault::sharedUserDefault()->getIntegerForKey(itemKey, 0);

				memset(itemKey, 0, sizeof(itemKey));
				sprintf(itemKey, "exchange_item_money_type_%d_%d", i, j);
				itemData->itemMoneyType = CCUserDefault::sharedUserDefault()->getIntegerForKey(itemKey, 0);

				memset(itemKey, 0, sizeof(itemKey));
				sprintf(itemKey, "exchange_item_hot_exchange_%d_%d", i, j);
				itemData->itemHotExchange = CCUserDefault::sharedUserDefault()->getIntegerForKey(itemKey, 0);

				memset(itemKey, 0, sizeof(itemKey));
				sprintf(itemKey, "exchange_item_need_jpq_num_%d_%d", i, j);
				itemData->itemNeedJPQNum = CCUserDefault::sharedUserDefault()->getIntegerForKey(itemKey, 0);

				memset(itemKey, 0, sizeof(itemKey));
				sprintf(itemKey, "exchange_item_need_score_num_%d_%d", i, j);
				itemData->itemNeedScoreNum = CCUserDefault::sharedUserDefault()->getIntegerForKey(itemKey, 0);

				memset(itemKey, 0, sizeof(itemKey));
				sprintf(itemKey, "exchange_item_sequence_%d_%d", i, j);
				itemData->sequence = CCUserDefault::sharedUserDefault()->getIntegerForKey(itemKey, 0);

				memset(itemKey, 0, sizeof(itemKey));
				sprintf(itemKey, "exchange_item_siteID_%d_%d", i, j);
				itemData->siteId = CCUserDefault::sharedUserDefault()->getIntegerForKey(itemKey, 0);

				memset(itemKey, 0, sizeof(itemKey));
				sprintf(itemKey, "exchange_item_channelID_%d_%d", i, j);
				itemData->channelId = CCUserDefault::sharedUserDefault()->getIntegerForKey(itemKey, 0);

				memset(itemKey, 0, sizeof(itemKey));
				sprintf(itemKey, "exchange_item_id_%d_%d", i, j);
				itemData->itemId = CCUserDefault::sharedUserDefault()->getIntegerForKey(itemKey, 0);

				memset(itemKey, 0, sizeof(itemKey));
				sprintf(itemKey, "exchange_item_name_%d_%d", i, j);
				string itemName = CCUserDefault::sharedUserDefault()->getStringForKey(itemKey, "");
				strcpy(itemData->itemName, itemName.c_str());

				memset(itemKey, 0, sizeof(itemKey));
				sprintf(itemKey, "exchange_item_picture_name_%d_%d", i, j);
				string itemPictureName = CCUserDefault::sharedUserDefault()->getStringForKey(itemKey, "");
				strcpy(itemData->itemIamgeUrl, itemPictureName.c_str());

				subItemDataList->push_back(itemData);
			}

			m_itemDataMap.insert(pair<char, vector<ItemData*>*>(i, subItemDataList));
		}
		
	}
}