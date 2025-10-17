import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    property int recentRefreshKey: 0
    Rectangle {
        anchors.fill: parent
        color: "#0D1B2A"
        Column {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 50
            spacing: 30

            Row {
                spacing: 20
                anchors.horizontalCenter: parent.horizontalCenter

                Image {
                    source: "icon/DUCK.jpg"
                    width: 100
                    height: 100
                    fillMode: Image.PreserveAspectFit
                }

                Text {
                    text: "DUCK"
                    font.pixelSize: 64
                    font.bold: true
                    color: "white"
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Rectangle {
                width: 600
                height: 100
                color: "transparent"

                Text {
                    anchors.centerIn: parent
                    text: "Getting Started"
                    font.pixelSize: 64
                    font.bold: true
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            Rectangle {
                width: 1500
                height: 200
                color: "#00BCD4"
                radius: 16

                Button {
                    id: openProject
                    anchors.fill: parent
                    background: Rectangle {
                        color: openProject.pressed ? "#0097A7" : (openProject.hovered ? "#26C6DA" : "transparent")
                        radius: 16
                    }

                    Text {
                        id: openText
                        text: "New Project"
                        font.pixelSize: 64
                        font.bold: true
                        color: "white"
                        anchors.centerIn: parent
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Image {
                        source: "icon/plus.png"
                        width: 50
                        height: 50
                        fillMode: Image.PreserveAspectFit
                        anchors.right: openText.left
                        anchors.top: openText.top
                        anchors.bottom: openText.bottom
                        anchors.margins: 20
                    }

                    onClicked: stackView.push(Qt.resolvedUrl("SecondMenu.qml"))
                }
            }

            Rectangle {
                width: 1500
                height: 450
                color: "#1A2B3C"
                radius: 16
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 20

                Column {
                    anchors.fill: parent
                    spacing: 20
                    anchors.margins: 20

                    Text {
                        text: "Recent Projects"
                        font.pixelSize: 48
                        font.bold: true
                        color: "white"
                    }

                    Grid {
                        columns: 8
                        spacing: 14

                        Repeater {
                            model: 16
                            Button {
                                width: 170
                                height: 150
                                background: Rectangle {
                                    color: "#263238"
                                    radius: 8
                                }

                                contentItem: Image {
                                    anchors.fill: parent
                                    fillMode: Image.PreserveAspectFit
                                    source: (menu.getRecent(index) === ""? "" : "file:///" + menu.getRecent(index))
                                }

                                onClicked: {
                                    console.log("Clicked recent project slot", index)
                                    if(menu.getRecent(index) !== "") {
                                        menu.loadImage(menu.getRecent(index), false)
                                        stackView.push(Qt.resolvedUrl("SecondMenu.qml"), {imagePath: menu.getRecent(index) })
                                        recentRefreshKey = recentRefreshKey + 1
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
