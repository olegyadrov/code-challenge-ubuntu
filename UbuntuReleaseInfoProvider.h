#include <QNetworkAccessManager>
#include <QNetworkReply>

class UbuntuReleaseInfoProvider: public QObject
{
    Q_OBJECT

public:
    UbuntuReleaseInfoProvider(QNetworkAccessManager* qnamInstance, QObject* parent = nullptr);
    void fetch();
    QList<QString> getSupportedReleases();
    QString getCurrentLtsVersion();
    QString getReleaseSha256(const QString& release);

signals:
    void finished();
    void errorOccurred(const QString& reason);

private slots:
    void processReply();

private:
    QNetworkAccessManager* m_qnamInstance;
    QNetworkReply* m_reply;
};
