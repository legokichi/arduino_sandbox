
struct SendData1 {
  //uint32_t timeStamp;       // この値を得た時刻。
  uint16_t value;           // analogReadの値。analogReadは 0~1023 の値を返す = 2 bytes = 16 bytes
  uint8_t tab = '\n';       // データ区切り
};


// SendData 構造体の内訳の例

//struct SendData {
//  uint32_t timeStamp = 1495200048;
//  uint16_t value = 24;
//  uint8_t tab  = '\n';
//}; 32+16+8 = 56bit = 7byte

// uint64_t type
// 0b 0100 0100 | 0100 0001 | 0000 0000 | 0100 0001
// 0b 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000
// 0x    4    4 |    4    1 |    0    0 |    0    0
// 0x    0    0 |    0    0 |    0    0 |    0    0
// ascii    'D' |       'A' |       'T' |       'A'
// ascii   '\0' |      '\0' |      '\0' |      '\0'

// uint32_t timeStamp
// 0b 0101 1001 | 0001 1110 | 1111 0001 | 0011 0000
// 0x    5    9 |    1    E |    F    1 |    3    0
// 0d                                    1495200048

// uint16_t value
// 0b 0000 0000 | 0001 1000
// 0x    0    0 |    1    8
// 0d                    24
