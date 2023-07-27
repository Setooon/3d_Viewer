/**
 *
 * @file mainwindow.cpp
 *
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), gif_timer(new QTimer)
{
    ui->setupUi(this);

    settings = new QSettings("3DViewer", "3DViewer Settings", this);
    loadSettings();
    connect(gif_timer, SIGNAL(timeout()), this, SLOT(create_gif()));
    this->ui->widget->lbl = ui->label_23;
    this->ui->widget->lbl_36 = ui->label_36;
}

MainWindow::~MainWindow()
{
    saveSattings();
    if (pgif) delete pgif;
    delete gif_timer;
    delete ui;
}

void MainWindow::saveSattings()
{
    // 1 - Уникальное имя  2 - Значение
// ------------------------------------------------------------------------------
    settings->beginGroup("Color and Size"); // группа настроек цвета

        settings->beginGroup("Color Line");

            settings->setValue("Color Line R", ui->ColorLine_R->value());
            settings->setValue("Color Line G", ui->ColorLine_G->value());
            settings->setValue("Color Line B", ui->ColorLine_B->value());

        settings->endGroup();

        settings->beginGroup("Size Line");

            settings->setValue("Size Line", ui->SizePoint->value());

        settings->endGroup();
// ------------------------------------------------------------------------------
        settings->beginGroup("Color Point");

            settings->setValue("Color Point R", ui->ColorPoint_R->value());
            settings->setValue("Color Point G", ui->ColorPoint_G->value());
            settings->setValue("Color Point B", ui->ColorPoint_B->value());

        settings->endGroup();

        settings->beginGroup("Size Point");

            settings->setValue("Size Point", ui->SizePoint_2->value());

        settings->endGroup();
// ------------------------------------------------------------------------------
        settings->beginGroup("Color Font");

            settings->setValue("Color Font R", ui->ColorPoint_R_2->value());
            settings->setValue("Color Font G", ui->ColorPoint_G_2->value());
            settings->setValue("Color Font B", ui->ColorPoint_B_2->value());

        settings->endGroup();
    settings->endGroup();
// ------------------------------------------------------------------------------

    settings->beginGroup("Other");

        settings->setValue("Type Line", this->ui->widget->LineStipple); // LineStipple

        settings->setValue("Type Point", this->ui->widget->PointType); // PointType

        settings->setValue("Type Projection", this->ui->widget->ProjectionType); // ProjectionType

    settings->endGroup();
}

void MainWindow::loadSettings()
{
// ------------------------------------------------------------------------------
    settings->beginGroup("Color and Size"); // загрузка группы настроек цвета
        settings->beginGroup("Color Line");

            ui->ColorLine_R->setValue(settings->value("Color Line R", 0).toInt());
            this->ui->widget->LineR = settings->value("Color Line R", 0).toInt();

            ui->ColorLine_G->setValue(settings->value("Color Line G", 0).toInt());
            this->ui->widget->LineG = settings->value("Color Line G", 0).toInt();

            ui->ColorLine_B->setValue(settings->value("Color Line B", INT_MAX).toInt());
            this->ui->widget->LineB = settings->value("Color Line B", INT_MAX).toInt();

        settings->endGroup();

        settings->beginGroup("Size Line");

            ui->SizePoint->setValue(settings->value("Size Line", 5).toInt());
            this->ui->widget->LineSize = settings->value("Size Line", 5).toInt();

        settings->endGroup();
// ------------------------------------------------------------------------------
        settings->beginGroup("Color Point");

            ui->ColorPoint_R->setValue(settings->value("Color Point R", INT_MAX).toInt());
            this->ui->widget->PointR = settings->value("Color Point R", INT_MAX).toInt();

            ui->ColorPoint_G->setValue(settings->value("Color Point G", 0).toInt());
            this->ui->widget->PointG = settings->value("Color Point G", 0).toInt();

            ui->ColorPoint_B->setValue(settings->value("Color Point B", 0).toInt());
            this->ui->widget->PointB = settings->value("Color Point B", 0).toInt();

        settings->endGroup();

        settings->beginGroup("Size Point");

            ui->SizePoint_2->setValue(settings->value("Size Point", 20).toInt());
            this->ui->widget->PointSize = settings->value("Size Point", 20).toInt();

        settings->endGroup();
// ------------------------------------------------------------------------------
        settings->beginGroup("Color Font");

            ui->ColorPoint_R_2->setValue(settings->value("Color Font R", 0).toInt());
            this->ui->widget->r = settings->value("Color Font R", 0).toInt();

            ui->ColorPoint_G_2->setValue(settings->value("Color Font G", 0).toInt());
            this->ui->widget->g = settings->value("Color Font G", 0).toInt();

            ui->ColorPoint_B_2->setValue(settings->value("Color Font B", 0).toInt());
            this->ui->widget->b = settings->value("Color Font B", 0).toInt();

        settings->endGroup();
    settings->endGroup();
// ------------------------------------------------------------------------------

    settings->beginGroup("Other");
        this->ui->widget->LineStipple = settings->value("Type Line", 1).toBool();
        if(this->ui->widget->LineStipple == 1)
        {
            ui->checkBox->setChecked(true);
            ui->checkBox_2->setChecked(false);
        } else {
            ui->checkBox->setChecked(false);
            ui->checkBox_2->setChecked(true);
        }

        this->ui->widget->PointType = settings->value("Type Point", 1).toInt(); // PointType
        if(this->ui->widget->PointType == 0)
        {
            ui->PointBox->setChecked(false);
            ui->PointRound->setChecked(false);
            ui->PointMissing->setDisabled(true);
            ui->PointMissing->setChecked(true);
            ui->PointRound->setDisabled(false);
            ui->PointBox->setDisabled(false);
        } else if(this->ui->widget->PointType == 1)
        {
            ui->PointMissing->setChecked(false);
            ui->PointBox->setChecked(false);
            ui->PointRound->setDisabled(true);
            ui->PointRound->setChecked(true);
            ui->PointBox->setDisabled(false);
            ui->PointMissing->setDisabled(false);
        } else if(this->ui->widget->PointType == 2)
        {
            ui->PointMissing->setChecked(false);
            ui->PointRound->setChecked(false);
            ui->PointBox->setDisabled(true);
            ui->PointBox->setChecked(true);
            ui->PointRound->setDisabled(false);
            ui->PointMissing->setDisabled(false);
        }

        this->ui->widget->ProjectionType = settings->value("Type Projection", 1).toBool(); // ProjectionType
        if(this->ui->widget->ProjectionType == 1)
        {
            ui->Central->setChecked(false);
            ui->Straight->setDisabled(true);
            ui->Central->setDisabled(false);
        } else if(this->ui->widget->ProjectionType == 0)
        {
            ui->Straight->setChecked(false);
            ui->Straight->setDisabled(false);
            ui->Central->setDisabled(true);
            ui->Central->setChecked(true);
        }

    settings->endGroup();
}

void MainWindow::on_pushButton_pX_clicked()
{
    this->ui->widget->x += sizesdvig;
    this->ui->label_res_x->setText(QString::number(this->ui->widget->x));
}

void MainWindow::on_pushButton_mX_clicked()
{
    this->ui->widget->x -= sizesdvig;
    this->ui->label_res_x->setText(QString::number(this->ui->widget->x));
}

void MainWindow::on_pushButton_pY_clicked()
{
    this->ui->widget->y += sizesdvig;
    this->ui->label_res_y->setText(QString::number(this->ui->widget->y));
}

void MainWindow::on_pushButton_mY_clicked()
{
    this->ui->widget->y -= sizesdvig;
    this->ui->label_res_y->setText(QString::number(this->ui->widget->y));
}

void MainWindow::on_pushButton_pZ_clicked()
{
    this->ui->widget->z += sizesdvig;
    this->ui->label_res_z->setText(QString::number(this->ui->widget->z));
}

void MainWindow::on_pushButton_mZ_clicked()
{
    this->ui->widget->z -= sizesdvig;
    this->ui->label_res_z->setText(QString::number(this->ui->widget->z));
}

void MainWindow::on_scale_l_clicked()
{
    this->ui->widget->scale *= 0.75;
    this->ui->scale_res->setText(QString::number((int)(this->ui->widget->scale * 100)));

    scaling(this->ui->widget->res, 0.75);
}

void MainWindow::on_scale_r_clicked()
{
    this->ui->widget->scale /= 0.75;
    this->ui->scale_res->setText(QString::number((int)(this->ui->widget->scale * 100)));

    scaling(this->ui->widget->res, 1.0/0.75);

}

void MainWindow::on_verticalSlider_sliderMoved(int position)
{
    this->ui->widget->Rx = position;
    this->ui->label_14->setText(QString::number(position));
}

void MainWindow::on_verticalSlider_2_sliderMoved(int position)
{
    this->ui->widget->Ry = position;
    this->ui->label_13->setText(QString::number(position));
}

void MainWindow::on_verticalSlider_3_sliderMoved(int position)
{
    this->ui->widget->Rz = position;
    this->ui->label_12->setText(QString::number(position));
}

void MainWindow::on_pushButton_2_clicked()
{
    this->ui->widget->str = QFileDialog::getOpenFileName(this, "Open File", ".", "obj file (*.obj);;"); // в str хронится путь до файла, его можно передать в парсер
    this->ui->widget->FOpen = 1;
    ui->label_filename->setText(this->ui->widget->str);

    ui->scale_res->setText("100");
    ui->label_res_x->setText("0");
    ui->label_res_y->setText("0");
    ui->label_res_z->setText("0");
    ui->label_12->setText("0");
    ui->label_13->setText("0");
    ui->label_14->setText("0");

    ui->verticalSlider->setSliderPosition(0);
    ui->verticalSlider_2->setSliderPosition(0);
    ui->verticalSlider_3->setSliderPosition(0);
}

void MainWindow::on_ColorLine_R_sliderMoved(int position)
{
    this->ui->widget->LineR = position;
}

void MainWindow::on_ColorLine_G_sliderMoved(int position)
{
    this->ui->widget->LineG = position;
}

void MainWindow::on_ColorLine_B_sliderMoved(int position)
{
    this->ui->widget->LineB = position;
}

void MainWindow::on_SizePoint_sliderMoved(int position)
{
    this->ui->widget->LineSize = position;
}

void MainWindow::on_ColorPoint_R_sliderMoved(int position)
{
    this->ui->widget->PointR = position;
}

void MainWindow::on_ColorPoint_G_sliderMoved(int position)
{
    this->ui->widget->PointG = position;
}

void MainWindow::on_ColorPoint_B_sliderMoved(int position)
{
    this->ui->widget->PointB = position;
}

void MainWindow::on_SizePoint_2_sliderMoved(int position)
{
    this->ui->widget->PointSize = position;
}

void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
    // отсутствуют
    if(arg1)
    {
        this->ui->widget->LineStipple = 2;
        ui->checkBox_5->setDisabled(true);

        ui->checkBox->setDisabled(false);
        ui->checkBox->setChecked(false);

        ui->checkBox_2->setChecked(false);
        ui->checkBox_2->setDisabled(false);
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    //прямая
    if(arg1)
    {
        this->ui->widget->LineStipple = 1;
        ui->checkBox->setDisabled(true);

        ui->checkBox_2->setDisabled(false);
        ui->checkBox_2->setChecked(false);

        ui->checkBox_5->setChecked(false);
        ui->checkBox_5->setDisabled(false);
    }
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    //пунктирная
    if(arg1)
    {
        this->ui->widget->LineStipple = 0;
        ui->checkBox_2->setDisabled(true);

        ui->checkBox->setChecked(false);
        ui->checkBox->setDisabled(false);

        ui->checkBox_5->setDisabled(false);
        ui->checkBox_5->setChecked(false);
    }

}

void MainWindow::on_ColorPoint_R_2_sliderMoved(int position)
{
    this->ui->widget->r = position;
}

void MainWindow::on_ColorPoint_G_2_sliderMoved(int position)
{
    this->ui->widget->g = position;
}

void MainWindow::on_ColorPoint_B_2_sliderMoved(int position)
{
    this->ui->widget->b = position;
}

void MainWindow::on_PointMissing_stateChanged(int arg1)
{
    // точки отсутствуют
    if(arg1)
    {
        this->ui->widget->PointType = 0;
        ui->PointBox->setChecked(false);
        ui->PointRound->setChecked(false);
        ui->PointMissing->setDisabled(true);
        ui->PointRound->setDisabled(false);
        ui->PointBox->setDisabled(false);
    }
}

void MainWindow::on_PointRound_stateChanged(int arg1)
{
    // точки круглые
    if(arg1)
    {
        this->ui->widget->PointType = 1;
        ui->PointMissing->setChecked(false);
        ui->PointBox->setChecked(false);
        ui->PointRound->setDisabled(true);
        ui->PointBox->setDisabled(false);
        ui->PointMissing->setDisabled(false);
    }
}

void MainWindow::on_PointBox_stateChanged(int arg1)
{
    // точки квадратные
    if(arg1)
    {
        this->ui->widget->PointType = 2;
        ui->PointMissing->setChecked(false);
        ui->PointRound->setChecked(false);
        ui->PointBox->setDisabled(true);
        ui->PointRound->setDisabled(false);
        ui->PointMissing->setDisabled(false);
    }
}

void MainWindow::on_Straight_stateChanged(int arg1)
{
    //прямая проекция
    if(arg1)
    {
        this->ui->widget->ProjectionType = 1;
        ui->Central->setChecked(false);
        ui->Straight->setDisabled(true);
        ui->Central->setDisabled(false);
    }
}

void MainWindow::on_Central_stateChanged(int arg1)
{
    // центральная проекция
    if(arg1)
    {
        this->ui->widget->ProjectionType = 0;
        ui->Straight->setChecked(false);
        ui->Straight->setDisabled(false);
        ui->Central->setDisabled(true);
    }
}

void MainWindow::on_jpeg_create_clicked()
{
    QString fileName = ui->name_file->text();
    if (fileName != "") {
      QImage img = ui->widget->grabFramebuffer();
      QString directoryName = QFileDialog::getExistingDirectory(this, "Выбирите папку",
        "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks) + "/";
      img.save(directoryName + fileName + ".jpeg", "JPEG");
    }
}

void MainWindow::on_bmp_create_clicked()
{
    QString filename = ui->name_file->text();
    if (filename != "") {
      QImage img = ui->widget->grabFramebuffer();
      QString dirname = QFileDialog::getExistingDirectory(this, "Выбирите папку",
        "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks) + "/";
      img.save(dirname + filename + ".bmp", "BMP");
    }
}

void MainWindow::create_gif() {
    if (pgif->frameCount() < 50) {
        QImage frame = ui->widget->grabFramebuffer();
        pgif->addFrame(frame.scaled(640, 480));
        return;
    }
    gif_timer->stop();
    ui->gif_create->setText("Создать gif");
    QString filename = ui->name_file->text();
    QString dirname = QFileDialog::getExistingDirectory(this, "Выбирите папку",
    "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks) + "/";
    pgif->save(dirname + filename + ".gif");
}

void MainWindow::on_gif_create_clicked()
{
    if (ui->name_file->text() != "" && ui->gif_create->text() == "Создать gif") {
        ui->gif_create->setText("Запись...");
        pgif = new QGifImage;
        pgif->setDefaultDelay(100);
        gif_timer->start(100);
    }
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    this->ui->widget->autorotate = arg1;
}

void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    this->ui->widget->xyz = arg1;
}


