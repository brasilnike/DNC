#include "MainWindowApp.h"

#define SQL_RESULT_LEN 1000

MainWindowApp::MainWindowApp(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

MainWindowApp::~MainWindowApp()
{
	ui.stackedWidget->setCurrentIndex(int(Pages::Principal));
}

void MainWindowApp::setHandle(const SQLHANDLE& sqlStmtHandle)
{
	m_sqlStmtHandle = sqlStmtHandle;
}

void MainWindowApp::setUser(User&& user)
{
	m_user = std::move(user);
}

void MainWindowApp::on_calendarButton_pressed()
{
	ui.stackedWidget->setCurrentIndex(int(Pages::Calendar));
	getAllNotes();
	for (Notes note : m_listNotes)
	{
		ui.listWidget->addItem(QString::number(note.getNotesId()) + " " + QString::fromStdString(note.getNoteTitle()));
	}
}

void MainWindowApp::on_medicButton_pressed()
{
	ui.stackedWidget->setCurrentIndex(int(Pages::Medic));
}

void MainWindowApp::on_covidButton_pressed()
{
	ui.stackedWidget->setCurrentIndex(int(Pages::Covid));
}

void MainWindowApp::on_calendarWidget_clicked()
{
	ui.stackedWidget->setCurrentIndex(int(Pages::Notes));
}

void MainWindowApp::on_addNoteButton_pressed()
{
	int listSize = m_listNotes.size();
	Notes aux(m_user.getId(), listSize, ui.notes->toPlainText().toStdString(), ui.title->toPlainText().toStdString(), QDate::currentDate().toString().toStdString());
	m_listNotes.push_back(aux);
	ui.listWidget->addItem(QString::number(aux.getNotesId()) + " " + QString::fromStdString(aux.getNoteTitle()));
	ui.stackedWidget->setCurrentIndex(int(Pages::Calendar));
	insertNote(aux);
}

void MainWindowApp::on_listWidget_itemDoubleClicked()
{
	m_noteSelected.show();
	for (Notes note : m_listNotes)
	{
		QString s1 = ui.listWidget->selectedItems()[0]->text();
		QString s2 = QString::number(note.getNotesId());
		s2.append(" ");
		s2.append(QString::fromStdString(note.getNoteTitle()));
		if (QString::compare(s1, s2) == 0)
		{
			m_currentNote = note;
			ui.listWidget->clearSelection();
			break;
		}
	}

	m_noteSelected.getUi().noteIdText->setText(QString::fromStdString(std::to_string(m_currentNote.getNotesId())));
	m_noteSelected.getUi().noteTitleText->setText(QString::fromStdString(m_currentNote.getNoteTitle()));
	m_noteSelected.getUi().noteTextText->setText(QString::fromStdString(m_currentNote.getNoteText()));
	m_noteSelected.getUi().noteDateText->setText(QString::fromStdString(m_currentNote.getDate()));

}

void MainWindowApp::insertNote(const Notes& note)
{
	int userId = note.getUserId();
	std::string title = note.getNoteTitle();
	std::string content= note.getNoteText();
	std::string date = note.getDate();
	SQLRETURN retcode = SQLPrepare(m_sqlStmtHandle, (SQLWCHAR*)L"INSERT INTO Notes (user_id, notes_title, notes_content,notes_date) VALUES(?,?,?,?) ", SQL_NTS);
	retcode = SQLBindParameter(m_sqlStmtHandle, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &userId, 0, NULL);
	retcode = SQLBindParameter(m_sqlStmtHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, (SQLPOINTER)title.c_str(), title.length(), NULL);
	retcode = SQLBindParameter(m_sqlStmtHandle, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 300, 0, (SQLPOINTER)content.c_str(), content.length(), NULL);
	retcode = SQLBindParameter(m_sqlStmtHandle, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, (SQLPOINTER)date.c_str(), date.length(), NULL);
	retcode = SQLExecute(m_sqlStmtHandle);

	if (SQL_SUCCESS != retcode) {
		std::cout << "ERROR" << std::endl;
	}
	else {

		SQLFreeStmt(m_sqlStmtHandle, SQL_CLOSE);
	}
}

void MainWindowApp::getAllNotes()
{
	std::string query_string = "SELECT notes_id, notes_title, notes_content, notes_date FROM Notes WHERE user_id=" + std::to_string(m_user.getId());
	std::wstring  query_wstring(query_string.begin(), query_string.end());
	SQLWCHAR* SQLQuery = (SQLWCHAR*)query_wstring.c_str();

	if (SQL_SUCCESS != SQLExecDirect(m_sqlStmtHandle, SQLQuery, SQL_NTS))
	{
		std::cout << "ERROR2" << std::endl;
	}
	else {

		int notesId;
		char noteTitle[SQL_RESULT_LEN];
		char noteText[SQL_RESULT_LEN];
		char date[SQL_RESULT_LEN];

		while (SQLFetch(m_sqlStmtHandle) == SQL_SUCCESS)
		{

			SQLGetData(m_sqlStmtHandle, 1, SQL_C_DEFAULT, &notesId, sizeof(notesId), NULL);
			SQLGetData(m_sqlStmtHandle, 2, SQL_C_DEFAULT, &noteTitle, sizeof(noteTitle), NULL);
			SQLGetData(m_sqlStmtHandle, 3, SQL_C_DEFAULT, &noteText, sizeof(noteText), NULL);
			SQLGetData(m_sqlStmtHandle, 4, SQL_C_DEFAULT, &date, sizeof(date), NULL);
			Notes note(m_user.getId(),notesId,noteText,noteTitle, date);
			m_listNotes.push_back(note);
		}

		SQLFreeStmt(m_sqlStmtHandle, SQL_CLOSE);
	}
}
