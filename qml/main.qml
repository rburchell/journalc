import QtQuick 2.3
import QtQuick.Controls 1.3
import JournalC 1.0

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
                color: {
                    var rating = model.priority;
                    var R = (7 - rating) / 7
                    var G = rating / 7

                    return Qt.rgba(R, G, 0, 0.3)
                }

                width: ListView.view.width
                height: 30

                Text {
                    anchors.centerIn: parent
                    text: model.message
                }
            }
        }
    }
}
