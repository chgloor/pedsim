#include <QApplication>

#include "sender.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Sender sender;
    sender.show();
    return app.exec();
}
