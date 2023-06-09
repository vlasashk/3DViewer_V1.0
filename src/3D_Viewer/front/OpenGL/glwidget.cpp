#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

GLWidget::~GLWidget() {
  if (ObjDraw != nullptr) {
    free_obj3d(&ObjDraw);
  }
  if (polygonIndices != nullptr) {
    free(polygonIndices);
    polygonIndices = nullptr;
  }
}

void GLWidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void GLWidget::resizeGL(int w, int h) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);
}

void GLWidget::paintGL() {
  glClearColor(ViewerColor.redF(), ViewerColor.greenF(), ViewerColor.blueF(),
               ViewerColor.alphaF());
  glPointSize(VertexSize);
  glLineWidth(LineWidth);
  if (ObjDraw != nullptr) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    projectionStyleHandler();

    glTranslatef(0, 0, -2);

    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);

    drawObj();
  }
}

void GLWidget::drawObj() {
  glEnableClientState(GL_VERTEX_ARRAY);
  vertexStyleHandler();
  lineStyleHandler();
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GLWidget::readObjFile(QString fileName) {
  QByteArray inputBytes = fileName.toUtf8();
  char *convertedFileName = strdup(inputBytes.constData());

  FILE *file_3d = NULL;
  if (!open_obj_file(convertedFileName, &file_3d)) {
    if (ObjDraw != nullptr) {
      free_obj3d(&ObjDraw);
    }
    if (polygonIndices != nullptr) {
      free(polygonIndices);
      polygonIndices = nullptr;
    }
    ObjDraw = (obj3d *)calloc(1, sizeof(obj3d));
    if (read_obj(file_3d, ObjDraw)) {
      QMessageBox::information(nullptr, "File .obj parsing error",
                               "Application failed to parse chosen file.");
    } else {
      totalVertex = ObjDraw->vtx_count;
      totalPolygons = ObjDraw->fct_count;
      reshapePolygonIndices();
      initialRescaleObj(scaleFactor, ObjDraw);
    }
  } else {
    QMessageBox::information(nullptr, "File open error",
                             "Application failed to open chosen file. Check if "
                             "file's path and extension are correct");
  }
  free(convertedFileName);
  if (file_3d) {
    fclose(file_3d);
  }
}

void GLWidget::reshapePolygonIndices() {
  if (polygonIndices != nullptr) {
    free(polygonIndices);
    polygonIndices = nullptr;
  }
  unsigned int polygonAmount = ObjDraw->fct_count;
  totalIndices =
      ObjDraw->total_indices * 2 /*depends on the shape of a single polygon*/;

  polygonIndices = (unsigned int *)calloc(totalIndices, sizeof(unsigned int));

  for (size_t i = 0, k = 0; i < polygonAmount; i++) {
    for (size_t j = 0, l = 0; j < ObjDraw->fct_vtx[i]; j++, l += 2) {
      polygonIndices[(k + l)] = ObjDraw->polygons[i].vertexes[j] - 1;
      if (j + 1 == ObjDraw->fct_vtx[i]) {
        polygonIndices[(k + l) + 1] = ObjDraw->polygons[i].vertexes[0] - 1;
      } else {
        polygonIndices[(k + l) + 1] = ObjDraw->polygons[i].vertexes[j + 1] - 1;
      }
    }
    k += ObjDraw->fct_vtx[i] * 2;
  }
}
