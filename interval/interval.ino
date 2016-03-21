// 必読
// [Arduino Language Reference](https://www.arduino.cc/en/Reference/HomePage)
// [2016年、C言語はどう書くべきか (前編)](http://postd.cc/how-to-c-in-2016-1/)
// [2016年、C言語はどう書くべきか (後編)](http://postd.cc/how-to-c-in-2016-2/)

// interval      - readme このファイルです
// IntervalTimer - インターバルタイマ構造体とかのライブラリです
// setup         - void setup() が入ってます


// uint32_t と バイナリのおさらい
// uint32_t は unsigned long
// unsigned long は 32bits = 4bytes

// unsigned long x = 9408; の場合
// decimal:                                         9408
// binary:       0000 0000 0000 0000 0010 0100 1100 0000
// hexadecimal:     0    0    0    0    2    4    C    0
// hexadecimal:       0x00      0x00      0x24      0xC0
// bytes:                0         0        36       192

// unsigned long x = 9488; の場合
// decimal:                                         9488
// binary:       0000 0000 0000 0000 0010 0101 0001 0000
// hexadecimal:     0    0    0    0    2    5    1    0
// hexadecimal:       0x00      0x00      0x24      0xC0
// bytes:                0         0        37        16

// unsigned long x = 0xFF; の場合
// decimal:                                          255
// binary:       0000 0000 0000 0000 0000 0000 1111 1111
// hexadecimal:     0    0    0    0    0    0    F    F
// hexadecimal:       0x00      0x00      0x00      0xFF
// bytes:                0         0         0       255


// 任意の位置のbyteを取り出す方法

// (x >> (8 * n) ) & 0xFF) でとり出せる

// x = 9408, n = 0 のとき
//   (9408 >> (8 * 0)) & 0xFF)
// = (9408 >> 0)       & 0xFF)
// = (9408 >> 0)       & 0xFF)
// = ((0b00000000000000000010010011000000 >> 0) & 0xFF)
// = (0b00000000000000000010010011000000 & 0xFF)
// = (0b00000000000000000010010011000000
//  & 0b00000000000000000000000011111111)
// =  0b00000000000000000000000011000000
// =  0x   0   0   0   0   0   0   C   0
// =  0x000000C0
// =  0xC0
// =  192


