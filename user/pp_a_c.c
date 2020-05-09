#include "lib.h"

void 
umain(void)
{
	u_int who = 0x1001, i = 0;
	for (;;) {
		writef("\n@@@@ %x got %d from %x", syscall_getenvid(), i, who);
		i = ipc_recv(&who, 0, 0);
//		writef("\n@@@@ %x got 0 from %x", syscall_getenvid(), who);
		if (i == 5) {
			return;
		}
		i++;
		writef("\n@@@@ send %d from %x to %x", i, syscall_getenvid(), who);
		ipc_send(who, i, 0, 0);
		if (i == 5) {
			return;
		}
	}
}
