// GENERATED FILE - DO NOT EDIT.
// Generated by gen_vk_internal_shaders.py.
//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// shaders/gen/ConvertVertex.comp.00000002.inc:
//   Pre-generated shader for the ANGLE Vulkan back-end.

#pragma once
constexpr uint8_t kConvertVertex_comp_00000002[] = {
    0x1f,0x8b,0x08,0x00,0x00,0x00,0x00,0x00,0x02,0xff,0x9d,0x98,0x77,0x70,0x57,0x45,
    0x10,0xc7,0xdf,0x4b,0xc2,0x2f,0x21,0xd4,0x50,0x12,0x22,0x21,0x12,0x3a,0xa4,0x10,
    0x85,0x80,0x0e,0xd2,0x66,0x10,0x50,0x41,0x11,0x14,0x85,0x0c,0x88,0x02,0x2a,0x2a,
    0x8a,0x80,0x0d,0xc1,0x4a,0x11,0x51,0x8a,0x8d,0x22,0x8a,0x22,0x4d,0x40,0xc4,0x0e,
    0x04,0x51,0x9a,0xd8,0x91,0x22,0x8a,0x58,0x66,0x74,0x06,0xcb,0x0c,0x48,0x51,0x14,
    0x2c,0x78,0xfb,0xde,0x67,0xcd,0x72,0xe6,0x2f,0x7f,0x33,0x6f,0x7e,0xb7,0xdf,0xad,
    0xb7,0xb7,0xb7,0x77,0xef,0x25,0x27,0x35,0x4e,0x0d,0x82,0x30,0x48,0x0f,0xd2,0x82,
    0x33,0xc2,0x20,0xfa,0x65,0x04,0x49,0x81,0x0c,0xab,0x04,0x89,0xe8,0xbf,0x47,0xaf,
    0x7e,0xbd,0x8a,0xc6,0x8c,0x1d,0x56,0xd4,0xb6,0xa4,0x58,0xf8,0xd5,0x83,0xe4,0x48,
    0x4e,0x78,0x35,0x9c,0x4c,0x25,0xf7,0x9f,0xe2,0x9e,0x91,0x57,0x8e,0xb8,0x51,0xf0,
    0xa3,0xee,0xa9,0xe9,0xf0,0x94,0xc8,0x56,0x10,0x74,0x41,0x56,0x9e,0x9e,0x4e,0xba,
    0x79,0xec,0x26,0x68,0xcc,0xbf,0x62,0x21,0x58,0x8a,0xc1,0x92,0xc0,0xd2,0x0c,0x96,
    0x0c,0x56,0xd5,0x60,0x29,0x60,0x35,0x0d,0x56,0x09,0xac,0x8e,0xc1,0x12,0x60,0xf5,
    0x0c,0x96,0x0a,0x96,0x63,0xb0,0x34,0xb0,0x86,0x06,0xab,0x0c,0xd6,0xc4,0x60,0xe9,
    0x60,0x2d,0x0c,0x56,0x05,0xac,0xc0,0x60,0x55,0xc1,0x8a,0x0d,0x56,0x0d,0xac,0xad,
    0xe4,0xd8,0xcd,0x4a,0xe7,0xdb,0xc3,0xcd,0x66,0x18,0xb1,0x6a,0x2e,0x86,0x7b,0x39,
    0x13,0xf9,0xe1,0xe4,0x42,0xe4,0xaf,0x71,0xff,0x8d,0xfe,0xe5,0xc5,0x74,0x1e,0x39,
    0x15,0xfa,0x80,0x67,0xef,0x60,0x05,0xf6,0x0e,0x1a,0x7b,0x87,0x3c,0x7b,0x87,0xb0,
    0xa7,0xf4,0x51,0xe6,0x99,0x03,0x5d,0x1c,0xc6,0x74,0xb6,0x7b,0x6a,0xbb,0x59,0x24,
    0x45,0xf2,0xc9,0x91,0x3d,0x19,0xd7,0x75,0x32,0x09,0xf2,0x19,0x44,0xff,0x29,0x51,
    0xde,0x53,0x89,0x2b,0xcf,0xc5,0x94,0xc6,0x58,0x71,0xd1,0xc9,0x40,0x27,0x8c,0x64,
    0x52,0x82,0x5a,0xd4,0x54,0x2a,0x36,0x32,0x19,0x0b,0x96,0xe9,0xbc,0x65,0x21,0x2f,
    0xb2,0xb2,0xc6,0x59,0x11,0x1e,0xcb,0xe6,0x20,0x9b,0x85,0xbf,0x06,0xc6,0x5f,0x0e,
    0x3a,0x8d,0x88,0x57,0xb0,0x5c,0x57,0x4d,0x5a,0x33,0xff,0xe7,0x11,0x9f,0x2d,0xa8,
    0x1b,0xb1,0xd3,0x01,0xba,0x25,0x58,0x3e,0xf3,0x6b,0x65,0xe4,0xf3,0xe1,0x25,0x0c,
    0xbf,0x98,0x5a,0x56,0xba,0x84,0x18,0xf3,0xc9,0x69,0x47,0xd6,0x55,0xe9,0xce,0xd4,
    0xaf,0xca,0x77,0xf7,0xe8,0x3e,0xc8,0xd7,0x71,0x56,0xfa,0x19,0xbd,0xfe,0xac,0xbf,
    0xca,0x95,0xb2,0x56,0x0d,0x1c,0xaa,0xf5,0x98,0x4b,0xdd,0x0d,0x23,0xde,0xab,0x89,
    0x65,0x38,0xf3,0x13,0xfa,0x1a,0x30,0xe1,0x5f,0xc7,0xd8,0xce,0x67,0x24,0xfb,0x41,
    0xfd,0x8e,0xc2,0x8f,0xf2,0x6f,0x63,0x5f,0x29,0x3d,0xc1,0x8b,0xeb,0x2e,0xf7,0x9c,
    0x4c,0x2e,0xa7,0xef,0x65,0x2f,0xa9,0xbd,0x07,0x8c,0xbe,0xd0,0x8f,0x7a,0xf9,0x5a,
    0x44,0x8d,0xa8,0xfe,0xf3,0x62,0xcf,0xfd,0x94,0x5e,0x41,0xbd,0xa9,0x7c,0x19,0xb4,
    0xcc,0xe7,0x1d,0x6a,0xa3,0x1f,0x79,0x39,0x60,0xf2,0x22,0xfb,0xe7,0x00,0x72,0x3f,
    0xe3,0xf3,0x20,0x79,0x11,0xfa,0x10,0x58,0x96,0xa3,0x0f,0xa3,0x97,0x8c,0xfc,0x11,
    0x7c,0x1c,0x46,0xfe,0x08,0x7d,0x54,0xfd,0xfe,0xc2,0x38,0x61,0xe2,0x6a,0x1d,0xc6,
    0xbd,0xb5,0xc0,0x51,0xa2,0x27,0x7b,0x50,0xb0,0x32,0x62,0x6e,0xe7,0xaa,0x26,0x89,
    0xb5,0x0e,0xf0,0xf5,0xbb,0x43,0x2a,0xe1,0x43,0xe6,0x51,0x29,0x8c,0xe7,0xa3,0x74,
    0xc2,0xa3,0xab,0x1b,0x5a,0xf6,0x51,0x7d,0x8f,0x9f,0x63,0x68,0xd9,0x43,0xa7,0x7b,
    0xf2,0x0d,0x3d,0xf9,0xc6,0x9e,0x7c,0x53,0x8f,0x5f,0x00,0xdd,0xd5,0x45,0x29,0x73,
    0xfe,0x8b,0x3c,0x8c,0x8a,0xea,0x3c,0x9e,0xf7,0xdf,0xe0,0x22,0x23,0xfb,0xe5,0x24,
    0x7b,0xaa,0xd4,0xc8,0x48,0xb2,0x04,0x5f,0xe5,0x64,0x64,0xad,0xc2,0x30,0xd6,0x13,
    0xfc,0x37,0xe9,0x4b,0x9c,0x75,0x27,0x9c,0xbc,0xf0,0x92,0xdc,0x23,0x98,0xe4,0x47,
    0xc6,0x7f,0x39,0x41,0x19,0x0b,0xd6,0xc9,0xc9,0x4b,0x9e,0x24,0x06,0x19,0x27,0x18,
    0x1f,0x77,0xfc,0x54,0x74,0xe4,0xff,0x98,0xb3,0x55,0xd9,0xfd,0xa7,0x63,0x5b,0xf8,
    0x55,0xe0,0xcb,0xbf,0xc6,0x56,0x35,0x8c,0xf3,0xbc,0x9a,0xd8,0xaa,0x85,0x31,0x56,
    0x46,0x3c,0x42,0xa7,0xb9,0xa7,0x32,0xba,0x32,0xd6,0x7c,0xd4,0x08,0xff,0x9b,0x8f,
    0x9a,0x61,0x8c,0x4f,0x74,0x32,0x42,0x67,0x84,0x31,0x56,0x66,0x64,0x6a,0xe1,0xf3,
    0x1e,0x64,0x6a,0x87,0xb1,0x5c,0x2d,0xe6,0x27,0xeb,0x5c,0xdb,0xc4,0x58,0x27,0x8c,
    0xd7,0x5e,0x73,0x5c,0x37,0x8c,0x73,0xbc,0xc2,0xd8,0xcc,0x0c,0x63,0x5c,0x73,0x9c,
    0x15,0xc6,0x7a,0x99,0xe4,0x38,0xdb,0xe4,0x58,0x78,0xf5,0xdc,0x93,0xcd,0x9c,0x64,
    0x2c,0xf9,0xd1,0x39,0x66,0x1b,0xdf,0x0d,0xf0,0x2d,0x71,0x49,0x7d,0x09,0x7d,0xb6,
    0xf3,0x21,0x7b,0x33,0x37,0x8c,0xcf,0xf3,0x1c,0xf8,0x52,0x8f,0xb9,0xe8,0x0a,0x3f,
    0x2f,0x8c,0x6b,0x54,0x78,0x52,0x7b,0x79,0xe8,0x4a,0xcf,0x6f,0xe4,0xc6,0xa7,0x51,
    0x93,0xc2,0x97,0x5a,0x6d,0x64,0xfc,0x36,0x31,0x7e,0xa5,0x4e,0x9b,0xc0,0x13,0xdd,
    0x66,0x61,0x5c,0xdb,0xc2,0x93,0x9a,0x6d,0x16,0xd9,0x4d,0x44,0x7a,0xcd,0xc3,0xb8,
    0x9f,0x88,0x4e,0x53,0x63,0xaf,0x45,0x18,0xef,0xaf,0xad,0xe4,0xbc,0x65,0x18,0x63,
    0xcd,0x4d,0x4d,0xb5,0x24,0x0f,0xe9,0xe4,0x21,0xdd,0xe8,0xb7,0xf2,0xd6,0x2c,0x3f,
    0x8c,0xb1,0x15,0xa6,0x0e,0xf3,0xc3,0x53,0xeb,0xb0,0xb2,0xd1,0x2f,0xc4,0xbf,0xc8,
    0xca,0xbe,0x2a,0x24,0x17,0xd2,0x13,0x8a,0xc2,0xf8,0x1e,0x53,0x40,0xad,0x9f,0xe5,
    0x9e,0x76,0xf8,0xa9,0x42,0xbf,0x90,0x33,0xa3,0xbd,0xd3,0x4d,0xe5,0x4c,0xd2,0x71,
    0x3a,0x7d,0xa4,0xaa,0xa9,0x85,0x66,0xc8,0x68,0xbd,0x14,0xb0,0x27,0x5b,0x19,0x99,
    0x42,0x70,0xad,0xd3,0x22,0xf4,0x0a,0x8d,0x4c,0x6b,0xec,0xab,0x9d,0x33,0xb0,0x53,
    0x6c,0x64,0xce,0x04,0x57,0x3b,0x6d,0xd0,0x13,0x5c,0x73,0xd5,0x16,0xfb,0x6d,0x8c,
    0xad,0x76,0xd8,0x2a,0x31,0xb6,0xda,0x83,0xab,0xde,0x59,0xe8,0xb6,0x8f,0xfa,0x4c,
    0x52,0x44,0xdb,0xdc,0xd4,0xa8,0x20,0x37,0xd5,0xcc,0xb8,0x3a,0xb9,0xa9,0x69,0x7a,
    0x5a,0x07,0xce,0x0c,0xf5,0x79,0x0e,0x3a,0x53,0xb1,0xd9,0x09,0xac,0xa3,0x99,0x53,
    0x17,0xf0,0xce,0xac,0x75,0x07,0x30,0xb5,0xd1,0x15,0xbb,0x12,0x63,0x57,0x13,0x63,
    0x06,0xf7,0x5d,0xf9,0xd5,0x32,0x71,0xd5,0x26,0xae,0xba,0x26,0xae,0x6e,0xc1,0xa9,
    0xbd,0xf7,0x7c,0x8f,0x1e,0xe4,0xd1,0x83,0x3d,0x7a,0x88,0x47,0x0f,0xf5,0xe8,0xb1,
    0x1e,0x3d,0xce,0xa3,0xa7,0x78,0xf4,0x74,0x8f,0x9e,0xe7,0xd1,0xf3,0x83,0x53,0xcf,
    0x96,0x25,0x1e,0x7f,0x9d,0xa1,0xe5,0x9c,0xde,0xe6,0xf1,0xb7,0x7b,0xfa,0x3b,0x3c,
    0xfa,0x4b,0x6f,0x9d,0xce,0x25,0x6f,0x5a,0x3f,0x3d,0xa8,0x9f,0xee,0x46,0xa6,0x27,
    0xf8,0x64,0xd6,0xed,0x3c,0xf4,0x7a,0xb2,0x6e,0xdd,0xc0,0x54,0xfe,0x02,0xcf,0x66,
    0xaf,0x0a,0x6c,0xf6,0x06,0xd7,0xfa,0xb8,0x10,0xbd,0xde,0xd8,0x3c,0x1f,0x4c,0xe5,
    0x2f,0x62,0xed,0xd4,0xe6,0xc5,0xd8,0xec,0x63,0x64,0xfa,0x82,0x6b,0xaf,0xbe,0x04,
    0xbd,0xbe,0x46,0xe6,0x52,0xec,0xe8,0xb9,0x74,0x19,0x98,0xdc,0x0b,0x97,0x82,0x5d,
    0x8e,0xae,0xf0,0xa4,0xc7,0x0f,0x0c,0xca,0x7b,0xbc,0xf0,0x06,0xb8,0x67,0x20,0xb5,
    0x36,0x80,0xfa,0x2c,0x85,0x1e,0x68,0x7c,0x5d,0x41,0xfd,0xc9,0x7c,0x06,0x43,0x2b,
    0xef,0x4a,0xe2,0x10,0xde,0x10,0x68,0xed,0xb5,0x57,0xd1,0x9f,0x06,0x53,0x7f,0x22,
    0x33,0x08,0x5c,0xf5,0xaf,0xa5,0x76,0x75,0x4d,0x46,0x80,0x75,0x8c,0x72,0x94,0x88,
    0xee,0xa4,0xd7,0x73,0x4f,0x2d,0x85,0xaf,0xba,0x37,0xc0,0x13,0xbb,0x43,0xa1,0x35,
    0xaf,0x37,0x92,0xd7,0x91,0x46,0xfe,0x26,0xf0,0x15,0xe4,0xe7,0x66,0xb0,0x51,0xe4,
    0x67,0x8c,0xc9,0x8f,0xf0,0x46,0xbb,0x67,0x2e,0xf9,0x18,0x6d,0xec,0xdc,0xc2,0x9c,
    0x97,0x63,0xe7,0x56,0xb0,0xfe,0xd1,0xfd,0x34,0x11,0xed,0xeb,0xdb,0xc1,0x4b,0xb8,
    0x23,0x8f,0x47,0xf7,0x0e,0x78,0x12,0xf3,0x58,0x68,0xb5,0x7b,0xa7,0x67,0x77,0x3c,
    0x98,0xb5,0x7b,0x37,0xf8,0x04,0xee,0xd6,0x6a,0xf7,0x1e,0x78,0x62,0x77,0x1c,0xb4,
    0xe6,0xe2,0x3e,0x72,0x71,0xaf,0xf1,0x75,0x3f,0xb8,0xe6,0x62,0x22,0x98,0xe6,0x62,
    0xb2,0xc9,0x85,0xf0,0x26,0xb9,0x67,0x1a,0xb9,0x98,0x64,0xec,0x4c,0x25,0x66,0xed,
    0x85,0x0f,0x72,0xa7,0x9f,0x4a,0x2c,0x53,0xc0,0xe4,0xdc,0x9b,0x8c,0xfe,0x34,0xa3,
    0xff,0x90,0x37,0xe7,0x87,0xc1,0xfa,0x13,0xc7,0x4c,0x13,0x87,0xf0,0x66,0xb8,0x67,
    0x16,0x76,0x66,0xe0,0x63,0x7a,0x50,0x7e,0xc7,0x9b,0x09,0x6f,0x96,0xf1,0xf1,0x08,
    0xfd,0x4d,0xe9,0xc7,0xf0,0x79,0x1f,0x31,0x3f,0xce,0x7b,0xc7,0x63,0x66,0x1e,0x4f,
    0xa0,0xf7,0xb8,0x39,0x6f,0x66,0x83,0x3f,0x6a,0xfc,0xce,0xf6,0xfc,0xce,0x34,0x7e,
    0xe6,0xd0,0x27,0x35,0x0f,0x73,0xbc,0x3c,0x4c,0x86,0x1e,0x03,0x3d,0xd7,0xe8,0x3e,
    0xc9,0xbe,0x10,0xdd,0x79,0xd0,0xba,0x9e,0x4f,0x55,0x70,0xce,0x3e,0x0d,0x2e,0xf2,
    0xf3,0xa1,0x75,0x1f,0x2e,0xe0,0x2c,0x9c,0x47,0x5f,0xd6,0x78,0x16,0x18,0x9b,0xcf,
    0x54,0x60,0xf3,0x59,0x70,0xcd,0xc9,0x42,0xb0,0xce,0xa6,0x7e,0x17,0x1a,0xf9,0xe7,
    0xc8,0xb3,0xae,0xe5,0x62,0xb0,0x45,0xac,0xe5,0x32,0xb3,0x96,0x8b,0xa3,0x3e,0x25,
    0xb2,0xf1,0xdc,0x97,0x62,0x73,0x09,0xef,0x78,0x92,0x97,0x65,0xf0,0x96,0x1b,0x1f,
    0x2b,0xf1,0xb1,0x85,0xf3,0xf3,0x05,0xee,0xb9,0x2b,0x59,0xcf,0x8c,0xa8,0x6f,0x96,
    0xe3,0x6a,0x73,0x95,0x67,0x73,0x59,0x50,0x7e,0x0f,0x7d,0x91,0xf3,0x49,0xf7,0xd2,
    0x6a,0x30,0xdd,0x4b,0xab,0xbd,0x75,0x1a,0x63,0xe2,0x79,0xc9,0xeb,0xe7,0x2f,0x57,
    0xd0,0xcf,0x5f,0x01,0xd7,0x7e,0xfe,0x2a,0x7a,0xaf,0x18,0x99,0xd7,0xbc,0x7d,0xf0,
    0x3a,0x98,0xed,0xe7,0x6f,0xa0,0xfb,0x3a,0xf9,0x5c,0x6b,0xf2,0x29,0xbc,0x35,0xee,
    0x59,0x4f,0x8c,0x6b,0x88,0x7f,0x1d,0xef,0x97,0x12,0xff,0x5a,0x78,0xeb,0x8d,0xdf,
    0x37,0xb9,0x0b,0x28,0xbd,0x81,0xb3,0x7e,0x13,0x6b,0xfe,0x16,0x32,0x1b,0x8c,0xcc,
    0xdb,0xdc,0x0f,0xb6,0x21,0xb3,0x11,0xb9,0xb7,0x8d,0xcf,0x8d,0x9e,0xcf,0xb5,0x46,
    0x7f,0x13,0x6b,0xa8,0x67,0xd7,0x66,0x30,0xad,0x93,0xad,0x66,0x5e,0x9b,0xa3,0xb5,
    0x0e,0x22,0x4c,0xec,0x6c,0x31,0x76,0xde,0xe5,0x1e,0xa1,0xf4,0x7b,0xd8,0xd5,0x7d,
    0xfd,0x3e,0x58,0x99,0xa9,0x97,0x0f,0xa8,0x8b,0xf7,0xcd,0x7a,0x7f,0x08,0xae,0xf3,
    0xf9,0x08,0xdb,0x1f,0x9a,0xfe,0xf8,0x31,0xb8,0xbe,0x57,0x6e,0x03,0x13,0xdf,0xc2,
    0xff,0x84,0x3b,0x8c,0xc4,0xbf,0xcb,0xc4,0x2f,0xf8,0x4e,0xf7,0xec,0x21,0xfe,0x9d,
    0x26,0xde,0xdd,0x5e,0x2d,0x7f,0x4a,0xed,0xef,0xc6,0xc7,0x0e,0x30,0xc9,0xe3,0x2e,
    0xf4,0xf7,0x18,0x5e,0xa9,0xc7,0xdb,0x65,0x6a,0xfa,0x33,0xee,0x4c,0x3a,0xc7,0xcf,
    0xc1,0x44,0x77,0x3b,0xb4,0xc6,0xb1,0x97,0xfb,0x96,0xd2,0x5f,0x90,0x57,0x7d,0x17,
    0xda,0x07,0xb6,0xd7,0xac,0xef,0x3e,0x7c,0xeb,0xba,0x6c,0x35,0xfa,0x5f,0xa1,0x3f,
    0x9e,0x58,0xbe,0x06,0x13,0xdd,0x2f,0xa1,0x35,0xce,0x6f,0xb8,0xcb,0xc9,0xdd,0xe3,
    0x1b,0x73,0x37,0x96,0xf7,0xb8,0xd3,0xc8,0x63,0x3d,0xee,0xc6,0x99,0x7c,0xb3,0x14,
    0x7f,0xf5,0x8d,0x8d,0x6f,0xc1,0x6f,0xe2,0xfd,0xef,0x3b,0x30,0xb1,0xf9,0x9d,0xf7,
    0x4e,0xd0,0xf0,0xdf,0xef,0x64,0xe5,0xf7,0xed,0x5c,0xc6,0xd1,0x37,0x11,0xec,0xe7,
    0x99,0xbb,0xe8,0x7e,0x73,0xd7,0x14,0xfb,0xdf,0x23,0xa7,0xf3,0xfb,0x01,0x4c,0x73,
    0xfd,0x23,0x98,0xcc,0x77,0x3f,0xb4,0xe6,0xe6,0x27,0xec,0x49,0x6c,0x3f,0x99,0xd8,
    0x92,0xf8,0x56,0x1d,0xf0,0x2d,0x57,0x63,0x6b,0x4c,0x3c,0x4d,0xcd,0x77,0x96,0x5f,
    0x2b,0xf8,0xce,0x72,0x0c,0x5c,0xfb,0xd0,0x6f,0xf4,0xa1,0x09,0x46,0xe6,0x77,0x70,
    0xbd,0x6b,0x1d,0x07,0xeb,0x68,0xce,0xb8,0x13,0xd8,0x3a,0x6e,0xf4,0xfe,0x20,0x0e,
    0xbd,0x8f,0xfd,0xc9,0xf7,0xb1,0x52,0xe4,0x65,0x9e,0x7f,0x22,0xa7,0xef,0xa7,0xff,
    0x00,0x11,0x39,0xfd,0x92,0xac,0x18,0x00,0x00
};

