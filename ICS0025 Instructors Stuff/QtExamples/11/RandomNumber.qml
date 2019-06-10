import QtQuick 2.4

RandomNumberForm {
    exitButton.onClicked: {
        Qt.quit();
   }
    computeButton.onClicked: {
        var val1 = parseInt(fieldLower.text);
        var val2 = parseInt(fieldUpper.text);
        fieldResult.text = randomGenerator.getRandomNumber(val1, val2);
   }
}
