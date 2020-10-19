#include <stdint.h>
#include <limits.h>
#include <string.h>

#include "defaultTask.h"
#include "queue.h"

static DEVICE_STATE_t device_state = DEVICE_STATE_idle;
void defaultTask(const DEFAULTMSGQ_t *Q)
{
    switch (Q->msg.ctx)
    {
        default:
        {
            switch (Q->msg.evt)
            {
                case TASK_DEFAULT_EVENT_boot:
                {
                    /* wait for outpost ID packet before activating GPIO */
                    device_state = DEVICE_STATE_idle;

                    /** @note THIS DOESNT GO HERE. ITS BEING PLACED HERE FOR
                     * HEARTBEAT DURING DEVELOPMENT */
                    USBSERIALMSGQ_t usmsg;
                    memset(&usmsg, 0, sizeof(usmsg));
                    usmsg.msg.ctx = TASK_USBSERIAL_CONTEXT_general;
                    usmsg.msg.evt = TASK_USBSERIAL_GENERAL_EVENT_start_notifs;
                    xQueueSend(usbSerialMsgQHandle, (void *)&usmsg, 0);
                }
                break;
            }
        }
        break;
    }
}
