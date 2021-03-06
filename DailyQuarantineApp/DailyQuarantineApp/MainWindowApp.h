#pragma once

#include <QWidget>
#include <iostream>
#include "ui_MainWindowApp.h"
#include <string>
#include "Notes.h"
#include <QListWidget>
#include <QStringListModel>
#include "NoteSelected.h"
#include "Database.h"
#include "User.h"
#include <Email.h>
#include "curl/curl.h"
#include <fstream>
#include <qfile.h>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <TreeGame.h>


class MainWindowApp : public QWidget
{
	Q_OBJECT

public:
	MainWindowApp(QWidget *parent = Q_NULLPTR);
	~MainWindowApp();

public:
	void setHandle(const SQLHANDLE& sqlStmtHandle);
	void setUser(User&& user);

private:
	Ui::MainWindowApp ui;
	NoteSelected m_noteSelected;
	TreeGame m_game;

private slots:
	void on_calendarButton_pressed();
	void on_medicButton_pressed();
	void on_covidButton_pressed();
	void on_gameButton_pressed();

	void on_CalendarReturnButton_pressed();
	void on_calendarWidget_clicked();
	void on_addNoteButton_pressed();
	void on_listWidget_itemDoubleClicked();

	void on_MedicReturnButton_pressed();
	void on_SendEmailButton_pressed();
	
	void on_CovidReturnButton_pressed();

private:
	void insertNote(const Notes& note);
	void getAllNotes();
	void statistics();
	std::string connectionCurl(std::string url);
	void jsonCovidUI(QJsonDocument json_doc);
	void jsonVaccinesUI(QJsonDocument json_doc);

private:
	SQLHANDLE m_sqlStmtHandle;
	Notes m_currentNote;
	std::vector<Notes> m_listNotes;
	User m_user;
	int m_lastNoteIndex;
	Email m_email;

};

enum class Pages
{
	Principal,
	Calendar,
	Notes,
	Covid,
	Medic
};