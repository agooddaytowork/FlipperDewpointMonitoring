import QtQuick 2.7
import QtCharts 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtQuick.VirtualKeyboard 2.1
import CustomControls 1.0


Item {
    property  int  schannel
    ChartView{
        id: chartView
         anchors.fill: parent

        theme: ChartView.ChartThemeDark
        animationOptions:  ChartView.SeriesAnimations
        antialiasing: true
        property  int initialX
        property int  initialY
        property double currentScale

        function toMsecsSinceEpoch(date) {
            var msecs = date.getTime();
            return msecs;
        }
        PinchArea{
            width: parent.width
            height: parent.height

            onPinchStarted: {
                chartView.currentScale = pinch.scale
                chartView.initialX = pinch.center.x
                valueIndicatorLine.visible = true
            }

            onPinchUpdated: {

                chartView.scrollLeft(pinch.center.x - pinch.previousCenter.x)
                chartView.scrollUp(pinch.center.y - pinch.previousCenter.y)

                if(Math.abs(pinch.center.x - chartView.initialX) >= 100)
                {
//                    LocalDb.updateDataToGraph(temperatureSerie,voltageSerie, currentSerie, axisX1.min, axisX1.max, sRFID)
                    chartView.initialX = pinch.center.x
                }

                if(Math.abs(pinch.scale - chartView.currentScale) >= 0.3)
                {

                    chartView.currentScale = pinch.scale
                    if (pinch.scale < 1)
                    {

                        if(Math.abs(chartView.toMsecsSinceEpoch(axisX1.min) - chartView.toMsecsSinceEpoch(axisX1.max)) <(24*60*60*1000))
                        {
                            axisX1.min = new Date(axisX1.min - 1000000*(1/pinch.scale))
                            axisX1.max = new Date(axisX1.max + 1000000*(1/pinch.scale))
                        }
                        else
                        {
                            axisX1.min = new Date(axisX1.max - (24*60*60*1000))
                        }
                    }
                    else
                    {
                        if(Math.abs(chartView.toMsecsSinceEpoch(axisX1.min) - chartView.toMsecsSinceEpoch(axisX1.max)) > (20*60*1000))
                        {
                            axisX1.min = new Date(axisX1.min + 1000000*pinch.scale)
                            axisX1.max = new Date(axisX1.max - 1000000*pinch.scale)
                        }
                        else
                        {
                            axisX1.min = new Date(axisX1.max - (20*60*1000))
                        }

                    }

//                    LocalDb.updateDataToGraph(temperatureSerie, voltageSerie, currentSerie, axisX1.min, axisX1.max, sRFID)

                }
                // //console.log("pinch scale: " + pinch.scale)
            }

            onPinchFinished:
            {

                // have to have something here to limit the min and max zoom on xAxis

//                LocalDb.updateDataToGraph(temperatureSerie, voltageSerie, currentSerie, axisX1.min, axisX1.max, sRFID)
                valueIndicatorLine.visible = false

            }
        }


        Rectangle
        {
            id: valueIndicatorLine
            width: 3
            height: 580
            color: "red"
            visible: false
            x:parent.width/2
            y:80
            z:3

        }

        ValueAxis{
            id: axisY2
            min: -100
            max: 20
            tickCount: 6
            labelFormat: "%d"


        }

        DateTimeAxis{
            id: axisX1
            tickCount: 6
            min: new Date(new Date() - 10000000)
            max: new Date()
            format: "MMM\dd hh:mm"
        }

        LineSeries{
            id: temperatureSerie
            name: "Channel Temperature"
            axisX: axisX1
            axisY: axisY2
            useOpenGL: true
            width: 4
            color: "cyan"
            style: Qt.DashLine

        }

        Timer
        {
            id:loadGraphFirstTimeTimer
            interval:0
            repeat: false
            running: true
            triggeredOnStart: true
            onTriggered:
            {
                console.log(schannel)
                theGuiInterface.updateChartData(schannel, temperatureSerie, axisX1)
                console.log(temperatureSerie.at(0).x)

            }
        }
        // Timer to load graph the first time, only run one time
        Timer
        {
            id:loadGraphScheduleTimer
            interval:30000
            repeat: true
            running:theGuiInterface.isRecording
            triggeredOnStart: false
            onTriggered:
            {
                theGuiInterface.updateChartData(schannel, temperatureSerie, axisX1)


            }
        }
    }
}
