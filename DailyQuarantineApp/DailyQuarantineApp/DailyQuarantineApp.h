#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DailyQuarantineApp.h"
#include "MainWindowApp.h"


class DailyQuarantineApp : public QMainWindow
{
    Q_OBJECT

public:
    DailyQuarantineApp(QWidget *parent = Q_NULLPTR);

private:
    Ui::DailyQuarantineAppClass ui;

private slots:
    void on_loggingButton_pressed();

private:
    MainWindowApp m_mainFrame;
};
