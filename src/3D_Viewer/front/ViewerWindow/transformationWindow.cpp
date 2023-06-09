#include "./ui_mainwindow.h"
#include "mainwindow.h"

/*---------------------Rotate via buttons---------------------*/
void MainWindow::on_horizontalSlider_rotX_valueChanged(int value) {
  emit emitRotateObjX(value - currentRotateX);
  currentRotateX = value;
  ui->spinBox_rotX->setValue(value);
}

void MainWindow::on_spinBox_rotX_valueChanged(int value) {
  ui->horizontalSlider_rotX->setValue(value);
}

void MainWindow::on_horizontalSlider_rotY_valueChanged(int value) {
  emit emitRotateObjY(value - currentRotateY);
  currentRotateY = value;
  ui->spinBox_rotY->setValue(value);
}

void MainWindow::on_spinBox_rotY_valueChanged(int value) {
  ui->horizontalSlider_rotY->setValue(value);
}

void MainWindow::on_horizontalSlider_rotZ_valueChanged(int value) {
  emit emitRotateObjZ(value - currentRotateZ);
  currentRotateZ = value;
  ui->spinBox_rotZ->setValue(value);
}

void MainWindow::on_spinBox_rotZ_valueChanged(int value) {
  ui->horizontalSlider_rotZ->setValue(value);
}

/*---------------------Scale via buttons---------------------*/
void MainWindow::on_horizontalSlider_Scale_valueChanged(int value) {
  if (currentScale > value) {
    emit emitZoomObj(-2);
  } else {
    emit emitZoomObj(2);
  }
  currentScale = value;
}

/*---------------------Move via buttons---------------------*/
void MainWindow::on_horizontalSlider_moveX_valueChanged(int value) {
  double moveVal = (value - currentMoveX) / 100.0;
  int factor = ui->spinBox_MoveX_Fact->value();
  emit emitMoveObjX(moveVal * factor);
  currentMoveX = value;
  ui->spinBox_MoveX->setValue(value);
}

void MainWindow::on_horizontalSlider_moveY_valueChanged(int value) {
  double moveVal = (value - currentMoveY) / 100.0;
  int factor = ui->spinBox_MoveY_Fact->value();
  emit emitMoveObjY(moveVal * factor);
  currentMoveY = value;
  ui->spinBox_MoveY->setValue(value);
}

void MainWindow::on_horizontalSlider_moveZ_valueChanged(int value) {
  double moveVal = (value - currentMoveZ) / 100.0;
  int factor = ui->spinBox_MoveZ_Fact->value();
  emit emitMoveObjZ(moveVal * factor);
  currentMoveZ = value;
  ui->spinBox_MoveZ->setValue(value);
}

void MainWindow::on_spinBox_MoveX_valueChanged(int value) {
  ui->horizontalSlider_moveX->setValue(value);
}

void MainWindow::on_spinBox_MoveY_valueChanged(int value) {
  ui->horizontalSlider_moveY->setValue(value);
}

void MainWindow::on_spinBox_MoveZ_valueChanged(int value) {
  ui->horizontalSlider_moveZ->setValue(value);
}
