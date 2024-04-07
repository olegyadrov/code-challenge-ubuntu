#include "UbuntuReleaseInfoProvider.h"

#include <QCoreApplication>
#include <QJsonObject>

const QString ALIAS_DEFAULT = QStringLiteral("default");
const QString ALIAS_LTS = QStringLiteral("lts");
const QString JSON_KEY_ALIASES = QStringLiteral("aliases");
const QString JSON_KEY_DISK1IMG = QStringLiteral("disk1.img");
const QString JSON_KEY_ITEMS = QStringLiteral("items");
const QString JSON_KEY_PRODUCTS = QStringLiteral("products");
const QString JSON_KEY_RELEASE_TITLE = QStringLiteral("release_title");
const QString JSON_KEY_SHA256 = QStringLiteral("sha256");
const QString JSON_KEY_SUPPORTED = QStringLiteral("supported");
const QString JSON_KEY_VERSION = QStringLiteral("version");
const QString JSON_KEY_VERSIONS = QStringLiteral("versions");
const QString TARGET_RELEASE_ARCHITECTURE = QStringLiteral("amd64");
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
    QJsonParseError jsonParseError;
    m_document = QJsonDocument::fromJson(m_reply->readAll(), &jsonParseError);
    m_reply->deleteLater();
    m_reply = nullptr;
    if (jsonParseError.error == QJsonParseError::NoError)
    {
        emit finished();
    }
    else
    {
        emit errorOccurred(jsonParseError.errorString());
    }
}

QList<QString> UbuntuReleaseInfoProvider::getSupportedReleases()
{
    if (m_document.isNull())
    {
        return {};
    }
    QList<QString> supportedReleases;
    const auto productsJson = m_document.object()[JSON_KEY_PRODUCTS].toObject();
    const auto products = productsJson.keys();
    for (const auto& product : products)
    {
        if (!product.endsWith(TARGET_RELEASE_ARCHITECTURE))
        {
            continue;
        }
        const auto productJson = productsJson[product].toObject();
        if (productJson[JSON_KEY_SUPPORTED].toBool())
        {
            supportedReleases.push_back(productJson[JSON_KEY_RELEASE_TITLE].toString());
        }
    }
    return supportedReleases;
}

QString UbuntuReleaseInfoProvider::getCurrentLtsVersion()
{
    if (m_document.isNull())
    {
        return {};
    }
    const auto productsJson =  m_document.object()[JSON_KEY_PRODUCTS].toObject();
    const auto products = productsJson.keys();
    for (const auto& product : products)
    {
        if (!product.endsWith(TARGET_RELEASE_ARCHITECTURE))
        {
            continue;
        }
        const auto productJson = productsJson[product].toObject();
        const auto aliases = productJson[JSON_KEY_ALIASES].toString().split(',');
        if (aliases.contains(ALIAS_LTS) && aliases.contains(ALIAS_DEFAULT))
        {
            return productJson[JSON_KEY_VERSION].toString();
        }
    }
    return {};
}

QString UbuntuReleaseInfoProvider::getReleaseSha256(const QString& release)
{
    if (m_document.isNull())
    {
        return {};
    }
    const auto productsJson = m_document.object()[JSON_KEY_PRODUCTS].toObject();
    const auto products = productsJson.keys();
    for (const auto& product : products)
    {
        if (!product.endsWith(TARGET_RELEASE_ARCHITECTURE))
        {
            continue;
        }
        const auto productJson = productsJson[product].toObject();
        if (productJson[JSON_KEY_VERSION].toString() != release)
        {
            continue;
        }
        const auto versions = productJson[JSON_KEY_VERSIONS].toObject().keys();
        if (versions.empty())
        {
            qWarning() << QStringLiteral("Release %1 has no versions (invalid JSON data?)");
            return {};
        }
        return productJson[JSON_KEY_VERSIONS].toObject()
            [versions.first()].toObject()
            [JSON_KEY_ITEMS].toObject()
            [JSON_KEY_DISK1IMG].toObject()
            [JSON_KEY_SHA256].toString();
    }
    return {};
}
