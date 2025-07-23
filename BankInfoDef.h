
/********************  �ͻ��� <<---->> ��Ϸ������ <<---->>�Ʒѷ����� *******************************/
/*������Ϣ�ǿͻ�������Ϸ������, ��Ϸ��������Ʒѷ�������ͬ������,���Ե�����ȡ����***************************/
/**********************************************************************************************/
#ifndef _BANKINFODEF_H_
#define _BANKINFODEF_H_

#include "NetMessage.h"

/**********************************�������ϢID ���ܺ� Odao_Client_Msg.h�е���Ϣ��ͬ************************************************************************/

const unsigned short  USER_LOGIN_BANK_REQ          =      0xD3;   //��ҵ�¼��������
const unsigned short  USER_LOGIN_RESULT_NOTICE     =      0xD4;   //���е�¼�����Ӧ
const unsigned short  GET_BANK_COIN_REQ            =      0xD5;   //ȡ������
const unsigned short  GET_COIN_RESULT_RES          =      0xD6;   //ȡ������Ӧ
const unsigned short  USER_SAVE_COIN_REQ           =      0xD7;   //�������
const unsigned short  USER_SAVE_COIN_RES           =      0xD8;   //�������Ӧ
const unsigned short  MODIFY_BANK_PASSWD_REQ       =      0xD9;   //�û��޸�������������
const unsigned short  MODIFY_BANK_PASSWD_RES       =      0xDA;   //�û��޸�����������Ӧ


typedef struct UserBankLoginReq                   //���е�¼
{
    HEADER;
    int            iUserID;                       
    char           szBankPass[PASSWD_LEN];        //��������
}UserBankLoginReqDef;

typedef struct LoginBankResult
{
    HEADER;
    unsigned char  ucResultType;                  //���ؽ���������  1 success ...������ֳ���ԭ��
    long long      llGameCoin;                    //�ɹ������Ϸ����  ���򷵻�Ϊ0
    long long      llBankCoin;                    //�ɹ�����ʵ����Ŀ  ���򷵻�Ϊ0

}LoginBankResultDef;

#pragma pack(4)
typedef struct LoginBankResultPC
{
	HEADER;
	unsigned char  ucResultType;                  //���ؽ���������  1 success ...������ֳ���ԭ��
	long long      llGameCoin;                    //�ɹ������Ϸ����  ���򷵻�Ϊ0
	long long      llBankCoin;                    //�ɹ�����ʵ����Ŀ  ���򷵻�Ϊ0

}LoginBankResultPCDef;
#pragma pack()

#define  LBR_NOFIND_USERID_ERROR      150         //�û�����ID���� userID������
#define  LBR_PASSWORD_ERROR           151         //�û��������
#define  LBR_DATEBASE_ERROR           152         //���ݿ����(�洢����ʧ��)ʧ��
#define  LBR_NOMORE_ENOUGH_COIN       153         //ȡǮ����û���㹻��Ǯ,��Ǯ������в���洢���
#define  LBR_SAVE_ERROR_STATE         154         //����״̬����
#define  LBR_DBCONNECT_ERROR          255         //���ݿ�����ʧ��

typedef struct GetBankCoinReq                     //ȡ������
{
    HEADER;
    int        iUserID;
    long long  llGetNum;
}GetBankCoinReqDef;

#pragma pack(4)
typedef struct GetBankCoinReqPC                     //ȡ������
{
	HEADER;
	int        iUserID;
	long long  llGetNum;
}GetBankCoinReqPCDef;
#pragma pack()


typedef struct GetCoinResult                      //ȡ����
{
    HEADER;
    unsigned char  ucResultType;                  //ȡ�������� 1�ɹ�,��Ӧ�ķ��ش��������
    long long      llGetCoinNum;                  //success ������ȡ�Ļ�����Ŀ ���򷵻ض�Ϊ0
}GetCoinResultDef;
#pragma pack(4)
typedef struct GetCoinResultPC                      //ȡ����
{
	HEADER;
	unsigned char  ucResultType;                  //ȡ�������� 1�ɹ�,��Ӧ�ķ��ش��������
	long long      llGetCoinNum;                  //success ������ȡ�Ļ�����Ŀ ���򷵻ض�Ϊ0
}GetCoinResultPCDef;
#pragma pack()
typedef struct SaveCoinReq
{
    HEADER;
    int        iUserID;
    long long  llSavingNum;                       //�����Ŀ
}SaveCoinReqDef;

typedef struct SaveCoinRes
{
    HEADER;
    unsigned char   ucResultType;                 //���������  1�ɹ�  �������ض�Ӧ�Ĵ�������
    long long       llSelfCoin;                   //����������ϵ�ǰ��Ŀ
}SaveCoinResDef;

typedef struct ModifyBankPasswdReq                //�޸�������������
{
    HEADER;
    int        iUserID;
    char       szOldPassWd[PASSWD_LEN];
    char       szNewPassWd[PASSWD_LEN];
}ModifyBankPasswdReqDef;

typedef struct ModifyBankPasswdRes                //�޸�������Ӧ
{
    HEADER;
    unsigned char     ucResultType;               //1success�������ؽ��
}ModifyBankPasswdResDef;

#endif /* _BANKINFODEF_H_ */





