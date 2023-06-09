#include "glwidget.h"

/*---------------------Mouse manipulation---------------------*/
void GLWidget::mousePressEvent(QMouseEvent *event) {
  mPos = event->position();
  mLastRotX = xRot;
  mLastRotY = yRot;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
  yRot = mLastRotY + event->position().x() - mPos.x();
  xRot = mLastRotX + event->position().y() - mPos.y();

  update();
}
void GLWidget::mouseReleaseEvent(QMouseEvent *event) {
  mLastRotX = xRot;
  mLastRotY = yRot;
  mPos = event->position();
}

void GLWidget::wheelEvent(QWheelEvent *event) {
  QPoint numPixels = event->pixelDelta();
  QPoint numDegrees = event->angleDelta() / 8;
  int numSteps = 0;
  if (!numPixels.isNull()) {
    numSteps = numPixels.y();
  } else if (!numDegrees.isNull()) {
    numSteps = numDegrees.y() / 15;
  }
  double zoomFactor = 1.0 + numSteps * 0.001f;
  if (zoomFactor < 0.1f) {
    zoomFactor = 0.1f;
  }
  rescaleObj(zoomFactor, ObjDraw);
  update();
}

/*---------------------Rotation via buttons---------------------*/

void GLWidget::rotateObjX(double angle) {
  if (ObjDraw != nullptr) {
    rotateX(angle / 57.29578, ObjDraw);
    update();
  }
}

void GLWidget::rotateObjY(double angle) {
  if (ObjDraw != nullptr) {
    rotateY(angle / 57.29578, ObjDraw);
    update();
  }
}

void GLWidget::rotateObjZ(double angle) {
  if (ObjDraw != nullptr) {
    rotateZ(angle / 57.29578, ObjDraw);
    update();
  }
}

/*---------------------Zoom via buttons---------------------*/
void GLWidget::zoomObj(double scale) {
  if (ObjDraw != nullptr) {
    double zoomFactor = 1.0 + scale * 0.01f;
    if (zoomFactor < 0.1f) {
      zoomFactor = 0.1f;
    }
    rescaleObj(zoomFactor, ObjDraw);
    update();
  }
}

/*---------------------Move via buttons---------------------*/
void GLWidget::moveObjX(double val) {
  if (ObjDraw != nullptr) {
    moveX(val, ObjDraw);
    update();
  }
}
void GLWidget::moveObjY(double val) {
  if (ObjDraw != nullptr) {
    moveY(val, ObjDraw);
    update();
  }
}
void GLWidget::moveObjZ(double val) {
  if (ObjDraw != nullptr) {
    moveZ(val, ObjDraw);
    update();
  }
}
