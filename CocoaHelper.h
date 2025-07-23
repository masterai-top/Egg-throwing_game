//////////////////////////////////////////////////////////////////////////
//
//
//	ODAO Engine Header File.
//  Copyright (C), ODAO
//-----------------------------------------------------------------------
//  File Name:  CocoaHelper.h
//  Version:    v0.0.1
//  Created:    12/9/2013 by neo
//  Compilers:  Visual Studio.Net
//  Description:
//-----------------------------------------------------------------------
//  History:
//  http://www.7pmi.com
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "ODEDefine.h"
#include "WebViewClass.h"

class CocoaHelper
{
public:
    static ODEUInt32 GetElectricity();
    
    static ODEUInt32 GetSignalStrength();
    
    static ODEUInt32 GetWIFIStrength();
    
    static void SetAlwaysLight();
    
    static void ShowWebView(const ODEChar8* pcUrl, ODEFloat32 x, ODEFloat32 y, ODEFloat32 f32Width, ODEFloat32 f32Height, ODEInt32 cache);
    
    static void ShowWebView(const ODEChar8* pcUrl);
    
    static void ShakeBody();
    
    static void DoUpdate(const ODEChar8* pcUrl);
    
    static const ODEChar8* GetDeviceID();
    
    static bool IsJailbreakDevice();
    
    static bool IsNetwork();

	static void openBrowser(const ODEChar8 * url);
    
    static void OnPurchase(ODEUInt32 u32Index);
    
    static void OnWangYinPurchase(const ODEChar8* pcIndentNo);
    
    static bool addSkipBackupAttributeToItemAtURL(const ODEChar8* url);

	//  是否可以拨打电话
	static bool canShowDial();
	// 拨打电话
	static void dialPhone(const char* phoneNum);
    
    //支付宝支付
    static void payWithAlipay(float money, int getCoin, int state);
    
    static void initLBS();
    
    //获取设备的总容量
    static int getDeviceTotalDiskSpace();
    //获取运营商信息
    static int getSimYunYing();
    //获取网络类型
    static int getSignalType();
    //获取设备的可用容量
    static int getDeviceFreeDiskSpace();
    //获取屏幕的宽度
    static float getDeviceWidth();
    //获取屏幕的高度
    static float getDeviceHeight();
    //获取应用的版本号
    static std::string getAppVersion();
    //获取系统版本号
    static float getDeviceSystemVersion();
    //获取手机型号
    static const char* getDevicePlatform();
    //获取设备名称
    static const char* getDeviceName();
    
    //纬度
    static void setLatitude(double latitude);
    static double getLatitude();
    //经度
    static void setLongitude(double longitude);
    static double getLongitude();
    //省
    static void setProvince(const char* province);
    static const char* getProvince();
    //城市
    static void setCity(const char* city);
    static const char* getCity();
    //区域
    static void setDistrict(const char* district);
    static const char* getDistrict();
    //地址
    static void setAddress(const char* address);
    static const char* getAddress();
    
    //gps是否开启
    static bool isGPSOpen();
    
    //请求定位
    static void reqLocation();
    
    //尝试使用微信登录分享等
    static void reqUseWeixinLoginAndShare();
    
    //尝试使用微信支付
    static void reqUserWeixinPay();

	//**********************************************************************
	//								微信支付相关

	// 获取微信应用ID
	static const char* getWeiXinAppId();
	// 获取微信签名
	static const char* getWeiXinApp_signature();
	// 获取微信商品描述信息
	static const char* getWeiXinApp_body();
	//
	static void setWeiXinApp_noncestr(const char* noncestr);
	//
	static void setWeiXinApp_package(const char* mpackage);
	//
	static void setWeiXinApp_partnerId(const char* partnerid);
	//
	static void setWeiXinApp_prepayid(const char * prepayid);
	//
	static void setWeiXinApp_timestamp(const char * timestamp);
	// 设置微信应用ID
	static void setWeiXinAppID(const char * appid);
	// 设置微信签名
	static void setWeiXinApp_signature(const char * signature);
	// 设置微信订单号
	static void setWeiXinPayOrde(const char * tradeNo);
	// 请求微信支付 
	static void reqWeiXinPay(long long iUserId, int iMoney, long long iPayPoint, int iChargeType, int iChargeEntrance, int serverid, const char *iChannelID);

	//**********************************************************************
    
    //显示二维码
    static void DisplayQRCode(const char*url, int x, int y, int width, float logoscale);
    static void RemoveQRCode();
    
    //声音下载
    
    
	static void CCHelperDownloadContent (int contentid, const char * downloadlinks, const char * version, int filelength);
    static int CCHelperDownloadPrecent (int contentid, const char * downloadlinks, const char * version, bool isInitLoader);
    static bool CCHelperDownloadTaskWorking (int contentid);
    static bool CCHelperDownloadTaskStartConnecting (int contentid);
    static bool CCHelperDownloadContentNeedUpdate (int contentid, const char * downloadlinks, const char * version);
    static bool CCHelperCurrentVersionIsExist (const char * downloadlinks, int filecounts);
    static bool CCHelperGetCurrentDownloadSuccessFlags (int contentid);
    static void CCHelperStopDownloadTask (int contentid);
    static void CCHelperResetDownloadSuccessFlags (int contentid);
    static const char * CCHelperGetSettingPath (int contentid, const char * downloadlinks, const char * version);
    static void CCHelperUnPackZipFile (const char * fileName);
    
    static bool isIOS8();
};