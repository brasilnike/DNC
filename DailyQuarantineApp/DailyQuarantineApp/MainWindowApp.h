#pragma once

#include <QWidget>
#include <iostream>
#include "ui_MainWindowApp.h"
#include <string>
#include "Notes.h"
#include <QListWidget>
#include <QStringListModel>
#include "NoteSelected.h"

class MainWindowApp : public QWidget
{
	Q_OBJECT

public:
	MainWindowApp(QWidget *parent = Q_NULLPTR);
	~MainWindowApp();

private:
	Ui::MainWindowApp ui;
	NoteSelected m_noteSelected;

private slots:
	void on_calendarButton_pressed();
	void on_medicButton_pressed();
	void on_covidButton_pressed();
	void on_calendarWidget_clicked();
	void on_addNoteButton_pressed();

	void on_listWidget_itemDoubleClicked();
private:
	Notes m_currentNote;
	std::vector<Notes> m_listNotes;
};

enum class Pages
{
	Principal,
	Calendar,
	Notes,
	Medic,
	Covid
};