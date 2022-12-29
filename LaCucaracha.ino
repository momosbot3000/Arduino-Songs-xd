void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);

  LaCucarcha(11);
  
}


void loop() {
  
  
}

float Frecuency(int note, int octave){
  
  int hz = 440 * pow(1.05946309436, 12 * (octave - 4) + note - 10);
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


void Play(uint8_t Notes[][2], int SizeNotes, byte bpm, int buzzer){
  
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

void LaCucarcha(int buzzer){

  uint8_t Notes[][2] = {
    {47, 4 }, {47, 4 }, {47, 4 }, //0
    {52, 12}, {56, 8 }, {47, 4 }, {47, 4 }, {47, 4 }, //1
    {52, 12}, {56, 20}, //2
    {0 , 8 }, {52, 4 }, {52, 4 }, {51, 4 }, {51, 4}, {49, 4}, {49, 4}, //3
    {47, 20}, {47, 4 }, {47, 4 }, {47, 4 }, //4
    {51, 12}, {54, 8 }, {47, 4 }, {47, 4 }, {47, 4 }, //5
    {51, 12}, {54, 20}, //6
    {0 , 8 }, {59, 4 }, {61, 4 }, {59, 4 }, {57, 4 }, {56, 4 }, {54, 4 }, //7
    {56, 12}, {52, 8 }, //8
  };

  byte bpm = 144;
  int SizeNotes =  (sizeof(Notes) / sizeof(*Notes));

  Play(Notes, SizeNotes, bpm, buzzer);
      
}