#include <QApplication>
#include "TranslatorWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    TranslatorWidget window;
    window.show();
    return app.exec();
}