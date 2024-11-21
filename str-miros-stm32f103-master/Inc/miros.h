/****************************************************************************
* MInimal Real-time Operating System (MiROS)
* version 1.26 (matching lesson 26, see https://youtu.be/kLxxXNCrY60)
*
* This software is a teaching aid to illustrate the concepts underlying
* a Real-Time Operating System (RTOS). The main goal of the software is
* simplicity and clear presentation of the concepts, but without dealing
* with various corner cases, portability, or error handling. For these
* reasons, the software is generally NOT intended or recommended for use
* in commercial applications.
*
* Copyright (C) 2018 Miro Samek. All Rights Reserved.
*
* SPDX-License-Identifier: GPL-3.0-or-later
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <https://www.gnu.org/licenses/>.
*
* Git repo:
* https://github.com/QuantumLeaps/MiROS
****************************************************************************/
#ifndef MIROS_H
#define MIROS_H


typedef struct {
    uint32_t deadline_absolute;
    uint32_t deadline_dinamic;
    uint32_t period_absolute;
    uint32_t period_dinamic;
} OSThread_periodics_task_parameters;


/* Thread Control Block (TCB) */
typedef struct {
    void *sp; /* stack pointer */
    uint32_t timeout; /* timeout delay down-counter */
    uint8_t prio; /* thread index */
    OSThread_periodics_task_parameters *task_parameters;
    /* ... other attributes associated with a thread */
} OSThread;

typedef struct {
	uint32_t sem_value;		//
    uint32_t max_value;
} semaphore_t;

typedef struct {
    OSThread TCB_thread;
    uint32_t stack_thread[40];
} struct_periodic_task;

typedef struct {
    struct_periodic_task *p_task;
    uint8_t priority_level;
} struct_priority_task;

#define TICKS_PER_SEC 100U

typedef void (*OSThreadHandler)();

void OS_calculate_next_periodic_task (void);

void OS_wait_next_period(void);

void OS_finished_aperiodic_task(void);

void enter_critical_region();

void out_critical_region();

void OS_init(void *stkSto, uint32_t stkSize);

/* callback to handle the idle condition */
void OS_onIdle(void);

/* this function must be called with interrupts DISABLED */
void OS_sched(void);

/* transfer control to the RTOS to run the threads */
void OS_run(void);

/* blocking delay */
void OS_delay(uint32_t ticks);

/* process all timeouts */
void OS_tick(void);

/* callback to configure and start interrupts */
void OS_onStartup(void);

/* initialization of the semaphore variable */
void semaphore_init(semaphore_t *p_semaphore, uint32_t start_value);

/*  */
void sem_up(semaphore_t *p_semaphore);

/*  */
void sem_down(semaphore_t *p_semaphore);


/*  */
void error_indicator_blink();

void OSAperiodic_task_start(OSThread *me,
    OSThreadHandler threadHandler,
    void *stkSto, uint32_t stkSize);

void OSPeriodic_task_start(
    OSThread *me,
    OSThreadHandler threadHandler,
    void *stkSto, uint32_t stkSize);

#endif /* MIROS_H */
