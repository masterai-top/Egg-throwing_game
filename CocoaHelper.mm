//////////////////////////////////////////////////////////////////////////
//
//
//	ODAO Engine Source File.
//  Copyright (C), ODAO
//-----------------------------------------------------------------------
//  File Name:  CocoaHelper.mm
//  Version:    v0.0.1
//  Created:    12/9/2013 by neo
//  Compilers:  Visual Studio.Net
//  Description:
//-----------------------------------------------------------------------
//  History:
//  http://www.7pmi.com
//////////////////////////////////////////////////////////////////////////

#include "CocoaHelper.h"
#import "AudioToolbox/AudioToolbox.h"
#import "Reachability.h"
#import "OpenUDID.h"
#import "AppController.h"
#include "MainScene.h"
#import "sys/xattr.h"
#include "DataBase64.h"
#include "ClientData.h"
#import "SFHFKeychainUtils.h"
#include "WeiXinPayControllerForIOS.h"
#import "EAGLView.h"
#import "QRCodeGenerator.h"
#import "YYFileMultiDownloader.h"
#import "SSZipArchive.h"
#import <CoreTelephony/CTCarrier.h>
#import <CoreTelephony/CTTelephonyNetworkInfo.h>

#include <sys/types.h>
#include <sys/sysctl.h>


static double m_latitude;
static double m_longitude;
static std::string m_province;
static std::string m_city;
static std::string m_district;
static std::string m_address;
static UIImageView * m_imageView;
static UIImageView * m_imageViewLogo;

static std::map<int, DouziFileMultiDownloader *> m_downloadTaskMaps;

ODEUInt32 CocoaHelper::GetElectricity()
{
    [[UIDevice currentDevice] setBatteryMonitoringEnabled:YES];
    ODEUInt32 ui32Electricity = fabs([[UIDevice currentDevice] batteryLevel] * 100);
    return ui32Electricity;
}

ODEUInt32 CocoaHelper::GetSignalStrength()
{
    //等ios sdk更新 7.0才能使用公有接口 现在先返回一个随即范围
    return (rand() % 20) + 80;
}

ODEUInt32 CocoaHelper::GetWIFIStrength()
{
    //等ios sdk更新 7.0才能使用公有接口 现在先返回一个随即范围
    return (rand() % 20) + 80;
}

void CocoaHelper::SetAlwaysLight()
{
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
}

void CocoaHelper::ShowWebView(const ODEChar8* pcUrl)
{
    NSString* strUrl = [NSString stringWithUTF8String:pcUrl];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:strUrl]];
}

void CocoaHelper::ShakeBody()
{
    AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
}

void CocoaHelper::DoUpdate(const ODEChar8 *pcUrl)
{
    NSString* pkUrl;
    pkUrl = [[NSString alloc]initWithUTF8String:pcUrl];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:pkUrl]];
    [pkUrl release];
}

const ODEChar8* CocoaHelper::GetDeviceID()
{
    NSString* deviceid = [SFHFKeychainUtils getPasswordForUsername:@"com.hswy.dzddz" andServiceName:@"device_id" error:nil];
    
    if (deviceid == nil)
    {
        string localdeviceId = g_pkClientData->getNewDeviceCode().c_str();
        NSString* newDeviceId = [NSString stringWithUTF8String:localdeviceId.c_str()];
        
        [SFHFKeychainUtils storeUsername:@"com.hswy.dzddz" andPassword:newDeviceId forServiceName:@"device_id" updateExisting:YES error:nil];
        
        return [newDeviceId UTF8String];
    }
    
    NSString* nsDeviceID = [OpenUDID value];
    //return [nsDeviceID UTF8String];
    return [deviceid UTF8String];
}

bool CocoaHelper::IsJailbreakDevice()
{
    NSString* cydiaPath = @"/Applications/Cydia.app";
    NSString* aptPath = @"/private/var/lib/apt";

    if ([[NSFileManager defaultManager] fileExistsAtPath:cydiaPath])
    {
        return true;
    }
    else if ([[NSFileManager defaultManager] fileExistsAtPath:aptPath])
    {
        return true;
    }
    return false;
}

