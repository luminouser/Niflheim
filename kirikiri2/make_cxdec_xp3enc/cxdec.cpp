#include <windows.h>
#include "cxdec.h"
#include "tp_stub.h"

//#pragma comment(linker, "/align:512")
#ifndef _DEBUG
//#pragma comment(linker, "/merge:.data=.text")
#pragma comment(linker, "/merge:.rdata=.text")
#endif

#define ONI_GOKKOKEY1 0x17b
#define ONI_GOKKOKEY2 0x35a

static int xcode_building_stage0(struct cxdec_xcode_status *xcode, int stage);
static int xcode_building_stage1(struct cxdec_xcode_status *xcode, int stage);

const unsigned char EncryptionControlBlock[4096] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA6, 0xEA, 0xB8, 0xCE, 0xC1,
	0x85, 0xCE, 0x00, 0xD0, 0xBB, 0xC3, 0x90, 0xD3, 0xA5, 0xAD, 0x8A, 0xC0, 0x9C, 0xC5, 0x91, 0xD1,
	0x90, 0xD1, 0xE5, 0xC7, 0xF8, 0xA2, 0x85, 0xC3, 0x23, 0xAC, 0x2F, 0xCB, 0xE1, 0xCA, 0x90, 0xD1,
	0x8D, 0xD0, 0xAF, 0xD1, 0xAC, 0xD3, 0x14, 0x4F, 0xC5, 0x5B, 0x85, 0xA6, 0x10, 0x0B, 0x00, 0x26,
	0x62, 0xB8, 0x15, 0x90, 0x02, 0xD1, 0x00, 0x13, 0x13, 0xBF, 0x13, 0x1B, 0x03, 0xB1, 0x01, 0xBA,
	0x03, 0x93, 0x01, 0xFA, 0x09, 0x82, 0x15, 0xC7, 0x15, 0x0D, 0x00, 0x78, 0x03, 0xBE, 0x03, 0xB6,
	0x03, 0x92, 0xA1, 0x2F, 0x7A, 0x66, 0xF4, 0xC4, 0xEC, 0xCA, 0x00, 0x14, 0x0F, 0x05, 0x12, 0x0B,
	0x12, 0x11, 0x08, 0xAF, 0x03, 0x88, 0x10, 0xA4, 0x11, 0x07, 0x1A, 0xDA, 0x00, 0x0F, 0x00, 0x7D,
	0x00, 0x05, 0x0E, 0x06, 0x0D, 0x19, 0x13, 0x69, 0x0D, 0x26, 0x0A, 0x06, 0x0F, 0xAC, 0x1E, 0xE7,
	0x00, 0x21, 0x03, 0x8A, 0x88, 0x65, 0x5C, 0x2B, 0x72, 0x4D, 0x4F, 0x40, 0x60, 0x21, 0x79, 0x25,
	0xCB, 0x4B, 0x42, 0x4F, 0xEE, 0x28, 0x5B, 0x71, 0x61, 0x5F, 0xF1, 0x4B, 0xC7, 0x4F, 0x34, 0xDA,
	0xC0, 0xE6, 0xA8, 0x1B, 0xCF, 0x17, 0x02, 0x0F, 0x41, 0x15, 0x77, 0x00, 0x74, 0x00, 0xEC, 0x00,
	0x26, 0x0E, 0x78, 0x0A, 0x38, 0x00, 0x19, 0x0F, 0x77, 0x00, 0x10, 0x00, 0x43, 0x00, 0x29, 0x00,
	0x0B, 0x00, 0x26, 0x00, 0x75, 0x03, 0xE0, 0x88, 0xA0, 0x08, 0x87, 0x13, 0x0D, 0x00, 0x12, 0x16,
	0x72, 0x14, 0xCE, 0x17, 0x58, 0x08, 0x71, 0x1F, 0x0F, 0x10, 0x33, 0x00, 0x7A, 0x00, 0x6C, 0x00,
	0x57, 0x16, 0x38, 0x0A, 0x3D, 0x00, 0x09, 0x00, 0x10, 0x00, 0x03, 0x03, 0xAA, 0x00, 0x1F, 0x03,
	0x8E, 0x00, 0x33, 0x05, 0xC6, 0x00, 0x04, 0x13, 0x50, 0x00, 0x08, 0x00, 0x23, 0x00, 0x57, 0x00,
	0x78, 0x00, 0x4E, 0x03, 0xF7, 0x88, 0x25, 0x01, 0x48, 0xC0, 0xE0, 0x68, 0x5E, 0xC3, 0x67, 0xED,
	0x4F, 0x28, 0x43, 0xC7, 0x55, 0xD3, 0x4F, 0x31, 0x68, 0x68, 0x2D, 0x68, 0xD9, 0x04, 0x6B, 0xC3,
	0x3A, 0xC9, 0x64, 0x02, 0x2D, 0x4B, 0x79, 0x24, 0x68, 0x32, 0x4F, 0x3F, 0x7A, 0x64, 0x4F, 0x47,
	0x4F, 0x62, 0x7F, 0x48, 0x5D, 0x4E, 0x64, 0x61, 0x57, 0x48, 0x65, 0x6C, 0xE7, 0x32, 0x44, 0x40,
	0x2C, 0xE8, 0x20, 0x44, 0x59, 0x1A, 0x21, 0x74, 0x66, 0xC3, 0x4B, 0x18, 0xC5, 0x08, 0x30, 0x08,
	0x5A, 0x00, 0x0E, 0x0D, 0x22, 0x10, 0x38, 0x16, 0x0C, 0x06, 0x6C, 0x00, 0x62, 0x0F, 0xA7, 0x0C,
	0x41, 0x00, 0x4D, 0x0B, 0x2D, 0x86, 0xEF, 0x16, 0x12, 0x00, 0x74, 0x00, 0x6F, 0x10, 0xDB, 0x00,
	0x6D, 0x01, 0xA1, 0x01, 0x82, 0x01, 0xB0, 0x00, 0x45, 0x11, 0x17, 0x00, 0x6A, 0x15, 0x1A, 0x00,
	0x08, 0x00, 0x70, 0x03, 0xFF, 0x88, 0xBF, 0x0C, 0x36, 0x0A, 0x26, 0x0C, 0xE3, 0x06, 0x5A, 0x10,
	0x0E, 0x16, 0x42, 0x0A, 0x5E, 0x00, 0x71, 0x0A, 0x6D, 0x0C, 0x44, 0x00, 0x69, 0x16, 0x5B, 0x03,
	0xB3, 0x14, 0x40, 0x00, 0x6F, 0x15, 0x02, 0x16, 0xDF, 0x98, 0x08, 0x2B, 0x5C, 0x28, 0x33, 0x28,
	0x73, 0x45, 0x4A, 0x26, 0x33, 0x4A, 0x44, 0x43, 0x72, 0x31, 0x79, 0x5D, 0x14, 0x2B, 0x43, 0x62,
	0x3F, 0x6C, 0xC0, 0xA3, 0x03, 0x92, 0x08, 0x16, 0x10, 0x12, 0x17, 0x69, 0x02, 0x76, 0x00, 0x16,
	0x00, 0x70, 0x0E, 0x64, 0x03, 0xF4, 0x0F, 0x19, 0x01, 0x55, 0x00, 0x2D, 0xA2, 0x9B, 0xBF, 0xD3,
	0x0B, 0x77, 0x00, 0x41, 0x00, 0x2E, 0x03, 0x85, 0x16, 0x1E, 0x17, 0x17, 0x03, 0xEF, 0x88, 0xED,
	0x03, 0xD7, 0x03, 0x28, 0x00, 0x78, 0x12, 0xA6, 0x13, 0x71, 0x00, 0x36, 0x0D, 0x2C, 0x17, 0x9F,
	0x00, 0x6A, 0x03, 0x85, 0x62, 0xDD, 0x16, 0x73, 0x01, 0x90, 0x02, 0xD2, 0x0D, 0x52, 0x0F, 0xA9,
	0x00, 0x29, 0x0C, 0x24, 0x11, 0x39, 0x0C, 0xF6, 0x12, 0x85, 0x00, 0x28, 0x00, 0x18, 0x03, 0xBF,
	0x88, 0x5B, 0xEE, 0x20, 0x4F, 0x2B, 0x22, 0x4A, 0x6F, 0x20, 0x45, 0xC0, 0xCE, 0x16, 0xFF, 0x1B,
	0xD3, 0x00, 0x3C, 0x0F, 0x3D, 0x00, 0x12, 0x03, 0xD0, 0x03, 0xDA, 0x17, 0xDD, 0x1A, 0x5E, 0x0D,
	0x5E, 0x10, 0x9C, 0x09, 0xCF, 0x00, 0x35, 0x00, 0x75, 0x00, 0x03, 0x03, 0xEB, 0x14, 0x62, 0x00,
	0x06, 0x08, 0xDE, 0x0D, 0xAF, 0x0F, 0xDF, 0x9F, 0xA0, 0x00, 0x11, 0x15, 0x0A, 0x15, 0x59, 0x03,
	0xB1, 0x0A, 0x31, 0x0C, 0x70, 0x00, 0x43, 0x0C, 0x5F, 0x00, 0x0F, 0x14, 0x35, 0x00, 0x08, 0x00,
	0x71, 0x0C, 0x37, 0x16, 0xDC, 0x1D, 0x0C, 0x0A, 0x5A, 0x00, 0x66, 0x08, 0x11, 0x00, 0x6E, 0x01,
	0x9E, 0x01, 0xC6, 0x01, 0xA0, 0x17, 0x90, 0x00, 0x0D, 0x00, 0x77, 0x00, 0x63, 0x00, 0x00, 0x03,
	0xE8, 0x8B, 0xD0, 0x4E, 0x39, 0x4B, 0x65, 0x15, 0x4A, 0x5A, 0x0A, 0x49, 0xC3, 0x39, 0x5F, 0xCE,
	0x02, 0x1C, 0x4E, 0x41, 0x30, 0x3E, 0xE1, 0x28, 0x4F, 0x5B, 0x1F, 0x69, 0x72, 0x59, 0xF1, 0x51,
	0xDE, 0x4F, 0x4B, 0x4A, 0x4A, 0x20, 0x42, 0xEA, 0x3E, 0x0D, 0xC1, 0x52, 0x88, 0x3E, 0x49, 0xFF,
	0x1F, 0x51, 0x4F, 0x3F, 0x3C, 0x68, 0x43, 0x46, 0x46, 0x20, 0x20, 0x6B, 0x68, 0xC0, 0xBB, 0x88,
	0x44, 0x39, 0x28, 0x44, 0x59, 0x4F, 0x23, 0x50, 0xFE, 0x52, 0x37, 0x6D, 0x4A, 0x37, 0x3C, 0x3F,
	0x2D, 0x4E, 0x47, 0x4C, 0xC0, 0xCF, 0xF4, 0x2D, 0xEE, 0x42, 0x26, 0x72, 0x44, 0x48, 0x43, 0x6F,
	0x4D, 0x32, 0x44, 0x4E, 0x72, 0xE8, 0x49, 0xC0, 0xEC, 0x16, 0x7A, 0x00, 0x05, 0x03, 0x8D, 0x16,
	0x39, 0x09, 0xDE, 0x0F, 0x0C, 0x01, 0x06, 0x00, 0x04, 0x0D, 0xFA, 0x00, 0x02, 0x00, 0x0E, 0x14,
	0xC8, 0x14, 0x5D, 0x09, 0xF5, 0x03, 0x88, 0x12, 0x21, 0x03, 0x9C, 0x00, 0x6E, 0x16, 0x39, 0x11,
	0x1B, 0x03, 0x8A, 0x0F, 0x93, 0x0A, 0x11, 0x00, 0x10, 0x0E, 0x8C, 0x0A, 0x28, 0x00, 0x7C, 0x00,
	0x09, 0x00, 0x4F, 0x00, 0x43, 0x03, 0x88, 0x00, 0x0E, 0x00, 0x4B, 0x03, 0xE6, 0x88, 0xC6, 0x10,
	0x37, 0x00, 0x13, 0x00, 0x03, 0x00, 0x21, 0x0C, 0xAE, 0x00, 0x72, 0x00, 0x47, 0x03, 0xAA, 0x02,
	0x77, 0x14, 0x00, 0x00, 0x27, 0x08, 0xBC, 0x15, 0x00, 0x00, 0x77, 0x00, 0x48, 0x03, 0x8A, 0x1F,
	0x76, 0x00, 0x64, 0x00, 0x59, 0x00, 0x5F, 0x00, 0x22, 0x07, 0xF7, 0x15, 0x70, 0x12, 0x59, 0x14,
	0x0F, 0x03, 0xAF, 0x17, 0x2B, 0x14, 0x67, 0x01, 0xDB, 0x01, 0x34, 0x01, 0xA4, 0x01, 0x82, 0x03,
	0xAA, 0x08, 0xA5, 0x0F, 0xF5, 0x10, 0x11, 0x9E, 0xC0, 0x00, 0x4B, 0x00, 0x57, 0x00, 0x23, 0x03,
	0xF8, 0x0A, 0x17, 0x0C, 0x0D, 0x00, 0x19, 0x0C, 0x17, 0x00, 0x56, 0x14, 0x76, 0x00, 0x52, 0x0B,
	0x62, 0x17, 0x4F, 0x0B, 0x7C, 0x03, 0xEB, 0x16, 0x55, 0x0A, 0x36, 0x00, 0x0C, 0x08, 0x1D, 0x00,
	0x25, 0x01, 0xB4, 0x01, 0xAF, 0x16, 0xC2, 0x00, 0x65, 0x0D, 0x22, 0x00, 0x0D, 0x00, 0x00, 0x00,
	0x54, 0x00, 0x00, 0x00, 0x9A, 0xE5, 0x57, 0x4E, 0x4F, 0x45, 0x31, 0x1F, 0x43, 0x4F, 0x46, 0x4A,
	0x62, 0x2C, 0xE2, 0xC0, 0xF6, 0x1F, 0xE1, 0x4C, 0xCC, 0x3E, 0x2A, 0x3D, 0x1F, 0x5E, 0x04, 0x62,
	0x4B, 0x4D, 0xF7, 0x47, 0x47, 0x4F, 0x62, 0x46, 0x6A, 0x20, 0x63, 0xEB, 0xEF, 0x0F, 0xEC, 0xDB,
	0xEE, 0x29, 0xF8, 0xF1, 0xE8, 0x51, 0x40, 0x31, 0x20, 0x68, 0x47, 0x46, 0x4B, 0x2C, 0xC1, 0x6B,
	0x40, 0xC0, 0xB7, 0x89, 0xCF, 0x38, 0xD7, 0x4F, 0xC7, 0x5A, 0xD7, 0x46, 0xF5, 0xDF, 0x08, 0xDF,
	0xC2, 0xDF, 0xF1, 0xDF, 0x12, 0xDE, 0x61, 0xDF, 0x66, 0x68, 0x84, 0x4C, 0x9E, 0x49, 0x50, 0xFB,
	0xF8, 0xBA, 0x5D, 0x8A, 0x00, 0x9C, 0xEC, 0xEF, 0x30, 0x83, 0x74, 0x84, 0x1F, 0x01, 0x78, 0x53,
	0x65, 0xF9, 0x8E, 0x0B, 0x84, 0x11, 0x03, 0xD3, 0x9D, 0x50, 0x1A, 0x28, 0x95, 0x08, 0x33, 0xDC,
	0xD2, 0x28, 0xAB, 0x56, 0x0E, 0x6E, 0x67, 0x52, 0x84, 0x3A, 0xFC, 0x98, 0x8C, 0x3A, 0x68, 0xAB,
	0x74, 0x13, 0xF6, 0x57, 0xA3, 0x6A, 0x7F, 0x4D, 0xAB, 0x69, 0xD3, 0x9B, 0x62, 0x25, 0x1D, 0x1D,
	0xE5, 0xBB, 0x10, 0x74, 0xA5, 0xA1, 0xA7, 0x10, 0x5F, 0xB8, 0xE7, 0x0F, 0x71, 0x1E, 0x90, 0xE2,
	0xDE, 0x9E, 0x9C, 0xAA, 0xAA, 0xF9, 0x2D, 0x0E, 0x9E, 0x2D, 0xF3, 0xDA, 0xB7, 0x37, 0x56, 0x55,
	0x64, 0x90, 0xE8, 0x44, 0x16, 0xC1, 0xB4, 0xA8, 0xFF, 0x7D, 0xEC, 0x38, 0x66, 0x76, 0x8E, 0x07,
	0xDF, 0xC0, 0xB2, 0x14, 0x45, 0x32, 0x2A, 0x5D, 0x17, 0xB0, 0xF2, 0x51, 0xAF, 0xE6, 0x13, 0xAC,
	0x92, 0xFE, 0xF1, 0x6E, 0x92, 0xEB, 0xCE, 0xA6, 0x3F, 0xBE, 0xC0, 0xE5, 0x7A, 0x96, 0x45, 0x62,
	0x33, 0xBE, 0x02, 0xB1, 0x77, 0x8C, 0x9D, 0x20, 0xA2, 0xE8, 0x8A, 0x71, 0x7E, 0xB4, 0xB8, 0x73,
	0x92, 0xFB, 0x74, 0xF3, 0xF2, 0x87, 0x59, 0x09, 0x23, 0x44, 0x67, 0xF7, 0xD0, 0x22, 0x5E, 0x58,
	0x9E, 0xC4, 0x77, 0x95, 0xE7, 0xEE, 0xD7, 0xD6, 0x8F, 0xDB, 0xBA, 0x66, 0xBD, 0x72, 0x09, 0x74,
	0x10, 0xB6, 0x13, 0x9D, 0xB7, 0x95, 0xAB, 0x13, 0xE7, 0xC1, 0x6D, 0x4D, 0xAE, 0x83, 0x1F, 0xE4,
	0xCB, 0x21, 0xFA, 0xA2, 0xE1, 0x20, 0x7A, 0xFD, 0x8B, 0xEE, 0xAC, 0xBC, 0x21, 0x1A, 0x8A, 0xA7,
	0x0F, 0xF0, 0xA4, 0x22, 0x2D, 0xAA, 0x4A, 0xFC, 0x07, 0x6A, 0xEF, 0x9D, 0x73, 0xE5, 0x42, 0x17,
	0xAD, 0x75, 0x6E, 0x11, 0x0A, 0x25, 0x58, 0xC2, 0xEE, 0x4B, 0xC5, 0xE6, 0x45, 0x0C, 0xE6, 0xB2,
	0xDE, 0xBF, 0x59, 0xA0, 0xF1, 0x3B, 0x27, 0xCC, 0xB9, 0x76, 0xC8, 0xA5, 0x8D, 0x49, 0xC1, 0xFD,
	0xBF, 0x42, 0x4E, 0xD3, 0xC4, 0x65, 0xA7, 0xD1, 0x80, 0x4A, 0x8B, 0x87, 0x77, 0x42, 0x89, 0xD1,
	0xC6, 0xBB, 0x35, 0x16, 0xF5, 0xC3, 0x64, 0x08, 0x02, 0xA5, 0x3A, 0xEE, 0xD3, 0x4A, 0xBB, 0x5E,
	0x3D, 0xB2, 0x66, 0xC8, 0x04, 0xAE, 0x7E, 0xF8, 0xD6, 0x6C, 0xE5, 0x4F, 0x7F, 0xFE, 0x36, 0xD8,
	0xDF, 0x8C, 0x5D, 0xC9, 0x6A, 0x3D, 0x93, 0x63, 0x74, 0x26, 0xCA, 0xC5, 0x2E, 0x50, 0x93, 0x71,
	0xFD, 0xB7, 0xE7, 0x26, 0x61, 0xE8, 0x47, 0x91, 0xC3, 0x01, 0x06, 0xE3, 0x6D, 0xB8, 0x16, 0x3E,
	0x5A, 0x6B, 0xBD, 0x6C, 0x58, 0x7B, 0x97, 0xA0, 0x00, 0xA4, 0x9A, 0x74, 0x02, 0x42, 0x7D, 0xDF,
	0x7F, 0x83, 0x41, 0x3D, 0xEE, 0x40, 0x15, 0xC2, 0xF1, 0xEE, 0x68, 0xB9, 0x7F, 0xD4, 0x84, 0x5B,
	0xF0, 0xBE, 0x68, 0xE5, 0x4F, 0x06, 0xE2, 0x07, 0x10, 0x40, 0x43, 0xEB, 0x91, 0x67, 0x04, 0xDB,
	0x9E, 0xE7, 0x1F, 0x4C, 0x0D, 0x1E, 0x12, 0x3C, 0xE1, 0x68, 0xF3, 0xA8, 0x66, 0x43, 0xC5, 0xE5,
	0x8C, 0x0A, 0x38, 0xEA, 0xFF, 0x6C, 0xA0, 0x71, 0x38, 0x84, 0xC3, 0x0C, 0xD7, 0x93, 0x0E, 0x12,
	0x2B, 0xD1, 0x6B, 0xDB, 0xDD, 0x8B, 0x3F, 0xB3, 0x57, 0xB4, 0xEB, 0x7E, 0x5C, 0xB9, 0x94, 0xBB,
	0x54, 0x91, 0x39, 0x34, 0xCF, 0x6E, 0xF5, 0x86, 0xEF, 0xB1, 0x77, 0x29, 0x87, 0xAE, 0xF5, 0x25,
	0xC5, 0xDF, 0x58, 0x59, 0x2F, 0x69, 0x3C, 0x35, 0x3B, 0x95, 0xA1, 0x68, 0x48, 0x79, 0xCF, 0x88,
	0xAA, 0xAB, 0xA1, 0xBF, 0xB0, 0xF1, 0x13, 0xB8, 0x3F, 0x75, 0x0C, 0x32, 0x65, 0x31, 0x7B, 0x8D,
	0xA9, 0xA3, 0x2C, 0x8B, 0x81, 0x77, 0x87, 0x91, 0x64, 0x76, 0xA4, 0x6F, 0x93, 0xBE, 0xB1, 0xBC,
	0x4E, 0x65, 0x70, 0x81, 0x89, 0x7B, 0x29, 0x71, 0xDB, 0x4A, 0x0B, 0x34, 0x90, 0xC0, 0xC0, 0xC1,
	0x5C, 0x55, 0x24, 0x8A, 0x8A, 0x38, 0xA7, 0xAC, 0x8F, 0xB4, 0x68, 0xF1, 0xD3, 0x79, 0x0E, 0x16,
	0x10, 0x10, 0xB0, 0x44, 0x65, 0xD0, 0xB3, 0xD8, 0x68, 0xF4, 0x90, 0x1F, 0x1D, 0x1D, 0x3C, 0x96,
	0x81, 0x47, 0x67, 0x75, 0x9F, 0x42, 0xFF, 0x98, 0x92, 0xF2, 0xCA, 0x98, 0x1A, 0xB4, 0x59, 0xE7,
	0x06, 0x2D, 0xC4, 0x27, 0x61, 0x28, 0x2B, 0xFC, 0x29, 0x67, 0xA8, 0xC8, 0xB1, 0x7A, 0x02, 0xC3,
	0x7B, 0x05, 0x0A, 0xF9, 0x08, 0xE3, 0x1C, 0x52, 0x76, 0xB6, 0x26, 0x77, 0xBE, 0x02, 0xF6, 0x24,
	0xA4, 0xBE, 0x59, 0x4C, 0xDE, 0x77, 0xA2, 0xC3, 0x90, 0x10, 0xF9, 0xC7, 0x13, 0xAA, 0xE9, 0x03,
	0x58, 0x8E, 0x9D, 0x92, 0xB7, 0xFE, 0xD1, 0xC0, 0xF6, 0xDB, 0xE5, 0x83, 0xF3, 0x36, 0x73, 0xCD,
	0x06, 0x04, 0xD9, 0x55, 0x7A, 0xC6, 0x51, 0x27, 0x98, 0x23, 0xCD, 0xE8, 0x32, 0x91, 0x68, 0x2C,
	0x32, 0x3D, 0x22, 0xDE, 0x2B, 0x2F, 0xA6, 0xDB, 0xD6, 0xE9, 0xBE, 0xC9, 0xEA, 0xE9, 0x2F, 0xD3,
	0xBC, 0x22, 0x98, 0x83, 0x70, 0x29, 0xEA, 0xEC, 0xDA, 0xC5, 0x93, 0x8C, 0xC8, 0x72, 0xF2, 0x0C,
	0xFB, 0x31, 0x9A, 0xFF, 0x38, 0xF3, 0x83, 0x26, 0x05, 0x90, 0x49, 0x70, 0xA3, 0x36, 0x35, 0x6A,
	0x79, 0x78, 0x0A, 0xE2, 0xFF, 0x8E, 0xE2, 0x84, 0x20, 0xD0, 0x3B, 0x03, 0x92, 0xB5, 0xFC, 0x87,
	0x23, 0x70, 0xE8, 0x1E, 0x81, 0x56, 0x1E, 0xED, 0x35, 0x99, 0x99, 0xB0, 0x7B, 0x7A, 0x42, 0x50,
	0x0F, 0xB7, 0x70, 0x9C, 0xD3, 0x2B, 0x32, 0x9D, 0x16, 0xBA, 0xBD, 0xB3, 0x38, 0x60, 0xFA, 0x69,
	0x4C, 0x69, 0x02, 0x34, 0x0C, 0xED, 0x99, 0x18, 0xB9, 0x6F, 0x16, 0xA7, 0x19, 0x69, 0xA9, 0x0B,
	0xA5, 0xDE, 0xFA, 0x79, 0x16, 0x15, 0x70, 0xD1, 0x46, 0xB5, 0xDB, 0x1A, 0x10, 0x5D, 0x0B, 0xDC,
	0xB3, 0x78, 0xB4, 0xA7, 0xBC, 0xCC, 0xC5, 0x2F, 0x16, 0xF9, 0x83, 0x47, 0x77, 0x95, 0xF5, 0x53,
	0x74, 0xA7, 0xD0, 0xCB, 0x4E, 0xF7, 0x59, 0x9D, 0x21, 0x75, 0x39, 0x60, 0x46, 0xF1, 0xC4, 0x3F,
	0x45, 0x72, 0xD1, 0xA4, 0x28, 0xD1, 0x7D, 0x76, 0x34, 0x6E, 0x93, 0xB5, 0x92, 0xA1, 0x09, 0xC2,
	0x85, 0x85, 0xD5, 0xC6, 0x90, 0x13, 0xEA, 0x40, 0x27, 0x55, 0xA1, 0x51, 0x5A, 0xB4, 0x63, 0xDC,
	0x6A, 0x3F, 0x8B, 0x82, 0xE1, 0x92, 0x6E, 0xF2, 0x75, 0x80, 0x3A, 0x65, 0x27, 0x00, 0x92, 0x35,
	0x2A, 0x22, 0x38, 0x82, 0xEA, 0x0B, 0xD3, 0xB3, 0x51, 0x30, 0x4F, 0x7F, 0x6F, 0x47, 0x00, 0x52,
	0x1C, 0x0C, 0x45, 0x21, 0xF2, 0x4A, 0x16, 0x62, 0x51, 0x99, 0x8C, 0x09, 0x19, 0x53, 0xAB, 0x77,
	0x65, 0x44, 0x2E, 0x49, 0x73, 0x67, 0x57, 0x61, 0x22, 0x59, 0x8A, 0x4A, 0x2E, 0x51, 0xB2, 0x04,
	0x3E, 0x23, 0x47, 0x96, 0x38, 0xF1, 0x20, 0x21, 0xB5, 0x2E, 0x6F, 0x89, 0xD3, 0xE4, 0xE1, 0x90,
	0x52, 0x1D, 0x77, 0xE6, 0x9D, 0xF2, 0xD7, 0x93, 0x82, 0xED, 0x77, 0x49, 0x90, 0xA7, 0x5C, 0x7C,
	0x62, 0xE9, 0xFA, 0xBA, 0x6F, 0xE2, 0x0C, 0xD4, 0x68, 0x9C, 0x68, 0xDA, 0x13, 0x26, 0x6E, 0xB5,
	0x3E, 0x42, 0xBB, 0xE1, 0x2C, 0x54, 0x67, 0x52, 0x80, 0xD6, 0xF4, 0xA8, 0x6C, 0x1E, 0xA9, 0xA0,
	0xC0, 0xDE, 0xE9, 0x1A, 0x26, 0x0C, 0x18, 0x8A, 0x16, 0xB9, 0xBB, 0xB9, 0x16, 0xDE, 0xF7, 0x77,
	0x3F, 0x86, 0x0F, 0x9E, 0x8B, 0xC6, 0x47, 0x6B, 0x56, 0x5F, 0x59, 0x57, 0xB9, 0xD5, 0xD2, 0x5C,
	0x51, 0x91, 0xD1, 0x48, 0x49, 0x29, 0x33, 0xE5, 0x20, 0x19, 0xCE, 0xC8, 0xD2, 0x00, 0xA6, 0xB5,
	0x12, 0xD0, 0x58, 0x04, 0x02, 0xF7, 0xF3, 0xE6, 0x51, 0x50, 0x5E, 0x86, 0xE6, 0x06, 0x08, 0x68,
	0x07, 0xA9, 0xFB, 0x8D, 0xB6, 0xC7, 0x42, 0x5E, 0x03, 0x4A, 0x38, 0xE1, 0xA7, 0x1D, 0x5C, 0x1A,
	0xBB, 0xF4, 0x18, 0xB2, 0x93, 0x2E, 0xFF, 0x6C, 0xE5, 0xFF, 0xFA, 0x69, 0xFC, 0xB2, 0x23, 0x41,
	0x91, 0x20, 0xEC, 0xBE, 0xE0, 0x86, 0x59, 0xF8, 0x27, 0xCC, 0xE2, 0x6B, 0x31, 0x0E, 0x1E, 0x67,
	0x1A, 0xB2, 0x4E, 0xF1, 0xBF, 0x8D, 0x99, 0x25, 0x3E, 0xC4, 0xBD, 0x0A, 0x63, 0xC0, 0x46, 0x9D,
	0x1A, 0xB0, 0xC6, 0x25, 0xCB, 0xB2, 0x9D, 0xEF, 0xE8, 0x51, 0x91, 0x31, 0x3C, 0x34, 0x56, 0x35,
	0x37, 0x89, 0x16, 0x8B, 0xB4, 0x88, 0x16, 0x9E, 0x22, 0xD1, 0x71, 0x7F, 0x70, 0x9A, 0xA4, 0x4D,
	0x3B, 0x72, 0xC9, 0x47, 0xEF, 0x75, 0xDE, 0xD3, 0x7A, 0x19, 0x89, 0xDE, 0x09, 0x07, 0x1E, 0x02,
	0x54, 0x1D, 0x0B, 0x4F, 0xD7, 0x51, 0x37, 0x50, 0xE2, 0xA8, 0xC1, 0x42, 0x13, 0x27, 0x71, 0x1F,
	0xE0, 0xEB, 0x55, 0xA7, 0xBC, 0xCF, 0x4B, 0xB7, 0xC3, 0x34, 0x90, 0xD2, 0xB4, 0x7E, 0xEF, 0xD9,
	0xDE, 0xBC, 0xD7, 0x55, 0x43, 0x3B, 0xF3, 0xA1, 0xE7, 0x3E, 0xE1, 0xC2, 0x9E, 0x88, 0xD6, 0xAB,
	0x85, 0x1E, 0x86, 0xF1, 0xBF, 0x8F, 0xA5, 0x5B, 0x72, 0x58, 0xA7, 0x1C, 0x8E, 0x2B, 0x28, 0xEA,
	0x69, 0x7F, 0xBB, 0x1B, 0xC2, 0x30, 0x7B, 0x61, 0x33, 0xE7, 0xA2, 0xD3, 0x83, 0x67, 0x53, 0xE9,
	0x88, 0x22, 0xE7, 0x03, 0x6D, 0x90, 0x94, 0xC1, 0x81, 0x5F, 0x21, 0x24, 0xF1, 0x02, 0xCB, 0x62,
	0x03, 0x64, 0xBD, 0x77, 0xB7, 0xB5, 0x68, 0x38, 0x99, 0xAC, 0x26, 0x1E, 0x5E, 0xE2, 0xD0, 0xE0,
	0x2C, 0xB5, 0x75, 0x6E, 0xA1, 0x0B, 0x66, 0xF8, 0x15, 0xDA, 0x91, 0xF7, 0xE8, 0x59, 0x0D, 0xEF,
	0xF8, 0x4E, 0x41, 0xF7, 0x9C, 0x5F, 0x56, 0xFA, 0x4A, 0xCE, 0x74, 0x61, 0xCA, 0x52, 0xD3, 0xCC,
	0xF9, 0x97, 0x03, 0xAF, 0x81, 0x21, 0x74, 0x13, 0x4C, 0x1E, 0x28, 0x1C, 0x6B, 0x12, 0x83, 0x92,
	0x78, 0xA5, 0x58, 0x3A, 0x47, 0x01, 0x06, 0x55, 0xD3, 0x42, 0x20, 0xEA, 0x7E, 0x01, 0x21, 0xBD,
	0xC3, 0xFA, 0x53, 0x4B, 0x87, 0x05, 0x95, 0x3A, 0x7F, 0xFB, 0x7C, 0x24, 0xD5, 0x74, 0x7E, 0xEB,
	0x12, 0x9B, 0x64, 0x9E, 0xC7, 0xAE, 0x59, 0x7B, 0xE5, 0xC3, 0x7A, 0x9D, 0xB3, 0x11, 0x5E, 0x0C,
	0x94, 0x67, 0xE6, 0x09, 0x7D, 0x41, 0x94, 0x30, 0x73, 0x66, 0xC7, 0x4B, 0xD9, 0x3E, 0x74, 0x25,
	0x25, 0xAD, 0xFB, 0xF1, 0x7E, 0x2B, 0x3F, 0x5B, 0x6F, 0x54, 0x21, 0x8C, 0x45, 0x1B, 0x7F, 0x43,
	0xD6, 0xBF, 0xB3, 0xB7, 0x97, 0x43, 0xD1, 0x88, 0xE4, 0xDE, 0x05, 0xC8, 0x77, 0xD7, 0x96, 0xF8,
	0x01, 0xE0, 0x5A, 0x32, 0x87, 0x56, 0x6D, 0x0E, 0x12, 0x2F, 0x0B, 0x39, 0x3E, 0x6A, 0x0B, 0xAF,
	0x4E, 0x21, 0x88, 0x80, 0xE3, 0x5C, 0x6F, 0xA0, 0x5A, 0xC8, 0xF6, 0x67, 0x06, 0xC9, 0xD6, 0xF4,
	0x54, 0x42, 0x54, 0xB4, 0x5B, 0xFA, 0xD6, 0x27, 0x5F, 0xCA, 0x6D, 0x89, 0x2A, 0x85, 0x6B, 0x6D,
	0x3C, 0x15, 0xAA, 0xF3, 0xD0, 0x67, 0xF2, 0xEB, 0x8D, 0x4C, 0x64, 0x8F, 0xB7, 0xF3, 0x34, 0x0B,
	0x11, 0x6D, 0x98, 0x12, 0x2E, 0x2A, 0x82, 0x51, 0x24, 0xE2, 0x05, 0x9E, 0x87, 0x2D, 0xD5, 0x50,
	0xC6, 0x1B, 0x17, 0xCE, 0xCB, 0xE5, 0xE0, 0x1D, 0xAC, 0xED, 0xDF, 0x6B, 0x9B, 0x29, 0xA2, 0x0C,
	0x2C, 0x39, 0xB9, 0xFD, 0x39, 0x3A, 0xEE, 0xAD, 0x4D, 0x97, 0x0B, 0xC6, 0x60, 0x8D, 0xCA, 0x9A,
	0x10, 0x04, 0x0F, 0x97, 0x2E, 0xBD, 0xFA, 0xD2, 0x30, 0x12, 0x10, 0xFB, 0x65, 0xDC, 0xA2, 0xDB,
	0x45, 0xAC, 0xAD, 0x09, 0xB4, 0x61, 0xCB, 0x12, 0xF6, 0xF4, 0xDB, 0xAB, 0x05, 0x42, 0xD9, 0x04,
	0x6A, 0xA5, 0xB7, 0x71, 0xAA, 0xF6, 0x0A, 0x05, 0xCD, 0xCB, 0xB8, 0xF8, 0x26, 0x68, 0xE7, 0x3D,
	0x09, 0x38, 0x97, 0x8D, 0x59, 0xE0, 0xBB, 0x1F, 0x7F, 0x58, 0xC5, 0xAE, 0x9B, 0xE9, 0xA1, 0x7F,
	0x13, 0xA7, 0xE8, 0xC1, 0x7E, 0x25, 0x8A, 0x83, 0xCF, 0x54, 0x6E, 0x49, 0x92, 0xE5, 0x7A, 0x5A,
	0xC7, 0xCF, 0x28, 0xA9, 0x7A, 0x61, 0x00, 0x8E, 0xC2, 0x33, 0x9F, 0x62, 0x9D, 0x67, 0x70, 0x23,
	0x3E, 0x4E, 0xD8, 0xEA, 0x16, 0x62, 0x2A, 0xA0, 0x29, 0xB4, 0xDF, 0x3C, 0x57, 0xF5, 0x4C, 0xCD,
	0x03, 0xB4, 0xA1, 0x93, 0x77, 0x2C, 0x2B, 0x59, 0x5C, 0x29, 0x6B, 0xBC, 0x39, 0xC8, 0x0E, 0x6B,
	0xFC, 0xF7, 0x8B, 0x84, 0xB8, 0xB4, 0xCE, 0x4D, 0xC2, 0xB5, 0x65, 0xD5, 0x52, 0x97, 0x41, 0x75,
	0xAD, 0xD5, 0xC0, 0x3C, 0xA0, 0x6E, 0xD5, 0xBC, 0x1B, 0x52, 0x4F, 0xB8, 0xF4, 0x4C, 0x50, 0x89,
	0x21, 0xDE, 0x96, 0x61, 0x69, 0x8A, 0xBB, 0x4F, 0x24, 0x90, 0x4F, 0x3D, 0x53, 0xBB, 0x50, 0x3B,
	0x5F, 0x78, 0xF3, 0xF3, 0x63, 0x12, 0xA7, 0x25, 0xFC, 0xF4, 0x5F, 0x77, 0x58, 0xEF, 0x77, 0xBA,
	0xE8, 0xDB, 0xDF, 0xC4, 0x25, 0xF7, 0x79, 0xBB, 0x5F, 0x51, 0xCA, 0x17, 0x76, 0xD7, 0x2F, 0xDE,
	0x03, 0x1D, 0xAB, 0xF9, 0xE0, 0x3D, 0xA7, 0x14, 0x0B, 0x12, 0x1E, 0x30, 0xA5, 0x54, 0x87, 0x9C,
	0xCD, 0x6B, 0xCB, 0xA3, 0xC2, 0x59, 0xB9, 0x26, 0xF8, 0xFF, 0x4C, 0xA4, 0xFB, 0xC1, 0x74, 0xE9,
	0x1D, 0x3B, 0xA1, 0x78, 0xAC, 0xDF, 0xD9, 0xDF, 0x46, 0x2E, 0x3F, 0xB3, 0x4C, 0x67, 0xF1, 0x43,
	0xED, 0xF6, 0x8A, 0x04, 0xE8, 0xAC, 0x0D, 0x7E, 0x40, 0x80, 0xD0, 0xA8, 0x37, 0x7F, 0x78, 0x04,
	0x49, 0x44, 0x79, 0xC3, 0xE6, 0x49, 0x37, 0x34, 0x11, 0xF6, 0x0C, 0x2D, 0x4D, 0xC5, 0x3F, 0x3D,
	0x3F, 0xAB, 0x8E, 0x20, 0xB8, 0xAB, 0x6F, 0xB1, 0xD7, 0x66, 0x15, 0x95, 0xE6, 0xEE, 0x99, 0x0D,
	0xA3, 0x61, 0xF8, 0x83, 0xFF, 0x76, 0xA6, 0x57, 0x22, 0x2A, 0x8B, 0x82, 0xBC, 0xBB, 0xAC, 0xF1,
	0xF4, 0x80, 0x26, 0xEE, 0xC5, 0x6F, 0x57, 0x97, 0x64, 0x2F, 0xFE, 0x50, 0xEC, 0x30, 0xFD, 0x77,
	0x58, 0xDE, 0xF8, 0xE7, 0x14, 0x24, 0xB8, 0x0F, 0x55, 0x7D, 0x07, 0xF9, 0xD3, 0xF8, 0xE1, 0x7C,
	0x9A, 0xF9, 0xC7, 0xDA, 0xB8, 0x44, 0x21, 0xB8, 0x15, 0x27, 0x00, 0x2C, 0x3A, 0x4A, 0xB8, 0x62,
	0xD7, 0x50, 0x82, 0x25, 0xB8, 0x5E, 0xE7, 0x96, 0xE2, 0x07, 0x6F, 0x38, 0x3B, 0x73, 0x76, 0xC6,
	0x38, 0x5C, 0xC9, 0xB4, 0x29, 0xFB, 0xD1, 0xFA, 0xB8, 0x22, 0x38, 0xC0, 0xA4, 0x60, 0xAD, 0x69,
	0x41, 0xF3, 0xB9, 0xE0, 0x99, 0x98, 0x4A, 0x9E, 0x60, 0x9C, 0xD6, 0x0F, 0xE3, 0x32, 0x8B, 0x6C,
	0x2C, 0x2F, 0x50, 0xF7, 0xDA, 0xBD, 0xAA, 0x14, 0x55, 0x91, 0x53, 0x71, 0xAA, 0xAD, 0xDF, 0x9C,
	0x93, 0xFC, 0x44, 0x84, 0x38, 0xDA, 0x9C, 0xCF, 0x78, 0x0E, 0xD4, 0x50, 0xDA, 0xCA, 0x23, 0x0E,
	0x1A, 0x26, 0x51, 0xBE, 0x19, 0x7D, 0x49, 0x4B, 0xB8, 0x1A, 0xCD, 0x1B, 0xCA, 0xEC, 0xD1, 0x10,
	0x3E, 0x97, 0x2A, 0x04, 0xF0, 0x5A, 0x10, 0xB1, 0xE1, 0x05, 0x8A, 0x52, 0x6C, 0xD0, 0x12, 0x0A,
	0x10, 0xF5, 0x60, 0xD5, 0x52, 0xDD, 0xC8, 0xED, 0x46, 0x04, 0x59, 0x36, 0x84, 0xA2, 0xAF, 0x16,
	0x4B, 0xA4, 0x39, 0xDA, 0xFC, 0xA9, 0x67, 0x54, 0x75, 0x88, 0x62, 0x46, 0x33, 0x33, 0xCC, 0x1D,
	0x40, 0xF2, 0x95, 0xF1, 0x20, 0x8C, 0x1E, 0xBD, 0xCB, 0x7C, 0x9D, 0x8D, 0x5C, 0x4C, 0xC6, 0xC5,
	0x07, 0x8A, 0xDF, 0xB3, 0x52, 0xAC, 0x5B, 0x9E, 0x34, 0x98, 0x73, 0x3B, 0x81, 0xD6, 0x3E, 0x0C,
	0x68, 0x83, 0xDD, 0xF6, 0x28, 0xE1, 0x8D, 0xDB, 0x06, 0x23, 0x5A, 0xEB, 0xD5, 0x95, 0x9E, 0x1D,
	0x7C, 0x98, 0x77, 0x98, 0x71, 0x99, 0xA6, 0x63, 0x59, 0x9D, 0x8C, 0x3F, 0xA5, 0xBE, 0x23, 0xF7,
	0x70, 0x3E, 0x76, 0x1A, 0x55, 0x24, 0x26, 0x97, 0xAF, 0x2B, 0xAE, 0xB0, 0x6C, 0xF6, 0x00, 0x50,
	0xF4, 0x5A, 0xC3, 0x5B, 0xD3, 0x8C, 0xE0, 0x01, 0x26, 0x85, 0x4E, 0xA3, 0xA0, 0x58, 0x78, 0x26,
	0x85, 0xF8, 0x2B, 0x07, 0x27, 0xD9, 0x1B, 0x38, 0x22, 0x56, 0xA9, 0x55, 0x42, 0x62, 0x9E, 0xC4,
	0x1F, 0x32, 0x6B, 0x12, 0xDA, 0xCE, 0xF9, 0xD1, 0x5D, 0xC8, 0x26, 0xD8, 0x81, 0x52, 0x1E, 0x1B,
	0x7E, 0xC0, 0xAB, 0xCB, 0x3A, 0x93, 0x54, 0x75, 0xC7, 0x48, 0x6D, 0x59, 0xDA, 0x7C, 0xBF, 0x9B,
	0xE7, 0xB5, 0xBA, 0x4E, 0x03, 0x6F, 0xE9, 0x74, 0x1F, 0x2F, 0xC7, 0x8C, 0xBF, 0xA9, 0x0F, 0x11,
	0xD3, 0x5F, 0x0F, 0x2C, 0x7F, 0x58, 0xB7, 0xD5, 0x5C, 0x0B, 0x7F, 0x28, 0xFB, 0x55, 0xBF, 0x22,
	0x82, 0x75, 0x8C, 0x78, 0xFB, 0x27, 0x28, 0xFD, 0xD2, 0x0B, 0x03, 0x1E, 0x00, 0xA4, 0x8F, 0x3C,
	0x96, 0x75, 0xAD, 0x8A, 0x7A, 0x9C, 0xC5, 0x14, 0x3E, 0x8E, 0xB2, 0x4D, 0x40, 0x9A, 0x9D, 0x8D,
	0xDC, 0x0A, 0xDE, 0xD8, 0xA3, 0x50, 0x3F, 0x38, 0x61, 0xB3, 0x46, 0x26, 0xA6, 0xB0, 0x1D, 0xA3,
	0x9D, 0xE7, 0xC4, 0x8E, 0x9C, 0xF9, 0xBA, 0x28, 0x8C, 0x6B, 0xEF, 0x16, 0xD7, 0x28, 0x2C, 0x63,
	0x5C, 0x29, 0x55, 0x18, 0xF1, 0x60, 0x04, 0x9C, 0x54, 0x9A, 0xB2, 0x79, 0xB6, 0x10, 0xDE, 0xE7,
	0x00, 0xB4, 0x29, 0xFE, 0x09, 0x33, 0x89, 0xD7, 0x0C, 0x58, 0xFC, 0xCB, 0x71, 0x86, 0x46, 0x39,
	0xA8, 0x66, 0x1A, 0x82, 0xFB, 0xDB, 0x93, 0xB2, 0x63, 0x5E, 0xB9, 0x40, 0x82, 0x0B, 0x2F, 0x98,
	0xAC, 0x38, 0xD7, 0x44, 0xF6, 0x73, 0x38, 0x7F, 0xCE, 0x4C, 0x4B, 0x8B, 0xFA, 0xAF, 0x61, 0x82,
	0x0D, 0xC9, 0x8B, 0x50, 0x26, 0x30, 0x7E, 0x6F, 0x87, 0x90, 0x5D, 0x1F, 0xE5, 0xFC, 0x73, 0xB2,
	0xC4, 0xCA, 0xCE, 0x29, 0xF6, 0x9E, 0x39, 0x0C, 0x72, 0x08, 0x90, 0x26, 0x7C, 0x0A, 0xC5, 0x12,
	0x74, 0xE1, 0xA1, 0xA0, 0x1C, 0x6C, 0xEA, 0xBD, 0xFC, 0x65, 0xF3, 0x9E, 0xD1, 0x3B, 0xA6, 0x7F,
	0xB0, 0xB9, 0x7E, 0x06, 0xF2, 0x83, 0x2D, 0xA1, 0xB1, 0x34, 0x3F, 0xE1, 0x6A, 0x1F, 0xF5, 0xF2,
	0x2F, 0x4F, 0xA8, 0xFA, 0x98, 0xA1, 0x66, 0xCE, 0x82, 0xE1, 0x15, 0x21, 0xDD, 0x00, 0xD0, 0xC4,
	0xF1, 0x5C, 0x24, 0x85, 0x07, 0xAA, 0x76, 0x17, 0xBF, 0x54, 0x11, 0xD4, 0xB1, 0xE4, 0xC8, 0xBD,
	0xE2, 0xA1, 0x9B, 0xB4, 0x72, 0x1B, 0x82, 0xCF, 0xDC, 0x61, 0xF3, 0x9D, 0x9E, 0x0E, 0x89, 0x8E,
	0x16, 0xB9, 0x3F, 0xCE, 0x97, 0x16, 0x1A, 0xA9, 0x6F, 0xDD, 0x93, 0x29, 0x9C, 0x7C, 0xBA, 0x8F,
	0x6E, 0x3F, 0x3C, 0x4A, 0x8E, 0x36, 0x95, 0x3C, 0xF8, 0x90, 0x96, 0x8C, 0xC5, 0xE2, 0x96, 0x67,
	0x08, 0xF7, 0x69, 0xBF, 0x57, 0xE4, 0xBD, 0x9D, 0x16, 0x94, 0xFC, 0xF1, 0xC5, 0x62, 0x41, 0x1F,
	0xB8, 0x28, 0x6E, 0x77, 0x00, 0x7B, 0x39, 0x6B, 0x78, 0xF1, 0x12, 0x99, 0xB5, 0xD0, 0x17, 0x80,
	0x65, 0xE7, 0xD1, 0xBD, 0x7F, 0x2D, 0xB5, 0x14, 0x30, 0xEA, 0x69, 0x59, 0xD4, 0xAE, 0x71, 0xCA,
	0x30, 0x5A, 0x86, 0x78, 0x23, 0x23, 0x3A, 0x0A, 0xC1, 0x09, 0x7B, 0x8F, 0x53, 0xA5, 0x8C, 0x6B,
	0xD4, 0xCD, 0x7A, 0x08, 0xF6, 0x56, 0xF8, 0x38, 0xF5, 0x76, 0x2E, 0x47, 0x89, 0x20, 0x53, 0x3F,
	0x07, 0x1F, 0xE2, 0x04, 0x3C, 0xA2, 0x59, 0xA7, 0x6D, 0xD2, 0x54, 0x8E, 0xE7, 0x0B, 0xAC, 0x14,
	0x4A, 0x20, 0x6F, 0xD4, 0x13, 0x21, 0x8C, 0x34, 0x17, 0x3D, 0xF4, 0x9C, 0x5E, 0xD9, 0x9A, 0x73,
	0x78, 0x3A, 0xD5, 0xDA, 0x27, 0x01, 0xA2, 0xD8, 0xD3, 0x33, 0xE3, 0x9F, 0x9D, 0x60, 0x68, 0xB0,
	0xE6, 0xB5, 0x95, 0x93, 0x9D, 0x85, 0x95, 0x1E, 0xDB, 0xBA, 0x40, 0xF5, 0xB9, 0x96, 0x8F, 0x1C,
	0xDF, 0x2E, 0xDB, 0x01, 0x38, 0xF0, 0x9E, 0xEC, 0xEF, 0xC7, 0x02, 0xAB, 0x27, 0xD6, 0x05, 0xCE,
	0xA8, 0xC7, 0x06, 0xBE, 0xA7, 0x07, 0x28, 0xDB, 0xF0, 0x48, 0x22, 0xDB, 0xA2, 0xB9, 0xD1, 0xD4,
	0xEA, 0x16, 0x9D, 0xF4, 0x0A, 0xFE, 0x42, 0xA8, 0xC6, 0xB5, 0x16, 0xD6, 0x2C, 0xAE, 0x16, 0x0F,
	0xEC, 0x7F, 0x32, 0xDE, 0xB2, 0x75, 0x15, 0x10, 0xE3, 0x90, 0x89, 0xE7, 0x4C, 0x59, 0x3B, 0xB1,
	0xE5, 0x79, 0x42, 0x54, 0xFE, 0x87, 0x8C, 0x15, 0xBE, 0xC1, 0x58, 0x93, 0x19, 0xE2, 0x48, 0x70,
	0xD5, 0x1F, 0xA0, 0xC2, 0xBD, 0xD5, 0xE9, 0xA4, 0x51, 0x87, 0xF6, 0x9C, 0x3C, 0x9F, 0x57, 0xD8
};

