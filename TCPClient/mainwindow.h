#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pBt_connect_clicked();

    void on_pBt_send_clicked();

    void ReadData();

private:
    Ui::MainWindow *ui;
    QTcpSocket* socket;
};
#endif // MAINWINDOW_H
