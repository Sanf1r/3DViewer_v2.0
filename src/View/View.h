#ifndef VIEW_H
#define VIEW_H

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>
#include <QTimer>
#include <QWidget>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "../Controller/Controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

class Singleton {
 public:
  static std::shared_ptr<Singleton> Instance() {
    static std::shared_ptr<Singleton> instance(new Singleton);
    return instance;
  }
  void Load() { set_ = new QSettings("./settings.ini", QSettings::IniFormat); }
  void Save() { set_->sync(); }

  QSettings *GetSet() { return set_; }

 private:
  QSettings *set_ = nullptr;
  Singleton(){};
  Singleton(const Singleton &old) = delete;
  const Singleton &operator=(const Singleton &old) = delete;
};

class View : public QOpenGLWidget {
  Q_OBJECT

 public:
  View(Controller *c, std::shared_ptr<Singleton> settings_,
       QWidget *parent = nullptr);
  ~View();

 private:
  QPoint mouse_position_;
  double y_start_, x_start_, camera_;
  Controller *controller_;
  std::shared_ptr<Singleton> settings_;
  Ui::View *ui_;

  void DrawCube();
  void Rotate();
  void Scale();
  void Move();
  void SaveSettings();
  void LoadSettings();

  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private slots:
  void OpenFile();
  void BackColorSlider();
  void VertColorSlider();
  void LinesColorSlider();
  void Reset();
  void SaveImage();
  void StartDraw();
  void Init();
};

}  // namespace s21

#endif  // VIEW_H
