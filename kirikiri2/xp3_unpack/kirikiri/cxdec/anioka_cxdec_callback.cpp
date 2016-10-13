#include "cxdec.h"

static int xcode_building_stage0(struct cxdec_xcode_status *xcode, int stage);
static int xcode_building_stage1(struct cxdec_xcode_status *xcode, int stage);

static BYTE EncryptionControlBlock[4096] = {
	0x20, 0x45, 0x6E, 0x63, 0x72, 0x79, 0x70, 0x74, 0x69, 0x6F, 
	0x6E, 0x20, 0x63, 0x6F, 0x6E, 0x74, 0x72, 0x6F, 0x6C, 0x20, 
	0x62, 0x6C, 0x6F, 0x63, 0x6B, 0x20, 0x2D, 0x2D, 0x20, 0x53, 
	0x74, 0x61, 0x74, 0x69, 0x63, 0x61, 0x6C, 0x6C, 0x79, 0x20, 
	0x6F, 0x72, 0x20, 0x64, 0x79, 0x6E, 0x61, 0x6D, 0x69, 0x63, 
	0x61, 0x6C, 0x6C, 0x79, 0x2C, 0x20, 0x64, 0x69, 0x72, 0x65, 
	0x63, 0x74, 0x6C, 0x79, 0x20, 0x6F, 0x72, 0x20, 0x69, 0x6E, 
	0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x6C, 0x79, 0x2C, 0x20, 
	0x75, 0x73, 0x69, 0x6E, 0x67, 0x20, 0x74, 0x68, 0x69, 0x73, 
	0x20, 0x70, 0x72, 0x6F, 0x67, 0x72, 0x61, 0x6D, 0x20, 0x61, 
	0x6E, 0x64, 0x2F, 0x6F, 0x72, 0x20, 0x62, 0x6C, 0x6F, 0x63, 
	0x6B, 0x20, 0x66, 0x72, 0x6F, 0x6D, 0x20, 0x6F, 0x74, 0x68, 
	0x65, 0x72, 0x20, 0x70, 0x72, 0x6F, 0x67, 0x72, 0x61, 0x6D, 
	0x73, 0x20, 0x77, 0x69, 0x6C, 0x6C, 0x20, 0x62, 0x65, 0x20, 
	0x69, 0x6C, 0x6C, 0x65, 0x67, 0x61, 0x6C, 0x20, 0x62, 0x79, 
	0x20, 0x74, 0x68, 0x65, 0x20, 0x6C, 0x69, 0x63, 0x65, 0x6E, 
	0x73, 0x65, 0x20, 0x61, 0x67, 0x72, 0x65, 0x65, 0x6D, 0x65, 
	0x6E, 0x74, 0x2E, 0x20, 0x82, 0xB1, 0x82, 0xCC, 0x83, 0x76, 
	0x83, 0x8D, 0x83, 0x4F, 0x83, 0x89, 0x83, 0x80, 0x82, 0xE2, 
	0x83, 0x75, 0x83, 0x8D, 0x83, 0x62, 0x83, 0x4E, 0x82, 0xF0, 
	0x81, 0x41, 0x90, 0xC3, 0x93, 0x49, 0x82, 0xC5, 0x82, 0xA0, 
	0x82, 0xEA, 0x93, 0xAE, 0x93, 0x49, 0x82, 0xC5, 0x82, 0xA0, 
	0x82, 0xEA, 0x81, 0x41, 0x92, 0xBC, 0x90, 0xDA, 0x93, 0x49, 
	0x82, 0xC5, 0x82, 0xA0, 0x82, 0xEA, 0x8A, 0xD4, 0x90, 0xDA, 
	0x93, 0x49, 0x82, 0xC5, 0x82, 0xA0, 0x82, 0xEA, 0x81, 0x41, 
	0x91, 0xBC, 0x82, 0xCC, 0x83, 0x76, 0x83, 0x8D, 0x83, 0x4F, 
	0x83, 0x89, 0x83, 0x80, 0x82, 0xA9, 0x82, 0xE7, 0x97, 0x70, 
	0x82, 0xA2, 0x82, 0xE9, 0x82, 0xB1, 0x82, 0xC6, 0x82, 0xCD, 
	0x83, 0x89, 0x83, 0x43, 0x83, 0x5A, 0x83, 0x93, 0x83, 0x58, 
	0x82, 0xC9, 0x82, 0xE6, 0x82, 0xE8, 0x8B, 0xD6, 0x82, 0xB6, 
	0x82, 0xE7, 0x82, 0xEA, 0x82, 0xC4, 0x82, 0xA2, 0x82, 0xDC, 
	0x82, 0xB7, 0x81, 0x42, 0x0A, 0x28, 0x43, 0x29, 0x4C, 0x61, 
	0x6D, 0x69, 0x61, 0x41, 0x6C, 0x6C, 0x52, 0x69, 0x67, 0x68, 
	0x74, 0x73, 0x52, 0x65, 0x73, 0x65, 0x72, 0x76, 0x65, 0x64, 
	0x2E, 0x0A, 0x0A, 0x90, 0xB6, 0x88, 0xD3, 0x8B, 0x43, 0x82, 
	0xC8, 0x96, 0x85, 0x81, 0x45, 0x95, 0x53, 0x89, 0xD4, 0x82, 
	0xC9, 0x8E, 0xD8, 0x82, 0xE8, 0x95, 0xA8, 0x82, 0xCC, 0x83, 
	0x47, 0x83, 0x8D, 0x96, 0x7B, 0x82, 0xE2, 0x44, 0x56, 0x44, 
	0x82, 0xF0, 0x8F, 0x88, 0x95, 0xAA, 0x82, 0xB3, 0x82, 0xEA, 
	0x82, 0xC4, 0x82, 0xB5, 0x82, 0xDC, 0x82, 0xA4, 0x8E, 0xE5, 
	0x90, 0x6C, 0x8C, 0xF6, 0x81, 0x42, 0x0A, 0x0A, 0x82, 0xBB, 
	0x82, 0xEA, 0x82, 0xE7, 0x82, 0xCC, 0x8E, 0x9D, 0x82, 0xBF, 
	0x8E, 0xE5, 0x82, 0xC5, 0x82, 0xA0, 0x82, 0xE9, 0x97, 0x46, 
	0x90, 0x6C, 0x82, 0xD6, 0x82, 0xCC, 0x98, 0x6C, 0x82, 0xD1, 
	0x82, 0xC6, 0x82, 0xB5, 0x82, 0xC4, 0x81, 0x41, 0x94, 0xDE, 
	0x82, 0xCD, 0x96, 0x85, 0x82, 0xCC, 0x92, 0x85, 0x91, 0xD6, 
	0x82, 0xA6, 0x82, 0xE2, 0x95, 0x97, 0x98, 0x43, 0x82, 0xF0, 
	0x93, 0x90, 0x8E, 0x42, 0x82, 0xB5, 0x8E, 0x6E, 0x82, 0xDF, 
	0x82, 0xE9, 0x81, 0x42, 0x0A, 0x0A, 0x82, 0xB5, 0x82, 0xA9, 
	0x82, 0xB5, 0x81, 0x41, 0x82, 0xA2, 0x82, 0xC2, 0x82, 0xCC, 
	0x8A, 0xD4, 0x82, 0xC9, 0x82, 0xA9, 0x8F, 0x97, 0x82, 0xE7, 
	0x82, 0xB5, 0x82, 0xAD, 0x90, 0xAC, 0x92, 0xB7, 0x82, 0xB5, 
	0x82, 0xC4, 0x82, 0xA2, 0x82, 0xBD, 0x96, 0x85, 0x82, 0xCC, 
	0x90, 0x67, 0x91, 0xCC, 0x82, 0xC9, 0x8B, 0x43, 0x95, 0x74, 
	0x82, 0xA2, 0x82, 0xC4, 0x82, 0xB5, 0x82, 0xDC, 0x82, 0xA4, 
	0x82, 0xC6, 0x81, 0x41, 0x82, 0xA2, 0x82, 0xC2, 0x82, 0xB5, 
	0x82, 0xA9, 0x8B, 0xD6, 0x92, 0x66, 0x82, 0xCC, 0x8A, 0xB4, 
	0x8F, 0xEE, 0x82, 0xAA, 0x89, 0xE8, 0x90, 0xB6, 0x82, 0xA6, 
	0x8E, 0x6E, 0x82, 0xDF, 0x81, 0x63, 0x81, 0x63, 0x81, 0x42, 
	0x0A, 0x0A, 0x88, 0xEA, 0x95, 0xFB, 0x81, 0x41, 0x95, 0x53, 
	0x89, 0xD4, 0x82, 0xCD, 0x8C, 0x5A, 0x82, 0xCC, 0x93, 0x90, 
	0x8E, 0x42, 0x82, 0xC9, 0x8B, 0x43, 0x95, 0x74, 0x82, 0xA2, 
	0x82, 0xC4, 0x82, 0xA2, 0x82, 0xBD, 0x81, 0x42, 0x82, 0xBB, 
	0x82, 0xB5, 0x82, 0xC4, 0x82, 0xBB, 0x82, 0xCC, 0x8F, 0xE3, 
	0x82, 0xC5, 0x81, 0x41, 0x89, 0xBD, 0x82, 0xE0, 0x8B, 0x43, 
	0x95, 0x74, 0x82, 0xA2, 0x82, 0xC4, 0x82, 0xA2, 0x82, 0xC8, 
	0x82, 0xA2, 0x82, 0xD3, 0x82, 0xE8, 0x82, 0xF0, 0x82, 0xB5, 
	0x82, 0xC4, 0x82, 0xA2, 0x82, 0xBD, 0x81, 0x42, 0x0A, 0x0A, 
	0x82, 0xC7, 0x82, 0xA4, 0x82, 0xB7, 0x82, 0xEA, 0x82, 0xCE, 
	0x82, 0xA2, 0x82, 0xA2, 0x82, 0xCC, 0x82, 0xA9, 0x95, 0xAA, 
	0x82, 0xA9, 0x82, 0xE7, 0x82, 0xC8, 0x82, 0xA9, 0x82, 0xC1, 
	0x82, 0xBD, 0x82, 0xB1, 0x82, 0xC6, 0x82, 0xE0, 0x82, 0xA0, 
	0x82, 0xE9, 0x81, 0x42, 0x82, 0xBE, 0x82, 0xAA, 0x82, 0xBB, 
	0x82, 0xEA, 0x88, 0xC8, 0x8F, 0xE3, 0x82, 0xC9, 0x81, 0x41, 
	0x8C, 0x5A, 0x82, 0xCC, 0x8E, 0x8B, 0x90, 0xFC, 0x82, 0xC9, 
	0x89, 0x78, 0x82, 0xD1, 0x82, 0xF0, 0x8A, 0xB4, 0x82, 0xB6, 
	0x82, 0xE9, 0x8E, 0xA9, 0x95, 0xAA, 0x82, 0xC9, 0x8B, 0x43, 
	0x95, 0x74, 0x82, 0xA2, 0x82, 0xC4, 0x82, 0xB5, 0x82, 0xDC, 
	0x82, 0xC1, 0x82, 0xBD, 0x82, 0xA9, 0x82, 0xE7, 0x81, 0x42, 
	0x0A, 0x0A, 0x82, 0xA8, 0x8C, 0x5A, 0x82, 0xBF, 0x82, 0xE1, 
	0x82, 0xF1, 0x82, 0xAA, 0x8E, 0x84, 0x82, 0xC5, 0x8B, 0xBB, 
	0x95, 0xB1, 0x82, 0xB5, 0x82, 0xC4, 0x82, 0xAD, 0x82, 0xEA, 
	0x82, 0xC4, 0x82, 0xA2, 0x82, 0xE9, 0x81, 0x42, 0x8E, 0x84, 
	0x82, 0xCC, 0x97, 0x87, 0x82, 0xC5, 0x83, 0x49, 0x83, 0x69, 
	0x83, 0x6A, 0x81, 0x5B, 0x82, 0xB5, 0x82, 0xC4, 0x82, 0xA2, 
	0x82, 0xE9, 0x81, 0x42, 0x82, 0xBB, 0x82, 0xEA, 0x82, 0xC1, 
	0x82, 0xC4, 0x82, 0xC8, 0x82, 0xF1, 0x82, 0xBE, 0x82, 0xA9, 
	0x83, 0x68, 0x83, 0x4C, 0x83, 0x68, 0x83, 0x4C, 0x82, 0xB7, 
	0x82, 0xE9, 0x81, 0x42, 0x0A, 0x0A, 0x83, 0x4A, 0x83, 0x81, 
	0x83, 0x89, 0x82, 0xC9, 0x8B, 0x43, 0x95, 0x74, 0x82, 0xAD, 
	0x82, 0xC6, 0x81, 0x41, 0x94, 0xDE, 0x8F, 0x97, 0x82, 0xCD, 
	0x8A, 0xCC, 0x90, 0x53, 0x82, 0xCC, 0x95, 0x94, 0x95, 0xAA, 
	0x82, 0xAA, 0x82, 0xE6, 0x82, 0xAD, 0x8C, 0xA9, 0x82, 0xA6, 
	0x82, 0xE9, 0x82, 0xE6, 0x82, 0xA4, 0x82, 0xC9, 0x82, 0xB3, 
	0x82, 0xE8, 0x82, 0xB0, 0x82, 0xC8, 0x82, 0xAD, 0x8B, 0x43, 
	0x82, 0xF0, 0x8C, 0xAD, 0x82, 0xA4, 0x81, 0x42, 0x0A, 0x0A, 
	0x96, 0xE9, 0x82, 0xC8, 0x96, 0xE9, 0x82, 0xC8, 0x95, 0x94, 
	0x89, 0xAE, 0x82, 0xC9, 0x94, 0x45, 0x82, 0xD1, 0x8D, 0x9E, 
	0x82, 0xF1, 0x82, 0xC5, 0x82, 0xAD, 0x82, 0xE9, 0x8C, 0x5A, 
	0x82, 0xCC, 0x8E, 0xE8, 0x82, 0xAA, 0x90, 0x47, 0x82, 0xEA, 
	0x82, 0xC4, 0x82, 0xAD, 0x82, 0xE9, 0x82, 0xCC, 0x82, 0xF0, 
	0x81, 0x41, 0x96, 0xB0, 0x82, 0xC1, 0x82, 0xBD, 0x82, 0xD3, 
	0x82, 0xE8, 0x82, 0xF0, 0x82, 0xB5, 0x82, 0xC8, 0x82, 0xAA, 
	0x82, 0xE7, 0x96, 0xE9, 0x96, 0x88, 0x90, 0x53, 0x91, 0xD2, 
	0x82, 0xBF, 0x82, 0xC9, 0x82, 0xB5, 0x82, 0xC4, 0x82, 0xA2, 
	0x82, 0xE9, 0x81, 0x42, 0x0A, 0x0A, 0x8F, 0x99, 0x81, 0x58, 
	0x82, 0xC9, 0x83, 0x47, 0x83, 0x58, 0x83, 0x4A, 0x83, 0x8C, 
	0x81, 0x5B, 0x83, 0x67, 0x82, 0xB5, 0x82, 0xC4, 0x82, 0xA2, 
	0x82, 0xAD, 0x8C, 0x5A, 0x82, 0xCC, 0x88, 0xAB, 0x8B, 0x59, 
	0x81, 0x42, 0x0A, 0x0A, 0x82, 0xB1, 0x82, 0xCC, 0x82, 0xDC, 
	0x82, 0xDC, 0x82, 0xA2, 0x82, 0xAD, 0x82, 0xC6, 0x81, 0x41, 
	0x82, 0xA2, 0x82, 0xC2, 0x82, 0xA9, 0x88, 0xEA, 0x90, 0xFC, 
	0x82, 0xF0, 0x89, 0x7A, 0x82, 0xA6, 0x82, 0xC4, 0x82, 0xB5, 
	0x82, 0xDC, 0x82, 0xA2, 0x82, 0xBB, 0x82, 0xA4, 0x82, 0xC5, 
	0x8B, 0xB0, 0x82, 0xEB, 0x82, 0xB5, 0x82, 0xA2, 0x81, 0x42, 
	0x0A, 0x0A, 0x82, 0xC5, 0x82, 0xE0, 0x82, 0xA8, 0x8C, 0x5A, 
	0x82, 0xBF, 0x82, 0xE1, 0x82, 0xF1, 0x82, 0xBE, 0x82, 0xC1, 
	0x82, 0xBD, 0x82, 0xE7, 0x81, 0x63, 0x81, 0x63, 0x81, 0x42, 
	0x0A, 0x0A, 0x82, 0xBB, 0x82, 0xB5, 0x82, 0xC4, 0x82, 0xA0, 
	0x82, 0xE9, 0x93, 0xFA, 0x82, 0xCC, 0x82, 0xB1, 0x82, 0xC6, 
	0x81, 0x41, 0x82, 0xC2, 0x82, 0xA2, 0x82, 0xC9, 0x82, 0xBB, 
	0x82, 0xCC, 0x8E, 0x9E, 0x82, 0xAA, 0x97, 0x88, 0x82, 0xBD, 
	0x82, 0xCC, 0x82, 0xF0, 0x8A, 0xB4, 0x82, 0xB6, 0x81, 0x41, 
	0x95, 0x53, 0x89, 0xD4, 0x82, 0xCD, 0x82, 0xA4, 0x82, 0xC1, 
	0x82, 0xB7, 0x82, 0xE7, 0x82, 0xC6, 0x96, 0xDA, 0x82, 0xF0, 
	0x8A, 0x4A, 0x82, 0xAF, 0x82, 0xE9, 0x81, 0x42, 0x0A, 0x0A, 
	0x82, 0xBE, 0x82, 0xAA, 0x81, 0x41, 0x8D, 0xA1, 0x82, 0xDC, 
	0x82, 0xB3, 0x82, 0xC9, 0x94, 0xDE, 0x8F, 0x97, 0x82, 0xF0, 
	0x94, 0xC6, 0x82, 0xBB, 0x82, 0xA4, 0x82, 0xC6, 0x82, 0xB5, 
	0x82, 0xC4, 0x82, 0xA2, 0x82, 0xBD, 0x82, 0xCC, 0x82, 0xCD, 
	0x81, 0x41, 0x8A, 0x6F, 0x8C, 0xE5, 0x82, 0xF0, 0x8C, 0x88, 
	0x82, 0xDF, 0x82, 0xC4, 0x82, 0xA2, 0x82, 0xBD, 0x8C, 0x5A, 
	0x82, 0xC5, 0x82, 0xCD, 0x82, 0xC8, 0x82, 0xAD, 0x82, 0xBB, 
	0x82, 0xCC, 0x97, 0x46, 0x90, 0x6C, 0x82, 0xBE, 0x82, 0xC1, 
	0x82, 0xBD, 0x81, 0x42, 0x0A, 0x0A, 0x81, 0x75, 0x83, 0x52, 
	0x83, 0x43, 0x83, 0x63, 0x81, 0x41, 0x82, 0xA8, 0x91, 0x4F, 
	0x82, 0xCC, 0x82, 0xB1, 0x82, 0xC6, 0x8D, 0x44, 0x82, 0xAB, 
	0x82, 0xE7, 0x82, 0xB5, 0x82, 0xA2, 0x82, 0xBA, 0x81, 0x42, 
	0x82, 0xBB, 0x82, 0xF1, 0x82, 0xC8, 0x82, 0xC9, 0x94, 0xC6, 
	0x82, 0xB3, 0x82, 0xEA, 0x82, 0xBD, 0x82, 0xA2, 0x82, 0xC8, 
	0x82, 0xE7, 0x81, 0x41, 0x82, 0xE2, 0x82, 0xC1, 0x82, 0xC4, 
	0x82, 0xE0, 0x82, 0xE7, 0x82, 0xA6, 0x82, 0xE6, 0x81, 0x76, 
	0x0A, 0x0A, 0x8B, 0xDF, 0x90, 0x65, 0x91, 0x8A, 0x8A, 0xAD, 
	0x82, 0xD6, 0x82, 0xCC, 0x8A, 0x89, 0x96, 0x5D, 0x82, 0xC6, 
	0x95, 0x7C, 0x82, 0xEA, 0x82, 0xC9, 0x98, 0x63, 0x82, 0xF1, 
	0x82, 0xBE, 0x8C, 0x5A, 0x82, 0xCC, 0x8A, 0xB4, 0x8F, 0xEE, 
	0x82, 0xAA, 0x81, 0x41, 0x82, 0xDC, 0x82, 0xB3, 0x82, 0xA9, 
	0x82, 0xCC, 0x8E, 0x53, 0x8C, 0x80, 0x82, 0xCC, 0x96, 0x8B, 
	0x82, 0xF0, 0x8A, 0x4A, 0x82, 0xAD, 0x81, 0x5C, 0x81, 0x5C, 
	0x0A, 0x0A, 0x81, 0x77, 0x89, 0xF3, 0x82, 0xB5, 0x82, 0xC4, 
	0x82, 0xE2, 0x82, 0xE9, 0x81, 0x42, 0x8E, 0xE8, 0x82, 0xC9, 
	0x93, 0xFC, 0x82, 0xE7, 0x82, 0xC8, 0x82, 0xA2, 0x82, 0xC8, 
	0x82, 0xE7, 0x81, 0x41, 0x82, 0xA2, 0x82, 0xC1, 0x82, 0xBB, 
	0x81, 0x41, 0x89, 0xB4, 0x82, 0xCC, 0x8E, 0xE8, 0x82, 0xC5, 
	0x81, 0x5C, 0x81, 0x5C, 0x81, 0x78, 0x0A, 0x0A, 0xF0, 0x5E, 
	0x4F, 0xE2, 0xFB, 0x61, 0x20, 0x5F, 0x02, 0x38, 0x6A, 0x92, 
	0xD3, 0x86, 0xDB, 0x4C, 0x75, 0x71, 0x16, 0xE1, 0x49, 0xDB, 
	0xDB, 0x8A, 0x5C, 0x38, 0xFE, 0xFE, 0x85, 0xB8, 0xBE, 0x02, 
	0x84, 0x7A, 0xFE, 0x6C, 0x6B, 0xD7, 0xC8, 0xAE, 0x9D, 0xD8, 
	0x43, 0xA6, 0x62, 0x4A, 0x16, 0xDC, 0xA7, 0xD0, 0x9E, 0xB5, 
	0x9D, 0xB2, 0xFA, 0x66, 0x1E, 0xFC, 0xAD, 0x48, 0x6A, 0xB1, 
	0x15, 0xE6, 0x4C, 0xBC, 0xB6, 0x37, 0xC6, 0x5F, 0x18, 0x93, 
	0xD7, 0x1B, 0x01, 0xAF, 0x49, 0xD7, 0x26, 0x41, 0x62, 0x20, 
	0x5A, 0xC3, 0x70, 0xFF, 0x96, 0xC9, 0x17, 0x76, 0x0E, 0xD8, 
	0x5D, 0x25, 0xCE, 0x42, 0xF0, 0x03, 0xB5, 0x96, 0xE0, 0x2B, 
	0x1D, 0xD3, 0x69, 0xFC, 0xA6, 0x00, 0xB5, 0x49, 0x6D, 0xC2, 
	0x8B, 0x94, 0x63, 0xE0, 0x31, 0x85, 0x24, 0xFF, 0x97, 0x9F, 
	0x20, 0xD5, 0xBD, 0x00, 0x38, 0x21, 0xFF, 0xF6, 0xBD, 0xAE, 
	0xD4, 0x2C, 0x77, 0x0E, 0x20, 0xD8, 0x8A, 0x84, 0x2E, 0x7D, 
	0x61, 0x80, 0x5A, 0x62, 0x27, 0x35, 0x22, 0xC8, 0x71, 0xE5, 
	0x73, 0x06, 0x26, 0xA9, 0x37, 0xF2, 0x71, 0xA3, 0x9E, 0xBB, 
	0x64, 0xBF, 0xFC, 0x3E, 0x5D, 0x61, 0x39, 0x20, 0x69, 0xE5, 
	0x10, 0xA5, 0x0D, 0x98, 0x1C, 0x05, 0x66, 0x81, 0xCB, 0xB7, 
	0xCB, 0xEE, 0x64, 0xA0, 0x63, 0x54, 0x11, 0x7D, 0x70, 0xFB, 
	0xAF, 0x8F, 0x97, 0x46, 0x8C, 0x4D, 0x98, 0x41, 0x87, 0xFC, 
	0xC3, 0x66, 0x35, 0x96, 0x0F, 0x01, 0x22, 0x7B, 0x34, 0x44, 
	0x76, 0x80, 0x95, 0xE0, 0x3B, 0xF5, 0x41, 0xA8, 0x93, 0x7C, 
	0x7A, 0xB0, 0xF2, 0x11, 0x94, 0xD7, 0x47, 0x9A, 0x04, 0xB8, 
	0x45, 0x91, 0x9B, 0x1A, 0x12, 0xFD, 0x9A, 0xC4, 0x40, 0x55, 
	0xFB, 0x15, 0x13, 0x93, 0x58, 0x05, 0x86, 0x0F, 0x11, 0xCB, 
	0x58, 0x89, 0xAF, 0x4D, 0xE2, 0xF9, 0x6C, 0x5A, 0xC7, 0x3B, 
	0xC5, 0x0F, 0x2C, 0xAF, 0xCA, 0xEA, 0xEB, 0x44, 0xF3, 0x7E, 
	0x5F, 0x8B, 0xF7, 0xAC, 0xE6, 0xCA, 0x1E, 0x7B, 0x2C, 0xBF, 
	0xE2, 0x79, 0x21, 0x14, 0x2C, 0x31, 0x91, 0x7C, 0xB9, 0x89, 
	0x69, 0x87, 0x7D, 0x28, 0x7C, 0x78, 0x7B, 0xD5, 0x9D, 0xE1, 
	0x26, 0xA1, 0x3A, 0xA7, 0x6B, 0xD9, 0x33, 0x8F, 0x37, 0x74, 
	0x57, 0x56, 0x4A, 0x2E, 0x72, 0x62, 0x57, 0x50, 0xF8, 0x19, 
	0xD3, 0x38, 0xCE, 0x2C, 0x76, 0x87, 0xD7, 0x50, 0xAD, 0x18, 
	0x84, 0x55, 0xBF, 0x22, 0x23, 0xB8, 0x58, 0xAC, 0x58, 0x51, 
	0x86, 0x36, 0x43, 0x3D, 0xE5, 0x80, 0x12, 0xC9, 0x28, 0x30, 
	0x91, 0x1E, 0xFA, 0xF5, 0x39, 0xAB, 0x90, 0x44, 0xF9, 0xF0, 
	0xB5, 0x0A, 0x51, 0x0E, 0x23, 0xC9, 0xBE, 0x5F, 0xA9, 0x7C, 
	0x33, 0x43, 0x02, 0xDD, 0x93, 0x3E, 0x8D, 0x54, 0x1E, 0x38, 
	0x2B, 0xAD, 0x59, 0x81, 0xC1, 0xEC, 0x97, 0xC8, 0xA9, 0x3B, 
	0x58, 0x37, 0x3B, 0x53, 0x5B, 0xB9, 0x85, 0xF4, 0xC3, 0x54, 
	0x9B, 0x61, 0xF6, 0xEB, 0x37, 0x05, 0x6C, 0x3B, 0x06, 0x95, 
	0x46, 0x1B, 0x81, 0xA6, 0x64, 0x3B, 0xFE, 0x97, 0x92, 0x1D, 
	0x79, 0x0D, 0x48, 0x07, 0x6A, 0x6F, 0xBE, 0x46, 0xF3, 0x93, 
	0xF1, 0x50, 0xDF, 0x59, 0xF9, 0xF3, 0xC3, 0x21, 0x77, 0x95, 
	0xB6, 0x81, 0x0E, 0x78, 0xDD, 0x4E, 0x17, 0x45, 0x1C, 0xF6, 
	0x1C, 0x17, 0x37, 0x6D, 0x5A, 0xF3, 0xB2, 0x70, 0xD5, 0x8E, 
	0xF9, 0x6E, 0x06, 0xA2, 0x77, 0x47, 0x58, 0x5D, 0x5A, 0xB7, 
	0xF2, 0x45, 0x87, 0xEC, 0x3E, 0xE7, 0x07, 0xED, 0xEE, 0x44, 
	0xCB, 0x0D, 0xFA, 0x66, 0xB1, 0xE4, 0xB6, 0xA5, 0x17, 0xA9, 
	0x54, 0xF7, 0xB8, 0x4B, 0x26, 0xAD, 0xCF, 0x80, 0xF0, 0xEA, 
	0xC3, 0x92, 0xEE, 0xD5, 0x25, 0x6B, 0x61, 0xD4, 0x0F, 0x8D, 
	0x37, 0x28, 0x8B, 0x31, 0x36, 0x8F, 0xD9, 0xFE, 0x68, 0xAB, 
	0x2F, 0x85, 0x80, 0x73, 0x79, 0x49, 0x0D, 0xD7, 0x93, 0x5C, 
	0x44, 0x31, 0x0B, 0x3F, 0x92, 0xD6, 0x54, 0x2A, 0xA8, 0xFE, 
	0x00, 0x4D, 0xD4, 0x2E, 0x46, 0x21, 0x1B, 0xEC, 0xA4, 0x1A, 
	0x80, 0x27, 0x29, 0xBF, 0xF3, 0xB2, 0x85, 0x98, 0x33, 0x1A, 
	0xC2, 0x9B, 0x2E, 0x9E, 0xBF, 0x60, 0x56, 0x69, 0x68, 0xA7, 
	0x98, 0x6A, 0x92, 0xF0, 0xAE, 0x8F, 0x24, 0x6B, 0x1A, 0x98, 
	0x4A, 0x2E, 0x10, 0xBD, 0x42, 0x66, 0x5C, 0xB9, 0x6B, 0x2F, 
	0xED, 0x85, 0x44, 0x4E, 0xB7, 0x5E, 0x93, 0x3C, 0xC8, 0xC9, 
	0x4C, 0xB4, 0x36, 0xEF, 0x8C, 0x00, 0x2C, 0x1C, 0x56, 0x24, 
	0xCB, 0x05, 0x9A, 0x41, 0x41, 0xA7, 0x50, 0x23, 0x3C, 0xB3, 
	0x4C, 0x95, 0xCC, 0x79, 0x3F, 0x59, 0xBD, 0xA7, 0x4F, 0x2D, 
	0x7B, 0xAE, 0xAD, 0x39, 0x22, 0x3A, 0x3A, 0x84, 0xCF, 0x3A, 
	0x5E, 0xE2, 0x84, 0x48, 0xF5, 0x30, 0x8E, 0x82, 0x69, 0xDB, 
	0xDA, 0x9E, 0x60, 0x29, 0x7A, 0xB0, 0x60, 0xB9, 0x44, 0x3B, 
	0xBD, 0x52, 0x82, 0xE9, 0x0D, 0x60, 0xC9, 0xBA, 0xBE, 0xEF, 
	0xE8, 0xA1, 0x12, 0x11, 0xE4, 0x4A, 0xCF, 0xDA, 0x06, 0x01, 
	0xF9, 0x8C, 0x40, 0xBB, 0x6F, 0x4B, 0x83, 0x9F, 0xAA, 0xA8, 
	0xE3, 0xC9, 0x7E, 0x8B, 0x57, 0x5D, 0xD2, 0x68, 0xB0, 0xB2, 
	0x3A, 0xB2, 0xDE, 0x5F, 0x9E, 0x82, 0x5B, 0xB7, 0x32, 0x74, 
	0x8C, 0x09, 0xD1, 0x07, 0x4B, 0xD2, 0x59, 0x30, 0xFA, 0x19, 
	0x6F, 0x7A, 0x06, 0x8E, 0xB4, 0x4F, 0xD9, 0x72, 0x25, 0x63, 
	0x60, 0xBD, 0xE7, 0x83, 0xEC, 0x41, 0x7F, 0x57, 0xED, 0x42, 
	0xBC, 0x46, 0x1A, 0x82, 0x84, 0xA0, 0xEE, 0x6B, 0x10, 0xA2, 
	0xF0, 0x3E, 0x0B, 0x54, 0x5C, 0x4F, 0xC7, 0xB9, 0x69, 0xA2, 
	0x35, 0xB8, 0x33, 0x33, 0x22, 0xC0, 0x60, 0x6F, 0x0A, 0x38, 
	0xF5, 0xAD, 0x4F, 0x2B, 0x2A, 0xFA, 0x29, 0x31, 0x6E, 0xE3, 
	0x4C, 0x7D, 0xDE, 0xC5, 0x97, 0x60, 0x56, 0x11, 0x00, 0x77, 
	0x9D, 0x4E, 0x83, 0x62, 0xAA, 0xC7, 0x4B, 0x57, 0x5D, 0x5F, 
	0x95, 0xD2, 0x91, 0xA3, 0xCD, 0x55, 0xBB, 0x52, 0xAD, 0x64, 
	0xA5, 0xBE, 0x43, 0x74, 0xD4, 0xF9, 0x16, 0x4C, 0x3D, 0xAE, 
	0xD2, 0x7A, 0xDC, 0xE9, 0x65, 0x9F, 0x8A, 0x7B, 0x85, 0x7A, 
	0x99, 0x1E, 0xBA, 0x23, 0x1E, 0x92, 0x41, 0xF8, 0x61, 0x32, 
	0x50, 0xCB, 0xC3, 0x52, 0x07, 0xBA, 0x1E, 0xA8, 0x2C, 0x17, 
	0xEB, 0x58, 0xAE, 0xFA, 0xB7, 0xE9, 0x85, 0xC2, 0xDA, 0x67, 
	0x0B, 0xA2, 0xD0, 0xCD, 0x78, 0x40, 0xD5, 0xA7, 0xCB, 0x9A, 
	0x84, 0x8F, 0x24, 0xCC, 0xB9, 0x37, 0xF9, 0xD9, 0xE4, 0xE5, 
	0x84, 0x2A, 0x8F, 0xCF, 0xCB, 0xBF, 0xFD, 0x8C, 0x60, 0xF2, 
	0xF6, 0xBA, 0xA6, 0x59, 0xBF, 0x10, 0xA3, 0x7F, 0x7C, 0x79, 
	0x07, 0x5A, 0x1F, 0x89, 0xC4, 0x4E, 0xBC, 0xDC, 0x4F, 0xEF, 
	0x8C, 0x15, 0x07, 0xBC, 0x9E, 0x6C, 0xF6, 0x6A, 0x45, 0xDF, 
	0x7A, 0xDA, 0x4F, 0x1F, 0x39, 0xFF, 0x39, 0x9F, 0xD0, 0x4D, 
	0x01, 0xE3, 0xEF, 0x17, 0x81, 0x43, 0x07, 0xBF, 0xA6, 0x04, 
	0x13, 0x5D, 0x14, 0x43, 0xB9, 0x8E, 0xCC, 0x88, 0x8D, 0x1A, 
	0x77, 0x97, 0x95, 0x76, 0x27, 0xDD, 0x37, 0xF6, 0x64, 0x48, 
	0xAB, 0x38, 0xA7, 0xFE, 0xFB, 0x44, 0x8F, 0x90, 0x31, 0xDD, 
	0xF7, 0x33, 0x25, 0x17, 0xDD, 0x4D, 0xDE, 0x5E, 0x75, 0x94, 
	0x34, 0x47, 0xE2, 0x6B, 0x5D, 0x5D, 0x09, 0xCC, 0xA8, 0x76, 
	0x7B, 0xDA, 0xA3, 0xE7, 0xE1, 0xCE, 0x36, 0x2C, 0x31, 0x59, 
	0xD4, 0x4F, 0x70, 0xC3, 0x65, 0xB7, 0xCB, 0xD7, 0x8C, 0xC4, 
	0x19, 0x11, 0x91, 0x4A, 0xE8, 0x46, 0x51, 0xE2, 0xBF, 0x16, 
	0xA9, 0x98, 0x8C, 0x39, 0x79, 0xBF, 0xF8, 0x17, 0x53, 0x17, 
	0x50, 0x6D, 0xC8, 0x0E, 0x47, 0x33, 0x4A, 0x6A, 0xC5, 0x86, 
	0x44, 0x69, 0x7B, 0x56, 0x70, 0xD3, 0x5C, 0x28, 0xB0, 0xF1, 
	0xB8, 0xBD, 0x1B, 0x50, 0x3B, 0xDF, 0x56, 0x3B, 0x5A, 0xE1, 
	0x09, 0xA9, 0x3C, 0xAD, 0x79, 0x95, 0xC4, 0x55, 0xF0, 0x21, 
	0x4A, 0x15, 0x45, 0x3A, 0xA1, 0x10, 0x00, 0x12, 0xAA, 0x73, 
	0xD3, 0x49, 0x3B, 0x03, 0x60, 0x8C, 0x2E, 0xC7, 0x24, 0xAD, 
	0x38, 0x1A, 0x4E, 0x94, 0xAA, 0x7E, 0x66, 0x67, 0x99, 0xEF, 
	0xF4, 0x92, 0x28, 0x53, 0x53, 0x3A, 0xE7, 0x2C, 0xB6, 0xC0, 
	0x9E, 0xEF, 0x51, 0x7B, 0x8D, 0xB3, 0xB3, 0x96, 0x0E, 0x81, 
	0xD1, 0xE8, 0x06, 0x42, 0x31, 0x21, 0x51, 0xD9, 0xA4, 0xD5, 
	0xF5, 0x8A, 0x38, 0x35, 0x46, 0x90, 0x88, 0x8C, 0xEC, 0xED, 
	0x87, 0x14, 0x5A, 0x79, 0x98, 0x31, 0x0D, 0xA4, 0x9D, 0x49, 
	0x9C, 0x03, 0x20, 0xC3, 0x5C, 0xDF, 0x54, 0xEC, 0x6C, 0x1C, 
	0x8B, 0xCB, 0xDF, 0x14, 0xB2, 0x17, 0x0C, 0xB5, 0xD0, 0x6E, 
	0x92, 0x6C, 0xC0, 0xED, 0x14, 0x1F, 0x7C, 0x52, 0x68, 0x9A, 
	0x82, 0xC4, 0x68, 0x55, 0xA9, 0xE9, 0x2C, 0x88, 0xEA, 0x15, 
	0xCB, 0x39, 0xC4, 0xF4, 0xB2, 0x0E, 0x6D, 0xEA, 0x65, 0x0A, 
	0x6C, 0x5A, 0x60, 0x81, 0x30, 0xCE, 0x86, 0x74, 0x10, 0x5F, 
	0xE5, 0x67, 0x93, 0x39, 0x1A, 0x03, 0xD5, 0xEB, 0x61, 0x6D, 
	0x3F, 0x10, 0xC3, 0x25, 0xE1, 0x11, 0x4A, 0xD0, 0x39, 0x73, 
	0xA2, 0xF1, 0x70, 0xE2, 0x03, 0xDC, 0x38, 0x3D, 0xEC, 0x31, 
	0x70, 0xAA, 0x4A, 0xE5, 0xDB, 0x31, 0xAC, 0x5E, 0xE4, 0xAC, 
	0x84, 0xBB, 0xAE, 0xE6, 0xA9, 0x1A, 0x37, 0xB7, 0x6A, 0x03, 
	0xE4, 0xBC, 0x78, 0xC9, 0x46, 0x6E, 0xE8, 0x80, 0x62, 0xC5, 
	0x18, 0xE0, 0x89, 0xD8, 0xB3, 0x2D, 0xE5, 0x35, 0xAD, 0x88, 
	0x68, 0x94, 0x9C, 0x3B, 0x5A, 0x32, 0xB8, 0x54, 0x1B, 0x4E, 
	0x69, 0x15, 0x67, 0x60, 0xA1, 0x3A, 0x2A, 0xE6, 0x43, 0x35, 
	0xB9, 0x72, 0xB0, 0xD1, 0x1C, 0x27, 0x61, 0x31, 0x81, 0xA6, 
	0xFF, 0xFE, 0x7A, 0x0F, 0x07, 0x43, 0x67, 0xE5, 0x12, 0x24, 
	0x3B, 0xD4, 0x10, 0xF9, 0x9C, 0x52, 0xD7, 0xBD, 0x2E, 0x38, 
	0x9B, 0x14, 0x8B, 0x28, 0x6E, 0x58, 0xC0, 0x13, 0xD8, 0xB5, 
	0x93, 0xF6, 0x19, 0xF8, 0xF1, 0xDB, 0xC6, 0x00, 0x9E, 0xF3, 
	0xDB, 0x41, 0x15, 0x88, 0x6D, 0x31, 0xA2, 0x87, 0x6C, 0xF2, 
	0x66, 0x24, 0x8A, 0xDC, 0xBC, 0xAC, 0x0F, 0xDA, 0x5E, 0x30, 
	0x5F, 0x3F, 0xE3, 0x5E, 0xF6, 0x89, 0x8F, 0x4F, 0x1E, 0xF5, 
	0x5F, 0x24, 0xB8, 0x74, 0xAF, 0xBF, 0x32, 0xAB, 0x9A, 0xC7, 
	0x03, 0x7C, 0x2A, 0x52, 0x01, 0x22, 0x43, 0x19, 0xD3, 0x25, 
	0x33, 0xE4, 0x94, 0xAC, 0x60, 0xA6, 0x93, 0x14, 0xE5, 0xFE, 
	0x98, 0x66, 0x07, 0x54, 0x66, 0x0B, 0x4E, 0x22, 0xB5, 0x14, 
	0xFB, 0x70, 0x57, 0xFE, 0xE9, 0x3B, 0x80, 0xBB, 0x2C, 0x8C, 
	0x61, 0x17, 0xD3, 0x1A, 0x25, 0x7B, 0xA9, 0x3F, 0x84, 0x12, 
	0xCB, 0x98, 0x11, 0x6A, 0xD0, 0x24, 0x24, 0x17, 0xA0, 0xAD, 
	0x11, 0x5C, 0x40, 0x23, 0x23, 0x47, 0xA0, 0x5C, 0xE1, 0x03, 
	0x95, 0x78, 0xF4, 0x94, 0xD3, 0x0F, 0x16, 0x82, 0x10, 0x2D, 
	0xAF, 0x10, 0xAB, 0x9A, 0x79, 0xF1, 0xF0, 0x46, 0x85, 0xFB, 
	0x73, 0x73, 0xA3, 0x5B, 0x74, 0x95, 0x27, 0xA2, 0xE8, 0xB8, 
	0x3F, 0x18, 0xB3, 0x64, 0x87, 0x14, 0x8C, 0x19, 0x32, 0xD8, 
	0x90, 0xB6, 0x8E, 0x9D, 0x34, 0x57, 0x97, 0x29, 0xB4, 0x45, 
	0xC2, 0xC4, 0x1D, 0x46, 0x1E, 0xFA, 0xCE, 0x1F, 0xBA, 0xE2, 
	0x17, 0x22, 0x77, 0xEE, 0xCB, 0x99, 0xED, 0xA1, 0x6C, 0x4C, 
	0x81, 0x68, 0x03, 0xE6, 0x70, 0x5E, 0xE8, 0x89, 0xC2, 0x99, 
	0x10, 0xAC, 0xD6, 0xFE, 0x33, 0x10, 0x46, 0x28, 0x81, 0x60, 
	0x01, 0xFF, 0xDA, 0xD7, 0xBE, 0x9A, 0xEB, 0xF5, 0x0A, 0xCB, 
	0xF4, 0xD4, 0x35, 0x73, 0x8D, 0x5A, 0xB8, 0xDB, 0xAF, 0x6C, 
	0xA8, 0x68, 0xF7, 0x5A, 0x81, 0x39, 0xE4, 0x0D, 0xB7, 0x96, 
	0x08, 0x76, 0xBB, 0x41, 0x43, 0xE2, 0xD8, 0x09, 0x20, 0xAB, 
	0x9A, 0x36, 0xBD, 0x2F, 0x53, 0xFC, 0x4E, 0x88, 0xCC, 0xB3, 
	0x33, 0xAE, 0x3B, 0x15, 0xA4, 0x94, 0x54, 0x2D, 0xED, 0x4D, 
	0x1F, 0x49, 0xF2, 0xE9, 0x77, 0xB9, 0x27, 0xD7, 0x64, 0xE8, 
	0x1E, 0x70, 0x18, 0x99, 0xEC, 0xAF, 0xE1, 0x8D, 0x0F, 0xE6, 
	0x97, 0x83, 0x24, 0x61, 0xAF, 0x60, 0xE2, 0xF3, 0xFA, 0x92, 
	0xA3, 0x77, 0xFF, 0x1D, 0x2F, 0xC1, 0x5C, 0x78, 0xDD, 0x4A, 
	0x0E, 0x3C, 0xAE, 0x50, 0x97, 0x2F, 0xC3, 0xBC, 0xFD, 0x3E, 
	0xB0, 0x3F, 0x17, 0xB1, 0x03, 0x01, 0x0D, 0x8F, 0x15, 0x12, 
	0x6C, 0x25, 0x1F, 0x72, 0x9E, 0xFC, 0x0A, 0xCA, 0xDF, 0xA3, 
	0x13, 0x55, 0x5A, 0xDA, 0xC9, 0xE7, 0x0C, 0x48, 0xC1, 0x00, 
	0x94, 0x93, 0x0D, 0x72, 0x1E, 0x26, 0x28, 0x46, 0xF2, 0x29, 
	0xB0, 0x93, 0xBA, 0xC8, 0xFA, 0xBA, 0x85, 0x6E, 0x38, 0xF6, 
	0x90, 0xC7, 0x49, 0x65, 0x11, 0x5F, 0x7E, 0x68, 0x71, 0xC7, 
	0xEE, 0xBA, 0xAF, 0xCE, 0xDD, 0xF1, 0x94, 0x5D, 0x3D, 0x33, 
	0xCF, 0x8B, 0x3D, 0x18, 0xC8, 0xB1, 0xA6, 0xA2, 0x13, 0x74, 
	0xCA, 0xCC, 0x7E, 0x81, 0xD5, 0xCD, 0xBA, 0x37, 0x03, 0xDB, 
	0x43, 0x94, 0xF1, 0x7C, 0xD1, 0xF5, 0x57, 0x55, 0x32, 0xB6, 
	0xC1, 0x88, 0xA9, 0x37, 0x59, 0x19, 0x0E, 0x59, 0xB5, 0xFD, 
	0x39, 0xA9, 0xB2, 0x13, 0x3C, 0x74, 0x5E, 0xB1, 0xB8, 0x28, 
	0x8D, 0x47, 0x94, 0x29, 0xDA, 0xAC, 0x58, 0xF8, 0xF7, 0xFA, 
	0xC8, 0x28, 0x87, 0x9F, 0xDA, 0x01, 0xE7, 0x73, 0x08, 0x3C, 
	0x20, 0x24, 0x3E, 0xBC, 0xF6, 0xD9, 0x76, 0x07, 0x94, 0x3D, 
	0xFB, 0x37, 0x66, 0x0C, 0x49, 0xE7, 0x7A, 0xC8, 0x45, 0x53, 
	0x1D, 0xEE, 0x77, 0xA9, 0x36, 0xF2, 0xCD, 0x83, 0xCA, 0xD8, 
	0xB4, 0x6D, 0x23, 0xC2, 0xFB, 0xAE, 0x62, 0x3E, 0xA5, 0x23, 
	0xE4, 0xEC, 0xCC, 0x3F, 0x01, 0x9C, 0xDC, 0x40, 0xA8, 0x0B, 
	0xDB, 0x0E, 0x50, 0xE2, 0xA8, 0xF8, 0x7A, 0x13, 0x45, 0x29, 
	0x0D, 0xF9, 0x75, 0xE0, 0xAE, 0x6A, 0x9F, 0xD6, 0x41, 0x08, 
	0xDC, 0x46, 0xA4, 0xD3, 0x84, 0xBF, 0x4F, 0xAD, 0x4B, 0xAD, 
	0x3D, 0xC9, 0x22, 0xED, 0x15, 0x30, 0x82, 0xA1, 0x3E, 0xD3, 
	0xC7, 0xB5, 0x4D, 0xDF, 0x45, 0x21, 0x74, 0x80, 0x1D, 0x4C, 
	0x38, 0x91, 0xFE, 0xD4, 0xFF, 0x44, 0x55, 0x0B, 0x08, 0x08, 
	0x96, 0xE9, 0x56, 0x29, 0xF7, 0x8E, 0x3B, 0xE3, 0x56, 0xDC, 
	0x09, 0x1B, 0x1B, 0x2B, 0xA9, 0xA8, 0x0E, 0xBB, 0x8C, 0x6D, 
	0x29, 0x7F, 0xBB, 0xF5, 0x84, 0xC3, 0x5E, 0x2A, 0x7F, 0x38, 
	0xF7, 0x1D, 0x23, 0x01, 0xF4, 0x55, 0x48, 0xB0, 0xA0, 0x49, 
	0xC6, 0xE2, 0x6E, 0x28, 0xDE, 0xE3, 0x1A, 0x33, 0xCE, 0x81, 
	0xB2, 0x1D, 0x9C, 0x32, 0x97, 0x96, 0xBB, 0x8D, 0xC5, 0x44, 
	0x9B, 0xE4, 0x7B, 0x1E, 0xBD, 0xAC, 0x3F, 0x4C, 0x5B, 0xE8, 
	0xEA, 0x56, 0x78, 0x6B, 0x1B, 0xB7, 0xC2, 0x0C, 0x17, 0x73, 
	0xEC, 0x16, 0x29, 0xD0, 0x78, 0x69, 0xE8, 0xE7, 0xB4, 0x40, 
	0xC7, 0x22, 0x84, 0xBA, 0x38, 0xC0, 0x30, 0xA0, 0x61, 0x21, 
	0x38, 0x8C, 0xC0, 0x90, 0xA8, 0xDC, 0x4D, 0xDD, 0x4B, 0x16, 
	0xAC, 0x01, 0x9D, 0x46, 0x70, 0xAB, 0x7C, 0xFE, 0x22, 0xB5, 
	0x42, 0xCE, 0x8E, 0xEB, 0xD8, 0x00, 0xD4, 0x9E, 0x4E, 0x17, 
	0x45, 0xAA, 0x29, 0x7B, 0xEE, 0x92, 0x13, 0x99, 0xD7, 0x43, 
	0x12, 0xC4, 0x8E, 0xBB, 0x2D, 0x5E, 0xF1, 0x28, 0xE0, 0x21, 
	0xBA, 0xCA, 0x5E, 0xC0, 0x06, 0x87, 0x8B, 0xFB, 0x1C, 0xD6, 
	0xFD, 0x72, 0x6F, 0xD2, 0xA0, 0xA2, 0x25, 0x4E, 0xFC, 0x86, 
	0x51, 0xD2, 0x86, 0xB3, 0x70, 0x2E, 0x6D, 0x2D, 0x6A, 0x43, 
	0xEB, 0x11, 0xEB, 0x49, 0xD6, 0x4F, 0xA0, 0x75, 0xA3, 0x07, 
	0x6E, 0x4A, 0x26, 0x95, 0x74, 0xD8, 0xE1, 0xD6, 0x5B, 0xB4, 
	0x09, 0xB5, 0x54, 0x8B, 0x56, 0xBC, 0x4B, 0x0F, 0xAE, 0x2C, 
	0x07, 0xFD, 0x4F, 0xA7, 0x02, 0x34, 0xF8, 0xB8, 0x6F, 0x06, 
	0x7C, 0x12, 0xAE, 0x00, 0x37, 0x65, 0x7F, 0xCE, 0x32, 0xAF, 
	0x85, 0x8D, 0xC6, 0x82, 0x50, 0x42, 0xF7, 0x92, 0x2D, 0x38, 
	0x5A, 0x53, 0xCD, 0xA8, 0x3A, 0x3A, 0xE3, 0xE9, 0xAA, 0xE0, 
	0x6F, 0x90, 0x84, 0xE0, 0x13, 0x12, 0x00, 0x70, 0xFC, 0xDB, 
	0xF2, 0x08, 0x72, 0x33, 0xC1, 0x15, 0x87, 0x9D, 0x34, 0x09, 
	0xB7, 0x04, 0xAA, 0x9D, 0xA5, 0xB1, 0xB5, 0xBB, 0x04, 0x41, 
	0xD6, 0x7B, 0x5B, 0xBC, 0x7F, 0x07, 0xA7, 0x5F, 0x38, 0x45, 
	0x2D, 0x69, 0x4E, 0xA3, 0xC1, 0x47, 0x8B, 0x14, 0x10, 0x5A, 
	0x67, 0xCB, 0x1F, 0x53, 0x70, 0xAE, 0xBB, 0xC2, 0xE9, 0xA8, 
	0x6E, 0xEF, 0xE6, 0x85, 0xF3, 0xCA, 0xF4, 0xE3, 0x4C, 0x89, 
	0x19, 0xF4, 0xB9, 0x78, 0x0E, 0x03, 0xE6, 0x2A, 0xCD, 0x3C, 
	0xD6, 0x77, 0x44, 0x43, 0x2D, 0x89, 0xCE, 0x7B, 0x3C, 0x9B, 
	0x44, 0x0B, 0x40, 0x38, 0x2A, 0x4B, 0x7F, 0x38, 0xAD, 0xA1, 
	0x32, 0xC5, 0xDE, 0xB9, 0x89, 0xDA, 0xF6, 0xEE, 0xDB, 0x54, 
	0x7F, 0xAD, 0x17, 0x89, 0x0D, 0xE5, 0xBE, 0xAE, 0xFD, 0xBF, 
	0x2E, 0x53, 0xF8, 0x7A, 0xAC, 0x26, 0xDA, 0x72, 0x84, 0x1E, 
	0x1A, 0x95, 0x64, 0xEF, 0x5C, 0x1D, 0x0B, 0xB4, 0x23, 0x92, 
	0x29, 0x5F, 0x31, 0x9D, 0xE7, 0x76, 0x5E, 0xB2, 0xF6, 0xEF, 
	0xB7, 0xB4, 0xE9, 0xD0, 0x8B, 0x76, 0x2A, 0x85, 0xAC, 0xDD, 
	0xF1, 0xB5, 0x4D, 0xE6, 0xEB, 0x73, 0x36, 0x70, 0x81, 0xC4, 
	0xD6, 0xAE, 0x83, 0xFD, 0xF6, 0x43, 0xAC, 0xAB, 0x93, 0x16, 
	0x78, 0xAD, 0x3C, 0xAD, 0x17, 0x11, 0xC8, 0xC1, 0x32, 0xB6, 
	0x5D, 0xC8, 0x55, 0x4B, 0x9F, 0xB1, 0x16, 0x85, 0xA7, 0xD4, 
	0x00, 0x06, 0x93, 0x07, 0x9D, 0x9F, 0x64, 0x6B, 0x53, 0x66, 
	0xCD, 0xBD, 0x0D, 0x09, 0x60, 0xDF, 0x39, 0xD5, 0x3C, 0x5D, 
	0xE3, 0x3E, 0x3D, 0x42, 0x48, 0x72, 0x5A, 0x50, 0xC9, 0x9B, 
	0x3A, 0xC4, 0xF2, 0x8D, 0xA2, 0x24, 0xEF, 0xFD, 0x74, 0xF7, 
	0x87, 0xCD, 0x4F, 0x17, 0x14, 0xCE, 0xC9, 0x95, 0x23, 0xF2, 
	0x18, 0x38, 0xF1, 0xB7, 0x23, 0x6C, 0x9F, 0xFF, 0x5C, 0x0A, 
	0x7C, 0xBE, 0xC5, 0x77, 0x95, 0x41, 0x1F, 0x60, 0x05, 0xE1, 
	0x06, 0x4A, 0x0D, 0xD6, 0x05, 0xFA, 0x6D, 0xD7, 0x35, 0x9B, 
	0xFC, 0x10, 0x34, 0x7F, 0x0F, 0xFE, 0x64, 0x7F, 0x49, 0x8C, 
	0x69, 0xB4, 0xB9, 0x4D, 0x59, 0x80, 0xAC, 0x0C, 0xB8, 0x3C, 
	0x7F, 0xBA, 0x7E, 0x5D, 0xBB, 0xFD, 0x9B, 0x7F, 0xCE, 0x13, 
	0x31, 0x03, 0x40, 0x2A, 0x2A, 0x22, 0xCB, 0xB5, 0x3E, 0x32, 
	0xC6, 0x15, 0x48, 0x2B, 0x1F, 0xAA, 0x32, 0x40, 0x3B, 0xAC, 
	0xF5, 0x0D, 0x12, 0x3F, 0xC0, 0xBD, 0x7D, 0xC2, 0x02, 0x81, 
	0xF0, 0x4A, 0xE2, 0xB1, 0x70, 0xD5, 0xD7, 0xF9, 0xB1, 0x0E, 
	0xD2, 0xD6, 0x2C, 0xFE, 0x14, 0x5A, 0xE3, 0x0B, 0x5E, 0x2F, 
	0x2B, 0xF5, 0x1B, 0x69, 0x86, 0xA1, 0x47, 0xFA, 0x4F, 0x29, 
	0xFF, 0xC4, 0x1F, 0x40, 0xF0, 0x30, 0xCE, 0xE1, 0xED, 0x1E, 
	0xE2, 0x17, 0x45, 0x4C, 0x21, 0x9D
};

