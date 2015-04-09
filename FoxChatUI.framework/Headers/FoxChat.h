//
//  FoxChat.h
//  FoxChat
//
//  Created by legend on 15/3/24.
//  Copyright (c) 2015 foxsdk. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

//! Project version number for FoxChat.
FOUNDATION_EXPORT double FoxChatVersionNumber;

//! Project version string for FoxChat.
FOUNDATION_EXPORT const unsigned char FoxChatVersionString[];

// FoxChat Header
typedef NS_ENUM(NSInteger, FCMessageType) {
    FCMessageTypeSys,
    FCMessageTypeText,
    FCMessageTypeImage,
    FCMessageTypeVoice,
    FCMessageTypeLocation,
    FCMessageTypeGif,
    FCMessageTypeCard,
    FCMessageTypeLocal,
    FCMessageTypeCustom,
    FCMessageTypeUnimplemented = 999
};

typedef NS_ENUM(NSInteger, FCMessageState) {
    FCMessageStateReceived,
    FCMessageStateSending,
    FCMessageStateSent,
    FCMessageStateFailure,
    FCMessageStateUploading,
    FCMessageStateDownloading
};

typedef NS_ENUM(NSInteger, FCGroupMemberAffi) {
    FCGroupMemberAffiOwner,
    FCGroupMemberAffiAdmin,
    FCGroupMemberAffiMember,
    FCGroupMemberAffiOutcast
};

typedef NS_ENUM(NSInteger, FCCoordType) {
    FCCoordTypeWGS84,
    FCCoordTypeGCJ02,
    FCCoordTypeBD09
};

@interface FCApp : NSObject
@property (readonly) NSString *appid;
@property (readonly) NSString *name;
@property (readonly) NSDictionary *theme;
@end

@interface FCUser : NSObject

@property (readonly) NSString *username;
@property (readonly) NSString *nickname;
@property (readonly) NSUInteger gender;
@property (readonly) NSString *location;
@property (readonly) NSString *avatar;
@end


@interface FCGroup : NSObject

@property (readonly) NSString *gid;
@property (readonly) NSString *name;
@property (readonly) NSString *displayName;
@property (readonly) NSUInteger members;
@property (readonly) NSString *avatar;
@property (readonly) NSString *avatarHash;
@property (readonly) NSString *cardName;
@property (readonly) FCGroupMemberAffi affi;
@property (readonly) BOOL noti;
@end

@interface FCGroupMember : FCUser
@property (readonly) FCGroupMemberAffi affi;
@property (readonly) NSString *cardName;
@end

@interface FCConversion : NSObject

@property (readonly) NSString *cid;
@property (readonly) NSString *name;
@property (readonly) NSString *summary;
@property (readonly) NSUInteger ts;
@property (readonly) BOOL isGroup;
@property (readonly) NSString *target;
@property (nonatomic) id extra;
@property (nonatomic) NSUInteger unreadNum;
@end

@interface FCMessage: NSObject
@property (readonly) NSUInteger mid;
@property (readonly) NSString *target;
@property (readonly) BOOL isGroup;
@property (readonly) FCMessageType type;
@property (readonly) FCMessageState state;
@property (readonly) NSString *body;
@property (readonly) NSDictionary *extra;
@property (readonly) NSUInteger ts;
@property (readonly) FCUser *sender;
@property (readonly) NSString *senderName;
@property (readonly) BOOL isMine;
@property (readonly) BOOL noti;
@property (nonatomic) CGFloat sendingProgress;
@end

@interface FCSysMessage : FCMessage
@end

@interface FCTextMessage : FCMessage
@end

@interface FCImageMessage : FCMessage
@property (readonly, copy) NSString *urlString;
@property (readonly, copy) NSString *thumbUrlString;
@property (readonly, copy) NSString *fileToken;
- (void)loadImageWithSuccess:(void (^)(UIImage *image))success failed:(void(^)(NSError *error))failed progress:(void(^)(CGFloat p))progress isThumb:(BOOL)isThumb;
@end

