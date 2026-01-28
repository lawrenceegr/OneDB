#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QString>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
class QLabel;
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
    QLabel *statusLabel;
    QStringList activityLog;
    void addLog(const QString &message);

private slots:
    void on_queryButton_clicked();
    void on_actionNew_Database_triggered();
    void on_actionOpen_Database_triggered();
    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();
};


#endif // MAINWINDOW_H
