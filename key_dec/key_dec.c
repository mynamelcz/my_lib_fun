#include "key_dec.h"





void key_state_detect(key_status_t *skey_t)
{
#if (DOUBLE_KEY_EN==1)  
    static u8 double_key_bck = __NO_KEY;
#endif
    if(skey_t == NULL)
        return;
    skey_t->c_val = skey_t->get_key_val();  
    if(skey_t->c_val != __NO_KEY){   /* 按键按下 */
        if(skey_t->b_val == __NO_KEY){
            skey_t->b_val = skey_t->c_val;
            skey_t->count = 0;
            skey_t->key_state = KEY_NULL;
        }
        skey_t->count++;
        if(skey_t->count == KEY_FILTER_TIME){
            skey_t->key_state = KEY_SHORT;
        }
#if (DOUBLE_KEY_EN==1)                
        if(skey_t->double_key_cnt > KEY_DOUBLE_MIN){
            skey_t->key_state = KEY_DOUBLE;
        }
#endif

#if(LONG_KEY_EN)				
        if(skey_t->count == KEY_LONG_TIME){
            skey_t->key_state = KEY_LONG;
			/*========  >>>>长按<<<<   =====*/
            skey_t->msg_state = KEY_LONG; 
            skey_t->msg_keynum = skey_t->b_val;			
        }
#endif

#if(REPEAT_KEY_EN)				
        if(skey_t->count == KEY_LONG_TIME + KEY_REPEAT_TIME){
            skey_t->key_state = KEY_REPEAT;
            skey_t->count = KEY_LONG_TIME;
            /*======== >>>> 连按 <<<<   =====*/
            skey_t->msg_state = skey_t->key_state; 
            skey_t->msg_keynum = skey_t->c_val;
        }
#endif
				
    }else{                                 
        if(skey_t->b_val != __NO_KEY){ /* 按键抬起 */
            switch(skey_t->key_state){
#if(REPEAT_KEY_EN)								
                case KEY_REPEAT:
					/*======== >>>> 连按 抬起 <<<<   =====*/
                    skey_t->msg_state = KEY_REPEAT_UP; 
                    skey_t->msg_keynum = skey_t->b_val;
                    break;
#endif
							
#if(LONG_KEY_EN)
 //               case KEY_LONG:
 //                  skey_t->msg_state = KEY_LONG; 
 //                  skey_t->msg_keynum = skey_t->b_val;
 //                  break;							
#endif
								
#if(DOUBLE_KEY_EN)
                case KEY_SHORT:
                    skey_t->double_key_cnt = 1; 
                    double_key_bck = skey_t->b_val;
                    break;
                case KEY_DOUBLE:
                    double_key_bck = __NO_KEY;
                    skey_t->double_key_cnt = 0; 
					 /*========  >>>>双击<<<<   =====*/
					skey_t->msg_state = KEY_DOUBLE; 
                    skey_t->msg_keynum = skey_t->b_val;
                    break;
#else
                case KEY_SHORT:
			        /*========  >>>>短按<<<<    =====*/
                    skey_t->msg_state = KEY_SHORT; 
                    skey_t->msg_keynum = skey_t->b_val;
                    break;
#endif
				default:
					break;
 

            }
            skey_t->key_state = KEY_NULL;
            skey_t->b_val = __NO_KEY;
            skey_t->count = 0;
        }

    }
    
#if (DOUBLE_KEY_EN==1)                
    if(skey_t->double_key_cnt){
        skey_t->double_key_cnt++;
        if(skey_t->double_key_cnt > KEY_DOUBLE_MAX){
            skey_t->key_state = KEY_NULL;
            skey_t->b_val = __NO_KEY;
            skey_t->double_key_cnt = 0;
            /*========  >>>>短按<<<<    =====*/
            skey_t->msg_state = KEY_SHORT; 
            skey_t->msg_keynum = double_key_bck;
            double_key_bck = __NO_KEY;
        }
    } 
#endif
}













