#pragma once

#include <QWidget>
#include <iostream>
#include "ui_MainWindowApp.h"

class MainWindowApp : public QWidget
{
	Q_OBJECT

public:
	MainWindowApp(QWidget *parent = Q_NULLPTR);
	~MainWindowApp();

private:
	Ui::MainWindowApp ui;

private slots:
	void on_calendarButton_pressed();
	void on_medicButton_pressed();
	void on_covidButton_pressed();
	void on_calendarWidget_clicked();
};

enum class Pages
{
	Principal,
	Calendar,
	Medic,
	Covid
};