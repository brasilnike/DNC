#include "DailyQuarantineApp.h"

DailyQuarantineApp::DailyQuarantineApp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void DailyQuarantineApp::on_loggingButton_pressed()
{
    m_mainFrame.show();
    this->hide();
}