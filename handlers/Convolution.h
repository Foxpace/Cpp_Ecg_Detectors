
#ifndef ECGDETECTORS_CONVOLUTION_H
#define ECGDETECTORS_CONVOLUTION_H

#include <vector>
#include "HelperInterface.h"

class Convolution: HelperInterface {
public:
    Convolution(int size, std::vector<double> *kernel) {
        this->size = size;
        this->kernel = kernel;
    }

    double passValue(double sample) override;
    void reset() override{
        HelperInterface::reset();
    }
protected:
    std::vector<double> *kernel;

private:
    double convolve();
};


#endif //ECGDETECTORS_CONVOLUTION_H
