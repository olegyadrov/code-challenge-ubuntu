#include "UbuntuReleaseInfoProvider.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QNetworkAccessManager qnamInstance;
    UbuntuReleaseInfoProvider infoProvider(&qnamInstance);
    QObject::connect(&infoProvider, &UbuntuReleaseInfoProvider::finished, [&infoProvider]()
    {
        qInfo().noquote() << infoProvider.getSupportedReleases().join(", ");
        qInfo().noquote() << infoProvider.getCurrentLtsVersion();
        qInfo().noquote() << infoProvider.getReleaseSha256("22.04");
        QCoreApplication::quit();
    });
    QObject::connect(&infoProvider, &UbuntuReleaseInfoProvider::errorOccurred, [](const QString& reason)
    {
        qCritical().noquote() << reason;
        QCoreApplication::exit(EXIT_FAILURE);
    });
    infoProvider.fetch();

    return app.exec();
}