static int xcode_building_first_stage(struct cxdec_xcode_status *xcode)
{
  	switch (xcode_rand(xcode) % 3) {
	case 1:
  		// MOV EAX, EDI
  		if (!push_2bytesxcode(xcode, 0x8b, 0xc7))
  			return 0;
  		break;
  	case 2:
		// MOV EAX, xcode_rand(xcode)
		if (!push_bytexcode(xcode, 0xb8)
				|| !push_dwordxcode(xcode, xcode_rand(xcode)))
			return 0;
		break;
	case 0:
		// MOV ESI, EncryptionControlBlock
		// MOV EAX, DWORD PTR DS:[ESI+((xcode_rand(xcode) & 0x3ff) << 2)]
		if (!push_bytexcode(xcode, 0xbe)
				|| !push_dwordxcode(xcode, (DWORD)EncryptionControlBlock)
				|| !push_2bytesxcode(xcode, 0x8b, 0x86)
				|| !push_dwordxcode(xcode, (xcode_rand(xcode) & 0x3ff) << 2))
			return 0;
		break;
  	}
  	return 1;
}

static int xcode_building_stage0(struct cxdec_xcode_status *xcode, int stage)
{
	if (stage == 1)
		return xcode_building_first_stage(xcode);

    if (xcode_rand(xcode) & 1) {
		if (!xcode_building_stage1(xcode, stage - 1))
			return 0;
    } else {
		if (!xcode_building_stage0(xcode, stage - 1))
			return 0;
    }

    switch (xcode_rand(xcode) & 7) {
	case 0:
		// NOT EAX
		if (!push_2bytesxcode(xcode, 0xf7, 0xd0))
			return 0;
		break;
	case 3:
		// NEG EAX
        if (!push_2bytesxcode(xcode, 0xf7, 0xd8))
			return 0;
        break;
	case 6:
		// INC EAX
		if (!push_bytexcode(xcode, 0x40))
			return 0;
        break;
	case 4:
		// DEC EAX
		if (!push_bytexcode(xcode, 0x48))
			return 0;
		break;
	case 2:
		// PUSH EBX
		// MOV EBX, EAX
		// AND EBX, AAAAAAAA
		// AND EAX, 55555555
		// SHR EBX, 1
		// SHL EAX, 1
		// OR EAX, EBX
		// POP EBX
		if (!push_bytexcode(xcode, 0x53)
				|| !push_2bytesxcode(xcode, 0x89, 0xc3)
				|| !push_6bytesxcode(xcode, 0x81, 0xe3, 0xaa, 0xaa, 0xaa, 0xaa)
				|| !push_5bytesxcode(xcode, 0x25, 0x55, 0x55, 0x55, 0x55)
				|| !push_2bytesxcode(xcode, 0xd1, 0xeb)
				|| !push_2bytesxcode(xcode, 0xd1, 0xe0)
				|| !push_2bytesxcode(xcode, 0x09, 0xd8)
				|| !push_bytexcode(xcode, 0x5b))
			return 0;
        break;
	case 5:
		// XOR EAX, xcode_rand(xcode)
		if (!push_bytexcode(xcode, 0x35) 
				|| !push_dwordxcode(xcode, xcode_rand(xcode)))
			return 0;
        break;
	case 1:
        if (xcode_rand(xcode) & 1) {
        	// ADD EAX, xcode_rand(xcode)
			if (!push_bytexcode(xcode, 0x05))
            	return 0;
        } else {
        	// SUB EAX, xcode_rand(xcode)
			if (!push_bytexcode(xcode, 0x2d))
            	return 0;
        }
        if (!push_dwordxcode(xcode, xcode_rand(xcode)))
        	return 0;
        break;
	case 7:
		// MOV ESI, EncryptionControlBlock
		// AND EAX, 3FFh
		// MOV EAX, DWORD PTR DS:[ESI+EAX*4]
        if (!push_bytexcode(xcode, 0xbe)
  				|| !push_dwordxcode(xcode, (DWORD)EncryptionControlBlock)
				|| !push_bytexcode(xcode, 0x25)
				|| !push_dwordxcode(xcode, 0x3ff)
				|| !push_3bytesxcode(xcode, 0x8b, 0x04, 0x86))
			return 0;
		break;
	}
	return 1;
}

