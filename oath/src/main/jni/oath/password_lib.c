/*
**********************************************************************
Copyright (C) 2017-2027, lianluo company
All rights reserved.
File Name : analysis_password.c
Description: analysis password 
Others : none
Version : 0.0.1
Author : zj
Date : 2017-5-2
**********************************************************************
*/
#include "oath.h"
#include "time.h"
#include "stdint.h"
#include "stdbool.h"
#include "password_lib.h"
#include <stdio.h>

#define SECRET_LEN  			32
#define SECRET_WINDOW_10 	10
#define SECRET_WINDOW_1 	1
#define SECRET_T0  				0
#define SECRET_TIME_STEP_SIZE_HOUR  				1 /* 1Сʱ */
#define SECRET_TIME_STEP_SIZE_SECONDS  			30
#define SECOND_2017  			1483200000 

const char pass_add[10][6]=
	{
		"HelLo!",
		"Y&Uji3",
		"DeG3wx",
		"W3d8$5",
		"FD8uck",
		"984@rt",
		"Vgj#.j",
		"aJH3k_",
		"wKds#F",
		"ldk@KD",
	};
const char pass1_buf[10] ={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x00,0x03,0x04};
char g_secret_32[33] = "7F701FB0D69D247D63F50983C908E122"; 
/* ���ݽ��� */
bool decoding_password(const uint8_t *ciphertext,uint8_t *password,uint8_t len)	
{
  uint8_t ciphertext_buf[10] ={0};
	uint8_t index = 0,flag = 1;
	uint8_t dynamic_k = 4;
	
	if(len < 6 || len > 10)
	{
		return false;
	}
	memcpy(ciphertext_buf,ciphertext,len);

	/* תΪ���� */	/* ��ȡ��̬k */
	for(index = 0;index < len ;index ++)
	{
			ciphertext_buf[index]=(ciphertext_buf[index]&0x0F);
			if((index < 4)&&(flag == 1)&&(ciphertext_buf[index] < 8 ))
			{
				dynamic_k = ciphertext_buf[index];
				flag = 0;
			}
	}
	/* ��һ����� */
	for(index = 4;index < len ;index ++)
	{
			if(ciphertext_buf[index] < 8)
			{
				ciphertext_buf[index] = ciphertext_buf[index]^dynamic_k;
			}
	}
	
	/* �ڶ������ */
	for(index = 0;index < len ;index ++)
	{
			if(ciphertext_buf[index] < 8)
			{
				//ciphertext_buf[index] = ciphertext_buf[index]^pass2_buf[index];
				ciphertext_buf[index] = ciphertext_buf[index]^pass1_buf[index];
			}
			password[index] = ciphertext_buf[index]|0x30;
	}
	return true;
}


