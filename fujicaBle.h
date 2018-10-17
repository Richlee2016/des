//
//  fujicaBle.h
//  fujicaBle
//
//  Created by xiaodianqian on 16/7/15.
//  Copyright © 2016年 xiaodianqian. All rights reserved.
//
#ifndef fujicaBle_h
#define fujicaBle_h
//#include <stdio.h>
#include "config.h"
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
#include "endes.h"
#endif /* fujicaBle_h */
void getOpenCmdByPhone(uchar *phone, uchar *result);
void getOldOpenCmdByPhone(uchar *phone, uchar *result);
void getRandomCmd(uchar *des);
void getOpenCmdByPhoneAndRandom(uchar *des,uchar *phone, uchar *random, uchar *key);