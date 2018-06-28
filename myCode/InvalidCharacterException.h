/*
 * InvalidCharacterException.h
 *
 *  Created on: Jan 16, 2018
 *      Author: arjun
 */

#ifndef MYCODE_INVALIDCHARACTEREXCEPTION_H_
#define MYCODE_INVALIDCHARACTEREXCEPTION_H_

#include <exception>
#include<iostream>
#include <sstream>

class InvalidCharacterException: public std::exception
{
private:
	std::string m_exceptionMessage;
public:
	InvalidCharacterException(const std::string& invalidCharacter,
			const int& lineNumber)
	{
		std::stringstream numStream;
		numStream << lineNumber;
		m_exceptionMessage = "Invalid Character '" + invalidCharacter + "' found at line: " + numStream.str();
	}
	virtual const char* what() const throw ()
	{
		return m_exceptionMessage.c_str();
	}
	virtual ~InvalidCharacterException() throw() {}
};

#endif /* MYCODE_INVALIDCHARACTEREXCEPTION_H_ */
