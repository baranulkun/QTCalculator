#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onButtonClicked();
    void hesapla();

private:
    QLineEdit *display;
    QWidget *centralWidget;
    QGridLayout *layout;
    QPushButton *buttons[16];

    void setupUI();
};

#endif // MAINWINDOW_H
