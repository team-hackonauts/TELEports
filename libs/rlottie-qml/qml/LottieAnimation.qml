import QLottieFrameProvider 1.0
import QtMultimedia 5.12
import QtQuick 2.7

Item {
    id: lottieItem
    property alias source: frameProvider.source
    property alias play: frameProvider.play
    function next() {
        frameProvider.requestFrame()
    }

    QLottieFrameProvider {
        id: frameProvider
        property bool play: false
        width: videoOutput.width
        onWidthChanged: requestFrame(play)
        height: videoOutput.height
        onHeightChanged: requestFrame(play)
        onPlayChanged: if (play) { requestFrame() }
        onFramePresented: if (play) { requestFrame() }
    }

    VideoOutput {
        id: videoOutput
        source: frameProvider
        anchors.fill: parent
    }

    ShaderEffect {
        id: removeBackground
        anchors.fill: videoOutput
        property variant source: ShaderEffectSource { sourceItem: videoOutput; hideSource: true }

        fragmentShader: "
            varying highp vec2 qt_TexCoord0;
            uniform sampler2D source;
            uniform lowp float qt_Opacity;
            void main() {
                lowp vec4 sourceColor = texture2D(source, qt_TexCoord0);
                gl_FragColor = sourceColor * qt_Opacity;
        }"
    }
    Component.onCompleted: frameProvider.requestFrame()
}
