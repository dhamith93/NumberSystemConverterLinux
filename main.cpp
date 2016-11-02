#include "numbersystemconverter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NumberSystemConverter w;
    w.show();

    return a.exec();
}
