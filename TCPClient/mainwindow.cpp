#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    ui->textEdit_display->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->socket;
}

void MainWindow::on_pBt_connect_clicked()
{
    if(ui->pBt_connect->text() == tr("连接服务器")){
        QString ip = ui->lineEdit_IP->text();
        int port = ui->lineEdit_PORT->text().toInt();

        socket->abort();//取消已有连接
        socket->connectToHost(ip, port);
        bool isconnected = socket->waitForConnected();
        if(isconnected){
            ui->textEdit_display->append("连接服务器成功");
            ui->pBt_connect->setEnabled(true);
            ui->pBt_connect->setText("断开连接");
            connect(socket,&QTcpSocket::readyRead,this,&MainWindow::ReadData);
        }
        else
            ui->textEdit_display->append("连接失败");
    }
    else{
        ui->pBt_connect->setText("连接服务器");
        ui->pBt_connect->setEnabled(false);
        socket->disconnectFromHost();
    }

}


void MainWindow::on_pBt_send_clicked()
{
    QByteArray data = ui->lineEdit_message->text().toUtf8();
    socket->write(data);
    bool iswrite = socket->waitForBytesWritten();
    if(iswrite){
        qDebug()<< "发送成功";
        ui->lineEdit_message->clear();
    }
    else{
        qDebug()<< "发送失败";
    }
}

void MainWindow::ReadData()
{
    QByteArray buffer;
    buffer = socket->readAll();
    if(!buffer.isEmpty()){
        // QString str = ui->textEdit_display->toPlainText();//获取之前的显示内容
        // str += tr(buffer);
        // ui->textEdit_display->clear();
        ui->textEdit_display->append(QString(buffer));
    }
}

