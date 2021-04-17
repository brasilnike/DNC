#include "User.h"

User::User()
{
	m_email = "";
	m_id = 0;
}

User::User(int id, const std::string& email)
	: m_id{ id },m_email{email}
{
}

User::User(User&& user)
{
	*this = std::move(user);
}

User::User(const User& user)
{
	m_email = user.m_email;
	m_id = user.m_id;
}

User& User::operator=(const User& user)
{
	m_email = user.m_email;
	m_id = user.m_id;

	return *this;
}

User& User::operator=(User&& user)
{
	this->m_id = user.m_id;
	this->m_email = user.m_email;
	
	new (&user)User;
	return *this;
}

void User::setId(int id)
{
	m_id = id;
}

void User::setEmail(const std::string& email)
{
	m_email = email;
}

const std::string User::getEmail() const
{
	return m_email;
}

int User::getId() const
{
	return m_id;
}
