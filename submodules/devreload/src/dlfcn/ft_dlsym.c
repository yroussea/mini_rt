/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlsym.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 02:46:32 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/26 01:57:38 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#define __RT_DEVRELOAD_DLFCN_INTERNAL__
#include <rt/devreload/dlfcn.h>
#include <rt/devreload/elf.h>

#define STT_GNU_IFUNC 10
#define DYNSYM_SECT ".dynsym"
#define DYNSTR_SECT ".dynstr"

static t_elf64_shdr	*find_dlsym_header_offset(t_elf64_shdr *shdr,
		uint16_t nb_shdr, const char *shstrtab)
{
	while (nb_shdr--)
	{
		if (shdr->sh_type == SHT_DYNSYM
			&& !ft_strcmp(shstrtab + shdr->sh_name, DYNSYM_SECT))
			return (shdr);
		shdr++;
	}
	return (0);
}

static t_elf64_shdr	*find_symbol_string_table_offset(t_elf64_shdr *shdr,
						uint16_t nb_shdr, const char *shstrtab)
{
	while (nb_shdr--)
	{
		if (shdr->sh_type == SHT_STRTAB
			&& !ft_strcmp(shstrtab + shdr->sh_name, DYNSTR_SECT))
			return (shdr);
		shdr++;
	}
	return (0);
}

static t_elf64_sym	*shdr_to_simbol(void *handle, t_elf64_shdr *sym_hdr,
						t_elf64_shdr *sym_string, const char *symbol)
{
	t_elf64_sym	*sym;
	uint16_t	nb_sym;
	const char	*sym_str;
	void		*result;

	sym = handle + sym_hdr->sh_offset;
	nb_sym = sym_hdr->sh_size / sizeof(t_elf64_sym);
	sym_str = handle + sym_string->sh_offset;
	result = NULL;
	while (nb_sym-- && !result)
	{
		if (!ft_strcmp(sym_str + sym->st_name, symbol))
			result = sym;
		sym++;
	}
	return (result);
}

static t_elf64_sym	*find_symbol(t_elf64_ehdr *header, t_elf64_shdr *shdr,
						const char *shstrtab, const char *symbol)
{
	t_elf64_shdr	*sym_hdr;
	t_elf64_shdr	*sym_string_hdr;
	const uint64_t	nb_shdr = header->e_shnum;

	sym_hdr = find_dlsym_header_offset(shdr, nb_shdr, shstrtab);
	if (!sym_hdr)
		return (NULL);
	sym_string_hdr = find_symbol_string_table_offset(shdr, nb_shdr, shstrtab);
	if (!sym_string_hdr)
		return (NULL);
	return (shdr_to_simbol(header, sym_hdr, sym_string_hdr, symbol));
}

void	*ft_dlsym(void *handle, const char *symbol)
{
	t_elf64_ehdr	*elf_header;
	t_elf64_shdr	*shdr;
	t_elf64_shdr	*shstrtab_hdr;
	char			*shstrtab;
	t_elf64_sym		*sym;

	handle = ((t_dl_info *)handle)->start;
	elf_header = handle;
	shdr = (t_elf64_shdr *)(handle + elf_header->e_shoff);
	shstrtab_hdr = &shdr[elf_header->e_shstrndx];
	shstrtab = (char *)(handle + shstrtab_hdr->sh_offset);
	sym = find_symbol(handle, shdr, shstrtab, symbol);
	if (!sym)
		return (NULL);
	if ((sym->st_info & 0xf) == STT_GNU_IFUNC)
		return (NULL);
	RT_DEBUG("symbol %s found at %p\n", symbol, handle + sym->st_value);
	return (handle + sym->st_value);
}
