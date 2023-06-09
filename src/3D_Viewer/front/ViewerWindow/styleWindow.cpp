#include "./ui_mainwindow.h"
#include "mainwindow.h"

void MainWindow::on_pushButton_widgetColor_clicked() {
  QColor initialColor = QColor(58, 57, 57, 0);
  QColor myColor = QColorDialog::getColor(initialColor, this, "Choose Color");
  if (myColor.isValid()) {
    colorChanger(myColor, 0);
  }
}

void MainWindow::on_pushButton_lineColor_clicked() {
  QColor initialColor = QColor(242, 165, 60);
  QColor myColor = QColorDialog::getColor(initialColor, this, "Choose Color");
  if (myColor.isValid()) {
    colorChanger(myColor, 1);
  }
}

void MainWindow::on_pushButton_vertexColor_clicked() {
  QColor initialColor = QColor(242, 165, 60);
  QColor myColor = QColorDialog::getColor(initialColor, this, "Choose Color");
  if (myColor.isValid()) {
    colorChanger(myColor, 2);
  }
}

void MainWindow::on_radioButton_VertexNone_toggled(bool value) {
  if (value) {
    emit emitVertexTypeChange(0);
  }
}

void MainWindow::on_radioButton_VertexCircle_toggled(bool value) {
  if (value) {
    emit emitVertexTypeChange(1);
  }
}

void MainWindow::on_radioButton_VertexSquare_toggled(bool value) {
  if (value) {
    emit emitVertexTypeChange(2);
  }
}

void MainWindow::on_radioButton_LineSolid_toggled(bool value) {
  if (value) {
    emit emitLineTypeChange(true);
  }
}

void MainWindow::on_radioButton_LineDashed_toggled(bool value) {
  if (value) {
    emit emitLineTypeChange(false);
  }
}

void MainWindow::on_radioButton_Central_toggled(bool value) {
  if (value) {
    emit emitProjectionChange(true);
  }
}

void MainWindow::on_radioButton_Parallel_toggled(bool value) {
  if (value) {
    emit emitProjectionChange(false);
  }
}

void MainWindow::on_horizontalSlider_LineSize_valueChanged(int value) {
  ui->doubleSpinBox_LineSize->setValue((double)value);
}

void MainWindow::on_doubleSpinBox_LineSize_valueChanged(double value) {
  emit emitLineWidthChange(value);
  ui->horizontalSlider_LineSize->setValue((int)value);
}

void MainWindow::on_horizontalSlider_VertexSize_valueChanged(int value) {
  ui->doubleSpinBox_VertexSize->setValue((double)value);
}

void MainWindow::on_doubleSpinBox_VertexSize_valueChanged(double value) {
  emit emitVertexSizeChange(value);
  ui->horizontalSlider_VertexSize->setValue((int)value);
}

void MainWindow::colorChanger(QColor color, int value) {
  switch (value) {
    case 0:
      emit emitWidgetColorChange(color);
      ui->label_backgroundColor->setStyleSheet(
          QString("background-color: %1; border: 1px solid white;")
              .arg(color.name()));
      break;
    case 1:
      emit emitLineColorChange(color);
      ui->label_lineColor->setStyleSheet(
          QString("background-color: %1; border: 1px solid white;")
              .arg(color.name()));
      break;
    case 2:
      emit emitVertexColorChange(color);
      ui->label_vertexColor->setStyleSheet(
          QString("background-color: %1; border: 1px solid white;")
              .arg(color.name()));
      break;
    default:
      break;
  }
}
