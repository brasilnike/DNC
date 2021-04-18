#pragma once

#include <QWidget>
#include "ui_TreeGame.h"
#include <QMessageBox>
#include <QWidget>
#include <QPushButton>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include <qstackedwidget.h>
#include <QTime>

class TreeGame : public QWidget
{
	Q_OBJECT

public:
	TreeGame(QWidget *parent = Q_NULLPTR);
	~TreeGame();
	QTime time;
	QTimer* timer;
private:
	Ui::TreeGame ui;

protected:
	bool eventFilter(QObject* watched, QEvent* event);

private:
	//void setupUI();
	//QStackedWidget* stackedWidget;
	int m_accDogs = 0;
	int m_currDogs = 0;

private slots:
	void on_startGameButton_pressed();
	void updateCountdown();
};
