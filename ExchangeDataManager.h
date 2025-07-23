#pragma once
#include "cocos2d.h"
#include <map>

/********************************************
*
*				管理兑换界面的相关数据
*
*********************************************/

//一级类型
typedef enum tagItemType
{
	ITEM_TYPE_SUI_PIAN_DUI_HUAN,				//碎片兑换
	ITEM_TYPE_SHI_WU_JIANG_PIN,					//实物奖品
	ITEM_TYPE_XU_NI_DAO_JU,						//虚拟道具
	ITEM_TYPE_SHENG_HUO_YOU_HUI,				//生活优惠
	ITEM_TYPE_MAX
}ItemType;

//二级类型 碎片兑换
typedef enum tagSubItemType0
{

}SubItemType0;

//二级类型 实物奖品
typedef enum tagSubItemType1
{
	SUB_ITEM_TYPE_1_KA_LEI,						//卡类
	SUB_ITEM_TYPE_1_DIAN_ZI,					//电子
	SUB_ITEM_TYPE_1_SHI_WU, 					//实物
	SUB_ITEM_TYPE_1_QI_TA,						//其他
	SUB_ITEM_TYPE_1_MAX,
}SubItemType1;

//二级类型 虚拟道具
typedef enum tagSubItemType2
{

}SubItemType2;

//二级类型 生活优惠
typedef enum tagSubItemType3
{

}SubItemType3;

typedef struct TagItemData
{
	char     itemMainType;			//商品一级类型
	char	 itemSubType;			//商品二级类型 0:没有二级类型 
	char     itemMoneyType;			//商品兑换所需货币类型 0：奖品券 1：积分 2：积分和奖品券
	char	 itemHotExchange;		//商品热兑 0：非热兑 1：热兑
	int      itemNeedJPQNum;		//商品兑换所需的奖品券的数量
	int      itemNeedScoreNum;		//商品兑换所需的积分的数量
	int		 itemId;				//商品的id
	int		 siteId;				//站点的id
	int		 channelId;				//渠道的id
	int		 sequence;				//显示顺序
	char     itemName[60];			//商品名称
	char     itemIamgeUrl[60];		//商品图片路径
}ItemData;

class ExchangeDataManager
{
public:
	ExchangeDataManager();
	~ExchangeDataManager();

	static ExchangeDataManager* getInstance();
	//根据一级类型获取下边的全部商品
	std::vector<ItemData*>* getItemDataListWithItemType(ItemType itemType);

	// 根绝一级类型获取该类型下的二级类型数量
	int getItemdataSubTypeCountByItemType(ItemType itemType);

	//获取一级类型下边的热兑奖品列表(注：使用完之后，需要手动清空并删除vector，但是里边的元素不需要删除)
	std::vector<ItemData*>* getReDuiItemDataListWithItemType(ItemType itemType);

	//获取一级类型下某一子类型下的商品列表,支持ItemType下边所有的子类型 (注：使用完之后，需要手动清空并删除vector，但是里边的元素不需要删除)
	std::vector<ItemData*>* getItemDataListWithItemTypeAndSubItemType(ItemType itemType, int subItemType);

	//清空缓存数据
	void clearCashData();

	//从服务器获取到数据之后写入到缓存中
	void updateCashDataFromExternal(ItemData* itemData);

	//写入缓存数据到文件(从服务器获取到数据保存到缓存中之后再调用此方法)
	void writeCashDataToLocalFile();

	//从文件读取缓存数据
	void readCashDataFromLocalFile();
	// 发送请求
	void sendRequestToWeb();
	// 得到商品的数据
	void getDataByWeb(std::string result);
	// 得到所有的商品数据
	std::map<char, std::vector<ItemData*>*> * getALLExchangeData();

private:

	static ExchangeDataManager* instance;

	std::map<char, std::vector<ItemData*>*> m_itemDataMap;
};
