#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_inputFileButton_clicked();

    void on_inputFilePath_textChanged();

    void on_outputDirButton_clicked();

    void on_outputFilePath_textChanged();

private:
    Ui::MainWindow *ui;

private:
    QString m_InputFile;
    QString m_OutputFile;

};
#endif // MAINWINDOW_H