// Generated from:
//
// #version 450 core
//
// layout(local_size_x = 64, local_size_y = 1, local_size_z = 1)in;
//
// layout(set = 0, binding = 0)buffer dest
// {
//     uint destData[];
// };
//
// layout(set = 0, binding = 1)buffer src
// {
//     uint srcData[];
// };
//
// layout(push_constant)uniform PushConstants
// {
//
//     uint outputCount;
//
//     uint componentCount;
//
//     uint srcOffset;
//     uint destOffset;
//
//     uint Ns;
//     uint Bs;
//     uint Ss;
//     uint Es;
//
//     uint Nd;
//     uint Bd;
//     uint Sd;
//     uint Ed;
//
//     bool isSrcHDR;
//     bool isSrcA2BGR10;
// } params;
//
// uint getSourceComponentOffset(uint vertex, uint component)
// {
//     return vertex * params . Ss + component * params . Bs + params . srcOffset;
// }
//
// uint getDestinationComponentOffset(uint vertex, uint component)
// {
//     return vertex * params . Sd + component * 4 + params . destOffset;
// }
//
// uint getShiftBits(uint offset, uint B)
// {
//
//     uint shift =(offset % 4)* 8;
//
//     return shift;
// }
//
//       int loadSourceComponent(uint cd)
// {
//
//     uint vertex = cd / params . Nd;
//     uint component = cd % params . Nd;
//
//     if(component >= params . Ns && component < 3)
//     {
//         return 0;
//     }
//
//     uint offset = getSourceComponentOffset(vertex, component);
//     uint block = srcData[offset / 4];
//
//     uint shiftBits;
//     uint valueBits;
//     uint valueMask;
//
//     if(params . isSrcHDR)
//     {
//         valueBits = component == 3 ? 2 : 10;
//         valueMask = component == 3 ? 0x03 : 0x3FF;
//         if(params . isSrcA2BGR10)
//         {
//             shiftBits = 10 * component;
//         }
//         else
//         {
//
//             shiftBits = component == 3 ? 0 :(valueBits *(2 - component)+ 2);
//         }
//     }
//     else
//     {
//         shiftBits = getShiftBits(offset, params . Bs);
//         valueBits = params . Bs * 8;
//         valueMask = valueBits == 32 ? - 1 :(1 << valueBits)- 1;
//     }
//
//     uint valueAsUint;
//
//     if(component >= params . Ns && component == 3)
//     {
//
//         valueAsUint = 1;
//
//     }
//     else
//     {
//         valueAsUint =(block >> shiftBits)& valueMask;
//     }
//
//     if(valueBits < 32)
//     {
//         bool isNegative =(valueAsUint &(1 <<(valueBits - 1)))!= 0;
//
//         uint signExtension = isNegative ? 0xFFFFFFFF << valueBits : 0;
//         valueAsUint |= signExtension;
//     }
//           int value = int(valueAsUint);
//
//     return value;
// }
//
//        float convertComponent(int srcValue)
// {
//
//     return srcValue;
// }
//
// uint makeDestinationComponent(uint cd, float value)
// {
//
//     uint valueAsUint = floatBitsToInt(value);
//
//     return valueAsUint;
// }
//
// void storeDestinationComponents(uint valueAsUint)
// {
//
//     destData[gl_GlobalInvocationID . x + params . destOffset / 4]= valueAsUint;
// }
//
// void main()
// {
//     if(gl_GlobalInvocationID . x >= params . outputCount)
//         return;
//
//     uint valueOut = 0;
//     for(uint i = 0;i < 1;++ i)
//     {
//         uint cd = gl_GlobalInvocationID . x * 1 + i;
//         if(cd >= params . componentCount)
//         {
//             break;
//         }
//
//               int srcValue = loadSourceComponent(cd);
//                float destValue = convertComponent(srcValue);
//         valueOut |= makeDestinationComponent(cd, destValue);
//     }
//
//     storeDestinationComponents(valueOut);
// }