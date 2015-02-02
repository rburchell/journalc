import QtQuick 2.3
import QtQuick.Controls 1.3

ApplicationWindow {
    width: 800
    height: 600
    title: "journalc"
    visible: true

    ScrollView {
        anchors.fill: parent
        ListView {
            model: journalModel
            anchors.fill: parent

            delegate: Rectangle {
                color: index % 2 == 0 ? "red" : "blue"
                width: ListView.view.width
                height: 100

                Text {
                    anchors.centerIn: parent
                    text: model.message
                }
            }
        }
    }
}
