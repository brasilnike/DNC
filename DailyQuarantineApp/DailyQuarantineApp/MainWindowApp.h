#pragma once

#include <QWidget>
#include "ui_MainWindowApp.h"

class MainWindowApp : public QWidget
{
	Q_OBJECT

public:
	MainWindowApp(QWidget *parent = Q_NULLPTR);
	~MainWindowApp();

private:
	Ui::MainWindowApp ui;
};
