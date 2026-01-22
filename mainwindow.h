#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QString>
#include <QStringListModel>

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

private:
    Ui::MainWindow *ui;
    QString dbPath;
    QSqlDatabase db;
    QStringListModel *activityModel;
    QStringList activityLog;
    void addLog(const QString &message);

private slots:
    void on_configButton_clicked();
    void on_connectButton_clicked();
    void on_disconnectButton_clicked();
    void on_queryButton_clicked();
};


#endif // MAINWINDOW_H
