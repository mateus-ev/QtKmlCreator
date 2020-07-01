/*
 *  author: Mateus Evangelista
 *  license model:
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QColor>
#include <QPalette>
#include <QColorDialog>

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

    void on_buttonColorSec1_clicked();

    void on_buttonColorSec2_clicked();

    void on_buttonColorSec3_clicked();

    void on_randomColorCheckbox_stateChanged(int arg1);

    void on_pciCheckbox_stateChanged(int arg1);

    void on_siteLabelCheckbox_stateChanged(int arg1);

    void on_sectorLabelCheckbox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;

private:
    QString m_InputFile;
    QString m_OutputFile;
    int m_SectorSize;
    QColor m_SecOneColor;
    QColor m_SecTwoColor;
    QColor m_SecThreeColor;
    bool m_RandomColor;
    bool m_SectorIdentifier;
    bool m_SectorLabel;
    bool m_SiteLabel;

private:
    void initial_config();

};
#endif // MAINWINDOW_H
