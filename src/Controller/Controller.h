#ifndef SRC_CONTROLLER_CONTROLLER_H
#define SRC_CONTROLLER_CONTROLLER_H

#include "../Model/Model.h"
namespace s21 {
class Controller {
 public:
  // Default constructor
  explicit Controller(Model* m) : model_(m){};
  // Public method for RPN calculation of input string
  bool Parse(const std::string& filename) { return model_->Parse(filename); }
  // Public method for graph calculation
  void ActionFacede(CoordXYZ rotate_coor, CoordXYZ move_coor,
                    double scale_value) {
    model_->ActionFacede(rotate_coor, move_coor, scale_value);
  }

  void RefreshVert() { model_->RefreshVert(); }
  // Public method for credit calculations

  // Getters
  double* GetMovedVert() { return model_->GetMovedVert(); }
  unsigned int* GetPoly() { return model_->GetPoly(); }
  size_t GetVertSize() { return model_->GetVertSize(); }
  size_t GetPolySize() { return model_->GetPolySize(); }
  double GetCamera() { return model_->GetCamera(); }

 private:
  Model* model_;
};
}  // namespace s21

#endif
