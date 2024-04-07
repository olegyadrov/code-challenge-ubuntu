#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class UbuntuReleaseInfoProvider: public QObject
{
    Q_OBJECT

public:
    /**
     * Constructs an UbuntuReleaseInfoProvider instance.
     *
     * @param qnamInstance A shared QNetworkAccessManager instance used by the app.
     * @param parent The parent QObject.
     */
    UbuntuReleaseInfoProvider(QNetworkAccessManager* qnamInstance, QObject* parent = nullptr);
    /**
     * Initiates the download of the release data.
     */
    void fetch();
    /**
     * @return A list of all currently supported Ubuntu releases (e.g., "20.04 LTS, 22.04 LTS, 23.10").
     */
    QList<QString> getSupportedReleases();
    /**
     * @return A string representing the current LTS version (e.g., "22.04").
     */
    QString getCurrentLtsVersion();
    /**
     * @param release The target Ubuntu release version (e.g., "20.04").
     * @return A string containing the SHA-256 checksum of the 'disk1.img' for the specified release.
     */
    QString getReleaseSha256(const QString& release);

signals:
    /**
     * Emitted when the JSON data has been successfully parsed.
     */
    void finished();
    /**
     * Emitted in case of a network error or if the fetched JSON data is invalid.
     *
     * @param reason A string describing the error.
     */
    void errorOccurred(const QString& reason);

private slots:
    /**
     * Slot to handle the network reply once the data is ready to be read.
     * Parses the reply and emits the appropriate signal based on the result.
     */
    void processReply();

private:
    QNetworkAccessManager* m_qnamInstance; // Network access manager for handling requests
    QNetworkReply* m_reply; // Network reply object for the current request
    QJsonDocument m_document; // JSON document parsed from the reply
};
