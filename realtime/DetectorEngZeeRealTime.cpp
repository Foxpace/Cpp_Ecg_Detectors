
/**
 * C. Zeelenberg, A single scan algorithm for QRS detection and
 * feature extraction, IEEE Comp. in Cardiology, vol. 6,
 * pp. 37-42, 1979 with modifications A. Lourenco, H. Silva,
 * P. Leite, R. Lourenco and A. Fred, “Real Time
 * Electrocardiogram Segmentation for Finger Based ECG
 * Biometrics”, BIOSIGNALS 2012, pp. 49-54, 2012.
 */

#include "DetectorEngZeeRealTime.h"
#include "../handlers/VectorFunctions.cpp"


int DetectorEngZeeRealTime::processSample(double sample) {
    if(!ready){
        double filtered = bandStop.filter(sample);
        filtered = moveDifference.passValue(filtered);
        if(std::isnan(filtered)){
            skipped++;
            return -1;
        }

        filtered = convolution.passValue(filtered);
        if(std::isnan(filtered)){
            skipped++;
            return -1;
        }

        if(--waitCounter != 0){
            skipped++;
            return -1;
        }

        ready = true;
        return -1;
    }else{
        double filtered = bandStop.filter(sample);
        filtered = moveDifference.passValue(filtered);
        filtered = convolution.passValue(filtered);

        unfilteredValues.push_back(sample);
        filteredValues.push_back(filtered);
        const unsigned int i = filteredValues.size() - 1;

        if(filteredValues.size() < 5 * fs){
            M = 0.6 * maxValueFromPointToEnd<double>(filteredValues, 0);
            MM.push_back(M);
            if(MM.size() > 5){
                MM.erase(MM.begin());
            }
        }else if(!QRS.empty()){

            if(filteredValues.size() < QRS.back() + ms200){
                newM5 = 0.6 * maxValueFromPointToEnd<double>(filteredValues, QRS.back());
                if(newM5 > 1.5 * MM.back()){
                    newM5 = 1.1 * MM.back();
                }
            } else if(i == QRS.back() + ms200){
                MM.push_back(newM5);
                if(MM.size() > 5){
                    MM.erase(MM.begin());
                }
                M = mean<double>(MM);
            } else if(i > (QRS.back() + ms200) && i < (QRS.back() + ms1200)){
                M = mean<double>(MM) * Mslope[i - (QRS.back() + ms200)];
            }else if(i > (QRS.back() + ms1200)){
                M = 0.6 * mean<double>(MM);
            }
        }


        if(QRS.empty() && filteredValues[i] > M){
            QRS.push_back(i);
            thiList.push_back(i);
            thi = true;
        }else if(!QRS.empty()){
            if(i > (QRS.back() + ms200) && filteredValues[i] > M){
                QRS.push_back(i);
                thiList.push_back(i);
                thi = true;
            }
        }

        if(!thiList.empty()){
            if(thi && i < (thiList.back() + ms160)){
                if(filteredValues[i] < -M && filteredValues[i - 1] > -M){
                    thf = true;
                }

                if(thf && filteredValues[i] < -M){
                    counter++;
                }else if(filteredValues[i] > -M && thf){
                    counter = 0;
                    thi = false;
                    thf = false;
                }
            }else if(thi && i > (thiList.back() + ms160)){
                counter = 0;
                thi = false;
                thf = false;
            }
        }

        if(counter > negThreshold){
            auto value = maxValueFromPointToEnd<double>(filteredValues, thiList.back() - negThreshold);
            int rPeak = findValueFromPointToEnd<double>(filteredValues, (thiList.back() - negThreshold), value);
            if(rPeak != -1){
                rPeaks.push_back(rPeak);
                counter = 0;
                thi = false;
                thf = false;
                return rPeak + skipped;
            }
        }
    }


    return -1;
}

void DetectorEngZeeRealTime::reset() {
    bandStop.reset();
    moveDifference.reset();
    convolution.reset();

    M = 0.0, newM5 = 0.0;

    MM.clear();
    QRS.clear();
    rPeaks.clear();

    counter = 0, skipped = 0, waitCounter =(int) (fs * 0.2);

    thiList.clear();
    thi = false, thf = false;

    unfilteredValues.clear();
    filteredValues.clear();

    ready = false;
}
