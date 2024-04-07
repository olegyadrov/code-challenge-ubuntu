#include "UbuntuReleaseInfoProvider.h"

#include <QList>
#include <QString>

UbuntuReleaseInfoProvider::UbuntuReleaseInfoProvider(QObject* parent)
    : QObject(parent)
{

}

void UbuntuReleaseInfoProvider::fetch()
{

}

void UbuntuReleaseInfoProvider::processReply()
{

}

QList<QString> UbuntuReleaseInfoProvider::getSupportedReleases()
{
    return QList<QString>();
}

QString UbuntuReleaseInfoProvider::getCurrentLtsVersion()
{
    return QString();
}

QString UbuntuReleaseInfoProvider::getReleaseSha256(const QString& release)
{
    return QString();
}
