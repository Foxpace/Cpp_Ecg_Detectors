
#include "MoveDifference.h"

double MoveDifference::passValue(double sample) {
    values.push_back(sample);

    if(values.size() == this->size){
        double first = values[0];
        values.erase(values.begin());
        return sample - first;

    }
    return NAN;
}