bool CocoaHelper::IsNetwork()
{
    BOOL isExistenceNetwork = YES;
    Reachability *r = [Reachability reachabilityWithHostName:@"www.baidu.com"];
    
    switch ([r currentReachabilityStatus]) {
        case NotReachable:
            isExistenceNetwork=NO;
            //   NSLog(@"没有网络");
            break;
        case ReachableViaWWAN:
            isExistenceNetwork=YES;
            //   NSLog(@"正在使用3G网络");
            break;
        case ReachableViaWiFi:
            isExistenceNetwork=YES;
            //  NSLog(@"正在使用wifi网络");
            break;  
    }
    [r release];
    return isExistenceNetwork;
}

void CocoaHelper::openBrowser(const ODEChar8 * url)
{
	NSString* pkUrl;
    pkUrl = [[NSString alloc]initWithUTF8String:url];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:pkUrl]];
    [pkUrl release];
}

void CocoaHelper::OnPurchase(ODEUInt32 u32Index)
{
    if ([SKPaymentQueue canMakePayments])
    {
        char idBuffer[20] = {0};
        sprintf(idBuffer, "%lld", g_pkClientData->GetUserID());
        string idStr = idBuffer;
        SaveData(idStr);
        CCUserDefault::sharedUserDefault()->setStringForKey("usinglecode", idStr);
        CCUserDefault::sharedUserDefault()->flush();
        g_pkTexasPokerGame->ShowLoading();
        [[AppController AppDelegate] OnPurchase:u32Index];
    }
}

void CocoaHelper::OnWangYinPurchase(const ODEChar8* pcIndentNo)
{
    NSString * str = [NSString stringWithUTF8String:pcIndentNo];
    [[AppController AppDelegate] StartUPPay:str];
}

bool CocoaHelper::addSkipBackupAttributeToItemAtURL(const ODEChar8 *url)
{
    if (&NSURLIsExcludedFromBackupKey == nil)
    {
        const char* filePath = url;//[[URL path] fileSystemRepresentation];
        
        const char* attrName = "com.apple.MobileBackup";
        u_int8_t attrValue = 1;
        
        int result = setxattr(filePath, attrName, &attrValue, sizeof(attrValue), 0, 0);
        return result == 0;
    }
    else
    {
        NSURL *tempurl = [NSURL URLWithString:[NSString stringWithUTF8String:url]];
        NSError *error = nil;
        [tempurl setResourceValue:[NSNumber numberWithBool:YES] forKey:NSURLIsExcludedFromBackupKey error:&error];
        return error == nil;
    }
}

bool CocoaHelper::canShowDial()
{
    NSString *modelname = [[UIDevice currentDevice]model];
    if ([modelname isEqualToString:@"iPhone"])
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CocoaHelper::dialPhone(const char *phoneNum)
{
    NSString* dialNum = [NSString stringWithUTF8String:phoneNum];
    NSMutableString * str=[[NSMutableString alloc] initWithFormat:@"telprompt://%@", dialNum];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:str]];
    [str release];
}

void CocoaHelper::payWithAlipay(float money, int getCoin, int state)
{
    [[AppController AppDelegate] payWithAlipay:(float)money getCoin:(int)getCoin sceneState:(int)state];
}

void CocoaHelper::initLBS()
{
    m_latitude = 0.0f;
    m_longitude = 0.0f;
    m_province = "";
    m_city = "";
    m_district = "";
    m_address = "";
}

int CocoaHelper::getDeviceTotalDiskSpace()
{
    NSDictionary* dictionary = [[NSFileManager defaultManager] attributesOfFileSystemForPath:NSHomeDirectory() error:nil];
    int totalDiskSpace = [[dictionary objectForKey:NSFileSystemSize] integerValue];
    return totalDiskSpace < 0 ? 0 : totalDiskSpace;
}

int CocoaHelper::getSimYunYing()
{
    CTTelephonyNetworkInfo* info = [[CTTelephonyNetworkInfo alloc] init];
    if (info)
    {
        CTCarrier* carrier = [info subscriberCellularProvider];
        NSString* mCarrier = [NSString stringWithFormat:@"%@", [carrier carrierName]];
        string str = [mCarrier UTF8String];
        if (strcmp(str.c_str(), "中国移动") == 0)
        {
            return 1;
        }
        else if (strcmp(str.c_str(), "中国联通") == 0)
        {
            return 2;
        }
        else if (strcmp(str.c_str(), "中国电信") == 0)
        {
            return 3;
        }
        else
        {
            return 4;
        }
    }
    else
    {
        return 0;
    }
}

