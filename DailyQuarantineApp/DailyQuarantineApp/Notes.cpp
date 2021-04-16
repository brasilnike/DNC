#include "Notes.h"

Notes::Notes()
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