// 1E001490
static int xcode_building_first_stage(struct cxdec_xcode_status *xcode)
{
  	switch (xcode_rand(xcode) % 3) {
  	case 2:
		// MOV ESI, EncryptionControlBlock
		// MOV EAX, DWORD PTR DS:[ESI+((xcode_rand(xcode) & 0x3ff) << 2)]
		if (!push_bytexcode(xcode, 0xbe)
				|| !push_dwordxcode(xcode, (DWORD)EncryptionControlBlock)
				|| !push_2bytesxcode(xcode, 0x8b, 0x86)
				|| !push_dwordxcode(xcode, (xcode_rand(xcode) & 0x3ff) << 2))
			return 0;
		break;
	case 0:
  		// MOV EAX, EDI
  		if (!push_2bytesxcode(xcode, 0x8b, 0xc7))
  			return 0;
		break;
  	case 1:
		// MOV EAX, xcode_rand(xcode)
		if (!push_bytexcode(xcode, 0xb8)
				|| !push_dwordxcode(xcode, xcode_rand(xcode)))
			return 0;
  		break;
  	}
  	return 1;
}

// 1E001530
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
	case 3:
		// NOT EAX
		if (!push_2bytesxcode(xcode, 0xf7, 0xd0))
			return 0;
        break;
	case 0:
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
	case 7:
		// DEC EAX
		if (!push_bytexcode(xcode, 0x48))
			return 0;
        break;
	case 4:
		// NEG EAX
        if (!push_2bytesxcode(xcode, 0xf7, 0xd8))
			return 0;
		break;
	case 2:
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
	case 5:
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
	case 1:
		// INC EAX
		if (!push_bytexcode(xcode, 0x40))
			return 0;
		break;
	case 6:
		// XOR EAX, xcode_rand(xcode)
		if (!push_bytexcode(xcode, 0x35) 
				|| !push_dwordxcode(xcode, xcode_rand(xcode)))
			return 0;
        break;
	}
	return 1;
}

// 1E001790
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
	case 5:
		// ADD EAX, EBX
		if (!push_2bytesxcode(xcode, 0x01, 0xd8))
			return 0;
		break;
    case 0:
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
    case 1:
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
    case 2:
    	// NEG EAX, ADD EAX, EBX
		if (!push_2bytesxcode(xcode, 0xf7, 0xd8) 
				|| !push_2bytesxcode(xcode, 0x01, 0xd8))
			return 0;
		break;
    case 4:
    	// IMUL EAX, EBX
		if (!push_3bytesxcode(xcode, 0x0f,  0xaf, 0xc3))
			return 0;
		break;
    case 3:
    	// SUB EAX, EBX
		if (!push_2bytesxcode(xcode, 0x29, 0xd8))
			return 0;
		break;
	}
	// POP EBX
	return push_bytexcode(xcode, 0x5b);
}

struct cxdec_callback anioka_cxdec_callback = {
	"anioka",
	{ 0x20E, 0x649 },		// 用作计算第1部分哈希大小的两个数
	xcode_building_stage1
};
