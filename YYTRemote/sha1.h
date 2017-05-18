//消息长度小于2的64bit，即2的61次方（24296075564733693952）个字符

#ifndef _SHA1_H_
#define _SHA1_H_

#include "stdint.h"

#ifndef _SHA_enum_
#define _SHA_enum_
enum
{
    shaSuccess = 0,
	shaNull,             // 空指示参量 
	shaInputTooLong,     // 输入数据太长提示 
	shaStateError        // called Input after Result --以输入结果命名之 
};
#endif

#define SHA1HashSize 20
//////////////////////////////////////////////////////////////////////////
// 控制上下文消息的结构
//////////////////////////////////////////////////////////////////////////
typedef struct SHA1Context
{
	//typedef unsigned uint32_t; unsigned为unsigned int（4字节，范围0 ~ 4294967295）
    uint32_t Intermediate_Hash[SHA1HashSize/4];	// Message Digest  
	
    uint32_t Length_Low;             // Message length in bits      
    uint32_t Length_High;            // Message length in bits      
	
	// typedef short int_least16_t; short为short int（2字节，范围-32768 ~ 32767） 
    int_least16_t Message_Block_Index;  // Index into message block array   

	//typedef unsigned char uint8_t; （1字节，范围0 ~ 255）
    uint8_t Message_Block[64];       // 512-bit message blocks      
	
    int Computed;                // Is the digest computed?         
    int Corrupted;              // Is the message digest corrupted? 
} SHA1Context;
//////////////////////////////////////////////////////////////////////////
//函数原型
//////////////////////////////////////////////////////////////////////////
int SHA1Reset(SHA1Context *);
int SHA1Input(SHA1Context *, const uint8_t *, unsigned int);
int SHA1Result( SHA1Context *, uint8_t Message_Digest[SHA1HashSize]);

#endif /*_SHA1_H_*/
