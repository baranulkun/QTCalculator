#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUI();
}

void MainWindow::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    layout = new QGridLayout();
    layout->setSpacing(10);

    display = new QLineEdit(this);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setStyleSheet(R"(
        QLineEdit {
            font-size: 28px;
            padding: 10px;
            border-radius: 10px;
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #ffffff, stop:1 #dfe6e9);
            border: 2px solid #b2bec3;
            color: #2d3436;
        }
    )");
    layout->addWidget(display, 0, 0, 1, 4);

    QString buttonLabels[16] = { "7", "8", "9", "/",
                                "4", "5", "6", "*",
                                "1", "2", "3", "-",
                                "C", "0", "=", "+" };

    int index = 0;
    for (int row = 1; row < 5; ++row) {
        for (int col = 0; col < 4; ++col) {
            buttons[index] = new QPushButton(buttonLabels[index], this);
            buttons[index]->setFixedSize(60, 60);

            if (buttonLabels[index] == "C") {
                buttons[index]->setStyleSheet(R"(
                    QPushButton {
                        background-color: #d63031;
                        color: white;
                        font-size: 20px;
                        border-radius: 10px;
                    }
                    QPushButton:hover {
                        background-color: #ff7675;
                    }
                )");
            } else if (buttonLabels[index] == "=") {
                buttons[index]->setStyleSheet(R"(
                    QPushButton {
                        background-color: #0984e3;
                        color: white;
                        font-size: 20px;
                        border-radius: 10px;
                    }
                    QPushButton:hover {
                        background-color: #74b9ff;
                    }
                )");
            } else if (buttonLabels[index] == "+" || buttonLabels[index] == "-" ||
                       buttonLabels[index] == "*" || buttonLabels[index] == "/") {
                buttons[index]->setStyleSheet(R"(
                    QPushButton {
                        background-color: #636e72;
                        color: white;
                        font-size: 20px;
                        border-radius: 10px;
                    }
                    QPushButton:hover {
                        background-color: #b2bec3;
                    }
                )");
            } else {
                buttons[index]->setStyleSheet(R"(
                    QPushButton {
                        background-color: #2d3436;
                        color: white;
                        font-size: 20px;
                        border-radius: 10px;
                    }
                    QPushButton:hover {
                        background-color: #636e72;
                    }
                )");
            }

            layout->addWidget(buttons[index], row, col);
            connect(buttons[index], &QPushButton::clicked, this, &MainWindow::onButtonClicked);
            index++;
        }
    }

    centralWidget->setLayout(layout);
    centralWidget->setStyleSheet("background-color: #f5f6fa;"); // Hafif açık arka plan
}



void MainWindow::onButtonClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;

    QString buttonText = clickedButton->text();
    QString currentText = display->text();
    if (!currentText.isEmpty()) {
        QChar lastChar = currentText[currentText.length() - 1];

        if (QString("*/+-").contains(lastChar) && QString("*/+-").contains(buttonText)) {
            if (lastChar == buttonText[0]) {
                return;
            }
            else {
                currentText.chop(1);
                currentText += buttonText;
                display->setText(currentText);
                return;
            }
        }
    }
    if (buttonText == "C") {
        display->clear();
    } else if (buttonText == "=") {
        hesapla();
    } else {
        display->setText(currentText + buttonText);
    }
}


void MainWindow::hesapla() {
    QString currentText = display ->displayText();
    QVector<int> numbers;
    QVector<QString> operators;
    QString currentNumber;

    for (int i = 0; i < currentText.length(); ++i) {
        QChar ch = currentText[i];

        if (ch.isDigit()) {
            currentNumber += ch;
        } else {
            if (!currentNumber.isEmpty()) {
                numbers.append(currentNumber.toInt());
                currentNumber.clear();
            }

            if (ch == '-' && (i == 0 || (!currentText[i - 1].isDigit() && currentText[i - 1] != ')'))) {
                currentNumber += ch;
            } else {
                operators.append(QString(ch));
            }
        }
    }

    if (!currentNumber.isEmpty()) {
        numbers.append(currentNumber.toInt());
    }

    for (int i=0; i< operators.length(); i++){
        if(operators[i]=="*"){
            qDebug() << i ;
            qDebug() << "Çarpma" << numbers[i] << "*" << numbers[i+1];
            qint64 newInt = numbers[i]*numbers[i+1];
            numbers[i+1] = newInt;
            numbers.removeAt(i);
            operators.removeAt(i);
            i--;
        }
        else if(operators[i]=="/"){
            qDebug() << i ;
            qDebug() << "Bölme" << numbers[i] << "/" << numbers[i+1];
            qint64 newInt = numbers[i]/numbers[i+1];
            numbers[i+1] = newInt;
            numbers.removeAt(i);
            operators.removeAt(i);
            i--;
        }
    }

    for(int i=0; i<operators.length();i++){
        if(operators[i]=="+"){
            qDebug() << "Toplama" << numbers[i] << "+" << numbers[i+1];
            qint64 newInt = numbers[i]+numbers[i+1];
            numbers[i+1] = newInt;
            numbers.removeAt(i);
            operators.removeAt(i);
            i--;
        }
        else if(operators[i]=="-"){
            qDebug() << "Çıkarma" << numbers[i] << "-" << numbers[i+1];
            qint64 newInt = numbers[i]-numbers[i+1];
            numbers[i+1] = newInt;
            numbers.removeAt(i);
            operators.removeAt(i);
            i--;
        }
    }
    display->setText(QString::number(numbers[0]));
}

