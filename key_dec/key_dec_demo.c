#include "key.h"

#include "includes.h"
#include "stm32f0xx_hal.h"
#include "timer.h"




static u8 get_key_id(void);
#define KEY_SCAN_NAME	get_key_id	//按键扫描函数
Def_Key_Scan(KEY_SCAN_NAME);		  //定义，初始化 按键扫描结构 


static u8 key_val_cbuf[KEY_VAL_CBUF_LEN];
static struct cbuf_t key_cbuft; 

static u8 get_key_id(void)
{
	if(HAL_GPIO_ReadPin(KEY_TEST_KEY_PORT, KEY_TEST_KEY_PIN) == GPIO_PIN_RESET){
		return	0;
	}else if(HAL_GPIO_ReadPin(RGB_TEST_KEY_PORT, RGB_TEST_KEY_PIN) == GPIO_PIN_RESET){
		return	1;
	}else if(HAL_GPIO_ReadPin(MMA_TEST_KEY_PORT, MMA_TEST_KEY_PIN) == GPIO_PIN_RESET){
		return	2;
	}else if(HAL_GPIO_ReadPin(GYR_TEST_KEY_PORT, GYR_TEST_KEY_PIN) == GPIO_PIN_RESET){
		return	3;
	}else if(HAL_GPIO_ReadPin(VOL_DEC_KEY_PORT, VOL_DEC_KEY_PIN) == GPIO_PIN_RESET){
		return	4;
	}else{
		return	__NO_KEY;
	}
}

static u8 key_val_put(struct key_val_t *k_val)
{
	ASSERT(k_val);
	return put_fifo(&key_cbuft, (const u8*)(k_val), sizeof(struct key_val_t));
}
u8 key_val_get(struct key_val_t *k_val)
{
	ASSERT(k_val);
	return get_fifo(&key_cbuft, (u8*)(k_val), sizeof(struct key_val_t));
}

static void key_scan_isr_loop(void)
{
	u8 key_id,key_state;
	struct key_val_t k_val;
	u8 ret = 0;
	key_state_detect(Key_hd(KEY_SCAN_NAME));
	GetKeyMsg(KEY_SCAN_NAME,key_id,key_state);
	if(key_id != __NO_KEY){
		k_val.key_id =  key_id;
		k_val.state  =  key_state;
		ret = key_val_put(&k_val);
		if(ret == 0){
			ERR_printf(ret);
		}
	}
}



void key_detect_init(void)
{
	cbuffer_init(&key_cbuft, key_val_cbuf, KEY_VAL_CBUF_LEN);
	register_timer1_handler_malloc(key_scan_isr_loop,10);
}






