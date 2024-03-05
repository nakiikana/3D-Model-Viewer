#ifndef CPP4_3DVIEWER_V2_0_SRC_OBSERVER_OBSERVER_H_
#define CPP4_3DVIEWER_V2_0_SRC_OBSERVER_OBSERVER_H_

#include <iostream>
#include "view/settings.h"

namespace s21 {

class Observer
{
public:
    virtual ~Observer(){};
    virtual void setOptions(Settings options) = 0;
};

};  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_SRC_OBSERVER_OBSERVER_H_
