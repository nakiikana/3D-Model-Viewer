#include "controller.h"

namespace s21 {

    void controller::parse(std::string path_to_file) {
        model_->modelDemolisher();
        model_->parserVertex(path_to_file);
    }

    std::vector<double> controller::getVertexes() {
        return model_->getVertex();
    }

    std::vector<unsigned int> controller::getPolygons() {
        return model_->getSegments();
    }

};  // namespace s21