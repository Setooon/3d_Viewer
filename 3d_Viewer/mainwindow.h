/**
 *
 * @file mainwindow.h
 *
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "unistd.h"
#include <QDebug>
#include <QFileDialog>
#include <QImage>
#include <QLabel>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>
#include <iostream>
#include <string>

#include "qgifimage.h" // гифки

#include "myopenglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  double sizesdvig = 0.25f;
  double scl = 0.1;
  void saveSattings();

  void loadSettings();

private slots:
  void on_pushButton_pX_clicked();

  void on_pushButton_mX_clicked();

  void on_pushButton_pY_clicked();

  void on_pushButton_mY_clicked();

  void on_pushButton_pZ_clicked();

  void on_pushButton_mZ_clicked();

  void on_scale_l_clicked();

  void on_scale_r_clicked();

  void on_verticalSlider_sliderMoved(int position);

  void on_verticalSlider_2_sliderMoved(int position);

  void on_verticalSlider_3_sliderMoved(int position);

  void on_pushButton_2_clicked();

  void on_ColorLine_R_sliderMoved(int position);

  void on_ColorLine_G_sliderMoved(int position);

  void on_ColorLine_B_sliderMoved(int position);

  void on_SizePoint_sliderMoved(int position);

  void on_ColorPoint_R_sliderMoved(int position);

  void on_ColorPoint_G_sliderMoved(int position);

  void on_ColorPoint_B_sliderMoved(int position);

  void on_SizePoint_2_sliderMoved(int position);

  void on_checkBox_stateChanged(int arg1);

  void on_checkBox_2_stateChanged(int arg1);

  void on_ColorPoint_R_2_sliderMoved(int position);

  void on_ColorPoint_G_2_sliderMoved(int position);

  void on_ColorPoint_B_2_sliderMoved(int position);

  void on_PointMissing_stateChanged(int arg1);

  void on_PointRound_stateChanged(int arg1);

  void on_PointBox_stateChanged(int arg1);

  void on_Straight_stateChanged(int arg1);

  void on_Central_stateChanged(int arg1);

  void on_gif_create_clicked();

  void create_gif();

  void on_jpeg_create_clicked();

  void on_bmp_create_clicked();

  void on_checkBox_3_stateChanged(int arg1);

  void on_checkBox_4_stateChanged(int arg1);

  void on_checkBox_5_stateChanged(int arg1);

private:
  Ui::MainWindow *ui;
  QSettings *settings;
  QGifImage *pgif;
  QTimer *gif_timer;
};

#endif // MAINWINDOW_H
