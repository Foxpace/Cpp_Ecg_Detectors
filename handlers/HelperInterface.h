
#ifndef ECGDETECTORS_HELPERINTERFACE_H
#define ECGDETECTORS_HELPERINTERFACE_H

#include <vector>

class HelperInterface {

public:
    virtual double passValue(double sample) {
        return 0;
    }

    virtual void reset(){
        values.clear();
    };

protected:
    int size = 0;
    std::vector<double> values;

};


#endif //ECGDETECTORS_HELPERINTERFACE_H
