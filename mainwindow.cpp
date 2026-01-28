#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QSqlQuery>
#include <QSqlError>
#include <QInputDialog>
#include <QSqlQueryModel>
#include <QStringListModel>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    activityModel = new QStringListModel(this);
    ui->activityView->setModel(activityModel);

    statusLabel = new QLabel("● Disconnected", this);
    ui->statusbar->addPermanentWidget(statusLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addLog(const QString &message)
{
    activityLog.prepend(message);
    activityModel->setStringList(activityLog);
}

void MainWindow::on_queryButton_clicked()
{
    if (!db.isOpen()) {
        addLog("Error: Connect to database first!");
        return;
    }

    QString sql = ui->queryEdit->toPlainText();

    if (sql.isEmpty()) {
        addLog("Error: Enter a query first!");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(sql);

    if (model->lastError().isValid()) {
        addLog("Error: " + model->lastError().text());
    } else {
        ui->resultView->setModel(model);
        addLog("Executed: " + sql.left(50));
    }
}

void MainWindow::on_actionNew_Database_triggered()
{
    QString path;

    path = QFileDialog::getSaveFileName(
        this,
        "Create New Database",
        "",
        "SQLite Database (*.db *.sqlite);;All Files (*)"
        );

    if (!path.isEmpty()){
        dbPath = path;
        statusLabel->setText("● Configured");
        addLog("Configured: " + QFileInfo(path).fileName());
    }
}

void MainWindow::on_actionOpen_Database_triggered()
{
    QString path;

    path = QFileDialog::getOpenFileName(
        this,
        "Open Existing Database",
        "",
        "SQLite Database (*.db *.sqlite);;All Files (*)"
        );

    if (!path.isEmpty()){
        dbPath = path;
        statusLabel->setText("● Configured");
        addLog("Configured: " + QFileInfo(path).fileName());
    }
}


void MainWindow::on_actionConnect_triggered()
{
    if(dbPath.isEmpty()){
        addLog("Error: Configure database first!");
        return;
    }

    db.setDatabaseName(dbPath);

    if(db.open()){
        statusLabel->setText("● Connected");
        addLog("Connected to database");
    } else {
        addLog("Error: Connection failed!");
    }
}


void MainWindow::on_actionDisconnect_triggered()
{
    if(db.isOpen()){
        db.close();
        statusLabel->setText("● Disconnected");
        addLog("Disconnected from database");
    } else {
        addLog("Error: Not connected");
    }
}

