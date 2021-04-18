#include "PasswordHash.h"
#include <CkCrypt2.h>
#include <exception>
#include <iostream>

bool PasswordHash::hashPassword(const char* password, const char*& hashedPassword)
{
	try
	{
		const char* bcryptHash = cryptObj.bCryptHash(password);
		hashedPassword = bcryptHash;

		if (hashedPassword != NULL)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	catch (std::exception& exception)
	{
		std::cout<<"Hashing error"<<std::endl;
	}

	return false;
}

bool PasswordHash::verifyPassword(const char* password, const char* cryptHash)
{
	try
	{
		bool passwordValid = cryptObj.BCryptVerify(password, cryptHash);
		if (passwordValid == true)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	catch (std::exception& exception)
	{
		std::cout << "Error during password verification" << std::endl;
	}
	return false;
}

void PasswordHash::setWorkFactor(const int& workFactor)
{
	try
	{
		if (workFactor < 4 || workFactor > 31)
		{
			throw "Invalid workFactor! Please enter a valid work factor between 4 and 31.\n";
		}
		else
		{
			cryptObj.put_BCryptWorkFactor(workFactor);
		}
	}
	catch (std::exception& exception) {

		std::cout << "Error:" << std::endl;
	}

}
