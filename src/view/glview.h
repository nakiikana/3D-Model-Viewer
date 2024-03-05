#ifndef CPP4_3DVIEWER_V2_0_SRC_CONTROLLER_GLVIEW_H
#define CPP4_3DVIEWER_V2_0_SRC_CONTROLLER_GLVIEW_H

#define GL_SILENCE_DEPRECATION // убрать ком

#include <iostream>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

#include "../controller/controller.h"
#include "../observer/observer.h"
#include "settings.h"


class glView : public QOpenGLWidget, public QOpenGLFunctions, public s21::Observer 
{
  Q_OBJECT

 public:
  glView(QWidget *parent = nullptr);

//  void IndexChanged(int);
//  void DotTypeChanged(int);
//  void LineTypeChanged(int);
  void freeModel();
//  void setColorDot(QColor);
//  void setColorLine(QColor);
//  void setColorBack(QColor);
  void scrollBar(int, QString);
//  void setConfig();
  virtual void setOptions(s21::Settings options) override {
      colorBack = options.back_color;
      colorDot = options.vertex_color;
      colorLine = options.line_color;
      proection = options.projection_orth;
      lineSize = options.line_width * 3;
      dotSize = options.vertex_size * 2 ;
      dotType = options.vertex_type;
      lineType = options.line_type;
      options.SaveSettings();
    };
  QColor getColorDot();
  QColor getColorLine();
  QColor getColorBack();
  void translate(std::vector <double> vertex, std::vector <unsigned int> object);
 private slots:

 protected:
  void initializeGL() override;
  void resizeGL(int, int) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void initShaders();
  void initDraw();

 private:
  QMatrix4x4 projection_m;
  QOpenGLShaderProgram m_program;
  QOpenGLVertexArrayObject m_vao;
  QOpenGLBuffer m_arrayBuffer; //для отрисовки нам необходимы два буфера: вершинный и пиксельный
  QOpenGLBuffer m_indexBuffer;
  QVector2D m_mousePosition;
  QQuaternion m_rotation;

  QPoint mPos;
  double xRot, yRot, zRot;
  double xMove, yMove, zMove;
  double scale;
  double moveValueButton;
  double moveValueButtonTmp = 1;

  void zeroing();
  std::vector<double> pointsGL = {0};
  std::vector<unsigned int> modelGL = {0};
  // config set = {0};
  bool proection = 0;
  int openFileFl = 0;
  int valueButtonTmp = 0;
  int lineType = 0;
  int dotType = 0;
  float lineSize = 5;
  float dotSize = 10;
  bool bMoveR;
  bool bMoveL;
  double n = -5;
  QColor colorDot;
  QColor colorLine;
  QColor colorBack;

};

#endif  // CPP4_3DVIEWER_V2_0_SRC_CONTROLLER_GLVIEW_H
