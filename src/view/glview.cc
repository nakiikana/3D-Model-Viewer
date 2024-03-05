#include "glview.h"

glView::glView(QWidget* parent) : QOpenGLWidget(parent), m_arrayBuffer(QOpenGLBuffer::VertexBuffer), m_indexBuffer(QOpenGLBuffer::IndexBuffer) { //в конструкторе для индексного буфера необходимо указать, что он индексный: array_buffer по умолчанию
  // QString path = QDir::home().absolutePath() + "/Desktop/config.txt";
  // get_config(&set, path.toStdString().c_str());
  // colorBack.setRgbF(set.background_color[0], set.background_color[1],
  //                   set.background_color[2], set.background_color[3]);
  // colorDot.setRgbF(set.vertex_color[0], set.vertex_color[1],
  //                  set.vertex_color[2]);
  // colorLine.setRgbF(set.rib_color[0], set.rib_color[1], set.rib_color[2]);
  // lineType = set.rib_type;
  // dotType = set.vertex_type;
  // lineSize = set.rib_thickness;
  // dotSize = set.vertex_size;
  // proection = set.projection_type;
}

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 qt_ModelViewProjectionMatrix;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = qt_ModelViewProjectionMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

const char *geometryShaderSource = "#version 330 core\n"
    "layout (lines) in;\n"
     "layout (triangle_strip, max_vertices = 4) out;\n"
    "void main()\n"
    "{\n"
    "vec2 dir_vec = normalize(gl_in[1].gl_Position.xy - gl_in[0].gl_Position.xy);\n"
    "vec2 normal = vec2(-dir_vec.y, dir_vec.x) * 0.04;\n"
    "gl_Position = gl_in[0].gl_Position + vec4(normal, 0.0, 0.0);\n"
    "EmitVertex();\n"
    "gl_Position = gl_in[0].gl_Position - vec4(normal, 0.0, 0.0);\n"
    "EmitVertex();\n"
    "gl_Position = gl_in[1].gl_Position + vec4(normal, 0.0, 0.0);\n"
    "EmitVertex();\n"
    "gl_Position = gl_in[1].gl_Position - vec4(normal, 0.0, 0.0);\n"
    "EmitVertex();\n"
    "EndPrimitive();\n"
    "}\0";



void glView::initializeGL() {

    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); //включает отсечение задней грани
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //подаем флаги? которые отвечает за очистку
    initShaders(); //загрузка кода шейдеров и компиляция
}

void glView::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    float aspect = w / (float) h;
    projection_m.setToIdentity(); //единичная матрица
    projection_m.perspective(45, aspect, 0.1f, 10.0f); //последние два параметра - передняя и дальняя плоскости отсечения
}

