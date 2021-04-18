#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DailyQuarantineApp.h"
#include "MainWindowApp.h"
#include "Database.h"
#include "test.h"
#include "CovidPopUp.h"
#include "User.h"
#include "TreeGame.h"

class DailyQuarantineApp : public QMainWindow
{
    Q_OBJECT

public:
    DailyQuarantineApp(QWidget *parent = Q_NULLPTR);

private:
    Ui::DailyQuarantineAppClass ui;
    QString m_username;
    QString m_password;
    Database database;
    //CovidPopUp m_covidFrame;
    TreeGame m_treeGameFrame;

protected:
    void showEvent(QShowEvent* ev);

private slots:
    void on_loginButton_pressed();
    void on_registrationButton_pressed();
    void on_signUpButton_pressed();


private:
    MainWindowApp m_mainFrame;
    test m_test;
    User m_user;

private:
	void setUsername(const QString& username);
	void setPassword(const QString& password);
	void verifyUserAccount();
    bool validateFields(const std::string& username, const std::string& password, const std::string& email);
    void updateUserTable(const::std::string& username, const std::string& password, const std::string& email);

    bool checkPasswordHash(const std::string&, const std::string&);
    std::string hashPassword(const char*&);

	QString getUsername()const;
	QString getPassword()const;
};