int CocoaHelper::getSignalType()
{
    Reachability *r = [Reachability reachabilityWithHostName:@"www.baidu.com"];
    
    switch ([r currentReachabilityStatus]) {
        case NotReachable:
            break;
        case ReachableViaWWAN:
            break;
        case ReachableViaWiFi:
            return 1;
            break;
    }
    
    CTTelephonyNetworkInfo* info = [[CTTelephonyNetworkInfo alloc] init];
    if (info)
    {
        NSString* mConnectType = [[NSString alloc] initWithFormat:@"%@", info.currentRadioAccessTechnology];
        if ([mConnectType isEqualToString:@"CTRadioAccessTechnologyLTE"])
        {
            return 4;
        }
        else if ([mConnectType isEqualToString:@"CTRadioAccessTechnologyWCDMA"] ||
                 [mConnectType isEqualToString:@"CTRadioAccessTechnologyHSDPA"] ||
                 [mConnectType isEqualToString:@"CTRadioAccessTechnologyHSUPA"] ||
                 [mConnectType isEqualToString:@"CTRadioAccessTechnologyCDMA1x"] ||
                 [mConnectType isEqualToString:@"CTRadioAccessTechnologyCDMAEVDORev0"] ||
                 [mConnectType isEqualToString:@"CTRadioAccessTechnologyCDMAEVDORevA"] ||
                 [mConnectType isEqualToString:@"CTRadioAccessTechnologyCDMAEVDORevB"] ||
                 [mConnectType isEqualToString:@"CTRadioAccessTechnologyeHRPD"])
        {
            return 3;
        }
        else if ([mConnectType isEqualToString:@"CTRadioAccessTechnologyGPRS"])
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 1;
    }
}

int CocoaHelper::getDeviceFreeDiskSpace()
{
    NSDictionary* dictionary = [[NSFileManager defaultManager] attributesOfFileSystemForPath:NSHomeDirectory() error:nil];
    int freeDiskSpace = [[dictionary objectForKey:NSFileSystemFreeSize] integerValue];
    return freeDiskSpace < 0 ? 0 : freeDiskSpace;
}

float CocoaHelper::getDeviceWidth()
{
    float width = [[UIScreen mainScreen] bounds].size.width;
    NSLog(@"width = %f", width);
    if (width == 736)
    {
        return 2208;
    }
    else
    {
        return width = width * 2;
    }
}

float CocoaHelper::getDeviceHeight()
{
    float height = [[UIScreen mainScreen] bounds].size.height;
    NSLog(@"height = %f", height);
    if (height == 414)
    {
        return 1242;
    }
    else
    {
        return height * 2;
    }
}

string CocoaHelper::getAppVersion()
{
    NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
    NSString *appCurVersion = [infoDictionary objectForKey:@"CFBundleShortVersionString"];
    return [appCurVersion UTF8String];
}

float CocoaHelper::getDeviceSystemVersion()
{
    return [[[UIDevice currentDevice] systemVersion] floatValue];
}

