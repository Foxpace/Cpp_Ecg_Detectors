
/**
 * Jiapu Pan and Willis J. Tompkins.
 * A Real-Time QRS Detection Algorithm.
 * In: IEEE Transactions on Biomedical Engineering
 * BME-32.3 (1985), pp. 230–236.
 */

#include "DetectorPanTompkins.h"

int DetectorPanTompkins::processSample(double sample) {

    if(!ready){
        double filteredSample = bandPass.filter(sample);
        filteredSample = moveDifference.passValue(filteredSample);
        if(std::isnan(filteredSample)){
            skipped++;
        }else{
            skipped++;
            ready = true;
        }
        return -1;
    }

    double filteredSample = bandPass.filter(sample);
    filteredSample = moveDifference.passValue(filteredSample);
    filteredSample = filteredSample * filteredSample;
    filteredSample = mwa.passValue(filteredSample);
    return (int) panPeakDetector.passValue(filteredSample);
}

void DetectorPanTompkins::reset() {
    bandPass.reset();
    moveDifference.reset();
    mwa.reset();
    skipped = 0;
    panPeakDetector.reset();
    ready = false;
}
