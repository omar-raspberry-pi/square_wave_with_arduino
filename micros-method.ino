// تعريف أرجل الليدات والأوقات (كما هي)
const int switchA = 11;
const int switchB = 10;

const unsigned long switchA_ON_TIME_us  = 9600;
const unsigned long switchA_OFF_TIME_us = 500;
const unsigned long switchB_ON_TIME_us  = 9600;
const unsigned long switchB_OFF_TIME_us = 500; // الفترة المفقودة سابقاً

unsigned long previousMicros = 0;

// الآن لدينا 5 حالات: 0، 1، 2، 3، 4
int currentState = 0;

void setup() {
  pinMode(switchA, OUTPUT);
  pinMode(switchB, OUTPUT);

}

void loop() {
  unsigned long currentMicros = micros();

  switch (currentState) {

    case 0: // الحالة 0: بداية التسلسل (تشغيل LED1)
      digitalWrite(switchA, HIGH);
     
      previousMicros = currentMicros;
      currentState = 1; // الانتقال لانتظار مدة التشغيل
      break;

    case 1: // الحالة 1: انتظار مدة تشغيل LED1 ثم إيقافه
      if (currentMicros - previousMicros >= switchA_ON_TIME_us) {
        digitalWrite(switchA, LOW);
        previousMicros = currentMicros;
        currentState = 2; // الانتقال لانتظار الفترة الفاصلة
      }
      break;

    case 2: // الحالة 2: انتظار الفترة الفاصلة (LED1 OFF) ثم تشغيل LED2
      if (currentMicros - previousMicros >= switchA_OFF_TIME_us) {
        digitalWrite(switchB, HIGH);
        previousMicros = currentMicros;
        currentState = 3; // الانتقال لانتظار مدة تشغيل LED2
      }
      break;

    case 3: // الحالة 3: انتظار مدة تشغيل LED2 ثم إيقافه
      if (currentMicros - previousMicros >= switchB_ON_TIME_us) {
        digitalWrite(switchB, LOW);
        previousMicros = currentMicros;
        currentState = 4; // الانتقال للحالة الجديدة: انتظار فترة إيقاف LED2
      }
      break;

    case 4: // الحالة 4: انتظار فترة الإيقاف الأخيرة (switchB_OFF_TIME_us)
      if (currentMicros - previousMicros >= switchB_OFF_TIME_us) {
        // انتهت فترة الإيقاف الأخيرة، نعود للبداية
        previousMicros = currentMicros;
        currentState = 0; // العودة إلى الحالة 0 لبدء التسلسل من جديد
      }
      break;
  }
}
