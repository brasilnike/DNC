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

private slots:
	void on_calendarButton_pressed();
	void on_medicButton_pressed();
	void on_covidButton_pressed();

	void on_CalendarReturnButton_pressed();
	void on_calendarWidget_clicked();
	void on_addNoteButton_pressed();


	void on_MedicReturnButton_pressed();
	void on_SendEmailButton_pressed();

	void on_listWidget_itemDoubleClicked();

private:
	void insertNote(const Notes& note);
	void getAllNotes();

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