# define __BUFFER_SIZE__ 32 // 送信バッファの大きさ

// 構造体をグローバル変数で使うよ宣言
struct IntervalTimer timer1; // サンプリングレートを保証するための精密タイマ
struct IntervalTimer timer2; // 頻度が異なる何らかの定期実行タスク用のタイマ
struct SendData1 sendData1s[__BUFFER_SIZE__];
struct SendData2 sendData2s[__BUFFER_SIZE__];
uint32_t counter1 = 0;
uint32_t counter2 = 0;

void setup() {
  Serial.begin(9600);
  delay(3000); // ArduinoのICの電圧が安定するまでしばし待つ
  uint32_t startTime = micros(); // 基準となる時間
  // 初期化
  initIntervalTimer(&timer1, startTime,   10000);
  initIntervalTimer(&timer2, startTime,   50000);
  Serial.println(timer1.intervalTime);
}

void loop() {
  uint32_t currentTime = micros(); 
  
  if( stepIntervalTimer(&timer1, currentTime) ){ // サンプリングの時間
    uint32_t i = counter1 % __BUFFER_SIZE__;
    sendData1s[i].timeStamp = currentTime;
    sendData1s[i].value     = analogRead(A0);
    if( i == __BUFFER_SIZE__ - 1 ){                       // バッファが一杯になった
      uint32_t len = sizeof(SendData1) * __BUFFER_SIZE__; // バイト配列の大きさを計算
      uint8_t *buf = (uint8_t*)sendData1s;                // 構造体をバイト配列にキャスト
      // Serial.write でメモリ上のバイト配列を送信した方が文字列に変換してから送るより通信効率は良い。
      Serial.write(buf, len);
    }
    counter1++;
  }
  
  if( stepIntervalTimer(&timer2, currentTime) ){ // サンプリングの時間
    uint32_t i = counter2 % __BUFFER_SIZE__;
    sendData2s[i].timeStamp = currentTime;
    sendData2s[i].value     = analogRead(A1);
    if( i == __BUFFER_SIZE__ - 1 ){                      // バッファが一杯になった
      // Serial.print は文字列送信用。
      // なので数値を送ろうとすると10進数のASCII文字列になる
      // 送信情報量が増えて通信が遅くなるので数値送信には向いていない
      // Serial.print はタブ(\t)区切りにすることでシリアルモニタで文字列を見やすくすることができる
      for(uint32_t j=0; j<__BUFFER_SIZE__; j++){
        Serial.print((char*)sendData2s[j].type);
        Serial.print('\t');
        Serial.print(sendData2s[j].timeStamp);
        Serial.print('\t');
        Serial.print(sendData2s[j].value);
        Serial.print('\n'); // println で改行して送信
      }
    }
    counter2++;
  }
}

