// GENERATED FILE - DO NOT EDIT.
// Generated by gen_vk_internal_shaders.py.
//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// shaders/gen/OverlayDraw.comp.00000001.inc:
//   Pre-generated shader for the ANGLE Vulkan back-end.

#pragma once
constexpr uint8_t kOverlayDraw_comp_00000001[] = {
    0x1f,0x8b,0x08,0x00,0x00,0x00,0x00,0x00,0x02,0xff,0x75,0x58,0x6b,0x8c,0x56,0xd5,
    0x15,0xbd,0xfb,0x7c,0xc3,0xcc,0xd0,0xfa,0x00,0x2b,0x5a,0x95,0x8e,0x32,0x48,0x6d,
    0x79,0x05,0x2d,0x12,0xcc,0x04,0x66,0x86,0xc7,0x30,0x80,0x2f,0x4a,0x8d,0xa6,0xfe,
    0x00,0x5a,0x1e,0xb5,0x44,0x12,0xd3,0xc6,0x64,0x66,0x3e,0x09,0x5a,0xb5,0xa1,0xd1,
    0xfe,0xb0,0xf2,0xa3,0x55,0x46,0x14,0x41,0x04,0x42,0xc6,0x20,0xce,0x38,0xfe,0x68,
    0x46,0x61,0xb0,0x8d,0xa0,0x22,0x49,0x85,0x46,0x21,0x5a,0x28,0x53,0x45,0x1e,0x89,
    0x0a,0xc2,0x64,0xba,0xd7,0xdd,0xeb,0x70,0xf7,0x77,0xfd,0x9c,0xe4,0xe4,0xde,0xb3,
    0xf6,0x3e,0x6b,0xaf,0xb3,0xcf,0xbe,0xe7,0x9c,0xf9,0x0a,0x61,0x64,0x55,0x92,0x48,
    0xf2,0xbd,0xa4,0x3a,0xb9,0x2f,0x24,0xe9,0xdf,0xd0,0x24,0x28,0x92,0x24,0xdf,0x4f,
    0x2a,0xd3,0xe7,0xac,0x5b,0xe7,0xdf,0x3a,0xfe,0x77,0xbf,0x5f,0x3c,0x7e,0xe2,0xcd,
    0x13,0x60,0xbf,0x24,0x29,0xa4,0x7e,0xb0,0x5d,0x9a,0x54,0x25,0x83,0xf4,0x59,0xa1,
    0xed,0xfe,0x45,0xf7,0xad,0x00,0xfe,0x9c,0xb6,0x4e,0x6d,0x43,0x74,0x7c,0x45,0xca,
    0x97,0x28,0xbb,0xb5,0x94,0x4f,0xd1,0x7a,0x7d,0x56,0xa6,0x3e,0x49,0xd2,0xac,0x0c,
    0x0d,0x16,0x3a,0x19,0xc9,0x67,0xc4,0x84,0x98,0xf7,0x0b,0xc4,0xae,0x73,0x58,0x81,
    0xd8,0x04,0xf2,0x4f,0x23,0xff,0x04,0x31,0x9f,0xe9,0x39,0xfe,0x59,0x3a,0x62,0x3a,
    0xb9,0xe0,0x3f,0x53,0x9f,0xb5,0x17,0x6c,0xd6,0x1f,0xe1,0xf4,0x2e,0xcd,0xd9,0x97,
    0xd2,0x5e,0xc1,0x7e,0x4b,0x6e,0x3e,0xad,0x65,0xe6,0xd3,0x5a,0x66,0x3e,0xad,0x65,
    0xe6,0xd3,0x5a,0x66,0x3e,0x6d,0xb9,0xf9,0x14,0xcb,0xcc,0xa7,0xe8,0xe6,0xb3,0x32,
    0xa7,0x77,0x25,0xf5,0x46,0xfb,0x73,0xe9,0xfa,0x26,0xc9,0x70,0xc6,0x5c,0x5f,0x86,
    0x6f,0xbd,0xf3,0xdf,0x91,0xe3,0xdb,0x41,0xbe,0x02,0xfb,0x9d,0xe4,0xbb,0x9a,0xfd,
    0x17,0xa4,0xd4,0x1f,0xfd,0x11,0xae,0xff,0xba,0x98,0xff,0x55,0xda,0x7e,0xa0,0x51,
    0x42,0xca,0x57,0x48,0xf9,0xf0,0x3e,0x4c,0x7d,0x2a,0x99,0x13,0xfc,0x5d,0xa9,0xfd,
    0x2a,0xe6,0x20,0xb0,0x5f,0xcd,0x3e,0xd6,0xe0,0x72,0x45,0x07,0xeb,0xf3,0x0a,0x65,
    0x18,0xc6,0x71,0xf0,0xa9,0x4d,0xb9,0xcc,0x07,0xfd,0x9f,0xea,0x73,0x30,0x39,0xc6,
    0x30,0xc6,0x24,0xc6,0x88,0xfd,0x3a,0xfa,0xc7,0xfe,0x54,0xae,0xd7,0x70,0xd6,0x6d,
    0x35,0xb1,0x1a,0xb5,0x36,0xb0,0x5f,0xcb,0x67,0xbd,0x1b,0xd7,0x48,0x1d,0xc3,0x59,
    0x8f,0x0d,0xc4,0x6a,0x58,0x7b,0xd3,0x52,0x7b,0x45,0x32,0x83,0x7a,0xa6,0xa7,0xb1,
    0xad,0x3f,0xd3,0xe5,0xa1,0x89,0x3c,0x42,0xee,0xa6,0x34,0x87,0x99,0xe6,0xa6,0x74,
    0x0d,0x6d,0x2d,0xc0,0x77,0x1b,0xc7,0x56,0x3a,0x2d,0xf3,0xa9,0x2f,0xf6,0xef,0xd1,
    0x36,0x90,0xe6,0x7f,0x70,0xb2,0x98,0x39,0x12,0x72,0xe6,0x9f,0xe0,0x5c,0xc2,0xf7,
    0xc5,0xd4,0x88,0xfe,0x52,0xb7,0x36,0xcb,0xf5,0xd9,0xe4,0xd6,0x66,0x05,0xfb,0x05,
    0xce,0xbf,0x25,0x97,0xb7,0xd6,0x5c,0xde,0x5a,0xe8,0x87,0x3a,0x6f,0x75,0x79,0x42,
    0x4d,0xb7,0x51,0xc3,0x43,0xe4,0x2f,0x52,0x03,0xfa,0x2b,0x5d,0xcc,0x3f,0x72,0x1e,
    0x05,0xce,0x13,0xef,0xab,0x53,0x85,0xab,0xea,0x61,0x5f,0xcb,0x9c,0xc4,0x3c,0xb5,
    0x73,0x8e,0x6b,0xc9,0xd7,0xce,0xbd,0x4b,0x18,0x1b,0xf5,0x5f,0x45,0xdf,0x17,0x59,
    0x37,0xeb,0xe9,0x8b,0xfe,0x06,0x62,0xb0,0x6f,0xe4,0x7b,0x95,0x8b,0xdd,0xc1,0xfc,
    0x8c,0x55,0x14,0xf3,0x7c,0x85,0x58,0x6c,0xab,0x99,0xff,0xed,0xd4,0x15,0xf3,0x9d,
    0x94,0xc9,0xff,0xab,0x7c,0xdf,0xce,0xf8,0xe8,0xef,0x20,0x16,0xb5,0x77,0xba,0x1a,
    0x01,0x5f,0x4f,0xae,0x66,0xde,0x65,0x1f,0x7c,0x1f,0x32,0x6f,0xd5,0x4e,0x5f,0x95,
    0x94,0xea,0xeb,0x70,0x63,0x87,0x88,0xf9,0x63,0xec,0x34,0xbe,0xd7,0xba,0x58,0x2d,
    0x8a,0x2d,0x74,0x73,0x7f,0x4c,0xfb,0x7b,0xde,0x79,0x67,0x6a,0xe4,0x7e,0x3c,0xc7,
    0x0d,0x3b,0xe6,0xbe,0x4e,0x4a,0x6b,0x2f,0xfe,0x05,0xa7,0xf5,0x79,0x1a,0xe1,0x5b,
    0xc7,0xfe,0x0b,0x12,0x73,0x5b,0x99,0xae,0x1f,0xf6,0x93,0xf9,0xac,0xf3,0x9e,0xf4,
    0x9b,0x1e,0x94,0x72,0x54,0x90,0x0f,0x6b,0x7e,0x46,0x11,0x9c,0x55,0x5f,0x6b,0xaf,
    0x9b,0xe3,0xcf,0xe9,0x3b,0xbe,0xff,0x37,0xc4,0xec,0x78,0x4e,0x61,0xad,0xac,0x63,
    0x3d,0xdc,0xa1,0x73,0xc0,0xba,0x3e,0x4f,0x6c,0x9d,0x5b,0x9f,0x46,0x65,0xc4,0xda,
    0xbf,0xc4,0x7a,0xc0,0x77,0x39,0x85,0x7b,0xd5,0x26,0xe2,0xdb,0xd4,0x07,0xfb,0xce,
    0xcb,0xe4,0x00,0xfe,0x37,0xf5,0x41,0xbd,0x6c,0x26,0x0e,0x4d,0x5b,0xc9,0xfb,0x8d,
    0xda,0x80,0x6f,0xd1,0xb6,0x95,0xba,0xf1,0x7e,0x56,0x9f,0xdd,0xd4,0xb9,0x95,0x71,
    0x50,0x0f,0xaf,0xb1,0x16,0xa2,0xee,0x2e,0xd6,0x42,0xd4,0xfd,0x3a,0xb1,0x2e,0xa7,
    0xbb,0xc8,0x6f,0xb6,0x9b,0xf6,0x05,0xea,0x89,0x5a,0x78,0x83,0x7c,0xdd,0x17,0xf6,
    0xfe,0x24,0x99,0xa7,0xfa,0xb1,0xc6,0x7f,0xa7,0x3d,0x71,0xd8,0x5b,0xc4,0x84,0xfa,
    0x76,0x52,0x2f,0x9e,0x5f,0x72,0xed,0x67,0x07,0xab,0x7d,0x68,0x5e,0xa2,0xef,0xbb,
    0x69,0xc3,0xf8,0x99,0xc1,0x38,0x60,0xdb,0x9f,0x98,0x6d,0x8b,0x72,0x23,0x37,0xff,
    0xa4,0x1d,0xeb,0xf3,0x95,0xea,0xed,0xa5,0x3d,0xe6,0x08,0xf6,0x5d,0xda,0x7a,0x19,
    0x13,0xef,0x17,0x29,0x2b,0xea,0x75,0x0f,0x35,0xcd,0x26,0x47,0x91,0x75,0xba,0x97,
    0xb6,0x9d,0x1a,0x03,0x7e,0xef,0xf3,0xbb,0xd8,0x9b,0x64,0x3e,0xfb,0x88,0xf7,0x72,
    0x8e,0xfb,0xc9,0xb1,0x2f,0x5d,0xef,0xaa,0xf4,0xdb,0x39,0xc0,0xbd,0x67,0x16,0xc7,
    0xc6,0x75,0x47,0x0e,0x0f,0xd2,0x1e,0xf3,0xdf,0x23,0x86,0x1d,0x74,0xf9,0x8f,0x35,
    0xf1,0xa6,0x58,0x4d,0xc0,0xe7,0x19,0xd6,0xc4,0x5b,0x62,0x38,0x6a,0xe2,0x6d,0xc9,
    0xe6,0x0b,0x7c,0xa7,0xb6,0xb7,0x59,0x03,0x78,0x8f,0x31,0x76,0xb9,0x18,0x81,0xf5,
    0xde,0xc1,0x18,0xbd,0x8c,0xb1,0xcb,0xc5,0xd8,0x2d,0x86,0x63,0xcd,0x22,0x1f,0x9e,
    0x58,0x17,0xd8,0xff,0x21,0xa6,0x63,0x17,0x7d,0x11,0x6b,0x13,0xc7,0x7e,0x4c,0x3b,
    0xf4,0x1d,0x76,0xeb,0x01,0xfc,0x90,0xb6,0xc3,0x5c,0x8f,0x43,0xac,0x89,0xdd,0xec,
    0x1f,0x76,0x75,0xf3,0xa9,0xfb,0x8e,0x22,0x76,0xc4,0xe5,0x68,0x33,0x6b,0xe0,0x28,
    0x7d,0x8f,0x24,0x59,0xfc,0xff,0x12,0x47,0xfc,0x3e,0x17,0x1f,0xf8,0x31,0x6d,0x7d,
    0x8c,0x77,0xcc,0x71,0x7f,0xc6,0x78,0xe2,0xb0,0xe3,0x8c,0x27,0x2e,0xde,0x17,0xf4,
    0x3d,0x4e,0xed,0x91,0xab,0x2f,0xc9,0x72,0x73,0x82,0xf1,0x0f,0xd3,0xff,0x98,0xd3,
    0x76,0x92,0x76,0x68,0x3b,0xed,0xb4,0x01,0x3f,0xa5,0xed,0x34,0xf9,0xf0,0xbe,0x8a,
    0x3a,0xbe,0xe4,0x1c,0x7b,0x9c,0xb6,0x33,0x6e,0x2d,0xa3,0xb6,0xb3,0xf4,0x3d,0x43,
    0x6d,0x91,0xeb,0xb4,0xd3,0xf6,0x0d,0xe3,0xf7,0xd1,0xff,0x94,0xd3,0x76,0x8e,0x76,
    0x68,0xeb,0x77,0xda,0x80,0x9f,0xd7,0xd6,0x4f,0xbe,0xf3,0x4e,0xc7,0x80,0xcb,0x5b,
    0xd4,0x8b,0xce,0x40,0x4e,0x6f,0x60,0xfd,0x15,0x9c,0xde,0x82,0x98,0x6f,0x60,0x9d,
    0x45,0xfe,0x7e,0xa7,0xb7,0x42,0x4c,0xd3,0x69,0xfa,0x9f,0xa7,0xbe,0x4a,0x57,0xf7,
    0xf0,0x19,0xa4,0xad,0x92,0x75,0x3a,0x48,0x4a,0xeb,0x0a,0xf8,0x23,0x1a,0x13,0xdf,
    0xc1,0xc5,0xee,0x7b,0x6a,0xd4,0xaf,0x11,0x77,0xa1,0xa1,0x52,0xfa,0xad,0xe2,0x2c,
    0x9b,0xc4,0xef,0x15,0xda,0x2f,0x13,0xf3,0x89,0x73,0xd9,0x23,0xc6,0x83,0xbf,0xc7,
    0x89,0xed,0x15,0xc3,0xe1,0x1b,0xb1,0xf7,0xc4,0xf0,0xba,0xf4,0x2c,0x37,0x6c,0x9f,
    0xc3,0x1a,0x75,0x86,0x88,0xff,0x41,0x2e,0x7e,0x33,0xc7,0xee,0x93,0x4c,0xc3,0x7e,
    0x31,0xbf,0xa8,0xe1,0x1a,0x97,0xcf,0x88,0xfd,0x48,0xb2,0x7a,0x7d,0x84,0x58,0x8d,
    0x98,0x2f,0x6c,0x5b,0x99,0xf7,0x91,0x62,0x7c,0x35,0xfc,0x46,0x47,0xb9,0x5c,0xc2,
    0x76,0xbd,0xb6,0x51,0xcc,0xe5,0xf5,0x2e,0xe6,0x0d,0x9c,0xb7,0x5f,0xeb,0x9f,0x88,
    0xe1,0x75,0xdc,0xb3,0xc0,0x3f,0x5a,0x0c,0xaf,0xe1,0x3a,0x44,0xae,0x51,0x6e,0xff,
    0x18,0x23,0xa6,0x03,0x6b,0x33,0x9a,0x31,0xa1,0x65,0x9c,0xd3,0x02,0x9f,0xb1,0xda,
    0xc6,0x71,0xfc,0x58,0xa7,0xe5,0x46,0xa7,0x25,0xee,0xc3,0x37,0x71,0x0d,0x60,0xdb,
    0x4d,0xec,0x67,0x62,0x78,0x8f,0xab,0xbb,0x89,0x62,0xf8,0x24,0x7e,0x27,0x91,0x7f,
    0x9c,0xd3,0x77,0xb3,0x98,0x46,0x68,0x9e,0x48,0x1d,0x31,0xf6,0x64,0x17,0x3b,0xe6,
    0xf9,0x16,0xce,0x77,0xb2,0xd8,0xbe,0x0a,0x8e,0x3a,0x31,0x7c,0xbf,0xdb,0x1b,0xa7,
    0x88,0x71,0xbf,0x44,0x9f,0xa9,0x62,0x7e,0x53,0x38,0xff,0x06,0x37,0x7f,0xd8,0xea,
    0xb5,0x35,0x50,0x5f,0xbd,0xd8,0xf9,0x82,0xfb,0xd5,0xf4,0x5c,0xcd,0xbc,0xcb,0x7a,
    0xc5,0x79,0x3a,0x83,0xf6,0x3b,0xb4,0xbe,0x71,0xe7,0xfd,0x97,0xd8,0x19,0x3b,0x3b,
    0x64,0xe7,0x4b,0x60,0xdd,0xe0,0x6e,0xf5,0xa1,0xd8,0x18,0xd4,0xd2,0x1f,0x88,0x1d,
    0x10,0xbb,0x7f,0xc2,0xf6,0x67,0xc5,0xc0,0x73,0x50,0x8c,0xeb,0x80,0xe3,0xfe,0x37,
    0xc7,0xce,0x90,0x52,0xee,0x38,0xe6,0x23,0x31,0x1f,0xf0,0x3c,0x4c,0xec,0x63,0x31,
    0xae,0x8f,0x24,0xd3,0x70,0x88,0x1a,0xa1,0xe1,0x31,0x62,0x9f,0x88,0xe1,0x07,0x9c,
    0xdf,0xa7,0x62,0xe3,0x13,0xa7,0xff,0x3f,0xc4,0xc4,0x61,0x47,0x88,0x41,0xcb,0x9d,
    0xbc,0x67,0x1c,0x15,0x1b,0x0f,0x7f,0xd8,0x3f,0x61,0x7d,0xc6,0xfc,0x36,0x48,0x76,
    0x27,0x59,0xca,0x7c,0xa1,0x26,0x8e,0x72,0x1d,0xfc,0x9e,0x62,0x77,0x94,0xc1,0xa9,
    0xef,0x12,0xfa,0x1e,0xe2,0x1d,0x19,0xfb,0x0f,0xc6,0x37,0x48,0xe9,0x9d,0xa7,0x97,
    0xf5,0xd6,0xcc,0x78,0xcd,0x2e,0x5e,0x33,0x39,0xe0,0xb3,0x4c,0x9f,0x73,0x25,0xbb,
    0x03,0x35,0x05,0xbb,0x5b,0xc1,0x76,0xb7,0x98,0x2d,0xde,0x81,0x6e,0x17,0xb3,0xc7,
    0x3b,0xd0,0x1c,0xda,0x63,0x0d,0xc1,0x3e,0x5b,0xdb,0x1c,0xc6,0xc4,0x7b,0xbc,0x03,
    0xcd,0x93,0xec,0x0e,0xd4,0xe4,0xee,0x40,0x3f,0x17,0xb3,0xc5,0x3b,0xd0,0x2f,0xc4,
    0xea,0x0b,0x78,0xf4,0xb9,0x4b,0x0c,0x8f,0xdf,0xde,0xdd,0xd4,0x71,0x97,0x64,0x77,
    0xa0,0x5f,0x8a,0xfd,0x9f,0x3a,0x8b,0x63,0xfd,0x1d,0xe8,0x5e,0x31,0x7b,0xbc,0x9f,
    0xf4,0x89,0x61,0xf7,0xca,0xb7,0xef,0x40,0xff,0xe3,0x9e,0xdd,0xe7,0xee,0x27,0x9f,
    0x89,0xe1,0xf8,0x66,0x4e,0xba,0xf9,0x02,0xff,0x5c,0xdb,0x49,0xce,0xf7,0x73,0x17,
    0xe3,0xb8,0x8b,0x91,0xbf,0x03,0x7d,0xc1,0x18,0xc7,0x5d,0x8c,0x13,0x62,0x38,0xd6,
    0x2c,0xf2,0x9d,0x74,0x7b,0xc4,0x29,0x31,0x1d,0xc8,0xe9,0x09,0xc6,0x8d,0xdf,0xf9,
    0x02,0x31,0x3b,0xf4,0x2d,0x72,0xfa,0x80,0x2f,0xd4,0xb6,0x88,0x7c,0x0b,0xc9,0x3f,
    0x97,0xfd,0x45,0xee,0xac,0x5a,0xe6,0xe6,0x1d,0x73,0xfa,0xdb,0x5c,0x4e,0x87,0x48,
    0x96,0xd3,0xe5,0x62,0xf6,0x38,0xdf,0x15,0x62,0xd8,0x72,0x97,0xd3,0xb8,0x87,0x3d,
    0x40,0x3c,0x38,0xec,0x41,0xe7,0x7b,0xe1,0x9e,0x21,0xa6,0xc3,0x9f,0x75,0x67,0xc5,
    0xf0,0x07,0xdd,0x59,0x77,0x4e,0x0c,0xaf,0x73,0x7e,0xfd,0x62,0xb8,0x3f,0xff,0x06,
    0x1c,0x16,0xcf,0x3f,0x88,0xf0,0x73,0x6a,0xe6,0xd8,0x01,0x77,0xfe,0x49,0x30,0xbf,
    0xc8,0x53,0x08,0x59,0xbc,0x47,0x89,0x55,0x04,0xc3,0xf1,0x3f,0xde,0x9b,0xc4,0xaa,
    0x82,0x8d,0xad,0x08,0xd9,0x99,0x50,0x1d,0x0c,0xbf,0x27,0xc9,0xf6,0xea,0x56,0x31,
    0xbc,0x85,0x6b,0x56,0x74,0x6b,0x06,0x5b,0x1b,0x6a,0x9f,0x6b,0xd4,0x26,0xa6,0x23,
    0xbd,0x4f,0x04,0xcb,0xcf,0x0a,0xc9,0xb4,0x5d,0x12,0x8c,0xab,0xd1,0xe5,0xe2,0x52,
    0x87,0xdd,0xc9,0xb1,0x43,0x82,0xf9,0xc2,0xf6,0x28,0xb1,0xa1,0xc1,0xb8,0x60,0xc3,
    0xdc,0xf1,0x7b,0xca,0x65,0xc1,0x7e,0x4b,0x59,0x45,0x9f,0x61,0xc1,0xfc,0x2e,0x0e,
    0xd9,0xff,0x69,0x57,0x04,0xc3,0x8b,0xfc,0x7f,0xfc,0xca,0x60,0x6b,0x3c,0x8f,0xdf,
    0xf0,0x0f,0x83,0xf9,0xc4,0xb5,0x05,0x76,0x15,0x31,0x49,0x35,0x55,0xa6,0xbf,0xc9,
    0x5c,0x1d,0xcc,0x17,0x36,0x70,0x2c,0xe0,0xfe,0x74,0x4d,0x30,0x1d,0xb0,0xfb,0xff,
    0xfb,0xb0,0xd7,0x0e,0x0f,0x66,0x4f,0x92,0xec,0x7c,0x5a,0x9d,0xab,0x53,0x7f,0x3e,
    0xfd,0x89,0xf6,0xb8,0x2f,0x3f,0x21,0xc6,0xe1,0xdb,0x45,0x5a,0xd1,0xb0,0x3d,0xc9,
    0x3d,0x6a,0x3c,0x7f,0x23,0xc0,0xd8,0x27,0xdc,0xf9,0x73,0x6d,0xb0,0xbd,0xb3,0xf9,
    0x3b,0xce,0xb6,0xeb,0x82,0x71,0xf8,0xb3,0x6d,0x44,0xb0,0xb3,0x0d,0xb6,0x78,0x4e,
    0xd5,0x06,0xe3,0x82,0x2d,0x72,0x8f,0xe4,0xd8,0x27,0xbf,0xe3,0x6c,0x1b,0x15,0xcc,
    0x07,0x3c,0xf1,0x6c,0xfb,0x71,0x30,0x2e,0xd8,0xa2,0x86,0x1b,0xa8,0xcf,0x9f,0x6d,
    0xa3,0x83,0xe1,0x23,0x9c,0xdf,0x98,0x60,0xe3,0xfd,0xd9,0x36,0x96,0x98,0x3f,0xdb,
    0xc6,0x11,0xf3,0x67,0xdb,0xf8,0x60,0xe3,0xe1,0x0f,0x3b,0xf8,0xb1,0xaf,0xc4,0x9a,
    0x2d,0xba,0xb3,0xe6,0x37,0xd4,0x83,0xbd,0x06,0xe3,0xda,0x72,0x7b,0xd0,0x5c,0xe7,
    0xbb,0x8c,0xbe,0xd8,0xa7,0x30,0xae,0x28,0xa5,0x67,0xd8,0x1c,0x77,0x36,0x3f,0x25,
    0xd9,0x3c,0xbb,0xf8,0x5d,0xfd,0x45,0x0c,0x5f,0xcd,0x7b,0xfb,0x1a,0xf7,0x5d,0xc1,
    0xf6,0xb4,0xb6,0x35,0xe4,0x7a,0xda,0xad,0xeb,0x5f,0xa5,0xfc,0xba,0x76,0x93,0xf7,
    0x59,0xf2,0x76,0x90,0xb7,0xdd,0xf1,0xc2,0xb6,0x56,0x5b,0x3b,0x79,0xd7,0x72,0x1f,
    0xc1,0xef,0x43,0xeb,0xf9,0xdb,0x50,0xfc,0x6e,0x36,0x70,0x8f,0xfd,0x95,0xf2,0x62,
    0xbe,0x1b,0xe9,0xb3,0xc1,0x69,0xd9,0x24,0x86,0x6f,0x94,0xf2,0x35,0xb6,0x99,0xb6,
    0x82,0xab,0x8d,0x2d,0x62,0xe3,0x36,0xbb,0xfb,0xd3,0x36,0x31,0xfc,0x29,0x77,0x17,
    0xea,0x10,0x9b,0xeb,0x36,0xe6,0x35,0x6a,0x6e,0xe7,0x1a,0xc0,0x67,0x4e,0x30,0x1f,
    0xe4,0xa7,0x83,0x73,0x8b,0xf3,0x79,0x25,0x37,0x9f,0xed,0x9c,0x4f,0xd4,0xb6,0x43,
    0x6c,0xbc,0xaf,0xa9,0xd7,0x88,0xf9,0x9a,0xea,0x24,0xe6,0x6b,0xaa,0x4b,0x6c,0x3c,
    0xfc,0x3b,0xb9,0x86,0xbf,0xd6,0x38,0x88,0x89,0x38,0x5d,0xd4,0x1c,0xd7,0x6f,0x8d,
    0x94,0xfe,0x06,0x85,0x67,0xbf,0x46,0x99,0xac,0xed,0xff,0x3d,0x04,0x96,0x98,0x48,
    0x1a,0x00,0x00
};

