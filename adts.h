//
//  adts.h
//  AdtsTest
//
//  Created by zg.shao on 15/4/9.
//  Copyright (c) 2015年 shaozg.cn. All rights reserved.
//

#ifndef __AdtsHeader__adts__
#define __AdtsHeader__adts__

#include <stdio.h>
#include <stdint.h>

/*
 * ADTS 全称: Audio Data Transport Stream. 是 AAC音频的传输流格式.
 * ADTS头中相对有用的信息包括: 采样率, 声道数, 帧长度. 每一个带ADTS头信息的AAC流都会清晰的告诉解码器他需要的这些信息.
 * 一般情况下ADTS的头信息都是7个字节, 分为两部分: 前28bit是 adts_fixed_header, 后28bit是 adts_variable_header.
 */

typedef struct adts_fixed_header {
    unsigned short syncword:				12;
    unsigned char id:                       1;
    unsigned char layer:					2;
    unsigned char protection_absent:        1;
    unsigned char profile:                  2;
    unsigned char sampling_frequency_index: 4;
    unsigned char private_bit:              1;
    unsigned char channel_configuration:	3;
    unsigned char original_copy:			1;
    unsigned char home:                     1;
} adts_fixed_header; // length : 28 bits

typedef struct adts_variable_header {
    unsigned char copyright_identification_bit:		1;
    unsigned char copyright_identification_start:	1;
    unsigned short aac_frame_length:				13;
    unsigned short adts_buffer_fullness:			11;
    unsigned char number_of_raw_data_blocks_in_frame:2;
} adts_variable_header; // length : 28 bits

// 设置adts固定的一部分
extern void set_fixed_header(adts_fixed_header *header);

// 设置adts可变的一部分
extern void set_variable_header(adts_variable_header *header, const int aac_raw_data_length);


// 解析buff中的adts固定部分头信息
extern void get_fixed_header(const unsigned char buff[7], adts_fixed_header *header);

// 解析buff中的adts可变部分头信息
extern void get_variable_header(const unsigned char buff[7], adts_variable_header *header);


// 将adts头信息转化为一个64位的整数, PS: 前面8位空着
extern void convert_adts_header2int64(const adts_fixed_header *fixed_header, const adts_variable_header *variable_header, uint64_t *header);

// 将adts头信息转化为一个7字节的buff
extern void convert_adts_header2char(const adts_fixed_header *fixed_header, const adts_variable_header *variable_header, unsigned char buffer[7]);

#endif /* defined(__AdtsHeader__adts__) */