const char* CocoaHelper::getDevicePlatform()
{
    size_t size;
    sysctlbyname("hw.machine", NULL, &size, NULL, 0);
    char *machine = (char*)malloc(size);
    sysctlbyname("hw.machine", machine, &size, NULL, 0);
    NSString *platform = [NSString stringWithCString:machine encoding:NSUTF8StringEncoding];
    
    free(machine);
    
    if ([platform isEqualToString:@"iPhone1,1"]) return "iPhone 2G (A1203)";
    if ([platform isEqualToString:@"iPhone1,2"]) return "iPhone 3G (A1241/A1324)";
    if ([platform isEqualToString:@"iPhone2,1"]) return "iPhone 3GS (A1303/A1325)";
    if ([platform isEqualToString:@"iPhone3,1"]) return "iPhone 4 (A1332)";
    if ([platform isEqualToString:@"iPhone3,2"]) return "iPhone 4 (A1332)";
    if ([platform isEqualToString:@"iPhone3,3"]) return "iPhone 4 (A1349)";
    if ([platform isEqualToString:@"iPhone4,1"]) return "iPhone 4S (A1387/A1431)";
    if ([platform isEqualToString:@"iPhone5,1"]) return "iPhone 5 (A1428)";
    if ([platform isEqualToString:@"iPhone5,2"]) return "iPhone 5 (A1429/A1442)";
    if ([platform isEqualToString:@"iPhone5,3"]) return "iPhone 5c (A1456/A1532)";
    if ([platform isEqualToString:@"iPhone5,4"]) return "iPhone 5c (A1507/A1516/A1526/A1529)";
    if ([platform isEqualToString:@"iPhone6,1"]) return "iPhone 5s (A1453/A1533)";
    if ([platform isEqualToString:@"iPhone6,2"]) return "iPhone 5s (A1457/A1518/A1528/A1530)";
    if ([platform isEqualToString:@"iPhone7,1"]) return "iPhone 6 Plus (A1522/A1524)";
    if ([platform isEqualToString:@"iPhone7,2"]) return "iPhone 6 (A1549/A1586)";
    
    if ([platform isEqualToString:@"iPod1,1"])   return "iPod Touch 1G (A1213)";
    if ([platform isEqualToString:@"iPod2,1"])   return "iPod Touch 2G (A1288)";
    if ([platform isEqualToString:@"iPod3,1"])   return "iPod Touch 3G (A1318)";
    if ([platform isEqualToString:@"iPod4,1"])   return "iPod Touch 4G (A1367)";
    if ([platform isEqualToString:@"iPod5,1"])   return "iPod Touch 5G (A1421/A1509)";
    
    if ([platform isEqualToString:@"iPad1,1"])   return "iPad 1G (A1219/A1337)";
    
    if ([platform isEqualToString:@"iPad2,1"])   return "iPad 2 (A1395)";
    if ([platform isEqualToString:@"iPad2,2"])   return "iPad 2 (A1396)";
    if ([platform isEqualToString:@"iPad2,3"])   return "iPad 2 (A1397)";
    if ([platform isEqualToString:@"iPad2,4"])   return "iPad 2 (A1395+New Chip)";
    if ([platform isEqualToString:@"iPad2,5"])   return "iPad Mini 1G (A1432)";
    if ([platform isEqualToString:@"iPad2,6"])   return "iPad Mini 1G (A1454)";
    if ([platform isEqualToString:@"iPad2,7"])   return "iPad Mini 1G (A1455)";
    
    if ([platform isEqualToString:@"iPad3,1"])   return "iPad 3 (A1416)";
    if ([platform isEqualToString:@"iPad3,2"])   return "iPad 3 (A1403)";
    if ([platform isEqualToString:@"iPad3,3"])   return "iPad 3 (A1430)";
    if ([platform isEqualToString:@"iPad3,4"])   return "iPad 4 (A1458)";
    if ([platform isEqualToString:@"iPad3,5"])   return "iPad 4 (A1459)";
    if ([platform isEqualToString:@"iPad3,6"])   return "iPad 4 (A1460)";
    
    if ([platform isEqualToString:@"iPad4,1"])   return "iPad Air (A1474)";
    if ([platform isEqualToString:@"iPad4,2"])   return "iPad Air (A1475)";
    if ([platform isEqualToString:@"iPad4,3"])   return "iPad Air (A1476)";
    if ([platform isEqualToString:@"iPad4,4"])   return "iPad Mini 2G (A1489)";
    if ([platform isEqualToString:@"iPad4,5"])   return "iPad Mini 2G (A1490)";
    if ([platform isEqualToString:@"iPad4,6"])   return "iPad Mini 2G (A1491)";
    
    if ([platform isEqualToString:@"i386"])      return "iPhone Simulator";
    if ([platform isEqualToString:@"x86_64"])    return "iPhone Simulator";
    
    return [platform UTF8String];
}

const char* CocoaHelper::getDeviceName()
{
    return [[[UIDevice currentDevice] name] UTF8String];
}

void CocoaHelper::setLatitude(double latitude)
{
    m_latitude = latitude;
}

double CocoaHelper::getLatitude()
{
    return m_latitude;
}

void CocoaHelper::setLongitude(double longitude)
{
    m_longitude = longitude;
}

double CocoaHelper::getLongitude()
{
    return m_longitude;
}

void CocoaHelper::setProvince(const char *province)
{
    m_province = province;
}

