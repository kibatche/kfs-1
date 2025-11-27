BITS 32
extern kernel_main
;Constantes pour le chargement multiboot avec Grub
; Aligner les modules charges sur la taille des pages
%define ALIGN 1<<0
; Permet d'avoir la structure de la memoire
%define MEMINFO 1<<1
; Champs FLAGS pour le multiboot
%define FLAGS ALIGN | MEMINFO
; Nombre magique qui permet au chargeur d'armorcage de trouver l'en-tete
%define MAGIC 0x1BADB002
; somme d everification des donnees ci-dessus, pour prouver que nous sommes en multiboot
%define CHECKSUM -(MAGIC + FLAGS)

; Declare un en-tete multiboot qui marque le programme comme etant un kernel
; Ce sont des valeur magiques qui sont documentees comme etant standard pour le multiboot
; Le chargeur d'arnorcage va chercher cette signature dans les premiers 8Ko du fichier du kernel alignes sur une limite de 32 bits.
; Cette signature est dans sa propre section de telle facon a ce que le header soit dans les premiers 8Ko du fichier du kernel.
; Le standard ne determine pas de taille pour le pointeur sur la stack (esp en 32bits)
; et c'est donc au kernel de definir lui meme la stack. Cela laisse un peu de place pour creer une petite stack en crean un symbole en bas de la stack.
; 16384 bytes lui sont alloues, avec pour terminer la creation d'un symbole en haut de la stack.
; La stack grandit par en bas (lorsqu'on alloue de la memoire sur le stack, on "descend" dans la memoire (ie sub esp, 0x10)). Etant dans la section .bss, elle peut etre marque com
; me notbit, ce qui a pour consequence qu'elle ne prend pas de place dans le fichier du kernel. La pile doit etre alginee sur 16 octets en x86 selon le standard System V abi.
; Le compileur assume que la pile est correctement alignee, sans quoi un comportement indefini peut survenir.

section .multiboot
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM

section .bss
align 16
stack_bottom:
; on reserve 16384 octets pour la stack. Le tuto est avec la syntaxe (affreuse) AT&T et utilise GAS. Nous uitlisons NASM.
	resb 16384

stack_top:


; Le script de link specifie _start comme point de depart pour l'execution du kernel
; et le bootloader va aller a cette position lorsque le kernel sera charge.
section .text
global _start:function
_start:
	mov esp, stack_top
	call kernel_main
	cli
sleep:  hlt
	jmp sleep
end:

%define _start_size (end - _start)
