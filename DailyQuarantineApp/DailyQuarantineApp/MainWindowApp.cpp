#include "MainWindowApp.h"

#define SQL_RESULT_LEN 1000

MainWindowApp::MainWindowApp(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	statistics();
}

MainWindowApp::~MainWindowApp()
{
	ui.stackedWidget->setCurrentIndex(int(Pages::Principal));
}

void MainWindowApp::setHandle(const SQLHANDLE& sqlStmtHandle)
{
	m_sqlStmtHandle = sqlStmtHandle;
}

void MainWindowApp::setUser(User&& user)
{
	m_user = std::move(user);
}

void MainWindowApp::on_calendarButton_pressed()
{
	ui.stackedWidget->setCurrentIndex(int(Pages::Calendar));
	getAllNotes();
	for (Notes note : m_listNotes)
	{
		ui.listWidget->addItem(QString::number(note.getNotesId()) + " " + QString::fromStdString(note.getNoteTitle()));
	}
}

void MainWindowApp::on_medicButton_pressed()
{
	ui.stackedWidget->setCurrentIndex(int(Pages::Medic));
}

void MainWindowApp::on_covidButton_pressed()
{
	ui.stackedWidget->setCurrentIndex(int(Pages::Covid));
}

void MainWindowApp::on_calendarWidget_clicked()
{
	ui.stackedWidget->setCurrentIndex(int(Pages::Notes));
}

void MainWindowApp::on_addNoteButton_pressed()
{
	int listSize = m_listNotes.size();
	Notes aux(m_user.getId(), listSize, ui.notes->toPlainText().toStdString(), ui.title->toPlainText().toStdString(), QDate::currentDate().toString().toStdString());
	m_listNotes.push_back(aux);
	ui.listWidget->addItem(QString::number(aux.getNotesId()) + " " + QString::fromStdString(aux.getNoteTitle()));
	ui.stackedWidget->setCurrentIndex(int(Pages::Calendar));
	insertNote(aux);
}

void MainWindowApp::on_MedicReturnButton_pressed()
{
	ui.stackedWidget->setCurrentIndex(int(Pages::Principal));
}

void MainWindowApp::on_SendEmailButton_pressed()
{
	std::cout << "EMAIL TEST" << std::endl;

	std::string emailTime = m_email.dateTimeToString(m_email.currentTime(), "%A %B, %d %Y %I:%M%p");
	std::string patientName = ui.email_name->toPlainText().toUtf8().constData();
	std::string emailContent = ui.email_content->toPlainText().toUtf8().constData();
	
	m_email.setName("Daily Quarantine App");
	m_email.setAdress(ui.email_medic_email->toPlainText().toUtf8().constData());
	m_email.setSubject(ui.email_title->toPlainText().toUtf8().constData());
	m_email.setMessage("Patient name: "+ patientName +" \n" + "Content: "+emailContent+"\n"+"Time when the email was send: "+ emailTime);

	if (m_email.sendMail());
}

void MainWindowApp::on_CalendarReturnButton_pressed()
{
	ui.stackedWidget->setCurrentIndex(int(Pages::Principal));
}

void MainWindowApp::on_listWidget_itemDoubleClicked()
{
	m_noteSelected.show();
	for (Notes note : m_listNotes)
	{
		QString s1 = ui.listWidget->selectedItems()[0]->text();
		QString s2 = QString::number(note.getNotesId());
		s2.append(" ");
		s2.append(QString::fromStdString(note.getNoteTitle()));
		if (QString::compare(s1, s2) == 0)
		{
			m_currentNote = note;
			ui.listWidget->clearSelection();
			break;
		}
	}

	m_noteSelected.getUi().noteIdText->setText(QString::fromStdString(std::to_string(m_currentNote.getNotesId())));
	m_noteSelected.getUi().noteTitleText->setText(QString::fromStdString(m_currentNote.getNoteTitle()));
	m_noteSelected.getUi().noteTextText->setText(QString::fromStdString(m_currentNote.getNoteText()));
	m_noteSelected.getUi().noteDateText->setText(QString::fromStdString(m_currentNote.getDate()));

}

