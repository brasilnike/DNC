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
#include "Database.h"
#include <User.h>

class TreeGame : public QWidget
{
	Q_OBJECT

public:
	TreeGame(QWidget *parent = Q_NULLPTR);
	~TreeGame();
	QTime time;
	QTimer* timer;

public:
	void setStmt(const SQLHANDLE& stmt);
	void setUser(User user);

private:
	Ui::TreeGame ui;

protected:
	bool eventFilter(QObject* watched, QEvent* event);
	void showEvent(QShowEvent* ev);

private:
	int m_accDogs;
	int m_currDogs = 0;
	SQLHANDLE m_stmt;
	User m_user;

private slots:
	void on_startGameButton_pressed();
	void on_GameReturnButton_pressed();
	void updateCountdown();
	void updateUserTable();
};
