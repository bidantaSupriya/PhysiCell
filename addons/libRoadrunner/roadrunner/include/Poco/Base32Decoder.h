//
// Base32Decoder.h
//
// $Id: //poco/1.4/Foundation/include/Poco/Base32Decoder.h#2 $
//
// Library: Foundation
// Package: Streams
// Module:  Base32
//
// Definition of class Base32Decoder.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Foundation_Base32Decoder_INCLUDED
#define Foundation_Base32Decoder_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/UnbufferedStreamBuf.h"
#include <istream>


namespace Poco {


class Foundation_API Base32DecoderBuf: public UnbufferedStreamBuf
	/// This streambuf base32-decodes all data read
	/// from the istream connected to it.
	///
	/// Note: For performance reasons, the characters 
	/// are read directly from the given istream's 
	/// underlying streambuf, so the state
	/// of the istream will not reflect that of
	/// its streambuf.
{
public:
	Base32DecoderBuf(std::istream& istr);
	~Base32DecoderBuf();
	
private:
	int readFromDevice();
	int readOne();

	unsigned char   _group[8];
	int             _groupLength;
	int             _groupIndex;
	std::streambuf& _buf;
	
	static unsigned char IN_ENCODING[256];
	static bool          IN_ENCODING_INIT;
	
private:
	Base32DecoderBuf(const Base32DecoderBuf&);
	Base32DecoderBuf& operator = (const Base32DecoderBuf&);
};


class Foundation_API Base32DecoderIOS: public virtual std::ios
	/// The base class for Base32Decoder.
	///
	/// This class is needed to ensure the correct initialization
	/// order of the stream buffer and base classes.
{
public:
	Base32DecoderIOS(std::istream& istr);
	~Base32DecoderIOS();
	Base32DecoderBuf* rdbuf();

protected:
	Base32DecoderBuf _buf;
	
private:
	Base32DecoderIOS(const Base32DecoderIOS&);
	Base32DecoderIOS& operator = (const Base32DecoderIOS&);
};


class Foundation_API Base32Decoder: public Base32DecoderIOS, public std::istream
	/// This istream base32-decodes all data
	/// read from the istream connected to it.
	///
	/// Note: For performance reasons, the characters 
	/// are read directly from the given istream's 
	/// underlying streambuf, so the state
	/// of the istream will not reflect that of
	/// its streambuf.
{
public:
	Base32Decoder(std::istream& istr);
	~Base32Decoder();

private:
	Base32Decoder(const Base32Decoder&);
	Base32Decoder& operator = (const Base32Decoder&);
};


} // namespace Poco


#endif // Foundation_Base32Decoder_INCLUDED
