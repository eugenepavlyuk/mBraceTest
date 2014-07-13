//
//  CardsViewController.m
//  mBraceTest
//
//  Created by Eugene Pavluk on 7/13/14.
//  Copyright (c) 2014 IgolSoft. All rights reserved.
//

#import "CardsViewController.h"
#import "CardView.h"

@interface CardsViewController () <CardViewDelegate>

@property (strong, nonatomic) NSMutableArray *cards;
@property (nonatomic) CardView *currentCardView;
@property (nonatomic, assign) NSInteger currentCount;

@end

@implementation CardsViewController

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.currentCount = 0;
    
    CGRect cardFrame = CGRectMake(15, self.view.bounds.size.height / 2 - 183, 290, 366);
    
    // Setup overlay views
    UIImage *leftImage = [UIImage imageNamed:@"visual_clue_no"];
    UIImageView *leftImageView = [[UIImageView alloc] initWithImage:leftImage];
    leftImageView.frame = CGRectMake(0, 0, 290, 255);

    UIImage *rightImage = [UIImage imageNamed:@"visual_clue_yes"];
    UIImageView *rightImageView = [[UIImageView alloc] initWithImage:rightImage];
    rightImageView.frame = CGRectMake(0, 0, 290, 255);
    
    // Initialize all CardView instances
    [CardView setCardViewFrame:cardFrame];
    [CardView setOverlayLeft:leftImageView right:rightImageView up:nil down:nil];
    
    self.cards = [NSMutableArray array];
    
    for (int i = 1; i <= 20; i++)
    {
        CardView *cardView = [[CardView alloc] init];
        cardView.delegate = self;
        cardView.layer.opacity = 0.0f;
        [self addCardContent:cardView forCard:i];
        [self.cards addObject:cardView];
    }
    
    self.currentCardView = [self.cards objectAtIndex:self.currentCount];
    [self.view addSubview:self.currentCardView];
    [self.currentCardView showFromLeft];
}

- (void)addCardContent:(CardView *)cardView forCard:(NSUInteger)cardNumber
{
    UIImageView *imageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:[NSString stringWithFormat:@"card_%02i", cardNumber]]];
    imageView.frame = cardView.bounds;
    [cardView addSubview:imageView];
}

#pragma mark - Delegate functions

- (void)cardDidLeaveLeftEdge:(CardView *)cardView
{
    NSLog(@"%s", __FUNCTION__);
    self.currentCount++;
    BOOL success = YES;
    if (self.currentCount > self.cards.count - 1)
    {
        self.currentCount--;
        success = NO;
    }
    
    self.currentCardView = [self.cards objectAtIndex:_currentCount];
    [self.view addSubview:self.currentCardView];
    
    if (success)
        [self.currentCardView showFromCenter];
    else
        [self.currentCardView showFromLeft];
}

- (void)cardDidLeaveRightEdge:(CardView *)cardView
{
    NSLog(@"%s", __FUNCTION__);
    self.currentCount++;
    BOOL success = YES;
    
    if (self.currentCount > self.cards.count - 1)
    {
        self.currentCount--;
        success = NO;
    }
    
    self.currentCardView = [self.cards objectAtIndex:_currentCount];
    [self.view addSubview:self.currentCardView];
    
    if (success)
        [self.currentCardView showFromCenter];
    else
        [self.currentCardView showFromLeft];
}

- (void)cardDidLeaveTopEdge:(CardView *)cardView
{
    NSLog(@"%s", __FUNCTION__);
    [self.cards removeObjectAtIndex:self.currentCount];
    BOOL success = YES;
		
    if (self.currentCount > self.cards.count - 1)
    {
        self.currentCount--;
        success = NO;
    }
    
    self.currentCardView = [self.cards objectAtIndex:_currentCount];
    [self.view addSubview:self.currentCardView];
    
    if (success)
        [self.currentCardView showFromCenter];
    else
        [self.currentCardView showFromLeft];
}

- (void)cardDidLeaveBottomEdge:(CardView *)cardView
{
    NSLog(@"%s", __FUNCTION__);
    BOOL success = YES;
    // Move current card to end
    // If at end, go to beginning
    if (self.currentCount == self.cards.count - 1)
    {
        self.currentCount = 0;
        success = NO;
    }
    
    self.currentCardView = [self.cards objectAtIndex:self.currentCount];
    if (success)
    {
        [self.cards removeObjectAtIndex:self.currentCount];
        [self.cards addObject:self.currentCardView];
        self.currentCardView = [self.cards objectAtIndex:self.currentCount];
        [self.view addSubview:self.currentCardView];
        [self.currentCardView showFromCenter];
    }
    else
    {
        self.currentCardView = [self.cards objectAtIndex:self.currentCount];
        [self.view addSubview:self.currentCardView];
        [self.currentCardView showFromLeft];
    }
}

@end
