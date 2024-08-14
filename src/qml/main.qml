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
            topMargin: 50
        }

        Rectangle {
            id: backGroundQueries
            anchors.fill: parent
            color: "#2e2d2d"
            border {
                color: "black"
                width: 6
            }
        }

        Text {
            id: titleQueies
            text: "Queries"
            color: standardTextColor
            anchors {
                bottom: parent.top
                horizontalCenter: parent.horizontalCenter
            }
            font.pointSize: 25
        }

        ListModel {
            id: queryList
            ListElement {
                query: "banana"
            }

            ListElement {
                query: "apple"
            }

            ListElement {
                query: "banana"
            }

            ListElement {
                query: "apple"
            }
        }

        ListView {
            id: queryView
            model: queryList
            height: parent.height - backGroundQueries.border.width * 4
            width: parent.width - backGroundQueries.border.width * 4
            spacing: 10
            clip: true
            anchors {
                left: parent.left
                top: parent.top
                margins: 10
            }

            ScrollBar.vertical: ScrollBar {
                id: queryVerticalSlider
                anchors {
                    right: queryList.right
                    top: queryList.top
                }
                width: 15
            }

            delegate: RowLayout {
                id: query
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
                    height: 15
                    font.pointSize: 15
                    text: model.query
                    //PlaceholderText: "Enter your query"
                    color: "white"
                    onTextEdited: {
                        model.query = text
                    }
                }

                MyButton { // delete query button
                    width: 40
                    height: 25
                    buttonText: "-"
                    fontPointSize: 15
                    staticButtonColor: "black"

                    onClickedFoo: {
                        queryList.remove(index);
                    }
                }
            }
        }

        MyButton { // add new query button
            width: 100
            height: 30
            buttonText: "+"
            fontPointSize: 15

            anchors {
                left: parent.left
                top: parent.bottom
                topMargin: 5
            }

            onClickedFoo: {
                queryList.append({query: "Enter your query"});
                queryView.positionViewAtIndex(queryList.count - 1, queryView.End);
            }
        }
    }


    Item {
        id: files
        width: parent.width / 2.5
        height: parent.height / 2.5
        anchors {
            bottom: parent.bottom
            left: parent.left
            margins: 10
            bottomMargin: 50
        }

        Rectangle {
            id: backGroundFiles
            anchors.fill: parent
            color: "#2e2d2d"
            border {
                color: "black"
                width: 6
            }
        }

        Text {
            id: titleFiles
            text: "Files"
            color: standardTextColor
            anchors {
                bottom: parent.top
                horizontalCenter: parent.horizontalCenter
            }
            font.pointSize: 25
        }

        ListModel {
            id: fileList
            ListElement {
                file: "file001.txt"
            }

            ListElement {
                file: "file002.txt"
            }

            ListElement {
                file: "file003.txt"
            }

            ListElement {
                file: "file004.txt"
            }
        }

        ListView {
            id: fileView
            model: fileList
            height: parent.height - backGroundFiles.border.width * 4
            width: parent.width - backGroundFiles.border.width * 4
            spacing: 10
            clip: true
            anchors {
                left: parent.left
                top: parent.top
                margins: 10
            }

            ScrollBar.vertical: ScrollBar {
                id: fileVerticalSlider
                anchors {
                    right: fileList.right
                    top: fileList.top
                }
                width: 15
            }

            delegate: RowLayout {
                id: file
                spacing: 10


                Label {
                    id: fileIndex
                    text: index + 1 + "."
                    color: "white"
                    font.pointSize: 15
                }

                TextInput {
                    //Layout.preferredWidth: queryList.width - queryVerticalSlider.width - myIndex.width - query.spacing //this is don't work
                    //Layout.fillWidth: false
                    height: 15
                    font.pointSize: 15
                    text: model.file
                    //PlaceholderText: "Enter your query"
                    color: "white"
                    onTextEdited: {
                        model.file = text
                    }
                }

                MyButton { // delete query button
                    width: 40
                    height: 25
                    buttonText: "-"
                    fontPointSize: 15
                    staticButtonColor: "black"

                    onClickedFoo: {
                        fileList.remove(index);
                    }
                }
            }
        }

        MyButton { // add new file button
            width: 100
            height: 30
            buttonText: "+"
            fontPointSize: 15

            anchors {
                left: parent.left
                top: parent.bottom
                topMargin: 5
            }

            onClickedFoo: {
                fileList.append({file: "Enter new path to file"});
                fileView.positionViewAtIndex(fileList.count - 1, fileView.End);
            }
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

            ListElement {
                answer: "1234"
            }

            ListElement {
                answer: "1234"
            }

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
                    //Layout.preferredWidth: queryList.width - queryVerticalSlider.width - myIndex.width - query.spacing //this is don't work
                    //Layout.fillWidth: false
                    height: 15
                    font.pointSize: 15
                    text: model.answer
                    //PlaceholderText: "Enter your query"
                    color: "white"
                }
            }
        }
    }
}
