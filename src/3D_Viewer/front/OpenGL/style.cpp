#include "glwidget.h"

void GLWidget::widgetColorChange(QColor value) {
  ViewerColor = value;
  update();
}

void GLWidget::lineColorChange(QColor value) {
  LineColor = value;
  update();
}

void GLWidget::vertexColorChange(QColor value) {
  VertexColor = value;
  update();
}

void GLWidget::vertexTypeChange(int value) {
  VertexType = value;
  update();
}

void GLWidget::lineTypeChange(bool value) {
  LineSolid = value;
  update();
}

void GLWidget::projectionChange(bool value) {
  CentralProjection = value;
  update();
}

void GLWidget::lineWidthChange(double value) {
  LineWidth = value;
  update();
}

void GLWidget::vertexSizeChange(double value) {
  VertexSize = value;
  update();
}

void GLWidget::vertexStyleHandler() {
  glVertexPointer(3, GL_DOUBLE, 0, ObjDraw->vet_arr);
  switch (VertexType) {
    case 1:
      glColor3f(VertexColor.redF(), VertexColor.greenF(), VertexColor.blueF());
      glEnable(GL_POINT_SMOOTH);
      glDrawArrays(GL_POINTS, 0, ObjDraw->vtx_count);
      break;
    case 2:
      glColor3f(VertexColor.redF(), VertexColor.greenF(), VertexColor.blueF());
      glDisable(GL_POINT_SMOOTH);
      glDrawArrays(GL_POINTS, 0, ObjDraw->vtx_count);
      break;
    default:
      break;
  }
}

void GLWidget::projectionStyleHandler() {
  if (CentralProjection == true) {
    glFrustum(-1, 1, -1.0, 1.0, 1.0, 5000.0);
  } else {
    glOrtho(-1, 1, -1.0, 1.0, 1.0, 5000.0);
  }
}

void GLWidget::lineStyleHandler() {
  if (!LineSolid) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00ff);
  }

  glColor3f(LineColor.redF(), LineColor.greenF(), LineColor.blueF());
  glDrawElements(GL_LINES, totalIndices, GL_UNSIGNED_INT, polygonIndices);

  if (!LineSolid) {
    glDisable(GL_LINE_STIPPLE);
  }
}
