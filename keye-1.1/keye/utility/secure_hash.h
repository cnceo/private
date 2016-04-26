// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#define CORE_API KEYE_API

// Unsigned base types.
typedef std::string			FString;
typedef unsigned char 		uint8;		// 8-bit  unsigned.
typedef unsigned int		uint32;		// 32-bit unsigned.
										/**
* Convert an array of bytes to hex
* @param In byte array values to convert
* @param Count number of bytes to convert
* @return Hex value in string.
*/
std::string bytes2hex(uint8* In,uint32 Count);
/*-----------------------------------------------------------------------------
	MD5 functions.
-----------------------------------------------------------------------------*/

/** @name MD5 functions */
//@{
//
// MD5 Context.
//

class CORE_API FMD5
{
public:
	enum { DigestSize=16 };

	FMD5();
	~FMD5();

	/**
	 * MD5 block update operation.  Continues an MD5 message-digest operation,
	 * processing another message block, and updating the context.
	 *
	 * @param input		input data
	 * @param inputLen	length of the input data in bytes
	 **/
	void Update(uint8* input, uint32 inputLen);

	/**
	 * MD5 finalization. Ends an MD5 message-digest operation, writing the
	 * the message digest and zeroizing the context.
	 * Digest is 16 BYTEs.
	 *
	 * @param digest	pointer to a buffer where the digest should be stored ( must have at least 16 bytes )
	 **/
	void Final(uint8* digest);

	/**
	 * Helper to perform the very common case of hashing an ASCII string into a hex representation.
	 * 
	 * @param String	the string the hash
	 **/
	static FString HashAnsiString(const char* String);
private:
	struct FContext
	{
		uint32 state[4];
		uint32 count[2];
		uint8 buffer[64];
	};

	void Transform( uint32* state, uint8* block );
	void Encode( uint8* output, uint32* input, uint32 len );
	void Decode( uint32* output, uint8* input, uint32 len );

	FContext Context;
};
//@}
/*-----------------------------------------------------------------------------
	SHA-1 functions.
-----------------------------------------------------------------------------*/

/*
 *	NOTE:
 *	100% free public domain implementation of the SHA-1 algorithm
 *	by Dominik Reichl <dominik.reichl@t-online.de>
 *	Web: http://www.dominik-reichl.de/
 */


class CORE_API FSHA1
{
	typedef union
	{
		uint8  c[64];
		uint32 l[16];
	} SHA1_WORKSPACE_BLOCK;
public:

	enum {DigestSize=20};
	// Constructor and Destructor
	FSHA1();
	~FSHA1();

	uint32 m_state[5];
	uint32 m_count[2];
	uint32 __reserved1[1];
	uint8  m_buffer[64];
	uint8  m_digest[DigestSize];
	uint32 __reserved2[3];

	void Reset();

	// Update the hash value
	void Update(const uint8 *data, uint32 len);

	/**
	* SHA1 finalization. Ends an SHA1 message-digest operation, writing the
	* the message digest and zeroizing the context.
	* Digest is 20 BYTEs.
	*
	* @param digest	pointer to a buffer where the digest should be stored ( must have at least 20 bytes )
	**/
	void Final(uint8* digest);

	/**
	 * Helper to perform the very common case of hashing an ASCII string into a hex representation.
	 * 
	 * @param String	the string the hash
	 **/
	static FString HashAnsiString(const char* String);

private:
	// Private SHA-1 transformation
	void Transform(uint32 *state, const uint8 *buffer);

	// Member variables
	uint8 m_workspace[64];
	SHA1_WORKSPACE_BLOCK *m_block; // SHA1 pointer to the byte array above
};
