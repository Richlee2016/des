//
// Created by linuxiao on 2016/7/8.
//

#include "config.h"

#ifndef BLUETOOCH_ENDES_H
#define BLUETOOCH_ENDES_H

#ifndef LOG_TAG
#define LOG_TAG "ANDROID_LAB"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#endif

#endif //BLUETOOCH_ENDES_H

void undes(uchar *m_bit, uchar *k_bit, uchar *e_bit);

void endes(uchar m_bit[8], uchar k_bit[8], uchar e_bit[8]);

