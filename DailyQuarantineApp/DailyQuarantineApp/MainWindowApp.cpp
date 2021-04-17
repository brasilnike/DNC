#include "MainWindowApp.h"

MainWindowApp::MainWindowApp(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	Notes aux(0, 0, "Ok", "Titlu", QDate::currentDate());
	m_listNotes.push_back(aux);
	m_listNotes.push_back(aux);

	for (Notes note : m_listNotes)
	{
		ui.listWidget->addItem(QString::number(note.getNotesId()) + " " + QString(note.getNoteTitle()));
	}
}

MainWindowApp::~MainWindowApp()
{
	ui.stackedWidget->setCurrentIndex(int(Pages::Principal));
}

void MainWindowApp::on_calendarButton_pressed()
{
	ui.stackedWidget->setCurrentIndex(int(Pages::Calendar));
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
	Notes aux(0, 0, ui.notes->toPlainText(), ui.title->toPlainText(), QDate::currentDate());
	m_listNotes.push_back(aux);
	ui.listWidget->addItem(QString::number(aux.getNotesId()) + " " + QString(aux.getNoteTitle()));
	ui.stackedWidget->setCurrentIndex(int(Pages::Calendar));
}

void MainWindowApp::on_listWidget_itemDoubleClicked()
{
	m_noteSelected.show();
	for (Notes note : m_listNotes)
	{
		QString s1 = ui.listWidget->selectedItems()[0]->text();
		QString s2 = QString::number(note.getNotesId());
		s2.append(" ");
		s2.append(note.getNoteTitle());
		if (QString::compare(s1, s2) == 0)
		{
			m_currentNote = note;
			ui.listWidget->clearSelection();
			break;
		}
		/*if (QString::compare(ui.listWidget->selectedItems()[0]->text(), note.getConcat())==0)
		{
			m_currentNote = note;
		}
		if (ui.listWidget->selectedItems()[0]->text() == note.getConcat())
		{
			m_currentNote = note;
		}*/
	}

	m_noteSelected.getUi().noteIdText->setText(QString(m_currentNote.getNotesId()));
	m_noteSelected.getUi().noteTitleText->setText(QString(m_currentNote.getNoteTitle()));
	m_noteSelected.getUi().noteTextText->setText(QString(m_currentNote.getNoteText()));
	m_noteSelected.getUi().noteDateText->setText(m_currentNote.getDate().toString("yyyy.MM.dd"));

}
