#ifndef __KEY_DEC_H
#define __KEY_DEC_H
#include "includes.h"
#include "key.h"
#define __NO_KEY  NO_KEY



#define DOUBLE_KEY_EN       1

#define KEY_FILTER_TIME     5      //��������ʱ�� 10ms
#define KEY_LONG_TIME       400    //��������ʱ�� 2s
#define KEY_REPEAT_TIME     (KEY_LONG_TIME+100)     
#define KEY_DOUBLE_MIN      10     //˫��������С��� 100ms
#define KEY_DOUBLE_MAX      350     //˫����������� 300ms


typedef enum _key_msg{
    KEY_NULL, 
    KEY_SHORT,
    KEY_LONG,
    KEY_DOUBLE,
    KEY_REPEAT,
    KEY_REPEAT_UP,
}key_msg_e;


typedef struct _key_status{
    u8 c_val;         		//��ǰ��ֵ  
    u8 b_val;         		//��һ�εļ�ֵ
    u8 msg_keynum;
    u16 count;           	//������    
    u16 double_key_cnt;  	//double key���  
    key_msg_e msg_state; 	//
	key_msg_e key_state;		
    u8(*get_key_val)(void);
}key_status_t; 





/*��ⰴ��״̬ */
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
