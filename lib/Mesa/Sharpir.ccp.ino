#include "Sharpir.h"


Sharpir::Sharpir():ads0(0x48),ads1(0x49),ads2(0x4A),ads3(0x4B){
  scalefactor = 0.1875F;
  rawADCvalue = 0;
  milivolts = 0.0;
}


double Sharpir::print(byte pin, double sampleArray[], byte sampleFinalSize, byte excludedEdgeValues){
  getFinalSortedSample(pin,sampleArray,sampleFinalSize,excludedEdgeValues);
  printMean(sampleArray,sampleFinalSize);
  printVariance(sampleArray,sampleFinalSize);
  double SD = standard_deviation(sampleArray,sampleFinalSize);
  median(sampleArray,sampleFinalSize);
  print_maxmin(sampleArray,sampleFinalSize);
  print_confidence_interval(SD, sampleFinalSize);
  
}

double Sharpir::mean(double sample[], byte size){
  double average = 0;
  for(int i = 0;i<size;i++){
    average += sample[i];
  }
  return average/size;
}
double Sharpir::printMean(double sample[], byte size){
  Serial.print(" - Mean: ");
  Serial.print(mean(sample,size));
}
double Sharpir::variance(double sample[], byte size){
  double average = mean(sample,size);
  double variance = 0;
  for(int i = 0;i<size;i++){
    variance += (sample[i]-average)*(sample[i]-average);
  }
  variance = (double)variance/(size-1);
  return variance;
}
double Sharpir::printVariance(double sample[], byte size){
  Serial.print(" - Var: ");
  Serial.print(variance(sample,size));
}
double Sharpir::standard_deviation(double sample[], byte size){
  double SD = sqrt(variance(sample,size));
  Serial.print(" - SD: ");
  Serial.print(SD);
  return SD;
}
double Sharpir::median(double sample[], byte size){
  double median;
  if(size%2==0){
    median = ((sample[size/2])+(sample[(-1+size/2)]))/2 ;
  }else{
    median = sample[(size-1)/2];
  }
  Serial.print(" - Median: ");
  Serial.print(median);
  return median;
}

void Sharpir::print_maxmin(double sample[], byte size){
  Serial.print(" - Max: ");
  Serial.print(sample[size-1]);
  Serial.print(" - Min: ");
  Serial.print(sample[0]);
}

double Sharpir::confidence_interval(double SD, byte size, byte confidence_level){
  double zvalue;
  switch(confidence_level){
    case 70: zvalue=1.037; break;
    case 80: zvalue=1.226; break;
    case 90: zvalue=1.645; break;
    case 91: zvalue=1.7; break;
    case 92: zvalue=1.75; break;
    case 93: zvalue=1.81; break;
    case 94: zvalue=1.84; break;
    case 95: zvalue=1.96; break;
    case 96: zvalue=2.055; break;
    case 97: zvalue=2.965; break;
    case 98: zvalue=2.33; break;
    case 99: zvalue=2.575; break;
    // case 999: zvalue=3.295; break;
  }
  return zvalue*SD/sqrt(size);
}

void Sharpir::print_confidence_interval(double SD, byte size){
  int confidence_level = 90;
  Serial.print("-");
  Serial.write(241);
  Serial.print(confidence_interval(SD,size,confidence_level));
  Serial.print("[");
  Serial.print(confidence_level);
  Serial.print("%] ");
  confidence_level = 95;
  Serial.print("-");
  Serial.write(241);
  Serial.print(confidence_interval(SD,size,confidence_level));
  Serial.print("[");
  Serial.print(confidence_level);
  Serial.print("%] ");
  confidence_level = 99;
  Serial.print("-");
  Serial.write(241);
  Serial.print(confidence_interval(SD,size,confidence_level));
  Serial.print("[");
  Serial.print(confidence_level);
  Serial.print("%] ");

}


void Sharpir::getFinalSortedSample(byte pin, double sampleArray[], byte sampleFinalSize, byte excludedEdgeValues){
  byte bigArraySize = sampleFinalSize + 2*excludedEdgeValues;
  double bigArray[bigArraySize];
  getSortedSample(pin, bigArray, bigArraySize);
  for(byte position= 0; position<sampleFinalSize; position++){
    sampleArray[position] = bigArray[position+excludedEdgeValues];
  }
}
void Sharpir::getSortedSample(byte pin, double sampleArray[], byte sampleSize){
  getSample(pin, sampleArray, sampleSize);
  for(int i=0; i<(sampleSize-1); i++) {
    bool flag = true;
    for(int o=0; o<(sampleSize-(i+1)); o++) {
      if(sampleArray[o] > sampleArray[o+1]) {
        int t = sampleArray[o];
        sampleArray[o] = sampleArray[o+1];
        sampleArray[o+1] = t;
        flag = false;
      }
    }
    if (flag) break;
  }
}
void Sharpir::getSample(byte pin, double sampleArray[], byte sampleSize){
  byte samples = 0;
  while (samples<sampleSize){
    sampleArray[samples] = getMiliVolts(pin);
    delay(30);
    samples++;
  }
}
double Sharpir::getMiliVolts(byte pin){ // 8 pinos disponiveis com 4 conversores
  switch(pin){
    case 0: milivolts = ads032(); break;
    case 1: milivolts = ads010(); break;
    case 2: milivolts = ads132(); break;
    case 3: milivolts = ads110(); break;
    case 4: milivolts = ads232(); break;
    case 5: milivolts = ads210(); break;
    case 6: milivolts = ads332(); break;
    case 7: milivolts = ads310(); break;
  }
  return milivolts;
}
double Sharpir::ads032(){
  rawADCvalue = ads0.readADC_Differential_2_3();
  milivolts = (rawADCvalue * scalefactor);
  return milivolts;
}
double Sharpir::ads010(){
  rawADCvalue = ads0.readADC_Differential_0_1();
  milivolts = (rawADCvalue * scalefactor);
  return milivolts;
}
double Sharpir::ads132(){
  rawADCvalue = ads1.readADC_Differential_2_3();
  milivolts = (rawADCvalue * scalefactor);
  return milivolts;
}
double Sharpir::ads110(){
  rawADCvalue = ads1.readADC_Differential_0_1();
  milivolts = (rawADCvalue * scalefactor);
  return milivolts;
}
double Sharpir::ads232(){
  rawADCvalue = ads2.readADC_Differential_2_3();
  milivolts = (rawADCvalue * scalefactor);
  return milivolts;
}
double Sharpir::ads210(){
  rawADCvalue = ads2.readADC_Differential_0_1();
  milivolts = (rawADCvalue * scalefactor);
  return milivolts;
}
double Sharpir::ads332(){
  rawADCvalue = ads3.readADC_Differential_2_3();
  milivolts = (rawADCvalue * scalefactor);
  return milivolts;
}
double Sharpir::ads310(){
  rawADCvalue = ads3.readADC_Differential_0_1();
  milivolts = (rawADCvalue * scalefactor);
  return milivolts;
}
