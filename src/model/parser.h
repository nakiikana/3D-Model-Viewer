#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_H_
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_H_

// #include <ctype.h>
// #include <float.h>
// #include <math.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cfloat>
#include <iostream>

#define START_VALUE_SCALE 0.50 /**< The starting value for scaling. */

namespace s21 {
/**
 * @struct vertex
 * @brief Represents a vertex with its properties.
 */
typedef struct vertex_scope {
  double minZ; /**< Minimum Z-coordinate value. */
  double maxZ; /**< Maximum Z-coordinate value. */
  double minY; /**< Minimum Y-coordinate value. */
  double maxY; /**< Maximum Y-coordinate value. */
  double minX; /**< Minimum X-coordinate value. */
  double maxX; /**< Maximum X-coordinate value. */
} vertex_scope;

/**
 * @struct config
 * @brief Represents configuration settings for visualization.
 */
typedef struct config {
  int projection_type;       /**< The type of projection for visualization. */
  int rib_type;              /**< The type of rib for visualization. */
  float rib_color[3];        /**< The color of ribs in RGB format. */
  float rib_thickness;       /**< The thickness of ribs. */
  int vertex_type;           /**< The type of vertex for visualization. */
  float vertex_color[3];     /**< The color of vertices in RGB format. */
  float vertex_size;         /**< The size of vertices. */
  float background_color[4]; /**< The background color in RGBA format. */
} config;

class ObjParser {
  public:

    ObjParser(){};
    ~ObjParser(){};

    void parserVertex(std::string path);
    std::vector<double> getVertex();
    std::vector<unsigned int> getSegments();
    void modelDemolisher();

  private:
    int takeO_(std::string line);
    void duplicateFunction_(size_t *i, std::vector<unsigned int> *victor, double num);
    void findingMinMax_(double x, double y, double z);
    void centering_();
    double calculateScale_();
    void setScale_(double scale);
    void initMinMaxValue_();

    std::vector<double> vertex_;
    std::vector<unsigned int> object_;
    vertex_scope scope_;

};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_H_