/* ���� */
bool decoding_password_twice(const uint8_t *password,uint8_t type,uint8_t pwd_len,uint32_t sys_timer,uint32_t* start_timer,bool del_pwd,uint8_t pwd_type)
{
		oath_rc rc;
		char  index = 0;
	
		if(pwd_len > 9|| pwd_len < 6)
		{
					return false;
		}
		
		if(type == 4)
		{
				char psd[5] ={0}; 
				char g_secret_diff[38]={0};
				
				memcpy(g_secret_diff,g_secret_32,32);
				for(index = 0; index < 6; index ++) //����ʱ��
				{
					g_secret_diff[(index+1)*5 -1] = pass_add[pwd_type][index];
				}
				memcpy(g_secret_diff+32,password+4,pwd_len-4);
				memcpy(psd ,password,PASSWORD_LEN_4);
				g_secret_diff[SECRET_LEN + pwd_len-4]='\0';
#if 0			
				printf("g_secret_diff=%s\r\n",g_secret_diff);
				printf("password=%s\r\n",password);
				printf("len=%d\r\n",(SECRET_LEN + pwd_len-4));
				printf("sys_timer=%d\r\n",sys_timer);
#endif				
				if(del_pwd)
				{
						for(index = 0; index < 24; index ++) //����ʱ��
						{
							rc = (oath_rc)oath_totp_validate2(g_secret_diff,(SECRET_LEN + pwd_len-4),((sys_timer/3600) - index),SECRET_TIME_STEP_SIZE_HOUR,SECRET_T0,SECRET_WINDOW_1,NULL,psd);
							if (rc == OATH_OK)
							{
								*start_timer  =((sys_timer/3600  - index)*3600);
								return true;
							}
					  }
				}else
				{
					for(index = 0; index < 24; index ++) //����ʱ��
					{
						rc = (oath_rc)oath_totp_validate(g_secret_diff,(SECRET_LEN + pwd_len-4),((sys_timer/3600) - index),SECRET_TIME_STEP_SIZE_HOUR,SECRET_T0,SECRET_WINDOW_1,psd);
						if (rc == OATH_OK)
						{
							*start_timer  =((sys_timer/3600  - index)*3600);
							return true;
						}
				 }
				}
			return false;
	 }else //8λ����
		{
			 char psd[8] ={0};
			 char g_secret_32_bck[35] = {0},index = 0,dynamic_num = 0;
			 memcpy(g_secret_32_bck,g_secret_32,32);
			 for(index = 0; index < 6; index ++) //����ʱ��
			 {
					g_secret_32_bck[(index+1)*5 -1] = pass_add[pwd_type][index];
			 }
			 dynamic_num = password[PASSWORD_LEN_7-1];
			 memcpy(psd ,password,PASSWORD_LEN_7);
			 psd[PASSWORD_LEN_7-1] = '\0';
			 
			 if(del_pwd)
				{
						for(index = 0; index < 24; index ++) //����ʱ��
						{
//							rc = (oath_rc)oath_totp_validate2(g_secret_32,SECRET_LEN,((sys_timer/3600) - index),SECRET_TIME_STEP_SIZE_HOUR,SECRET_T0,SECRET_WINDOW_1,NULL,psd);
//							if (rc == OATH_OK)
//							{
//								*start_timer  =((sys_timer/3600  - index)*3600);
//								return true;
//							}else
//							{
								g_secret_32_bck[32]='0';
								g_secret_32_bck[33]=dynamic_num;
								
								rc = (oath_rc)oath_totp_validate2(g_secret_32_bck,(SECRET_LEN+2),((sys_timer/3600) - index),SECRET_TIME_STEP_SIZE_HOUR,SECRET_T0,SECRET_WINDOW_1,NULL,(char*)psd);
								if (rc == OATH_OK)
								{
									*start_timer  =((sys_timer/3600  - index)*3600);
									return true;
								}else
								{
									g_secret_32_bck[32]='1';
									rc = (oath_rc)oath_totp_validate2(g_secret_32_bck,(SECRET_LEN+2),((sys_timer/3600) - index),SECRET_TIME_STEP_SIZE_HOUR,SECRET_T0,SECRET_WINDOW_1,NULL,(char*)psd);
									if (rc == OATH_OK)
									{
										*start_timer  =((sys_timer/3600  - index)*3600);
										return true;
									}
							 }
							//}
					  }
				}else
				{
					for(index = 0; index < 24; index ++) //����ʱ��
					{
//						rc = (oath_rc)oath_totp_validate(g_secret_32,SECRET_LEN,((sys_timer/3600) - index),SECRET_TIME_STEP_SIZE_HOUR,SECRET_T0,SECRET_WINDOW_1,psd);
//						if (rc == OATH_OK)
//						{
//							//gt_lock_pwd.start_timestamp  =(gt_param.time_stamp - 3600*index);
//							*start_timer   =((sys_timer /3600  - index)*3600);
//							return true;
//						}else
//						{
						  	g_secret_32_bck[32]='0';
								g_secret_32_bck[33]=dynamic_num;
								rc = (oath_rc)oath_totp_validate(g_secret_32_bck,(SECRET_LEN+2),((sys_timer/3600) - index),SECRET_TIME_STEP_SIZE_HOUR,SECRET_T0,SECRET_WINDOW_1,(char*)psd);
								if (rc == OATH_OK)
								{
									*start_timer   =((sys_timer /3600  - index)*3600);
									return true;
								}else
								{
									g_secret_32_bck[32]='1';
									
									rc = (oath_rc)oath_totp_validate(g_secret_32_bck,(SECRET_LEN+2),((sys_timer/3600) - index),SECRET_TIME_STEP_SIZE_HOUR,SECRET_T0,SECRET_WINDOW_1,(char*)psd);
									if (rc == OATH_OK)
									{
										*start_timer   =((sys_timer /3600  - index)*3600);
										return true;
									}
								}
						//}
					}
		   }
			if (rc == OATH_OK)
			{
					return true;
			}
			else
			{	
				return false;
			}
		}
}	
//����ʱ��������֤
bool timer_syn_verify(const uint8_t *psd, uint32_t app_timer,uint8_t psd_len)
{
		uint8_t password[10] = {0};
		oath_rc rc;
		
		if(psd_len > PASSWORD_LEN_9 || psd_len < 6)
		{
			return false;
		}
		memcpy(password,psd,psd_len);
		password[psd_len] = '\0';
		g_secret_32[32] = '\0';

		app_timer += SECOND_2017;
		rc = (oath_rc)oath_totp_validate(g_secret_32,SECRET_LEN,app_timer,SECRET_TIME_STEP_SIZE_SECONDS,SECRET_T0, SECRET_WINDOW_1,(char*)password);			
		if(rc == OATH_OK)
		{	
			return true;
		}
	return false;
}

