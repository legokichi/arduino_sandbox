
// インターバルタイマー構造体。コンストラクタとメンバ関数のない、メンバ変数だけのクラスです
struct IntervalTimer {
  uint32_t startTime;    // 基準となる時間
  uint32_t intervalTime; // インターバル時間
  uint32_t nextTime;     // 次のインターバル時刻
  uint32_t pastTime;     // startTime からの経過時間
  uint32_t nthLoop;      // このインターバルは nthLoop 回目
  uint32_t delayTime;    // 予定されたインターバルから delayTime だけ遅れている
};

// t はポインタ
// t には timer 構造体のアドレスが入ってる
// t が構造体そのものの時は t.startTime で構造体のメンバにアクセスできるが、
// t は構造体のポインタなので、この時は t->startTime でポインタが示すアドレスに存在する構造体にアクセスできる

// 構造体初期化関数。stepで呼ぶこと。
void initIntervalTimer(struct IntervalTimer* t, uint32_t startTime, uint32_t intervalTime){
  t->startTime    = startTime;
  t->intervalTime = intervalTime;
  t->nextTime     = startTime + intervalTime * 1;
  t->pastTime     = 0;
  t->nthLoop      = 0;
  t->delayTime    = 0;
}

// loopで呼ぶ。戻り値はこのループがインターバル時刻を満たしているかどうかの真偽値
bool stepIntervalTimer(struct IntervalTimer* t, uint32_t currentTime){
  t->pastTime  = currentTime - t->startTime;
  t->nthLoop   = t->pastTime / t->intervalTime; // 現在はnthLoop回目のインターバル
  t->delayTime = t->pastTime % t->intervalTime; // 現在はnthLoop回目のインターバルからdelayTimeだけ遅れてる
  if( currentTime > t->nextTime ){
    t->nextTime = t->startTime + t->intervalTime * (t->nthLoop + 1); // 次回は (nthLoop + 1) 回目のインターバルにセット
    return true; // 今がそのとき
  }
  return false; // まだ早い
}


