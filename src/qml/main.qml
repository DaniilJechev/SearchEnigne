import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs

import MyAlertModel
import AlertStates
import ConverterJSON
import ListModelType

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
            ConverterJSON.writeToJson(queries.listModel.getAllData(), ListModelType.Queries);
            ConverterJSON.writeToJson(paths.listModel.getAllData(), ListModelType.Paths);
            searchHandler.search();
            answerList.clear();
            answerList.append({"answer": ConverterJSON.getAnswers()});
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

        customFilter: function(str){
            var result = "";
            for (var x = 0; x < str.length; ++x) {
                if ((str[x] >= 'a' && str[x] <= 'z') || str[x] === " ") {
                    result += str[x]
                }
            }
            if (result.length < str.length){
                console.log("Queries must contain only lower-case letters");
            }
            return result;
        }

        Component.onCompleted: {
            listModel.fillData(ListModelType.Queries);
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


        MyButton { // open file
            id: browseFile
            width: 115
            height: 30
            buttonText: "Browse file"
            fontPointSize: 14

            anchors {
                left: parent.addEmptyButton.right
                verticalCenter: parent.addEmptyButton.verticalCenter
                leftMargin: 5
                rightMargin: 5
            }

            onClickedFoo: {
                var path = dialogFinder.openFileDialog();
                if (path.length !== 0) {
                    parent.listModel.appendMessage(path)
                }
            }
        }

        MyButton { // open directory
            id: browseDirectory
            width: 165
            height: 30
            buttonText: "Browse directory"
            fontPointSize: 14

            anchors {
                left: browseFile.right
                verticalCenter: browseFile.verticalCenter
                leftMargin: 5
                rightMargin: 5
            }

            onClickedFoo: {
                var path = dialogFinder.openDirDialog();
                if (path.length !== 0) {
                    parent.listModel.appendMessage(path)
                }
            }
        }

        clearButton.anchors.left: browseDirectory.right

        Component.onCompleted: {
            listModel.fillData(ListModelType.Paths);
        }
    }

    onClosing: { // autosave paths and queries
        ConverterJSON.writeToJson(queries.listModel.getAllData(), ListModelType.Queries);
        ConverterJSON.writeToJson(paths.listModel.getAllData(), ListModelType.Paths);
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
        }

        ListView {
            id: answerView
            model: answerList
            height: parent.height - backGroundAnswers.border.width * 2
            width: parent.width - backGroundAnswers.border.width * 2
            clip: true
            anchors {
                left: parent.left
                top: parent.top
                bottom: parent.bottom
                margins: backGroundAnswers.border.width
            }
            property int leftAnchorMarginMultiplier: 0


            ScrollBar.vertical: ScrollBar {
                id: answerVerticalSlider
                anchors {
                    right: answerView.right
                    top: answerView.top
                }
                width: 15
            }

            delegate: Label { // answers
                font.pointSize: 15
                text: model.answer
                color: "white"
                anchors {
                    left: parent !== null ? parent.left : undefined
                    top: parent !== null ? parent.top : undefined
                    leftMargin: parent !== null ?
                                ((parent.width - width - answerVerticalSlider.width * 2)
                                 * answerView.leftAnchorMarginMultiplier) / 100
                                  : 0
                }
                onContentSizeChanged: {
                    if (width < answerView.width) {
                        answerHorizontalSlider.policy = ScrollBar.AlwaysOff
                        answerHorizontalSlider.setPosition(0)
                        anchors.leftMargin = 0
                    }
                    answerHorizontalSlider.policy = ScrollBar.AlwaysOn
                }
            }
        }

        ScrollBar {
            id: answerHorizontalSlider
            height: 15
            stepSize: 0.1
            orientation: Qt.Horizontal
            policy: ScrollBar.AlwaysOff

            anchors {
                right: backGroundAnswers.right
                left: backGroundAnswers.left
                top: backGroundAnswers.bottom
                margins: 2
            }

            onPositionChanged: {
                answerView.leftAnchorMarginMultiplier = position * 100
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
                if (status === AlertStates.safely) return alertStatus.safely;
                if (status === AlertStates.warning) return alertStatus.warning;
                if (status === AlertStates.critical) return alertStatus.critical;
                return "white"; // default color
            }
        }


        AlertModel {
            id: alertList
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
                    text: model.message
                    color: colorDefinitions.getColor(model.status);
                }
            }
        }
        Component.onCompleted: {
            alertList.append("file is not found", AlertStates.Warning);
        }
    }
}