const char* CocoaHelper::getProvince()
{
    return m_province.c_str();
}

void CocoaHelper::setCity(const char *city)
{
    m_city = city;
}

const char* CocoaHelper::getCity()
{
    return m_city.c_str();
}

void CocoaHelper::setDistrict(const char *district)
{
    m_district = district;
}

const char* CocoaHelper::getDistrict()
{
    return m_district.c_str();
}

void CocoaHelper::setAddress(const char *address)
{
    m_address = address;
}

const char* CocoaHelper::getAddress()
{
    return m_address.c_str();
}

bool CocoaHelper::isGPSOpen()
{
    CLAuthorizationStatus status = [CLLocationManager authorizationStatus];
    if (kCLAuthorizationStatusDenied == status || kCLAuthorizationStatusRestricted == status)
    {
        NSLog(@"定位服务没有打开");
        return false;
    }
    return true;
}

void CocoaHelper::reqLocation()
{
    if (isGPSOpen())
    {
        [[AppController AppDelegate] reqLocation];
    }
}

void CocoaHelper::reqUseWeixinLoginAndShare()
{
    [[AppController AppDelegate] reqUseWeixinLoginAndShare];
}

void CocoaHelper::reqUserWeixinPay()
{
    WeiXinPayControllerForIOS::getInstance()->registApp();
}

const char* CocoaHelper::getWeiXinAppId()
{
	return WEI_XIN_APP_ID;
}

const char* CocoaHelper::getWeiXinApp_signature()
{
	return WeiXinPayControllerForIOS::getInstance()->getApp_signature();
}

const char* CocoaHelper::getWeiXinApp_body()
{
	return WeiXinPayControllerForIOS::getInstance()->getApp_body();
}

void CocoaHelper::setWeiXinApp_noncestr(const char* noncestr)
{
	WeiXinPayControllerForIOS::getInstance()->setApp_noncestr(noncestr);
}

void CocoaHelper::setWeiXinApp_package(const char* mpackage)
{
	WeiXinPayControllerForIOS::getInstance()->setApp_package(mpackage);
}

void CocoaHelper::setWeiXinApp_partnerId(const char* partnerid)
{
	WeiXinPayControllerForIOS::getInstance()->setApp_partnerId(partnerid);
}

void CocoaHelper::setWeiXinApp_prepayid(const char * prepayid)
{
	WeiXinPayControllerForIOS::getInstance()->setApp_prepayid(prepayid);
}

void CocoaHelper::setWeiXinApp_timestamp(const char * timestamp)
{
	WeiXinPayControllerForIOS::getInstance()->setApp_timestamp(timestamp);
}

void CocoaHelper::setWeiXinAppID (const char * appid)
{
	WeiXinPayControllerForIOS::getInstance()->setWeiXinAppID(appid);
}

void CocoaHelper::setWeiXinApp_signature(const char * signature)
{
	WeiXinPayControllerForIOS::getInstance()->setApp_signature(signature);
}

void CocoaHelper::setWeiXinPayOrde(const char * tradeNo)
{
	WeiXinPayControllerForIOS::getInstance()->setWeiXinPayOrde(tradeNo);
}

void CocoaHelper::reqWeiXinPay(long long iUserId, int iMoney, long long iPayPoint, int iChargeType, int iChargeEntrance, int serverid, const char *iChannelID)
{
	if (IsJailbreakDevice())
	{
		WeiXinPayControllerForIOS::getInstance()->reqWeiXinPay(iUserId, iMoney, iPayPoint, iChargeType, iChargeEntrance, serverid, iChannelID, "ios");
	}
	else
	{
		WeiXinPayControllerForIOS::getInstance()->reqWeiXinPay(iUserId, iMoney, iPayPoint, iChargeType, iChargeEntrance, serverid, iChannelID, "appstore");
	}
	
}

