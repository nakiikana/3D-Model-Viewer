#include "parser.h"

namespace s21 {

void ObjParser::parserVertex(std::string path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("файл не открылся");
  }
  std::string line;
  initMinMaxValue_();
  while (std::getline(file, line)) {
    if (line[0] == 'v' && line[1] == ' ') {
      double x, y, z;
      std::istringstream iss(line);
      char v;
      iss >> v;
      if (iss >> x >> y >> z) {
        vertex_.push_back(x);
        vertex_.push_back(y);
        vertex_.push_back(z);
      } else {
        file.close();
        throw std::runtime_error("проблемма с координатами точек");
      }
      findingMinMax_(x, y, z);
    } else if (line[0] == 'f' && line[1] == ' ') {
      if (takeO_(line)) {
        file.close();
        throw std::runtime_error("проблемма с номерами точек");
      }
    }
  }
  file.close();

//for (long unsigned int j = 0; j < vertex_.size(); j++) {
//  if (!(j % 3)) std::cout << "| ";
//  std::cout << vertex_[j] << " ";
//}
//std::cout << "\n" << (vertex_.size()/3) << "\n";
//for (long unsigned int j = 0; j < object_.size(); j++) {
//  if (!(j % 2)) std::cout << "| ";
//  std::cout << object_[j] << " ";
//}
//std::cout << "\n" << (object_.size()/2) << "\n";

  if (vertex_.size() % 3) throw std::runtime_error("проблемма с координатами точек1");
  centering_();
  double scale = calculateScale_();
  setScale_(scale);
  return;
}

std::vector<double> ObjParser::getVertex() {
  return vertex_;
}

std::vector<unsigned int> ObjParser::getSegments() {
  return object_;
}

void ObjParser::modelDemolisher() {
  vertex_.clear();
  object_.clear();
}

int ObjParser::takeO_(std::string line) {
  int res = 0;
  size_t i = 0;
  std::vector<unsigned int> pol;
  std::istringstream iss(line);
  char f;
  while ((iss >> f) && !res) {
    if (std::isdigit(f) || f == '-') {
      int number;
      iss.unget();
      if (iss >> number) {
        number--;
        if (number == -1) res = 4;
        if (number >= 0) {
          res = (int)(vertex_.size() / 3) < number ? 1 : res;
          duplicateFunction_(&i, &pol, number);
        } else {
          number -= -(vertex_.size() / 3);
          if (number < 0) res = 3;
          res = (int)(vertex_.size() / 3) < number ? 1 : res;
          duplicateFunction_(&i, &pol, number);
        }
      }
    } else {
      iss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    }
  }
  if ((i != 1) && (res == 0)) {
    pol.push_back(pol[0]);
  }
  for (long unsigned int j = 0; j < pol.size(); j++) {
    object_.push_back(pol[j]);
  }
  return res;
}

void ObjParser::duplicateFunction_(size_t *i, std::vector<unsigned int> *victor, double num) {
  victor->push_back(num);
  if (*i) {
    victor->push_back(num);
    (*i)++;
  }
  (*i)++;
}

void ObjParser::findingMinMax_(double x, double y, double z) {
  scope_.minX = fmin(scope_.minX, x);
  scope_.minY = fmin(scope_.minY, y);
  scope_.minZ = fmin(scope_.minZ, z);
  scope_.maxX = fmax(scope_.maxX, x);
  scope_.maxY = fmax(scope_.maxY, y);
  scope_.maxZ = fmax(scope_.maxZ, z);
}

void ObjParser::centering_() {
  double centerX = scope_.minX + (scope_.maxX - scope_.minX) / 2;
  double centerY = scope_.minY + (scope_.maxY - scope_.minY) / 2;
  double centerZ = scope_.minZ + (scope_.maxZ - scope_.minZ) / 2;
  for (long unsigned int i = 0; i < vertex_.size(); ++i) {
    switch (i % 3) {
      case 0:
        vertex_[i] -= centerX;
        break;
      case 1:
        vertex_[i] -= centerY;
        break;
      case 2:
        vertex_[i] -= centerZ;
        break;
    }
  }
}

double ObjParser::calculateScale_() {
  double x = scope_.maxX - scope_.minX;
  double y = scope_.maxY - scope_.minY;
  double z = scope_.maxZ - scope_.minZ;
  double max = fmax(fmax(x, y), z);
  return (START_VALUE_SCALE) / max;
}

void ObjParser::setScale_(double scale) {
  for (long unsigned int i = 0; i < vertex_.size(); ++i) vertex_[i] *= scale;
}

void ObjParser::initMinMaxValue_() {
  scope_.minX = DBL_MAX;
  scope_.minY = DBL_MAX;
  scope_.minZ = DBL_MAX;
  scope_.maxX = -DBL_MAX;
  scope_.maxY = -DBL_MAX;
  scope_.maxZ = -DBL_MAX;
}

}  // namespace s21

// int main() {
//   s21::ObjParser objeckt;
//   std::string path = "./cube.obj";
//   objeckt.parserVertex(path);
//   return 0;
// }
