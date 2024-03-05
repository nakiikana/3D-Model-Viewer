#ifndef CPP4_3DVIEWER_V2_0_SRC_CONTROLLER_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_0_SRC_CONTROLLER_CONTROLLER_H_

#include "../model/parser.h"

namespace s21 {

class controller {
    public:
        controller(ObjParser *m) : model_(m){};

        void parse(std::string path_to_file);
        std::vector<double> getVertexes();
        std::vector<unsigned int> getPolygons();

    private:
        ObjParser *model_;
};
}      // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_SRC_CONTROLLER_CONTROLLER_H_
