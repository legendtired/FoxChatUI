//
//  FoxChatUI.h
//  FoxChatUI
//
//  Created by legend on 15/3/24.
//  Copyright (c) 2015 foxsdk. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for FoxChatUI.
FOUNDATION_EXPORT double FoxChatUIVersionNumber;

//! Project version string for FoxChatUI.
FOUNDATION_EXPORT const unsigned char FoxChatUIVersionString[];

#import "FoxChat.h"

@interface FoxChatUI : NSObject

@property (nonatomic) BOOL autoLogin;

/**
 *  获取FoxChatUI实例
 *
 *  @return FoxChatUI实例
 */
+ (FoxChatUI *)sharedInstance;

/**
 *  设置日志级别
 *
 *  @param logLevel 日志级别
 *  @see FCLogLevel
 */
+ (void)setLogLevel:(FCLogLevel)logLevel;

/**
 *  静态方法，设置appid和是否自动登录
 *
 *  @param appid     开发者后台获取的appid
 *  @param autoLogin 开启此项，将会保存用户的用户名和密码和密码到keychain中，下次启动app是会从keychain中读取用户名和密码自动登录
 */
+ (void)setAppid:(NSString *)appid autoLogin:(BOOL)autoLogin;

/**
 *  注册用户推送通知的Device Token并指定使用的证书类型
 *
 *  @param token      设备ID
 *  @param isProduction 是否使用生产环境的推送证书，默认为NO，使用开发环境的推送证书，YES则使用生产环境的推送证书。程序发布前需要修改为YES
 */
- (void)registerDeviceToken:(NSData *)token isProduction:(BOOL)isProduction;


/**
 *  设置用户名或密码并登录到服务器
 *
 *  @param username 用户名，username如无特别说明，均指可以标志此用户的唯一id，可以为数据库中的唯一id或用户名、电子邮件地址、电话等
 *  @param password 密码，安全考虑，此密码最好不要使用用户的真实密码，可单独为此用户生成一个foxchat登录密码
 */
- (void)loginWithUserName:(NSString *)username password:(NSString *)password;

/**
 *  发起会话
 *
 *  @param target  聊天对象用户名或群组id
 *  @param isGroup 是否为群组
 */
- (void)chatWithTarget:(NSString *)target isGroup:(BOOL)isGroup;

/**
 *  打开聊天窗口
 */
- (void)open;

/**
 *  关闭聊天窗口
 */
- (void)close;

@end
