#include "mainwindow.h"

MainWindow::MainWindow() : waitingForOperand(true) // interface creation
{
    QGridLayout* mainLayout = new QGridLayout;

    display = new QLineEdit();
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(20);
    display->setStyleSheet("background-color: rgba(0, 0, 0, 0);"
                           "color: black; border-radius:"
                           "12px; padding: 10px;"
                           "font-size: 30px");

    QList<QString> opersMain;

    display->setText("0");

    for (int i = 0; i < 10; ++i) {
        digitButtons[i] = createButton(QString::number(i), SLOT(addOper()));
        digitButtons[i]->setStyleSheet("background-color: gray; color: white; border-radius: 15px");
    }


    button *backspaceButton = createButton("<--", SLOT(onceBack()));
    backspaceButton->setStyleSheet("background-color: gray; color: white; border-radius: 15px");

    button *clearAllButton = createButton("AC", SLOT(clearDisplay()));
    clearAllButton->setStyleSheet("background-color: gray; color: white; border-radius: 15px");

    button *divisionButton = createButton("/", SLOT(addOper()));
    divisionButton->setStyleSheet("background-color: orange; color: white; border-radius: 15px");

    button *timesButton = createButton("*", SLOT(addOper()));
    timesButton->setStyleSheet("background-color: orange; color: white; border-radius: 15px");

    button *minusButton = createButton("-", SLOT(addOper()));
    minusButton->setStyleSheet("background-color: orange; color: white; border-radius: 15px");

    button *plusButton = createButton("+", SLOT(addOper()));
    plusButton->setStyleSheet("background-color: orange; color: white; border-radius: 15px");

    button *equalButton = createButton("=", SLOT(checkString()));
    equalButton->setStyleSheet("background-color: orange; color: white; border-radius: 15px");

    button *percentButton = createButton("%", SLOT(addOper()));
    percentButton->setStyleSheet("background-color: gray; color: white; border-radius: 15px");

    button *dotButton = createButton(".", SLOT(addOper()));
    dotButton->setStyleSheet("background-color: gray; color: white; border-radius: 15px");



    mainLayout->addWidget(display, 0, 0, 1, 6);
    setLayout(mainLayout);
    setWindowTitle("Calculator");

    for (int i = 0; i < 10; ++i) {
        int row =((9 - i) / 3) + 2;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(digitButtons[i], row, column);
    }

    mainLayout->addWidget(digitButtons[0], 5, 1, 1, 2);
    mainLayout->addWidget(clearAllButton, 1, 1);
    mainLayout->addWidget(percentButton, 1, 3);
    mainLayout->addWidget(backspaceButton, 1, 2);
    mainLayout->addWidget(dotButton, 5, 3);
    mainLayout->addWidget(divisionButton, 1, 4);
    mainLayout->addWidget(timesButton, 2, 4);
    mainLayout->addWidget(minusButton, 3, 4);
    mainLayout->addWidget(plusButton, 4, 4);
    mainLayout->addWidget(equalButton, 5, 4);


}

button *MainWindow::createButton(const QString &text, const char *member) // create button
{
    button* btn = new button(text);
    connect(btn, SIGNAL(clicked()), this, member);
    return btn;
}

void MainWindow::displayResult(const QList<QString> &symbol) //display
{
    QString resStr;
    for (int i = 0; i < symbol.size(); ++i){
        resStr += symbol[i];
    }
    display -> setText(resStr);
}


void MainWindow::calcResult() //calculate the result
{
    const QString numbers = "0123456789.";
    QString num;
    QList<float> nums;
    QList<QString> operands;
    int k = 0;
    for (int i = 0; i < opersMain.length(); ++i) {
        if ((numbers.contains(opersMain[i], Qt::CaseInsensitive)) && (k == 0)) {
            num = opersMain[i];
            k += 1;
            if (i + 1 == opersMain.length())
                {
                    nums.append(num.toFloat());
                }
        }
        else if (numbers.contains(opersMain[i], Qt::CaseInsensitive) && k != 0 && numbers.contains(opersMain[i - 1], Qt::CaseInsensitive)) {
            num = num + opersMain[i];
            if (i + 1 == opersMain.length())
            {
                nums.append(num.toFloat());
            }
        }
        else {
            k = 0;
            nums.append(num.toFloat());
            operands.append(opersMain[i]);
        }
    }


    for (int i = 0; i < operands.length(); ++i) {
        if (operands[i] == "%") {
            nums[i] = nums[i] / 100;
            operands.removeOne("%");
            i -= 1;
        }
    }

    for (int i = 0; i < operands.length(); ++i) {
        if (operands[i] == "/") {
            nums[i] = nums[i] / nums[i+1];
            nums.removeAt(i+1);
            operands.removeOne("/");
            i -= 1;
        }
        else if (operands[i] == "*") {
            nums[i] = nums[i] * nums[i+1];
            nums.removeAt(i+1);
            operands.removeOne("*");
            i -= 1;
        }
    }

    for (int i = 0; i < operands.length(); ++i) {
        if (operands[i] == "+") {
            nums[i] = nums[i] + nums[i+1];
            nums.removeAt(i+1);
            operands.removeOne("+");
            i -= 1;
        }
        else if (operands[i] == "-") {
            nums[i] = nums[i] - nums[i+1];
            nums.removeAt(i + 1);
            operands.removeOne("-");
            i -= 1;
        }
    }
    display -> setText(QString::number(nums[0]));
    opersMain.clear();
    opersMain.append(QString::number(nums[0]));
}

void MainWindow::addOper() //add operator or operand
{
    const QString numbers = "0123456789";
    const QString operands = "+*-/.";

    button *clickeckedButton = (button*) sender();
    QString component = clickeckedButton->text();
    if  (numbers.contains(component, Qt::CaseInsensitive) && opersMain.size() == 0)
    {
        opersMain.append(component);
    }
    else if (numbers.contains(component, Qt::CaseInsensitive) && opersMain.size() != 0)
    {
        if (opersMain[opersMain.length()-1] == "%" && numbers.contains(component, Qt::CaseInsensitive)){}
        else
        {
            opersMain.append(component);
        }
    }
    else if (!(opersMain.size() == 0))
    {
        if ((operands.contains(opersMain[opersMain.length()-1], Qt::CaseInsensitive)) &&
            (operands.contains(component, Qt::CaseInsensitive)))
        {
            opersMain[opersMain.length() - 1] = component;
        }
        else if ((opersMain[opersMain.length()-1] == "%" && component == "%")
                || (operands.contains(opersMain[opersMain.length()-1], Qt::CaseInsensitive))) {}
        else
        {
            opersMain.append(component);
        }
    }
    displayResult(opersMain);
}


void MainWindow::clearDisplay() //erase everything
{
    opersMain.clear();
    display->clear();
}

void MainWindow::checkString() //check string before evaluation
{
    bool flag = false;
    const QString numbers = "0123456789.";
    qDebug() << opersMain;
    if (!opersMain.isEmpty())
    {
        for (QString& n : opersMain)
        {
            qDebug() << n;
            if (!(numbers.contains(n, Qt::CaseInsensitive)))
            {
                flag = true;
                break;
            }
        }
        if (numbers.contains(opersMain[opersMain.length()-1]))
        {
            if (flag)
            {
                calcResult();
            }
            else
            {
                opersMain.clear();
                display->setText("0");
            }
        }
    }

}

void MainWindow::onceBack() //erase one character
{
    if (!opersMain.isEmpty())
    {
        opersMain.removeLast();
        displayResult(opersMain);
    }
}

void MainWindow::pusto() {

}