void MainWindowApp::insertNote(const Notes& note)
{
	int userId = note.getUserId();
	std::string title = note.getNoteTitle();
	std::string content= note.getNoteText();
	std::string date = note.getDate();
	SQLRETURN retcode = SQLPrepare(m_sqlStmtHandle, (SQLWCHAR*)L"INSERT INTO Notes (user_id, notes_title, notes_content,notes_date) VALUES(?,?,?,?) ", SQL_NTS);
	retcode = SQLBindParameter(m_sqlStmtHandle, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &userId, 0, NULL);
	retcode = SQLBindParameter(m_sqlStmtHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, (SQLPOINTER)title.c_str(), title.length(), NULL);
	retcode = SQLBindParameter(m_sqlStmtHandle, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 300, 0, (SQLPOINTER)content.c_str(), content.length(), NULL);
	retcode = SQLBindParameter(m_sqlStmtHandle, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, (SQLPOINTER)date.c_str(), date.length(), NULL);
	retcode = SQLExecute(m_sqlStmtHandle);

	if (SQL_SUCCESS != retcode) {
		std::cout << "ERROR" << std::endl;
	}
	else {

		SQLFreeStmt(m_sqlStmtHandle, SQL_CLOSE);
	}
}

void MainWindowApp::getAllNotes()
{
	std::string query_string = "SELECT notes_id, notes_title, notes_content, notes_date FROM Notes WHERE user_id=" + std::to_string(m_user.getId());
	std::wstring  query_wstring(query_string.begin(), query_string.end());
	SQLWCHAR* SQLQuery = (SQLWCHAR*)query_wstring.c_str();

	if (SQL_SUCCESS != SQLExecDirect(m_sqlStmtHandle, SQLQuery, SQL_NTS))
	{
		std::cout << "ERROR2" << std::endl;
	}
	else {

		int notesId;
		char noteTitle[SQL_RESULT_LEN];
		char noteText[SQL_RESULT_LEN];
		char date[SQL_RESULT_LEN];

		while (SQLFetch(m_sqlStmtHandle) == SQL_SUCCESS)
		{

			SQLGetData(m_sqlStmtHandle, 1, SQL_C_DEFAULT, &notesId, sizeof(notesId), NULL);
			SQLGetData(m_sqlStmtHandle, 2, SQL_C_DEFAULT, &noteTitle, sizeof(noteTitle), NULL);
			SQLGetData(m_sqlStmtHandle, 3, SQL_C_DEFAULT, &noteText, sizeof(noteText), NULL);
			SQLGetData(m_sqlStmtHandle, 4, SQL_C_DEFAULT, &date, sizeof(date), NULL);
			Notes note(m_user.getId(),notesId,noteText,noteTitle, date);
			m_listNotes.push_back(note);
		}

		SQLFreeStmt(m_sqlStmtHandle, SQL_CLOSE);
	}
}

static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
{
	std::string& text = *static_cast<std::string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}

