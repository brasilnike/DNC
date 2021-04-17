#pragma once
#define CURL_STATICLIB
#include <QWidget>
#include "ui_CovidPopUp.h"
#include "curl/curl.h"
#include <iostream>

class CovidPopUp : public QWidget
{
	Q_OBJECT

public:
	CovidPopUp(QWidget *parent = Q_NULLPTR);
	~CovidPopUp();

private:
	Ui::CovidPopUp ui;
};
