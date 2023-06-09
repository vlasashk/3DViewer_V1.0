#ifndef SRC_3DVIEWER_FRONT_VIEWERWINDOW_MAINWINDOW_H_
#define SRC_3DVIEWER_FRONT_VIEWERWINDOW_MAINWINDOW_H_

#include <QColorDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include <QMainWindow>
#include <QSettings>

#include "../OpenGL/glwidget.h"

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

 private:
  Ui::MainWindow *ui;
  GLWidget *glWidget;
  QSettings *settings;

  double currentMoveX = 0;
  double currentMoveY = 0;
  double currentMoveZ = 0;
  int currentRotateX = 0;
  int currentRotateY = 0;
  int currentRotateZ = 0;
  int currentScale = 100;

  void displayObjInfo(QString filePath);
  void adjustFont(QLabel *label);
  void initTransformSettings();
  void saveSettings();
  void downloadSettings();
  void colorChanger(QColor color, int value);

 signals:
  void emitReadObjFile(QString fileName);
  void emitRotateObjX(int angle);
  void emitRotateObjY(int angle);
  void emitRotateObjZ(int angle);
  void emitZoomObj(int scale);
  void emitMoveObjX(double val);
  void emitMoveObjY(double val);
  void emitMoveObjZ(double val);
  void emitWidgetColorChange(QColor value);
  void emitLineColorChange(QColor value);
  void emitVertexColorChange(QColor value);
  void emitVertexTypeChange(int value);
  void emitLineTypeChange(bool value);
  void emitProjectionChange(bool value);
  void emitLineWidthChange(double value);
  void emitVertexSizeChange(double value);

 private slots:
  void on_pushButton_openFile_clicked();
  void on_horizontalSlider_rotX_valueChanged(int value);
  void on_spinBox_rotX_valueChanged(int value);
  void on_horizontalSlider_rotY_valueChanged(int value);
  void on_spinBox_rotY_valueChanged(int value);
  void on_horizontalSlider_rotZ_valueChanged(int value);
  void on_spinBox_rotZ_valueChanged(int value);

  void on_horizontalSlider_Scale_valueChanged(int value);

  void on_horizontalSlider_moveX_valueChanged(int value);
  void on_horizontalSlider_moveY_valueChanged(int value);
  void on_horizontalSlider_moveZ_valueChanged(int value);
  void on_spinBox_MoveX_valueChanged(int value);
  void on_spinBox_MoveY_valueChanged(int value);
  void on_spinBox_MoveZ_valueChanged(int value);

  void on_pushButton_widgetColor_clicked();
  void on_pushButton_lineColor_clicked();
  void on_pushButton_vertexColor_clicked();

  void on_radioButton_VertexNone_toggled(bool value);
  void on_radioButton_VertexCircle_toggled(bool value);
  void on_radioButton_VertexSquare_toggled(bool value);

  void on_radioButton_LineSolid_toggled(bool value);
  void on_radioButton_LineDashed_toggled(bool value);

  void on_radioButton_Central_toggled(bool value);
  void on_radioButton_Parallel_toggled(bool value);

  void on_horizontalSlider_LineSize_valueChanged(int value);
  void on_doubleSpinBox_LineSize_valueChanged(double value);

  void on_horizontalSlider_VertexSize_valueChanged(int value);
  void on_doubleSpinBox_VertexSize_valueChanged(double value);

  void on_pushButton_screenshot_clicked();
};
#endif  // SRC_3DVIEWER_FRONT_VIEWERWINDOW_MAINWINDOW_H_
