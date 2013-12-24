/*
 * Macro.h
 *
 *  Created on: 2010-8-18
 *      Author: panda
 */

#ifndef MACRO_H_
#define MACRO_H_

//屏幕分辨率
#define SCREEN_WIDTH 360
#define SCREEN_HEIGHT 640
//初始化时第一个worldobject的center位置
#define FIRST_CENTER_AXIS_Y  95
//初始化时最后一个worldobject的center位置
//#define Y_AXIS_BEGIN   585

//队列在最老元素center值为此时更新一次队列
#define Y_AXIS_REPLACE_POSITION  495


//每个center之间的间隔
#define CENTER_SPAN_AXIS_Y   70

//可见区域Y轴最大值
#define Y_AXIS_MAX_LIMIT   530
//可见区域Y轴最小值
#define Y_AXIS_MIN_LIMIT   60

//上限上针板的高度，用于判断Man首先被刺的位置
#define Y_UP_LIMIT_HEIGHT    15
//队列对象个数
#define QUEUE_ELEMENTS_COUNT 8

//每一帧worldobject的Y轴速度
#define SCROLL_SPEED_HIGH  5
#define SCROLL_SPEED       3
#define SCROLL_SPEED_SLOW  1
//当刚进入游戏界面时，暂时让游戏速度保持低速
#define SLOW_SPEED_LIMID_TICKS 100

//worldobject的X轴随机大小的范围
#define X_AXIS_MIN     48
#define X_AXIS_SPAN   264
//每秒包含微秒数
#define KONE_SECOND_IN_MICRO_SECONDS  1000000
//游戏初始帧数 
#define KFRAMES_PER_SECOND  35
//scroll速度 以10层为一个单位，然后再根据游戏难度决定变化快慢
#define SCROLL_CHANGE_UNIT_BY_FLOORS  40
//
#define TICKS_MAX_FRAMES  80
#define MAN_LIVES  1
//重力加速度
#define GRAVITY_ACCELERATION_SCROLL 3
#define GRAVITY_INITIAL_VELOCITY    3
//Man的X轴正常行走速度
#define MAN_X_VELOCITY  10
#define CONVEY_BOARD_VELOCITY 5
//弹簧板给Man 的Y轴初速度
#define SPRING_BOARD_BELOCITY -20
//两边墙的宽度
#define WIDTH_WALL   15
//Tick相关
//Man 受伤后恢复时间 1/2秒
#define TICKS_SPAN_OF_HURTING 15
//Man生命值复原的频率
#define TICKS_LIFE_RECOVERY   60
//菜单中选项进入位置的速度
#define MENU_OPTION_VELOCITY  45
#define MENU_EXPAND_MAX       20
//菜单中心向左偏移的最大值
#define MENU_LEFT_MAX_OFFSET         40

//目录布局
#define FIRST_MENU_HEIGHT       180
#define MENU_HEIGHT_SPAN            55
#define FIRST_MENU_POSITION     460
#define MENU_WIGTH_SPAN             40
//MotionElement 移动速度
#define MOTION_EASTWEST_RECOVERY    20
#define MOTION_SOUTHNORTH_RECONVERY 4
//该值用于控制两个BitMap之间的距离，用于增大间隙
#define MOTION_EASTWEST_SPAN       30
#define MOTION_SOUTHNORTH_SPAN     5
//最后一个Player de Score存的是Option信息
#define DEFAULT_OPTION_VALUE      1205
#define AWARD_PLAYER_COUNT        11
#define MAX_NAME_LENGTH           15
#define MAX_LINES_COUNTS          100
typedef TBuf<1500>*               PBufText;
typedef TBuf<1500>                BufText;
//控制Help 和  About的显示区域
#define TEXT_DISPLAY_MIN_Y    120
#define TEXT_DISPLAY_MAX_Y    560
#define TEXT_LINE_HEIGHT      30
//每一行能够显示的最大的宽度,根据宽度计算，来控制中间对齐显示
#define MAX_PIXELS_ONE_LINE    358
//能够显示的最大行数
#define MAX_LINES   17
#endif /* MACRO_H_ */
