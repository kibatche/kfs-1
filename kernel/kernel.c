#include <tty.h>
#include <stdio.h>

extern uint16_t *terminal_buff;

void bonus_printf(void)
{
    int res = printf("%s %d %s\n", "Et le cordeau des trompettes marines", 12, "Un AUTRE TEST");
    printf("Nombre de caracteres ecrits : %d\n", res);
    // printf("%d %d %d\n", 42, 55, 68);
    // printf("Ceci est le nombre -2147483648 en int : %d\n", -2147483648);
    // printf("Ceci est le nombre 2147483647 en int : %d\n", 2147483647);
    // printf("Ceci est le nombre 4294967295 en unsigned int : %u\n", 4294967295);
    // printf("Ceci est le nombre 4294967295 en HEX : %X\n", 4294967295);
    // printf("Ceci est le nombre 4294967295 en hex : %x\n", 4294967295);
    // printf("Ceci est une chaine de caracteres : %s\n", "abcdefghijklmnopqrstuvwxy0123456789,;!?./%*");
    // printf("Ceci est une chaine de caracteres nulle: %s\n", NULL);
    // printf("Ceci est un caractere : %c\n", 'A');
}

void print_welcome_msg(void)
{
    terminal_set_color(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
    printf("%s %d\n","26225352196173432615458667836903", 42);
    printf("%s %d\n","78553247483422402724743861600851", 42);
    printf("%s %d\n","61214689052339195365782119790228", 42);
    printf("%s %d\n","36235414216805717866444730325626", 42);
    printf("%s %d\n","11477881243063881820053925436830", 42);
    printf("%s %d\n","44771614195420343574544247721017", 42);
    printf("%s %d\n","51115003559324004359699149623647", 42);
    printf("%s %d\n","54956527725592719088750403041854", 42);
    printf("%s %d\n","44253380892937762130478813226047", 42);
    printf("%s %d\n","70345770544967293917510422463754", 42);
    printf("%s %d\n","11782068815683599379545084761486", 42);
    printf("%s %d\n","58260551781312535408674459456760", 42);
    printf("%s %d\n","83590985916825190717601959908828", 42);
    printf("%s %d\n","68114184551879109114780680671994", 42);
    printf("%s %d\n","18259229013886069629728361511259", 42);
    printf("%s %d\n","41714436712869995397701525271501", 42);
    printf("%s %d\n","06133360017880913435048062596827", 42);
    printf("%s %d\n","20992820835829479376409182513344", 42);
    printf("%s %d\n","43189255346788755032831553865382", 42);
    printf("%s %d\n","59061563429973866417504407709071", 42);
    printf("%s %d\n","17252972728042593073833691695511", 42);
    printf("%s %d\n","74252449590151704533658675263795", 42);
    printf("%s %d\n","82828292505246370907320724139524", 42);
    printf("%s %d\n","57476833191969459123477356804161", 42);
    printf("%s %d\n","60575482899668808355373872027231", 42);
    printf("%s %d\n","00010191707233132643899469982495", 42);
    printf("%s %d\n","78730569900004822283670107384322", 42);
    printf("%s %d\n","53957197478604073171018785154556", 42);
    printf("%s %d\n","02073688363977350359047945248349", 42);
    printf("%s %d\n","64483558292439235062764880221630", 42);
    terminal_set_color(vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
}

void kernel_main(void)
{
    terminal_init();
    print_welcome_msg();
}
