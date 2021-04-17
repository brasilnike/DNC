#pragma once

#include <QWidget>
#include "ui_test.h"

class test : public QWidget
{
	Q_OBJECT

public:
	test(QWidget *parent = Q_NULLPTR);
	~test();

private:
	Ui::test ui;
};
