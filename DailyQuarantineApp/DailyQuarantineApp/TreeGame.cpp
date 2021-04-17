#include "TreeGame.h"
#include <QtWidgets/qboxlayout.h>

TreeGame::TreeGame(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
    //ui.stackedWidget = new QLabel();
    ui.stackedWidget->installEventFilter(this);

    /*QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(ui.stackedWidget);
    mainLayout->addStretch();
    this->setLayout(mainLayout);*/
}

TreeGame::~TreeGame()
{
}

bool TreeGame::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == ui.stackedWidget)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            qDebug() << tr("Button event is monitored, mouse enter button event");
            return true;
        }
        if (event->type() == QEvent::Leave)
        {
            qDebug() << tr("Button event monitored, mouse left button event");
            return true;
        }
        /*if (event->type() == QEvent::FocusOut)
        {
            qDebug() << tr("Button event is monitored, mouse enter button event");
            return true;
        }
        else 
        else if (event->type() == QEvent::MouseButtonPress)
        {
            qDebug() << tr("Button event is monitored, mouse click button event");
            return true;
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            qDebug() << tr("Button event monitored, mouse release button event");
            return true;
        }
        else if (event->type() == QEvent::MouseMove)
        {
            qDebug() << tr("Button event monitored, mouse release button event");
            return true;
        }*/
    }
    return QWidget::eventFilter(watched, event);
}