// Generated from:
//
// #version 450 core
//
// #extension GL_EXT_samplerless_texture_functions : require
//
// layout(local_size_x = 8, local_size_y = 8, local_size_z = 1)in;
//
// struct TextWidgetData
// {
//     uvec4 coordinates;
//     vec4 color;
//     uvec4 fontSize;
//     uvec4 text[256 / 16];
// };
//
// struct GraphWidgetData
// {
//     uvec4 coordinates;
//     vec4 color;
//     uvec4 valueWidth;
//     uvec4 values[64 / 4];
// };
//
// layout(set = 0, binding = 0, rgba32f)uniform image2D blendOutput;
//
// layout(set = 0, binding = 1)uniform TextWidgets
// {
//     TextWidgetData textWidgetsData[32];
// };
//
// layout(set = 0, binding = 2)uniform GraphWidgets
// {
//     GraphWidgetData graphWidgetsData[32];
// };
//
// layout(set = 0, binding = 3)uniform utexture2D culledWidgets;
// layout(set = 0, binding = 4)uniform texture2DArray font;
//
// layout(push_constant)uniform PushConstants
// {
//     uvec2 outputSize;
// } params;
//
// bool intersects(const uvec2 imageCoords, const uvec4 widgetCoords)
// {
//     return all(greaterThanEqual(imageCoords, widgetCoords . xy))&&
//            all(lessThan(imageCoords, widgetCoords . zw));
// }
//
// uint getChar(const uint textWidget, const uvec2 coordInWidget, const uint fontGlyphWidth)
// {
//     const uint charIndex = coordInWidget . x / fontGlyphWidth;
//     const uint packIndex = charIndex / 4;
//     const uint packedChars = textWidgetsData[textWidget]. text[packIndex / 4][packIndex % 4];
//     const uint shift =(charIndex % 4)* 8;
//
//     return(packedChars >> shift)& 0xFF;
//
// }
//
// float sampleFont(const uint textChar,
//                  const uvec2 coordInWidget,
//                  const uvec2 fontGlyphSize,
//                  const uint fontLayer)
// {
//     const uvec2 coordInGlyph = coordInWidget % fontGlyphSize;
//     const uvec2 glyphOffset = fontGlyphSize *
//         uvec2(textChar % 32, textChar / 32);
//
//     return texelFetch(font, ivec3(glyphOffset + coordInGlyph, fontLayer), 0). x;
// }
//
// uint getValue(const uint graphWidget, const uvec2 coordInWidget, const uint valueWidth)
// {
//     const uint valueIndex = coordInWidget . x / valueWidth . x;
//     return graphWidgetsData[graphWidget]. values[valueIndex / 4][valueIndex % 4];
// }
//
// vec4 blend(const vec4 blendedSoFar, const vec4 color)
// {
//
//     return vec4(blendedSoFar . rgb *(1 - color . a)+ color . rgb * color . a,
//                 blendedSoFar . a *(1 - color . a));
// }
//
// void main()
// {
//     const uvec2 imageCoords = gl_GlobalInvocationID . xy;
//     if(any(greaterThanEqual(imageCoords, params . outputSize)))
//     {
//         return;
//     }
//
//     vec4 blendedWidgets = vec4(0, 0, 0, 1);
//
//     const uvec2 subgroupWidgets = texelFetch(culledWidgets, ivec2(gl_WorkGroupID . xy), 0). xy;
//     uint textWidgets = subgroupWidgets . x;
//     uint graphWidgets = subgroupWidgets . y;
//
//     while(graphWidgets != 0)
//     {
//         const uint graphWidget = findLSB(graphWidgets);
//         graphWidgets ^= 1 << graphWidget;
//
//         const uvec4 widgetCoords = graphWidgetsData[graphWidget]. coordinates;
//         if(! intersects(imageCoords, widgetCoords))
//         {
//             continue;
//         }
//
//         if(imageCoords . x == widgetCoords . x || imageCoords . y == widgetCoords . y ||
//             imageCoords . x + 1 == widgetCoords . z || imageCoords . y + 1 == widgetCoords . w)
//         {
//
//             blendedWidgets = vec4(0);
//             continue;
//         }
//
//         const uvec2 coordInWidget = imageCoords - widgetCoords . xy;
//         const uint valueWidth = graphWidgetsData[graphWidget]. valueWidth . x;
//
//         const uint value = getValue(graphWidget, coordInWidget, valueWidth);
//
//         vec4 color = vec4(0);
//         const uint widgetHeight = widgetCoords . w - widgetCoords . y;
//
//         bool indicateOverflow = value > widgetHeight && coordInWidget . y + 4 >= widgetHeight
//                 &&((coordInWidget . x ^ coordInWidget . y)& 1)== 0;
//
//         if((widgetHeight - coordInWidget . y)< value && ! indicateOverflow)
//         {
//             color = graphWidgetsData[graphWidget]. color;
//             blendedWidgets = blend(blendedWidgets, color);
//         }
//     }
//
//     while(textWidgets != 0)
//     {
//         const uint textWidget = findLSB(textWidgets);
//         textWidgets ^= 1 << textWidget;
//
//         const uvec4 widgetCoords = textWidgetsData[textWidget]. coordinates;
//         if(! intersects(imageCoords, widgetCoords))
//         {
//             continue;
//         }
//
//         const uvec2 coordInWidget = imageCoords - widgetCoords . xy;
//         const uvec4 fontSizePacked = textWidgetsData[textWidget]. fontSize;
//         const uvec2 fontGlyphSize = fontSizePacked . xy;
//         const uint fontLayer = fontSizePacked . z;
//
//         const uint textChar = getChar(textWidget, coordInWidget, fontGlyphSize . x);
//
//         if(textChar <(32 * 3))
//         {
//
//             const float sampleValue = sampleFont(textChar, coordInWidget, fontGlyphSize, fontLayer);
//
//             vec4 color = vec4(0, 0, 0, 0.4);
//             color = mix(color, textWidgetsData[textWidget]. color, sampleValue);
//
//             blendedWidgets = blend(blendedWidgets, color);
//         }
//     }
//
//     if(blendedWidgets . a < 1)
//     {
//         vec3 blendedColor = blendedWidgets . rgb;
//         if(blendedWidgets . a > 0)
//         {
//             const vec4 color = imageLoad(blendOutput, ivec2(imageCoords));
//             blendedColor += color . rgb * color . a * blendedWidgets . a;
//         }
//         imageStore(blendOutput, ivec2(imageCoords), vec4(blendedColor, 1));
//     }
// }