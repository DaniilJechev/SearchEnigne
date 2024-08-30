import QtQuick 2.15
import QtQuick.Controls 2.15


Button {
    property string pathToIcon: ""
    signal clickedFoo();

    state: "normal"

    contentItem: Image {
        id: myIcon
        anchors.fill: parent
        source: pathToIcon
        fillMode: Image.PreserveAspectCrop
    }

    background: Rectangle {
        anchors.fill: parent
        color: "transparent"
    }

    MouseArea {
        anchors.fill: parent

        onEntered: {
            parent.state = "hovered"
        }

        onExited: {
            parent.state = "normal"
        }

        onClicked: {
            clickedFoo();
        }
    }


    states: [
        State {
            name: "normal"
            PropertyChanges {
                target: myIcon
                opacity: 1
            }
        },

        State {
            name: "hovered"
            PropertyChanges {
                target: myIcon
                opacity: 0.5
            }
        }
    ]

    transitions: [
        Transition {
            from: "normal"
            to: "hovered"
            reversible: true

            NumberAnimation {
                target: myIcon
                property: "opacity"
                from: 1
                to: 0.5
                duration: 200
            }
        }
    ]

}
