#pragma once

#include <QWidget>
#include <QNetworkAccessManager>

class QLineEdit;
class QComboBox;
class QPushButton;
class QLabel;

class TranslatorWidget : public QWidget {
    Q_OBJECT

public:
    TranslatorWidget(QWidget *parent = nullptr);

private slots:
    void translateText();

private:
    QLineEdit *inputField;
    QComboBox *langCombo;
    QPushButton *translateBtn;
    QLabel *resultLabel;
    QNetworkAccessManager netManager;
};