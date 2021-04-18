#include "User.h"

User::User()
{
	m_email = "";
	m_id = 0;
	m_dogs = 0;
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
	m_dogs = user.m_dogs;
}

User& User::operator=(const User& user)
{
	m_email = user.m_email;
	m_id = user.m_id;
	m_dogs = user.m_dogs;

	return *this;
}

User& User::operator=(User&& user)
{
	this->m_id = user.m_id;
	this->m_email = user.m_email;
	this->m_dogs = user.m_dogs;
	
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

void User::setDogs(int dogs)
{
	m_dogs = dogs;
}

int User::getDogs() const
{
	return m_dogs;
}
