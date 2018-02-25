#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <csetting.h>
#include <iec104driver.h>
#include "tablemodel.h"
#include <QSettings>
#include <QLabel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    //CSetting *settings;
    QSettings *qsettings;
    IEC104Driver *driver;
    TableModel *tabmodel;

    ~MainWindow();

private:
    Ui::MainWindow *ui;
     QLabel *connectionStatusLabel;
public slots:
    void OnConnectPressed(void);
    void OnConnectAck(void);//

    void OnDisconnectPressed(void);
    void OnSettingsPressed(void);
    void OnConnected();
    void OnDisconnected();
    void LogReceived(QString);
    void OnClearLogPressed();

    void MToolAdd();
    void MToolRemove();
    void IECReceived(CIECSignal* tag);

    void OnGIPressed(void); //general interrogation
};

#endif // MAINWINDOW_H
