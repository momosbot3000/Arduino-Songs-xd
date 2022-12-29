void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  Renai_Circulation();
}


void loop() {
  
}

float Frecuency(int note, int octave){
  
  float hz = 440 * pow(1.05946309436, 12 * (octave - 4) + note - 10);
  return hz;

}


float nKey_Hz(uint8_t nKey){

  if(nKey >= 1 && nKey <= 88){
    int sum = 0;
    nKey += 9;
    while(nKey > 12){
      sum++;    
      nKey -= 12;
    }
    int N = nKey;
    int Oc = sum;
  
    float hz = Frecuency(N, Oc);
    return hz;
  }
  else {
    return 0;
  }
}


void Play(uint8_t Notes[][2], int SizeNotes, byte bpm, byte buzzer){
  
  float start = millis();
  float keep = start;
  float beatDuration = 60000 / bpm;

  for (int i = 0; i < SizeNotes; i++) {
    
    float noteDuration = (Notes[i][1] * beatDuration) / 8; 
    float Frecuency = nKey_Hz(Notes[i][0]);

    if(Frecuency > 0){    
      while(millis() <= keep + (noteDuration * 0.9)){
        tone(buzzer, Frecuency);
      }
      while(millis() >= keep + (noteDuration * 0.9) && millis() <= keep + noteDuration){    
        noTone(buzzer);
      }
    }
    else{
      while(millis() <= keep + noteDuration){
        noTone(buzzer);
      }
    }
    keep += noteDuration;
  }
}

void Renai_Circulation(){

  uint8_t Notes[][2] = {
    {0 , 12}, {53, 2 }, {51, 2 }, //0
    {53, 6 }, {53, 6 }, {51, 4 }, {56, 6 }, {56, 2 }, {0 , 4 }, {53, 2 }, {51, 2 }, //1
    {53, 6 }, {53, 6 }, {51, 4 }, {56, 6 }, {60, 2 }, {0 , 4 }, {53, 2 }, {51, 2 }, //2
    {53, 6 }, {53, 4 }, {53, 2 }, {51, 4 }, {56, 6 }, {56, 4 }, {56, 2 }, {58, 4 }, //3
    {56, 6 }, {56, 4 }, {56, 2 }, {53, 4 }, {60, 8 }, {0 , 8 }, //4
    {56, 6 }, {56, 2 }, {0 , 2 }, {58, 2 }, {59, 2 }, {0 , 2 }, {60, 6 }, {56, 2 }, {0 , 4 }, {51, 2 }, {53, 2 }, //5
    {56, 6 }, {56, 2 }, {0 , 2 }, {58, 2 }, {59, 2 }, {0 , 2 }, {60, 6 }, {56, 2 }, {0 , 4 }, {53, 2 }, {0 , 2 }, //6
    {56, 2 }, {0 , 2 }, {53, 2 }, {56, 2 }, {0 , 4 }, {53, 2 }, {0 , 2 }, {56, 2 }, {0 , 2 }, {53, 2 }, {56, 2 }, {0 , 4 }, {53, 2 }, {0 , 2 }, //7
    {61, 2 }, {60, 4 }, {56, 6 }, {53, 2 }, {0 , 2 }, {60, 8 }, {0 , 4 }, //8
    {56, 6 }, {56, 2 }, {0 , 2 }, {58, 2 }, {59, 2 }, {0 , 2 }, {60, 6 }, {56, 2 }, {0 , 4 }, {51, 2 }, {53, 2 }, //9
    {56, 6 }, {56, 2 }, {0 , 2 }, {58, 2 }, {59, 2 }, {0 , 2 }, {60, 6 }, {56, 2 }, {0 , 4 }, {53, 2 }, {0 , 2 }, //10
    {56, 2 }, {0 , 2 }, {53, 2 }, {56, 2 }, {0 , 4 }, {53, 2 }, {0 , 2 }, {56, 2 }, {0 , 2 }, {53, 2 }, {56, 2 }, {0 , 4 }, {53, 2 }, {0 , 2 }, //11
    {61, 2 }, {60, 4 }, {56, 6 }, {58, 2 }, {0 , 2 }, {56, 8 }, {0 , 8 }, //12
  };


  byte bpm = 120;
  byte buzzer = 11;
  int SizeNotes =  (sizeof(Notes) / sizeof(*Notes));

  Play(Notes, SizeNotes, bpm, buzzer);
}