void glView::paintGL() {
//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
  QMatrix4x4 modelViewMatrix;
  modelViewMatrix.setToIdentity();
  modelViewMatrix.translate(0.0, 0.0, -3.0); //отодвигаем камеру назад
  glClearColor(colorBack.redF(), colorBack.greenF(), colorBack.blueF(),
               colorBack.alphaF()); // not working
  modelViewMatrix.rotate(m_rotation);

  m_program.bind();
  m_program.setUniformValue("qt_ModelViewProjectionMatrix", projection_m * modelViewMatrix);
  m_vao.bind();
  m_arrayBuffer.bind();
  m_program.setAttributeBuffer("aPos", GL_FLOAT, 0, 3);
  std::cout << glGetError() << std::endl;
  m_program.enableAttributeArray("aPos");
  std::cout << glGetError() << std::endl;
  m_indexBuffer.bind();
  std::cout << glGetError() << std::endl;
  glDrawElements(GL_LINES, 30, GL_UNSIGNED_INT, 0);
  std::cout << glGetError() << std::endl;



//  glMatrixMode(GL_MODELVIEW);
//  glLoadIdentity();
//  glVertexPointer(3, GL_DOUBLE, 0, pointsGL.v);
//  glEnableClientState(GL_VERTEX_ARRAY);
//  if (openFileFl) {
//    if (proection == 0) {
//      glOrtho(-(1), 1, -(1), 1, 1, 5);
//      glTranslatef(0, 0, -2);
//    } else {
//      glFrustum(-(2), 2, -(2), 2, 1, 5);
//      glTranslatef(0, 0, -3);
//    }
//    // rotate_model_x(&pointsGL, xRot);
//    // rotate_model_y(&pointsGL, yRot);
//    // rotate_model_z(&pointsGL, zRot);
//    // move_model(&pointsGL, xMove, -yMove, zMove);
//    // scale_model(&pointsGL, scale);
//    zeroing();
//    glPointSize(dotSize);
//    glColor3f(colorDot.redF(), colorDot.greenF(), colorDot.blueF());
//    if (dotType == 0) {
//      glEnable(GL_POINT_SMOOTH);
//      glDrawArrays(GL_POINTS, 0, pointsGL.amountV / 3);
//      glDisable(GL_POINT_SMOOTH);
//    } else if (dotType == 1) {
//      glDrawArrays(GL_POINTS, 0, pointsGL.amountV / 3);
//    }
//    glColor3f(colorLine.redF(), colorLine.greenF(), colorLine.blueF());
//    glLineWidth(lineSize);
//    if (lineType == 0) {
//      glDisable(GL_LINE_STIPPLE);
//      glDrawElements(GL_LINES, (modelGL.amountF), GL_UNSIGNED_INT, modelGL.f);
//    } else if (lineType == 1) {
//      glEnable(GL_LINE_STIPPLE);
//      glLineStipple(1, 0x00F0);
//      glDrawElements(GL_LINES, (modelGL.amountF), GL_UNSIGNED_INT, modelGL.f);
//    }
//    glDisable(GL_LINE_STIPPLE);
//  }
//  glDisableClientState(GL_VERTEX_ARRAY);
}

void glView::mousePressEvent(QMouseEvent* event) {
//  mPos = event->pos();
//  if (event->button() == Qt::LeftButton) {
//    bMoveL = true;
//  } else if (event->button() == Qt::RightButton) {
//    bMoveR = true;
//  }
}

void glView::mouseMoveEvent(QMouseEvent* event) {
//  if (event->buttons() & Qt::LeftButton) {
//    xRot = .01 * (event->pos().y() - mPos.y());
//    yRot = .01 * (event->pos().x() - mPos.x());
//  }
//  if (event->buttons() & Qt::RightButton) {
//    xMove = .005 * (event->pos().x() - mPos.x());
//    yMove = .005 * (event->pos().y() - mPos.y());
//  }
//  mPos = event->pos();
//  update();
}

void glView::scrollBar(int valueButton, QString check) {
//  if (check == "radioButtonRotationX") {
//    xRot = .0635 * (valueButton - valueButtonTmp);
//    valueButtonTmp = valueButton;
//    qDebug() << "x" << xRot;
//  } else if (check == "radioButtonRotationY") {
//    yRot = .0635 * (valueButton - valueButtonTmp);
//    valueButtonTmp = valueButton;
//    qDebug() << "y" << yRot;
//  } else if (check == "radioButtonRotationZ") {
//    zRot = .0635 * (valueButton - valueButtonTmp);
//    valueButtonTmp = valueButton;
//    qDebug() << "z" << zRot;
//  } else if (check == "radioButtonMoveX") {
//    moveValueButton = valueButton / 50.0;
//    xMove = 3.5 * (moveValueButton - moveValueButtonTmp);
//    moveValueButtonTmp = moveValueButton;
//  } else if (check == "radioButtonMoveY") {
//    moveValueButton = valueButton / 50.0;
//    yMove = 3.5 * (moveValueButton - moveValueButtonTmp);
//    moveValueButtonTmp = moveValueButton;
//  } else if (check == "radioButtonMoveZ") {
//    moveValueButton = valueButton / 50.0;
//    zMove = 3.5 * (moveValueButton - moveValueButtonTmp);
//    moveValueButtonTmp = moveValueButton;
//  } else if (check == "radioButtonZoomeModel") {
//    moveValueButton = valueButton;
//    scale = (moveValueButton - moveValueButtonTmp) * 0.02;
//    moveValueButtonTmp = moveValueButton;
//  }
//  update();
}

