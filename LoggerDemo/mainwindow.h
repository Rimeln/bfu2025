#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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
    void onWorkingButtonClicked();
    void onBrokenButtonClicked();
    void onClearButtonClicked();

    void updateLogDisplay();

private:
    Ui::MainWindow *ui;
    QTimer *logTimer;

    void setupConnections();
    QString getLogFileContent();
    void clearLogFile();

    void executeCorrectCode();
    void executeBrokenCode();
};

#endif // MAINWINDOW_H
