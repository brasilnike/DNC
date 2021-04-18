#include "CovidPopUp.h"

static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
{
	std::string& text = *static_cast<std::string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}


CovidPopUp::CovidPopUp(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
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

	QString totalCases =  json_doc.object().value("covid_romania").toArray()[0].toObject().value("total_cases").toVariant().toString();
	qDebug() << totalCases;
	QString newCases = json_doc.object().value("covid_romania").toArray()[0].toObject().value("new_cases_today").toVariant().toString();
	qDebug() << newCases;
	QString totalTest = json_doc.object().value("covid_romania").toArray()[0].toObject().value("total_tests").toVariant().toString();
	qDebug() << totalTest;
	QString newTest = json_doc.object().value("covid_romania").toArray()[0].toObject().value("new_tests_today").toVariant().toString();
	qDebug() << newTest;
	QString totalDeaths = json_doc.object().value("covid_romania").toArray()[0].toObject().value("total_deaths").toVariant().toString();
	qDebug() << totalDeaths;
	QString newDeathsToday = json_doc.object().value("covid_romania").toArray()[0].toObject().value("new_deaths_today").toVariant().toString();
	qDebug() << newDeathsToday;
	QString totalRecovered = json_doc.object().value("covid_romania").toArray()[0].toObject().value("total_recovered").toVariant().toString();
	qDebug() << totalRecovered;
	QString newRecoveredToday = json_doc.object().value("covid_romania").toArray()[0].toObject().value("new_recovered_today").toVariant().toString();
	qDebug() << newRecoveredToday;
	QString intensiveCareRightNow = json_doc.object().value("covid_romania").toArray()[0].toObject().value("intensive_care_right_now").toVariant().toString();
	qDebug() << intensiveCareRightNow;



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
	QString total1 = json_doc2.object().value("covid_romania_vaccination").toArray()[0].toObject().value("total_1").toVariant().toString();
	qDebug() << total1;
	QString total2 = json_doc2.object().value("covid_romania_vaccination").toArray()[0].toObject().value("total_2").toVariant().toString();
	qDebug() << total2;
}


CovidPopUp::~CovidPopUp()
{
}

