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
 *  静态方法，设置appid和是否自动登录
 *
 *  @param appid     开发者后台获取的appid
 *  @param autoLogin 开启此项，将会保存用户的用户名和密码和密码到keychain中，下次启动app是会从keychain中读取用户名和密码自动登录
 */
+ (void)setAppid:(NSString *)appid autoLogin:(BOOL)autoLogin;

/**
 *  注册用户推送通知的Device Token
 *
 *  @param token ANPS DeviceToken
 */
- (void)registerDeviceToken:(NSData *)token;

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
