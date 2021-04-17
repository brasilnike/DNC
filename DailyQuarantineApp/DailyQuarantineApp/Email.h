#pragma once
#include <string>
#include <tuple>

class Email
{
public:
	Email();
	Email(const std::string& email_personName, const std::string& email_adress, const std::string& email_title, const std::string& email_message);
	~Email();

	bool sendMail();
	bool emailUnitTest();

	void setName(const std::string& name);
	void setAdress(const std::string& adress);
	void setSubject(const std::string& subject);
	void setMessage(const std::string& message);

	std::string dateTimeToString(const tm& t, const char* format);
	std::ostream& formatDateTime(std::ostream& out, const tm& t, const char* fmt);
	tm currentTime();

private:
	bool verifyEmail();
	bool canSend();

private:
	// 0 - m_name, 1 - m_adress, 2 - m_subject, 3 - m_message
	std::tuple<std::string, std::string, std::string, std::string> m_email;
};

