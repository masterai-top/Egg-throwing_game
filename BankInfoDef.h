
/********************  客户端 <<---->> 游戏服务器 <<---->>计费服务器 *******************************/
/*这里消息是客户端与游戏服务器, 游戏服务器与计费服务器共同处理部分,所以单独提取出来***************************/
/**********************************************************************************************/
#ifndef _BANKINFODEF_H_
#define _BANKINFODEF_H_

#include "NetMessage.h"

/**********************************这里的消息ID 不能和 Odao_Client_Msg.h中的消息相同************************************************************************/

const unsigned short  USER_LOGIN_BANK_REQ          =      0xD3;   //玩家登录银行请求
const unsigned short  USER_LOGIN_RESULT_NOTICE     =      0xD4;   //银行登录结果相应
const unsigned short  GET_BANK_COIN_REQ            =      0xD5;   //取款清求
const unsigned short  GET_COIN_RESULT_RES          =      0xD6;   //取款结果响应
const unsigned short  USER_SAVE_COIN_REQ           =      0xD7;   //存款请求
const unsigned short  USER_SAVE_COIN_RES           =      0xD8;   //存款结果响应
const unsigned short  MODIFY_BANK_PASSWD_REQ       =      0xD9;   //用户修改银行密码请求
const unsigned short  MODIFY_BANK_PASSWD_RES       =      0xDA;   //用户修改银行密码响应


typedef struct UserBankLoginReq                   //银行登录
{
    HEADER;
    int            iUserID;                       
    char           szBankPass[PASSWD_LEN];        //银行密码
}UserBankLoginReqDef;

typedef struct LoginBankResult
{
    HEADER;
    unsigned char  ucResultType;                  //返回结果编号类型  1 success ...代表各种出错原因
    long long      llGameCoin;                    //成功玩家游戏货币  否则返回为0
    long long      llBankCoin;                    //成功返回实际数目  否则返回为0

}LoginBankResultDef;

#pragma pack(4)
typedef struct LoginBankResultPC
{
	HEADER;
	unsigned char  ucResultType;                  //返回结果编号类型  1 success ...代表各种出错原因
	long long      llGameCoin;                    //成功玩家游戏货币  否则返回为0
	long long      llBankCoin;                    //成功返回实际数目  否则返回为0

}LoginBankResultPCDef;
#pragma pack()

#define  LBR_NOFIND_USERID_ERROR      150         //用户输入ID错误 userID不存在
#define  LBR_PASSWORD_ERROR           151         //用户密码错误
#define  LBR_DATEBASE_ERROR           152         //数据库操作(存储过程失败)失败
#define  LBR_NOMORE_ENOUGH_COIN       153         //取钱银行没有足够的钱,存钱玩家手中不足存储金额
#define  LBR_SAVE_ERROR_STATE         154         //银行状态错误
#define  LBR_DBCONNECT_ERROR          255         //数据库连接失败

typedef struct GetBankCoinReq                     //取款请求
{
    HEADER;
    int        iUserID;
    long long  llGetNum;
}GetBankCoinReqDef;

#pragma pack(4)
typedef struct GetBankCoinReqPC                     //取款请求
{
	HEADER;
	int        iUserID;
	long long  llGetNum;
}GetBankCoinReqPCDef;
#pragma pack()


typedef struct GetCoinResult                      //取款结果
{
    HEADER;
    unsigned char  ucResultType;                  //取款结果类型 1成功,对应的返回错误的类型
    long long      llGetCoinNum;                  //success 返回所取的货币数目 否则返回都为0
}GetCoinResultDef;
#pragma pack(4)
typedef struct GetCoinResultPC                      //取款结果
{
	HEADER;
	unsigned char  ucResultType;                  //取款结果类型 1成功,对应的返回错误的类型
	long long      llGetCoinNum;                  //success 返回所取的货币数目 否则返回都为0
}GetCoinResultPCDef;
#pragma pack()
typedef struct SaveCoinReq
{
    HEADER;
    int        iUserID;
    long long  llSavingNum;                       //存款数目
}SaveCoinReqDef;

typedef struct SaveCoinRes
{
    HEADER;
    unsigned char   ucResultType;                 //存款结果类型  1成功  其他返回对应的错误类型
    long long       llSelfCoin;                   //返回玩家身上的前数目
}SaveCoinResDef;

typedef struct ModifyBankPasswdReq                //修改银行密码请求
{
    HEADER;
    int        iUserID;
    char       szOldPassWd[PASSWD_LEN];
    char       szNewPassWd[PASSWD_LEN];
}ModifyBankPasswdReqDef;

typedef struct ModifyBankPasswdRes                //修改密码响应
{
    HEADER;
    unsigned char     ucResultType;               //1success其他返回结果
}ModifyBankPasswdResDef;

#endif /* _BANKINFODEF_H_ */





