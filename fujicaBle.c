//
//  fujicaBle.c
//  fujicaBle
//
//  Created by xiaodianqian on 16/7/15.
//  Copyright © 2016年 xiaodianqian. All rights reserved.
//
//#include <android/log.h>
#include "fujicaBle.h"
void printfByte(uchar *c, int len) {
    int i = 0;
    for (; i < len; i++) {
        printf("%02x ", c[i]);
    }
    printf("\n");
}
void inttohex(unsigned long m1, uchar *result) {
    uchar data[4];
    data[0] = (m1 >> 24) & 0xff;
    data[1] = (m1 >> 16) & 0xff;
    data[2] = (m1 >> 8) & 0xff;
    data[3] = (m1 >> 0) & 0xff;
    memcpy(result, data, 4);
}
void getId(uchar *phone, uchar *des) {
    uchar    temp[9];
    memcpy(temp, phone + 2, 9);//  取出手机号码的前9位
    unsigned long longPhone = atol((char *) temp);
    // free(temp);
    uchar hexId[4];
    inttohex(longPhone, hexId);
    memcpy(des, hexId, 4);
    //  free(hexId);
}
void checkOxr(uchar des[1],uchar *src,int len){
    int i ;
    for (i = 1,des[0] = src[0]; i < len; i++) {
        des[0] ^= src[i];
    }
}
void getOpenCmdByPhone(uchar *phone, uchar *des) {
    //ID
    uchar id[4];
    getId(phone, id);
    uchar result[9] ;
    uchar start[3] = {0xA5, 0x01, 0x04};
    uchar end[1] = {0x5A};
    memcpy(result, start, 3);
    memcpy(result + 3, id, 4);
    memcpy(result + 8, end, 1);
    uchar oxr[1];
    checkOxr(oxr, id, 4);
    memcpy(result + 7, oxr, 1);
    memcpy(des,result,9);
}
void getOldOpenCmdByPhone(uchar *phone, uchar *des) {
    //ID
    uchar id[4];
    getId(phone, id);
    uchar result[8] ;
    uchar start[2] = {0x00, 0x7e};
    uchar end[1] = {0xe7};
    memcpy(result, start, 2);
    memcpy(result + 2, id, 4);
    memcpy(result + 7, end, 1);
    uchar oxr[1];
    checkOxr(oxr, id, 4);
    memcpy(result + 6, oxr, 1);
    memcpy(des,result,8);
}
void getRandomCmd(uchar *des) {
    uchar result[5] = {0xA5, 0x03, 0x00, 0x00, 0x5A};
    memcpy(des, result, 5);
}
void getOpenCmdByPhoneAndRandom(uchar *des, uchar *phone, uchar *random, uchar *key) {
    uchar result[21] = {0xA5, 0x02, 0x10,
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00, 0x00, 0x5A};
    uchar id[4] = {};
    getId(phone, id);
    printfByte(id,4);
    memcpy(result + 3, id, 4);
    memcpy(result + 7, random + 2, 4);
    uchar m_bit[8];
    memcpy(m_bit, result + 3, 8);
    uchar k_bit[16] = {0x20, 0x04, 0x04, 0x08, 0x18, 0x28, 0x38, 0x48, 0x58, 0x68, 0xFF, 0xFF, 0xFF,
                       0xFF, 0xFF, 0xFF}; //密码
    memcpy(k_bit + 10, key, 6);
    uchar e_bit[8]; //存放加密结果
    uchar f_bit[8];
    endes(m_bit, k_bit, e_bit);
    undes(e_bit, k_bit + 8, f_bit);
    endes(f_bit, k_bit, e_bit);
    memcpy(result + 3 + 8, e_bit, 8);
    uchar oxrSrc[16];
    memcpy(oxrSrc, result + 3, 16);
    uchar oxr[1];
    checkOxr(oxr, oxrSrc,16);
    memcpy(result + 19, oxr, 1);
    memcpy(des,result,21);
}