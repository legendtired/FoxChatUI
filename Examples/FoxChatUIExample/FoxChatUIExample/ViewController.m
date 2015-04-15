//
//  ViewController.m
//  FoxChatUIExample
//
//  Created by legend on 15/4/15.
//  Copyright (c) 2015年 foxim. All rights reserved.
//

#import "ViewController.h"
#import <FoxChatUI/FoxChatUI.h>

static NSString *const FOXCHAT_DEMO_TARGET = @"demo";

@interface ViewController ()<FoxChatDelegate>

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Do any additional setup after loading the view, typically from a nib.
    
    self.title = @"DEMO";
    
    self.profileView.layer.borderWidth = .5;
    self.profileView.layer.cornerRadius = 3;
    self.profileView.layer.borderColor = [UIColor colorWithRed:0 green:0 blue:0 alpha:.3].CGColor;
    
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"打开" style:UIBarButtonItemStylePlain target:self action:@selector(openChatWindow:)];
    
    [[FoxChat sharedInstance] addDelegate:self];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

// 打开FoxChat会话窗口
- (void)openChatWindow:(id)sender
{
    [[FoxChatUI sharedInstance] open];
}


// 发起聊天
- (IBAction)chatWithMe:(id)sender
{
    [[FoxChatUI sharedInstance] chatWithTarget:FOXCHAT_DEMO_TARGET isGroup:NO];
}


#pragma mark - FoxChat Delegate
- (void)foxChatWillConnectWithUserName:(NSString *)username
{
    self.statusLabel.text = @"正在登录FoxChat";
}

- (void)foxChatDidConnectWithUser:(FCUser *)user
{
    self.statusLabel.text = [NSString stringWithFormat:@"演示用户登录成功\n%@", user.username];
}

- (void)foxChatConnectionDidFailWithError:(NSError *)error
{
    self.statusLabel.text = @"连接失败";
}

- (void)foxChatConnectionDidRefuseWithError:(NSError *)error
{
    self.statusLabel.text = @"演示用户登录失败";
}


@end