@interface FCVoiceMessage : FCMessage
@property (readonly, copy) NSString *urlString;
@property (readonly, copy) NSString *fileToken;
@property (nonatomic) BOOL playing;
- (void)loadVoiceWithSuccess:(void (^)(NSData *data))success failed:(void(^)(NSError *error))failed progress:(void(^)(CGFloat p))progress;
@end


@interface FCCardMessage : FCMessage
@property (readonly) NSString *owner;
@property (readonly) NSDictionary *card;
@end

@interface FCLocationMessage : FCMessage
@property (readonly) NSString *locationName;
@property (readonly) CLLocationCoordinate2D coordinate;
- (void)loadMapThumbWithCallback:(void (^)(UIImage *))callback;
@end

@interface FCGifMessage : FCMessage
@end

@interface FCLocalMessage : FCMessage
@end

@interface FCCustomMessage : FCMessage
@end

@interface FCUnimplementedMessage : FCMessage
@end


@interface FoxChat : NSObject

@property (readonly) FCApp *app;
@property (nonatomic, readonly) NSDictionary *theme;
@property (nonatomic, readonly) FCUser *user;
@property (readonly) NSDictionary *userSettings;
@property (readonly) NSArray *contacts;
@property (readonly) NSArray *groups;
@property (readonly) NSUInteger unreadMessagesCount;
@property (readonly) NSArray *conversionsList;
@property (readonly, getter=isConnected) BOOL connected;
@property (readonly, copy) NSString *version;

@property (nonatomic) BOOL autoLogin;

/**
 *  FoxChat为单例模式
 *
 *  @return FoxChat实例
 */
+ (FoxChat *)sharedInstance;

/**
 *  静态方法，设置appid
 *
 *  @param appid 开发者后台为您分配的appid
 */
+ (void)setAppid:(NSString *)appid;


/**
 *  静态方法，设置appid和是否自动登录
 *
 *  @param appid     开发者后台获取的appid
 *  @param autoLogin 开启此项，将会保存用户的用户名和密码和密码到keychain中，下次启动app是会从keychain中读取用户名和密码自动登录
 */
+ (void)setAppid:(NSString *)appid autoLogin:(BOOL)autoLogin;


/**
 *  添加和删除委托，FoxChat对象允许多个委托
 *
 *  @param delegate 委托
 */
- (void)addDelegate:(id)delegate;
- (void)removeDelegate:(id)delegate;

/**
 *  设置登录的用户名和密码
 *
 *  @param username 用户名，username如无特别说明，均指可以标志此用户的唯一id，可以为数据库中的唯一id或用户名、电子邮件地址、电话等
 *  @param password 密码，安全考虑，此密码最好不要使用用户的真实密码，可单独为此用户生成一个foxchat登录密码
 */
- (void)setUserName:(NSString *)username password:(NSString *)password;

/**
 *  设置用户名和密码并登录到foxchat服务器
 *
 *  @param username 用户名
 *  @param password 密码
 */
- (void)connectWithUserName:(NSString *)username password:(NSString *)password;

/**
 *  如果用户名与密码已设置，可通过此方法直接登录
 */
- (void)connect;

/**
 *  退出登录，显示式调用此方法会删除保存在keychain里的用于自动登录的用户名和密码
 */
- (void)disconnect;

/**
 *  检查当前用户的登录状态
 *
 *  @return 登录状态
 */
- (BOOL)isConnected;

/**
 *  注册用户推送通知的Device Token
 *
 *  @param token ANPS DeviceToken
 */
- (void)registerDeviceToken:(NSData *)token;


/** 会话相关 */

/**
 *  标记会话为已读
 *
 *  @param target  聊天对象
 *  @param isGroup 是否为群组
 */
- (void)markConversionReadWithTarget:(NSString *)target isGroup:(BOOL)isGroup;

/**
 *  删除会话，删除后不在会话列表中显示，但不会删除聊天记录
 *
 *  @param target  聊天对象
 *  @param isGroup 是否为群组
 */
- (void)deleteConversionWithTarget:(NSString *)target isGroup:(BOOL)isGroup;


/** 消息相关 */

/**
 *  发送普通文本消息
 *
 *  @param to      收件人用户名或群组id
 *  @param isGroup 是否为群组
 *  @param text    消息内容
 *
 *  @return FCTextMessage对象
 */
