# define __BUFFER_SIZE__ 16 // 送信バッファの大きさ

// 構造体をグローバル変数で使うよ宣言
struct IntervalTimer timer1; // サンプリングレートを保証するための精密タイマ
struct SendData1 sendData1s[__BUFFER_SIZE__];
uint32_t counter1 = 0; // __BUFFER_SIZE__ 回ごとに送信するためのカウンタ
uint32_t prevLoop = 0; // 前回のフレーム
uint8_t lag = 0;
uint32_t buffer_length = sizeof(SendData1) * __BUFFER_SIZE__; // バイト配列の大きさを計算

void setup() {
  Serial.begin(115200);
  delay(3000); // ArduinoのICの電圧が安定するまでしばし待つ
  uint32_t startTime = micros(); // 基準となる時間
  // 初期化
  initIntervalTimer(&timer1, startTime, 500); // 1/0.0005 = 2000Hz = 2KHz
  Serial.println(timer1.intervalTime);
}

void loop() {
  uint32_t currentTime = micros(); 
  
  if( stepIntervalTimer(&timer1, currentTime) ){ // サンプリングの時間
    uint32_t i = counter1 % __BUFFER_SIZE__;
    //sendData1s[i].timeStamp = currentTime;
    sendData1s[i].value     = analogRead(A0);
     lag += timer1.nthLoop - prevLoop - 1; // フレーム落ち検出
    if( i == __BUFFER_SIZE__ - 1 ){                       // バッファが一杯になった
      uint8_t *buf = (uint8_t*)sendData1s;                // 構造体をバイト配列にキャスト
      Serial.write(buf, buffer_length);
      //Serial.println();
      Serial.println(lag);
      lag = 0;
    }
    prevLoop = timer1.nthLoop;
    counter1++;
  }
}

