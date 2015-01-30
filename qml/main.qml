import QtQuick 2.3

Item {
    width: 800
    height: 600

    ListView {
        model: journalModel
        anchors.fill: parent

        delegate: Rectangle {
            color: index % 2 == 0 ? "red" : "blue"
            width: ListView.view.width
            height: 100
        }
    }
}
