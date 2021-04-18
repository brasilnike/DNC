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
}

TreeGame::~TreeGame()
{
}

void TreeGame::setStmt(const SQLHANDLE& stmt)
{
    m_stmt = stmt;
}

void TreeGame::setUser(User user)
{
    m_user = user;
}

void TreeGame::on_GameReturnButton_pressed()
{
    updateUserTable();
    close();
}

void TreeGame::updateCountdown()
{
	time = time.addSecs(-1);
	ui.time_remaining->setText(time.toString("mm:ss"));
    if (ui.time_remaining->text() == "00:01")
    {
        m_currDogs++;
        ui.catelusiText->setText(QString::number(m_currDogs));
        ui.catelusiContText->setText(QString::number(m_accDogs));
        time.setHMS(0, 20, 0);
    }
}

void TreeGame::updateUserTable()
{
    if (!cheated)
    {
        std::string query_string = "UPDATE Users SET nr_dogs = ? WHERE user_id = ?";
        std::wstring  query_wstring(query_string.begin(), query_string.end());
        SQLWCHAR* SQLQuery = (SQLWCHAR*)query_wstring.c_str();
        int id = m_user.getId();
        int count = m_accDogs + m_currDogs;
        SQLRETURN retcode = SQLPrepare(m_stmt, SQLQuery, SQL_NTS);
        retcode = SQLBindParameter(m_stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &count, 0, NULL);
        retcode = SQLBindParameter(m_stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &id, 0, NULL);

        retcode = SQLExecute(m_stmt);

        if (SQL_SUCCESS != retcode) {
            std::cout << "ERROR UPDATE" << std::endl;

        }

        SQLFreeStmt(m_stmt, SQL_CLOSE);
    }
}

void TreeGame::on_startGameButton_pressed()
{
    ui.stackedWidget->setCurrentIndex(ui.stackedWidget->currentIndex() + 1);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCountdown()));
    timer->start(1000);
    time.setHMS(0, 20, 0);
}

bool TreeGame::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == ui.stackedWidget)
    {
        if (event->type() == QEvent::Leave)
        {
            timer->stop();
            ui.time_remaining->setText("You tried to cheat. Not cool.");
            qDebug() << tr("Button event monitored, mouse left button event");
            cheated = true;
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void TreeGame::showEvent(QShowEvent* ev)
{
    QWidget::showEvent(ev);
    m_accDogs = m_user.getDogs();
}
