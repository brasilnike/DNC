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
	QString m_noteText;
	QString m_noteTitle;
	QDate m_date;

public:
	Notes();
	Notes(const int userId, const int notesId, const QString noteText, const QString noteTitle, const QDate date);
	Notes(const int userId);
	Notes(const Notes& note);
	~Notes();

	void setUserId(const int& id);
	void setNotesId(const int& notesId);
	void setNoteText(const QString& noteText);
	void setNoteTitle(const QString& noteTitle);

	int getUserId()const;
	int getNotesId()const;
	QString getNoteText()const;
	QString getNoteTitle()const;
	QDate getDate()const;
};

