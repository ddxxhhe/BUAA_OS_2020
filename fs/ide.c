/*
 * operations on IDE disk.
 */

#include "fs.h"
#include "lib.h"
#include <mmu.h>

// Overview:
// 	read data from IDE disk. First issue a read request through
// 	disk register and then copy data from disk buffer
// 	(512 bytes, a sector) to destination array.
//
// Parameters:
//	diskno: disk number.
// 	secno: start sector number.
// 	dst: destination for data read from IDE disk.
// 	nsecs: the number of sectors to read.
//
// Post-Condition:
// 	If error occurred during read the IDE disk, panic. 
// 	
// Hint: use syscalls to access device registers and buffers
void
ide_read(u_int diskno, u_int secno, void *dst, u_int nsecs)
{
	// 0x200: the size of a sector: 512 bytes.
	int offset_begin = secno * 0x200;
	int offset_end = offset_begin + nsecs * 0x200;
	int offset = 0;
/*	u_int dev_addr = 0x13000000;
	u_char status = 0;
	u_char read_value = 0;

	while (offset_begin + offset < offset_end) {
            // Your code here
            // error occurred, then panic.
			u_int now_offset = offset_begin + offset;
			if (syscall_write_dev((u_int)&diskno, dev_addr + 0x10, 4) != 0) {
				user_panic("read error");
			}
			if (syscall_write_dev((u_int)&now_offset, dev_addr + 0x0, 4) != 0) {
				user_panic("read error");
			}
			if (syscall_write_dev((u_int)&read_value, dev_addr + 0x20, 4) != 0) {
				user_panic("read error");
			}
			status = 0;
			if (syscall_read_dev((u_int)&status, dev_addr + 0x30, 4) != 0) {
				user_panic("read error");
			}
			if (status == 0) {
				user_panic("read error");
			}
			if (syscall_read_dev((u_int)(dst + offset), dev_addr + 0x4000, 0x200) != 0) {
				user_panic("read error");
			}
			offset += 0x200;
	}*/  
	int offset_disk = 0;
	int read_status = 0;
	int ide_can_read = 0;
	int r;
	while (offset_begin + offset < offset_end) {
        // error occurred, then panic.
		if ((r = syscall_write_dev(&diskno, 0x13000010, 4)) != 0) {
			user_panic("write diskno failed!\n");
		}
		offset_disk = offset_begin + offset;
		if ((r = syscall_write_dev(&offset_disk, 0x13000000, 4)) != 0) {
			user_panic("write offset failed!\n");
		}
		if ((r = syscall_write_dev(&read_status, 0x13000020, 1)) != 0) {
			user_panic("write read status failed!\n");
		}
		if ((r = syscall_read_dev(&ide_can_read, 0x13000030, 1)) != 0) {
			user_panic("read the return value failed!\n");
		}
		if (ide_can_read == 0) {
			user_panic("ide read failed!\n");
		}
		if ((r = syscall_read_dev(dst + offset, 0x13004000, 0x200)) != 0) {
			user_panic("read 512 bytes data failed!\n");
		}
		offset += 0x200;
	}
}


// Overview:
// 	write data to IDE disk.
//
// Parameters:
//	diskno: disk number.
//	secno: start sector number.
// 	src: the source data to write into IDE disk.
//	nsecs: the number of sectors to write.
//
// Post-Condition:
//	If error occurred during read the IDE disk, panic.
//	
// Hint: use syscalls to access device registers and buffers
void
ide_write(u_int diskno, u_int secno, void *src, u_int nsecs)
{
        // Your code here
	int offset_begin = secno * 0x200;
	int offset_end = offset_begin + nsecs * 0x200;
	int offset = 0;
/*	u_int dev_addr = 0x13000000;
	u_char status = 0;
	u_char write_value = 1;
	writef("diskno: %d\n", diskno);
	while (offset_begin + offset < offset_end) {
		u_int now_offset = offset_begin + offset;
		if (syscall_write_dev((u_int)&diskno, dev_addr + 0x10, 4) < 0) {
			user_panic("write error");
		}
		if (syscall_write_dev((u_int)&now_offset, dev_addr + 0x0, 4) < 0) {
			user_panic("write error");
		}
		if (syscall_write_dev((u_int)&write_value, dev_addr + 0x20, 4) < 0) {
			user_panic("write error");
		}
		if (syscall_write_dev(src + offset, 0x13004000, 512) != 0) {
			user_panic("write error");
		}
		status = 0;
		if (syscall_read_dev((u_int)&status, dev_addr + 0x30, 4) < 0) {
			user_panic("write error");
		}
		if (status == 0) {
			user_panic("write error");
		}
		offset += 0x200;
	    // copy data from source array to disk buffer.

            // if error occur, then panic.
	 }*/
   int offset_disk = 0;
	int write_status = 1;
	int ide_can_write = 0;
	int r;
	
	writef("diskno: %d\n", diskno);
	while (offset_begin + offset < offset_end) {
        // error occurred, then panic.
		if ((r = syscall_write_dev(&diskno, 0x13000010, 4)) != 0) {
			user_panic("write diskno failed!\n");
      }
		offset_disk = offset_begin + offset;
		if ((r = syscall_write_dev(&offset_disk, 0x13000000, 4)) != 0) {
			user_panic("write offset failed!\n");
		}
		if ((r = syscall_write_dev(src + offset, 0x13004000, 512)) != 0) {
			user_panic("write 512 bytes data failed!\n");
		}
		if ((r = syscall_write_dev(&write_status, 0x13000020, 1)) != 0) {
			user_panic("write read status failed!\n");
		}
		if ((r = syscall_read_dev(&ide_can_write, 0x13000030, 1)) != 0) {
			user_panic("read the return value failed!\n");
		}
		if (ide_can_write == 0) {
			user_panic("ide write failed!\n");
		}
		offset += 0x200;
	}
}

