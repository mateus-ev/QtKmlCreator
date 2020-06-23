#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_inputFileButton_clicked()
{
    m_InputFile = QFileDialog::getOpenFileName(this, "Open a file", "C:\\" );
    ui->inputFilePath->setPlainText(m_InputFile);
}

void MainWindow::on_inputFilePath_textChanged()
{
    m_InputFile = ui->inputFilePath->toPlainText();

}

void MainWindow::on_outputDirButton_clicked()
{
    m_OutputFile = QFileDialog::getSaveFileName(this, "Save file", "C:\\", tr("kml file (*.kml)"));
    ui->outputFilePath->setPlainText(m_OutputFile);
}

void MainWindow::on_outputFilePath_textChanged()
{
    m_OutputFile = ui->outputFilePath->toPlainText();
}

void MainWindow::on_generateButton_clicked()
{
    auto obj = read_csv(m_InputFile.toStdString());
    std::ofstream out(m_OutputFile.toStdString(), std::ios::out);
    if(out.is_open())
    {
        for(const auto& el: obj.second)
            out << el.str() << "\n";
        out.close();
        QMessageBox::about(this, ".kml generator", "Done");
    }

}