- (FCTextMessage *)sendMessageTo:(NSString *)to isGroup:(BOOL)isGroup withText: (NSString *)text;

/**
 *  发送图片消息
 *
 *  @param to      收件人用户名或群组id
 *  @param isGroup 是否为群组
 *  @param image   要发送的UIImage对象
 *
 *  @return FCImageMessage对象
 */
- (FCImageMessage *)sendMessageTo:(NSString *)to isGroup:(BOOL)isGroup withImage: (UIImage *)image;

/**
 *  发送语音消息
 *
 *  @param to       收件人用户名或群组id
 *  @param isGroup  是否为群组
 *  @param data     语音数据，AMR格式
 *  @param duration 持续时间，秒
 *
 *  @return FCVoiceMessage对象
 */
- (FCVoiceMessage *)sendMessageTo:(NSString *)to isGroup:(BOOL)isGroup withVoice: (NSData *)data duration:(CGFloat)duration;

/**
 *  发送地理位置信息
 *
 *  @param to         收件人用户名或群组id
 *  @param isGroup    是否为群组
 *  @param coordinate 坐标
 *  @param type       坐标类型
 *  @param name       位置名称
 *
 *  @return FCLocationMessage对象
 */
- (FCLocationMessage *)sendMessageTo:(NSString *)to isGroup:(BOOL)isGroup withLocationCoordinate:(CLLocationCoordinate2D)coordinate type:(FCCoordType)type name:(NSString *)name;

/**
 *  发送联系人名片
 *
 *  @param to       收件人用户名或群组id
 *  @param isGroup  是否为群组
 *  @param username 欲发送的联系人用户名
 *
 *  @return FCCardMessage对象
 */
- (FCCardMessage *)sendMessageTo:(NSString *)to isGroup:(BOOL)isGroup withCardOwner: (NSString *)username;

/**
 *  获取最近的聊天记录
 *
 *  @param target  聊天对象
 *  @param isGroup 是否为群组
 *
 *  @return FCMessage数组
 */
- (NSArray *)messagesForTarget:(NSString *)target isGroup:(BOOL)isGroup;

/**
 *  获取聊天记录
 *
 *  @param target  聊天对象
 *  @param isGroup 是否为群组
 *  @param mid     mid不大于，可用于获取早期聊天记录或分页
 *
 *  @return FCMessage数组
 */
- (NSArray *)messagesForTarget:(NSString *)target isGroup:(BOOL)isGroup earlierThanMid:(NSUInteger)mid;

/**
 *  删除聊天记录，不可恢复
 *
 *  @param target  聊天对象
 *  @param isGroup 是否为群组
 *
 *  @return 是否成功
 */
- (BOOL)clearMessagesHistoryWithTarget:(NSString *)target isGroup:(BOOL)isGroup;


/** 联系人相关 */

/**
 *  检查是否已添加此用户为联系人
 *
 *  @param username 用户名
 *
 *  @return 是否为联系人
 */
- (BOOL)isContact:(NSString *)username;

/**
 *  添加某用户为联系人，单向
 *
 *  @param username 用户名
 */
- (void)addContact:(NSString *)username;

/**
 *  删除联系人，单向
 *
 *  @param username 用户名
 */
- (void)deleteContact:(NSString *)username;

/**
 *  将某用户加入黑名单，加入黑名单后将接收不到此用户发送的消息，要移出黑名单需重新调用addContact方法
 *
 *  @param username 用户名
 */
- (void)blockContact:(NSString *)username;

/**
 *  联系人搜索
 *
 *  @param keyword 关键字，完整的用户名或部分用户昵称
 *
 *  @return 匹配的联系人数组
 */
- (NSArray *)searchContactsWithKeyword: (NSString *)keyword;


/** 群组相关 */

/**
 *  创建群组
 *
 *  @param members 群成员的用户名数组
 */
- (void)createGroupWithMembers:(NSArray *)members;

/**
 *  添加群成员（单个）
 *
 *  @param groupId 群组ID
 *  @param member  群成员用户名
 */
- (void)addMemberToGroup:(NSString *)groupId member:(NSString *)member;

/**
 *  添加群成员（多个）
 *
 *  @param groupId 群组ID
 *  @param members 群成员的用户名数组
 */
