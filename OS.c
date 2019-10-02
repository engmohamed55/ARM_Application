/*-
 * OS.c
 *
 *  Created on: 16/9/2019
 *      Author: Mohamed AbdElkader - Mina Gamal
 */

#include "OS.h"
#include "OS_cfg.h"


OS_Str_Tasks_Info_t Str_Array_Tasks[MAX_NUM_TASKS];
static uint8 u8_Tasks_Index=0u;
volatile static unsigned long long OS_TickCounter=0u;
/**************************************************************************
 * Function Name : OS_init
 *
 * Description   : Set Tick time and initialize tasks buffer
 *
 * INPUTS        : void
 *
 * OUTPUTS       : void
 *
 * Return        : void
 **************************************************************************/
void OS_Init(void)
{
    uint8 u8_Array_Index;

    TIMER0_Init();
    for(u8_Array_Index=0;u8_Array_Index<MAX_NUM_TASKS;u8_Array_Index++)
    {
        Str_Array_Tasks[u8_Array_Index].OS_PTR_Function=NULL;
        Str_Array_Tasks[u8_Array_Index].Task_Priority=0u;
        Str_Array_Tasks[u8_Array_Index].Task_Periodicity=0u;
        Str_Array_Tasks[u8_Array_Index].Task_Status=WAITING;
        Str_Array_Tasks[u8_Array_Index].Task_Start_Time=0u;

    }
}
/**************************************************************************
 * Function Name : Create_Task
 *
 * Description   : Creating Tasks and assign it in the buffer
 *
 * INPUTS        : void
 *
 * OUTPUTS       : void
 *
 * Return        : void
 **************************************************************************/
OS_Status_t Create_Task(OS_PTR_Function OS_PTR_Function,uint8 Task_Priority,uint16 Task_Periodicity,uint16 Task_Temp_Periodicity,uint16 Task_Start_time)
{
    OS_Status_t Ret_Value;
    /*Check for first Null*/
    if(u8_Tasks_Index<MAX_NUM_TASKS)
    {
        Str_Array_Tasks[u8_Tasks_Index].OS_PTR_Function = OS_PTR_Function;
        Str_Array_Tasks[u8_Tasks_Index].Task_Priority = Task_Priority;
        Str_Array_Tasks[u8_Tasks_Index].Task_Periodicity = Task_Periodicity;
        Str_Array_Tasks[u8_Tasks_Index].Task_Status = WAITING;
        Str_Array_Tasks[u8_Tasks_Index].Task_Temp_Periodicity=Task_Temp_Periodicity;
        Str_Array_Tasks[u8_Tasks_Index].Task_Start_Time=Task_Start_time;
        u8_Tasks_Index++;
        Ret_Value=OS_OK;
    }
    else
    {
        Ret_Value=OS_NOT_OK;
    }
    return Ret_Value;
}
/**************************************************************************
 * Function Name : Delete_Task
 *
 * Description   : Deleting Tasks and removing its Pointer to function form the structure
 *
 * INPUTS        : Pointer to function , Task priority ,Task periodicity
 *
 * OUTPUTS       : void
 *
 * Return        : void
 **************************************************************************/
OS_Status_t Delete_Task(OS_PTR_Function OS_PTR_Function)
{
    uint8 u8_Array_Index;
    OS_Status_t Ret_Value=OS_NOT_OK;
    for(u8_Array_Index=0;u8_Array_Index<u8_Tasks_Index;u8_Array_Index++)
    {
        if(Str_Array_Tasks[u8_Array_Index].OS_PTR_Function==OS_PTR_Function)
        {
            Str_Array_Tasks[u8_Array_Index].OS_PTR_Function=NULL;
            Str_Array_Tasks[u8_Array_Index].Task_Priority=0u;
            Str_Array_Tasks[u8_Array_Index].Task_Periodicity=0u;
            Str_Array_Tasks[u8_Array_Index].Task_Status=DELETED;
            Str_Array_Tasks[u8_Array_Index].Task_Temp_Periodicity=0u;
            Str_Array_Tasks[u8_Tasks_Index].Task_Start_Time=0u;

            Ret_Value=OS_OK;
        }
    }
    return Ret_Value;
}
/**************************************************************************
 * Function Name : OS_Run
 *
 * Description   : Running the scheduler with while(1) which manage tasks and run the task when its time come and
 *                 have max Priority.
 *
 * INPUTS        : pointer to function
 *
 * OUTPUTS       : void
 *
 * Return        : void
 **************************************************************************/
extern void OS_Run(void)
{
    uint8 u8_Array_Index;
    uint8 u8_Priority_Index;
    while(1)
    {
        for(u8_Array_Index = 0u ; u8_Array_Index < u8_Tasks_Index ; u8_Array_Index++)
        {
            // check if the tack is ready.
            if( Str_Array_Tasks[u8_Array_Index].Task_Status == READY)
            {
                //if this task is ready check is't priority to insure it have the highest priority
                for(u8_Priority_Index = HIGHST_PRIORITY ; u8_Priority_Index <= LOWEST_PRIORITY ; u8_Priority_Index++)
                {
                    //if there is two tasks or more have to be run check its priority and run the highest then the lower
                    if( Str_Array_Tasks[u8_Array_Index].Task_Priority == u8_Priority_Index )
                    {
                        //if the task has highest priority and its time to run change its state to running state
                        Str_Array_Tasks[u8_Array_Index].Task_Status = RUNNING;
                        if(Str_Array_Tasks[u8_Array_Index].Task_Status == RUNNING)
                        {
                            //run task here
                            Str_Array_Tasks[u8_Array_Index].OS_PTR_Function();
                        }
                        //change its state to waiting until its time come again
                        Str_Array_Tasks[u8_Array_Index].Task_Status = WAITING;
                    }
                }
            }
        }
    }
}
/**************************************************************************
 * Function Name : OS_Long_Term
 *
 * Description   : Callback function to update status will be called from
 *
 * INPUTS        : void
 *
 * OUTPUTS       : void
 *
 * Return        : void
 **************************************************************************/
void OS_Long_Term(void)
{
    uint8 u8_Array_Index;
    for(u8_Array_Index = 0u ;u8_Array_Index < u8_Tasks_Index ; u8_Array_Index++)
    {
        if(Str_Array_Tasks[u8_Array_Index].Task_Temp_Periodicity == 1000000)
        {
            OS_TickCounter=1;
            Str_Array_Tasks[u8_Array_Index].Task_Temp_Periodicity =1;
        }

        if( Str_Array_Tasks[u8_Array_Index].Task_Temp_Periodicity == OS_TickCounter )
        {
            Str_Array_Tasks[u8_Array_Index].Task_Temp_Periodicity = Str_Array_Tasks[u8_Array_Index].Task_Periodicity + OS_TickCounter ;
            Str_Array_Tasks[u8_Array_Index].Task_Status = READY;
        }
        else
        {
            Str_Array_Tasks[u8_Array_Index].Task_Status = WAITING;
        }

    }

    OS_TickCounter++;
}
/**************************************************************************
 * Function Name : OS_Deinit
 *
 * Description   : de-initialize the OS
 *
 * INPUTS        : void
 *
 * OUTPUTS       : void
 *
 * Return        : void
 **************************************************************************/
void OS_Deinit(void)
{
    TIMER0_deInit();
}
