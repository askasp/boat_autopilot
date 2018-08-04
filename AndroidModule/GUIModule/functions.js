
function testf(a, b) {
}

function LongtitudeToPixel(ImageWidth,ImageLeftLong,ImageRightLong,LongtitudeCoordinate){
    return ImageWidth*(LongtitudeCoordinate-ImageLeftLong)/(ImageRightLong-ImageLeftLong)
}

function LatitudeToPixel(ImageHeight,ImageBottomLat,ImageTopLat,LatitudeCoordinate){
    return ImageHeight*(LatitudeCoordinate-ImageBottomLat)/(ImageTopLat-ImageBottomLat)
}

function PixelToCoordinate(x,y){
    var long = longLeft+ x*(longRight-longLeft)/flicrect.width
    var lat = latTop - y*(latTop-latBot)/flicrect.height
    return [long,lat]
}

function CoordinateToPixel(x,y){
    var xPixel = (x-longLeft)*flicrect.width/(longRight-longLeft)
    var yPixel = ((y-latTop)*flicrect.height/(-latTop+latBot))
    return [xPixel,yPixel]
}

function degreesToName(degrees){
    var piece = 360/8
    var directions = ["NE","SE","S","SW","NW"]
    var headingName = "";
    for (var i = 0; i<5; i++) { 
        if((degrees >= (i+1)*piece) && (degrees <= (i+2)*piece )){
            headingName = directions[i]
        }
    }
    if (headingName ==""){
        headingName = "N"}

    return headingName
}

function roundNumber(someNumber,decimals){
    return someNumber.toFixed(decimals)
}

function createRect(earthCoord)
{       
    var newObject = Qt.createQmlObject('import QtQuick 2.0; Rectangle {color: "red"; width: 20; height: 20;radius:width*0.5}',
    frame,
    "dynamicSnippet1");
    var pixelCoord = CoordinateToPixel(earthCoord[0],earthCoord[1])
    newObject.x = pixelCoord[0]/flick.visibleArea.widthRatio -newObject.width/2
    newObject.y = pixelCoord[1]/flick.visibleArea.heightRatio -newObject.width/2
    return newObject
}

function redrawWP(){
    for (i = 0; i < guiWaypoints.length; i++) { 
           guiWaypoints[i].destroy();
       }
    guiWaypoints=[]

    for (var i =0; i<waypoints.length;i++){
      guiWaypoints.push(createRect(waypoints[i]))
    }

}
            

    function zoomFull() {
        var temp = Qt.point(locationDot.x,locationDot.y)
        flick.contentY = locationDot.y  -flicrect.height/2
        flick.contentX = locationDot.x - flicrect.width/2
        flick.resizeContent(flicrect.width*6,flicrect.width*6, temp);
        JS.redrawWP()

    }

