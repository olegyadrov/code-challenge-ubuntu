#include <QObject>

class UbuntuReleaseInfoProvider: public QObject
{
    Q_OBJECT

public:
    UbuntuReleaseInfoProvider(QObject* parent = nullptr);
    void fetch();
    QList<QString> getSupportedReleases();
    QString getCurrentLtsVersion();
    QString getReleaseSha256(const QString& release);

signals:
    void finished();
    void errorOccurred(const QString& reason);

private slots:
    void processReply();
};
