#include "lib.h"

void
umain(void) 
{
	u_int who1 = 0x800, who2 = 0x1802, i;
	ipc_send_double(who1, who2, 0, 0, 0);
	for (;;) {
		i = ipc_recv(&who1, 0, 0);
		i = ipc_recv(&who2, 0, 0);
		if (i == 5) {
			return;
		}
		i++;
		ipc_send_double(who1, who2, i, 0, 0);
		if (i == 5) {
			return;
		}
	}
}
