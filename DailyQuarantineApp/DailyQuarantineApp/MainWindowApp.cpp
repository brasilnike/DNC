#include "MainWindowApp.h"

MainWindowApp::MainWindowApp(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
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

