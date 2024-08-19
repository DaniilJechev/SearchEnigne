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
    property color standardTextColor: "white"

    Rectangle {
        anchors.fill: parent
        color: windowColor
    }

    MyButton {
        id: searchButton
        height: 100
        width: 170
        buttonText: "Search"
        fontPointSize: 20

        anchors {
            bottom: parent.bottom
            bottomMargin: 10
            horizontalCenter:parent.horizontalCenter
        }
        onClickedFoo: {
            myClass.search();
        }
    }

    MyWindow {
        id: queries
        anchors.left: parent.left
        anchors.margins:10
        anchors.top: parent.top
        anchors.topMargin: 50

        title: "Queries"
        myPlaceHolderText: "Enter new query"

        Component.onCompleted: {
            listModel.append({"message": "banana"})
            listModel.append({"message": "apple"})
            listModel.append({"message": "banana"})
            listModel.append({"message": "apple"})
        }
    }

    MyWindow {
        id: paths
        anchors.right: parent.right
        anchors.margins:10
        anchors.top: parent.top
        anchors.topMargin: 50

        title: "Paths"
        myPlaceHolderText: "Enter/new/path"

        Component.onCompleted: {
            listModel.append({"message": "file001.txt"});
            listModel.append({"message": "myDirectory/*"});
        }
    }

    Item {
        id: answers
        width: parent.width / 2.5
        height: parent.height / 2.5
        anchors {
            bottom: parent.bottom
            right: parent.right
            margins: 10
            bottomMargin: 50
        }

        Rectangle {
            id: backGroundAnswers
            anchors.fill: parent
            color: "#2e2d2d"
            border {
                color: "black"
                width: 6
            }
        }

        Text {
            id: titleAnswers
            text: "Answers"
            color: standardTextColor
            anchors {
                bottom: parent.top
                horizontalCenter: parent.horizontalCenter
            }
            font.pointSize: 25
        }

        ListModel {
            id: answerList
            ListElement {
                answer: "1234"
            }
        }

        ListView {
            id: answerView
            model: answerList
            height: parent.height - backGroundAnswers.border.width * 4
            width: parent.width - backGroundAnswers.border.width * 4
            spacing: 10
            clip: true
            anchors {
                left: parent.left
                top: parent.top
                margins: 10
            }

            ScrollBar.vertical: ScrollBar {
                id: answerVerticalSlider
                anchors {
                    right: answerList.right
                    top: answerList.top
                }
                width: 15
            }

            delegate: RowLayout {
                id: answer
                spacing: 10


                Label {
                    id: answerIndex
                    text: index + 1 + "."
                    color: "white"
                    font.pointSize: 15
                }

                Label {
                    height: 15
                    font.pointSize: 15
                    text: model.answer
                    color: "white"
                }
            }
        }
    }

    Item {
        id: alerts
        width: parent.width / 2.5
        height: parent.height / 2.5
        anchors {
            bottom: parent.bottom
            left: parent.left
            margins: 10
            bottomMargin: 50
        }

        Rectangle {
            id: backGroundAlert
            anchors.fill: parent
            color: "#2e2d2d"
            border {
                color: "black"
                width: 6
            }
        }

        Text {
            id: titleAlert
            text: "Alerts"
            color: standardTextColor
            anchors {
                bottom: parent.top
                horizontalCenter: parent.horizontalCenter
            }
            font.pointSize: 25
        }

        QtObject {
            id: colorDefinitions
            property var alertStatus: ({
                safely: "white",
                warning: "#e6e600",
                critical: "red"
            })
            function getColor (status) {
                if (status === "safely") return alertStatus.safely;
                if (status === "warning") return alertStatus.warning;
                if (status === "critical") return alertStatus.critical;
                return "white"; // default color
            }
        }


        ListModel {
            id: alertList

            ListElement {
                dangerStatus: "safely"
                alert: "file <filename> is not found"
            }

            ListElement {
                dangerStatus: "warning"
                alert: "directory <path/to/directory> is empty"
            }

            ListElement {
                dangerStatus: "critical"
                alert: "\"name\" field in \"config.json\" is not exist"
            }
        }

        ListView {
            id: alertView
            model: alertList
            height: parent.height - backGroundAlert.border.width * 4
            width: parent.width - backGroundAlert.border.width * 4
            spacing: 10
            clip: true
            anchors {
                left: parent.left
                top: parent.top
                margins: 10
            }

            ScrollBar.vertical: ScrollBar {
                id: alertVerticalSlider
                anchors {
                    right: answerList.right
                    top: answerList.top
                }
                width: 15
            }

            delegate: RowLayout {
                id: alert
                spacing: 10

                Label {
                    height: 15
                    font.pointSize: 15
                    text: model.alert
                    color: colorDefinitions.getColor(model.dangerStatus);
                }
            }
        }
    }
}
