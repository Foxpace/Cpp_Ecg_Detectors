cmake_minimum_required(VERSION 3.17)
project(Cpp_Ecg_Detectors)

set(CMAKE_CXX_STANDARD 14)

add_executable(Cpp_Ecg_Detectors
        main.cpp
        realtime/RealTimeDetector.h
        realtime/DetectorEngZeeRealTime.cpp
        realtime/DetectorEngZeeRealTime.h
        realtime/DetectorPanTompkins.cpp
        realtime/DetectorPanTompkins.h
        realtime/Detectors.h

        iir1/Butterworth.cpp
        iir1/Butterworth.h
        iir1/Common.h
        iir1/Biquad.cpp
        iir1/Biquad.h
        iir1/Cascade.h
        iir1/Cascade.cpp
        iir1/MathSupplement.h
        iir1/PoleFilter.h
        iir1/PoleFilter.cpp
        iir1/State.h
        iir1/State.cpp
        iir1/Types.h

        handlers/HelperInterface.h
        handlers/MoveDifference.h
        handlers/MoveDifference.cpp
        handlers/Convolution.cpp
        handlers/Convolution.h
        handlers/MWA.cpp
        handlers/MWA.h
        handlers/VectorFunctions.cpp
        handlers/PanPeakDetector.cpp
        handlers/PanPeakDetector.h
        )
#add_library(
#        # Sets the name of the library.
#        native-lib
#
#        # Sets the library as a shared library.
#        SHARED
#
#        # Provides a relative path to your source file(s).
#        realtime/RealTimeDetector.h
#        realtime/DetectorEngZeeRealTime.cpp
#        realtime/DetectorEngZeeRealTime.h
#        realtime/DetectorPanTompkins.cpp
#        realtime/DetectorPanTompkins.h
#        realtime/Detectors.h
#
#        iir1/Butterworth.cpp
#        iir1/Butterworth.h
#        iir1/Common.h
#        iir1/Biquad.cpp
#        iir1/Biquad.h
#        iir1/Cascade.h
#        iir1/Cascade.cpp
#        iir1/MathSupplement.h
#        iir1/PoleFilter.h
#        iir1/PoleFilter.cpp
#        iir1/State.h
#        iir1/State.cpp
#        iir1/Types.h
#
#        handlers/HelperInterface.h
#        handlers/MoveDifference.h
#        handlers/MoveDifference.cpp
#        handlers/Convolution.cpp
#        handlers/Convolution.h
#        handlers/MWA.cpp
#        handlers/MWA.h
#        handlers/VectorFunctions.cpp
#        handlers/PanPeakDetector.cpp
#        handlers/PanPeakDetector.h
#)