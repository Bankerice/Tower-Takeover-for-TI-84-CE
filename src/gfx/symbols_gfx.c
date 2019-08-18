// convpng v7.1
#include <stdint.h>
#include "symbols_gfx.h"

uint16_t symbols_gfx_pal[256] = {
 0x0000,  // 00 :: rgb(0,0,0)
 0x7FFF,  // 01 :: rgb(252,252,252)
 0xB494,  // 02 :: rgb(103,36,167)
 0x7B7E,  // 03 :: rgb(244,220,244)
 0x77DD,  // 04 :: rgb(242,242,242)
 0x0287,  // 05 :: rgb(0,160,56)
 0x7984,  // 06 :: rgb(247,99,29)
 0x6BBA,  // 07 :: rgb(216,233,210)
 0x6B5C,  // 08 :: rgb(216,209,232)
 0xF2D5,  // 09 :: rgb(229,183,174)
 0x7A94,  // 10 :: rgb(247,163,163)
 0xD31E,  // 11 :: rgb(163,199,247)
 0x7794,  // 12 :: rgb(237,227,161)
 0x8000,  // 13 :: rgb(4,4,3)
 0x74E3,  // 14 :: rgb(240,58,23)
 0xB3A0,  // 15 :: rgb(100,237,0)
 0xC87E,  // 16 :: rgb(148,28,250)
 0x98C6,  // 17 :: rgb(53,53,53)
 0x7641,  // 18 :: rgb(237,146,9)
 0x82A4,  // 19 :: rgb(0,173,34)
 0xFFE0,  // 20 :: rgb(255,255,0)
 0x8000,  // 21 :: rgb(3,3,3)
 0x2108,  // 22 :: rgb(65,65,65)
 0xAD6B,  // 23 :: rgb(94,94,94)
 0x8000,  // 24 :: rgb(4,4,4)
 0xDDC0,  // 25 :: rgb(193,117,4)
 0x1E40,  // 26 :: rgb(61,144,0)
 0x2C53,  // 27 :: rgb(91,17,154)
 0x2108,  // 28 :: rgb(66,66,66)
 0xB96B,  // 29 :: rgb(119,95,91)
 0x6AB4,  // 30 :: rgb(214,170,162)
 0xB9AF,  // 31 :: rgb(114,111,122)
 0xE71A,  // 32 :: rgb(203,197,216)
 0x8224,  // 33 :: rgb(0,143,33)
 0xEF36,  // 34 :: rgb(226,205,183)
 0x3DCC,  // 35 :: rgb(124,113,101)
 0xB9EE,  // 36 :: rgb(116,124,113)
 0x6B99,  // 37 :: rgb(211,226,206)
 0xF39C,  // 38 :: rgb(229,229,229)
 0x4404,  // 39 :: rgb(143,0,33)
 0x9CA5,  // 40 :: rgb(56,44,42)
 0x2108,  // 41 :: rgb(63,63,63)
 0x4210,  // 42 :: rgb(129,129,129)
 0x1CE6,  // 43 :: rgb(61,55,49)
 0x9CE7,  // 44 :: rgb(57,61,55)
 0xDE51,  // 45 :: rgb(186,148,141)
 0x56B7,  // 46 :: rgb(176,171,188)
 0x9CC7,  // 47 :: rgb(54,53,58)
 0x7641,  // 48 :: rgb(237,144,5)
 0x7BFE,  // 49 :: rgb(249,249,249)
 0x8C63,  // 50 :: rgb(28,28,28)
 0x8401,  // 51 :: rgb(6,6,6)
 0x5EB2,  // 52 :: rgb(188,170,152)
 0x56F5,  // 53 :: rgb(176,188,171)
 0x3DEF,  // 54 :: rgb(120,120,120)
 0x6F3B,  // 55 :: rgb(224,204,224)
 0xBDAF,  // 56 :: rgb(122,111,122)
 0xF2D5,  // 57 :: rgb(228,182,173)
 0xEE52,  // 58 :: rgb(226,149,149)
 0x3D4A,  // 59 :: rgb(124,82,82)
 0xA98F,  // 60 :: rgb(82,100,124)
 0xCADB,  // 61 :: rgb(149,183,226)
 0x8284,  // 62 :: rgb(0,167,33)
 0xEF53,  // 63 :: rgb(224,215,154)
 0xBDCA,  // 64 :: rgb(122,117,83)
 0x3DEF,  // 65 :: rgb(122,122,122)
 0x1084,  // 66 :: rgb(33,33,33)
 0xA0E8,  // 67 :: rgb(62,62,62)
 0x1CE7,  // 68 :: rgb(57,57,57)
 0x8400,  // 69 :: rgb(5,5,4)
 0x7BDE,  // 70 :: rgb(244,244,244)
 0x8421,  // 71 :: rgb(12,12,12)
 0x0421,  // 72 :: rgb(9,9,9)
 0xDEF7,  // 73 :: rgb(191,191,191)
 0x8401,  // 74 :: rgb(6,6,5)
 0x1CA5,  // 75 :: rgb(61,40,40)
 0x5294,  // 76 :: rgb(162,162,162)
 0x14C7,  // 77 :: rgb(40,49,61)
 0xCA52,  // 78 :: rgb(149,149,149)
 0x4A52,  // 79 :: rgb(145,145,145)
 0x5EB7,  // 80 :: rgb(186,169,186)
 0x9CC7,  // 81 :: rgb(58,53,58)
 0x1084,  // 82 :: rgb(34,34,34)
 0x8421,  // 83 :: rgb(11,11,11)
 0x1CE5,  // 84 :: rgb(58,56,39)
 0x5004,  // 85 :: rgb(167,0,33)
 0xB96B,  // 86 :: rgb(118,94,90)
 0x6AB4,  // 87 :: rgb(213,169,161)
 0x5A51,  // 88 :: rgb(185,147,140)
 0xDDEF,  // 89 :: rgb(188,124,124)
 0x3E77,  // 90 :: rgb(124,152,188)
 0x5ECF,  // 91 :: rgb(186,178,126)
 0x6F36,  // 92 :: rgb(225,204,182)
 0x5EB2,  // 93 :: rgb(187,169,151)
 0x3DCC,  // 94 :: rgb(123,112,100)
 0x56F5,  // 95 :: rgb(175,187,170)
 0x6B99,  // 96 :: rgb(210,225,205)
 0x39EE,  // 97 :: rgb(115,123,112)
 0x8842,  // 98 :: rgb(20,20,20)
 0xBDEF,  // 99 :: rgb(126,126,126)
 0xC631,  // 100 :: rgb(141,141,141)
 0xF7BD,  // 101 :: rgb(240,240,240)
 0x4E73,  // 102 :: rgb(153,153,153)
 0x98A6,  // 103 :: rgb(46,46,46)
 0x4631,  // 104 :: rgb(137,137,137)
 0x7A94,  // 105 :: rgb(246,162,162)
 0xD31E,  // 106 :: rgb(162,198,246)
 0x7793,  // 107 :: rgb(236,226,160)
 0x77BD,  // 108 :: rgb(236,236,236)
 0xB9CE,  // 109 :: rgb(119,119,119)
 0x739C,  // 110 :: rgb(227,227,227)
 0x0842,  // 111 :: rgb(18,18,18)
 0xEE52,  // 112 :: rgb(225,148,148)
 0x3D4A,  // 113 :: rgb(123,81,81)
 0x5DEF,  // 114 :: rgb(187,123,123)
 0x94A5,  // 115 :: rgb(43,43,43)
 0x298F,  // 116 :: rgb(81,99,123)
 0xCADB,  // 117 :: rgb(148,182,225)
 0xBE57,  // 118 :: rgb(123,151,187)
 0x0421,  // 119 :: rgb(10,10,10)
 0x6004,  // 120 :: rgb(200,0,33)
 0x5ACF,  // 121 :: rgb(185,177,125)
 0xBDCA,  // 122 :: rgb(121,116,82)
 0xEF53,  // 123 :: rgb(223,214,153)
 0x8304,  // 124 :: rgb(0,200,33)
 0x7F99,  // 125 :: rgb(252,228,204)
 0x0000,  // 126 :: rgb(0,0,0)
 0x0000,  // 127 :: rgb(0,0,0)
 0x0000,  // 128 :: rgb(0,0,0)
 0x0000,  // 129 :: rgb(0,0,0)
 0x0000,  // 130 :: rgb(0,0,0)
 0x0000,  // 131 :: rgb(0,0,0)
 0x0000,  // 132 :: rgb(0,0,0)
 0xFFFF,  // 133 :: rgb(255,255,255)
 0x0000,  // 134 :: rgb(0,0,0)
 0x0000,  // 135 :: rgb(0,0,0)
 0x0000,  // 136 :: rgb(0,0,0)
 0x0000,  // 137 :: rgb(0,0,0)
 0x0000,  // 138 :: rgb(0,0,0)
 0x0000,  // 139 :: rgb(0,0,0)
 0x0000,  // 140 :: rgb(0,0,0)
 0x0000,  // 141 :: rgb(0,0,0)
 0x0000,  // 142 :: rgb(0,0,0)
 0x0000,  // 143 :: rgb(0,0,0)
 0x0000,  // 144 :: rgb(0,0,0)
 0x0000,  // 145 :: rgb(0,0,0)
 0x0000,  // 146 :: rgb(0,0,0)
 0x0000,  // 147 :: rgb(0,0,0)
 0x0000,  // 148 :: rgb(0,0,0)
 0x0000,  // 149 :: rgb(0,0,0)
 0x0000,  // 150 :: rgb(0,0,0)
 0x0000,  // 151 :: rgb(0,0,0)
 0x0000,  // 152 :: rgb(0,0,0)
 0x0000,  // 153 :: rgb(0,0,0)
 0x0000,  // 154 :: rgb(0,0,0)
 0x0000,  // 155 :: rgb(0,0,0)
 0x0000,  // 156 :: rgb(0,0,0)
 0x0000,  // 157 :: rgb(0,0,0)
 0x0000,  // 158 :: rgb(0,0,0)
 0x0000,  // 159 :: rgb(0,0,0)
 0x0000,  // 160 :: rgb(0,0,0)
 0x0000,  // 161 :: rgb(0,0,0)
 0x0000,  // 162 :: rgb(0,0,0)
 0x0000,  // 163 :: rgb(0,0,0)
 0x0000,  // 164 :: rgb(0,0,0)
 0x0000,  // 165 :: rgb(0,0,0)
 0x0000,  // 166 :: rgb(0,0,0)
 0x0000,  // 167 :: rgb(0,0,0)
 0x0000,  // 168 :: rgb(0,0,0)
 0x0000,  // 169 :: rgb(0,0,0)
 0x0000,  // 170 :: rgb(0,0,0)
 0x0000,  // 171 :: rgb(0,0,0)
 0x0000,  // 172 :: rgb(0,0,0)
 0x0000,  // 173 :: rgb(0,0,0)
 0x0000,  // 174 :: rgb(0,0,0)
 0x0000,  // 175 :: rgb(0,0,0)
 0x0000,  // 176 :: rgb(0,0,0)
 0x0000,  // 177 :: rgb(0,0,0)
 0x0000,  // 178 :: rgb(0,0,0)
 0x0000,  // 179 :: rgb(0,0,0)
 0x0000,  // 180 :: rgb(0,0,0)
 0x0000,  // 181 :: rgb(0,0,0)
 0x0000,  // 182 :: rgb(0,0,0)
 0x0000,  // 183 :: rgb(0,0,0)
 0x0000,  // 184 :: rgb(0,0,0)
 0x0000,  // 185 :: rgb(0,0,0)
 0x0000,  // 186 :: rgb(0,0,0)
 0x0000,  // 187 :: rgb(0,0,0)
 0x0000,  // 188 :: rgb(0,0,0)
 0x0000,  // 189 :: rgb(0,0,0)
 0x0000,  // 190 :: rgb(0,0,0)
 0x0000,  // 191 :: rgb(0,0,0)
 0x0000,  // 192 :: rgb(0,0,0)
 0x0000,  // 193 :: rgb(0,0,0)
 0x0000,  // 194 :: rgb(0,0,0)
 0x0000,  // 195 :: rgb(0,0,0)
 0x0000,  // 196 :: rgb(0,0,0)
 0x0000,  // 197 :: rgb(0,0,0)
 0x0000,  // 198 :: rgb(0,0,0)
 0x0000,  // 199 :: rgb(0,0,0)
 0x0000,  // 200 :: rgb(0,0,0)
 0x0000,  // 201 :: rgb(0,0,0)
 0x0000,  // 202 :: rgb(0,0,0)
 0x0000,  // 203 :: rgb(0,0,0)
 0x0000,  // 204 :: rgb(0,0,0)
 0x0000,  // 205 :: rgb(0,0,0)
 0x0000,  // 206 :: rgb(0,0,0)
 0x0000,  // 207 :: rgb(0,0,0)
 0x0000,  // 208 :: rgb(0,0,0)
 0x0000,  // 209 :: rgb(0,0,0)
 0x0000,  // 210 :: rgb(0,0,0)
 0x0000,  // 211 :: rgb(0,0,0)
 0x0000,  // 212 :: rgb(0,0,0)
 0x0000,  // 213 :: rgb(0,0,0)
 0x0000,  // 214 :: rgb(0,0,0)
 0x0000,  // 215 :: rgb(0,0,0)
 0x0000,  // 216 :: rgb(0,0,0)
 0x0000,  // 217 :: rgb(0,0,0)
 0x0000,  // 218 :: rgb(0,0,0)
 0x0000,  // 219 :: rgb(0,0,0)
 0x0000,  // 220 :: rgb(0,0,0)
 0x0000,  // 221 :: rgb(0,0,0)
 0x0000,  // 222 :: rgb(0,0,0)
 0x0000,  // 223 :: rgb(0,0,0)
 0x0000,  // 224 :: rgb(0,0,0)
 0x0000,  // 225 :: rgb(0,0,0)
 0x0000,  // 226 :: rgb(0,0,0)
 0x0000,  // 227 :: rgb(0,0,0)
 0x0000,  // 228 :: rgb(0,0,0)
 0x0000,  // 229 :: rgb(0,0,0)
 0x0000,  // 230 :: rgb(0,0,0)
 0x0000,  // 231 :: rgb(0,0,0)
 0x0000,  // 232 :: rgb(0,0,0)
 0x0000,  // 233 :: rgb(0,0,0)
 0x0000,  // 234 :: rgb(0,0,0)
 0x0000,  // 235 :: rgb(0,0,0)
 0x0000,  // 236 :: rgb(0,0,0)
 0x0000,  // 237 :: rgb(0,0,0)
 0x0000,  // 238 :: rgb(0,0,0)
 0x0000,  // 239 :: rgb(0,0,0)
 0x0000,  // 240 :: rgb(0,0,0)
 0x0000,  // 241 :: rgb(0,0,0)
 0x0000,  // 242 :: rgb(0,0,0)
 0x0000,  // 243 :: rgb(0,0,0)
 0x0000,  // 244 :: rgb(0,0,0)
 0x0000,  // 245 :: rgb(0,0,0)
 0x0000,  // 246 :: rgb(0,0,0)
 0x0000,  // 247 :: rgb(0,0,0)
 0xFFFF,  // 248 :: rgb(255,255,255)
 0x4C13,  // 249 :: rgb(153,1,153)
 0x74E3,  // 250 :: rgb(239,56,24)
 0x001F,  // 251 :: rgb(0,0,255)
 0xD62B,  // 252 :: rgb(176,141,87)
 0xDEF7,  // 253 :: rgb(192,192,192)
 0x6F8B,  // 254 :: rgb(225,227,89)
 0xBDEF,  // 255 :: rgb(127,127,127)
};
