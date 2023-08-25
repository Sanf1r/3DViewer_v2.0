#ifndef SRC_MODEL_MODEL_H
#define SRC_MODEL_MODEL_H

#include <chrono>  // work time
#include <cmath>
#include <execution>
#include <fstream>  // for open
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <vector>

#include "./ActionFacede.h"

namespace s21 {

class Model {
 public:
  // Default constructor
  Model() = default;
  // Public method
  bool Parse(const std::string& filename);
  void RefreshVert() { moved_vert_ = orig_vert_; }

  // Public method for graph calculation

  // Public method for credit calculations
  void ActionFacede(CoordXYZ rotate_coor, CoordXYZ move_coor,
                    double scale_value);
  // Getters
  double* GetMovedVert() { return moved_vert_.data(); }
  unsigned int* GetPoly() { return poly_.data(); }
  size_t GetVertSize() { return moved_vert_.size() / 3; }
  size_t GetPolySize() { return poly_.size(); }
  double GetCamera() { return camera_o_; }

 private:
  std::vector<double> orig_vert_;
  std::vector<double> moved_vert_;
  std::vector<unsigned int> poly_;
  double camera_o_ = 0;

  // Private helpers methods

  bool ParsingObj(std::ifstream& f);
  static bool BothAreSpaces(char lhs, char rhs);
  void Normalization();

  ActionPlace action_place;
};

}  // namespace s21

#endif
