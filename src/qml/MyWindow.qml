import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: window
    width: parent.width / 2 - 20
    height: parent.height / 3

    property string title
    property string myPlaceHolderText
    property string windowColor: "#2e2d2d"
    property alias listModel : m_listModel

    Rectangle {
        id: backGroundWindow
        anchors.fill: parent
        color: windowColor
        border {
            color: "black"
            width: 6
        }
    }

    Text {
        id: titleWindow
        text: title
        color: standardTextColor
        anchors {
            bottom: parent.top
            horizontalCenter: parent.horizontalCenter
        }
        font.pointSize: 25
    }

    ListModel {
        id: m_listModel
    }

    ListView {
        id: listView
        model: listModel
        height: parent.height - backGroundWindow.border.width * 4
        width: parent.width - backGroundWindow.border.width * 4
        spacing: 5
        clip: true
        anchors {
            left: parent.left
            top: parent.top
            margins: 10
        }

        ScrollBar.vertical: ScrollBar {
            id: verticalSlider
            anchors {
                right: listView.right
                top: listView.top
            }
            width: 15
        }

        delegate: RowLayout {
            id: myDelegate
            spacing: 10

            Label {
                id: idx
                text: index + 1 + "."
                color: standardTextColor
                font.pointSize: 15
            }

            TextField {
                id: textField
                height: 15
                implicitWidth: window.width - deleteButton.width - idx.width - myDelegate.spacing * 2 - backGroundWindow.border.width * 2 - 15
                text: model.message
                color: standardTextColor
                placeholderText: myPlaceHolderText
                placeholderTextColor: Qt.rgba(255, 255, 255, 0.65)
                font.pointSize: 17

                background: Rectangle {
                    anchors.fill: parent
                    color: windowColor
                }

                onTextEdited: {
                    model.message = text
                }
            }

            MyButton { // delete button
                id: deleteButton
                width: 40
                height: 25
                buttonText: "-"
                    fontPointSize: 15
                    staticButtonColor: "black"

                    onClickedFoo: {
                        m_listModel.remove(index);
                    }
                }
            }
        }

    MyButton { // add new button
        id: addNewButton
        width: 100
        height: 30
        buttonText: "+"
        fontPointSize: 20

        anchors {
            left: parent.left
            top: parent.bottom
            topMargin: 5
        }

        onClickedFoo: {
            m_listModel.append({});
            listView.positionViewAtIndex(m_listModel.count - 1, listView.End);
        }
    }

    MyButton {
        id: clearButton
        width: 70
        height: 30
        buttonText: "clear"
        fontPointSize: 14
        anchors {
            verticalCenter: addNewButton.verticalCenter
            left: addNewButton.right
            leftMargin: 5
        }
        onClickedFoo: {
            if (m_listModel.count === 0) return;
            m_listModel.remove(0, m_listModel.count);
        }
    }
}
