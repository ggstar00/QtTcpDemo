#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
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
    void on_pBt_listen_clicked();

    void on_pBt_send_clicked();

    void ConnectClient();

    void ReadData();

private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    QTcpSocket *socket;
};
#endif // MAINWINDOW_H
