#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initial_config();
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

        auto csvInfo = read_csv(m_InputFile.toStdString());
        std::string siteName{"init"};
        int sectorOrder{1};
        int colorSelector;
        std::string sectorColor;

        for(const auto& obj: csvInfo.second)
        {

            if(obj.m_SiteName != siteName)
            {
                sectorOrder = 1;
                out << create_site_style(obj);
                out << create_site_info(obj);
                siteName = obj.m_SiteName;
            }

            colorSelector = sectorOrder % 4;
            if(colorSelector == 0) colorSelector++;

            switch(colorSelector)
            {
                case 1:
                    sectorColor= change_color_name_endian(m_SecOneColor.name().toStdString());
                    out << create_sector_style(obj, sectorColor);
                    break;
                case 2:
                    sectorColor = change_color_name_endian(m_SecTwoColor.name().toStdString());
                    out << create_sector_style(obj, sectorColor);
                    break;
                case 3:
                    sectorColor = change_color_name_endian(m_SecThreeColor.name().toStdString());
                    out << create_sector_style(obj, sectorColor);
                    break;
            }
            out << create_sector(obj, m_SectorSize);

            ++sectorOrder;
            sectorColor.clear();
        }
        out << R"(</Document></kml>)";

        out.close();

    }

    QMessageBox::about(this, ".kml", "Done");

}

void MainWindow::on_sizeSectorBox_valueChanged(int size)
{
    m_SectorSize = ui->sizeSectorBox->value();
}

void MainWindow::on_buttonColorSec1_clicked()
{
    m_SecOneColor = QColorDialog::getColor(Qt::blue, this, "Select Color");

    QPalette palette = ui->widgetColorSec1->palette();
    palette.setColor(QPalette::Background, m_SecOneColor);
    ui->widgetColorSec1->setPalette(palette);

}

void MainWindow::on_buttonColorSec2_clicked()
{
    m_SecTwoColor = QColorDialog::getColor(Qt::red, this, "Select Color");

    QPalette palette = ui->widgetColorSec2->palette();
    palette.setColor(QPalette::Background, m_SecTwoColor);
    ui->widgetColorSec2->setPalette(palette);
}

void MainWindow::on_buttonColorSec3_clicked()
{
    m_SecThreeColor = QColorDialog::getColor(Qt::gray, this, "Select Color");

    QPalette palette = ui->labelColorSec3->palette();
    palette.setColor(QPalette::Background, m_SecThreeColor);
    ui->widgetColorSec3->setPalette(palette);
}




void MainWindow::initial_config()
{
    m_SectorSize = 100;
    ui->widgetColorSec1->setAutoFillBackground(true);
    ui->widgetColorSec2->setAutoFillBackground(true);
    ui->widgetColorSec3->setAutoFillBackground(true);

    m_SecOneColor = Qt::blue;
    QPalette palette = ui->widgetColorSec1->palette();
    palette.setColor(QPalette::Background, m_SecOneColor);
    ui->widgetColorSec1->setPalette(palette);

    m_SecTwoColor = Qt::red;
    palette = ui->widgetColorSec2->palette();
    palette.setColor(QPalette::Background, m_SecTwoColor);
    ui->widgetColorSec2->setPalette(palette);

    m_SecThreeColor = Qt::gray;
    palette = ui->widgetColorSec3->palette();
    palette.setColor(QPalette::Background, m_SecThreeColor);
    ui->widgetColorSec3->setPalette(palette);

}


