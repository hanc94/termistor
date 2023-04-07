int analogPin = 0;   // Pin donde esta conectado el divisor de tension en el Arduino
#define sample 50
float Vin = 5.0;     // [V]       Voltage de entrada en el divisor de tension
float R = 37700;  // [ohm]     Valor de la resistencia secundaria del divisor de tension
float Rt, AVo[sample], VRt;       // Resistencia del termistor
float Vo = 0;     // Voltaje de salida del divisor
float T0 = 298.15;   // [K] (25ºC)
float R0 = 100000;    //R termistor a 25°
float beta = 3950;    // [K]        Parametro Beta
float TemC = 0.0;   // [ºC]       Temperatura de salida en grados Celsius


void setup() {
  // Configuramos el puerto Serie
  Serial.begin(9600);

  // Configuramos el pin del Arduino en entrada
  pinMode(analogPin, INPUT);
}
int i;
void loop(){
  
  for (i = 0; i < sample; i++) {
    AVo[i] = analogRead(analogPin);
    delay(10);
  }
  // average all the samples out
  float media = 0;
  for (i = 0; i < sample; i++) {
    media += AVo[i];
  }
  media /= sample;

  Vo = Vin * ((float)(media)) / 1023;

  VRt = Vin - Vo;

  Rt = ((R * VRt) / (Vin)) / (1 - (VRt / Vin));

  TemC =  1 / (((log(Rt / R0)) / beta) + 1 / T0);
  TemC -= 273.15;
  //TemC = (VRt + 12.29) / (0.0491) - 273;
  //Rt = R * ( (Vin / VRt) - 1);

  Serial.print("Voltaje ");
  Serial.print(VRt);
  Serial.print("  Temperatura  ");
  Serial.print(TemC);
  Serial.print("  Resistencia   ");
  Serial.println(Rt);




  delay(500);
}