- (void)addMembersToGroup:(NSString *)groupId members:(NSArray *)members;

/**
 *  移除群成员
 *
 *  @param groupId 群组ID
 *  @param member  成员用户名
 */
- (void)removeMemberFromGroup:(NSString *)groupId member:(NSString *)member;

/**
 *  获取群成员列表
 *
 *  @param groupId 群组ID
 */
- (void)fetchMembersOfGroup:(NSString *)groupId;

/**
 *  更改群名称
 *
 *  @param groupId 群组ID
 *  @param name    群组名称
 */
- (void)changeNameOfGroup:(NSString *)groupId withName:(NSString *)name;


/**
 *  修改群名片
 *
 *  @param groupId  群组ID
 *  @param cardName 群名片
 */
- (void)updateSettingsOfGroup:(NSString *)groupId withCardName:(NSString *)cardName;

/**
 *  更改群消息提醒设置
 *
 *  @param groupId 群组ID
 *  @param noti    消息提醒1或0
 */
- (void)updateSettingsOfGroup:(NSString *)groupId withNotificationsEnabled:(BOOL)noti;

/**
 *  退出群组
 *
 *  @param groupId 群组ID
 */
- (void)exitGroup: (NSString *)groupId;

/** 获取用户或群组 */

/**
 *  从本地数据库中获取用户信息
 *
 *  @param username 用户名
 *
 *  @return FCUser对象或null
 */
- (FCUser *)userNamed:(NSString *)username;

/**
 *  从本地数据库中获取群组信息
 *
 *  @param gid 群组ID
 *
 *  @return FCGroup对象
 */
- (FCGroup *)groupWithId:(NSString *)gid;

/** 媒体相关 */

/**
 *  开始录音
 */
- (void)audioStartRecord;

/**
 *  结束录音
 */
- (void)audioStopRecord;

/**
 *  取消录音
 */
- (void)audioCancelRecord;

/**
 *  播放语音消息
 *
 *  @param message FCVoiceMessage对象
 */
- (void)playVoiceMessage:(FCVoiceMessage *)message;

/**
 *  停止播放语音消息
 */
- (void)stopPlayVoiceMessage;

/** 用户设置 */

/**
 *  修改用户头像
 *
 *  @param image   UIImage对象
 *  @param success 成功回调
 *  @param failure 失败回调
 */
- (void)updateUserAvatarWithImage:(UIImage *)image success:(void (^)(FCUser *user))success failure:(void (^)(NSError *error))failure;

/**
 *  修改用户设置
 *
 *  @param option 设置项
 *  @param value  值
 */
- (void)updateUserSettingsOption:(NSString *)option value:(NSString *)value;

/**
 *  修改用户资料
 *
 *  @param profile 资料项
 *  @param value   值
 */
- (void)updateUserProfile:(NSString *)profile value:(NSString *)value;

/** http api方法 */

/**
 *  搜索用户
 *
 *  @param name    用户名或用户昵称
 *  @param success 成功回调
 *  @param failure 失败回调
 */
- (void)searchUserWithName:(NSString *)name success:(void (^)(NSArray *users))success failure:(void (^)(NSError *error))failure;
- (void)fetchNewUsers:(void (^)(NSArray *users))success failure:(void (^)(NSError *error))failure;
- (void)registerUserWithPhoneNumber: (NSString *)phoneNumber password: (NSString *)password nickname: (NSString *)nickname success:(void (^)(NSDictionary *user))success failure:(void (^)(NSError *error))failure;
;

/** 其他 */

/**
 *  不同坐标系标准之间的转化
 *
 *  @param coordinate 经纬度
 *  @param from
 *  @param to
 *
 *  @return 转化后的经纬度坐标
 */
- (CLLocationCoordinate2D)convertCoordinate:(CLLocationCoordinate2D)coordinate fromType:(FCCoordType)from to:(FCCoordType)to;
@end

@protocol FoxChatDelegate <NSObject>
@optional

// connection
- (void)foxChatWillConnectWithUserName:(NSString *)username;
- (void)foxChatDidConnectWithUser:(FCUser *)user;
- (void)foxChatConnectionDidFailWithError:(NSError *)error;
- (void)foxChatConnectionDidRefuseWithError:(NSError *)error;
- (void)foxChatDidDisconnect;

