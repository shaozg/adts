#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <math.h>
#include "adts.h"


#define BUFFER_SIZE (100)

static void print_binary(u_int64_t value) {
    int index = 0;
    int binary_count = sizeof(u_int64_t) * 8;
    while (binary_count-- > 0) {
        u_int64_t tmp = value >> binary_count;
        if ((tmp & 0x01) == 1) {
            printf("1");
        } else {
            printf("0");
        }
        
        if (++index % 8 == 0) {
            printf(" ");
        }
    }
    
    printf("==> %lld \n", value);
}

static void print_fixed_header(const adts_fixed_header *header) {
    printf("---- ADTS fixed header details: ----\n");
    printf("syncword:%02X\n", header->syncword);
    printf("id:%d\n", header->id);
    printf("layer:%d\n", header->layer);
    printf("protection_absent:%d\n", header->protection_absent);
    printf("profile:%d\n", header->profile);
    printf("sampling_frequency_index:%d\n", header->sampling_frequency_index);
    printf("private_bit:%d\n", header->private_bit);
    printf("channel_configuration:%d\n", header->channel_configuration);
    printf("original_copy:%d\n", header->original_copy);
    printf("home:%d\n", header->home);
    printf("------------------------------------------\n");
}

static void print_variable_header(const adts_variable_header *header) {
    printf("---- ADTS variable header details: ----\n");
    printf("copyright_identification_bit:%d\n", header->copyright_identification_bit);
    printf("copyright_identification_start:%d\n", header->copyright_identification_start);
    printf("aac_frame_length:%d\n", header->aac_frame_length);
    printf("adts_buffer_fullness:%d\n", header->adts_buffer_fullness);
    printf("number_of_raw_data_blocks_in_frame:%d\n", header->number_of_raw_data_blocks_in_frame);
    printf("------------------------------------------\n");
}

int main(int argc, char **argv) {
    adts_fixed_header fixed_header;
    adts_variable_header variable_header;
    
    memset(&fixed_header, 0, sizeof(adts_fixed_header));
    memset(&variable_header, 0, sizeof(adts_variable_header));
    
    char *buffer = (char *)malloc(BUFFER_SIZE + 7);

    unsigned char adts[7];
    // 1 组装 buffer
    set_fixed_header(&fixed_header);
    set_variable_header(&variable_header, BUFFER_SIZE);
    
    convert_adts_header2char(&fixed_header, &variable_header, adts);
    
    memcpy(&buffer[0], adts, 7);
    
    // 2 打印组装的buffer头7个字节
    print_fixed_header(&fixed_header);
    print_variable_header(&variable_header);
    
    // 3 拆解 buffer
    unsigned char headerBuff[7];
    memcpy(headerBuff, buffer, 7);
    memset(&fixed_header, 0, sizeof(adts_fixed_header));
    memset(&variable_header, 0, sizeof(adts_variable_header));
    get_fixed_header(headerBuff, &fixed_header);
    get_variable_header(headerBuff, &variable_header);
    
    // 4 打印拆解后的结构体
    print_fixed_header(&fixed_header);
    print_variable_header(&variable_header);
    free(buffer);
    
    return 0;
}