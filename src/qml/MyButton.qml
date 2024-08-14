import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


Rectangle {
    property color staticButtonColor: "#212224"
    property color hoveredButtonColor: "#4a4c4f"
    property string buttonText
    property int fontPointSize

    id: button
    radius: height / 4
    color: staticButtonColor
    state: "normal"

    signal clickedFoo();

    Text {
        text: buttonText
        anchors.centerIn: button
        font.pointSize: fontPointSize
        color: "white"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: button
        onEntered: {
            button.state = "hovered"
        }

        onExited: {
            button.state = "normal"
        }

        onClicked: {
            clickedFoo();
        }
    }

    states: [
        State {
            name: "normal"
            PropertyChanges {
                target: button
                color: staticButtonColor
            }
        },

        State {
            name: "hovered"
            PropertyChanges {
                target: button
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
                target: button
                property: "color"
                duration: 200
            }
        }
    ]
}
