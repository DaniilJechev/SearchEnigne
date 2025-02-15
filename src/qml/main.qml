import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs

import MyAlertModel
import AlertStates
import ConverterJSON
import ListModelType

ApplicationWindow {
    id: mainWindow
    visible: true
    maximumWidth: 1366
    minimumWidth: 1366
    maximumHeight: 768
    minimumHeight: 768

    property color windowColor: "#7d7d7d"
    property color standardTextColor: "white"
    property int countOfNoResults: 0

    Component.onCompleted: {
        criticAlertHandler.checkOnAlerts()
    }

    onClosing: { // autosave paths and queries
        ConverterJSON.writeToJson(queries.listModel.getAllData(), ListModelType.Queries);
        ConverterJSON.writeToJson(paths.listModel.getAllData(), ListModelType.Paths);
    }

    Item {
        id: criticAlertHandler
        anchors.centerIn: parent // for criticAlertDialog centring
        signal getCriticAlert(string criticAlert);

        onGetCriticAlert: criticAlert => {
            criticAlertDialog.alertText = criticAlert
            console.log(criticAlert)
            criticAlertDialog.open();
        }

        function checkOnAlerts(){
            var criticAlert = guardWrapper.checkData().toString()
            if (criticAlert.length !== 0) {
                console.log(criticAlert)
                getCriticAlert(criticAlert)
            }
        }

        Dialog {
            id: criticAlertDialog
            width: 355
            height: 250
            modal: true
            property string alertText: ""
            anchors.centerIn: parent
            standardButtons: Dialog.Ok

            Text {
                id: myText
                text: criticAlertDialog.alertText
                wrapMode: Text.WordWrap
                font.pointSize: 14
                anchors {
                    centerIn: parent
                    fill: parent
                }
            }

            onClosed: Qt.quit();
        }
    }


    Rectangle {
        id: backGroundMainWindow
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
            var searchResults = ConverterJSON.getAnswers();
            if (searchResults.length !== 0) {
                countOfNoResults = 0;
                answerList.append({"answer": searchResults});
            } else {
                countOfNoResults+=1;
                if (countOfNoResults >= 10) {
                    answerList.append({"answer": "You have found the paschal egg!!!"});
                } else {
                    answerList.append({"answer": "No results"});
                }
            }
            alertView.positionViewAtIndex(alertList.rowCount() - 1, alertView.End);
        }
    }

    MyButtonWithIcon {
        id: openSetings
        width: 70
        pathToIcon: "qrc:/icons/gearIcon"
        anchors {
            top: parent.top
            right: parent.right
            bottom: queries.top
        }

        onClickedFoo: {
            settingDialog.open();
        }
    }

    Dialog {
        id: settingDialog
        width: 355
        height: 120
        modal: true
        anchors.centerIn: parent

        background: Rectangle {
            anchors.fill: parent
            color: windowColor
        }

        footer: Rectangle {
            width: parent.width
            height: parent.height / 2.5
            color: windowColor

            RowLayout {
                anchors.centerIn: parent
                spacing: 30

                MyButton {
                    id: apply
                    width: 80
                    height: 35
                    buttonText: "Apply"
                    fontPointSize: 12
                    onClickedFoo: {
                        maxResponsesSpinbox.forceActiveFocus();
                        maxResponsesSpinbox.focus = false;
                        ConverterJSON.setResponsesLimit(maxResponsesSpinbox.value);
                        settingDialog.close();
                    }
                }

                MyButton {
                    id: close
                    width: 80
                    height: 35
                    buttonText: "Close"
                    fontPointSize: 12
                    onClickedFoo: {
                        settingDialog.close();
                    }
                }
            }
        }

        Column {
            anchors.fill: parent
            spacing: 40

            RowLayout {
                width: parent.width
                spacing: 30

                Label {
                    width: 50
                    height: 50
                    font.pointSize: 16
                    text: "Max responses: "
                }

                SpinBox {
                    id: maxResponsesSpinbox
                    width: 120
                    height: 80
                    editable: true
                    from: 1
                    value: ConverterJSON.getResponsesLimit()
                }
            }
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

            function getRandomColor() {
                return Qt.rgba(Math.random(), Math.random(), Math.random(), 1);
            }

            delegate: Label { // answers
                font.pointSize: 15
                text: model.answer
                color: (text === "You have found an Easter egg!!!" ) ?
                           answerView.getRandomColor() : "white"
                anchors {
                    left: parent !== null ? parent.left : undefined
                    top: parent !== null ? parent.top : undefined
                    leftMargin: parent !== null ?
                                    ((parent.width - width - answerVerticalSlider.width * 2)
                                     * answerView.leftAnchorMarginMultiplier) / 100 : 0
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
            property var alertColors: ({
                safely: "white",
                warning: "#e6e600",
                critical: "red"
            })
            function getColor (status) {
                if (status === AlertStates.Safely) return alertColors.safely;
                if (status === AlertStates.Warning) return alertColors.warning;
                if (status === AlertStates.Critical) return alertStatus.critical;
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
            spacing: 15
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

            delegate: Text {
                id: alert
                height: implicitHeight
                width: alertView.width * 0.9
                font.pointSize: 15
                text: model.message
                color: colorDefinitions.getColor(model.status);
                wrapMode: Text.WordWrap
            }
        }

        MyButton {
            id: clearButton
            width: 70
            height: 30
            buttonText: "clear"
            fontPointSize: 14
            anchors {
                top: backGroundAlert.bottom
                left: backGroundAlert.left
                topMargin: 5
            }
            onClickedFoo: {
                alertList.clear();
            }
        }
    }
}