void MainWindowApp::statistics()
{
	std::string result;
	CURL* curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://www.graphs.ro/json.php");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (CURLE_OK != res) {
			std::cerr << "CURL error: " << res << '\n';
		}
	}
	curl_global_cleanup();
	//std::cout << result << "\n\n";
	std::ofstream write("test.json");
	write << result;
	write.close();

	QFile inFile("test.json");
	inFile.open(QIODevice::ReadOnly | QIODevice::Text);
	QByteArray data = inFile.readAll();
	//data.remove(0, 1);
	//data.remove(data.size() - 2, 1);
	//qDebug() << data.data();


	QTextStream file_text(&inFile);
	QString json_string;
	json_string = file_text.readAll();
	//json_string.replace(QString("["), QString(""));
	//json_string.replace(QString("]"), QString(""));

	//qDebug() << json_string;

	inFile.close();
	QByteArray json_bytes = json_string.toLocal8Bit();

	auto json_doc = QJsonDocument::fromJson(data);

	QString totalCases = json_doc.object().value("covid_romania").toArray()[0].toObject().value("total_cases").toVariant().toString();
	qDebug() << totalCases;

	ui.totalCasesText->setText(totalCases);

	QString newCases = json_doc.object().value("covid_romania").toArray()[0].toObject().value("new_cases_today").toVariant().toString();
	qDebug() << newCases;

	ui.newCasesText->setText(newCases);

	QString totalTest = json_doc.object().value("covid_romania").toArray()[0].toObject().value("total_tests").toVariant().toString();
	qDebug() << totalTest;

	ui.totalTestsText->setText(totalTest);

	QString newTest = json_doc.object().value("covid_romania").toArray()[0].toObject().value("new_tests_today").toVariant().toString();
	qDebug() << newTest;

	ui.newTestsText->setText(newTest);

	QString totalDeaths = json_doc.object().value("covid_romania").toArray()[0].toObject().value("total_deaths").toVariant().toString();
	qDebug() << totalDeaths;

	ui.totalDeathsText->setText(totalDeaths);

	QString newDeathsToday = json_doc.object().value("covid_romania").toArray()[0].toObject().value("new_deaths_today").toVariant().toString();
	qDebug() << newDeathsToday;

	ui.newDeathsTodayText->setText(newDeathsToday);

	QString totalRecovered = json_doc.object().value("covid_romania").toArray()[0].toObject().value("total_recovered").toVariant().toString();
	qDebug() << totalRecovered;

	ui.totalRecoveredText->setText(totalRecovered);

	QString newRecoveredToday = json_doc.object().value("covid_romania").toArray()[0].toObject().value("new_recovered_today").toVariant().toString();
	qDebug() << newRecoveredToday;

	ui.newRecoveredTodayText->setText(newRecoveredToday);

	QString intensiveCareRightNow = json_doc.object().value("covid_romania").toArray()[0].toObject().value("intensive_care_right_now").toVariant().toString();
	qDebug() << intensiveCareRightNow;

	ui.IntensiveCareRightNowText->setText(intensiveCareRightNow);


	if (json_doc.isNull()) {
		qDebug() << "Failed to create JSON doc.";
		exit(2);
	}
	if (!json_doc.isObject()) {
		qDebug() << "JSON is not an object.";
		exit(3);
	}

	QJsonObject json_obj = json_doc.object();

	if (json_obj.isEmpty()) {
		qDebug() << "JSON object is empty.";
		exit(4);
	}

	QVariantMap json_map = json_obj.toVariantMap();


	std::string resultVaccinare;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://www.graphs.ro/vaccinare_json.php");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resultVaccinare);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (CURLE_OK != res) {
			std::cerr << "CURL error: " << res << '\n';
		}
	}
	curl_global_cleanup();
	//std::cout << resultVaccinare << "\n\n";

	std::ofstream writeVaccinare("vaccinare.json");
	writeVaccinare << resultVaccinare;
	writeVaccinare.close();

	QFile inFile2("vaccinare.json");
	inFile2.open(QIODevice::ReadOnly | QIODevice::Text);
	QByteArray data2 = inFile2.readAll();

	auto json_doc2 = QJsonDocument::fromJson(data2);

	QString totalVaccines = json_doc2.object().value("covid_romania_vaccination").toArray()[0].toObject().value("total_doze").toVariant().toString();
	qDebug() << totalVaccines;

	ui.totalDosesText->setText(totalVaccines);

	QString total1 = json_doc2.object().value("covid_romania_vaccination").toArray()[0].toObject().value("total_1").toVariant().toString();
	qDebug() << total1;

	ui.totalVaccinated1Text->setText(total1);

	QString total2 = json_doc2.object().value("covid_romania_vaccination").toArray()[0].toObject().value("total_2").toVariant().toString();
	qDebug() << total2;

	ui.totalVaccinated2Text->setText(total2);
}
