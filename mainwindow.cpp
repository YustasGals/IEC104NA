#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <settingsdialog.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // ui->tabWidget->setContentsMargins(0,0,0,0);
    settings = new CSetting();
    driver = new IEC104Driver();

    connectionStatusLabel= new QLabel();
    statusBar()->addWidget(connectionStatusLabel);

    connect(driver,SIGNAL(Connected()),this,SLOT(OnConnected()));
    connect(driver,SIGNAL(Disconnected()),this,SLOT(OnDisconnected()));

    connect(driver,SIGNAL(Message(QString)),this,SLOT(LogReceived(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnConnectPressed(void)
{
    //IEC104Driver::GetInstance()->OpenConnection(settings->IP,settings->Port);
    driver->OpenConnection(settings);
}

void MainWindow::OnDisconnectPressed(void)
{
    //IEC104Driver::GetInstance()->CloseConnection();
    driver->CloseConnection();

}

void MainWindow::OnSettingsPressed(void)
{
    SettingsDialog *cdialog = new SettingsDialog(settings);
    cdialog->exec();
}

void MainWindow::OnConnected()
{
    connectionStatusLabel->setText("connected: "+settings->IP);
    ui->actionConnect->setEnabled(false);
    ui->actionDisconnect->setEnabled(true);
}

void MainWindow::OnDisconnected()
{
    connectionStatusLabel->setText("disconnected");
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);

    ui->log->append("Соединение разорвано");
}

void MainWindow::LogReceived(QString text)
{
    ui->log->append(text);
}