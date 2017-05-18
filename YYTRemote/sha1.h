//��Ϣ����С��2��64bit����2��61�η���24296075564733693952�����ַ�

#ifndef _SHA1_H_
#define _SHA1_H_

#include "stdint.h"

#ifndef _SHA_enum_
#define _SHA_enum_
enum
{
    shaSuccess = 0,
	shaNull,             // ��ָʾ���� 
	shaInputTooLong,     // ��������̫����ʾ 
	shaStateError        // called Input after Result --������������֮ 
};
#endif

#define SHA1HashSize 20
//////////////////////////////////////////////////////////////////////////
// ������������Ϣ�Ľṹ
//////////////////////////////////////////////////////////////////////////
typedef struct SHA1Context
{
	//typedef unsigned uint32_t; unsignedΪunsigned int��4�ֽڣ���Χ0 ~ 4294967295��
    uint32_t Intermediate_Hash[SHA1HashSize/4];	// Message Digest  
	
    uint32_t Length_Low;             // Message length in bits      
    uint32_t Length_High;            // Message length in bits      
	
	// typedef short int_least16_t; shortΪshort int��2�ֽڣ���Χ-32768 ~ 32767�� 
    int_least16_t Message_Block_Index;  // Index into message block array   

	//typedef unsigned char uint8_t; ��1�ֽڣ���Χ0 ~ 255��
    uint8_t Message_Block[64];       // 512-bit message blocks      
	
    int Computed;                // Is the digest computed?         
    int Corrupted;              // Is the message digest corrupted? 
} SHA1Context;
//////////////////////////////////////////////////////////////////////////
//����ԭ��
//////////////////////////////////////////////////////////////////////////
int SHA1Reset(SHA1Context *);
int SHA1Input(SHA1Context *, const uint8_t *, unsigned int);
int SHA1Result( SHA1Context *, uint8_t Message_Digest[SHA1HashSize]);

#endif /*_SHA1_H_*/