// user
- (void)foxChatDidReceiveUserInfo:(FCUser *)user;
- (void)foxChatDidUpdateUserSettings:(NSDictionary *)settings;
- (void)foxChatDidFailToUpdateUserSettingsWithError:(NSError *)error;
- (void)foxChatDidUpdateUserProfiles:(FCUser *)user;
- (void)foxChatDidFailToUpdateUserProfilesWithError:(NSError *)error;

// contacts delegate
- (void)foxChatdidReceiveContactsList:(NSArray *)contacts;
- (void)foxChatDidUpdateContactsList:(NSArray *)contacts;
- (void)foxChatFetchingContactsDidFailWithError:(NSError *)error;
- (void)foxChatDidSendContactsAddRequest;
- (void)foxChatDidFailToSendContactsAddRequestWithError:(NSError *)error;
- (void)foxChatDidSendContactsBlockRequest;
- (void)foxChatDidFailToSendContactsBlockRequestWithError:(NSError *)error;
- (void)foxChatDidSendContactsDeleteRequest;
- (void)foxChatDidFailToSendContactsDeleteRequestWithError:(NSError *)error;

- (void)foxChatDidReceiveNewContact: (FCUser *)contact;
- (void)foxChatDidDeleteContact: (FCUser *)contact;


// conversations delegate
- (void)foxChatDidUpdateConversationsList: (NSArray *)conversations;

// messages delegate
- (void)foxChatDidReceiveMessage: (FCMessage *)message;
- (void)foxChatWillSendMessage: (FCMessage *)message;
- (void)foxChatDidSendMessage: (FCMessage *)message;
- (void)foxChatDidFailToSendMessage:(FCMessage *)message withError: (NSError *)error;
- (void)foxChatMessage:(FCMessage *)message didChangeState:(FCMessageState)state;
- (void)foxChatMessage:(FCMessage *)message sendingWithProgress:(CGFloat)progress;
- (void)foxChatWillPlayVoiceMessage:(FCVoiceMessage *)message;
- (void)foxChatDidStopPlayVoiceMessage:(FCVoiceMessage *)message;

// unread messages delegate
- (void)foxChatDidChangeUnreadMessagesCount:(NSUInteger)count;

// groups
- (void)foxChatdidReceiveGroups:(NSArray *)groups;
- (void)foxChatFetchingGroupsDidFailWithError:(NSError *)error;
- (void)foxChatDidUpdateGroup: (FCGroup *)group;
- (void)foxChatDidJoinGroup: (FCGroup *)group;
- (void)foxChatDidExitGroup: (FCGroup *)group;
- (void)foxChatDidFailToExitGroupWithError:(NSError *)error;
- (void)foxChatDidCreateGroup: (FCGroup *)group;
- (void)foxChatDidFailToCreateGroupWithError: (NSError *)error;
- (void)foxChatDidAddGroupMembers:(NSArray *)members toGroup:(FCGroup *)group;
- (void)foxChatDidFailToAddGroupMembersWithError: (NSError *)error;
- (void)foxChatDidRemoveMember:(FCGroupMember *)member fromGroup: (FCGroup *)group;
- (void)foxChatDidFailToRemoveGroupMemberWithError: (NSError *)error;
- (void)foxChatDidReceiveGroupInfo:(FCGroup *)group;
- (void)foxChatdidReceiveGroupMembers:(NSArray *)members;
- (void)foxChatFetchingGroupMembersDidFailWithError:(NSError *)error;
- (void)foxChatDidChangeNameOfGroup:(FCGroup *)group;
- (void)foxChatDidFailToChangeGroupNameWithError:(NSError *)error;
- (void)foxChatDidUpdateSettingsOfGroup:(FCGroup *)group;
- (void)foxChatDidFailToUpdateGroupSettingsWithError:(NSError *)error;

// media
- (void)foxChatDidFinishAudioRecordingWithAmrData:(NSData *)amr duration:(CGFloat)duration;
- (void)foxChatDidUpdateAudioRecorderMeterLevel:(double)level;
@end
