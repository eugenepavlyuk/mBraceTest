//
//  CardsViewController.h
//  mBraceTest
//
//  Created by Eugene Pavluk on 7/13/14.
//  Copyright (c) 2014 IgolSoft. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 @brief Parameter used to specify how far the card must be dragged for the card
 to leave the left or right edge.
 @remark Recommended value is 65.
*/
#define kHorizontalEdgeOffset   65

/**
 @brief Parameter used to specify how far the card must be dragged for the card
 to leave the top or bottom edge.
 @remark Recommended value is 65.
*/
#define kVerticalEdgeOffset     65

/**
 @brief Paramter used to specify how far past the resting point, the rubber band
 animation will go in the first pass.
 @remark Recommended value is 25.
*/
#define kRubberBandFirstPass    25

/**
 @brief Paramter used to specify how far past the resting point, the rubber band
 animation will go in the second pass.
 @remark Recommended value is 10.
 */
#define kRubberBandSecondPass   10

/**
 @brief Parameter stating the duration of the rubber band animation.
 @remark Recommended value is 0.75f.
*/
#define kRubberBandDuration     0.75f

/**
 @brief Parameter stating the duration of the card leaving animation.
 @remark Recommended value is 0.5f.
*/
#define kCardLeavesDuration     0.5f

/**
 @brief Rotation factor that controls how many degrees the rotation is.
 @detail This is a ratio; make this 1.0f for full rotation and less than 1 for
 less rotation.
 @remark Recommended value is 0.25f.
*/
#define kRotationFactor         0.25f

/**
 @brief Opacity factor that controls how quickly the opacity increases when overlay
 is fading in.
 @detail This is a ratio; make this 1.0f for a rapid change and less than 1 for
 a less quick transition.
 @remark Recommended value is 0.5f
*/
#define kOverlayOpacityFactor   0.5f

/**
 @brief Opacity factor that controls how quickly the opacity descreases when the
 view is dragged in any direction when there is an overlay present.
 @detail This is a ratio; make this greater than 1.0f for a rapid change and 
 less than 1 for a less quick transition.
 @remark Recommended value is 0.15f.
*/
#define kViewOpacityFactor      0.15f

/**
 @brief Opacity factor that controls how quickly the opacity descreases when the
 view is dragged to the left or right during the rotation animation.
 @detail This is a ratio; make this greater than 1.0f for a rapid change and
 less than 1 for a less quick transition.
 @remark Recommended value is 0.5f.
 */
#define kViewRotationOpacityFactor      0.5f

/**
 @brief This is the amount of degrees that the view starts at when it is being
 shown from the left or right.
 @remark Recommended value is 60.
 @see showFromLeft
 @see showFromRight
*/
#define kStartRotation          60


@protocol CardViewDelegate;


@interface CardView : UIView

/**
 @brief The delegate of the view. Ensure that you set this delegate so that you
 can perform functions when the cards leaves the screen.
*/
@property (nonatomic, weak) id <CardViewDelegate> delegate;

/**
 @brief A flag that can be set to not allow the view to be moved to the left.
*/
@property (nonatomic, assign) BOOL allowLeft;

/**
 @brief A flag that can be set to not allow the view to be moved to the right.
*/
@property (nonatomic, assign) BOOL allowRight;

/**
 @brief A flag that can be set to not allow the view to be moved to the top.
*/
@property (nonatomic, assign) BOOL allowUp;

/**
 @brief A flag that can be set to not allow the view to be moved to the bottom.
*/
@property (nonatomic, assign) BOOL allowDown;

/**
 @pre setCardViewFrame
 @brief This method initializes an instance of the class CardView. You must
 set the card view's frame before initializing. 
 @warning This is the only valid way to initialize an instance of a CardView.
 Others will throw an exception.
 @throws No Frame Specified
*/
- (instancetype)init;

/**
 @brief Sets the frame for every instance of CardView. This is a factory function.
 @param frame The frame to set as the CardView frame.
 @note This must be done before creating any instances of the CardView.
 @post Call the init function for each instance.
*/
+ (void)setCardViewFrame:(CGRect)frame;

/**
 @brief Sets the overlay views for each direction; nil can be specified if an
 overlay is not desired in a specific direction. This is a factory function.
 @param leftOverlay The view to be overlayed when the card view is dragged to 
 the left.
 @param rightOverlay The view to be overlayed when the card view is dragged to
 the right.
 @param upOverlay The view to be overlayed when the card view is dragged to
 the top.
 @param downOverlay The view to be overlayed when the card view is dragged to
 the bottom.
 @note This is done once and should be set up before creating any instances
 of the CardView. If this function is not called, all overlays will be nil;
 the CardView will still work.
*/
+ (void)setOverlayLeft:(UIView *)leftOverlay right:(UIView *)rightOverlay
                    up:(UIView *)upOverlay down:(UIView *)downOverlay;

/**
 @brief Presents the card from the left side of the screen. Opacity increases
 from 0 and rotation starts from -kStartRotation degrees to 0.
 @see kStartRotation
*/
- (void)showFromLeft;

/**
 @brief Presents the card from the right side of the screen. Opacity increases
 from 0 and rotation starts from kStartRotation degrees to 0.
 @see kStartRotation
*/
- (void)showFromRight;

/**
 @brief Presents the card from the top of the screen. Opacity increases
 from 0 to 1.
*/
- (void)showFromTop;

/**
 @brief Presents the card from the bottom of the screen. Opacity increases
 from 0 to 1.
*/
- (void)showFromBottom;

/**
 @brief Presents the card from the center of the screen. Opacity increases
 from 0 to 1.
 */
- (void)showFromCenter;


@end

@protocol CardViewDelegate

/**
 @brief Callback delegate function that is called when the card leaves the top
 of the screen.
 @param cardView The card view that has left the screen.
 @see kVerticalEdgeOffset
*/
- (void)cardDidLeaveTopEdge:(CardView *)cardView;

/**
 @brief Callback delegate function that is called when the card leaves the bottom
 of the screen.
 @param cardView The card view that has left the screen.
 @see kVerticalEdgeOffset
*/
- (void)cardDidLeaveBottomEdge:(CardView *)cardView;

/**
 @brief Callback delegate function that is called when the card leaves the left
 side of the screen.
 @param cardView The card view that has left the screen.
 @see kHorizontalEdgeOffset
*/
- (void)cardDidLeaveLeftEdge:(CardView *)cardView;

/**
 @brief Callback delegate function that is called when the card leaves the right
 side of the screen.
 @param cardView The card view that has left the screen.
 @see kHorizontalEdgeOffset
*/
- (void)cardDidLeaveRightEdge:(CardView *)cardView;

@end