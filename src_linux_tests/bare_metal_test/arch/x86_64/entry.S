/* arch/x86_64/entry.S - 64-bit Long Mode entry with Multiboot2
 * QEMU -kernel with Multiboot2 supports 64-bit ELF images.
 * The bootloader still starts us in 32-bit protected mode;
 * we set up paging and transition to IA-32e (Long Mode).
 */

.extern kmain

/* ---- Multiboot2 header (8-byte aligned) ---- */
.section .multiboot
.align 8
mb2_header_start:
    .long 0xE85250D6                          /* magic */
    .long 0                                   /* architecture: 32-bit protected mode */
    .long mb2_header_end - mb2_header_start   /* header_length */
    .long -(0xE85250D6 + 0 + (mb2_header_end - mb2_header_start))  /* checksum */

    /* Termination tag (required by spec) */
    .align 8
    .short 0    /* type = 0 */
    .short 0    /* flags */
    .long  8    /* size */
mb2_header_end:

/* ---- PVH ELF Note: tells QEMU we're a PVH-compatible x86-64 kernel ---- */
.pushsection .note.Xen, "a", @note
    .align 4
    .long 4                 /* namesz */
    .long 4                 /* descsz */
    .long 18                /* type = XEN_ELFNOTE_PHYS32_ENTRY */
    .string "Xen"           /* name */
    .long _start            /* desc: 32-bit entry point */
.popsection

/* ---- 32-bit entry ---- */
.section .text
.code32
.global _start
_start:
    cli

    /* Save multiboot arguments to memory (survives mode switch) */
    movl %eax, saved_magic
    movl %ebx, saved_mb_info

    /* 1. Check Long Mode support via CPUID */
    movl $0x80000000, %eax
    cpuid
    cmpl $0x80000001, %eax
    jb   no_long_mode

    movl $0x80000001, %eax
    cpuid
    testl $(1 << 29), %edx        /* LM bit */
    jz   no_long_mode

    /* 2. Build 4-level page tables (identity-map first 1GB with 2MB huge pages) */
    /* Clear PML4, PDPT, PD (each 4096 bytes, 3 pages total) */
    movl $pml4, %edi
    xorl %eax, %eax
    movl $(3 * 1024), %ecx        /* 3 pages * 1024 dwords */
    cld
    rep stosl

    /* PML4[0] -> PDPT */
    movl $pdpt, %eax
    orl  $0x3, %eax               /* Present + Writable */
    movl %eax, pml4

    /* PDPT[0] -> PD */
    movl $pd, %eax
    orl  $0x3, %eax
    movl %eax, pdpt

    /* PD[0..511] -> 512 × 2MB huge pages = 1GB identity map */
    movl $pd, %edi
    movl $0x83, %eax              /* Present + Writable + Huge (bit 7) */
    movl $512, %ecx
1:
    movl %eax, (%edi)
    movl $0, 4(%edi)              /* Upper 32 bits = 0 */
    addl $0x200000, %eax          /* Next 2MB physical address */
    addl $8, %edi
    decl %ecx
    jnz  1b

    /* 3. Load CR3 (PML4 physical address) */
    movl $pml4, %eax
    movl %eax, %cr3

    /* 4. Enable PAE (CR4 bit 5) */
    movl %cr4, %eax
    orl  $(1 << 5), %eax
    movl %eax, %cr4

    /* 5. Set EFER.LME (MSR 0xC0000080 bit 8) */
    movl $0xC0000080, %ecx
    rdmsr
    orl  $(1 << 8), %eax
    wrmsr

    /* 6. Enable paging (CR0 bit 31) — now in compatibility mode */
    movl %cr0, %eax
    orl  $(1 << 31), %eax
    movl %eax, %cr0

    /* 7. Load 64-bit GDT (32-bit GDTR format: 2B limit + 4B base) */
    lgdt gdtr32

    /* 8. Far jump to 64-bit code — final transition to Long Mode */
    ljmp $0x08, $long_mode_start

no_long_mode:
    movl $0x0F4F0F4F, 0xB8000     /* "NO" */
    movl $0x0F4C0F4D, 0xB8004     /* "LM" */
    cli
    hlt
    jmp .

/* ---- 64-bit mode ---- */
.code64
long_mode_start:
    /* Clear all data segment registers */
    xorl %eax, %eax
    movl %eax, %ds
    movl %eax, %es
    movl %eax, %fs
    movl %eax, %gs
    movl %eax, %ss

    /* Set up 64-bit stack (16-byte aligned for System V ABI) */
    leaq stack_top(%rip), %rsp
    andq $-16, %rsp

    /* Clear BSS */
    leaq _bss_start(%rip), %rdi
    leaq _bss_end(%rip), %rcx
    subq %rdi, %rcx
    xorl %eax, %eax
    shrq $3, %rcx
    cld
    rep stosq

    /* Call kmain: rdi=magic, rsi=multiboot_info */
    movl saved_magic(%rip), %edi
    movl saved_mb_info(%rip), %esi
    call kmain

    /* kmain should not return */
    cli
    hlt
    jmp .

/* ---- BSS: stack space ---- */
.section .bss
.align 16
_bss_start:
    .space 32 * 1024             /* 32KB stack */
stack_top:
_bss_end:

/* ---- Page tables (page-aligned, in BSS for automatic zeroing) ---- */
.section .pagetables, "aw", @nobits
.align 4096
pml4:
    .space 4096
pdpt:
    .space 4096
pd:
    .space 4096

/* ---- Boot parameters + Temporary 64-bit GDT ---- */
.section .data
.align 8
saved_magic:   .long 0
saved_mb_info: .long 0

temp_gdt:
    .quad 0                      /* NULL descriptor */
    .quad 0x00209A0000000000     /* 64-bit code: P=1,DPL=0,S=1,Type=1010,L=1,D=0 */
    .quad 0x0000920000000000     /* 64-bit data: P=1,DPL=0,S=1,Type=0010 */

gdtr32:                          /* 32-bit GDTR (6 bytes) loaded in compatibility mode */
    .word . - temp_gdt - 1
    .long temp_gdt