//��̬��֤����
bool dynamic_verify(const uint8_t *psd, uint32_t sys_timer,uint8_t psd_len)
{
		uint8_t password[10] = {0};
		oath_rc rc;
		
		if(psd_len > PASSWORD_LEN_9|| psd_len < PASSWORD_LEN_6)
		{
			return false;
		}
		memcpy(password,psd,psd_len);
		password[psd_len] = '\0';//ĩβ�ӽ�����
		g_secret_32[32] = '\0';//ĩβ�ӽ�����

		rc = (oath_rc)oath_totp_validate(g_secret_32,SECRET_LEN,sys_timer,SECRET_TIME_STEP_SIZE_SECONDS,SECRET_T0, SECRET_WINDOW_1,(char*)password);
		if(rc == OATH_OK)
		{	
			return true;
		}
	return false;
}
//��̬��֤����
bool dynamic_verify_once_test(uint8_t *psd, uint32_t sys_timer,uint8_t psd_len)
{
		uint8_t password[10] = {0};
		char g_secret_32_bck[35] = {0},index = 0;
		oath_rc rc;
		
		if(psd_len > PASSWORD_LEN_9 || psd_len < PASSWORD_LEN_6)
		{
			return false;
		}
		
		memcpy(g_secret_32_bck,g_secret_32,32);

		g_secret_32_bck[32]= (index/10 + 0x30);
		g_secret_32_bck[33]= (index%10 + 0x30);
		
		rc = (oath_rc)oath_totp_generate(g_secret_32_bck,(SECRET_LEN+2),(1498642289/3600),SECRET_TIME_STEP_SIZE_HOUR,SECRET_T0,8,(char*)password);
		memcpy(psd,password,8);
		if (rc == OATH_OK)
		{
			return true;
		}
	return false;
}


bool app_get_dev_dynamic(uint8_t *psd,uint32_t sys_timer)
{
		uint8_t password[10] = {0};
		oath_rc rc;
		
		g_secret_32[32] = '\0';
		rc = (oath_rc)oath_totp_generate2(g_secret_32,SECRET_LEN,sys_timer,SECRET_TIME_STEP_SIZE_SECONDS,SECRET_T0,8,OATH_TOTP_HMAC_SHA256,(char*)password);
		memcpy(psd,password,8);
		if (rc == OATH_OK)
		{
			return true;
		}
	return false;
}
//��̬��֤����
bool dynamic_verify_once(const uint8_t *psd, uint32_t sys_timer,uint8_t psd_len,uint32_t* start_timer)
{
		uint8_t password[10] = {0},dynamic_num = 0,index = 0;					
		char g_secret_32_bck[35] = {0};
		oath_rc rc;
	
		if(psd_len > PASSWORD_LEN_9 || psd_len < PASSWORD_LEN_6)
		{
			return false;
		}
		dynamic_num =psd[psd_len-1]; 
		memcpy(password,psd,psd_len-1);
		password[psd_len-1] = '\0';//ĩβ�ӽ�����
		g_secret_32[32] = '\0';//ĩβ�ӽ�����
		memcpy(g_secret_32_bck,g_secret_32,32);
		
		for(index = 0; index < 6; index ++) //����ʱ��
		{
			g_secret_32_bck[(index+1)*5 -1] = pass_add[0][index];
		}
		
		for(index = 0; index < 6; index ++) //����ʱ��
		{
//		  rc = (oath_rc)oath_totp_validate(g_secret_32,SECRET_LEN,sys_timer/3600,SECRET_TIME_STEP_SIZE_HOUR,SECRET_T0, SECRET_WINDOW_1,(char*)password);
//			if(rc == OATH_OK)
//			{	
//				*start_timer  =((sys_timer/3600  - index)*3600);
//				return true;
//			}else
//			{
			
				g_secret_32_bck[32]='0';
				g_secret_32_bck[33]=dynamic_num;
				g_secret_32_bck[34] = '\0';
				rc = (oath_rc)oath_totp_validate(g_secret_32_bck,34,((sys_timer/3600) - index),SECRET_TIME_STEP_SIZE_HOUR,SECRET_T0,SECRET_WINDOW_1,(char*)password);
				if (rc == OATH_OK)
				{
					*start_timer  =((sys_timer/3600  - index)*3600);
					return true;
				}else
				{
					*start_timer  =((sys_timer/3600  - index)*3600);
					g_secret_32_bck[32]='1';
					rc = (oath_rc)oath_totp_validate(g_secret_32_bck,34,((sys_timer/3600) - index),SECRET_TIME_STEP_SIZE_HOUR,SECRET_T0,SECRET_WINDOW_1,(char*)password);
					if (rc == OATH_OK)
					{
						return true;
					}
				}
			//}					
		}
	return false;
}

