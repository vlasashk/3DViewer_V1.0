#include "./ui_mainwindow.h"
#include "mainwindow.h"

void MainWindow::initTransformSettings() {
  double currentMoveX = 0;
  double currentMoveY = 0;
  double currentMoveZ = 0;
  int currentRotateX = 0;
  int currentRotateY = 0;
  int currentRotateZ = 0;
  int currentScale = 100;
  ui->spinBox_MoveX->setValue(0);
  ui->spinBox_MoveY->setValue(0);
  ui->spinBox_MoveZ->setValue(0);

  ui->spinBox_MoveX_Fact->setValue(1);
  ui->spinBox_MoveY_Fact->setValue(1);
  ui->spinBox_MoveZ_Fact->setValue(1);

  ui->spinBox_rotX->setValue(0);
  ui->spinBox_rotY->setValue(0);
  ui->spinBox_rotZ->setValue(0);

  ui->horizontalSlider_Scale->setValue(100);
}

void MainWindow::saveSettings() {
  QColor color;
  settings->beginGroup("Colors");
  color = ui->label_backgroundColor->palette().color(QPalette::Window);
  settings->setValue("BackgroundR", color.red());
  settings->setValue("BackgroundG", color.green());
  settings->setValue("BackgroundB", color.blue());
  settings->setValue("BackgroundA", color.alpha());
  color = ui->label_lineColor->palette().color(QPalette::Window);
  settings->setValue("LineR", color.red());
  settings->setValue("LineG", color.green());
  settings->setValue("LineB", color.blue());
  color = ui->label_vertexColor->palette().color(QPalette::Window);
  settings->setValue("VertexR", color.red());
  settings->setValue("VertexG", color.green());
  settings->setValue("VertexB", color.blue());
  settings->endGroup();

  settings->beginGroup("LineStyle");
  settings->setValue("LineSolid", ui->radioButton_LineSolid->isChecked());
  settings->setValue("LineWidth", ui->doubleSpinBox_LineSize->value());
  settings->endGroup();

  settings->beginGroup("VertexStyle");
  settings->setValue("None", ui->radioButton_VertexNone->isChecked());
  settings->setValue("Circle", ui->radioButton_VertexCircle->isChecked());
  settings->setValue("Square", ui->radioButton_VertexSquare->isChecked());
  settings->setValue("VertexSize", ui->doubleSpinBox_VertexSize->value());
  settings->endGroup();

  settings->beginGroup("Projection");
  settings->setValue("CentralProjection", ui->radioButton_Central->isChecked());
  settings->endGroup();
}

void MainWindow::downloadSettings() {
  QColor color;
  settings->beginGroup("Colors");
  color = QColor(settings->value("BackgroundR", 58.0).toInt(),
                 settings->value("BackgroundG", 57.0).toInt(),
                 settings->value("BackgroundB", 57.0).toInt(),
                 settings->value("BackgroundA", 0.0).toInt());
  colorChanger(color, 0);
  color = QColor(settings->value("LineR", 242.0).toInt(),
                 settings->value("LineG", 165.0).toInt(),
                 settings->value("LineB", 60.0).toInt(), 0);
  colorChanger(color, 1);

  color = QColor(settings->value("VertexR", 242.0).toInt(),
                 settings->value("VertexG", 165.0).toInt(),
                 settings->value("VertexB", 60.0).toInt(), 0);
  colorChanger(color, 2);
  settings->endGroup();

  settings->beginGroup("LineStyle");
  if (settings->value("LineSolid", true).toBool()) {
    ui->radioButton_LineSolid->setChecked(true);
  } else {
    ui->radioButton_LineDashed->setChecked(true);
  }
  ui->doubleSpinBox_LineSize->setValue(
      settings->value("LineWidth", ui->doubleSpinBox_LineSize->value())
          .toDouble());
  settings->endGroup();

  settings->beginGroup("VertexStyle");
  if (settings->value("None", true).toBool()) {
    ui->radioButton_VertexNone->setChecked(true);
  } else if (settings->value("Circle", true).toBool()) {
    ui->radioButton_VertexCircle->setChecked(true);
  } else if (settings->value("Square", true).toBool()) {
    ui->radioButton_VertexSquare->setChecked(true);
  }
  ui->doubleSpinBox_VertexSize->setValue(
      settings->value("VertexSize", ui->doubleSpinBox_VertexSize->value())
          .toDouble());
  settings->endGroup();

  settings->beginGroup("Projection");
  if (settings->value("CentralProjection", true).toBool()) {
    ui->radioButton_Central->setChecked(true);
  } else {
    ui->radioButton_Parallel->setChecked(true);
  }
  settings->endGroup();
}
