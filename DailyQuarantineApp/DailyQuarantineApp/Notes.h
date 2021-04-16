#pragma once
#include <iostream>
#include <qstring.h>
#include <qdatetime.h>

class Notes
{
private:
	int m_userId;
	int m_notesId;
	QString m_noteText;
	QString m_noteTitle;
	QDate m_date;

public:
	Notes();
	Notes(const int userId);
	Notes(const Notes& note);
	~Notes();

	void setUserId(int id);
	void setNotesId(const int& email);
	void setNoteText(const QString& noteText);
	void setNoteTitle(const QString& noteTitle);

	int getUserId()const;
	int getNotesId()const;
	QString getNoteText()const;
	QString getNoteTitle()const;
};

