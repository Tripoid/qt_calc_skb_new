#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "button.h"
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QtWidgets/qdialog.h>
#include <QGridLayout>
#include <QToolButton>
#include <QDebug>
#include <QtMath>
#include <QMessageBox>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void displayResult(const QList<QString> &symbol);
    void calcResult();
    void addOper();
    void pusto();
    void clearDisplay();
    void checkString();
    void onceBack();
private:
    Ui::MainWindow *ui;

    button* createButton(const QString &text, const char* member);
    button* digitButtons[10];

    QLineEdit* display;

    bool waitingForOperand;

    QList<QString> opersMain;
};
#endif // MAINWINDOW_H
