﻿

#ifndef __pe_loader_h__
#define __pe_loader_h__

#include <windows.h>
#include <stdio.h>
#include <stdint.h>

struct pe_loader
{
    char    filename[256];
    
    HANDLE  file_handl;
    HANDLE  map_handl;
    uint8_t* buf_base;
    uint8_t* image_base;
    uint8_t* sec_handl[16];
    FILE *fp;

    uint32_t entry_point;
    uint32_t fake_image_base;

    int     is_x64;
    int     pe_header_size;
    int     size_of_image;
    // 这个参数的意思时在映射到内存时，直接把整个section按照标准
    // dll加载的方式展开，这样可以直接不用再做地址访问了。
    int     expand;

    unsigned char *iat_addr[128];
    int  iat_addr_i;
};

struct pe_loader *pe_loader_create(LPCTSTR path);
void pe_loader_destroy(struct pe_loader *mod);
void pe_loader_dump(struct pe_loader *mod);
long pe_loader_section_find(struct pe_loader *mod, const char *sec_name, unsigned char **section_start, int *section_size);
int pe_loader_sym_find(struct pe_loader *mod, DWORD rva, char *sym_name, int sym_buf_siz);

int pe_loader_fix_reloc(struct pe_loader *mod, int just_vmp);
// virtual address to file address
DWORD pe_loader_rva2rfa(struct pe_loader *mod, DWORD rva);
int pe_loader_addr_in_iat(struct pe_loader *mod, unsigned char *addr);

/* 虚拟地址有2种，一种是进程运行的真实地址，一种是程序根据pe文件
 * 默认的entry point算出来的地址，这个函数计算第一种情况，下面那个
 * 带尾部2后缀的计算第2种情况  */
uint8_t* pe_loader_va2fa(struct pe_loader *mod, uint8_t *va);
uint8_t* pe_loader_va2fa2(struct pe_loader *mod, uint32_t va);

DWORD pe_loader_fa2rva(struct pe_loader *mod, DWORD64 fa);
DWORD64 pe_loader_fa_fix(struct pe_loader *mod, DWORD64 fa, int rva);
int pe_loader_fix_iat(struct pe_loader *mod);
DWORD pe_loader_entry_point(struct pe_loader *mod);
PIMAGE_DOS_HEADER pe_loader_get_dos_header(struct pe_loader *mod);
PIMAGE_NT_HEADERS pe_loader_get_nt_header(struct pe_loader *mod);
PIMAGE_FILE_HEADER pe_loader_get_file_headers(struct pe_loader *mod);


#endif