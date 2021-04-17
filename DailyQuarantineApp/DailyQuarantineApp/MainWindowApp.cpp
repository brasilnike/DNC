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
