/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 02:03:35 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 02:43:56 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELF_H
# define ELF_H
# undef ELF_H
# ifndef __RT_DEVRELOAD_ELF_H__
#  define __RT_DEVRELOAD_ELF_H__

#  include <stdint.h>
#  include <stddef.h>

//////////////////////////////////////////////////////////////
///					elf header
//////////////////////////////////////////////////////////////

typedef uint16_t	t_elf64_half;			// 16-bit unsigned integer
typedef uint32_t	t_elf64_word;			// 32-bit unsigned integer
typedef uint64_t	t_elf64_addr;			// 64-bit unsigned integer (address)
typedef uint64_t	t_elf64_off;			// 64-bit unsigned integer (offset)

typedef struct s_elf64_ehdr
{
	unsigned char	e_ident[16];	// EI_NIDENT is usually defined as 16
	t_elf64_half	e_type;			// Object file type
	t_elf64_half	e_machine;		// Architecture
	t_elf64_word	e_version;		// Object file version
	t_elf64_addr	e_entry;		// Entry point virtual address
	t_elf64_off		e_phoff;		// Program header table file offset
	t_elf64_off		e_shoff;		// Section header table file offset
	t_elf64_word	e_flags;		// Processor-specific flags
	t_elf64_half	e_ehsize;		// ELF header size in bytes
	t_elf64_half	e_phentsize;	// Program header table entry size
	t_elf64_half	e_phnum;		// Number of program header entries
	t_elf64_half	e_shentsize;	// Section header table entry size
	t_elf64_half	e_shnum;		// Number of section header entries
	t_elf64_half	e_shstrndx;		// Section header string table index
}	t_elf64_ehdr;

typedef struct s_elf64_eident
{
	char	ei_magic[4];	// Magic number (0x7F 'E' 'L' 'F')
	uint8_t	ei_class;		// File class (none or 32-bit or 64-bit)
	uint8_t	ei_data;		// Data encoding (01 little endian or 02 big endian)
	uint8_t	ei_version;		// ELF version normaly always 1
	uint8_t	ei_osabi;		// OS ABI (target operating system ABI);
							// is a lot of the time set to 0 (none)
	uint8_t	ei_abiversion;	// ABI version (almost never use)
	uint8_t	ei_pad[7];		// Padding (should be all 0's)
}	t_elf64_eident;

typedef enum e_elf64_etype
{
	ET_NONE		= 0,		// No file type
	ET_REL		= 1,		// Relocatable file
	ET_EXEC		= 2,		// Executable file
	ET_DYN		= 3,		// Shared object file
	ET_CORE		= 4,		// Core file
	ET_LOOS		= 0xFE00,	// Operating system-specific
	ET_HIOS		= 0xFEFF,	// Operating system-specific
	ET_LOPROC	= 0xFF00,	// Processor-specific
	ET_HIPROC	= 0xFFFF	// Processor-specific
}	t_elf64_etype;

typedef enum e_elf64_emachine
{
	EM_NONE		= 0,		// No machine
	EM_M32		= 1,		// AT&T WE 32100
	EM_SPARC	= 2,		// SPARC
	EM_386		= 3,		// Intel 80386
	EM_68K		= 4,		// Motorola 68000
	EM_88K		= 5,		// Motorola 88000
	EM_IAMCU	= 6,		// Intel MCU
	EM_860		= 7,		// Intel 80860
	EM_MIPS		= 8,		// MIPS R3000
	EM_ARM		= 40,		// ARM
	EM_X86_64	= 62,		// x86-64
	EM_AARCH64	= 183,		// ARM 64-bit (AARCH64)
	EM_RISCV	= 243,		// RISC-V
	EM_LOPROC	= 0xFF00,	// Processor-specific
	EM_HIPROC	= 0xFFFF	// Processor-specific
}	t_elf64_emachine;

//////////////////////////////////////////////////////////////
///					PROGRAM header
//////////////////////////////////////////////////////////////

