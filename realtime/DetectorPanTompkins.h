
#ifndef ECGDETECTORS_DETECTORPANTOMPKINS_H
#define ECGDETECTORS_DETECTORPANTOMPKINS_H

/**
 * Jiapu Pan and Willis J. Tompkins.
 * A Real-Time QRS Detection Algorithm.
 * In: IEEE Transactions on Biomedical Engineering
 * BME-32.3 (1985), pp. 230–236.
 */

#include "RealTimeDetector.h"
#include "../iir1/Butterworth.h"
#include "vector"
#include <numeric>
#include "../handlers/MoveDifference.h"
#include "../handlers/Convolution.h"
#include "../handlers/MWA.h"
#include "../handlers/PanPeakDetector.h"

class DetectorPanTompkins : public RealTimeDetector  {
public:
    explicit DetectorPanTompkins(double fs) : RealTimeDetector(fs){
        bandPass.setup(fs, 10.0, 5.0);
    };
    int processSample(double sample) override;
    void reset() override;

    ~DetectorPanTompkins() override{
        DetectorPanTompkins::reset();
        bandPass.reset();
    }

private:
    const static int order = 1; // 1th order
    Iir::Butterworth::BandPass<order> bandPass;
    MoveDifference moveDifference = MoveDifference(2);
    MWA mwa = MWA((int) (0.12 * fs));
    PanPeakDetector panPeakDetector = PanPeakDetector(fs);

    unsigned int skipped = 0;
    bool ready = false;


};


#endif //ECGDETECTORS_DETECTORPANTOMPKINS_H
