import "functions.js" as JS
import QtQuick 2.7

import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtPositioning 5.4
import QtQuick.Controls.Styles 1.4
import Qt.labs.folderlistmodel 1.0
//import QtNetworkInterface 1.0

ApplicationWindow {
    id: mainwindow
    objectName:"mainwindow"
    visible: true
    width: Screen.width
    height: Screen.height
    property double lati:59.65
    property double longi:9.67
    property real speed:2
    property real direction:0
    property real magHeading:271
    readonly property color lightBackgroundColor: "#cccccc"
    readonly property color darkBackgroundColor: "#282A2E"
    readonly property color oldbg :"#161616"
    property color lightFontColor: "#222"
    property color darkFontColor: "#e7e7e7"

    property var waypoints:[]
    property int activeWaypoints:0
    property var guiWaypoints:[]

    property bool createWaypoints:false
    property var latBot: 57.9540811
    property var latTop:58.0477806
    property var longLeft:7.2912077
    property var longRight:7.529351
    property real accuracy
    property bool accuracyValid
    property string manual: "Manual"
    property string connectedState:"No"
    property bool controlActive


    PositionSource{
        id:src2
        updateInterval:1
        active:true
        onPositionChanged: {
            var tmp=src2.position.coordinate;
            lati = tmp.latitude;
            longi = tmp.longitude
            speed = src2.position.speed
            direction = src2.position.direction
            magHeading = JS.roundNumber(direction,0)
            accuracy = src2.position.horizontalAccuracy
            accuracyValid = src2.position.horizontalAccuracyValid
        }
    }

    Item{
        Connections {
            target: myInMessage
            onMessageChanged: {
                magHeading = myInMessage.getPsi
            }
        }
    }


    Rectangle{
        id:statusBar
        width: parent.width
        height: Screen.height/8
        color:oldbg
        border.width:2
        border.color: Qt.lighter("#468bb7", 1.2)
        z:100



        Text{
            font.pixelSize:parent.height*0.4
            id: headingText
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.left:parent.left 
            anchors.leftMargin:parent.width/8
            color:darkFontColor
            text:"ψ: " + magHeading+"° " + JS.degreesToName(magHeading)
        }
        Text {
            anchors.right:parent.right
            anchors.rightMargin:20
            anchors.verticalCenter: parent.verticalCenter
            y:connectText.y + connectText.contentHeight
            font.pixelSize: parent.height*0.12
            Behavior on x { NumberAnimation{ easing.type: Easing.OutCubic} }
            text:"Connected: " +connectedState + "\nGround Speed:" + JS.roundNumber(speed,1) +"Kn" +"\nTravel direction: "
            +JS.roundNumber(direction,0) + "\nGPS Accuracy: " + JS.roundNumber(accuracy,2) + "\nAccuracy Valid: " + accuracyValid
            color:darkFontColor
        }

    }
    TabBar {
        z:100
        id: bar
        width: parent.width
        anchors.top:statusBar.bottom
        TabButton {
            text: qsTr("Manual\n Control")
        }
        TabButton {
            text: qsTr("Heading \n Autopilot")
            onClicked:{
                if(controlActive){
                    myOutMessage.updateState("AP")
                }
            }
        }
        TabButton {
            text: qsTr("Waypoint \n tracking")
            onClicked:{
                if(controlActive){
                    myOutMessage.updateState("AP")
                }
            }
        }
        TabButton {
            text: qsTr("Debug")
        }
    }
    Rectangle{
        z:100
        id:menuRect
        width:parent.width
        height:parent.height/16
        anchors.top:bar.bottom
        color:oldbg
        border.width:2
        border.color:Qt.lighter("#468bb7", 1.2)


        StackLayout {
            id:stack
            width: parent.width
            currentIndex: bar.currentIndex
            anchors.fill:parent
            Item{ 
                id:manualControlTab
                Button{
                    id:counterClock
                    height: parent.height
                    width: parent.width/3
                    anchors.left:parent.left
                    text:"↶"
                    onPressed:
                    {
                        if(controlActive){
                            myOutMessage.updateState("CCW");
                        }
                    }
                    onReleased:{
                        if (controlActive){
                            myOutMessage.updateState("Hold")
                        }
                    }


                }
                Button{
                    id:clockwise
                    height: parent.height
                    width: parent.width/3
                    anchors.right:parent.right
                    text:"↷"
                    onPressed:
                    {
                        if(controlActive){
                            myOutMessage.updateState("CW");
                        }
                    }
                    onReleased:{
                        if (controlActive){
                            myOutMessage.updateState("Hold")
                        }
                    }
                }
            }
            Item {
                id: headingAutopilotTab
                AutopilotTab{}
            }
            Item {
                id: waypointtab
                WaypointTab{}
            }
            Item{
                id: debug
                Rectangle{
                    anchors.fill:parent
                    color:oldbg
                    Text{
                        id:latText
                        anchors.left:parent.left
                        text:"Latitude: "
                        color:"white"
                    }
                    TextField { 
                        id: lattitudeOffset;
                        placeholderText: qsTr("Lattitude Offset")
                        text: "0"
                        anchors.left:lonText.right
                        height: parent.height/2
                        anchors.top:parent.top
                    }
                    Text{
                        id:lonText
                        anchors.left:parent.left
                        text:"Longtitude: "
                        color:"white"
                        height: parent.height/2
                        anchors.bottom:parent.bottom
                    }
                    TextField { 
                        id: longtitudeOffset;
                        placeholderText: qsTr("Longitude Offset")
                        text: "0"
                        anchors.left:lonText.right
                        height: parent.height/2
                        anchors.bottom:parent.bottom
                    }
                }
            }
        }
    }


    Rectangle {
        color: "gray"
        id: flicrect
        anchors.top:menuRect.bottom
        anchors.left:parent.left
        anchors.right:parent.right
        anchors.bottom:parent.bottom


        Flickable {
            id: flick
            anchors.fill: parent
            contentHeight: parent.height
            contentWidth: parent.width
            boundsBehavior: Flickable.StopAtBounds
            clip:true

            MouseArea{
                anchors.fill:frame
                onClicked: {
                    if(createWaypoints){
                        waypoints.push(JS.PixelToCoordinate(mouseX*flick.visibleArea.widthRatio,mouseY*flick.visibleArea.heightRatio))
                        var tmp = JS.createRect(waypoints[waypoints.length -1])
                        guiWaypoints.push(tmp)
                        activeWaypoints++
                    }
                }
            }


            Rectangle{
                id:frame
                width:parent.width
                height:parent.height
                Image {
                    id:map
                    fillMode: Image.PreserveAspectFit
                    transformOrigin: locationDot.Center
                    anchors.fill: parent
                    source: "Images/hyttatilman.png"
                }

                Rectangle{
                    id:locationDot
                    x:JS.LongtitudeToPixel(frame.width,7.2912077,7.529351,longi-longtitudeOffset.text);
                    y:JS.LatitudeToPixel(frame.height,57.9540811,58.0477806,lati-lattitudeOffset.text)
                    width: 30
                    height:30
                    color: Qt.lighter("#468bb7", 1.2)
                    border.color: "white"
                    border.width: width*0.1
                    radius: width*0.5
                }
            }
        }

        RoundButton {
            z:100
            anchors.bottom:parent.bottom
            anchors.right:parent.right
            anchors.bottomMargin:parent.height/20
            anchors.rightMargin:parent.height/20
            height:60
            id: button
            text: ""
            implicitWidth: height
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            property string source
            onClicked:JS.zoomFull()
            palette.button: darkBackgroundColor
            Image {
                id: gps
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
                sourceSize.height: button.background.height - 6
                height: sourceSize.height
                source: "Images/gps-icon.png"
            }
        }

        DelayButton{
            id: startButton
            anchors.bottom:parent.bottom
            delay:1000
            anchors.bottomMargin:parent.height/20
            anchors.horizontalCenter: parent.horizontalCenter
            text:"Start"
            height:150
            width:250
            visible:true
            palette.button:"red"
            onActivated:{
                controlActive = true;
                stopButton.visible=true

            }
        }
        Button{
            id:stopButton
            anchors.fill:startButton
            palette.button:Qt.lighter("#468bb7", 1.2)
            text:"Stop"
            visible:false
            onClicked:{
                visible=false
                myOutMessage.updateState("OFF")
                controlActive = false;
            }

        }
        Button{
            id:zoomOut
            anchors.bottom:parent.bottom
            anchors.bottomMargin:parent.height/20
            anchors.left:parent.left
            anchors.leftMargin:20
            width:100
            palette.button:Qt.lighter("#468bb7", 1.2)
            text:"-"
            onClicked:{
                var temp = Qt.point(flick.contentX+flick.width/2,flick.contentY+flick.height/2) 
                flick.resizeContent(frame.width*1/1.2,frame.width*1/1.2, temp);
                JS.redrawWP()

            }

        }
        Button{
            id:zoomIn
            anchors.bottom:parent.bottom
            anchors.bottomMargin:parent.height/20
            anchors.left:zoomOut.right
            anchors.leftMargin:20
            width:100
            palette.button:Qt.lighter("#468bb7", 1.2)
            text:"+"
            onClicked:{
                var temp = Qt.point(flick.contentX+flick.width/2,flick.contentY+flick.height/2) 
                flick.resizeContent(frame.width*1.2,frame.width*1.2, temp);
                JS.redrawWP()
                myOutMessage.updateCoordinates(longi,lati);
            }

        }
    }

}
