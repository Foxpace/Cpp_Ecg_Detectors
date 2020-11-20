# ECG R wave detectors in C++

**This library is inspired by [py-ecg-detectors](https://github.com/berndporr/py-ecg-detectors).**

**_This library is not created with affiliation to authors of Python library Luis Howell and Bernd Porr._** 

**_Citation DOI: [10.5281/zenodo.3353396](https://doi.org/10.5281/zenodo.3353396) and license: [GPL-3.0 License](https://github.com/berndporr/py-ecg-detectors) to their work.  Great gratitude for their work._** [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

# Changes:

* implementation of 2 algorithms, which are modified to work in real time
* **implementation of the Butterworth filters are handled by [IIR1 -- Realtime C++ filter library](https://github.com/berndporr/iir1)**
* results of the algorithms may vary, due to the rounding errors and implementation of the filters 
* HRV variability and testing is not available

*Citations can be found above every class of the detector*

### Available real-time detectors:
* Engelse and Zeelenberg detector
* Pan and Tompkins detector

### [For Kotlin/Java implementation go here](https://github.com/Creative-Motion-Apps/Kotlin-Ecg-Detectors) 

# Real-time detector usage:
```c++
#include "realtime/Detectors.h"
    
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
```

# Third parties and thanks goes to:

* **[IIR1 -- Realtime C++ filter library](https://github.com/berndporr/iir1)** **- An infinite impulse response (IIR) filter library for Linux, Mac OSX and Windows which implements Butterworth, RBJ, Chebychev filters . Library is created by *Bernd Porr*, who is also contributor to py-ecg-detectors**. **_Library is licensed under MIT license_**. [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/berndporr/iir1/blob/master/COPYING)




# License:

Licensed under the same license as [py-ecg-detectors](https://github.com/berndporr/py-ecg-detectors) - GPL-3.0 License. For more information visit LICENSE file in depository. [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)