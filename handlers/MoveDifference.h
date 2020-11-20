
#ifndef ECGDETECTORS_MOVEDIFFERENCE_H
#define ECGDETECTORS_MOVEDIFFERENCE_H


#include "HelperInterface.h"

class MoveDifference: HelperInterface {
public:
    explicit MoveDifference(int size){
        this->size = size;
    };
    double passValue(double sample) override;
    void reset() override{
        HelperInterface::reset();
    };
};


#endif //ECGDETECTORS_MOVEDIFFERENCE_H
