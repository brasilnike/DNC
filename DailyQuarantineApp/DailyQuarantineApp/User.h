#pragma once
#include<string>

class User
{
public:
	User();
	User(int id,const std::string& email);
	User(User&& user);
	User(const User& user);

	User& operator=(const User& user);
	User& operator=(User&& user);

	void setId(int id);
	void setEmail(const std::string& email);
	const std::string getEmail()const;
	int getId()const;

private:
	int m_id;
	std::string m_email;
};


