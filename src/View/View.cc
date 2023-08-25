#include "View.h"

#include <charconv>

#include "./ui_View.h"

namespace s21 {

View::View(Controller* c, std::shared_ptr<Singleton> s, QWidget* parent)
    : QOpenGLWidget(parent), controller_(c), settings_(s), ui_(new Ui::View) {
  setFixedSize(1200, 1200);
  ui_->setupUi(this);

  connect(ui_->OpenFile, SIGNAL(clicked()), this, SLOT(OpenFile()));
  connect(ui_->ResetButton, SIGNAL(clicked()), this, SLOT(Reset()));
  connect(ui_->save_image, SIGNAL(clicked()), this, SLOT(SaveImage()));
  connect(ui_->horizontalSlider, SIGNAL(valueChanged(int)), this,
          SLOT(BackColorSlider()));
  connect(ui_->horizontalSlider_2, SIGNAL(valueChanged(int)), this,
          SLOT(BackColorSlider()));
  connect(ui_->horizontalSlider_3, SIGNAL(valueChanged(int)), this,
          SLOT(BackColorSlider()));
  connect(ui_->horizontalSlider_4, SIGNAL(valueChanged(int)), this,
          SLOT(VertColorSlider()));
  connect(ui_->horizontalSlider_5, SIGNAL(valueChanged(int)), this,
          SLOT(VertColorSlider()));
  connect(ui_->horizontalSlider_6, SIGNAL(valueChanged(int)), this,
          SLOT(VertColorSlider()));
  connect(ui_->horizontalSlider_7, SIGNAL(valueChanged(int)), this,
          SLOT(LinesColorSlider()));
  connect(ui_->horizontalSlider_8, SIGNAL(valueChanged(int)), this,
          SLOT(LinesColorSlider()));
  connect(ui_->horizontalSlider_9, SIGNAL(valueChanged(int)), this,
          SLOT(LinesColorSlider()));
  connect(ui_->horizontalSlider_10, SIGNAL(valueChanged(int)), this,
          SLOT(StartDraw()));
  connect(ui_->horizontalSlider_11, SIGNAL(valueChanged(int)), this,
          SLOT(StartDraw()));
  connect(ui_->horizontalSlider_12, SIGNAL(valueChanged(int)), this,
          SLOT(StartDraw()));
  connect(ui_->horizontalSlider_13, SIGNAL(valueChanged(int)), this,
          SLOT(StartDraw()));
  connect(ui_->horizontalSlider_14, SIGNAL(valueChanged(int)), this,
          SLOT(StartDraw()));
  connect(ui_->horizontalSlider_15, SIGNAL(valueChanged(int)), this,
          SLOT(StartDraw()));

  connect(ui_->spinBox_4, SIGNAL(valueChanged(int)), this, SLOT(StartDraw()));
  connect(ui_->spinBox_5, SIGNAL(valueChanged(int)), this, SLOT(StartDraw()));
  connect(ui_->spinBox_6, SIGNAL(valueChanged(int)), this, SLOT(StartDraw()));

  connect(ui_->lines_style, SIGNAL(currentIndexChanged(int)), this,
          SLOT(StartDraw()));
  connect(ui_->vert_style, SIGNAL(currentIndexChanged(int)), this,
          SLOT(StartDraw()));
  connect(ui_->proj_type, SIGNAL(currentIndexChanged(int)), this,
          SLOT(StartDraw()));

  LoadSettings();
  Init();
}

View::~View() {
  SaveSettings();
  delete ui_;
}

void View::initializeGL() { glEnable(GL_DEPTH_TEST); }

void View::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void View::paintGL() {
  glClearColor(ui_->horizontalSlider->value() / 100.0,
               ui_->horizontalSlider_2->value() / 100.0,
               ui_->horizontalSlider_3->value() / 100.0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (ui_->proj_type->currentIndex() == 0) {
    glOrtho(-camera_ * 2, camera_ * 2, -camera_ * 2, camera_ * 2,
            -camera_ * 100, camera_ * 100);
  } else {
    gluPerspective(90.0, 1.0, 0.1, 1000000);
    glTranslated(0, 0, -camera_ * 2);
  }

  CoordXYZ rotate{ui_->horizontalSlider_13->value(),
                  ui_->horizontalSlider_14->value(),
                  ui_->horizontalSlider_15->value()};
  CoordXYZ move{ui_->horizontalSlider_10->value(),
                ui_->horizontalSlider_11->value(),
                ui_->horizontalSlider_12->value()};
  controller_->ActionFacede(rotate, move, ui_->spinBox_6->value() / 100.0);

  DrawCube();
  controller_->RefreshVert();
}

void View::StartDraw() { update(); }

void View::Init() {
  ui_->color_r->setText(
      QString::number(ui_->horizontalSlider->value() / 100.0));
  ui_->color_g->setText(
      QString::number(ui_->horizontalSlider_2->value() / 100.0));
  ui_->color_b->setText(
      QString::number(ui_->horizontalSlider_3->value() / 100.0));
  ui_->color_r_3->setText(
      QString::number(ui_->horizontalSlider_7->value() / 100.0));
  ui_->color_g_3->setText(
      QString::number(ui_->horizontalSlider_8->value() / 100.0));
  ui_->color_b_3->setText(
      QString::number(ui_->horizontalSlider_9->value() / 100.0));
  ui_->color_r_2->setText(
      QString::number(ui_->horizontalSlider_4->value() / 100.0));
  ui_->color_g_2->setText(
      QString::number(ui_->horizontalSlider_5->value() / 100.0));
  ui_->color_b_2->setText(
      QString::number(ui_->horizontalSlider_6->value() / 100.0));
}

void View::DrawCube() {
  glVertexPointer(3, GL_DOUBLE, 0, controller_->GetMovedVert());
  glEnableClientState(GL_VERTEX_ARRAY);
  glColor3d(ui_->horizontalSlider_4->value() / 100.0,
            ui_->horizontalSlider_5->value() / 100.0,
            ui_->horizontalSlider_6->value() / 100.0);
  glPointSize(ui_->spinBox_5->value());
  if (ui_->vert_style->currentIndex() == 0) {
    ui_->label_9->show();
    ui_->spinBox_5->show();
    glDrawArrays(GL_POINTS, 0, controller_->GetVertSize());
  } else if (ui_->vert_style->currentIndex() == 1) {
    ui_->label_9->show();
    ui_->spinBox_5->show();
    glEnable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, controller_->GetVertSize());
    glDisable(GL_POINT_SMOOTH);
  } else {
    ui_->label_9->hide();
    ui_->spinBox_5->hide();
  }
  glColor3d(ui_->horizontalSlider_7->value() / 100.0,
            ui_->horizontalSlider_8->value() / 100.0,
            ui_->horizontalSlider_9->value() / 100.0);
  glLineWidth(ui_->spinBox_4->value());
  if (ui_->lines_style->currentIndex() == 1) {
    glLineStipple(1, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
    glDrawElements(GL_LINES, controller_->GetPolySize(), GL_UNSIGNED_INT,
                   controller_->GetPoly());
    glDisable(GL_LINE_STIPPLE);
  } else {
    glDrawElements(GL_LINES, controller_->GetPolySize(), GL_UNSIGNED_INT,
                   controller_->GetPoly());
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

void View::OpenFile() {
  QString filter = " OBJ Files (*.obj)";
  QString file_name = QFileDialog::getOpenFileName(this, "Open OBJ file",
                                                   QDir::homePath(), filter);
  if (!file_name.isEmpty() && !file_name.isNull()) {
    QString name = file_name.mid(file_name.lastIndexOf('/') + 1);
    if (controller_->Parse(file_name.toStdString())) {
      camera_ = controller_->GetCamera();
      ui_->name->setText(name);
      ui_->vertices->setText(QString::number(controller_->GetVertSize()));
      ui_->edges->setText(QString::number(controller_->GetPolySize() / 2));
      ui_->path->setText(file_name);
    } else {
      ui_->name->setText("");
      ui_->vertices->setText("");
      ui_->edges->setText("");
      ui_->path->setText("");
      QMessageBox messageBox;
      messageBox.critical(0, "Error", "Error with obj file!");
      messageBox.setFixedSize(500, 200);
    }
  }
}

// mouse movement
void View::mousePressEvent(QMouseEvent* mo) {
  mouse_position_ = mo->pos();
  x_start_ = ui_->horizontalSlider_13->value();
  y_start_ = ui_->horizontalSlider_14->value();
}

void View::mouseMoveEvent(QMouseEvent* mo) {
  ui_->horizontalSlider_13->setValue(
      x_start_ + 0.2 * (mo->pos().y() - mouse_position_.y()));
  ui_->horizontalSlider_14->setValue(
      y_start_ + 0.2 * (mo->pos().x() - mouse_position_.x()));
  update();
}

void View::Reset() {
  ui_->horizontalSlider_10->setValue(0);
  ui_->horizontalSlider_11->setValue(0);
  ui_->horizontalSlider_12->setValue(0);
  ui_->horizontalSlider_13->setValue(0);
  ui_->horizontalSlider_14->setValue(0);
  ui_->horizontalSlider_15->setValue(0);
  ui_->spinBox_6->setValue(100);
  ui_->horizontalSlider->setValue(0);
  ui_->horizontalSlider_2->setValue(0);
  ui_->horizontalSlider_3->setValue(0);
  ui_->lines_style->setCurrentIndex(0);
  ui_->spinBox_4->setValue(1);
  ui_->horizontalSlider_7->setValue(100);
  ui_->horizontalSlider_8->setValue(0);
  ui_->horizontalSlider_9->setValue(0);
  ui_->vert_style->setCurrentIndex(0);
  ui_->spinBox_5->setValue(2);
  ui_->horizontalSlider_4->setValue(0);
  ui_->horizontalSlider_5->setValue(0);
  ui_->horizontalSlider_6->setValue(100);
  update();
}

void View::BackColorSlider() {
  ui_->color_r->setText(
      QString::number(ui_->horizontalSlider->value() / 100.0));
  ui_->color_g->setText(
      QString::number(ui_->horizontalSlider_2->value() / 100.0));
  ui_->color_b->setText(
      QString::number(ui_->horizontalSlider_3->value() / 100.0));
  update();
}

void View::VertColorSlider() {
  ui_->color_r_2->setText(
      QString::number(ui_->horizontalSlider_4->value() / 100.0));
  ui_->color_g_2->setText(
      QString::number(ui_->horizontalSlider_5->value() / 100.0));
  ui_->color_b_2->setText(
      QString::number(ui_->horizontalSlider_6->value() / 100.0));
  update();
}

void View::LinesColorSlider() {
  ui_->color_r_3->setText(
      QString::number(ui_->horizontalSlider_7->value() / 100.0));
  ui_->color_g_3->setText(
      QString::number(ui_->horizontalSlider_8->value() / 100.0));
  ui_->color_b_3->setText(
      QString::number(ui_->horizontalSlider_9->value() / 100.0));
  update();
}

void View::SaveImage() {
  QString str = QFileDialog::getSaveFileName(this, NULL, NULL,
                                             "BMP (*.bmp) ;; JPEG (*.jpeg)");
  if (!str.isEmpty()) {
    this->grabFramebuffer().save(str);
  }
}

void View::SaveSettings() {
  settings_->GetSet()->setValue("scale", ui_->spinBox_6->value());
  settings_->GetSet()->setValue("rotate_x", ui_->horizontalSlider_13->value());
  settings_->GetSet()->setValue("rotate_y", ui_->horizontalSlider_14->value());
  settings_->GetSet()->setValue("rotate_z", ui_->horizontalSlider_15->value());
  settings_->GetSet()->setValue("move_x", ui_->horizontalSlider_10->value());
  settings_->GetSet()->setValue("move_y", ui_->horizontalSlider_11->value());
  settings_->GetSet()->setValue("move_z", ui_->horizontalSlider_12->value());
  settings_->GetSet()->setValue("background_r", ui_->horizontalSlider->value());
  settings_->GetSet()->setValue("background_g",
                                ui_->horizontalSlider_2->value());
  settings_->GetSet()->setValue("background_b",
                                ui_->horizontalSlider_3->value());
  settings_->GetSet()->setValue("lines_style",
                                ui_->lines_style->currentIndex());
  settings_->GetSet()->setValue("lines_thick", ui_->spinBox_4->value());
  settings_->GetSet()->setValue("lines_r", ui_->horizontalSlider_7->value());
  settings_->GetSet()->setValue("lines_g", ui_->horizontalSlider_8->value());
  settings_->GetSet()->setValue("lines_b", ui_->horizontalSlider_9->value());
  settings_->GetSet()->setValue("vertices_style",
                                ui_->vert_style->currentIndex());
  settings_->GetSet()->setValue("vertices_size", ui_->spinBox_5->value());
  settings_->GetSet()->setValue("vertices_r", ui_->horizontalSlider_4->value());
  settings_->GetSet()->setValue("vertices_g", ui_->horizontalSlider_5->value());
  settings_->GetSet()->setValue("vertices_b", ui_->horizontalSlider_6->value());
  settings_->Save();
}

void View::LoadSettings() {
  settings_->Load();
  ui_->spinBox_6->setValue(settings_->GetSet()->value("scale", "100").toInt());
  ui_->horizontalSlider_13->setValue(
      settings_->GetSet()->value("rotate_x", "0").toInt());
  ui_->horizontalSlider_14->setValue(
      settings_->GetSet()->value("rotate_y", "0").toInt());
  ui_->horizontalSlider_15->setValue(
      settings_->GetSet()->value("rotate_z", "0").toInt());
  ui_->horizontalSlider_10->setValue(
      settings_->GetSet()->value("move_x", "0").toInt());
  ui_->horizontalSlider_11->setValue(
      settings_->GetSet()->value("move_y", "0").toInt());
  ui_->horizontalSlider_12->setValue(
      settings_->GetSet()->value("move_z", "0").toInt());
  ui_->horizontalSlider->setValue(
      settings_->GetSet()->value("background_r", "0").toInt());
  ui_->horizontalSlider_2->setValue(
      settings_->GetSet()->value("background_g", "0").toInt());
  ui_->horizontalSlider_3->setValue(
      settings_->GetSet()->value("background_b", "0").toInt());
  ui_->lines_style->setCurrentIndex(
      settings_->GetSet()->value("lines_style", "0").toInt());
  ui_->spinBox_4->setValue(
      settings_->GetSet()->value("lines_thick", "1").toInt());
  ui_->horizontalSlider_7->setValue(
      settings_->GetSet()->value("lines_r", "100").toInt());
  ui_->horizontalSlider_8->setValue(
      settings_->GetSet()->value("lines_g", "0").toInt());
  ui_->horizontalSlider_9->setValue(
      settings_->GetSet()->value("lines_b", "0").toInt());
  ui_->vert_style->setCurrentIndex(
      settings_->GetSet()->value("vertices_style", "0").toInt());
  ui_->spinBox_5->setValue(
      settings_->GetSet()->value("vertices_size", "2").toInt());
  ui_->horizontalSlider_4->setValue(
      settings_->GetSet()->value("vertices_r", "0").toInt());
  ui_->horizontalSlider_5->setValue(
      settings_->GetSet()->value("vertices_g", "0").toInt());
  ui_->horizontalSlider_6->setValue(
      settings_->GetSet()->value("vertices_b", "100").toInt());
}

}  // namespace s21
