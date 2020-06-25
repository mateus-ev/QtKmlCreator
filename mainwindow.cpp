#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_SectorSize = 100;
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

    std::ofstream out(m_OutputFile.toStdString(), std::ios::out);
    if(out.is_open())
    {
        out << R"literal(<?xml version="1.0" encoding="UTF-8"?>

<kml xmlns="http://earth.google.com/kml/2.1">

<Document>
)literal" << '\t';

        auto obj = read_csv(m_InputFile.toStdString());

        out << create_site_style(obj.second.at(0));
        out << create_sector_style(obj.second.at(0));
        out << create_site_info(obj.second.at(0));
        out << create_sector(obj.second.at(0), m_SectorSize);

        out << R"(</Document></kml>)";



        out.close();

    }

    QMessageBox::about(this, "", "Done");

}

void MainWindow::on_sizeSectorBox_valueChanged(int size)
{
    m_SectorSize = ui->sizeSectorBox->value();
}
