#include "UbuntuReleaseInfoProvider.h"

#include <QCommandLineParser>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCommandLineParser clParser;
    clParser.addOption({"c", "Print the current Ubuntu LTS version"});
    clParser.addOption({"h", "Print the sha256 of the disk1.img item of a given Ubuntu release", "release"});
    clParser.addOption({"r", "Print a list of all currently supported Ubuntu releases"});
    clParser.process(app);

    if (clParser.optionNames().empty())
    {
        clParser.showHelp();
    }

    QNetworkAccessManager qnamInstance;
    UbuntuReleaseInfoProvider infoProvider(&qnamInstance);
    QObject::connect(&infoProvider, &UbuntuReleaseInfoProvider::finished, [&clParser, &infoProvider]()
    {
        if (clParser.isSet("r"))
        {
            const auto supportedReleases = infoProvider.getSupportedReleases();
            qInfo().noquote() << QStringLiteral("Currently supported Ubuntu releases: %1")
                                     .arg(supportedReleases.empty() ? QStringLiteral("Not found")
                                                                    : supportedReleases.join(", "));
        }
        if (clParser.isSet("c"))
        {
            const auto currentLtsVersion = infoProvider.getCurrentLtsVersion();
            qInfo().noquote() << QStringLiteral("Current Ubuntu LTS version: %1")
                                     .arg(currentLtsVersion.isEmpty() ? QStringLiteral("Not found")
                                                                      : currentLtsVersion);
        }
        if (clParser.isSet("h"))
        {
            const auto version = clParser.value("h");
            const auto hash = infoProvider.getReleaseSha256(version);
            qInfo().noquote() << (hash.isEmpty() ? QStringLiteral("Release %1 was not found")
                                                       .arg(version)
                                                 : QStringLiteral("The sha256 of the disk1.img item of the %1 Ubuntu release: %2")
                                                       .arg(version, hash));
        }
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
