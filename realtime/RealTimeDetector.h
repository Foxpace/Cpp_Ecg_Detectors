
#ifndef ECGDETECTORS_REALTIMEDETECTOR_H
#define ECGDETECTORS_REALTIMEDETECTOR_H



class RealTimeDetector {
public:
    explicit RealTimeDetector(double samplingRate) {
        this->fs = samplingRate;
    }

    virtual int processSample(double sample) = 0;
    virtual void reset() {}
    virtual ~RealTimeDetector()= default;

protected:
    double fs = 0;
};


#endif //ECGDETECTORS_REALTIMEDETECTOR_H
