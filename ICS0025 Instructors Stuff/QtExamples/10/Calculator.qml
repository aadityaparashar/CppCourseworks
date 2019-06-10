import QtQuick 2.4

CalculatorForm {
    multiplyButton.onClicked: {
        var x1 = parseFloat(fieldX1.text);
        var x2 = parseFloat(fieldX2.text);
        resultField.text = x1 * x2;
    }
    addButtom.onClicked: {
        var x1 = parseFloat(fieldX1.text);
        var x2 = parseFloat(fieldX2.text);
        resultField.text = x1 + x2;
    }
    resetButton.onClicked: {
        fieldX1.text = "0"
        fieldX2.text = "0"
    }
    exitButton.onClicked: {
        Qt.quit();
    }
}
