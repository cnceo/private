// --------------------------------------------------------
/*Copyright KeyeLeo.All rights reserved.
 *
 *File		: md5_generate.cpp
 *Desc		: 
 *Version	: 1.0
 *Program	: KeyeLeo
 *Date		: 2012-09-09
 */
// --------------------------------------------------------
#include "stdafx.h"
#include <keye/utility/utility_fwd.h>
/*
#include <stdio.h>
#include <string.h>
#include <string>
#include "CMD5Encrypt.h"
*/
// --------------------------------------------------------
//!数据大小
#define ENCRYPT_KEY_LEN					5									//!密钥长度

//////////////////////////////////////////////////////////////////////////////////////////////////////////////!

#define S11		7
#define S12		12
#define S13		17
#define S14		22
#define S21		5
#define S22		9
#define S23 	14
#define S24 	20
#define S31 	4
#define S32 	11
#define S33 	16
#define S34 	23
#define S41 	6
#define S42 	10
#define S43 	15
#define S44 	21

#define F(x,y,z) (((x)&(y))|((~x)&(z)))
#define G(x,y,z) (((x)&(z))|((y)&(~z)))
#define H(x,y,z) ((x)^(y)^(z))
#define I(x,y,z) ((y)^((x)|(~z)))

#define ROTATE_LEFT(x,n) (((x)<<(n))|((x)>>(32-(n))))

#define FF(a,b,c,d,x,s,ac)													\
{																			\
	(a)+=F((b),(c),(d))+(x)+(unsigned long int)(ac);						\
	(a)=ROTATE_LEFT((a),(s));												\
	(a)+=(b);																\
}

#define GG(a,b,c,d,x,s,ac)													\
{																			\
	(a)+=G((b),(c),(d))+(x)+(unsigned long int)(ac);						\
	(a)=ROTATE_LEFT ((a),(s));												\
	(a)+=(b);																\
}

#define HH(a,b,c,d,x,s,ac)													\
{																			\
	(a)+=H((b),(c),(d))+(x)+(unsigned long int)(ac);						\
	(a)=ROTATE_LEFT((a),(s));												\
	(a)+=(b);																\
}

