#pragma once
#include <iostream>
#include <qstring.h>
#include <qdatetime.h>
#include <QListWidget>
#include <QStringListModel>

class Notes : QListWidgetItem
{
private:
	int m_userId;
	int m_notesId;
	std::string m_noteText;
	std::string m_noteTitle;
	QDate m_date;

public:
	Notes();
	Notes(const int userId, const int notesId, const std::string& noteText, const std::string& noteTitle, const QDate date);
	Notes(const int userId);
	Notes(const Notes& note);
	~Notes();

	Notes& operator=(const Notes& note);

	void setUserId(const int& id);
	void setNotesId(const int& notesId);
	void setNoteText(const std::string& noteText);
	void setNoteTitle(const std::string& noteTitle);

	int getUserId()const;
	int getNotesId()const;
	const std::string& getNoteText()const;
	const std::string& getNoteTitle()const;
	const QDate getDate()const;
};

