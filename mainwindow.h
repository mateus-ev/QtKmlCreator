#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include "utility_functions.h"

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

    void on_generateButton_clicked();

    void on_sizeSectorBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

private:
    QString m_InputFile;
    QString m_OutputFile;
    int m_SectorSize;

};
#endif // MAINWINDOW_H
