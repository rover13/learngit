#include "sha1.h"
// 32bit字左循环移位的宏
//C++中单斜杠（\）的意思：转义字符；换行的标志（一般在宏定义中）
#define SHA1CircularShift(bits,word) \
                (((word) << (bits)) | ((word) >> (32-(bits))))

//////////////////////////////////////////////////////////////////////////
//  局部函数原型 
//////////////////////////////////////////////////////////////////////////
void SHA1PadMessage(SHA1Context *);    /*  定义填充信息指针  */
void SHA1ProcessMessageBlock(SHA1Context *);

 
//数据初始化操作
int SHA1Reset(SHA1Context *context)
{
    if (!context)
    {
        return shaNull;
    }

    context->Length_Low             = 0;
    context->Length_High            = 0;
    context->Message_Block_Index    = 0;

    context->Intermediate_Hash[0]   = 0x67452301;
    context->Intermediate_Hash[1]   = 0xEFCDAB89;
    context->Intermediate_Hash[2]   = 0x98BADCFE;
    context->Intermediate_Hash[3]   = 0x10325476;
    context->Intermediate_Hash[4]   = 0xC3D2E1F0;

    context->Computed   = 0;
    context->Corrupted  = 0;
    return shaSuccess;
}

//接收单位长度为8字节倍数的消息，处理最后一个分组前面的所有分组
//调用SHA1ProcessMessage
int SHA1Input(SHA1Context *context, const uint8_t *message_array, unsigned length)
{
    if (!length)
    {
        return shaSuccess;
    }

    if (!context || !message_array)	
    {
        return shaNull;
    }

    if (context->Computed)
    {
        context->Corrupted = shaStateError;
        return shaStateError;
    }

    if (context->Corrupted)
    {
         return context->Corrupted;
    }

    while(length-- && !context->Corrupted)	//执行while循环，读取message_array中的每一个字符
    {
		context->Message_Block[context->Message_Block_Index++] = (*message_array & 0xFF);

		context->Length_Low += 8;

		if (context->Length_Low == 0)
		{
			context->Length_High++;

			if (context->Length_High == 0)
			{	
				context->Corrupted = 1;	// Message is too long 
			}
		}

		if (context->Message_Block_Index == 64)
		{
			SHA1ProcessMessageBlock(context);	//处理每一个512bit消息块
		}

		message_array++;	//指针指向下一个字符
		}

		return shaSuccess;
}

//返回一个160bit的消息摘要队列
//调用SHA1PadMessage
int SHA1Result( SHA1Context *context, uint8_t Message_Digest[SHA1HashSize])
{
    int i;
	
    if (!context || !Message_Digest)	
    {
        return shaNull;
    }
	
    if (context->Corrupted)
    {
        return context->Corrupted;
    }
	
    if (!context->Computed)	//执行此处
    {
        SHA1PadMessage(context);	//数据填充模块

        for(i=0; i<64; ++i)
        {
            context->Message_Block[i] = 0;	//消息清零 
        }

        context->Length_Low = 0;	// 长度清零
        context->Length_High = 0;

        context->Computed = 1;
    }
	
    for(i = 0; i < SHA1HashSize; ++i)
    {
		//由Intermediate_Hash[0 ~ 4]得到Message_Digest[0 ~ 40]
        Message_Digest[i] = context->Intermediate_Hash[i>>2] >> 8 * ( 3 - ( i & 0x03 ) );
    }
	
    return shaSuccess;
}

