
#ifndef ECGDETECTORS_MWA_H
#define ECGDETECTORS_MWA_H


#include "HelperInterface.h"
#include <numeric>

class MWA: HelperInterface {
public:
    explicit MWA(int size){
        this->size = size;
    };
    double passValue(double sample) override;
    void reset() override;
};


#endif //ECGDETECTORS_MWA_H
