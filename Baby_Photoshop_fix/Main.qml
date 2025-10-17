import QtQuick
import QtQuick.Controls

Window {
    width: 1920
    height: 1080
    visible: true
    title: qsTr("Baby Photoshop")

    StackView {
        id : stackView
        anchors.fill: parent
        initialItem: FirstMenu {}
    }
}
