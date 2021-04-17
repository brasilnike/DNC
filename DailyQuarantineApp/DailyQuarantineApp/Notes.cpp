#include "Notes.h"

Notes::Notes()
{
}

Notes::Notes(const int userId, const int notesId, const std::string& noteText, const std::string& noteTitle, const QDate date)
	: m_userId{ userId }, m_notesId{ notesId }, m_noteText{ noteText }, m_noteTitle{ noteTitle }, m_date{ date }
{
}

Notes::Notes(const int userId)
{
	m_userId = userId;
}

Notes::Notes(const Notes& note)
{
	m_userId = note.m_userId;
	m_notesId = note.m_notesId;
	m_noteText = note.m_noteText;
	m_noteTitle = note.m_noteTitle;
	m_date = note.m_date;
}

Notes::~Notes()
{
}

void Notes::setUserId(const int& id)
{
	m_userId = id;
}

void Notes::setNotesId(const int& notesId)
{
	m_notesId = notesId;
}

void Notes::setNoteText(const std::string& noteText)
{
	m_noteText = noteText;
}

void Notes::setNoteTitle(const std::string& noteTitle)
{
	m_noteTitle = noteTitle;
}

int Notes::getUserId() const
{
	return m_userId;
}

int Notes::getNotesId() const
{
	return m_notesId;
}

const std::string& Notes::getNoteText() const
{
	return m_noteText;
}

const std::string& Notes::getNoteTitle() const
{
	return m_noteTitle;
}

const QDate Notes::getDate() const
{
	return m_date;
}

Notes& Notes::operator=(const Notes& note)
{
	m_notesId = note.m_notesId;
	m_userId = note.m_userId;
	m_noteTitle = note.m_noteTitle;
	m_noteText = note.m_noteText;
	m_date = note.m_date;

	return *this;
}
