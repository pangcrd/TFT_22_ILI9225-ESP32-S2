// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 8.3.11
// Project name: PowerMonitor

#include "ui.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
    #define LV_ATTRIBUTE_MEM_ALIGN
#endif

// IMAGE DATA: assets/voltnone 1.png
const LV_ATTRIBUTE_MEM_ALIGN uint8_t ui_img_voltnone_1_png_data[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x04,0x02,0xFF,0x06,0x10,0x9E,0x06,0x11,0x5F,0x05,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x06,0x12,0xBD,0x06,0x4F,0xBD,0x06,0x7D,0xBE,0x06,0x7B,0xBD,0x06,0x4F,0xBA,0x06,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5D,0x06,0x0E,0x9D,0x06,0x72,0x9E,0x06,0x99,
    0x9D,0x06,0x50,0x9E,0x06,0x57,0x9E,0x06,0x99,0x9D,0x06,0x62,0x3F,0x06,0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x9D,0x06,0x31,0x7D,0x06,0x9D,0x7D,0x06,0x37,0x00,0x00,0x00,0xFF,0x07,0x03,0x9D,0x06,0x3C,0x7E,0x06,0x9A,0x9D,0x06,0x31,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x9E,0x06,0x11,0x3D,0x06,0x89,0x5E,0x06,0x5D,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5E,0x06,0x76,0x5D,0x06,0x99,0xFF,0x07,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1D,0x06,0x4A,0x3D,0x06,0xAA,0x5E,0x06,0x13,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x9E,0x06,0x16,0x3D,0x06,0xA9,0xFD,0x05,0x3B,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFD,0x05,0x10,0x1E,0x06,0xA3,0xFD,0x05,0x4C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFD,0x05,0x4C,0x1E,0x06,0xAF,0xBB,0x05,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x05,0x70,0xDD,0x05,0x92,0x5F,0x05,0x06,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,0x05,0x06,0xFE,0x05,0x98,0xDD,0x05,0x62,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xBD,0x05,0x2A,0xBE,0x05,0xA8,0xBE,0x05,0x34,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x9D,0x05,0x36,0xBE,0x05,0xA6,0xBD,0x05,0x2A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x05,0x08,0x9E,0x05,0x7A,0x9E,0x05,0x6D,0x5F,0x05,0x06,0x00,0x00,0x00,0x7D,0x05,0x10,0x9E,0x05,0x28,0x7D,0x05,0x30,0x7D,0x05,0x30,0x7D,0x05,0x30,0x9E,0x05,0x2D,0x9F,0x05,0x0A,0xFF,0x05,0x0C,0x9D,0x05,0x7C,0x9E,0x05,0x7A,0xBF,0x05,0x07,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x07,0x01,0x7D,0x05,0x47,0x7E,0x05,0x9A,0x3E,0x05,0x23,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x05,0x5A,0x7E,0x05,0xA3,0x7E,0x05,0x8D,0x7E,0x05,0x8C,0x9E,0x05,0xA1,0x7E,0x05,0xA9,0x7E,0x05,0x26,0x00,0x00,0x00,0x9D,0x05,0x34,0x7E,0x05,0x9A,0x7E,0x05,0x32,0xFF,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x9F,0x05,0x0A,0x5D,0x05,0x84,0x5D,0x05,0x6F,0xFB,0x04,0x08,0x00,0x00,0x00,0x9C,0x05,0x0A,0x5E,0x05,0x85,0x5E,0x05,0x74,0x3E,0x05,0x23,0x5E,0x05,0x24,0x5D,0x05,0x73,0x5E,0x05,0x86,0x5E,0x05,0x15,0x00,0x00,0x00,0xFB,0x04,0x08,0x5D,0x05,0x6F,0x5D,0x05,0x80,0x9F,0x05,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5E,0x05,0x3B,0x3E,0x05,0xA8,0x3D,0x05,0x1A,0x00,0x00,0x00,
    0x00,0x00,0x00,0x3E,0x05,0x1F,0x3D,0x05,0x90,0x3D,0x05,0x41,0x00,0x00,0x00,0x5E,0x05,0x1B,0x3E,0x05,0x88,0x3D,0x05,0x4C,0x1F,0x04,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x3D,0x05,0x1A,0x3E,0x05,0xC2,0x3E,0x05,0x36,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFD,0x04,0x0D,0x1D,0x05,0xBC,0x1D,0x05,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFD,0x04,0x39,0x1E,0x05,0x8D,0x1C,0x05,0x19,0x00,0x00,0x00,0xFD,0x04,0x42,0xFE,0x04,0xAB,0x1E,0x05,0x2C,0xBD,0x04,0x16,0xDF,0x04,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x1D,0x05,0x50,0x1E,0x05,0x9A,0x5D,0x04,0x0D,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x04,0x60,0xDE,0x04,0xA4,0xDF,0x04,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x9B,0x04,0x07,0xFD,0x04,0x58,0xFE,0x04,0x79,0xFF,0x05,0x04,0x00,0x00,0x00,0xFE,0x04,0x6D,0xDE,0x04,0xBA,0xDD,0x04,0x8E,0xDE,0x04,0x81,0x9F,0x04,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,
    0x1A,0x04,0x06,0xDE,0x04,0xA1,0xDE,0x04,0x57,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xDD,0x04,0x28,0xBE,0x04,0xAB,0xBE,0x04,0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7D,0x04,0x10,0xBD,0x04,0x8D,0xBE,0x04,0x65,0xDD,0x04,0x1E,0xDD,0x04,0x1E,0xDE,0x04,0x2E,0xDD,0x04,0x60,0xBE,0x04,0xC5,0xDE,0x04,0x74,0x1F,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xDE,0x04,0x35,0xBD,0x04,0xB2,0xDD,0x04,0x21,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,0x05,0x03,0x9E,0x04,0x7E,0x9E,0x04,0x80,0x1F,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x9D,0x04,0x17,0x9D,0x04,0xC4,0x9E,0x04,0xC1,0x9E,0x04,0xB6,0x9D,0x04,0xC3,0x9F,0x04,0x0E,0x9E,0x04,0x67,0x9D,0x04,0x93,0xBE,0x04,0x1B,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x04,0x12,0x9D,0x04,0x80,0x9E,0x04,0x6A,0x1F,0x04,0x04,0x00,0x00,0x00,0x1F,0x04,0x02,0x7E,0x04,0x3D,0x7D,0x04,0xA1,0x9E,0x04,0x2C,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x9D,0x04,0x35,0x7D,0x04,0xB2,0x7E,0x04,0x50,0x7E,0x04,0xA9,0x7D,0x04,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x04,0x24,0x7E,0x04,0x9C,0x7D,0x04,0x3D,0x00,0x00,0x00,0x5D,0x04,0x1A,0x5E,0x04,0x87,0x7E,0x04,0x5D,0x9F,0x04,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5D,0x04,0x5F,0x5E,0x04,0xAF,0x5E,0x04,0xA7,0x5D,0x04,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x39,0x03,0x05,0x5E,0x04,0x72,0x5E,0x04,0x87,0x5D,0x04,0x0D,0x3E,0x04,0x4B,0x3E,0x04,0x9E,0x7E,0x04,0x1D,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x04,0x82,0x3E,0x04,0xE4,0x3E,0x04,0x57,0x1F,0x04,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5E,0x04,0x27,0x3E,0x04,0x9E,0xFD,0x03,0x36,0x1D,0x04,0x8E,0x1D,0x04,0x5B,0xFF,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xBD,0x03,0x0B,0x1D,0x04,0xA4,0x1D,0x04,0x83,0x1A,0x04,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x04,0x02,0x1E,0x04,0x60,0x1E,0x04,0x86,0xFE,0x03,0xB1,0xFD,0x03,0x23,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1E,0x04,0x24,0xFD,0x03,0x65,0x1E,0x04,0x16,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xBD,0x03,0x20,0xFD,0x03,0xC5,0xDE,0x03,0xA7,0xDE,0x03,0x42,0x1F,0x00,0x01,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xDE,0x03,0x13,0xBD,0x03,0x0D,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x01,0xBD,0x03,0x3A,0xDE,0x03,0xB9,0xBE,0x03,0x61,0x9E,0x03,0x9D,0x9D,0x03,0x59,0x9D,0x03,0x42,0x9D,0x03,0x40,0x9D,0x03,0x40,0x9D,0x03,0x40,0x9D,0x03,0x40,0x9D,0x03,0x40,0x9D,0x03,0x40,0x9D,0x03,0x40,0x9D,0x03,0x40,0x9D,0x03,0x40,0x9D,0x03,0x40,0x9D,0x03,0x40,0x9D,0x03,0x40,0x9D,0x03,0x40,0x9D,0x03,0x40,0x9D,0x03,0x40,0x9D,0x03,0x40,0x9D,0x03,0x40,0x9D,0x03,0x40,0x7D,0x03,0x43,0x9D,0x03,0x5E,0x9E,0x03,0x9D,0xBE,0x03,0x53,0x1D,0x03,0x0D,0x7E,0x03,0x58,0x7D,0x03,0x81,0x9D,0x03,0x8F,0x9D,0x03,0x8F,0x9D,0x03,0x8F,0x9D,0x03,0x8F,0x9D,0x03,0x8F,0x9D,0x03,0x8F,0x9D,0x03,0x8F,0x9D,0x03,0x8F,0x9D,0x03,0x8F,0x9D,0x03,0x8F,0x9D,0x03,0x8F,0x9D,0x03,0x8F,0x9D,0x03,0x8F,
    0x9D,0x03,0x8F,0x9D,0x03,0x8F,0x9D,0x03,0x8F,0x9D,0x03,0x8F,0x9D,0x03,0x8F,0x9D,0x03,0x8F,0x7E,0x03,0x8C,0x9D,0x03,0x82,0x7E,0x03,0x58,0x1D,0x03,0x0D,0x00,0x00,0x00,0x1F,0x04,0x04,0x5D,0x03,0x0C,0x5E,0x03,0x11,0x5E,0x03,0x13,0x5E,0x03,0x13,0x5E,0x03,0x13,0x5E,0x03,0x13,0x5E,0x03,0x13,0x5E,0x03,0x13,0x5E,0x03,0x13,0x5E,0x03,0x13,0x5E,0x03,0x13,0x5E,0x03,0x13,0x5E,0x03,0x13,0x5E,0x03,0x13,0x5E,0x03,0x13,0x5E,0x03,0x13,0x5E,0x03,0x13,0x5E,0x03,0x13,0x5E,0x03,0x13,0x5E,0x03,0x13,0x5E,0x03,0x13,0x5D,0x03,0x0C,0x1F,0x04,0x04,0x00,0x00,0x00,
};
const lv_img_dsc_t ui_img_voltnone_1_png = {
    .header.always_zero = 0,
    .header.w = 26,
    .header.h = 26,
    .data_size = sizeof(ui_img_voltnone_1_png_data),
    .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
    .data = ui_img_voltnone_1_png_data
};
