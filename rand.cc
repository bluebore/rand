// Copyright (c) 2015, Baidu.com, Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Author: yanshiguang02@baidu.com

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <pthread.h>

void* MinProc(void*) {
    for (int i = 0; ; i++) {
         i = rand();
    }
    return NULL;
}
void* MaxProc(void*) {
    while (1) {
        long x = rand() % 100;
        if (x % 2 == 1) {
           long range = x * 300000000;
            int t1 = time(NULL);
            for (long i = 0; i < range; i++) {
            }
            int t2 = time(NULL);
            printf("Done one long loop %ld used %d s.\n", x, t2 - t1);
        } else {
            int mem = x * 1024 * 1024;
            char* tmp = new char[mem];
            memset(tmp, 0 , mem);
            sleep(x);
            printf("Sleep %ld s.\n", x);
            delete[] tmp;
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Use %s --conf=conf_path m c\n", argv[0]);
        return 1;
    }
    long mem = atoi(argv[2]);
    long mem_G = mem + (rand() % mem);
    long mem_M = rand() % 1024;
    long mem_res = (mem_G * 1024 + mem_M) * 1024L * 1024L;
    char* buffer_res = new char[mem_res];
    memset(buffer_res, 0 , mem_res);

    char* buffer_vm = new char[(rand() % mem) * 1024L * 1024 * 1024];

    int cpu = atoi(argv[3]);
    pthread_t tid;
    for (int i = 0; i < cpu; i++) {
        pthread_create(&tid, NULL, MaxProc, NULL);
    }
    while (1) sleep(1);

    delete[] buffer_res;
    delete[] buffer_vm;
    return 0;
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
