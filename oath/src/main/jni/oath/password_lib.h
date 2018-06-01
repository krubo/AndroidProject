/*
**********************************************************************
Copyright (C) 2017-2027, lianluo company
All rights reserved.
File Name : analysis_password.h
Description: analysis password 
Others : none
Version : 0.0.1
Author : zj
Date : 2017-5-2
**********************************************************************
*/

#ifndef _PASSWORD_LIB_H
#define _PASSWORD_LIB_H
#include "stdint.h"
#include "stdbool.h"

/* LOCK PASSWORD ENUM */
typedef enum{
LOCK_SINGLE_PSD=0,     						 
LOCK_LIMIT_TIME_PWD,
LOCK_LIMIT_TIME_AND_DEL_PWD,
LOCK_PERMANENT_PWD,
LOCK_PERMANENT_AND_DEL_PWD,
LOCK_CYCLE_0_9_PWD,
LOCK_CYCLE_10_19_PWD,
LOCK_CYCLE_20_23_PWD,
LOCK_BACKUP_PWD,
LOCK_BACKUP_2_PWD,
}LOCK_PSD_TYPE_ENUM;

/* WEEK ENUM */
typedef enum{
CYCLE_EVERYDAY=0,     			 		   
CYCLE_WORKDAY,     			 			 	 
CYCLE_WEEKENDDAY,    			 			 
CYCLE_SUNDAY,     			 				 
CYCLE_SATURDAY,     				 		 
CYCLE_FRIDAY,     		 					 
CYCLE_THURDAY,     				 			 
CYCLE_WEDNESDAY,     						 
CYCLE_TUESDAY,     				 			 
CYCLE_MONDAY,    						 
}WEEK_ENUM;

typedef enum{
PASSWORD_LEN_4=4,
PASSWORD_LEN_6=6,
PASSWORD_LEN_7=7,
PASSWORD_LEN_8=8,
PASSWORD_LEN_9=9,
}LOCK_PWD_LEN_ENUM;

extern bool decoding_password(const uint8_t *ciphertext,uint8_t *password,uint8_t len);
extern bool decoding_password_twice(const uint8_t *password,uint8_t type,uint8_t pwd_len,uint32_t sys_timer,uint32_t* start_timer,bool del_pwd,uint8_t pwd_type);
extern bool timer_syn_verify(const uint8_t *psd, uint32_t app_timer,uint8_t psd_len);
//∂ØÃ¨—È÷§√‹¬Î
extern bool dynamic_verify(const uint8_t *psd, uint32_t sys_timer,uint8_t psd_len);
extern bool dynamic_verify_once(const uint8_t *psd, uint32_t sys_timer,uint8_t psd_len,uint32_t* start_timer);
extern bool app_get_dev_dynamic(uint8_t *psd,uint32_t sys_timer);
#endif //_PASSWORD_LIB_H
