#ifndef Sharpir_h
#define Sharpir_h
#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_ADS1015.h>

class Sharpir{

  public:
    Sharpir();
  private:
    Adafruit_ADS1115 ads0;
    Adafruit_ADS1115 ads1;
    Adafruit_ADS1115 ads2;
    Adafruit_ADS1115 ads3;


    double print(byte pin, double sampleArray[], byte sampleFinalSize, byte excludedEdgeValues);

    double mean(double sample[], byte size);
    double printMean(double sample[], byte size);
    double variance(double sample[], byte size);
    double printVariance(double sample[], byte size);
    double standard_deviation(double sample[], byte size);
    double median(double sample[], byte size);
    void print_maxmin(double sample[], byte size);
    double confidence_interval(double SD, byte size, byte confidence_level);
    void print_confidence_interval(double SD, byte size);
    void getFinalSortedSample(byte pin, double sampleArray[], byte sampleFinalSize, byte excludedEdgeValues);
    void getSortedSample(byte pin, double sampleArray[], byte sampleSize);
    void getSample(byte pin, double sampleArray[], byte sampleSize);
    double getMiliVolts(byte pin);
    double ads032(); // pino:0 - terra no 2 e tensao no 3
    double ads010(); // pino:1 - terra no 0 e tensao no 1
    double ads132(); // pino:2
    double ads110(); // pino:3
    double ads232(); // pino:4 
    double ads210(); // pino:5 
    double ads332(); // pino:6 
    double ads310(); // pino:7
    float scalefactor;
    int16_t rawADCvalue;
    double milivolts;

};
#endif
