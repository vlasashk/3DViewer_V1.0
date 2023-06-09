#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("3D Viewer");
  glWidget = new GLWidget();
  ui->horizontalLayout->insertWidget(0, glWidget);
#ifdef Q_OS_MAC
  settings = new QSettings("grenoullelogique.fr", "Squash", this);
#else
  settings = new QSettings("Grenoulle Logique", "Squash", this);
#endif

  connect(this, &MainWindow::emitReadObjFile, glWidget, &GLWidget::readObjFile);
  connect(this, &MainWindow::emitRotateObjX, glWidget, &GLWidget::rotateObjX);
  connect(this, &MainWindow::emitRotateObjY, glWidget, &GLWidget::rotateObjY);
  connect(this, &MainWindow::emitRotateObjZ, glWidget, &GLWidget::rotateObjZ);
  connect(this, &MainWindow::emitZoomObj, glWidget, &GLWidget::zoomObj);
  connect(this, &MainWindow::emitMoveObjX, glWidget, &GLWidget::moveObjX);
  connect(this, &MainWindow::emitMoveObjY, glWidget, &GLWidget::moveObjY);
  connect(this, &MainWindow::emitMoveObjZ, glWidget, &GLWidget::moveObjZ);
  connect(this, &MainWindow::emitWidgetColorChange, glWidget,
          &GLWidget::widgetColorChange);
  connect(this, &MainWindow::emitLineColorChange, glWidget,
          &GLWidget::lineColorChange);
  connect(this, &MainWindow::emitVertexColorChange, glWidget,
          &GLWidget::vertexColorChange);
  connect(this, &MainWindow::emitVertexTypeChange, glWidget,
          &GLWidget::vertexTypeChange);
  connect(this, &MainWindow::emitLineTypeChange, glWidget,
          &GLWidget::lineTypeChange);
  connect(this, &MainWindow::emitProjectionChange, glWidget,
          &GLWidget::projectionChange);
  connect(this, &MainWindow::emitLineWidthChange, glWidget,
          &GLWidget::lineWidthChange);
  connect(this, &MainWindow::emitVertexSizeChange, glWidget,
          &GLWidget::vertexSizeChange);
  downloadSettings();
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
  delete glWidget;
}

void MainWindow::on_pushButton_openFile_clicked() {
  QDir::setCurrent(QCoreApplication::applicationDirPath());
  QDir dir(QDir::currentPath());
  dir.cdUp();
  dir.cdUp();
  dir.cdUp();
  dir.cdUp();
  dir.cd("data-samples");
  QString dataSamplesDir = dir.absolutePath();
  QString filePath = QFileDialog::getOpenFileName(
      this, "Choose file", dataSamplesDir, ".obj (*.obj)");
  if (filePath.isEmpty()) {
    QMessageBox::information(
        nullptr, "File error",
        "The file has not been selected or the file is not an .obj");
  } else {
    initTransformSettings();
    emit emitReadObjFile(filePath);
    displayObjInfo(filePath);
  }
}

void MainWindow::displayObjInfo(QString filePath) {
  QFileInfo fi(filePath);
  QString name = fi.fileName();
  ui->label_name->setText(name);
  adjustFont(ui->label_name);
  ui->label_vertex->setText(QString::number(glWidget->totalVertex, 10));
  adjustFont(ui->label_vertex);
  ui->label_polygons->setText(QString::number(glWidget->totalPolygons, 10));
  adjustFont(ui->label_polygons);
}

void MainWindow::adjustFont(QLabel* label) {
  QFont font = label->font();
  font.setPointSize(13);
  label->setFont(font);
  QFontMetrics fontMetrics(font);
  int textWidth = fontMetrics.horizontalAdvance(label->text());
  int labelWidth = label->width();

  if (textWidth > labelWidth - 5) {
    int fontSize = font.pointSize();
    while (textWidth > labelWidth - 5 && fontSize > 7) {
      fontSize--;
      font.setPointSize(fontSize);
      fontMetrics = QFontMetrics(font);
      textWidth = fontMetrics.horizontalAdvance(label->text());
    }
    label->setFont(font);
  }
}

void MainWindow::on_pushButton_screenshot_clicked() {
  QImage img = glWidget->grabFramebuffer();
  QString screenshot = QFileDialog::getSaveFileName(
      this, tr("Save File"), QDir::homePath(), tr("Images (*.jpeg *.bmp)"));
  if (!screenshot.isNull()) {
    img.save(screenshot);
  }
}
