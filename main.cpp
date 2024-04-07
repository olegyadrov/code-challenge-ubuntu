#include "UbuntuReleaseInfoProvider.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    UbuntuReleaseInfoProvider infoProvider;
    QObject::connect(&infoProvider, &UbuntuReleaseInfoProvider::finished, [&infoProvider]()
    {

    });
    QObject::connect(&infoProvider, &UbuntuReleaseInfoProvider::errorOccurred, [](const QString& reason)
    {

    });
    infoProvider.fetch();

    return app.exec();
}
