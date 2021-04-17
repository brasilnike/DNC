#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DailyQuarantineApp.h"
#include "MainWindowApp.h"
#include "Database.h"
#include "test.h"
#include "CovidPopUp.h"

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
    CovidPopUp m_covidFrame;

protected:
    void showEvent(QShowEvent* ev);

private slots:
    void on_loginButton_pressed();
    void on_registrationButton_pressed();


private:
    MainWindowApp m_mainFrame;
    test m_test;

private:
	void setUsername(const QString& username);
	void setPassword(const QString& password);
	void verifyUserAccount();
	
	QString getUsername()const;
	QString getPassword()const;
};