#define II(a,b,c,d,x,s,ac)													\
{																			\
	(a)+=I((b),(c),(d))+(x)+(unsigned long int)(ac);						\
	(a)=ROTATE_LEFT((a),(s));												\
	(a)+=(b);																\
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////!

//!MD5 加密类
class CMD5
{
	//!变量定义
private:
	unsigned long int				state[4];
	unsigned long int				count[2];
	unsigned char					buffer[64];
	unsigned char					PADDING[64];

	//!函数定义
public:
	//!构造函数
	CMD5() { MD5Init(); }

	//!功能函数
public:
	//!最终结果
	void MD5Final(unsigned char digest[16]);
	//!设置数值
	void MD5Update(unsigned char * input, unsigned int inputLen);

	//!内部函数
private:
	//!初始化
	void MD5Init();
	//!置位函数
	void MD5_memset(unsigned char * output, int value, unsigned int len);
	//!拷贝函数
	void MD5_memcpy(unsigned char * output, unsigned char * input, unsigned int len);
	//!转换函数
	void MD5Transform(unsigned long int state[4], unsigned char block[64]);
	//!编码函数
	void Encode(unsigned char * output, unsigned long int * input, unsigned int len);
	//!解码函数
	void Decode(unsigned long int *output, unsigned char * input, unsigned int len);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////!

//!初始化
void CMD5::MD5Init()
{
	count[0]=0;
	count[1]=0;
	state[0]=0x67452301;
	state[1]=0xefcdab89;
	state[2]=0x98badcfe;
	state[3]=0x10325476;
	MD5_memset(PADDING,0,sizeof(PADDING));
	*PADDING=0x80;
	return;
}

//!更新函数
void CMD5::MD5Update (unsigned char * input, unsigned int inputLen)
{
	unsigned int i,index,partLen;
	index=(unsigned int)((this->count[0]>>3)&0x3F);
	if ((count[0]+=((unsigned long int)inputLen<<3))<((unsigned long int)inputLen<<3)) count[1]++;
	count[1]+=((unsigned long int)inputLen>>29);
	partLen=64-index;
	if (inputLen>=partLen) 
	{
		MD5_memcpy((unsigned char*)&buffer[index],(unsigned char *)input,partLen);
		MD5Transform(state,buffer);
		for (i=partLen;i+63<inputLen;i+=64) MD5Transform(state,&input[i]);
		index=0;
	}
	else i=0;
	MD5_memcpy((unsigned char*)&buffer[index],(unsigned char *)&input[i],inputLen-i);
	return;
}

//!最终结果
void CMD5::MD5Final(unsigned char digest[16])
{
	unsigned char bits[8];
	unsigned int index,padLen;
	Encode(bits,count,8);
	index=(unsigned int)((count[0]>>3)&0x3f);
	padLen=(index<56)?(56-index):(120-index);
	MD5Update( PADDING,padLen);
	MD5Update(bits,8);
	Encode(digest,state,16);
	MD5_memset((unsigned char*)this,0,sizeof (*this));
	MD5Init();
	return;
}

//!转换函数
void CMD5::MD5Transform(unsigned long int state[4], unsigned char block[64])
{
	unsigned long int a=state[0],b=state[1],c=state[2],d=state[3],x[16];
	Decode(x,block,64);

	FF(a,b,c,d,x[ 0],S11,0xd76aa478); /* 1 */
	FF(d,a,b,c,x[ 1],S12,0xe8c7b756); /* 2 */
	FF(c,d,a,b,x[ 2],S13,0x242070db); /* 3 */
	FF(b,c,d,a,x[ 3],S14,0xc1bdceee); /* 4 */
	FF(a,b,c,d,x[ 4],S11,0xf57c0faf); /* 5 */
	FF(d,a,b,c,x[ 5],S12,0x4787c62a); /* 6 */
	FF(c,d,a,b,x[ 6],S13,0xa8304613); /* 7 */
	FF(b,c,d,a,x[ 7],S14,0xfd469501); /* 8 */
	FF(a,b,c,d,x[ 8],S11,0x698098d8); /* 9 */
	FF(d,a,b,c,x[ 9],S12,0x8b44f7af); /* 10 */
	FF(c,d,a,b,x[10],S13,0xffff5bb1); /* 11 */
	FF(b,c,d,a,x[11],S14,0x895cd7be); /* 12 */
	FF(a,b,c,d,x[12],S11,0x6b901122); /* 13 */
	FF(d,a,b,c,x[13],S12,0xfd987193); /* 14 */
	FF(c,d,a,b,x[14],S13,0xa679438e); /* 15 */
	FF(b,c,d,a,x[15],S14,0x49b40821); /* 16 */

	GG(a,b,c,d,x[ 1],S21,0xf61e2562); /* 17 */
	GG(d,a,b,c,x[ 6],S22,0xc040b340); /* 18 */
	GG(c,d,a,b,x[11],S23,0x265e5a51); /* 19 */
	GG(b,c,d,a,x[ 0],S24,0xe9b6c7aa); /* 20 */
	GG(a,b,c,d,x[ 5],S21,0xd62f105d); /* 21 */
	GG(d,a,b,c,x[10],S22,0x2441453);  /* 22 */
	GG(c,d,a,b,x[15],S23,0xd8a1e681); /* 23 */
	GG(b,c,d,a,x[ 4],S24,0xe7d3fbc8); /* 24 */
	GG(a,b,c,d,x[ 9],S21,0x21e1cde6); /* 25 */
	GG(d,a,b,c,x[14],S22,0xc33707d6); /* 26 */
	GG(c,d,a,b,x[ 3],S23,0xf4d50d87); /* 27 */
	GG(b,c,d,a,x[ 8],S24,0x455a14ed); /* 28 */
	GG(a,b,c,d,x[13],S21,0xa9e3e905); /* 29 */
	GG(d,a,b,c,x[ 2],S22,0xfcefa3f8); /* 30 */
	GG(c,d,a,b,x[ 7],S23,0x676f02d9); /* 31 */
	GG(b,c,d,a,x[12],S24,0x8d2a4c8a); /* 32 */

	HH(a,b,c,d,x[ 5],S31,0xfffa3942); /* 33 */
	HH(d,a,b,c,x[ 8],S32,0x8771f681); /* 34 */
	HH(c,d,a,b,x[11],S33,0x6d9d6122); /* 35 */
	HH(b,c,d,a,x[14],S34,0xfde5380c); /* 36 */
	HH(a,b,c,d,x[ 1],S31,0xa4beea44); /* 37 */
	HH(d,a,b,c,x[ 4],S32,0x4bdecfa9); /* 38 */
	HH(c,d,a,b,x[ 7],S33,0xf6bb4b60); /* 39 */
	HH(b,c,d,a,x[10],S34,0xbebfbc70); /* 40 */
	HH(a,b,c,d,x[13],S31,0x289b7ec6); /* 41 */
	HH(d,a,b,c,x[ 0],S32,0xeaa127fa); /* 42 */
	HH(c,d,a,b,x[ 3],S33,0xd4ef3085); /* 43 */
	HH(b,c,d,a,x[ 6],S34,0x4881d05);  /* 44 */
	HH(a,b,c,d,x[ 9],S31,0xd9d4d039); /* 45 */
	HH(d,a,b,c,x[12],S32,0xe6db99e5); /* 46 */
	HH(c,d,a,b,x[15],S33,0x1fa27cf8); /* 47 */
	HH(b,c,d,a,x[ 2],S34,0xc4ac5665); /* 48 */

	II(a,b,c,d,x[ 0],S41,0xf4292244); /* 49 */
	II(d,a,b,c,x[ 7],S42,0x432aff97); /* 50 */
	II(c,d,a,b,x[14],S43,0xab9423a7); /* 51 */
	II(b,c,d,a,x[ 5],S44,0xfc93a039); /* 52 */
	II(a,b,c,d,x[12],S41,0x655b59c3); /* 53 */
	II(d,a,b,c,x[ 3],S42,0x8f0ccc92); /* 54 */
	II(c,d,a,b,x[10],S43,0xffeff47d); /* 55 */
	II(b,c,d,a,x[ 1],S44,0x85845dd1); /* 56 */
	II(a,b,c,d,x[ 8],S41,0x6fa87e4f); /* 57 */
	II(d,a,b,c,x[15],S42,0xfe2ce6e0); /* 58 */
	II(c,d,a,b,x[ 6],S43,0xa3014314); /* 59 */
	II(b,c,d,a,x[13],S44,0x4e0811a1); /* 60 */
	II(a,b,c,d,x[ 4],S41,0xf7537e82); /* 61 */
	II(d,a,b,c,x[11],S42,0xbd3af235); /* 62 */
	II(c,d,a,b,x[ 2],S43,0x2ad7d2bb); /* 63 */
	II(b,c,d,a,x[ 9],S44,0xeb86d391); /* 64 */

	state[0]+=a;
	state[1]+=b;
	state[2]+=c;
	state[3]+=d;

	MD5_memset((unsigned char *)x,0,sizeof(x));

	return;
}

//!编码函数
void CMD5::Encode(unsigned char * output, unsigned long int * input,unsigned int len)
{
	unsigned int i, j;
	for (i=0,j=0;j<len;i++,j+=4)
	{
		output[j]=(unsigned char)(input[i]&0xff);
		output[j+1]=(unsigned char)((input[i]>>8)&0xff);
		output[j+2]=(unsigned char)((input[i]>>16)&0xff);
		output[j+3]=(unsigned char)((input[i]>>24)&0xff);
	}
	return;
}

//!解码函数
void CMD5::Decode(unsigned long int *output, unsigned char *input, unsigned int len)
{
	unsigned int i,j;
	for (i=0,j=0;j<len;i++,j+=4)
	{
		output[i]=((unsigned long int)input[j])|(((unsigned long int)input[j+1])<<8)|
			(((unsigned long int)input[j+2])<<16)|(((unsigned long int)input[j+3])<< 24);
	}
	return;
}

//!拷贝函数
void CMD5::MD5_memcpy(unsigned char * output, unsigned char * input,unsigned int len)
{
	for (unsigned int i=0;i<len;i++) output[i]=input[i];
}

//!置位函数
void CMD5::MD5_memset (unsigned char * output, int value, unsigned int len)
{
	for (unsigned int i=0;i<len;i++) ((char *)output)[i]=(char)value;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////!

using namespace std;

/*! 
 * Manage MD5. 
 */  
class _CMD5  
{  
private:  
    #define uint8  unsigned char  
    #define uint32 unsigned long int  
  
    struct md5_context  
    {  
        uint32 total[2];  
        uint32 state[4];  
        uint8 buffer[64];  
    };  
  
    void md5_starts( struct md5_context *ctx );  
    void md5_process( struct md5_context *ctx, const uint8 data[64] );  
    void md5_update( struct md5_context *ctx, const uint8 *input, uint32 length );  
    void md5_finish( struct md5_context *ctx, uint8 digest[16] );  
  
public:  
    //! construct a _CMD5 from any buffer  
    void GenerateMD5(const unsigned char* buffer,int bufferlen);  
  
    //! construct a _CMD5  
    _CMD5();  
  
    //! construct a md5src from char *  
    _CMD5(const char * md5src);  
  
    //! construct a _CMD5 from a 16 bytes md5  
    _CMD5(unsigned long* md5src);  
  
    //! add a other md5  
    _CMD5 operator +(_CMD5 adder);  
  
    //! just if equal  
    bool operator ==(_CMD5 cmper);  
  
    //! give the value from equer  
    // void operator =(_CMD5 equer);  
  
    //! to a string  
    string ToString();  
  
    unsigned long m_data[4];  
};  

/* 
    * RFC 1321 compliant MD5 implementation, 
    * by Christophe Devine <devine@cr0.net>; 
    * this program is licensed under the GPL. 
    */  
      
#define GET_UINT32(n,b,i) \
{ \
    (n) = (uint32) ((uint8 *) b)[(i)] \
        | (((uint32) ((uint8 *) b)[(i)+1]) <<  8) \
        | (((uint32) ((uint8 *) b)[(i)+2]) << 16) \
        | (((uint32) ((uint8 *) b)[(i)+3]) << 24); \
}  
      
#define PUT_UINT32(n,b,i) \
{ \
    (((uint8 *) b)[(i)]  ) = (uint8) (((n)      ) & 0xFF); \
    (((uint8 *) b)[(i)+1]) = (uint8) (((n) >>  8) & 0xFF); \
    (((uint8 *) b)[(i)+2]) = (uint8) (((n) >> 16) & 0xFF); \
    (((uint8 *) b)[(i)+3]) = (uint8) (((n) >> 24) & 0xFF); \
}  
      
//extern pthread_mutex_t mutexMemory;  
      
void _CMD5::md5_starts( struct md5_context *ctx )  
{  
    ctx->total[0] = 0;  
    ctx->total[1] = 0;  
    ctx->state[0] = 0x67452301;  
    ctx->state[1] = 0xEFCDAB89;  
    ctx->state[2] = 0x98BADCFE;  
    ctx->state[3] = 0x10325476;  
}  
      
void _CMD5::md5_process( struct md5_context *ctx, const uint8 data[64] )  
{  
    uint32 A, B, C, D, X[16];  
      
    GET_UINT32( X[0],  data,  0 );  
    GET_UINT32( X[1],  data,  4 );  
    GET_UINT32( X[2],  data,  8 );  
    GET_UINT32( X[3],  data, 12 );  
    GET_UINT32( X[4],  data, 16 );  
    GET_UINT32( X[5],  data, 20 );  
    GET_UINT32( X[6],  data, 24 );  
    GET_UINT32( X[7],  data, 28 );  
    GET_UINT32( X[8],  data, 32 );  
    GET_UINT32( X[9],  data, 36 );  
    GET_UINT32( X[10], data, 40 );  
    GET_UINT32( X[11], data, 44 );  
    GET_UINT32( X[12], data, 48 );  
    GET_UINT32( X[13], data, 52 );  
    GET_UINT32( X[14], data, 56 );  
    GET_UINT32( X[15], data, 60 );  
      
#define S(x,n) ((x << n) | ((x & 0xFFFFFFFF) >> (32 - n)))  
#define P(a,b,c,d,k,s,t) {a += F(b,c,d) + X[k] + t; a = S(a,s) + b;}
      
    A = ctx->state[0];  
    B = ctx->state[1];  
    C = ctx->state[2];  
    D = ctx->state[3];  
      
#undef F  
#define F(x,y,z) (z ^ (x & (y ^ z)))  
      
    P( A, B, C, D,  0,  7, 0xD76AA478 );  
    P( D, A, B, C,  1, 12, 0xE8C7B756 );  
    P( C, D, A, B,  2, 17, 0x242070DB );  
    P( B, C, D, A,  3, 22, 0xC1BDCEEE );  
    P( A, B, C, D,  4,  7, 0xF57C0FAF );  
    P( D, A, B, C,  5, 12, 0x4787C62A );  
    P( C, D, A, B,  6, 17, 0xA8304613 );  
    P( B, C, D, A,  7, 22, 0xFD469501 );  
    P( A, B, C, D,  8,  7, 0x698098D8 );  
    P( D, A, B, C,  9, 12, 0x8B44F7AF );  
    P( C, D, A, B, 10, 17, 0xFFFF5BB1 );  
    P( B, C, D, A, 11, 22, 0x895CD7BE );  
    P( A, B, C, D, 12,  7, 0x6B901122 );  
    P( D, A, B, C, 13, 12, 0xFD987193 );  
    P( C, D, A, B, 14, 17, 0xA679438E );  
    P( B, C, D, A, 15, 22, 0x49B40821 );  
      
#undef F  
      
#define F(x,y,z) (y ^ (z & (x ^ y)))  
      
    P( A, B, C, D,  1,  5, 0xF61E2562 );  
    P( D, A, B, C,  6,  9, 0xC040B340 );  
    P( C, D, A, B, 11, 14, 0x265E5A51 );  
    P( B, C, D, A,  0, 20, 0xE9B6C7AA );  
    P( A, B, C, D,  5,  5, 0xD62F105D );  
    P( D, A, B, C, 10,  9, 0x02441453 );  
    P( C, D, A, B, 15, 14, 0xD8A1E681 );  
    P( B, C, D, A,  4, 20, 0xE7D3FBC8 );  
    P( A, B, C, D,  9,  5, 0x21E1CDE6 );  
    P( D, A, B, C, 14,  9, 0xC33707D6 );  
    P( C, D, A, B,  3, 14, 0xF4D50D87 );  
    P( B, C, D, A,  8, 20, 0x455A14ED );  
    P( A, B, C, D, 13,  5, 0xA9E3E905 );  
    P( D, A, B, C,  2,  9, 0xFCEFA3F8 );  
    P( C, D, A, B,  7, 14, 0x676F02D9 );  
    P( B, C, D, A, 12, 20, 0x8D2A4C8A );  
      
#undef F  
          
#define F(x,y,z) (x ^ y ^ z)  
      
    P( A, B, C, D,  5,  4, 0xFFFA3942 );  
    P( D, A, B, C,  8, 11, 0x8771F681 );  
    P( C, D, A, B, 11, 16, 0x6D9D6122 );  
    P( B, C, D, A, 14, 23, 0xFDE5380C );  
    P( A, B, C, D,  1,  4, 0xA4BEEA44 );  
    P( D, A, B, C,  4, 11, 0x4BDECFA9 );  
    P( C, D, A, B,  7, 16, 0xF6BB4B60 );  
    P( B, C, D, A, 10, 23, 0xBEBFBC70 );  
    P( A, B, C, D, 13,  4, 0x289B7EC6 );  
    P( D, A, B, C,  0, 11, 0xEAA127FA );  
    P( C, D, A, B,  3, 16, 0xD4EF3085 );  
    P( B, C, D, A,  6, 23, 0x04881D05 );  
    P( A, B, C, D,  9,  4, 0xD9D4D039 );  
    P( D, A, B, C, 12, 11, 0xE6DB99E5 );  
    P( C, D, A, B, 15, 16, 0x1FA27CF8 );  
    P( B, C, D, A,  2, 23, 0xC4AC5665 );  
      
#undef F  
      
#define F(x,y,z) (y ^ (x | ~z))  
      
    P( A, B, C, D,  0,  6, 0xF4292244 );  
    P( D, A, B, C,  7, 10, 0x432AFF97 );  
    P( C, D, A, B, 14, 15, 0xAB9423A7 );  
    P( B, C, D, A,  5, 21, 0xFC93A039 );  
    P( A, B, C, D, 12,  6, 0x655B59C3 );  
    P( D, A, B, C,  3, 10, 0x8F0CCC92 );  
    P( C, D, A, B, 10, 15, 0xFFEFF47D );  
    P( B, C, D, A,  1, 21, 0x85845DD1 );  
    P( A, B, C, D,  8,  6, 0x6FA87E4F );  
    P( D, A, B, C, 15, 10, 0xFE2CE6E0 );  
    P( C, D, A, B,  6, 15, 0xA3014314 );  
    P( B, C, D, A, 13, 21, 0x4E0811A1 );  
    P( A, B, C, D,  4,  6, 0xF7537E82 );  
    P( D, A, B, C, 11, 10, 0xBD3AF235 );  
    P( C, D, A, B,  2, 15, 0x2AD7D2BB );  
    P( B, C, D, A,  9, 21, 0xEB86D391 );  
      
#undef F  
      
    ctx->state[0] += A;  
    ctx->state[1] += B;  
    ctx->state[2] += C;  
    ctx->state[3] += D;  
}  
      
void _CMD5::md5_update( struct md5_context *ctx, const uint8 *input, uint32 length )  
{  
    uint32 left, fill;  
      
    if( ! length ) return;  
      
    left = ( ctx->total[0] >> 3 ) & 0x3F;  
    fill = 64 - left;  
      
    ctx->total[0] += length <<  3;  
    ctx->total[1] += length >> 29;  
      
    ctx->total[0] &= 0xFFFFFFFF;  
    ctx->total[1] += ctx->total[0] < length << 3;  
      
    if( left && length >= fill )  
    {  
        memcpy( (void *) (ctx->buffer + left), (void *) input, fill );  
        md5_process( ctx, ctx->buffer );  
        length -= fill;  
        input  += fill;  
        left = 0;  
    }  
      
    while( length >= 64 )  
    {  
        md5_process( ctx, input );  
        length -= 64;  
        input  += 64;  
    }  
      
    if( length )  
    {  
        memcpy( (void *) (ctx->buffer + left), (void *) input, length );  
    }  
}  
      
static uint8 md5_padding[64] =  
{  
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  
};  
      
void _CMD5::md5_finish( struct md5_context *ctx, uint8 digest[16] )  
{  
    uint32 last, padn;  
    uint8 msglen[8];  
      
    PUT_UINT32( ctx->total[0], msglen, 0 );  
    PUT_UINT32( ctx->total[1], msglen, 4 );  
      
    last = ( ctx->total[0] >> 3 ) & 0x3F;  
    padn = ( last < 56 ) ? ( 56 - last ) : ( 120 - last );  
      
    md5_update( ctx, md5_padding, padn );  
    md5_update( ctx, msglen, 8 );  
      
    PUT_UINT32( ctx->state[0], digest,  0 );  
    PUT_UINT32( ctx->state[1], digest,  4 );  
    PUT_UINT32( ctx->state[2], digest,  8 );  
    PUT_UINT32( ctx->state[3], digest, 12 );  
}  
      
void _CMD5::GenerateMD5(const unsigned char* buffer,int bufferlen)  
{  
    struct md5_context context;  
    md5_starts (&context);  
    md5_update (&context, buffer, bufferlen);  
    md5_finish (&context,(unsigned char*)m_data);  
}  
      
_CMD5::_CMD5()  
{  
    for(int i=0;i<4;i++)  
        m_data[i]=0;  
}  
      
_CMD5::_CMD5(unsigned long* md5src)  
{  
    memcpy(m_data,md5src,16);  
}  
int _httoi(const char *value)  
{  
    struct CHexMap  
    {  
    char chr;  
    int value;  
    };  
    const int HexMapL = 16;  
    CHexMap HexMap[HexMapL] =  
    {  
    {'0', 0}, {'1', 1},  
    {'2', 2}, {'3', 3},  
    {'4', 4}, {'5', 5},  
    {'6', 6}, {'7', 7},  
    {'8', 8}, {'9', 9},  
    {'a', 10}, {'b', 11},  
    {'c', 12}, {'d', 13},  
    {'e', 14}, {'f', 15}  
    };  
    //pthread_mutex_lock(&mutexMemory);  
    char *mstr = strdup(value);  
    //pthread_mutex_unlock(&mutexMemory);  
    char *s = mstr;  
    int result = 0;  
    if (*s == '0' && *(s + 1) == 'X') s += 2;  
    bool firsttime = true;  
    while (*s != '/0')  
    {  
    bool found = false;  
    for (int i = 0; i < HexMapL; i++)  
    {  
        if (*s == HexMap[i].chr)  
        {  
        if (!firsttime) result <<= 4;  
        result |= HexMap[i].value;  
        found = true;  
        break;  
        }  
    }  
    if (!found) break;  
    s++;  
    firsttime = false;  
    }  
    //pthread_mutex_lock(&mutexMemory);  
    free(mstr);  
    //pthread_mutex_unlock(&mutexMemory);  
    return result;  
}  
      
      
_CMD5::_CMD5(const char* md5src)  
{  
    if (strcmp(md5src,"")==0)  
    {  
        for(int i=0;i<4;i++)  
            m_data[i]=0;  
        return;  
    }  
    for(int j = 0; j < 16; j++ )  
    {  
        char buf[10];  
        strncpy(buf,md5src,2);  
        md5src+=2;  
        ((unsigned char*)m_data)[j] = _httoi(buf);  
    }  
}  
      
_CMD5 _CMD5::operator +(_CMD5 adder)  
{  
    unsigned long m_newdata[4];  
    for(int i=0;i<4;i++)  
        m_newdata[i]=m_data[i]^(adder.m_data[i]);  
    return _CMD5(m_newdata);  
}  
      
bool _CMD5::operator ==(_CMD5 cmper)  
{  
    return (memcmp(cmper.m_data ,m_data,16)==0);  
}  
      
//void _CMD5::operator =(_CMD5 equer)  
//{  
//  memcpy(m_data,equer.m_data ,16);  
//}  
      
string _CMD5::ToString()  
{  
    char output[33];  
    for(int j = 0; j < 16; j++ )  
    {  
        sprintf( output + j * 2, "%02x", ((unsigned char*)m_data)[j]);  
    }  
    return string(output);  
} 

namespace keye{
void md5_generate(char out[32],const unsigned char* in,size_t len){
    string key;  
    _CMD5 iMD5;  
    iMD5.GenerateMD5(in,len*sizeof(char));  
    key = iMD5.ToString();
	strcpy(out,key.c_str());
}
};
