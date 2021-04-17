#pragma once

#include <QWidget>
#include "ui_CovidPopUp.h"

class CovidPopUp : public QWidget
{
	Q_OBJECT

public:
	CovidPopUp(QWidget *parent = Q_NULLPTR);
	~CovidPopUp();

private:
	Ui::CovidPopUp ui;
};
