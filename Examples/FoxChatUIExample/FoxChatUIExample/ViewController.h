//
//  ViewController.h
//  FoxChatUIExample
//
//  Created by legend on 15/4/15.
//  Copyright (c) 2015年 foxim. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

@property (nonatomic) IBOutlet UIView *profileView;
@property (nonatomic) IBOutlet UILabel *statusLabel;


- (IBAction)chatWithMe:(id)sender;

@end

