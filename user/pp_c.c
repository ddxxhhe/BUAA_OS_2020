#include "lib.h"

void
umain(void)
{
	u_int who = 0x1001, i;
	for(;;) {
		i = ipc_recv(&who, 0, 0);
		if (i == 5) {
			return;
		}
		i++;
		ipc_send(who, i, 0, 0);
		if (i == 5) {
			return;
		}
	}
}
