#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DailyQuarantineApp.h"

class DailyQuarantineApp : public QMainWindow
{
    Q_OBJECT

public:
    DailyQuarantineApp(QWidget *parent = Q_NULLPTR);

private:
    Ui::DailyQuarantineAppClass ui;
};
