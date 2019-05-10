#ifndef __KEY_DEC_H
#define __KEY_DEC_H
#include "includes.h"
#include "key.h"
#define __NO_KEY  NO_KEY



#define DOUBLE_KEY_EN       1

#define KEY_FILTER_TIME     5      //按键消抖时间 10ms
#define KEY_LONG_TIME       400    //按键长按时间 2s
#define KEY_REPEAT_TIME     (KEY_LONG_TIME+100)     
#define KEY_DOUBLE_MIN      10     //双击按键最小间隔 100ms
#define KEY_DOUBLE_MAX      350     //双击按键最大间隔 300ms


typedef enum _key_msg{
    KEY_NULL, 
    KEY_SHORT,
    KEY_LONG,
    KEY_DOUBLE,
    KEY_REPEAT,
    KEY_REPEAT_UP,
}key_msg_e;


typedef struct _key_status{
    u8 c_val;         		//当前键值  
    u8 b_val;         		//上一次的键值
    u8 msg_keynum;
    u16 count;           	//计数器    
    u16 double_key_cnt;  	//double key间隔  
    key_msg_e msg_state; 	//
	key_msg_e key_state;		
    u8(*get_key_val)(void);
}key_status_t; 





/*检测按键状态 */
void key_state_detect(key_status_t *skey_t);





#define GetKeyMsg(fun_name,key_val,key_state)       \
 do{                                                \
    key_val   = key_##fun_name.msg_keynum;       \
    key_state = key_##fun_name.msg_state;   \
    if(key_state != KEY_NULL)               \
		key_##fun_name.msg_keynum = __NO_KEY;    \
    key_##fun_name.msg_state = KEY_NULL;    \
 }while(0)

#define Key_hd(fun_name)	(&key_##fun_name)
#define Def_Key_Scan(fun_name) \
key_status_t key_##fun_name = \
{NO_KEY, \
 NO_KEY, \
 NO_KEY, \
 0,\
 0,\
 KEY_NULL,\
 KEY_NULL,\
 fun_name}






#endif
