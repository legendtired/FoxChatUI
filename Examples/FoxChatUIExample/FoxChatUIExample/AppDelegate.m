//
//  AppDelegate.m
//  FoxChatUIExample
//
//  Created by legend on 15/4/15.
//  Copyright (c) 2015年 foxim. All rights reserved.
//

#import "AppDelegate.h"
#include <stdlib.h>
#import <FoxChatUI/FoxChatUI.h>

static NSString *const FOXCHAT_DEMO_USER_PREFIX = @"demo";
static NSString *const FOXCHAT_DEMO_USER_PASSWORD = @"demo";
static NSString *const FOXCHAT_DEMO_USER_KEY = @"fc_demo_user";

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    // 演示用AppID
    [FoxChatUI setAppid:@"1000" autoLogin:YES];
    
    // 演示用随机用户
    [[FoxChatUI sharedInstance] loginWithUserName:[self randomDemoUser] password:FOXCHAT_DEMO_USER_PASSWORD];
    
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


// 随机演示用户
- (NSString *)randomDemoUser
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    if (![defaults stringForKey:FOXCHAT_DEMO_USER_KEY]) {
        NSString *demoUser = [NSString stringWithFormat:@"%@%d", FOXCHAT_DEMO_USER_PREFIX, arc4random()];
        [defaults setObject:demoUser forKey:FOXCHAT_DEMO_USER_KEY];
        [defaults synchronize];
    }
    
    return [defaults stringForKey:FOXCHAT_DEMO_USER_KEY];
}

@end
