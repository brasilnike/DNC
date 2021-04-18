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
	void setDogs(int dogs);
	int getDogs()const;

private:
	int m_id;
	int m_dogs;
	std::string m_email;
};