void CocoaHelper::DisplayQRCode(const char*url, int x, int y, int width, float logoscale)
{
    NSString* strUrl = [[NSString alloc] initWithCString:url encoding:nil];
    
    m_imageView = [[UIImageView alloc] initWithFrame:CGRectMake(x, y, width, width)];
    m_imageView.image = [QRCodeGenerator qrImageForString:strUrl imageSize:m_imageView.bounds.size.width];
    
    [strUrl release];
    
    m_imageViewLogo = [[UIImageView alloc] initWithFrame:CGRectMake(x + width / 2 - 36 * logoscale, y + width / 2 - 36 * logoscale, 72 * logoscale, 72 * logoscale)];
    m_imageViewLogo.image = [UIImage imageNamed:@"Icon.png"];
    
    [[EAGLView sharedEGLView] addSubview:m_imageView];
    [[EAGLView sharedEGLView] addSubview:m_imageViewLogo];
    
    [m_imageView release];
    [m_imageViewLogo release];
}

void CocoaHelper::RemoveQRCode()
{
    [m_imageView removeFromSuperview];
    [m_imageViewLogo removeFromSuperview];
    m_imageView = NULL;
    m_imageViewLogo = NULL;
}

void CocoaHelper::CCHelperUnPackZipFile (const char * fileName)
{
    char links[256];
    memset(links, 0, sizeof (fileName));
    NSString * nsLinks = [[NSString alloc] initWithCString:fileName encoding:NSASCIIStringEncoding];
    NSString * caches = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES) objectAtIndex:0];
    NSString * unzipPath = caches;

	NSString * checkFilePath = [unzipPath stringByAppendingString:@"/config.xml"];
    [SSZipArchive unzipFileAtPath:nsLinks toDestination:caches];
    [nsLinks release];
}

void CocoaHelper::CCHelperDownloadContent (int contentid, const char * downloadlinks, const char * version, int fileLength)
{
    bool alreadyHasDownloader = false;
    map<int, DouziFileMultiDownloader *>::iterator it;
    for (it = m_downloadTaskMaps.begin(); it != m_downloadTaskMaps.end(); it++)
    {
        if (it->first == contentid)
        {
             [it->second startDownloadWithSize:contentid:fileLength];
            alreadyHasDownloader = true;
        }
    }
    
    if (!alreadyHasDownloader)
    {
        char links[256];
        memset(links, 0, sizeof (links));
        NSString * nsLinks = [[NSString alloc] initWithCString:downloadlinks encoding:NSASCIIStringEncoding];
        
        int index = 0;
        for (int i = nsLinks.length -1; i >= 0; i--)
        {
            if ([nsLinks characterAtIndex:i] == 47)
            {
                index = i;
                break;
            }
        }
        
        NSString * savePath = [nsLinks substringFromIndex:index];
        NSString * caches = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES) objectAtIndex:0];
        NSString * downloadSaveFile = [caches stringByAppendingString:savePath];
        NSString * unzipPath = caches;
        DouziFileMultiDownloader * multiDonwloader = [[DouziFileMultiDownloader alloc] init];
        multiDonwloader.downloadurl = nsLinks;
        multiDonwloader.saveDestPath = downloadSaveFile;
        multiDonwloader.unzipDestPath = unzipPath;
        [multiDonwloader startDownloadWithSize:contentid:fileLength];
        m_downloadTaskMaps.insert(make_pair(contentid, multiDonwloader));
    }
}

int CocoaHelper::CCHelperDownloadPrecent (int contentid, const char * downloadlinks, const char * version, bool isInitLoader)
{
    if (m_downloadTaskMaps.size() <= 0)
        return 0;
    map<int, DouziFileMultiDownloader *>::iterator it;
    
    for (it = m_downloadTaskMaps.begin(); it != m_downloadTaskMaps.end(); it++)
    {
        if (it->first == contentid)
            return [it->second getDownloadLength];
    }
    return 0;
}

bool CocoaHelper::CCHelperDownloadTaskWorking (int contentid)
{
    if (m_downloadTaskMaps.size() <= 0)
        return false;
    
    map<int, DouziFileMultiDownloader *>::iterator it;
    
    for (it = m_downloadTaskMaps.begin(); it != m_downloadTaskMaps.end(); it++)
    {
        if (it->first == contentid && [it->second isDownloading:contentid])
            return true;
    }
    return false;
}

bool CocoaHelper::CCHelperDownloadTaskStartConnecting (int contentid)
{
    if (m_downloadTaskMaps.size() <= 0)
        return false;
    
    map<int, DouziFileMultiDownloader *>::iterator it;
    
    for (it = m_downloadTaskMaps.begin(); it != m_downloadTaskMaps.end(); it++)
    {
        if (it->first == contentid && [it->second isConnecting:contentid])
            return true;
    }
    return false;
}

