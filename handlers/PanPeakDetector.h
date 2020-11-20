
#ifndef ECGDETECTORS_PANPEAKDETECTOR_H
#define ECGDETECTORS_PANPEAKDETECTOR_H

#include <vector>
#include "HelperInterface.h"

class PanPeakDetector: HelperInterface {
public:
    explicit PanPeakDetector(double fs){
        this->fs = fs;
        signalPeaks.push_back(0);
    };
    double passValue(double sample) override;
    void reset() override;

protected:
    double fs = 0.0;
    double minDistance = (0.25 * fs);

    std::vector<int> signalPeaks, noisePeaks;

    double SPKI = 0.0, NPKI = 0.0;
    double thresholdI1 = 0.0, thresholdI2 = 0.0;
    int RRMissed = 0;

    int index = 0;
    std::vector<int> indexes, missedPeaks, peaks;

    std::vector<double> filteredSignal;


private:
    void callAtEnd();
};


#endif //ECGDETECTORS_PANPEAKDETECTOR_H
