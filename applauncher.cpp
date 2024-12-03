#include "AppLauncher.h"
#include <QDomDocument>
AppLauncher::AppLauncher(QObject *parent) : QObject(parent) {}

void AppLauncher::loadApplications(const QString &xmlPath) {
    QFile file(xmlPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open XML file:" << xmlPath;
        return;
    }

    QXmlStreamReader xml(&file);
    while (!xml.atEnd() && !xml.hasError()) {
        xml.readNext();
        if (xml.isStartElement() && xml.name() == "Application") {
            QString name;
            QString path;

            foreach (const QXmlStreamAttribute &attr, xml.attributes()) {
                if (attr.name().toString() == "name")
                    name = attr.value().toString();
                else if (attr.name().toString() == "path")
                    path = attr.value().toString();
            }

            if (!name.isEmpty() && !path.isEmpty()) {
                appMap[name] = path;
            }
        }
    }

    if (xml.hasError()) {
        qWarning() << "Error parsing XML:" << xml.errorString();
    }
    file.close();
}
void AppLauncher::addApplication(const QString &appName, const QString &appPath) {
    if (appName.isEmpty() || appPath.isEmpty()) {
        qWarning() << "Application name or path is empty.";
        return;
    }

    // Check if the application already exists
    if (appMap.contains(appName)) {
        qWarning() << "Application already exists:" << appName;
        return;
    }

    // Add to the map
    appMap[appName] = appPath;

    // Update the XML file
    QFile file("D:/QTDEMO/AppLauncher/Applications.xml"); // Replace with your XML file path
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Failed to open XML file for writing:" << file.fileName();
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qWarning() << "Failed to parse XML file.";
        file.close();
        return;
    }

    file.close();

    QDomElement root = doc.documentElement();
    QDomElement appElement = doc.createElement("Application");
    appElement.setAttribute("name", appName);
    appElement.setAttribute("path", appPath);
    root.appendChild(appElement);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open XML file for updating:" << file.fileName();
        return;
    }

    QTextStream stream(&file);
    stream << doc.toString();
    file.close();

    qDebug() << "Application added successfully:" << appName;
}

QStringList AppLauncher::getAppNames() {
    return appMap.keys();
}

void AppLauncher::launchApp(const QString &appName) {
    if (!appMap.contains(appName)) {
        qWarning() << "Application not found:" << appName;
        return;
    }

    QString appPath = appMap[appName];
    QProcess *process = new QProcess(this);
    process->start(appPath);

    if (!process->waitForStarted()) {
        qWarning() << "Failed to start application:" << appPath;
    }
}
