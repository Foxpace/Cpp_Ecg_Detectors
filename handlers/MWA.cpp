
#include "MWA.h"

double MWA::passValue(double sample) {
    values.push_back(sample);
    if (values.size() != size) {
        return std::accumulate(values.begin(), values.end(), 0.0) / values.size();
    }

    double result = std::accumulate(values.begin(), values.end(), 0.0) / values.size();
    values.erase(values.begin());
    return result;

}

void MWA::reset() {
    values.clear();
}
