import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: window
    width: parent.width / 2 - 20
    height: parent.height / 3

    property string title
    property string placeHolderText
    property alias listModel : m_listModel

    Rectangle {
        id: backGroundWindow
        anchors.fill: parent
        color: "#2e2d2d"
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
        spacing: 10
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
                id: queryIndex
                text: index + 1 + "."
                color: "white"
                font.pointSize: 15
            }

            TextInput {
                //Layout.preferredWidth: queryList.width - queryVerticalSlider.width - myIndex.width - query.spacing //this is don't work
                //Layout.fillWidth: false
                //PlaceholderText: "Enter your query"
                height: 15
                font.pointSize: 15
                text: model.message
                color: "white"
                onTextEdited: {
                    model.message = text
                }
            }

            MyButton { // delete query button
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

    MyButton { // add new query button
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
            m_listModel.append({message: placeHolderText});
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
