
#include "Convolution.h"

double Convolution::passValue(double sample) {

    values.push_back(sample);
    if(values.size() == kernel->size()){
        double result = convolve();
        values.erase(values.begin());
        return result;
    }

    return NAN;
}

double Convolution::convolve() {

    std::vector<double> result(values.size() + kernel->size() - 1, 0);
    for (int n = 0; n < values.size() + kernel->size() - 1; n++){

        size_t kmin, kmax, k;
        result[n] = 0;

        kmin = (n >= kernel->size() - 1) ? n - (kernel->size() - 1) : 0;
        kmax = (n < values.size() - 1) ? n : values.size()- 1;

        for (k = kmin; k <= kmax; k++){
            result[n] += values[k] * kernel->at(n-k);
        }
    }
    return result[kernel->size()-1];
}
