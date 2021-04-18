#pragma once
#define CURL_STATICLIB
#include <QWidget>
#include "ui_CovidPopUp.h"
#include "curl/curl.h"
#include <iostream>
#include <fstream>
#include <qfile.h>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

class CovidPopUp : public QWidget
{
	Q_OBJECT

public:
	CovidPopUp(QWidget *parent = Q_NULLPTR);
	~CovidPopUp();

private:
	Ui::CovidPopUp ui;
};
