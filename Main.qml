import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Application Launcher")

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "Select an application to launch:"
            font.pixelSize: 16
        }

        Repeater {
            model: AppLauncher.getAppNames()

            Button {
                text: modelData
                onClicked: {
                    AppLauncher.launchApp(modelData)
                }
            }
        }

        Button {
            text: "Add Application"
            onClicked: {
                addAppDialog.open()
            }
        }
    }

    Dialog {
        id: addAppDialog
        modal: true
        visible: false
        title: "Add Application"

        ColumnLayout {
            spacing: 10
            TextField {
                id: appNameField
                placeholderText: "Enter application name"
            }
            TextField {
                id: appPathField
                placeholderText: "Enter application path"
            }
            Button {
                text: "Add"
                onClicked: {
                    AppLauncher.addApplication(appNameField.text, appPathField.text);
                    addAppDialog.close();
                }
            }
            Button {
                text: "Cancel"
                onClicked: addAppDialog.close
            }
        }
    }
}
