#include <QApplication>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QSurfaceFormat window_surface = QSurfaceFormat::defaultFormat();
  window_surface.setMajorVersion(3);
  window_surface.setMinorVersion(3);
  window_surface.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(window_surface);
  QApplication a(argc, argv);
  s21::ObjParser model;
  s21::controller Controller(&model);
  s21::controller *ptr = &Controller;
  MainWindow w(ptr); //s21::controller *Controller, QWidget *parent = nullptr);
  w.setFixedSize(1310, 1050);
  w.setWindowTitle("3DViewer v2");
  w.show();
  return a.exec();
}