//数据填充模块，被SHA1Result调用
//调用SHA1ProcessMessage
void SHA1PadMessage(SHA1Context *context)
{

    if (context->Message_Block_Index > 55)
    {
        context->Message_Block[context->Message_Block_Index++] = 0x80;
        while(context->Message_Block_Index < 64)
        {
            context->Message_Block[context->Message_Block_Index++] = 0;
        }

        SHA1ProcessMessageBlock(context);	//处理最后一个（含消息长度）512bit消息块
		//处理后context->Message_Block_Index = 0;

        while(context->Message_Block_Index < 56)
        {
            context->Message_Block[context->Message_Block_Index++] = 0;
        }
    }
    else
    {
        context->Message_Block[context->Message_Block_Index++] = 0x80;
        while(context->Message_Block_Index < 56)
        {
            context->Message_Block[context->Message_Block_Index++] = 0;
        }
    }

	//最后64位保存为数据长度
    context->Message_Block[56] = context->Length_High >> 24;
    context->Message_Block[57] = context->Length_High >> 16;
    context->Message_Block[58] = context->Length_High >> 8;
    context->Message_Block[59] = context->Length_High;
    context->Message_Block[60] = context->Length_Low >> 24;
    context->Message_Block[61] = context->Length_Low >> 16;
    context->Message_Block[62] = context->Length_Low >> 8;
    context->Message_Block[63] = context->Length_Low;

    SHA1ProcessMessageBlock(context);	//处理最后一个（含消息长度）512bit消息块
}

// 消息块（固定长度512bit）处理，被SHA1Input，SHA1PadMessage调用
void SHA1ProcessMessageBlock(SHA1Context *context)
{
    const uint32_t K[] = { 
		0x5A827999,
			0x6ED9EBA1,
			0x8F1BBCDC,
			0xCA62C1D6 
	};
	
    int           t;                  // 循环计数 
    uint32_t      temp;               // 临时缓存 
    uint32_t      W[80];              // 字顺序   
    uint32_t      A, B, C, D, E;      // 设置系统磁盘缓存块 
	
	//初始化W队列中的头16个字数据
    for(t = 0; t < 16; t++)
    {
        W[t] = context->Message_Block[t * 4] << 24;
        W[t] |= context->Message_Block[t * 4 + 1] << 16;
        W[t] |= context->Message_Block[t * 4 + 2] << 8;
        W[t] |= context->Message_Block[t * 4 + 3];
    }
	
	//字W[16]~W[79]的生成
    for(t = 16; t < 80; t++)
    {
		W[t] = SHA1CircularShift(1,W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16]);
    }
	
    A = context->Intermediate_Hash[0];
    B = context->Intermediate_Hash[1];
    C = context->Intermediate_Hash[2];
    D = context->Intermediate_Hash[3];
    E = context->Intermediate_Hash[4];
	
	// 定义算法所用之数学函数及其迭代算法描述
    for(t = 0; t < 20; t++)
    {
        temp =  SHA1CircularShift(5,A) + ((B & C) | ((~B) & D)) + E + W[t] + K[0];
        E = D;
        D = C;
        C = SHA1CircularShift(30,B);
		B = A;
        A = temp;
    }
	
    for(t = 20; t < 40; t++)
    {
        temp = SHA1CircularShift(5,A) + (B ^ C ^ D) + E + W[t] + K[1];
        E = D;
        D = C;
        C = SHA1CircularShift(30,B);
        B = A;
        A = temp;
    }
	
    for(t = 40; t < 60; t++)
    {
        temp = SHA1CircularShift(5,A) + ((B & C) | (B & D) | (C & D)) + E + W[t] + K[2];
        E = D;
        D = C;
        C = SHA1CircularShift(30,B);
        B = A;
        A = temp;
    }
	
    for(t = 60; t < 80; t++)
    {
        temp = SHA1CircularShift(5,A) + (B ^ C ^ D) + E + W[t] + K[3];
        E = D;
        D = C;
        C = SHA1CircularShift(30,B);
        B = A;
        A = temp;
    }
	
	// 迭代算法第80步（最后一步）描述
    context->Intermediate_Hash[0] += A;
    context->Intermediate_Hash[1] += B;
    context->Intermediate_Hash[2] += C;
    context->Intermediate_Hash[3] += D;
    context->Intermediate_Hash[4] += E;
	
    context->Message_Block_Index = 0;
}


