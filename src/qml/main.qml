import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    maximumWidth: 1366
    minimumWidth: 1366
    maximumHeight: 768
    minimumHeight: 768

    property color windowColor: "#7d7d7d"
    property color standardTextColor: "#1c1919"

    Rectangle {
        anchors.fill: parent
        color: windowColor
    }

    SearchButton {
        id: searchButton
        anchors {
            bottom: parent.bottom
            bottomMargin: 10
            horizontalCenter:parent.horizontalCenter
        }

        MouseArea {
            // onClicked: {  //search
            // }
        }
    }

    Item {
        id: queries
        width: parent.width
        height: parent.height / 3
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 10
        }

        Rectangle {
            id: backGround
            anchors.fill: parent
            color: windowColor
            border {
                color: "black"
                width: 6
            }
        }

        Text {
            id: title
            anchors {
                top: parent.top
                horizontalCenter: parent.horizontalCenter
            }
            text: "Queries"
            color: "white "
            font.pointSize: 25
        }
    }
}














