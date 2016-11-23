#include "cmd.h"
#include "includes.h"
#include <stdbool.h>

void *worker();

bool all_workers_stopped();
void wait_all_workers_stopped(void);

