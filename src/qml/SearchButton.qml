import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


Item {
    id: button // Ensure this ID is unique and correctly used
    height: 100
    width: 170
    property color staticButtonColor: "#212224"
    property color hoveredButtonColor: "#4a4c4f"

    Rectangle {
        id: backGround
        anchors.fill: parent
        radius: height / 4
        color: staticButtonColor
    }

    Text {
        text: "Search"
        anchors.centerIn: parent
        font.pointSize: 20
        color: "white"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: backGround
        onEntered: {
            button.state = "hovered"
        }

        onExited: {
            button.state = "normal"
        }
    }

    states: [
        State {
            name: "normal"
            PropertyChanges {
                target: backGround
                color: staticButtonColor
            }
        },

        State {
            name: "hovered"
            PropertyChanges {
                target: backGround
                color: hoveredButtonColor
            }
        }
    ]

    transitions: [
        Transition {
            from: "normal"
            to: "hovered"
            reversible: true
            ColorAnimation {
                target: backGround
                property: "color"
                duration: 200
            }
        }
    ]
}
