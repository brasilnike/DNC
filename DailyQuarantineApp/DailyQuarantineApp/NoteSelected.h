#pragma once

#include <QWidget>
#include "ui_NoteSelected.h"

class NoteSelected : public QWidget
{
	Q_OBJECT

public:
	NoteSelected(QWidget *parent = Q_NULLPTR);
	~NoteSelected();

private:
	Ui::NoteSelected ui;

public:
	Ui::NoteSelected getUi();

private slots:
	void on_backButton_pressed();
};
