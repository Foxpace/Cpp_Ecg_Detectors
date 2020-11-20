
#ifndef ECGDETECTORS_DETECTORENGZEEREALTIME_H
#define ECGDETECTORS_DETECTORENGZEEREALTIME_H

/**
 * C. Zeelenberg, A single scan algorithm for QRS detection and
 * feature extraction, IEEE Comp. in Cardiology, vol. 6,
 * pp. 37-42, 1979 with modifications A. Lourenco, H. Silva,
 * P. Leite, R. Lourenco and A. Fred, “Real Time
 * Electrocardiogram Segmentation for Finger Based ECG
 * Biometrics”, BIOSIGNALS 2012, pp. 49-54, 2012.
 */


#include "RealTimeDetector.h"
#include "../iir1/Butterworth.h"
#include "vector"
#include <numeric>
#include "../handlers/MoveDifference.h"
#include "../handlers/Convolution.h"

class DetectorEngZeeRealTime: public RealTimeDetector  {
public:
    explicit DetectorEngZeeRealTime(double samplingRate) : RealTimeDetector(samplingRate){
        bandStop.setup(samplingRate, 50.0, 4.0);

        double diff = (ms1200-ms200);
        double sum = 0.6;
        for(int i=0; i < diff ; i++){
            Mslope.push_back(sum);
            sum = sum + 0.4/diff;
        }

//        for(double i=1; i >= 0.6; i = i - (i/diff)){
//            Mslope.push_back(i);
//        }
    };
    int processSample(double sample) override;
    void reset() override;

    ~DetectorEngZeeRealTime() override{
        DetectorEngZeeRealTime::reset();
        fs = 0;
    }


private:
    const static int order = 4; // 4th order
    Iir::Butterworth::BandStop<order> bandStop;
    MoveDifference moveDifference = MoveDifference(4);
    std::vector<double> kernel = {1.0, 4.0, 6.0, 4.0, 1.0};
    Convolution convolution = Convolution(kernel.size(), &kernel);

    double threshold = 0.01;

    int ms200 = (int) (0.2 * fs);
    int ms1200 = (int)  (1.2 * fs);
    int ms160 = (int) (0.16 * fs);
    int negThreshold = (int) (threshold * fs);

    double M = 0.0, newM5 = 0.0;

    std::vector<double> MM, Mslope;
    std::vector<int> QRS, rPeaks;

    int counter = 0, skipped = 0, waitCounter = (int) (fs * 0.2);

    std::vector<int> thiList;
    bool thi = false, thf = false;

    std::vector<double> unfilteredValues, filteredValues;

    bool ready = false;

};


#endif //ECGDETECTORS_DETECTORENGZEEREALTIME_H
