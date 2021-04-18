#include "NoteSelected.h"

NoteSelected::NoteSelected(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

NoteSelected::~NoteSelected()
{
}

Ui::NoteSelected NoteSelected::getUi()
{
	return ui;
}

void NoteSelected::on_backButton_pressed()
{
	this->hide();
}