static int xcode_building_stage1(struct cxdec_xcode_status *xcode, int stage)
{
	if (stage == 1)
		return xcode_building_first_stage(xcode);

	// PUSH EBX
	if (!push_bytexcode(xcode, 0x53))
		return 0;

	if (xcode_rand(xcode) & 1) {
		if (!xcode_building_stage1(xcode, stage - 1))
			return 0;
	} else {
		if (!xcode_building_stage0(xcode, stage - 1))
			return 0;
	}

	// MOV EBX, EAX
	if (!push_2bytesxcode(xcode, 0x89, 0xc3))
		return 0;

	if (xcode_rand(xcode) & 1) {
		if (!xcode_building_stage1(xcode, stage - 1))
			return 0;
	} else {
		if (!xcode_building_stage0(xcode, stage - 1))
			return 0;
	}

	switch (xcode_rand(xcode) % 6) {
    case 1:
		// ADD EAX, EBX
		if (!push_2bytesxcode(xcode, 0x01, 0xd8))
			return 0;
		break;
    case 3:
    	// SUB EAX, EBX
		if (!push_2bytesxcode(xcode, 0x29, 0xd8))
			return 0;
		break;
    case 4:
    	// NEG EAX, ADD EAX, EBX
		if (!push_2bytesxcode(xcode, 0xf7, 0xd8) 
				|| !push_2bytesxcode(xcode, 0x01, 0xd8))
			return 0;
		break;
    case 2:
    	// IMUL EAX, EBX
		if (!push_3bytesxcode(xcode, 0x0f,  0xaf, 0xc3))
			return 0;
		break;
	case 0:
		// PUSH ECX
		// MOV ECX, EBX
		// AND ECX, 0F
		// SHL EAX, CL
		// POP ECX
		if (!push_bytexcode(xcode, 0x51)
				|| !push_2bytesxcode(xcode, 0x89, 0xd9)
				|| !push_3bytesxcode(xcode, 0x83, 0xe1, 0x0f)
				|| !push_2bytesxcode(xcode, 0xd3, 0xe0)
				|| !push_bytexcode(xcode, 0x59))
			return 0;
		break;
    case 5:
    	// PUSH ECX
    	// MOV ECX, EBX
    	// AND ECX, 0F
    	// SHR EAX, CL
    	// POP ECX
		if (!push_bytexcode(xcode, 0x51) 
				|| !push_2bytesxcode(xcode, 0x89, 0xd9)
				|| !push_3bytesxcode(xcode, 0x83, 0xe1, 0x0f)
				|| !push_2bytesxcode(xcode, 0xd3, 0xe8)
				|| !push_bytexcode(xcode, 0x59))
			return 0;
		break;
	}
	// POP EBX
	return push_bytexcode(xcode, 0x5b);
}

