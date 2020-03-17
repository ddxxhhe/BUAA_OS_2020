/* This is a simplefied ELF reader.
 * You can contact me if you find any bugs.
 *
 * Luming Wang<wlm199558@126.com>
 */

#include "kerelf.h"
#include <stdio.h>
/* Overview:
 *   Check whether it is a ELF file.
 *
 * Pre-Condition:
 *   binary must longer than 4 byte.
 *
 * Post-Condition:
 *   Return 0 if `binary` isn't an elf. Otherwise
 * return 1.
 */
int is_elf_format(u_char *binary)
{
        Elf32_Ehdr *ehdr = (Elf32_Ehdr *)binary;
        if (ehdr->e_ident[EI_MAG0] == ELFMAG0 &&
                ehdr->e_ident[EI_MAG1] == ELFMAG1 &&
                ehdr->e_ident[EI_MAG2] == ELFMAG2 &&
                ehdr->e_ident[EI_MAG3] == ELFMAG3) {
                return 1;
        }

        return 0;
}

/* Overview:
 *   read an elf format binary file. get ELF's information
 *
 * Pre-Condition:
 *   `binary` can't be NULL and `size` is the size of binary.
 *
 * Post-Condition:
 *   Return 0 if success. Otherwise return < 0.
 *   If success, output address of every section in ELF.
 */

/*
    Exercise 1.2. Please complete func "readelf". 
*/

unsigned int Reverse32(unsigned int num){
	unsigned int ret = 0;
	int i;
	for(i = 0;i < 32;i++){
		ret <<= 1;
		ret |= num&1;
		num >>= 1;
	}
	return ret;
}

unsigned int Reverse16(unsigned int num){
	unsigned int ret = 0;
	int i;
	for(i = 0;i < 16;i++){
		ret <<= 1;
		ret |= num&1;
		num >>= 1;
	}
	return ret;
}

int readelf(u_char *binary, int size)
{
        Elf32_Ehdr *ehdr = (Elf32_Ehdr *)binary;

        int Nr;

	Elf32_Phdr *phdr = NULL;
	u_char *ptr_ph_table = NULL;

	Elf32_Half ph_entry_count;
	Elf32_Half ph_entry_size;

        // check whether `binary` is a ELF file.
        if (size < 4 || !is_elf_format(binary)) {
                printf("not a standard elf format\n");
                return 0;
        }else{

	if(ehdr->e_ident[5] == 1){
	ph_entry_count = ehdr->e_phnum;
	ph_entry_size = ehdr->e_phentsize;
	ptr_ph_table = (u_char *)(((u_char *)ehdr) + ehdr->e_phoff);
	phdr = (Elf32_Phdr *)(ptr_ph_table);	
	for(Nr = 0;Nr < ph_entry_count;Nr++){
		printf("%d:0x%x,0x%x\n",Nr,phdr->p_filesz,phdr->p_memsz);
		phdr++;
		}
	}

	else if(ehdr->e_ident[5] == 2){
//		printf("%d\n",ehdr->e_phnum);
		ph_entry_count = Reverse16(ehdr->e_phnum);
		ph_entry_size = Reverse16(ehdr->e_phentsize);
		ptr_ph_table = (u_char *)(((u_char *)ehdr) + Reverse32(ehdr->e_phoff));
//		printf("%d",ph_entry_count);
		phdr = (Elf32_Phdr *)(ptr_ph_table);
		for(Nr = 0;Nr < ph_entry_count;Nr++){
			printf("%d:0x%x,0x%x\n",Nr,Reverse32(phdr->p_filesz),Reverse32(phdr->p_memsz));
			phdr++;
		}
	}

	else{
		printf("illegal input");
	}
	}
        return 0;
}

