/*
 * Macro.h
 *
 *  Created on: 2010-8-18
 *      Author: panda
 */

#ifndef MACRO_H_
#define MACRO_H_

//��Ļ�ֱ���
#define SCREEN_WIDTH 360
#define SCREEN_HEIGHT 640
//��ʼ��ʱ��һ��worldobject��centerλ��
#define FIRST_CENTER_AXIS_Y  95
//��ʼ��ʱ���һ��worldobject��centerλ��
//#define Y_AXIS_BEGIN   585

//����������Ԫ��centerֵΪ��ʱ����һ�ζ���
#define Y_AXIS_REPLACE_POSITION  495


//ÿ��center֮��ļ��
#define CENTER_SPAN_AXIS_Y   70

//�ɼ�����Y�����ֵ
#define Y_AXIS_MAX_LIMIT   530
//�ɼ�����Y����Сֵ
#define Y_AXIS_MIN_LIMIT   60

//���������ĸ߶ȣ������ж�Man���ȱ��̵�λ��
#define Y_UP_LIMIT_HEIGHT    15
//���ж������
#define QUEUE_ELEMENTS_COUNT 8

//ÿһ֡worldobject��Y���ٶ�
#define SCROLL_SPEED_HIGH  5
#define SCROLL_SPEED       3
#define SCROLL_SPEED_SLOW  1
//���ս�����Ϸ����ʱ����ʱ����Ϸ�ٶȱ��ֵ���
#define SLOW_SPEED_LIMID_TICKS 100

//worldobject��X�������С�ķ�Χ
#define X_AXIS_MIN     48
#define X_AXIS_SPAN   264
//ÿ�����΢����
#define KONE_SECOND_IN_MICRO_SECONDS  1000000
//��Ϸ��ʼ֡�� 
#define KFRAMES_PER_SECOND  35
//scroll�ٶ� ��10��Ϊһ����λ��Ȼ���ٸ�����Ϸ�ѶȾ����仯����
#define SCROLL_CHANGE_UNIT_BY_FLOORS  40
//
#define TICKS_MAX_FRAMES  80
#define MAN_LIVES  1
//�������ٶ�
#define GRAVITY_ACCELERATION_SCROLL 3
#define GRAVITY_INITIAL_VELOCITY    3
//Man��X�����������ٶ�
#define MAN_X_VELOCITY  10
#define CONVEY_BOARD_VELOCITY 5
//���ɰ��Man ��Y����ٶ�
#define SPRING_BOARD_BELOCITY -20
//����ǽ�Ŀ��
#define WIDTH_WALL   15
//Tick���
//Man ���˺�ָ�ʱ�� 1/2��
#define TICKS_SPAN_OF_HURTING 15
//Man����ֵ��ԭ��Ƶ��
#define TICKS_LIFE_RECOVERY   60
//�˵���ѡ�����λ�õ��ٶ�
#define MENU_OPTION_VELOCITY  45
#define MENU_EXPAND_MAX       20
//�˵���������ƫ�Ƶ����ֵ
#define MENU_LEFT_MAX_OFFSET         40

//Ŀ¼����
#define FIRST_MENU_HEIGHT       180
#define MENU_HEIGHT_SPAN            55
#define FIRST_MENU_POSITION     460
#define MENU_WIGTH_SPAN             40
//MotionElement �ƶ��ٶ�
#define MOTION_EASTWEST_RECOVERY    20
#define MOTION_SOUTHNORTH_RECONVERY 4
//��ֵ���ڿ�������BitMap֮��ľ��룬���������϶
#define MOTION_EASTWEST_SPAN       30
#define MOTION_SOUTHNORTH_SPAN     5
//���һ��Player de Score�����Option��Ϣ
#define DEFAULT_OPTION_VALUE      1205
#define AWARD_PLAYER_COUNT        11
#define MAX_NAME_LENGTH           15
#define MAX_LINES_COUNTS          100
typedef TBuf<1500>*               PBufText;
typedef TBuf<1500>                BufText;
//����Help ��  About����ʾ����
#define TEXT_DISPLAY_MIN_Y    120
#define TEXT_DISPLAY_MAX_Y    560
#define TEXT_LINE_HEIGHT      30
//ÿһ���ܹ���ʾ�����Ŀ��,���ݿ�ȼ��㣬�������м������ʾ
#define MAX_PIXELS_ONE_LINE    358
//�ܹ���ʾ���������
#define MAX_LINES   17
#endif /* MACRO_H_ */
