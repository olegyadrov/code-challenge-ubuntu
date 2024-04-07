#include "UbuntuReleaseInfoProvider.h"

#include <QCoreApplication>

const QString UBUNTU_CLOUD_RELEASES_URL = QStringLiteral("https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json");

UbuntuReleaseInfoProvider::UbuntuReleaseInfoProvider(QNetworkAccessManager* qnamInstance, QObject* parent)
    : QObject(parent)
    , m_qnamInstance(qnamInstance)
    , m_reply(nullptr)
{
    if (qnamInstance == nullptr)
    {
        qCritical().noquote() << "A valid QNetworkAccessManager instance is required!";
        QCoreApplication::exit(EXIT_FAILURE);
    }
}

void UbuntuReleaseInfoProvider::fetch()
{
    if (m_reply)
    {
        disconnect(m_reply, &QNetworkReply::finished, this, &UbuntuReleaseInfoProvider::processReply);
        m_reply->deleteLater();
    }
    QNetworkRequest request(UBUNTU_CLOUD_RELEASES_URL);
    m_reply = m_qnamInstance->get(request);
    connect(m_reply, &QNetworkReply::finished, this, &UbuntuReleaseInfoProvider::processReply);
}

void UbuntuReleaseInfoProvider::processReply()
{
    if (m_reply->error() != QNetworkReply::NoError)
    {
        emit errorOccurred(m_reply->errorString());
        m_reply->deleteLater();
        m_reply = nullptr;
        return;
    }
    QString json = m_reply->readAll();
    qDebug() << json;
    m_reply->deleteLater();
    m_reply = nullptr;
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