void glView::wheelEvent(QWheelEvent* event) {
//  QPoint circle = event->pixelDelta();
//  if ((event->buttons() & Qt::LeftButton) && bMoveL) {
//    zRot = ((double)circle.y() * .01);
//  } else if ((event->buttons() & Qt::RightButton) && bMoveR) {
//    zMove = ((double)circle.y() * .005);
//  } else if (!bMoveL && !bMoveR) {
//    scale = ((double)circle.y() * .01);
//  }
//  update();
}

void glView::mouseReleaseEvent(QMouseEvent* event) {
//  if (event->button() == Qt::LeftButton && bMoveL) {
//    bMoveL = false;
//  }
//  if (event->button() == Qt::RightButton && bMoveR) {
//    bMoveR = false;
//  }
}

void glView::initShaders()
{
    m_program.create();
    m_program.bind();
    if (!m_program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource))
        close();
    if (!m_program.addShaderFromSourceCode(QOpenGLShader::Geometry, geometryShaderSource))
        close();
    if (!m_program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource))
        close();
    if (!m_program.link())
        close();
}


void glView::initDraw() {
//    m_vao.create();
//    m_vao.bind();
//    m_arrayBuffer.create();
//    m_arrayBuffer.bind(); //размещение памяти
//    m_arrayBuffer.allocate(vertices.constData(), vertices.size()*sizeof(float)); //выделение памяти и газрузка укзанных данных
//    m_arrayBuffer.release();

//    m_indexBuffer.create();
//    m_indexBuffer.bind(); //размещение памяти
//    m_indexBuffer.allocate(indeces.constData(), indeces.size()*sizeof(float)); //выделение памяти и газрузка укзанных данных
//    m_indexBuffer.release();
}


void glView::zeroing() {
//  xMove = 0;
//  yMove = 0;
//  zMove = 0;
//  yRot = 0;
//  xRot = 0;
//  zRot = 0;
//  scale = 0;
}



void glView::translate(std::vector <double> p, std::vector <unsigned int> m) {
//  pointsGL = p;
//  modelGL = m;
//  openFileFl = 1;
//  update();
}

//void glView::IndexChanged(int proectionin) {
////  proection = proectionin;
////  paintGL();
////  update();
//}

//void glView::DotTypeChanged(int index) {
////  dotType = index;
////  paintGL();
////  update();
//}

//void glView::LineTypeChanged(int index) {
////  lineType = index;
////  qDebug() << "2" << lineType;
////  paintGL();
////  update();
//}

void glView::freeModel() { /*free_all_struct(&pointsGL, &modelGL); */}

//void glView::setColorDot(QColor color) {/* colorDot = color;*/ }

//void glView::setColorLine(QColor color) { /*colorLine = color; */}

//void glView::setColorBack(QColor color) { /*colorBack = color; */ }

//QColor glView::getColorDot() { return /*this->colorDot; */}
//QColor glView::getColorLine() { return /*this->colorLine;*/ }
//QColor glView::getColorBack() { return /*this->colorBack;*/ }

//void glView::setOptions(s21::Settings options) {
//  options.back_color = colorBack;
//  options.vertex_color = colorDot;
//  options.line_color = colorLine;
//  options.projection_orth = proection;
//  options.line_width = lineSize / 0.3;
//  options.vertex_size = dotSize / 0.5;
//  options.vertex_type = dotType;
//  options.line_type = lineType;
//  options.SaveSettings();
//}
