#ifndef APPLAUNCHER_H
#define APPLAUNCHER_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QMap>
#include <QXmlStreamReader>
#include <QFile>

class AppLauncher : public QObject {
    Q_OBJECT
public:
    explicit AppLauncher(QObject *parent = nullptr);

    Q_INVOKABLE QStringList getAppNames();
    Q_INVOKABLE void launchApp(const QString &appName);
    Q_INVOKABLE void addApplication(const QString &appName, const QString &appPath);


    void loadApplications(const QString &xmlPath);

private:
    QMap<QString, QString> appMap; // Map of appName -> appPath
};

#endif // APPLAUNCHER_H