const struct cxdec_callback dec_callback = {
	"",
	{ ONI_GOKKOKEY1, ONI_GOKKOKEY2 },
	xcode_building_stage1
};

static struct cxdec {
	BYTE *xcode;			// 容纳128个解密函数，每个函数100字节
	void *address_list[128];// 128个解密函数的地址(用index索引)
	DWORD current_count;		// 当前有效的解密函数的个数
	DWORD index_list[100];	// 记录有效的index编号
	int init_flag;
} cxdec;

static int cxdec_init(void)
{
	cxdec.xcode = (BYTE *)VirtualAlloc(NULL, 128 * 100, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (!cxdec.xcode)
		return S_FALSE;

	memset(cxdec.address_list, 0, sizeof(cxdec.address_list));
	cxdec.current_count = 0;
	memset(cxdec.index_list, -1, sizeof(cxdec.index_list));
	cxdec.init_flag = 1;

	return 0;
}

//---------------------------------------------------------------------------
static int xcode_building_start(struct cxdec_xcode_status *xcode, int stage)
{
	// PUSH EDI, PUSH ESI, PUSH EBX, PUSH ECX, PUSH EDX
	if (!push_5bytesxcode(xcode, 0x57, 0x56, 0x53, 0x51, 0x52))
		return 0;

	// MOV EDI, DWORD PTR SS:[ESP+18] (load parameter0)
	if (!push_4bytesxcode(xcode, 0x8b, 0x7c, 0x24, 0x18))
		return 0;

	if (!xcode_building_stage1(xcode, stage))
		return 0;

	// POP EDX, POP ECX, POP EBX, POP ESI, POP EDI
	if (!push_5bytesxcode(xcode, 0x5a, 0x59, 0x5b, 0x5e, 0x5f))
		return 0;

	// RETN
	return push_bytexcode(xcode, 0xc3);
}
//---------------------------------------------------------------------------
static int xcode_building(const cxdec_callback *callback, DWORD seed, void *start, DWORD size)
{
	struct cxdec_xcode_status xcode;
	int stage;
	xcode.start = (BYTE *)start;
	xcode.curr = (BYTE *)start;
	xcode.space_size = size;
	xcode.seed = seed;
	xcode.xcode_building = callback->xcode_building;

	// @1E017A90
  	for (stage = 5; stage > 0; --stage) {  		
  		if (xcode_building_start(&xcode, stage))
  			break;
  		xcode.curr = (BYTE *)start;
  	}
  	if (!stage) {
		TVPThrowExceptionMessage(TJS_W("Insufficient code space"));
		return S_FALSE;
	}

	FlushInstructionCache(GetCurrentProcess(), start, size);
	return 1;
}
//---------------------------------------------------------------------------
static void cxdec_execute_xcode(const cxdec_callback *callback, DWORD hash, DWORD *ret1, DWORD *ret2)
{
	DWORD index = hash & 0x7f;
	hash >>= 7;	

	if (!cxdec.init_flag)
		cxdec_init();

	if (!cxdec.address_list[index]) {
		if (cxdec.index_list[cxdec.current_count] != index) {
			if (cxdec.index_list[cxdec.current_count] != -1)
				cxdec.address_list[cxdec.index_list[cxdec.current_count]] = 0;
			xcode_building(callback, index, cxdec.xcode + cxdec.current_count * 128, 128);
			cxdec.address_list[index] = cxdec.xcode + cxdec.current_count * 128;
			cxdec.index_list[cxdec.current_count++] = index;
			if (cxdec.current_count >= 100)
				cxdec.current_count = 0;
		}
	}

	*ret1 = (*(DWORD (*)(DWORD))cxdec.address_list[index])(hash);
	*ret2 = (*(DWORD (*)(DWORD))cxdec.address_list[index])(~hash);
}
//---------------------------------------------------------------------------
static void __cxdec_decode(const cxdec_callback *callback, DWORD hash, DWORD offset, BYTE *buf, DWORD len)
{
	BYTE key[12];
	DWORD ret[2], i, k, *dbuf;

	cxdec_execute_xcode(callback, hash, &ret[0], &ret[1]);

	key[8] = ret[0] >> 8;
	key[9] = ret[0] >> 16;
	key[10] = ret[0];
	DWORD key1 = ret[1] >> 16;
	DWORD key2 = ret[1] & 0xffff;
	*(DWORD *)&key[0] = key1;

	if (key1 == key2)
		++key2;

	*(DWORD *)&key[4] = key2;
	
	if (!key[10])
		key[10] = 1;

	if ((key2 >= offset) && (key2 < offset + len))
		buf[key2 - offset] ^= key[9];
	
	if ((key1 >= offset) && (key1 < offset + len))
		buf[key1 - offset] ^= key[8];

	if (len>16)
	{
		k = 0x1010101 * key[10];
		for (i = 0; i < ((DWORD)buf & 3); i++) buf[i] ^= key[10];
		len-=i;
		dbuf=(DWORD*)(buf+i);
		for (i = 0; i < len>>2; i++) *(dbuf++) ^= k;
		buf=(BYTE*)dbuf;
		for (i = 0; i < (len & 3); i++) *buf++ ^= key[10];
	}
	else
		for (i = 0; i < len; ++i)
			buf[i] ^= key[10];
}
//---------------------------------------------------------------------------
static void cxdec_decode(const cxdec_callback *callback, DWORD hash, DWORD offset, BYTE *buf, DWORD len)
{
	DWORD bondary = (hash & callback->key[0]) + callback->key[1];
	DWORD dec_len = 0;

	if (offset < bondary) {
		if (offset + len > bondary)
			dec_len = bondary - offset;
		else
			dec_len = len;
		__cxdec_decode(callback, hash, offset, buf, dec_len);
		offset += dec_len;
		buf += dec_len;
		dec_len = len - dec_len;
	} else
		dec_len = len;

	if (dec_len)
		__cxdec_decode(callback, (hash >> 16) ^ hash, offset, buf, dec_len);
}
//---------------------------------------------------------------------------
void TVP_tTVPXP3ArchiveExtractionFilter_CONVENTION
        TVPXP3ArchiveExtractionFilter(tTVPXP3ExtractionFilterInfo *info)
{
    if(info->SizeOfSelf != sizeof(tTVPXP3ExtractionFilterInfo))
        TVPThrowExceptionMessage(TJS_W("Incompatible tTVPXP3ExtractionFilterInfo size"));

	//if(info->FileHash==0xc30215d1) return;
	cxdec_decode(&dec_callback, info->FileHash, info->Offset, (unsigned char*)info->Buffer, info->BufferSize);

}
//---------------------------------------------------------------------------
#pragma comment(linker, "/EXPORT:V2Link=_V2Link@4,PRIVATE")
extern "C" HRESULT _stdcall V2Link(iTVPFunctionExporter *exporter)
{
        TVPInitImportStub(exporter);

        TVPSetXP3ArchiveExtractionFilter(TVPXP3ArchiveExtractionFilter);

        return S_OK;
}
//---------------------------------------------------------------------------
#pragma comment(linker, "/EXPORT:V2Unlink=_V2Unlink@0,PRIVATE")
extern "C" HRESULT _stdcall V2Unlink()
{

        TVPSetXP3ArchiveExtractionFilter(NULL);

        TVPUninitImportStub();

        return S_OK; 
}
//---------------------------------------------------------------------------
#pragma pack(1)
typedef struct {
	unsigned int SizeOfSelf; // @0 structure size of tTVPXP3ExtractionFilterInfo itself
	unsigned __int64 Offset; // @4 offset of the buffer data in uncompressed stream position
	void *Buffer; // @c target data buffer
	unsigned int BufferSize; // @10 buffer size in bytes pointed by "Buffer"
	unsigned long FileHash; // @14 hash value of the file (since inteface v2)
} TVPXP3ExtractionFilterInfo;

#pragma comment(linker, "/EXPORT:XP3ArchiveAttractFilter_v2=_XP3ArchiveAttractFilter_v2@20,PRIVATE")
extern "C" void __stdcall XP3ArchiveAttractFilter_v2( unsigned __int32 hash,
        unsigned __int64 offset, void * buffer, long bufferlen)
{
        // 接口版本 2 可以接受并使用以下的参数
        // hash      : 输入文件（解密后）内容的32位 Hash （散列）值
        // offset    : "Buffer" 成员所指向的数据偏离这个文件头部的偏移值
        //             （当文件被压缩时，将显示文件为压缩状态下的字节偏移
        //                                值）
        // buffer    : 指向要加密的数据的指针。当文件被压缩时，给出的是文
        //             件被压缩前的数据。
        //             ( 本函数不能更改压缩后的文件数据 )
        // bufferlen : "buffer" 参数给出的数据块的长度
    cxdec_decode(&dec_callback, hash, offset, (unsigned char*)buffer, bufferlen);
}
//---------------------------------------------------------------------------
//BOOL APIENTRY DllMain( HANDLE hModule, 
//                       DWORD  ul_reason_for_call, 
//                       LPVOID lpReserved
//					 )
//{
//    return TRUE;
//}
