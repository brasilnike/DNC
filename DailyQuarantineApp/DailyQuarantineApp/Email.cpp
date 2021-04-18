#include "Email.h"
#include "Networking.h"
#include <iostream>
#include <CkMailMan.h>
#include <CkEmail.h>
#include <regex>
#include <string>
#include <iterator>
#include <sstream>
#include<chrono>

Email::Email()
{

}

Email::Email(const std::string& email_personName, const std::string& email_adress, const std::string& email_title, const std::string& email_message)
{
    m_email = std::make_tuple(email_personName, email_adress, email_title, email_message);
}


Email::~Email()
{
}

bool Email::verifyEmail()
{
    std::string adress(std::get<1>(m_email));
    std::smatch regexMatch;
    std::regex e1("\\b(@)([^ ]*)");
    std::regex e2("\\b(.)([^ ]*)");
    std::regex e3("\\b(com)([^ ]*)");
    std::regex e4("\\b(net)([^ ]*)");
    std::regex e5("\\b(host)([^ ]*)");

    if (std::regex_search(adress, regexMatch, e1) == false)
    {
        return false;
    }
    if (std::regex_search(adress, regexMatch, e2) == false)
    {
        return false;
    }
    if (std::regex_search(adress, regexMatch, e3) == false && std::regex_search(adress, regexMatch, e4) == false && std::regex_search(adress, regexMatch, e5) == false)
    {
        return false;
    }
    return true;
}

bool Email::canSend()
{
    if (verifyEmail() != true) {
        return false;
    }
    Networking networking;
    if (networking.networkConnection_QuickMode() == false && networking.networkConnection_AdvancedMode() == false)
    {
        return false;
    }
    return true;
}


bool Email::sendMail()
{
    if (canSend() == false)
        return false;

    //CkMailMan mailman;

    //// Set the SMTP server.
    //mailman.put_SmtpHost("smtp.gmail.com");

    //// Set the SMTP login/password
    //mailman.put_SmtpUsername("questionnaireproject2020@gmail.com");
    //mailman.put_SmtpPassword("BTRNEPWEB");
    //mailman.put_SmtpPort(465);

    //// Create a new email object
    //CkEmail email;

    //email.put_Subject(&std::get<2>(m_email)[0]);
    //email.put_Body(&std::get<3>(m_email)[0]);

    //std::string sintax = std::get<0>(m_email) + " <" + std::get<1>(m_email) + ">";

    //email.put_From(&sintax[0]);

    //bool success = email.AddTo(&std::get<0>(m_email)[0], &std::get<1>(m_email)[0]);

    //if (email.get_LastMethodSuccess() != true) {
    //    return false;
    //}

     // The mailman object is used for sending and receiving email.
    CkMailMan mailman;

    // Set the SMTP server.
    mailman.put_SmtpHost("smtp.gmail.com");
    mailman.put_SmtpPort(587);

    // Set the SMTP login/password (if required)
    mailman.put_SmtpUsername("questionnaireproject2020@gmail.com");
    mailman.put_SmtpPassword("BTRNEPWEB");

    // Create a new email object
    CkEmail email;

    email.put_Subject("This is a test");
    email.put_Body("This is a test");
    email.put_From("Salam <questionnaireproject2020@gmail.com>");
    boolean success = email.AddTo("Chilkat Admin", "alexneacsu2000@gmail.com");
    // To add more recipients, call AddTo, AddCC, or AddBcc once per recipient.

    // Call SendEmail to connect to the SMTP server and send.
    // The connection (i.e. session) to the SMTP server remains
    // open so that subsequent SendEmail calls may use the
    // same connection.  
    
    success = mailman.SendEmail(email);
    if (success != true) {
        return false;
    }

    success = mailman.CloseSmtpConnection();
    if (success != true) {
        return false;
    }

    return true;
}

void Email::setName(const std::string& name)
{
    std::get<0>(m_email) = name;
}

void Email::setAdress(const std::string& adress)
{
    std::get<1>(m_email) = adress;
}

void Email::setSubject(const std::string& subject)
{
    std::get<2>(m_email) = subject;
}

void Email::setMessage(const std::string& message)
{
    std::get<3>(m_email) = message;
}


std::ostream& Email::formatDateTime(std::ostream& out, const tm& t, const char* fmt) {
    const std::time_put<char>& dateWriter = std::use_facet<std::time_put<char> >(out.getloc());
    int n = strlen(fmt);
    if (dateWriter.put(out, out, ' ', &t, fmt, fmt + n).failed()) {
        throw std::runtime_error("Failure to format date time");
    }
    return out;
}

std::string Email::dateTimeToString(const tm& t, const char* format) {
    std::stringstream s;
    formatDateTime(s, t, format);
    return s.str();
}

tm  Email::currentTime() {

    auto current = std::chrono::system_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(current);
    tm now_local;
    localtime_s(&now_local, &time);
    return now_local;
}