bool CocoaHelper::CCHelperDownloadContentNeedUpdate (int contentid, const char * downloadlinks, const char * version)
{
    return false;
}

bool CocoaHelper::CCHelperCurrentVersionIsExist (const char * downloadlinks, int filecounts)
{
    char links[256];
    memset(links, 0, sizeof (links));
    NSString * nsLinks = [[NSString alloc] initWithCString:downloadlinks encoding:NSASCIIStringEncoding];
    int index = 0;
    for (int i = nsLinks.length -1; i >= 0; i--)
    {
        if ([nsLinks characterAtIndex:i] == 47)
        {
            index = i;
            break;
        }
    }
    
    NSString * savePath = [nsLinks substringFromIndex:index];
    [nsLinks release];
    NSString * caches = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES) objectAtIndex:0];
    NSString * downloadSaveFile = [caches stringByAppendingString:savePath];
    
    index = 0;
    
    for (int i = downloadSaveFile.length -1; i >= 0; i--)
    {
        if ([downloadSaveFile characterAtIndex:i] == 46)
        {
            index = i;
            break;
        }
    }
    NSString * unzipPath = [downloadSaveFile substringToIndex:index];
    NSString * checkFilePath = [unzipPath stringByAppendingString:@"/content-summary.xml"];

    NSFileManager *mgr=[NSFileManager defaultManager];
    
    if ([mgr fileExistsAtPath:checkFilePath])
    {
        return true;
    }
    
    return false;
}

bool CocoaHelper::CCHelperGetCurrentDownloadSuccessFlags (int contentid)
{
    if (m_downloadTaskMaps.size() <= 0)
        return false;
    
    map<int, DouziFileMultiDownloader *>::iterator it;
    
    for (it = m_downloadTaskMaps.begin(); it != m_downloadTaskMaps.end(); it++)
    {
        if (it->first == contentid && [it->second isDownloadSuccess:contentid])
            return true;
    }
    return false;
}

void CocoaHelper::CCHelperStopDownloadTask (int contentid)
{
    map<int, DouziFileMultiDownloader *>::iterator it;
    for (it = m_downloadTaskMaps.begin(); it != m_downloadTaskMaps.end(); it++)
    {
        if (it->first == contentid)
            [it->second pause];
    }
}

void CocoaHelper::CCHelperResetDownloadSuccessFlags (int contentid)
{
    map<int, DouziFileMultiDownloader *>::iterator it;
    for (it = m_downloadTaskMaps.begin(); it != m_downloadTaskMaps.end(); it++)
    {
        if (it->first == contentid)
            [it->second resetDownloadSuccessFlags];
    }
}

const char * CocoaHelper::CCHelperGetSettingPath (int contentid, const char * downloadlinks, const char * version)
{
    char links[256];
    memset(links, 0, sizeof (links));
    NSString * nsLinks = [[NSString alloc] initWithCString:downloadlinks encoding:NSASCIIStringEncoding];
    
    int index = 0;
    for (int i = nsLinks.length -1; i >= 0; i--)
    {
        if ([nsLinks characterAtIndex:i] == 47)
        {
            index = i;
            break;
        }
    }
    
    NSString * savePath = [nsLinks substringFromIndex:index];
    NSString * caches = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES) objectAtIndex:0];
    NSString * downloadSaveFile = [caches stringByAppendingString:savePath];
    
    index = 0;
    
    for (int i = downloadSaveFile.length -1; i >= 0; i--)
    {
        if ([downloadSaveFile characterAtIndex:i] == 46)
        {
            index = i;
            break;
        }
    }
    
    NSString * unzipPath = [downloadSaveFile substringToIndex:index];
    const char * path =  [unzipPath cStringUsingEncoding:NSASCIIStringEncoding];
    char settingPath [256];
    strcpy(settingPath, path);
    string returnStr = settingPath;
    CCLog("FUNCTION [%s] LINE [%d] returnStr [%s]", __FUNCTION__, __LINE__, returnStr.c_str());
    return returnStr.c_str();
}

bool CocoaHelper::isIOS8()
{
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0)
    {
        return true;
    }
    else
    {
        return false;
    }
}