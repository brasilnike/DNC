#include "TreeGame.h"
#include <QtWidgets/qboxlayout.h>
#include <ctime>
#include <QTime>
#include <QTimer>
#include <qpainter.h>
TreeGame::TreeGame(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    ui.stackedWidget->installEventFilter(this);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCountdown()));
    timer->start(1000);
    time.setHMS(0, 20, 0);
}

TreeGame::~TreeGame()
{
}

void TreeGame::updateCountdown()
{
	time = time.addSecs(-1);
	ui.time_remaining->setText(time.toString("mm:ss"));
    if (ui.time_remaining->text() == "19:59")
    {
        m_currDogs++;
        ui.catelusiText->setText(QString::number(m_currDogs));
        m_accDogs++;
        ui.catelusiContText->setText(QString::number(m_accDogs));
    }
	if (ui.time_remaining->text() == "19:59")
	{
        time.setHMS(0, 20, 0);
	}
}

void TreeGame::on_startGameButton_pressed()
{
    ui.stackedWidget->setCurrentIndex(ui.stackedWidget->currentIndex() + 1);
}

bool TreeGame::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == ui.stackedWidget)
    {
        if (event->type() == QEvent::Leave)
        {
            timer->stop();
            ui.time_remaining->setText("Ati incercat sa trisati");
            qDebug() << tr("Button event monitored, mouse left button event");
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}