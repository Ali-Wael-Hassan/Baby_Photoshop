import QtQuick
import QtQuick.Controls
import Qt.labs.platform
import QtQuick.Layouts

Page {
    id: filterMenu

    Keys.onPressed: {
        const ctrlOrCmd = event.modifiers & Qt.ControlModifier || event.modifiers & Qt.MetaModifier
        const shift = event.modifiers & Qt.ShiftModifier
        if ((event.key === Qt.Key_Z) && ctrlOrCmd && !shift) {
            if (undo.enabled) {
                menu.undoF()
                event.accepted = true
            }
        }

        if ((event.key === Qt.Key_Z) && ctrlOrCmd && shift) {
            if (redo.enabled) {
                menu.redoF()
                event.accepted = true
            }
        }

        if ((event.key === Qt.Key_Y) && ctrlOrCmd && !shift) {
            if (redo.enabled) {
                menu.redoF()
                event.accepted = true
            }
        }

        if (event.key === Qt.Key_S && ctrlOrCmd && !shift) {
            menu.saveImage(menu.getName())
            event.accepted = true
        }

        if (event.key === Qt.Key_F12) {
            saveAsDialog.open()
            event.accepted = true
        }
    }

    property string imagePath: ""

    Rectangle {
        id: mainRect
        color: "#1E1E1E"
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#1F1F1F" }
            GradientStop { position: 1.0; color: "#1B1B1B" }
        }
        anchors.fill: parent
        z: 0

        function closeAll() {
            sliders.visible = false
            detectSlider.visible = false
            contrastSlider.visible = false
            blurSlider.visible = false
            sunsSlider.visible = false
            mergeParam.visible = false
            flipOption.visible = false
            rotateOption.visible = false
            cropOption.visible = false
            colorPicker.visible = false
        }
        function showMessage(success, text) {
            notify.color = success? "#28A745" : "#A72845"
            notifyText.text = text
            notify.visible = true
            flow.start()
        }

        Connections {
            target: menu

            function onSaveSuccess(msg) {
                mainRect.showMessage(true, msg)
            }

            function onErrorOccurred(msg) {
                mainRect.showMessage(false, msg)
            }

            function onImageChanged() {
                const path = menu.getAppDirPath() + "/temp.png"
                menu.saveImage(path, false)
                imageDisplay.source = ""
                imageDisplay.source = "file:///" + path + "?v=" + Date.now()
                name.text = menu.cleanName()
            }

            function onUndoAvailable(status) {
                undo.enabled = status
            }

            function onRedoAvailable(status) {
                redo.enabled = status
            }
        }

        Timer {
            id: flow
            interval: 3000
            repeat: false
            running: true

            onTriggered: notify.visible = false
        }

        // Notification
        Rectangle {
            id: notify
            color: "#28A745"
            width: parent.width * 0.6
            height: parent.height * 0.05
            radius: height / 2
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            visible: false
            z: 1000

            Text {
                id: notifyText
                anchors.centerIn: parent
                text: "default"
                color: "white"
                font.pixelSize: 18
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }


        // Exit messages
        Rectangle {
            id: exit
            color: "#2D2D2D"
            radius: 10
            width: parent.width * 0.15
            height: parent.height * 0.12
            anchors.centerIn: parent
            visible: false
            border.color: "#666"
            border.width: 1
            z: 10000

            Column {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 15
                anchors.centerIn: parent

                Text {
                    text: "Are you sure you want to exit?"
                    color: "white"
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignHCenter
                }

                Row {
                    spacing: 20
                    anchors.horizontalCenter: parent.horizontalCenter

                    Button {
                        id: ok
                        text: "OK"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: ok.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (ok.pressed ? "#007ACC" : (ok.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: {
                            stackView.pop()
                            exit.visible = false
                        }
                    }

                    Button {
                        id: cancel
                        text: "Cancel"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: cancel.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (cancel.pressed ? "#007ACC" : (cancel.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: exit.visible = false
                    }
                }
            }
        }


        //Merge bar
        Rectangle {
            id: mergeParam
            color: "#555555"
            height: 150
            anchors.bottom: parent.bottom
            anchors.left: filter.right
            anchors.right: parent.right
            visible: false
            border.color: "#555555"
            border.width: 1
            z: 50

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#3A3A3A" }
                GradientStop { position: 1.0; color: "#252525" }
            }

            Row {
                id: mergeRow
                spacing: 20
                anchors.centerIn: parent
                anchors.verticalCenter: parent.verticalCenter

                Button {
                    id: resizeOption
                    text: "Resize"
                    width: 120
                    height: 40
                    contentItem: Text {
                        text: resizeOption.text
                        color: "#FFFFFF"
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle {
                        radius: 5
                        color: (resizeOption.pressed ? "#007ACC" : (resizeOption.hovered ? "#505050" : "#3C3C3C"))
                        border.color: "#555555"
                    }
                    onClicked: {
                        menu.mergeImage(imageDisplay2.source, 1, 50, 0, 0, 0, 0, 1, 1)
                        imageDisplay2.source = ""
                        mergeParam.visible = false
                    }
                }

                Button {
                    id: cropOption
                    text: "Common Area"
                    width: 140
                    height: 40
                    contentItem: Text {
                        text: cropOption.text
                        color: "#FFFFFF"
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle {
                        radius: 5
                        color: (cropOption.pressed ? "#007ACC" : (cropOption.hovered ? "#505050" : "#3C3C3C"))
                        border.color: "#555555"
                    }
                    onClicked: {
                        let overlapLeft   = Math.max(imageDisplay.x, imageDisplay2.x)
                        let overlapTop    = Math.max(imageDisplay.y, imageDisplay2.y)
                        let overlapRight  = Math.min(imageDisplay.x + imageDisplay.width, imageDisplay2.x + imageDisplay2.width)
                        let overlapBottom = Math.min(imageDisplay.y + imageDisplay.height, imageDisplay2.y + imageDisplay2.height)

                        let scale1x = imageDisplay.implicitWidth  / imageDisplay.width
                        let scale1y = imageDisplay.implicitHeight / imageDisplay.height
                        let scale2x = imageDisplay2.implicitWidth  / imageDisplay2.width
                        let scale2y = imageDisplay2.implicitHeight / imageDisplay2.height

                        let x1 = (overlapLeft - imageDisplay.x) * scale1x
                        let y1 = (overlapTop  - imageDisplay.y) * scale1y
                        let x2 = (overlapLeft - imageDisplay2.x) * scale2x
                        let y2 = (overlapTop  - imageDisplay2.y) * scale2y
                        let w  = (overlapRight - overlapLeft) * scale1x
                        let h  = (overlapBottom - overlapTop) * scale1y

                        x1 = Math.max(0, Math.min(x1, imageDisplay.implicitWidth  - 1))
                        y1 = Math.max(0, Math.min(y1, imageDisplay.implicitHeight - 1))
                        x2 = Math.max(0, Math.min(x2, imageDisplay2.implicitWidth  - 1))
                        y2 = Math.max(0, Math.min(y2, imageDisplay2.implicitHeight - 1))

                        w = Math.max(1, Math.min(w, Math.min(
                            imageDisplay.implicitWidth  - x1,
                            imageDisplay2.implicitWidth - x2
                        )))
                        h = Math.max(1, Math.min(h, Math.min(
                            imageDisplay.implicitHeight  - y1,
                            imageDisplay2.implicitHeight - y2
                        )))

                        menu.mergeImage( imageDisplay2.source, 0, 50, x1, y1, x2, y2, w, h)

                        imageDisplay2.source = ""
                        mergeParam.visible = false
                    }
                }

                Button {
                    id: cancelMerge
                    text: "Cancel"
                    width: 100
                    height: 40
                    contentItem: Text {
                        text: cancelMerge.text
                        color: "#FFFFFF"
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle {
                        radius: 5
                        color: (cancelMerge.pressed ? "#007ACC" : (cancelMerge.hovered ? "#505050" : "#3C3C3C"))
                        border.color: "#555555"
                    }
                    onClicked: {
                        imageDisplay2.source = ""
                        mergeParam.visible = false
                    }
                }
            }
        }


        // Flip bar
        Rectangle {
            id: flipOption
            color: "#555555"
            height: 150
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.left: filter.right
            visible: false
            border.color: "#555555"
            border.width: 1
            z: 50

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#3A3A3A" }
                GradientStop { position: 1.0; color: "#252525" }
            }
            Row {
                id: flipRow
                spacing: 20
                anchors.centerIn: parent
                anchors.verticalCenter: parent.verticalCenter

                Button {
                    id: vertical
                    text: "Vertical"
                    width: 120
                    height: 40
                    contentItem: Text {
                        text: vertical.text
                        color: "#FFFFFF"
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle {
                        radius: 5
                        color: (vertical.pressed ? "#007ACC" : (vertical.hovered ? "#505050" : "#3C3C3C"))
                        border.color: "#555555"
                    }
                    onClicked: {
                        menu.flipImage(false)
                        flipOption.visible = false
                    }
                }

                Button {
                    id: horizontal
                    text: "Horizontal"
                    width: 120
                    height: 40
                    contentItem: Text {
                        text: horizontal.text
                        color: "#FFFFFF"
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle {
                        radius: 5
                        color: (horizontal.pressed ? "#007ACC" : (horizontal.hovered ? "#505050" : "#3C3C3C"))
                        border.color: "#555555"
                    }
                    onClicked: {
                        menu.flipImage(true)
                        flipOption.visible = false
                    }
                }

                Button {
                    id: cancelFlip
                    text: "Cancel"
                    width: 100
                    height: 40
                    contentItem: Text {
                        text: cancelFlip.text
                        color: "#FFFFFF"
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle {
                        radius: 5
                        color: (cancelFlip.pressed ? "#007ACC" : (cancelFlip.hovered ? "#505050" : "#3C3C3C"))
                        border.color: "#555555"
                    }
                    onClicked: {
                        flipOption.visible = false
                    }
                }
            }
        }

        // Rotate bar
        Rectangle {
            id: rotateOption
            color: "#555555"
            height: 150
            anchors.bottom: parent.bottom
            anchors.left: filter.right
            anchors.right: parent.right
            visible: false
            border.color: "#555555"
            border.width: 1
            z: 50

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#3A3A3A" }
                GradientStop { position: 1.0; color: "#252525" }
            }

            Row {
                id: rotateRow
                spacing: 20
                anchors.centerIn: parent
                anchors.verticalCenter: parent.verticalCenter

                Button {
                    id: degree1
                    text: "90 Degree"
                    width: 120
                    height: 40
                    contentItem: Text {
                        text: degree1.text
                        color: "#FFFFFF"
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle {
                        radius: 5
                        color: (degree1.pressed ? "#007ACC" : (degree1.hovered ? "#505050" : "#3C3C3C"))
                        border.color: "#555555"
                    }
                    onClicked: {
                        menu.rotateImage(90)
                        rotateOption.visible = false
                    }
                }

                Button {
                    id: degree2
                    text: "180 Degree"
                    width: 120
                    height: 40
                    contentItem: Text {
                        text: degree2.text
                        color: "#FFFFFF"
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle {
                        radius: 5
                        color: (degree2.pressed ? "#007ACC" : (degree2.hovered ? "#505050" : "#3C3C3C"))
                        border.color: "#555555"
                    }
                    onClicked: {
                        menu.rotateImage(180)
                        rotateOption.visible = false
                    }
                }

                Button {
                    id: degree3
                    text: "270 Degree"
                    width: 120
                    height: 40
                    contentItem: Text {
                        text: degree3.text
                        color: "#FFFFFF"
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle {
                        radius: 5
                        color: (degree3.pressed ? "#007ACC" : (degree3.hovered ? "#505050" : "#3C3C3C"))
                        border.color: "#555555"
                    }
                    onClicked: {
                        menu.rotateImage(270)
                        rotateOption.visible = false
                    }
                }

                Button {
                    id: cancelRotate
                    text: "Cancel"
                    width: 100
                    height: 40
                    contentItem: Text {
                        text: cancelRotate.text
                        color: "#FFFFFF"
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle {
                        radius: 5
                        color: (cancelRotate.pressed ? "#007ACC" : (cancelRotate.hovered ? "#505050" : "#3C3C3C"))
                        border.color: "#555555"
                    }
                    onClicked: {
                        rotateOption.visible = false
                    }
                }
            }
        }

        // Crop bar
        Rectangle {
            id: crop
            color: "#555555"
            height: 150
            anchors.bottom: parent.bottom
            anchors.left: filter.right
            anchors.right: parent.right
            visible: false
            border.color: "#555555"
            border.width: 1
            z: 50

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#3A3A3A" }
                GradientStop { position: 1.0; color: "#252525" }
            }

            Button {
                id: cancelCrop
                text: "Cancel"
                width: 100
                height: 40
                anchors.centerIn: parent
                contentItem: Text {
                    text: cancelFlip.text
                    color: "#FFFFFF"
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle {
                    radius: 5
                    color: (cancelFlip.pressed ? "#007ACC" : (cancelFlip.hovered ? "#505050" : "#3C3C3C"))
                    border.color: "#555555"
                }
                onClicked: {
                    selectionRect.width = 0
                    selectionRect.height = 0
                    imageArea.cropMode = false
                    selectionRect.visible = false
                    crop.visible = false
                }
            }
        }

        // Frame bar
        Rectangle {
            id: frameOption
            color: "#555555"
            height: 150
            anchors.bottom: parent.bottom
            anchors.left: filter.right
            anchors.right: parent.right
            visible: false
            border.color: "#555555"
            border.width: 1
            z: 50

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#3A3A3A" }
                GradientStop { position: 1.0; color: "#252525" }
            }

            property string path: ""

            Column {
                anchors.centerIn: parent
                Row {
                    id: frameRow
                    spacing: 20
                    Layout.alignment: Qt.AlignCenter

                    Button {
                        id: frame1
                        text: "Simple Frame"
                        icon.source: "icon/simple.png"
                        icon.width: 20
                        icon.height: 20
                        onClicked: {
                            frameOption.path = "/icon/simple.png"
                        }
                    }

                    Button {
                        id: frame2
                        text: "Fancy Frame"
                        icon.source: "icon/fancy.png"
                        icon.width: 32
                        icon.height: 32
                        onClicked: {
                            frameOption.path = "/icon/fancy.png"
                        }
                    }
                }

                Row {
                    spacing: 20
                    anchors.horizontalCenter: parent.horizontalCenter

                    Button {
                        id: applyFrame
                        text: "Apply"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: applyFrame.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (applyFrame.pressed ? "#007ACC" : (applyFrame.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: {
                            console.log(menu.getAppDirPath() + frameOption.path)
                            menu.addFrame(frameOption.path, colorPicker.redVal * 255, colorPicker.greenVal * 255, colorPicker.blueVal * 255)
                            frameOption.visible = false
                            colorPicker.visible = false
                        }
                    }

                    Button {
                        id: cancelFrame
                        text: "Cancel"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: cancelFrame.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (cancelFrame.pressed ? "#007ACC" : (cancelFrame.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: {
                            frameOption.visible = false
                            colorPicker.visible = false
                        }
                    }
                }
            }
        }

        // Resize Bar
        Rectangle {
            id: resizeBar
            color: "#555555"
            height: 150
            anchors.bottom: parent.bottom
            anchors.left: filter.right
            anchors.right: parent.right
            visible: false
            border.color: "#555555"
            border.width: 1
            z: 50

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#3A3A3A" }
                GradientStop { position: 1.0; color: "#252525" }
            }

            property int newWidth: 0
            property int newHeight: 0

            Column {
                anchors.centerIn: parent
                spacing: 20

                Row {
                    spacing: 15
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        text: "Width:"
                        color: "white"
                        font.pixelSize: 16
                        verticalAlignment: Text.AlignVCenter
                    }

                    TextField {
                        id: widthField
                        width: 100
                        placeholderText: "e.g. 800"
                        inputMethodHints: Qt.ImhDigitsOnly
                        validator: IntValidator { bottom: 1; top: 10000 }
                        onTextChanged: {
                            resizeBar.newWidth = parseInt(text) || 0
                            widthError.visible = (resizeBar.newWidth <= 0)
                        }
                    }

                    Text {
                        id: widthError
                        text: "Invalid"
                        color: "red"
                        font.pixelSize: 12
                        visible: false
                        verticalAlignment: Text.AlignVCenter
                    }

                    Text {
                        text: "Height:"
                        color: "white"
                        font.pixelSize: 16
                        verticalAlignment: Text.AlignVCenter
                    }

                    TextField {
                        id: heightField
                        width: 100
                        placeholderText: "e.g. 600"
                        inputMethodHints: Qt.ImhDigitsOnly
                        validator: IntValidator { bottom: 1; top: 10000 }
                        onTextChanged: {
                            resizeBar.newHeight = parseInt(text) || 0
                            heightError.visible = (resizeBar.newHeight <= 0)
                        }
                    }

                    Text {
                        id: heightError
                        text: "Invalid"
                        color: "red"
                        font.pixelSize: 12
                        visible: false
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                Row {
                    spacing: 20
                    anchors.horizontalCenter: parent.horizontalCenter

                    Button {
                        id: applyResize
                        text: "Apply"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: applyResize.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (applyResize.pressed ? "#007ACC" : (applyResize.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: {
                            if (resizeBar.newWidth > 0 && resizeBar.newHeight > 0) {
                                menu.resizeImage(resizeBar.newWidth, resizeBar.newHeight)
                                resizeBar.visible = false
                            } else {
                                console.log("Invalid resize values.")
                                widthError.visible = (resizeBar.newWidth <= 0)
                                heightError.visible = (resizeBar.newHeight <= 0)
                            }
                        }
                    }

                    Button {
                        id: cancelResize
                        text: "Cancel"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: cancelResize.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (cancelResize.pressed ? "#007ACC" : (cancelResize.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: resizeBar.visible = false
                    }
                }
            }
        }

        Rectangle {
            id: sizeOfImage
            color: "#555555"
            height: 20
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            visible: true
            border.color: "#555555"
            border.width: 1
            z: 70

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#3A3A3A" }
                GradientStop { position: 1.0; color: "#252525" }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                spacing: 30

                Text {
                    id: name
                    text: menu.cleanName()
                    color: "white"
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                Text {
                    text: imageDisplay.implicitWidth + "x" + imageDisplay.implicitHeight + "px"
                    color: "white"
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }


        //color picker and preview
        Rectangle {
            id: colorPicker
                width: 0.2 * parent.width
                anchors.right: parent.right
                anchors.top: fileSave.bottom
                anchors.bottom: parent.bottom
                visible: false
                z: 60

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#3A3A3A" }
                    GradientStop { position: 1.0; color: "#252525" }
                }
                border.color: "#666666"
                border.width: 1

                property real redVal: 0.5
                property real greenVal: 0.5
                property real blueVal: 0.5

            Column {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 15

                Rectangle {
                    width: parent.width
                    height: 50
                    color: "#282828"
                    border.width: 1
                    border.color: "#4A4A4A"
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter:parent.verticalCenter
                        text: "Pick Color"
                        font.bold: true
                        font.pixelSize: 24
                        color: "white"
                    }
                }


                Rectangle {
                    id: preview
                    width: parent.width
                    height: 70
                    radius: 4
                    border.width: 2
                    border.color: "#666"
                    color: Qt.rgba(colorPicker.redVal, colorPicker.greenVal, colorPicker.blueVal, 1)
                }

                RowLayout {
                    spacing: 15
                    anchors.horizontalCenter: parent.horizontalCenter
                    Rectangle {
                        width: 25
                        height: 25
                        color: "#333333"
                        radius: 3

                        Text {
                            text: "R"
                            color: "#FF5252"
                            font.pixelSize: 16
                            anchors.centerIn: parent
                        }
                    }

                    Rectangle {
                        width: 200
                        height: 10
                        radius: 5
                        color: "#1E1E1E"
                        Layout.alignment : Qt.AlignHCenter

                        Rectangle {
                            width: (parent.width * (redSlider.value - redSlider.from) / (redSlider.to - redSlider.from))
                            height: parent.height
                            radius: parent.radius
                            color: "#FF5252"
                        }

                        Rectangle {
                            width: 20
                            height: 20
                            radius: 10
                            color: "#FFFFFF"
                            border.color: "#FF5252"
                            border.width: 2
                            y: parent.height / 2 - height / 2
                            x: (parent.width - width) * (redSlider.value - redSlider.from) / (redSlider.to - redSlider.from)
                        }

                        Slider {
                            id: redSlider
                            anchors.fill: parent
                            from: 0
                            to: 100
                            value: 0
                            opacity: 0.0001
                            onValueChanged: {
                                colorPicker.redVal = value/100
                                preview.color = Qt.rgba(colorPicker.redVal, colorPicker.greenVal, colorPicker.blueVal, 1)
                                colorBox.updateGradient()
                            }
                        }
                    }
                }

                RowLayout {
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 15
                    Rectangle {
                        width: 25
                        height: 25
                        color: "#333333"
                        radius: 3

                        Text {
                            text: "G"
                            color: "#00FF00"
                            font.pixelSize: 16
                            anchors.centerIn: parent
                        }
                    }

                    Rectangle {
                        width: 200
                        height: 10
                        radius: 5
                        color: "#1E1E1E"
                        Layout.alignment : Qt.AlignHCenter

                        Rectangle {
                            width: (parent.width * (greenSlider.value - greenSlider.from) / (greenSlider.to - greenSlider.from))
                            height: parent.height
                            radius: parent.radius
                            color: "#00FF00"
                        }

                        Rectangle {
                            width: 20
                            height: 20
                            radius: 10
                            color: "#FFFFFF"
                            border.color: "#00FF00"
                            border.width: 2
                            y: parent.height / 2 - height / 2
                            x: (parent.width - width) * (greenSlider.value - greenSlider.from) / (greenSlider.to - greenSlider.from)
                        }

                        Slider {
                            id: greenSlider
                            anchors.fill: parent
                            from: 0
                            to: 100
                            value: 100
                            opacity: 0.0001
                            onValueChanged: {
                                colorPicker.greenVal = value/100
                                preview.color = Qt.rgba(colorPicker.redVal, colorPicker.greenVal, colorPicker.blueVal, 1)
                                circle.y = (1 - colorPicker.greenVal) * colorBox.height - circle.height/2
                                colorBox.updateGradient()
                            }
                        }
                    }
                }

                RowLayout {
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 15
                    Rectangle {
                        width: 25
                        height: 25
                        color: "#333333"
                        radius: 3

                        Text {
                            text: "B"
                            color: "#007FFF"
                            font.pixelSize: 16
                            anchors.centerIn: parent
                        }
                    }

                    Rectangle {
                        width: 200
                        height: 10
                        radius: 5
                        color: "#1E1E1E"
                        Layout.alignment : Qt.AlignHCenter

                        Rectangle {
                            width: (parent.width * (blueSlider.value - blueSlider.from) / (blueSlider.to - blueSlider.from))
                            height: parent.height
                            radius: parent.radius
                            color: "#007FFF"
                        }

                        Rectangle {
                            width: 20
                            height: 20
                            radius: 10
                            color: "#FFFFFF"
                            border.color: "#007FFF"
                            border.width: 2
                            y: parent.height / 2 - height / 2
                            x: (parent.width - width) * (blueSlider.value - blueSlider.from) / (blueSlider.to - blueSlider.from)
                        }

                        Slider {
                            id: blueSlider
                            anchors.fill: parent
                            from: 0
                            to: 100
                            value: 0
                            opacity: 0.0001
                            onValueChanged: {
                                colorPicker.blueVal = value/100
                                preview.color = Qt.rgba(colorPicker.redVal, colorPicker.greenVal, colorPicker.blueVal, 1)
                                circle.x = colorPicker.blueVal * colorBox.width - circle.width / 2
                                colorBox.updateGradient()
                            }
                        }
                    }
                }

                Rectangle {
                    id: colorBox // G/B
                    width: 250
                    height: 250
                    radius: 4
                    border.width: 2
                    border.color: "#888888"
                    anchors.horizontalCenter: parent.horizontalCenter
                    Rectangle {
                        anchors.fill: parent
                        radius: parent.radius
                        color: Qt.rgba(1, 0, 0, colorPicker.redVal * 0.3)
                    }
                    gradient: Gradient {
                        GradientStop { position: 0; color: Qt.rgba(redSlider.value, 1, 0, 1); }
                        GradientStop { position: 1; color: Qt.rgba(redSlider.value, 0, 1, 1); }
                    }

                    function updateGradient() {
                        gradient.stops[0].color = Qt.rgba(redSlider.value/100, 1, 0, 1);
                        gradient.stops[1].color = Qt.rgba(redSlider.value/100, 0, 1, 1);
                    }

                    Rectangle {
                        id: circle
                        width: 24
                        height: 24
                        radius: 12
                        color: "transparent"
                        border.color: "#FFFFFF"
                        border.width: 3
                        x: colorBox.width * colorPicker.blueValue - width/2
                        y: colorBox.height * (1 - colorPicker.greenValue) - height/2
                        Rectangle {
                            width: 6
                            height: 6
                            radius: 3
                            color: "#000000"
                            anchors.centerIn: parent
                        }

                        MouseArea {
                            anchors.fill: parent
                            drag.target: parent
                            drag.minimumX: -circle.width/2
                            drag.maximumX: colorBox.width - circle.width/2
                            drag.minimumY: -circle.height/2
                            drag.maximumY: colorBox.height - circle.height/2
                            cursorShape: Qt.CrossCursor

                            onPositionChanged: {
                                colorPicker.blueVal = (circle.x + circle.width/2) / colorBox.width
                                colorPicker.greenVal = 1 - (circle.y + circle.height/2) / colorBox.height
                                greenSlider.value = 100 * colorPicker.greenVal
                                blueSlider.value = 100 * colorPicker.blueVal
                                preview.color = Qt.rgba(colorPicker.redVal, colorPicker.greenVal, colorPicker.blueVal, 1)
                            }
                        }
                    }
                }
            }
        }

        // Image
        Item {
            id: imageArea
            anchors.top: fileSave.bottom
            anchors.bottom: resizeBar.top
            anchors.left: filter.right
            anchors.right: colorPicker.right
            clip: true
            property bool cropMode: false

            Grid {
                id: checkerboard
                width: parent.width
                height: parent.height
                anchors.centerIn: parent
                columns: 20
                rowSpacing: 0
                columnSpacing: 0

                Repeater {
                    model: 400
                    Rectangle {
                        width: checkerboard.width / 20
                        height: checkerboard.height / 20
                        color: "#2D2D2D"
                    }
                }
            }

            Image {
                id: imageDisplay
                source: ""
                fillMode: Image.PreserveAspectFit
                width: Math.min(imageArea.width, imageDisplay.implicitWidth)
                height: Math.min(imageArea.height, imageDisplay.implicitHeight)
                x: (imageArea.width - width) / 2
                y: (imageArea.height - height) / 2
                smooth: true
                z: 5

                property real startX
                property real startY
                property real startMouseX
                property real startMouseY

                MouseArea {
                    id: dragArea
                    anchors.fill: parent
                    drag.target: parent
                    drag.axis: Drag.XAndYAxis
                    cursorShape: Qt.OpenHandCursor
                    enabled: !imageArea.cropMode

                    drag.minimumX: Math.min(0, imageArea.width - imageDisplay.width)
                    drag.maximumX: Math.max(0, imageArea.width - imageDisplay.width)
                    drag.minimumY: Math.min(0, imageArea.height - imageDisplay.height)
                    drag.maximumY: Math.max(0, imageArea.height - imageDisplay.height)

                    onPressed: {
                        cursorShape = Qt.ClosedHandCursor
                        parent.z = 30
                    }

                    onReleased: {
                        cursorShape = Qt.OpenHandCursor
                        parent.z = 5
                    }
                }
            }

            Image {
                id: imageDisplay2
                source: (imagePath === ""? "" : "file:///" + imagePath)
                fillMode: Image.PreserveAspectFit
                width: Math.min(imageArea.width, implicitWidth)
                height: Math.min(imageArea.height, implicitHeight)
                x: (imageArea.width - width) / 2
                y: (imageArea.height - height) / 2
                smooth: true
                z: 10

                property real startX
                property real startY
                property real startMouseX
                property real startMouseY

                MouseArea {
                    id: dragArea2
                    anchors.fill: parent
                    drag.target: parent
                    drag.axis: Drag.XAndYAxis
                    cursorShape: Qt.OpenHandCursor
                    enabled: !imageArea.cropMode

                    drag.minimumX: Math.min(0, imageArea.width - imageDisplay2.width)
                    drag.maximumX: Math.max(0, imageArea.width - imageDisplay2.width)
                    drag.minimumY: Math.min(0, imageArea.height - imageDisplay2.height)
                    drag.maximumY: Math.max(0, imageArea.height - imageDisplay2.height)

                    onPressed: {
                        cursorShape = Qt.ClosedHandCursor
                        parent.z = 30
                    }

                    onReleased: {
                        cursorShape = Qt.OpenHandCursor
                        parent.z = 10
                    }
                }
            }

            Rectangle {
                id: dimOverlay
                anchors.fill: imageArea
                color: "#000000CC"
                visible: imageArea.cropMode
                z: 100
            }

            Rectangle {
                id: selectionRect
                color: "transparent"
                border.color: "#00FFFF"
                border.width: 2
                visible: imageArea.cropMode
                z: 200
                width: 0
                height: 0
            }

            MouseArea {
                id: selectionRectMouseArea
                anchors.fill: parent
                cursorShape: Qt.CrossCursor
                enabled: imageArea.cropMode
                z: 300

                property real startX
                property real startY

                onPressed: {
                    startX = mouse.x
                    startY = mouse.y
                    selectionRect.x = startX
                    selectionRect.y = startY
                    selectionRect.width = 0
                    selectionRect.height = 0

                    selectionRect.visible = true
                    selectionRect.z = 999
                }

                onPositionChanged: {
                    let clampedX = Math.max(imageDisplay.x, Math.min(mouse.x, imageDisplay.x + imageDisplay.width))
                    let clampedY = Math.max(imageDisplay.y, Math.min(mouse.y, imageDisplay.y + imageDisplay.height))

                    selectionRect.x = Math.min(startX, clampedX)
                    selectionRect.y = Math.min(startY, clampedY)
                    selectionRect.width = Math.abs(clampedX - startX)
                    selectionRect.height = Math.abs(clampedY - startY)
                }

                onReleased: {
                    if (selectionRect.width <= 0 || selectionRect.height <= 0) {
                        imageArea.cropMode = false
                        return
                    }

                    let scaleX = imageDisplay.implicitWidth / imageDisplay.width
                    let scaleY = imageDisplay.implicitHeight / imageDisplay.height

                    let x = (selectionRect.x - imageDisplay.x) * scaleX
                    let y = (selectionRect.y - imageDisplay.y) * scaleY
                    let w = selectionRect.width * scaleX
                    let h = selectionRect.height * scaleY
                    selectionRect.width = 0
                    selectionRect.height = 0
                    imageArea.cropMode = false
                    crop.visible = false
                    selectionRect.visible = false
                    menu.cropImage(x,y, w, h)

                    console.log("Crop done")
                }
            }
        }



        // Save, Load, Home, Undo, Redo
        Rectangle {
            id: fileSave
            color: "#2B2B2B"
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#2C2C2C" }
                GradientStop { position: 1.0; color: "#1F1F1F" }
            }
            width: 1920
            height: 43
            anchors.top: parent.top
            anchors.bottom: filter.top
            z: 10
            border.color: "#1A1A1A"
            border.width: 1

            Row {
                anchors.verticalCenter: parent.verticalCenter
                spacing: 20
                anchors.margins: 10
                height: 30

                Button {
                    id: save
                    text: "Save"
                    width: 75
                    height: parent.height

                    contentItem: Text {
                        text: save.text
                        color: "#FFFFFF"
                        font.bold: true
                        font.pixelSize: 16
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    background: Rectangle {
                        radius: 5
                        color: (save.pressed ? "#007ACC" : (save.hovered ? "#505050" : "transparent"))
                        border.color: "transparent"
                        border.width: 1
                    }

                    onClicked: {
                        menu.saveImage(menu.getName())
                    }
                }

                Button {
                    id: saveAs
                    text: "Save As"
                    width: 75
                    height: parent.height

                    contentItem: Text {
                        text: saveAs.text
                        color: "#FFFFFF"
                        font.bold: true
                        font.pixelSize: 16
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    background: Rectangle {
                        radius: 5
                        color: (saveAs.pressed ? "#007ACC" : (saveAs.hovered ? "#505050" : "transparent"))
                        border.color: "transparent"
                        border.width: 1
                    }

                    onClicked: saveAsDialog.open()
                }

                Button {
                    id: load
                    text: "Load"
                    width: 75
                    height: parent.height

                    contentItem: Text {
                        text: load.text
                        color: "#FFFFFF"
                        font.bold: true
                        font.pixelSize: 16
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    background: Rectangle {
                        radius: 5
                        color: (load.pressed ? "#007ACC" : (load.hovered ? "#505050" : "transparent"))
                        border.color:"transparent"
                        border.width: 1
                    }

                    onClicked: fileDialog.open()
                }
            }

            Row {
                anchors.verticalCenter: parent.verticalCenter
                spacing: 20
                anchors.right: parent.right
                height: 30

                Button {
                    id: undo
                    text: "Undo"
                    icon.source: "icon/undo.png"
                    width: 40
                    height: parent.height
                    icon.width: parent.width
                    icon.height: parent.height
                    enabled: false

                    ToolTip.visible: hovered
                    ToolTip.delay: 500
                    ToolTip.text: "Undo"

                    background: Rectangle {
                        radius: 5
                        color: (enabled? (undo.pressed ? "#007ACC" : (undo.hovered ? "#505050" : "transparent")) : "#303030")
                        border.color: "transparent"
                        border.width: 1
                    }

                    onClicked: {
                        if(enabled) menu.undoF()
                    }
                }

                Button {
                    id: redo
                    text: "Redo"
                    width: 40
                    icon.source: "icon/redo.png"
                    height: parent.height
                    icon.width: parent.width
                    icon.height: parent.height
                    enabled: false

                    ToolTip.visible: hovered
                    ToolTip.delay: 500
                    ToolTip.text: "Redo"

                    background: Rectangle {
                        radius: 5
                        color: (enabled? (redo.pressed ? "#007ACC" : (redo.hovered ? "#505050" : "transparent")) : "#303030")
                        border.color: "transparent"
                        border.width: 1
                    }

                    onClicked: {
                        if(enabled) menu.redoF()
                    }
                }

                Button {
                    id: home
                    icon.source: "icon/home.png"
                    width: 40
                    height: parent.height
                    icon.width: parent.width
                    icon.height: parent.height

                    ToolTip.visible: hovered
                    ToolTip.delay: 500
                    ToolTip.text: "Go to main menu"

                    background: Rectangle {
                        radius: 5
                        color: (home.pressed ? "#007ACC" : (home.hovered ? "#505050" : "transparent"))
                        border.color: "transparent"
                        border.width: 1
                    }

                    onClicked: exit.visible = !exit.visible
                }
            }
        }

        // left side bar
        Rectangle {
            id: filter
            color: "#2B2B2B"
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#444444" }
                GradientStop { position: 1.0; color: "#222222" }
            }
            border.color: "#1A1A1A"
            border.width: 1
            width: 0.04 * parent.width
            height: 0.97 * parent.height
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            ScrollView {
                anchors.fill: parent
                ColumnLayout {

                    Button {
                        id: gray
                        width: 70
                        height: 50
                        icon.source: "icon/gray.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Gray Scale"

                        background: Rectangle {
                            radius: 5
                            color: (gray.pressed ? "#007ACC" : (gray.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: { menu.grayScale() }
                    }

                    Button {
                        id: bw
                        width: 70
                        height: 50
                        icon.source: "icon/blackAndwhite.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Black and White"
                        background: Rectangle {
                            radius: 5
                            color: (bw.pressed ? "#007ACC" : (bw.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: { menu.blackWhite() }
                    }

                    Button {
                        id: invert
                        width: 70
                        height: 50
                        icon.source: "icon/invert.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Invert Color"

                        background: Rectangle {
                            radius: 5
                            color: (invert.pressed ? "#007ACC" : (invert.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: { menu.invertImage() }
                    }

                    Button {
                        id: merge
                        width: 70
                        height: 50
                        icon.source: "icon/Merge.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Merge Image"

                        background: Rectangle {
                            radius: 5
                            color: (merge.pressed ? "#007ACC" : (merge.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: fileDialog2.open()
                    }

                    Button {
                        id: flip
                        width: 70
                        height: 50
                        icon.source: "icon/flip.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Flip Image"

                        background: Rectangle {
                            radius: 5
                            color: (flip.pressed ? "#007ACC" : (flip.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: flipOption.visible = !flipOption.visible
                    }

                    Button {
                        id: rotate
                        width: 70
                        height: 50
                        icon.source: "icon/rotate.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Rotate Image"

                        background: Rectangle {
                            radius: 5
                            color: (rotate.pressed ? "#007ACC" : (rotate.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: rotateOption.visible = !rotateOption.visible
                    }

                    Button {
                        id: brightness
                        width: 70
                        height: 50
                        icon.source: "icon/bright.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Adjust Brightness"

                        background: Rectangle {
                            radius: 5
                            color: (brightness.pressed ? "#007ACC" : (brightness.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: { sliders.visible = !sliders.visible }
                    }

                    Button {
                        id: cropButton
                        width: 70
                        height: 50
                        icon.source: "icon/crop.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Crop Image"

                        background: Rectangle {
                            radius: 5
                            color: (cropButton.pressed ? "#007ACC" : (cropButton.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: {
                            imageArea.cropMode = !imageArea.cropMode;
                            crop.visible = !crop.visible
                            selectionRect.visible = !selectionRect.visible
                        }
                    }

                    Button {
                        id: detect
                        width: 70
                        height: 50
                        icon.source: "icon/edge.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Detect Edges"

                        background: Rectangle {
                            radius: 5
                            color: (detect.pressed ? "#007ACC" : (detect.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: {
                            mainRect.closeAll()
                            detectSlider.visible = !detectSlider.visible
                        }
                    }

                    Button {
                        id: resize
                        width: 70
                        height: 50
                        icon.source: "icon/resize.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Resize Image"

                        background: Rectangle {
                            radius: 5
                            color: (resize.pressed ? "#007ACC" : (resize.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: resizeBar.visible = !resizeBar.visible
                    }

                    Button {
                        id: blur
                        width: 70
                        height: 50
                        icon.source: "icon/blur.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Blur Image"

                        background: Rectangle {
                            radius: 5
                            color: (blur.pressed ? "#007ACC" : (blur.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: {
                            mainRect.closeAll()
                            blurSlider.visible = !blurSlider.visible
                        }
                    }

                    Button {
                        id: contrast
                        width: 70
                        height: 50
                        icon.source: "icon/contrast.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Adjust Contrast"

                        background: Rectangle {
                            radius: 5
                            color: (contrast.pressed ? "#007ACC" : (contrast.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: {
                            mainRect.closeAll()
                            contrastSlider.visible = !contrastSlider.visible
                        }
                    }

                    Button {
                        id: purple
                        width: 70
                        height: 50
                        icon.source: "icon/purple.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Purple Filter"

                        background: Rectangle {
                            radius: 5
                            color: (purple.pressed ? "#007ACC" : (purple.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: { menu.purbleFilter() }
                    }

                    Button {
                        id: infrared
                        width: 70
                        height: 50
                        icon.source: "icon/infrared.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Infrared Filter"

                        background: Rectangle {
                            radius: 5
                            color: (infrared.pressed ? "#007ACC" : (infrared.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: { menu.infraredFilter() }
                    }

                    Button {
                        id: sun
                        width: 70
                        height: 50
                        icon.source: "icon/sun.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Adjust Sun"

                        background: Rectangle {
                            radius: 5
                            color: (sun.pressed ? "#007ACC" : (sun.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: {
                            mainRect.closeAll()
                            sunsSlider.visible = !sunsSlider.visible
                        }
                    }

                    Button {
                        id: tv
                        width: 70
                        height: 50
                        icon.source: "icon/tv.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Old Tv Effect"

                        background: Rectangle {
                            radius: 5
                            color: (tv.pressed ? "#007ACC" : (tv.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: { menu.tv() }
                    }

                    Button {
                        id: frame
                        width: 70
                        height: 50
                        icon.source: "icon/frame.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Add frame"

                        background: Rectangle {
                            radius: 5
                            color: (frame.pressed ? "#007ACC" : (frame.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: {
                            colorPicker.visible = !colorPicker.visible
                            frameOption.visible = !frameOption.visible
                        }
                    }

                    Button {
                        id: skew
                        width: 70
                        height: 50
                        icon.source: "icon/skew.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Skew Image"

                        background: Rectangle {
                            radius: 5
                            color: (skew.pressed ? "#007ACC" : (skew.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: {
                            mainRect.closeAll()
                            skewSlider.visible = !skewSlider.visible
                        }
                    }

                    Button {
                        id: oil
                        width: 70
                        height: 50
                        icon.source: "icon/oil.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Convert to Oil painting"

                        background: Rectangle {
                            radius: 5
                            color: (oil.pressed ? "#007ACC" : (oil.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: {
                            mainRect.closeAll()
                            oilSlider.visible = !oilSlider.visible
                        }
                    }

                    Button {
                        id: oldPhoto
                        width: 70
                        height: 50
                        icon.source: "icon/oldPhoto.png"
                        icon.width: 50
                        icon.height: 50

                        ToolTip.visible: hovered
                        ToolTip.delay: 500
                        ToolTip.text: "Old Photo Effect"

                        background: Rectangle {
                            radius: 5
                            color: (oldPhoto.pressed ? "#007ACC" : (oldPhoto.hovered ? "#505050" : "transparent"))
                            border.color: "#555555"
                            border.width: 1
                        }
                        onClicked: {
                            menu.oldPhoto()
                        }
                    }
                }
            }
        }

        // Sliders
        Rectangle {
            id: sliders
            color: "#555555"
            height: 150
            anchors.bottom: parent.bottom
            anchors.left: filter.right
            anchors.right: parent.right
            visible: false
            border.color: "#555555"
            border.width: 1

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#3A3A3A" }
                GradientStop { position: 1.0; color: "#252525" }
            }

            Column {
                anchors.centerIn: parent
                spacing: 20

                Row {
                    spacing: 10
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        text: "Brightness"
                        color: "white"
                        font.pixelSize: 18
                        font.bold: true
                    }

                    Text {
                        id: brightValueLabel
                        text: Math.round(brightnessSlider.value) + "%"
                        color: "#CCCCCC"
                        font.pixelSize: 16
                    }
                }

                Rectangle {
                    width: 320
                    height: 8
                    radius: 4
                    color: "#333"
                    anchors.horizontalCenter: parent.horizontalCenter

                    Rectangle {
                        width: (parent.width * (brightnessSlider.value - brightnessSlider.from) / (brightnessSlider.to - brightnessSlider.from))
                        height: parent.height
                        radius: parent.radius
                        color: "#007ACC"
                    }

                    Rectangle {
                        width: 20
                        height: 20
                        radius: 10
                        color: "#FFFFFF"
                        border.color: "#007ACC"
                        border.width: 2
                        y: parent.height / 2 - height / 2
                        x: (parent.width - width) * (brightnessSlider.value - brightnessSlider.from) / (brightnessSlider.to - brightnessSlider.from)
                    }

                    Slider {
                        id: brightnessSlider
                        anchors.fill: parent
                        from: -100
                        to: 100
                        value: 0
                        opacity: 0.0001
                        onValueChanged: brightValueLabel.text = Math.round(value) + "%"
                    }
                }


                Row {
                    spacing: 20
                    anchors.horizontalCenter: parent.horizontalCenter

                    Button {
                        id: apply
                        text: "Apply"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: apply.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (apply.pressed ? "#007ACC" : (apply.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: {
                            menu.brightness(brightnessSlider.value)
                            sliders.visible = false
                        }
                    }

                    Button {
                        id: cancelBright
                        text: "Cancel"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: cancelBright.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (cancelBright.pressed ? "#007ACC" : (cancelBright.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: sliders.visible = false
                    }
                }
            }
        }

        Rectangle {
            id: detectSlider
            color: "#555555"
            height: 150
            anchors.bottom: parent.bottom
            anchors.left: filter.right
            anchors.right: parent.right
            visible: false
            border.color: "#555555"
            border.width: 1

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#3A3A3A" }
                GradientStop { position: 1.0; color: "#252525" }
            }

            Column {
                anchors.centerIn: parent
                spacing: 10

                Row {
                    spacing: 10
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        text: "Edegs"
                        color: "white"
                        font.pixelSize: 18
                        font.bold: true
                    }

                    Text {
                        id: detectValueLabel
                        text: Math.round(detectslide.value) + "%"
                        color: "#CCCCCC"
                        font.pixelSize: 16
                    }
                }

                Rectangle {
                    width: 320
                    height: 8
                    radius: 4
                    color: "#333"
                    anchors.horizontalCenter: parent.horizontalCenter

                    Rectangle {
                        width: (parent.width * (detectslide.value - detectslide.from) / (detectslide.to - detectslide.from))
                        height: parent.height
                        radius: parent.radius
                        color: "#007ACC"
                    }

                    Rectangle {
                        width: 20
                        height: 20
                        radius: 10
                        color: "#FFFFFF"
                        border.color: "#007ACC"
                        border.width: 2
                        y: parent.height / 2 - height / 2
                        x: (parent.width - width) * (detectslide.value - detectslide.from) / (detectslide.to - detectslide.from)
                    }

                    Slider {
                        id: detectslide
                        anchors.fill: parent
                        from: 0
                        to: 100
                        value: 0
                        opacity: 0.0001
                        onValueChanged: detectValueLabel.text = Math.round(value) + "%"
                    }
                }

                Row {
                    spacing: 20
                    anchors.horizontalCenter: parent.horizontalCenter

                    Button {
                        id: applyDetect
                        text: "Apply"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: applyDetect.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (applyDetect.pressed ? "#007ACC" : (applyDetect.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: {
                            menu.detectEdges(detectslide.value)
                            detectSlider.visible = false
                        }
                    }

                    Button {
                        id: cancelDetect
                        text: "Cancel"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: cancelDetect.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (cancelDetect.pressed ? "#007ACC" : (cancelDetect.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: detectSlider.visible = false
                    }
                }
            }
        }

        Rectangle {
            id: blurSlider
            color: "#555555"
            height: 150
            anchors.bottom: parent.bottom
            anchors.left: filter.right
            anchors.right: parent.right
            visible: false
            border.color: "#555555"
            border.width: 1

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#3A3A3A" }
                GradientStop { position: 1.0; color: "#252525" }
            }

            Column {
                anchors.centerIn: parent
                spacing: 10

                Row {
                    spacing: 10
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        text: "Blur"
                        color: "white"
                        font.pixelSize: 18
                        font.bold: true
                    }

                    Text {
                        id: blurValueLabel
                        text: Math.round(blurslider.value) + "%"
                        color: "#CCCCCC"
                        font.pixelSize: 16
                    }
                }

                Rectangle {
                    width: 320
                    height: 8
                    radius: 4
                    color: "#333"
                    anchors.horizontalCenter: parent.horizontalCenter

                    Rectangle {
                        width: (parent.width * (blurslider.value - blurslider.from) / (blurslider.to - blurslider.from))
                        height: parent.height
                        radius: parent.radius
                        color: "#007ACC"
                    }

                    Rectangle {
                        width: 20
                        height: 20
                        radius: 10
                        color: "#FFFFFF"
                        border.color: "#007ACC"
                        border.width: 2
                        y: parent.height / 2 - height / 2
                        x: (parent.width - width) * (blurslider.value - blurslider.from) / (blurslider.to - blurslider.from)
                    }

                    Slider {
                        id: blurslider
                        anchors.fill: parent
                        from: 0
                        to: 100
                        value: 0
                        opacity: 0.0001
                        onValueChanged: blurValueLabel.text = Math.round(value) + "%"
                    }
                }

                Row {
                    spacing: 20
                    anchors.horizontalCenter: parent.horizontalCenter

                    Button {
                        id: applyblur
                        text: "Apply"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: applyblur.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (applyblur.pressed ? "#007ACC" : (applyblur.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: {
                            menu.blurImage(1, blurslider.value)
                            blurSlider.visible = false
                        }
                    }

                    Button {
                        id: cancelBlur
                        text: "Cancel"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: cancelBlur.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (cancelBlur.pressed ? "#007ACC" : (cancelBlur.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: blurSlider.visible  = false
                    }
                }
            }
        }

        Rectangle {
            id: contrastSlider
            color: "#555555"
            height: 150
            anchors.bottom: parent.bottom
            anchors.left: filter.right
            anchors.right: parent.right
            visible: false
            border.color: "#555555"
            border.width: 1

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#3A3A3A" }
                GradientStop { position: 1.0; color: "#252525" }
            }

            Column {
                anchors.centerIn: parent
                spacing: 10

                Row {
                    spacing: 10
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        text: "Contrast"
                        color: "white"
                        font.pixelSize: 18
                        font.bold: true
                    }

                    Text {
                        id: contrastValueLabel
                        text: Math.round(contrastslider.value) + "%"
                        color: "#CCCCCC"
                        font.pixelSize: 16
                    }
                }

                Rectangle {
                    width: 320
                    height: 8
                    radius: 4
                    color: "#333"
                    anchors.horizontalCenter: parent.horizontalCenter

                    Rectangle {
                        width: (parent.width * (contrastslider.value - contrastslider.from) / (contrastslider.to - contrastslider.from))
                        height: parent.height
                        radius: parent.radius
                        color: "#007ACC"
                    }

                    Rectangle {
                        width: 20
                        height: 20
                        radius: 10
                        color: "#FFFFFF"
                        border.color: "#007ACC"
                        border.width: 2
                        y: parent.height / 2 - height / 2
                        x: (parent.width - width) * (contrastslider.value - contrastslider.from) / (contrastslider.to - contrastslider.from)
                    }

                    Slider {
                        id: contrastslider
                        anchors.fill: parent
                        from: -100
                        to: 100
                        value: 0
                        opacity: 0.0001
                        onValueChanged: contrastValueLabel.text = Math.round(value) + "%"
                    }
                }

                Row {
                    spacing: 20
                    anchors.horizontalCenter: parent.horizontalCenter

                    Button {
                        id: applyContrast
                        text: "Apply"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: applyContrast.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (applyContrast.pressed ? "#007ACC" : (applyContrast.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: {
                            menu.contrast(contrastslider.value)
                            contrastSlider.visible = false
                        }
                    }

                    Button {
                        id: cancelContrast
                        text: "Cancel"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: cancelContrast.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (cancelContrast.pressed ? "#007ACC" : (cancelContrast.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: contrastSlider.visible = false
                    }
                }
            }
        }

        Rectangle {
            id: sunsSlider
            color: "#555555"
            height: 150
            anchors.bottom: parent.bottom
            anchors.left: filter.right
            anchors.right: parent.right
            visible: false
            border.color: "#555555"
            border.width: 1

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#3A3A3A" }
                GradientStop { position: 1.0; color: "#252525" }
            }

            Column {
                anchors.centerIn: parent
                spacing: 10

                Row {
                    spacing: 10
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        text: "Sun"
                        color: "white"
                        font.pixelSize: 18
                        font.bold: true
                    }

                    Text {
                        id: sunValueLabel
                        text: Math.round(sunslider.value) + "%"
                        color: "#CCCCCC"
                        font.pixelSize: 16
                    }
                }

                Rectangle {
                    width: 320
                    height: 8
                    radius: 4
                    color: "#333"
                    anchors.horizontalCenter: parent.horizontalCenter

                    Rectangle {
                        width: (parent.width * (sunslider.value - sunslider.from) / (sunslider.to - sunslider.from))
                        height: parent.height
                        radius: parent.radius
                        color: "#007ACC"
                    }

                    Rectangle {
                        width: 20
                        height: 20
                        radius: 10
                        color: "#FFFFFF"
                        border.color: "#007ACC"
                        border.width: 2
                        y: parent.height / 2 - height / 2
                        x: (parent.width - width) * (sunslider.value - sunslider.from) / (sunslider.to - sunslider.from)
                    }

                    Slider {
                        id: sunslider
                        anchors.fill: parent
                        from: 0
                        to: 100
                        value: 0
                        opacity: 0.0001
                        onValueChanged: sunValueLabel.text = Math.round(value) + "%"
                    }
                }

                Row {
                    spacing: 20
                    anchors.horizontalCenter: parent.horizontalCenter

                    Button {
                        id: applySun
                        text: "Apply"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: applySun.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (applySun.pressed ? "#007ACC" : (applySun.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: {
                            menu.sun(sunslider.value)
                            sunsSlider.visible = false
                        }
                    }

                    Button {
                        id: cancelSun
                        text: "Cancel"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: cancelSun.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (cancelSun.pressed ? "#007ACC" : (cancelSun.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: sunsSlider.visible = false
                    }
                }
            }
        }

        Rectangle {
            id: skewSlider
            color: "#555555"
            height: 150
            anchors.bottom: parent.bottom
            anchors.left: filter.right
            anchors.right: parent.right
            visible: false
            border.color: "#555555"
            border.width: 1

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#3A3A3A" }
                GradientStop { position: 1.0; color: "#252525" }
            }

            Column {
                anchors.centerIn: parent
                spacing: 10

                Row {
                    spacing: 10
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        text: "Degree"
                        color: "white"
                        font.pixelSize: 18
                        font.bold: true
                    }

                    Text {
                        id: skewValueLabel
                        text: Math.round(skewslider.value) + "%"
                        color: "#CCCCCC"
                        font.pixelSize: 16
                    }
                }

                Rectangle {
                    width: 320
                    height: 8
                    radius: 4
                    color: "#333"
                    anchors.horizontalCenter: parent.horizontalCenter

                    Rectangle {
                        width: (parent.width * (skewslider.value - skewslider.from) / (skewslider.to - skewslider.from))
                        height: parent.height
                        radius: parent.radius
                        color: "#007ACC"
                    }

                    Rectangle {
                        width: 20
                        height: 20
                        radius: 10
                        color: "#FFFFFF"
                        border.color: "#007ACC"
                        border.width: 2
                        y: parent.height / 2 - height / 2
                        x: (parent.width - width) * (skewslider.value - skewslider.from) / (skewslider.to - skewslider.from)
                    }

                    Slider {
                        id: skewslider
                        anchors.fill: parent
                        from: 0
                        to: 89
                        value: 0
                        opacity: 0.0001
                        onValueChanged: skewValueLabel.text = Math.round(value)
                    }
                }

                Row {
                    spacing: 20
                    anchors.horizontalCenter: parent.horizontalCenter

                    Button {
                        id: applySkew
                        text: "Apply"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: applySkew.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (applySkew.pressed ? "#007ACC" : (applySkew.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: {
                            menu.skew(skewslider.value)
                            skewSlider.visible = false
                        }
                    }

                    Button {
                        id: cancelSkew
                        text: "Cancel"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: cancelSkew.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (cancelSkew.pressed ? "#007ACC" : (cancelSkew.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: skewSlider.visible = false
                    }
                }
            }
        }

        Rectangle {
            id: oilSlider
            color: "#555555"
            height: 150
            anchors.bottom: parent.bottom
            anchors.left: filter.right
            anchors.right: parent.right
            visible: false
            border.color: "#555555"
            border.width: 1

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#3A3A3A" }
                GradientStop { position: 1.0; color: "#252525" }
            }

            Column {
                anchors.centerIn: parent
                spacing: 10

                Row {
                    spacing: 10
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        text: "Percentage"
                        color: "white"
                        font.pixelSize: 18
                        font.bold: true
                    }

                    Text {
                        id: oilValueLabel
                        text: Math.round(oilslider.value) + "%"
                        color: "#CCCCCC"
                        font.pixelSize: 16
                    }
                }

                Rectangle {
                    width: 320
                    height: 8
                    radius: 4
                    color: "#333"
                    anchors.horizontalCenter: parent.horizontalCenter

                    Rectangle {
                        width: (parent.width * (oilslider.value - oilslider.from) / (oilslider.to - oilslider.from))
                        height: parent.height
                        radius: parent.radius
                        color: "#007ACC"
                    }

                    Rectangle {
                        width: 20
                        height: 20
                        radius: 10
                        color: "#FFFFFF"
                        border.color: "#007ACC"
                        border.width: 2
                        y: parent.height / 2 - height / 2
                        x: (parent.width - width) * (oilslider.value - oilslider.from) / (oilslider.to - oilslider.from)
                    }

                    Slider {
                        id: oilslider
                        anchors.fill: parent
                        from: 0
                        to: 100
                        value: 0
                        opacity: 0.0001
                        onValueChanged: oilValueLabel.text = Math.round(value) + "%"
                    }
                }

                Row {
                    spacing: 20
                    anchors.horizontalCenter: parent.horizontalCenter

                    Button {
                        id: applyOil
                        text: "Apply"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: applyOil.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (applyOil.pressed ? "#007ACC" : (applyOil.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: {
                            menu.oilPainting(Math.max(1,oilslider.value))
                            oilSlider.visible = false
                        }
                    }

                    Button {
                        id: cancelOil
                        text: "Cancel"
                        width: 100
                        height: 40

                        contentItem: Text {
                            text: cancelOil.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        background: Rectangle {
                            radius: 6
                            color: (cancelOil.pressed ? "#007ACC" : (cancelOil.hovered ? "#505050" : "#3C3C3C"))
                            border.color: "#666"
                        }

                        onClicked: oilSlider.visible = false
                    }
                }
            }
        }

        // Files Explorer
        FileDialog {
            id: fileDialog
            title: "Select an Image"
            nameFilters: ["Images (*.png *.jpg *.jpeg *.bmp)"]

            onAccepted: {
                if (file !== "") {
                    var path = file
                    menu.loadImage(path)
                    imageDisplay.source = file
                    console.log(path)
                }
            }
        }

        FileDialog {
            id: fileDialog2
            title: "Select an Image"
            nameFilters: ["Images (*.png *.jpg *.jpeg *.bmp)"]

            onAccepted: {
                if (file !== "") {
                    var path = file
                    imageDisplay2.source = file
                    mergeParam.visible = true
                    console.log(path)
                }
            }
        }

        FileDialog {
            id: saveAsDialog
            title: "Save Image As"
            nameFilters: ["Image files (*.png *.jpg *.jpeg *.bmp)"]
            fileMode: FileDialog.SaveFile

            onAccepted: {
                if (saveAsDialog.file) {
                    var path = saveAsDialog.file.toString()
                    console.log("Saving to:", path)
                    menu.saveImage(path)
                }
            }
        }
    }
}
