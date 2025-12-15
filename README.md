# KFS 1

## Structuration du projet

- Le dossier `kernel` contient les fichiers propres au kernel. Exemple : driver, écriture sur le terminal etc.
- Le dossier `libk` contient un début de librairie C. Les implémentations ne sont pas standard pour la plupart.
- Le Makefile principal archive la libk en `libk` ("libkernel"), puis ensuite le kernel en `kernel.bin`
- Ensuite, il archive sous forme d'iso le kernel, avec le fichier grub pour loader le kernel.
- Pour terminer, qemu est utilisé afin d'émuler notre kernel.

```bash
.
├── grub.cfg
├── kernel
│   ├── include
│   │   ├── tty.h
│   │   └── vga.h
│   ├── kernel
│   │   ├── assembly
│   │   │   └── boot.asm
│   │   └── kernel.c
│   ├── linker.ld
│   └── tty
│       └── tty.c
├── libk
│   ├── include
│   │   ├── itoa.h
│   │   ├── stdio.h
│   │   ├── string.h
│   │   └── fs.h
│   ├── itoa
│   │   ├── itoa.c
│   │   ├── uitoa_base.c
│   │   └── uitoa.c
│   ├── Makefile
│   ├── stdio
│   │   ├── printf.c
│   │   ├── putchar.c
│   │   └── puts.c
│   ├── string
│   │   ├── bzero.c
│   │   ├── memchr.c
│   │   ├── memcpm.c
│   │   ├── memcpy.c
│   │   ├── memmove.c
│   │   ├── memset.c
│   │   ├── strchr.c
│   │   ├── strcmp.c
│   │   ├── strcpy.c
│   │   └── strlen.c
│   └── unistd
│       └── write.c
├── Makefile
└── README.md
```

## Directives NASM d'initialisation de données

| Directive | Description | Taille | Exemple |
|-----------|-------------|--------|---------|
| `db` | Define Byte - Définit un ou plusieurs octets | 1 octet | `db 0x42` ou `db 'A'` |
| `dw` | Define Word - Définit un ou plusieurs mots | 2 octets | `dw 0x1234` |
| `dd` | Define Double word - Définit un ou plusieurs doubles mots | 4 octets | `dd 0x12345678` |
| `dq` | Define Quad word - Définit un ou plusieurs quadruples mots | 8 octets | `dq 0x123456789ABCDEF0` |
| `dt` | Define Ten bytes - Définit une valeur de 10 octets (80 bits) | 10 octets | `dt 3.141592653589793` |
| `do` | Define Octa word - Définit une valeur de 16 octets (128 bits) | 16 octets | `do 0x12345678_9ABCDEF0_12345678_9ABCDEF0` |
| `dy` | Define 32 bytes - Définit une valeur de 32 octets (256 bits) | 32 octets | `dy 0` |
| `dz` | Define 64 bytes - Définit une valeur de 64 octets (512 bits) | 64 octets | `dz 0` |
| `resb` | Reserve Bytes - Réserve des octets non initialisés | 1 octet × N | `resb 100` |
| `resw` | Reserve Words - Réserve des mots non initialisés | 2 octets × N | `resw 50` |
| `resd` | Reserve Double words - Réserve des doubles mots non initialisés | 4 octets × N | `resd 25` |
| `resq` | Reserve Quad words - Réserve des quadruples mots non initialisés | 8 octets × N | `resq 10` |
| `rest` | Reserve Ten bytes - Réserve des blocs de 10 octets non initialisés | 10 octets × N | `rest 5` |
| `reso` | Reserve Octa words - Réserve des blocs de 16 octets non initialisés | 16 octets × N | `reso 4` |
| `resy` | Reserve 32 bytes - Réserve des blocs de 32 octets non initialisés | 32 octets × N | `resy 2` |
| `resz` | Reserve 64 bytes - Réserve des blocs de 64 octets non initialisés | 64 octets × N | `resz 1` |
| `equ` | Equate - Définit une constante symbolique (pas de donnée en mémoire) | - | `SIZE equ 1024` |
| `times` | Répète une directive N fois | Variable | `times 10 db 0xFF` |

## Notes importantes

- Les directives `db`, `dw`, `dd`, `dq`, `dt`, `do`, `dy`, `dz` **initialisent** les données
- Les directives `resb`, `resw`, `resd`, `resq`, `rest`, `reso`, `resy`, `resz` **réservent** de l'espace non initialisé (section `.bss`)
- `equ` ne crée pas de données en mémoire, c'est uniquement une constante pour l'assembleur
- `times` peut être utilisé avec n'importe quelle directive d'initialisation pour répéter des valeurs
