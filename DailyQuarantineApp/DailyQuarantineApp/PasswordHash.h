#pragma once

#include <string>
#include <CkCrypt2.h>

class PasswordHash
{

public:
	bool hashPassword(const char*, const char*&);
	bool verifyPassword(const char*, const char*);
	void setWorkFactor(const int&);

private:
	CkCrypt2 cryptObj;
};