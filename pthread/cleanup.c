/*
 * Whitecat, pthread implementation ober FreeRTOS
 *
 * Copyright (C) 2015 - 2016
 * IBEROXARXA SERVICIOS INTEGRALES, S.L. & CSS IBÉRICA, S.L.
 * 
 * Author: Jaume Olivé (jolive@iberoxarxa.com / jolive@whitecatboard.org)
 * 
 * All rights reserved.  
 *
 * Permission to use, copy, modify, and distribute this software
 * and its documentation for any purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that the copyright notice and this
 * permission notice and warranty disclaimer appear in supporting
 * documentation, and that the name of the author not be used in
 * advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.
 *
 * The author disclaim all warranties with regard to this
 * software, including all implied warranties of merchantability
 * and fitness.  In no event shall the author be liable for any
 * special, indirect or consequential damages or any damages
 * whatsoever resulting from loss of use, data or profits, whether
 * in an action of contract, negligence or other tortious action,
 * arising out of or in connection with the use or performance of
 * this software.
 */

#include "pthread.h"

#include <errno.h>
#include <stdlib.h>

extern struct list thread_list;

void pthread_cleanup_push(void (*routine)(void *), void *arg) {
    struct pthread *thread;
    struct pthread_clean *clean;
    int res, idx;
    
    // Get current thread
    res = list_get(&thread_list, pthread_self(), (void **)&thread);
    if (res == 0){
        clean =(struct pthread_clean *) malloc(sizeof(struct pthread_clean));
        if (!clean) {
            return;
        }
        
        clean->clean = routine;
        clean->args = arg;
        
        list_add(&thread->clean_list, clean, &idx);
    }
}