typedef struct s_elf64_phdr
{
	uint32_t	p_type;		// Segment type
	uint32_t	p_flags;	// Segment flags
	uint64_t	p_offset;	// Offset of the segment in the file
	uint64_t	p_vaddr;	// Virtual address of the segment in memory
	uint64_t	p_paddr;	// Physical address (not relevant on most platforms,
							// use p_vaddr)
	uint64_t	p_filesz;	// Size of the segment in the file
	uint64_t	p_memsz;	// Size of the segment in memory
	uint64_t	p_align;	// Alignment of the segment
}	t_elf64_phdr;

typedef enum e_elf64_ptype
{
	PT_NULL		= 0,				// Unused segment
	PT_LOAD		= 1,				// Loadable segment
	PT_DYNAMIC	= 2,				// Dynamic linking information
	PT_INTERP	= 3,				// Interpreter path
	PT_NOTE		= 4,				// Auxiliary information
	PT_SHLIB	= 5,				// Reserved
	PT_PHDR		= 6,				// Program header itself
	PT_TLS		= 7,				// Thread-Local Storage
	PT_LOOS		= 0x60000000,		// OS-specific
	PT_HIOS		= 0x6fffffff,		// OS-specific
	PT_LOPROC	= 0x70000000,		// Processor-specific
	PT_HIPROC	= 0x7fffffff		// Processor-specific
}	t_elf64_ptype;

typedef enum e_elf64_pflags
{
	PF_X = 0x1,	// Execute permission
	PF_W = 0x2,	// Write permission
	PF_R = 0x4	// Read permission
}	t_elf64_pflags;

//////////////////////////////////////////////////////////////
///					Section header
//////////////////////////////////////////////////////////////

typedef struct s_elf64_shdr
{
	uint32_t	sh_name;		// Section name (offset into the section header
								// string table)
	uint32_t	sh_type;		// Section type (SHT_PROGBITS, SHT_SYMTAB, etc.)
	uint64_t	sh_flags;		// Section attributes (write, exec, etc.)
	uint64_t	sh_addr;		// Virtual address in memory where
								// the section will be loaded
	uint64_t	sh_offset;		// Offset of the section in the file
	uint64_t	sh_size;		// Size of the section in bytes
	uint32_t	sh_link;		// Link to another section (depends on type)
	uint32_t	sh_info;		// Additional information (depends on type)
	uint64_t	sh_addralign;	// Alignment of the section
	uint64_t	sh_entsize;		// Size of entries, if the section holds a table
}	t_elf64_shdr;

typedef enum e_elf64_shtype
{
	SHT_NULL		= 0,	// Section header is inactive
	SHT_PROGBITS	= 1,	// Program information
	SHT_SYMTAB		= 2,	// Symbol table
	SHT_STRTAB		= 3,	// String table
	SHT_RELA		= 4,	// Relocation entries with addends
	SHT_HASH		= 5,	// Symbol hash table
	SHT_DYNAMIC		= 6,	// Dynamic linking information
	SHT_NOTE		= 7,	// Auxiliary information
	SHT_NOBITS		= 8,	// Uninitialized data (e.g., .bss)
	SHT_REL			= 9,	// Relocation entries without addends
	SHT_DYNSYM		= 11	// Dynamic symbol table
}	t_elf64_shtype;

typedef enum e_elf64_shflags
{
	SHF_WRITE		= 0x1,	// Section contains writable data
	SHF_ALLOC		= 0x2,	// Section is allocated in memory
	SHF_EXECINSTR	= 0x4	// Section contains executable instructions
}	t_elf64_shflags;

	//////////////////////////////////////////////////////////////
	///					Symbol header
	//////////////////////////////////////////////////////////////

typedef struct s_elf64_sym
{
	uint32_t	st_name;	// Offset into the string table for the symbol name
	uint8_t		st_info;	// Type and binding attributes of the symbol
	uint8_t		st_other;	// Visibility of the symbol
	uint16_t	st_shndx;	// Section index the symbol is in
	uint64_t	st_value;	// Symbol value (e.g., address)
	uint64_t	st_size;	// Size of the symbol
}	t_elf64_sym;

typedef struct s_elf64_rela
{
	uint64_t	r_offset;	// Offset where relocation applies
	uint64_t	r_info;		// Symbol and type of relocation
	int64_t		r_addend;	// Constant addend (only in RELA relocations)
}	t_elf64_rela;

# endif // __RT_DEVRELOAD_ELF_H__
#endif // ELF_H
