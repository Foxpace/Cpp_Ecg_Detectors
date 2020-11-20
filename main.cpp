#include "realtime/Detectors.h"


int main() {

    double fs = 512.0; // sampling frequency
    DetectorEngZeeRealTime detector = DetectorEngZeeRealTime(fs); // create specific detector with inputs
    double samples[] = {0}; // ECG signal - just for demonstration
    // to simulate real-time procedure, we will use for
    for (double sample: samples) {
        int qrs = detector.processSample(sample);
        if(qrs != -1){
            // -1 - nothing
            // otherwise - it is index of the QRS complex in signal
            // does not need to be in order for some detectors (sorting required in some cases)
        }
    }
    detector.reset(); // if something went wrong - this will empty memory in detector
    // for new configuration create new detector object
}
