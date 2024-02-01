#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new QTcpServer(this);
    connect(server,&QTcpServer::newConnection,this,&MainWindow::ConnectClient);//连接客户端
}

MainWindow::~MainWindow()
{
    delete ui;
    server->close();
    server->deleteLater();
}

void MainWindow::on_pBt_listen_clicked()
{
    if(ui->pBt_listen->text() == tr("监听")){
        int port = ui->lineEdit_PORT->text().toInt();
        if(!server->listen(QHostAddress::Any,port)){
            qDebug() << server->errorString();
            return;
        }
        else
            ui->pBt_listen->setText("取消监听");
    }
    else
    {
        socket->abort();
        server->close();
        ui->pBt_listen->setText("监听");
    }
}


void MainWindow::on_pBt_send_clicked()
{
    if(ui->comboBox_client->count() == 0)//没有客户端连接
        return;
    socket->write(ui->lineEdit_message->text().toUtf8());
    ui->lineEdit_message->clear();
}

void MainWindow::ConnectClient()
{
    //获取客户端连接
    while (server->hasPendingConnections()){
        socket = server->nextPendingConnection();//获取连接的socket
        QString str = QString("%1:%2").arg(socket->peerAddress().toString()).arg(socket->peerPort());
        ui->textEdit_display->append(str+"连接成功");
        ui->comboBox_client->addItem(str);
        ui->comboBox_client->setItemData(ui->comboBox_client->count()-1,socket->socketDescriptor());//保存socket描述符
        connect(socket,&QTcpSocket::readyRead,this,&MainWindow::ReadData);//接收数据
    }
}

void MainWindow::ReadData(){
    QByteArray buf = socket->readAll();
    QString str = QString("[ip:%1,port:%2]").arg(socket->peerAddress().toString()).arg(socket->peerPort());
    ui->textEdit_display->append(str + QString(buf));
}
