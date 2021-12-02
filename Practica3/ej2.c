//VENTURA MATEOS PEREZ
#include <stdio.h>
#include <sched.h>

int main(int argc, char * argv[]){
    int policy;
    if(policy = sched_getscheduler(0) == -1){
        perror("sched_getscheduler call error");
    }
    char * policy_out;

    switch (policy)
    {
    case SCHED_FIFO:
        policy_out = "FIFO";
        break;
    case SCHED_OTHER:
        policy_out = "OTHER";
        break;
    case SCHED_RR:
        policy_out = "RR";
        break;
    default:
        break;
    }

    printf("Policy: %s\n",policy_out);
    struct sched_param prio;
    sched_getparam(0,&prio);

    printf("Priorities for %s policy:\n\tMax:\t%d\n\tMin:\t%d\n\tCurrent:%d\n",
                policy_out,sched_get_priority_max(policy),sched_get_priority_min(policy),prio.sched_priority);

    return 0;
}