#include "DailyQuarantineApp.h"
#include "Networking.h"
#include <QtWidgets/qmessagebox.h>
#include <sstream>

#define SQL_RESULT_LEN 50

DailyQuarantineApp::DailyQuarantineApp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void DailyQuarantineApp::on_loginButton_pressed()
{
	QString username = ui.username_login_edit->text();
	QString password = ui.password_login_edit->text();
	m_mainFrame.show();
	//m_test.show();
    //setUsername(username);
    //setPassword(password);
    //verifyUserAccount();
}

void DailyQuarantineApp::on_registrationButton_pressed()
{
	ui.login_label->setCurrentIndex(1);
}

void DailyQuarantineApp::showEvent(QShowEvent* ev)
{
	QMainWindow::showEvent(ev);
	//Verify if is possible to connect to the database. Show a warning message if not possbile and exit the application.
	Networking networking;
	/*if (!networking.networkConnection_QuickMode())
	{
		if (!networking.networkConnection_AdvancedMode())
		{
			QMessageBox::warning(this, "Eroare de conexiune", "A aparut o eroare privind conexiunea la internet. Va rugam sa verificati conexiunea dvs. la internet!");
			exit(EXIT_FAILURE);
		}
	}
	if (!database.getIsConnected())
	{
		QMessageBox::warning(this, "Eroare de conexiune", "A aparut o eroare privind conectarea la baza de date. Va rugam sa reveniti mai tarziu");
		exit(EXIT_FAILURE);
	}*/
}

void DailyQuarantineApp::setUsername(const QString& username)
{
	m_username = username;
}

void DailyQuarantineApp::setPassword(const QString& password)
{
	m_password = password;
}

void DailyQuarantineApp::verifyUserAccount()
{
	SQLHANDLE sqlStmtHandle = database.getStmtHandle();
	SQLWCHAR SQLQuery[] = L"SELECT * FROM Users";

	std::string user_username = m_username.toUtf8().constData();
	std::string user_password = m_password.toUtf8().constData();

	std::string data_username;
	std::string data_password;

	//if there is a problem executing the query then exit application else display query result
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, SQLQuery, SQL_NTS)) {
		
	}

	else {

		char  username[SQL_RESULT_LEN];
		char  password[SQL_RESULT_LEN];
		char  email[SQL_RESULT_LEN];
		int id;
		bool connect = false;

		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			// Fetches the next rowset of data from the result
			SQLGetData(sqlStmtHandle, 1, SQL_C_DEFAULT, &id, sizeof(id), NULL);
			SQLGetData(sqlStmtHandle, 2, SQL_C_DEFAULT, &username, sizeof(username), NULL);
			SQLGetData(sqlStmtHandle, 3, SQL_C_DEFAULT, &password, sizeof(password), NULL);
			SQLGetData(sqlStmtHandle, 4, SQL_C_DEFAULT, &email, sizeof(password), NULL);

			std::stringstream ss;
			ss << username;
			ss >> data_username;
			ss.clear();
			ss << password;
			ss >> data_password;

			//Verify if the user exists in the database 
			if (data_username == user_username &&  user_password==data_password) {
				//If exists, set the id of the student to retrieve additional information about him from the database
				m_mainFrame.show();
				close();
				connect = true;
				break;
			}
		}
		if (connect == false)
		{
			QMessageBox::warning(this, "Autentificare", "Numele de utilizator si/sau parola nu sunt corecte!");
		}
	}
	SQLFreeStmt(sqlStmtHandle, SQL_CLOSE);
}

QString DailyQuarantineApp::getUsername() const
{
	return m_username;
}

QString DailyQuarantineApp::getPassword() const
{
	return m_password;
}
