
#include "PanPeakDetector.h"
#include "../handlers/VectorFunctions.cpp"

double PanPeakDetector::passValue(double sample) {
    filteredSignal.push_back(sample);
    int i = (int) (filteredSignal.size() - 2);

    if(i > 0 && i < filteredSignal.size() - 1){
        if(filteredSignal[i - 1] < filteredSignal[i] && filteredSignal[i+1] < filteredSignal[i]){
            int peak = i;
            peaks.push_back(peak);

            if(filteredSignal[peak] > thresholdI1 && (peak - signalPeaks.back()) > 0.3 * fs){
                signalPeaks.push_back(peak);
                indexes.push_back(index);
                SPKI = 0.125 * filteredSignal[signalPeaks.back()] + 0.875 * SPKI;

                if(RRMissed != 0){
                    if (signalPeaks.back() - signalPeaks[signalPeaks.size() - 2] > RRMissed){
                        std::vector<int> missedSections = subVector(peaks,
                                indexes[indexes.size() - 2] + 1, indexes.back());
                        std::vector<int> missedSections2;

                        for(int missedPeak: missedSections){
                            if(missedPeak - signalPeaks[signalPeaks.size() - 2] > minDistance &&
                            signalPeaks.back() - missedPeak > minDistance &&
                            filteredSignal[missedPeak] > thresholdI2){
                                missedSections2.push_back(missedPeak);
                            }
                        }

                        if(!missedSections2.empty()){
                            std::vector<double> o = valuesOfIndexes(filteredSignal, missedSections2);
                            if(!o.empty()){
                                auto maxValue = maxValueFromPointToEnd<double>(o, 0);
                                int missedPeak = findValueFromPointToEnd<int>(missedSections2, 0, maxValue);
                                missedPeaks.push_back(missedPeak);
                                signalPeaks.push_back(signalPeaks.back());
                                signalPeaks[signalPeaks.size() - 2] = missedPeak;
                                callAtEnd();
                                return missedPeak;
                            }
                        }
                    }
                }
                callAtEnd();
                return peak;
            }else{
                noisePeaks.push_back(peak);
                NPKI = 0.125 * filteredSignal[noisePeaks.back()] + 0.875 * NPKI;
            }
            callAtEnd();
        }
    }
    return -1.0;
}

void PanPeakDetector::callAtEnd() {

    thresholdI1 = NPKI + 0.25 * (SPKI - NPKI);
    thresholdI2 = 0.5 * thresholdI1;

    if(signalPeaks.size() > 8){
        std::vector<int> array = subVector(signalPeaks, signalPeaks.size()-9, signalPeaks.size()-1);
        std::vector<int> RR = diff(array);
        double RRAve = mean(RR);
        RRMissed = (int) (1.66 * RRAve);
    }

    index++;

}

void PanPeakDetector::reset() {

    signalPeaks.clear();
    noisePeaks.clear();

    SPKI = 0.0, NPKI = 0.0;
    thresholdI1 = 0.0, thresholdI2 = 0.0;
    RRMissed = 0;
    index = 0;

    indexes.clear();
    missedPeaks.clear();
    peaks.clear();
    filteredSignal.clear();
}
