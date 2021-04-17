#pragma once

#include <QWidget>
#include "ui_TreeGame.h"

class TreeGame : public QWidget
{
	Q_OBJECT

public:
	TreeGame(QWidget *parent = Q_NULLPTR);
	~TreeGame();

private:
	Ui::TreeGame ui;
};
