#ifndef SRC_3DVIEWER_FRONT_OPENGL_GLWIDGET_H_
#define SRC_3DVIEWER_FRONT_OPENGL_GLWIDGET_H_

#define GL_SILENCE_DEPRECATION

#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QTimer>
#include <QWheelEvent>
#include <QWidget>
#include <QtOpenGL>

#ifdef __cplusplus
extern "C" {
#endif
#include "../../back/s21_3dviewer.h"
#ifdef __cplusplus
}
#endif

#if defined(linux) || defined(_WIN32)
#include <GL/glut.h>
#else
#include <GLUT/GLUT.h>
#endif

class GLWidget : public QOpenGLWidget {
    Q_OBJECT

   public:
    unsigned int totalVertex = 0;
    unsigned int totalPolygons = 0;
    GLWidget(QWidget *parent = nullptr);
    ~GLWidget();

   public slots:
    void readObjFile(QString fileName);
    void rotateObjX(double angle);
    void rotateObjY(double angle);
    void rotateObjZ(double angle);

    void zoomObj(double scale);

    void moveObjX(double val);
    void moveObjY(double val);
    void moveObjZ(double val);

    void widgetColorChange(QColor value);
    void lineColorChange(QColor value);
    void vertexColorChange(QColor value);

    void vertexTypeChange(int value);
    void lineTypeChange(bool value);
    void projectionChange(bool value);

    void lineWidthChange(double value);
    void vertexSizeChange(double value);

   protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

   private:
    /*----object related----*/
    obj3d *ObjDraw = nullptr;
    unsigned int *polygonIndices = nullptr;
    unsigned int totalIndices;

    /*----mouse manipulation----*/
    float xRot, yRot, mLastRotY, mLastRotX;
    double scaleFactor = 0.6f;
    QPointF mPos;

    /*----Colors----*/
    QColor VertexColor = QColor(242, 165, 60);
    QColor LineColor = QColor(242, 165, 60);
    QColor ViewerColor = QColor(58, 57, 57, 0);

    bool LineSolid = true;
    double LineWidth = 1.0;

    int VertexType = 0;
    double VertexSize = 1.0;

    bool CentralProjection = true;

    void drawObj();
    void reshapePolygonIndices();
    void drawCube(float a);

    void vertexStyleHandler();
    void projectionStyleHandler();
    void lineStyleHandler();
};

#endif  // SRC_3DVIEWER_FRONT_OPENGL_GLWIDGET_H_
