#include "lib.h"

void
umain(void) 
{
	u_int who1 = 0x800, who2 = 0x1802, i = 0;
	writef("\n@@@@ %x send %x,%x 0", syscall_getenvid(), who1, who2);
	ipc_send_double(who1, who2, 0, 0, 0);
	for (;;) {
		writef("\n@@@@ %x got %d from %x",syscall_getenvid(), i, who1);
		i = ipc_recv(&who1, 0, 0);
		writef("\n@@@@ %x got %d from %x",syscall_getenvid(), i, who2);
		i = ipc_recv(&who2, 0, 0);
		if (i == 5) {
			return;
		}
		i++;
		writef("\n@@@@ %x send %x,%x %d", syscall_getenvid(), who1, who2, i);
		ipc_send_double(who1, who2, i, 0, 0);
		if (i == 5) {
			return;
		}
	}
}
