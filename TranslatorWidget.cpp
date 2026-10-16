#include "TranslatorWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>

TranslatorWidget::TranslatorWidget(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Traducteur Qt");
    resize(400, 200);

    auto *layout = new QVBoxLayout(this);

    inputField = new QLineEdit(this);
    inputField->setPlaceholderText("Entrez un mot en français...");

    langCombo = new QComboBox(this);
    langCombo->addItem("Anglais", "en");
    langCombo->addItem("Espagnol", "es");
    langCombo->addItem("Allemand", "de");
    langCombo->addItem("Italien", "it");

    translateBtn = new QPushButton("Traduire", this);
    resultLabel = new QLabel("Traduction : ", this);
    resultLabel->setWordWrap(true);

    auto *controlsLayout = new QHBoxLayout();
    controlsLayout->addWidget(langCombo);
    controlsLayout->addWidget(translateBtn);

    layout->addWidget(inputField);
    layout->addLayout(controlsLayout);
    layout->addWidget(resultLabel);

    connect(translateBtn, &QPushButton::clicked, this, &TranslatorWidget::translateText);
    connect(inputField, &QLineEdit::returnPressed, this, &TranslatorWidget::translateText);
}

void TranslatorWidget::translateText() {
    QString text = inputField->text().trimmed();
    if (text.isEmpty()) return;

    QString targetLang = langCombo->currentData().toString();

    QUrl url("https://api.mymemory.translated.net/get");
    QUrlQuery query;
    query.addQueryItem("q", text);
    query.addQueryItem("langpair", QString("fr|%1").arg(targetLang));
    url.setQuery(query);

    QNetworkRequest request(url);
    resultLabel->setText("Traduction en cours...");

    QNetworkReply *reply = netManager.get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument json = QJsonDocument::fromJson(response);
            QString translated = json.object()["responseData"].toObject()["translatedText"].toString();
            resultLabel->setText("Traduction : " + translated);
        } else {
            resultLabel->setText("Erreur réseau : " + reply->errorString());
        }
        reply->deleteLater();
    });
}