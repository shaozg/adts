#ADTS
##什么是ADTS
ADTS全称是(Audio Data Transport Stream)，是AAC的一种十分常见的传输格式。
一般的AAC解码器都需要把AAC的ES流打包成ADTS的格式，一般是在AAC ES流前添加7个字节的ADTS header。也就是说你可以吧ADTS这个头看作是AAC的frameheader。
##ADTS内容及结构
ADTS 头中相对有用的信息 采样率、声道数、帧长度。
一般情况下ADTS的头信息都是7个字节，分为2部分：
### 1 固定部分

```
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
```

### 2 可变部分
```
typedef struct adts_variable_header {
    unsigned char copyright_identification_bit:		1;
    unsigned char copyright_identification_start:	1;
    unsigned short aac_frame_length:				13;
    unsigned short adts_buffer_fullness:			11;
    unsigned char number_of_raw_data_blocks_in_frame:2;
} adts_variable_header; // length : 28 bits
```
## 如何使用?
直接将adts.h & adts.c这两个文件加入到工程中即可编译.
