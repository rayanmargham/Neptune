#include "idt.h"
#include "memfunc.h"
#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"
#include "expections.h"
extern struct flanterm_context *ft_ctx;
extern void kflantprint(struct flanterm_context *ft_ctx, char msg[], size_t count, uint32_t color, char from_who[], size_t length_for_that, bool next_line);
extern void load_idt(struct idtptr *idtptr);
static struct idtentry epic_gamer_table[256];
void (*idt_handlers[256])(struct interrupt_frame* frame);
struct idtptr idtptr = {sizeof(epic_gamer_table) - 1, (uintptr_t)&epic_gamer_table}; 

void register_interrupt(int n, void *handler, uint8_t type_attrib)
{
    epic_gamer_table[n].ist = 0;
    epic_gamer_table[n].type_attributes = type_attrib;
    epic_gamer_table[n].selector = 0x08; // Kernel Code Segment
    
    uintptr_t base = (uintptr_t)handler;
    epic_gamer_table[n].offset1 = base & 0xffff;
    epic_gamer_table[n].offset2 = base >> 16;
    epic_gamer_table[n].offset3 = base >> 32;
}

void *isr0();
void *isr1();
void *isr2();
void *isr3();
void *isr4();
void *isr5();
void *isr6();
void *isr7();
void *isr8();
void *isr9();
void *isr10();
void *isr11();
void *isr12();
void *isr13();
void *isr14();
void *isr15();
void *isr16();
void *isr17();
void *isr18();
void *isr19();
void *isr20();
void *isr21();
void *isr22();
void *isr23();
void *isr24();
void *isr25();
void *isr26();
void *isr27();
void *isr28();
void *isr29();
void *isr30();
void *isr31();
void *isr32();
void *isr33();
void *isr34();
void *isr35();
void *isr36();
void *isr37();
void *isr38();
void *isr39();
void *isr40();
void *isr41();
void *isr42();
void *isr43();
void *isr44();
void *isr45();
void *isr46();
void *isr47();
void *isr48();
void *isr49();
void *isr50();
void *isr51();
void *isr52();
void *isr53();
void *isr54();
void *isr55();
void *isr56();
void *isr57();
void *isr58();
void *isr59();
void *isr60();
void *isr61();
void *isr62();
void *isr63();
void *isr64();
void *isr65();
void *isr66();
void *isr67();
void *isr68();
void *isr69();
void *isr70();
void *isr71();
void *isr72();
void *isr73();
void *isr74();
void *isr75();
void *isr76();
void *isr77();
void *isr78();
void *isr79();
void *isr80();
void *isr81();
void *isr82();
void *isr83();
void *isr84();
void *isr85();
void *isr86();
void *isr87();
void *isr88();
void *isr89();
void *isr90();
void *isr91();
void *isr92();
void *isr93();
void *isr94();
void *isr95();
void *isr96();
void *isr97();
void *isr98();
void *isr99();
void *isr100();
void *isr101();
void *isr102();
void *isr103();
void *isr104();
void *isr105();
void *isr106();
void *isr107();
void *isr108();
void *isr109();
void *isr110();
void *isr111();
void *isr112();
void *isr113();
void *isr114();
void *isr115();
void *isr116();
void *isr117();
void *isr118();
void *isr119();
void *isr120();
void *isr121();
void *isr122();
void *isr123();
void *isr124();
void *isr125();
void *isr126();
void *isr127();
void *isr128();
void *isr129();
void *isr130();
void *isr131();
void *isr132();
void *isr133();
void *isr134();
void *isr135();
void *isr136();
void *isr137();
void *isr138();
void *isr139();
void *isr140();
void *isr141();
void *isr142();
void *isr143();
void *isr144();
void *isr145();
void *isr146();
void *isr147();
void *isr148();
void *isr149();
void *isr150();
void *isr151();
void *isr152();
void *isr153();
void *isr154();
void *isr155();
void *isr156();
void *isr157();
void *isr158();
void *isr159();
void *isr160();
void *isr161();
void *isr162();
void *isr163();
void *isr164();
void *isr165();
void *isr166();
void *isr167();
void *isr168();
void *isr169();
void *isr170();
void *isr171();
void *isr172();
void *isr173();
void *isr174();
void *isr175();
void *isr176();
void *isr177();
void *isr178();
void *isr179();
void *isr180();
void *isr181();
void *isr182();
void *isr183();
void *isr184();
void *isr185();
void *isr186();
void *isr187();
void *isr188();
void *isr189();
void *isr190();
void *isr191();
void *isr192();
void *isr193();
void *isr194();
void *isr195();
void *isr196();
void *isr197();
void *isr198();
void *isr199();
void *isr200();
void *isr201();
void *isr202();
void *isr203();
void *isr204();
void *isr205();
void *isr206();
void *isr207();
void *isr208();
void *isr209();
void *isr210();
void *isr211();
void *isr212();
void *isr213();
void *isr214();
void *isr215();
void *isr216();
void *isr217();
void *isr218();
void *isr219();
void *isr220();
void *isr221();
void *isr222();
void *isr223();
void *isr224();
void *isr225();
void *isr226();
void *isr227();
void *isr228();
void *isr229();
void *isr230();
void *isr231();
void *isr232();
void *isr233();
void *isr234();
void *isr235();
void *isr236();
void *isr237();
void *isr238();
void *isr239();
void *isr240();
void *isr241();
void *isr242();
void *isr243();
void *isr244();
void *isr245();
void *isr246();
void *isr247();
void *isr248();
void *isr249();
void *isr250();
void *isr251();
void *isr252();
void *isr253();
void *isr254();
void *isr255();


void init_idt()
{
    kflantprint(ft_ctx, "Registering Interrupts into IDT Table...", 41, 0xFFA500, "IDT", 4, true);
    __asm__ volatile ("cli");
    register_interrupt(0, isr0, default_type_attribute_interrupt);
    register_interrupt(1, isr1, default_type_attribute_interrupt);
    register_interrupt(2, isr2, default_type_attribute_interrupt);
    register_interrupt(3, isr3, default_type_attribute_interrupt);
    register_interrupt(4, isr4, default_type_attribute_interrupt);
    register_interrupt(5, isr5, default_type_attribute_interrupt);
    register_interrupt(6, isr6, default_type_attribute_interrupt);
    register_interrupt(7, isr7, default_type_attribute_interrupt);
    register_interrupt(8, isr8, default_type_attribute_interrupt);
    register_interrupt(9, isr9, default_type_attribute_interrupt);
    register_interrupt(10, isr10, default_type_attribute_interrupt);
    register_interrupt(11, isr11, default_type_attribute_interrupt);
    register_interrupt(12, isr12, default_type_attribute_interrupt);
    register_interrupt(13, isr13, default_type_attribute_interrupt);
    register_interrupt(14, isr14, default_type_attribute_interrupt);
    register_interrupt(15, isr15, default_type_attribute_interrupt);
    register_interrupt(16, isr16, default_type_attribute_interrupt);
    register_interrupt(17, isr17, default_type_attribute_interrupt);
    register_interrupt(18, isr18, default_type_attribute_interrupt);
    register_interrupt(19, isr19, default_type_attribute_interrupt);
    register_interrupt(20, isr20, default_type_attribute_interrupt);
    register_interrupt(21, isr21, default_type_attribute_interrupt);
    register_interrupt(22, isr22, default_type_attribute_interrupt);
    register_interrupt(23, isr23, default_type_attribute_interrupt);
    register_interrupt(24, isr24, default_type_attribute_interrupt);
    register_interrupt(25, isr25, default_type_attribute_interrupt);
    register_interrupt(26, isr26, default_type_attribute_interrupt);
    register_interrupt(27, isr27, default_type_attribute_interrupt);
    register_interrupt(28, isr28, default_type_attribute_interrupt);
    register_interrupt(29, isr29, default_type_attribute_interrupt);
    register_interrupt(30, isr30, default_type_attribute_interrupt);
    register_interrupt(31, isr31, default_type_attribute_interrupt);
    register_interrupt(32, isr32, default_type_attribute_interrupt);
    register_interrupt(33, isr33, default_type_attribute_interrupt);
    register_interrupt(34, isr34, default_type_attribute_interrupt);
    register_interrupt(35, isr35, default_type_attribute_interrupt);
    register_interrupt(36, isr36, default_type_attribute_interrupt);
    register_interrupt(37, isr37, default_type_attribute_interrupt);
    register_interrupt(38, isr38, default_type_attribute_interrupt);
    register_interrupt(39, isr39, default_type_attribute_interrupt);
    register_interrupt(40, isr40, default_type_attribute_interrupt);
    register_interrupt(41, isr41, default_type_attribute_interrupt);
    register_interrupt(42, isr42, default_type_attribute_interrupt);
    register_interrupt(43, isr43, default_type_attribute_interrupt);
    register_interrupt(44, isr44, default_type_attribute_interrupt);
    register_interrupt(45, isr45, default_type_attribute_interrupt);
    register_interrupt(46, isr46, default_type_attribute_interrupt);
    register_interrupt(47, isr47, default_type_attribute_interrupt);
    register_interrupt(48, isr48, default_type_attribute_interrupt);
    register_interrupt(49, isr49, default_type_attribute_interrupt);
    register_interrupt(50, isr50, default_type_attribute_interrupt);
    register_interrupt(51, isr51, default_type_attribute_interrupt);
    register_interrupt(52, isr52, default_type_attribute_interrupt);
    register_interrupt(53, isr53, default_type_attribute_interrupt);
    register_interrupt(54, isr54, default_type_attribute_interrupt);
    register_interrupt(55, isr55, default_type_attribute_interrupt);
    register_interrupt(56, isr56, default_type_attribute_interrupt);
    register_interrupt(57, isr57, default_type_attribute_interrupt);
    register_interrupt(58, isr58, default_type_attribute_interrupt);
    register_interrupt(59, isr59, default_type_attribute_interrupt);
    register_interrupt(60, isr60, default_type_attribute_interrupt);
    register_interrupt(61, isr61, default_type_attribute_interrupt);
    register_interrupt(62, isr62, default_type_attribute_interrupt);
    register_interrupt(63, isr63, default_type_attribute_interrupt);
    register_interrupt(64, isr64, default_type_attribute_interrupt);
    register_interrupt(65, isr65, default_type_attribute_interrupt);
    register_interrupt(66, isr66, default_type_attribute_interrupt);
    register_interrupt(67, isr67, default_type_attribute_interrupt);
    register_interrupt(68, isr68, default_type_attribute_interrupt);
    register_interrupt(69, isr69, default_type_attribute_interrupt);
    register_interrupt(70, isr70, default_type_attribute_interrupt);
    register_interrupt(71, isr71, default_type_attribute_interrupt);
    register_interrupt(72, isr72, default_type_attribute_interrupt);
    register_interrupt(73, isr73, default_type_attribute_interrupt);
    register_interrupt(74, isr74, default_type_attribute_interrupt);
    register_interrupt(75, isr75, default_type_attribute_interrupt);
    register_interrupt(76, isr76, default_type_attribute_interrupt);
    register_interrupt(77, isr77, default_type_attribute_interrupt);
    register_interrupt(78, isr78, default_type_attribute_interrupt);
    register_interrupt(79, isr79, default_type_attribute_interrupt);
    register_interrupt(80, isr80, default_type_attribute_interrupt);
    register_interrupt(81, isr81, default_type_attribute_interrupt);
    register_interrupt(82, isr82, default_type_attribute_interrupt);
    register_interrupt(83, isr83, default_type_attribute_interrupt);
    register_interrupt(84, isr84, default_type_attribute_interrupt);
    register_interrupt(85, isr85, default_type_attribute_interrupt);
    register_interrupt(86, isr86, default_type_attribute_interrupt);
    register_interrupt(87, isr87, default_type_attribute_interrupt);
    register_interrupt(88, isr88, default_type_attribute_interrupt);
    register_interrupt(89, isr89, default_type_attribute_interrupt);
    register_interrupt(90, isr90, default_type_attribute_interrupt);
    register_interrupt(91, isr91, default_type_attribute_interrupt);
    register_interrupt(92, isr92, default_type_attribute_interrupt);
    register_interrupt(93, isr93, default_type_attribute_interrupt);
    register_interrupt(94, isr94, default_type_attribute_interrupt);
    register_interrupt(95, isr95, default_type_attribute_interrupt);
    register_interrupt(96, isr96, default_type_attribute_interrupt);
    register_interrupt(97, isr97, default_type_attribute_interrupt);
    register_interrupt(98, isr98, default_type_attribute_interrupt);
    register_interrupt(99, isr99, default_type_attribute_interrupt);
    register_interrupt(100, isr100, default_type_attribute_interrupt);
    register_interrupt(101, isr101, default_type_attribute_interrupt);
    register_interrupt(102, isr102, default_type_attribute_interrupt);
    register_interrupt(103, isr103, default_type_attribute_interrupt);
    register_interrupt(104, isr104, default_type_attribute_interrupt);
    register_interrupt(105, isr105, default_type_attribute_interrupt);
    register_interrupt(106, isr106, default_type_attribute_interrupt);
    register_interrupt(107, isr107, default_type_attribute_interrupt);
    register_interrupt(108, isr108, default_type_attribute_interrupt);
    register_interrupt(109, isr109, default_type_attribute_interrupt);
    register_interrupt(110, isr110, default_type_attribute_interrupt);
    register_interrupt(111, isr111, default_type_attribute_interrupt);
    register_interrupt(112, isr112, default_type_attribute_interrupt);
    register_interrupt(113, isr113, default_type_attribute_interrupt);
    register_interrupt(114, isr114, default_type_attribute_interrupt);
    register_interrupt(115, isr115, default_type_attribute_interrupt);
    register_interrupt(116, isr116, default_type_attribute_interrupt);
    register_interrupt(117, isr117, default_type_attribute_interrupt);
    register_interrupt(118, isr118, default_type_attribute_interrupt);
    register_interrupt(119, isr119, default_type_attribute_interrupt);
    register_interrupt(120, isr120, default_type_attribute_interrupt);
    register_interrupt(121, isr121, default_type_attribute_interrupt);
    register_interrupt(122, isr122, default_type_attribute_interrupt);
    register_interrupt(123, isr123, default_type_attribute_interrupt);
    register_interrupt(124, isr124, default_type_attribute_interrupt);
    register_interrupt(125, isr125, default_type_attribute_interrupt);
    register_interrupt(126, isr126, default_type_attribute_interrupt);
    register_interrupt(127, isr127, default_type_attribute_interrupt);
    register_interrupt(128, isr128, default_type_attribute_interrupt);
    register_interrupt(129, isr129, default_type_attribute_interrupt);
    register_interrupt(130, isr130, default_type_attribute_interrupt);
    register_interrupt(131, isr131, default_type_attribute_interrupt);
    register_interrupt(132, isr132, default_type_attribute_interrupt);
    register_interrupt(133, isr133, default_type_attribute_interrupt);
    register_interrupt(134, isr134, default_type_attribute_interrupt);
    register_interrupt(135, isr135, default_type_attribute_interrupt);
    register_interrupt(136, isr136, default_type_attribute_interrupt);
    register_interrupt(137, isr137, default_type_attribute_interrupt);
    register_interrupt(138, isr138, default_type_attribute_interrupt);
    register_interrupt(139, isr139, default_type_attribute_interrupt);
    register_interrupt(140, isr140, default_type_attribute_interrupt);
    register_interrupt(141, isr141, default_type_attribute_interrupt);
    register_interrupt(142, isr142, default_type_attribute_interrupt);
    register_interrupt(143, isr143, default_type_attribute_interrupt);
    register_interrupt(144, isr144, default_type_attribute_interrupt);
    register_interrupt(145, isr145, default_type_attribute_interrupt);
    register_interrupt(146, isr146, default_type_attribute_interrupt);
    register_interrupt(147, isr147, default_type_attribute_interrupt);
    register_interrupt(148, isr148, default_type_attribute_interrupt);
    register_interrupt(149, isr149, default_type_attribute_interrupt);
    register_interrupt(150, isr150, default_type_attribute_interrupt);
    register_interrupt(151, isr151, default_type_attribute_interrupt);
    register_interrupt(152, isr152, default_type_attribute_interrupt);
    register_interrupt(153, isr153, default_type_attribute_interrupt);
    register_interrupt(154, isr154, default_type_attribute_interrupt);
    register_interrupt(155, isr155, default_type_attribute_interrupt);
    register_interrupt(156, isr156, default_type_attribute_interrupt);
    register_interrupt(157, isr157, default_type_attribute_interrupt);
    register_interrupt(158, isr158, default_type_attribute_interrupt);
    register_interrupt(159, isr159, default_type_attribute_interrupt);
    register_interrupt(160, isr160, default_type_attribute_interrupt);
    register_interrupt(161, isr161, default_type_attribute_interrupt);
    register_interrupt(162, isr162, default_type_attribute_interrupt);
    register_interrupt(163, isr163, default_type_attribute_interrupt);
    register_interrupt(164, isr164, default_type_attribute_interrupt);
    register_interrupt(165, isr165, default_type_attribute_interrupt);
    register_interrupt(166, isr166, default_type_attribute_interrupt);
    register_interrupt(167, isr167, default_type_attribute_interrupt);
    register_interrupt(168, isr168, default_type_attribute_interrupt);
    register_interrupt(169, isr169, default_type_attribute_interrupt);
    register_interrupt(170, isr170, default_type_attribute_interrupt);
    register_interrupt(171, isr171, default_type_attribute_interrupt);
    register_interrupt(172, isr172, default_type_attribute_interrupt);
    register_interrupt(173, isr173, default_type_attribute_interrupt);
    register_interrupt(174, isr174, default_type_attribute_interrupt);
    register_interrupt(175, isr175, default_type_attribute_interrupt);
    register_interrupt(176, isr176, default_type_attribute_interrupt);
    register_interrupt(177, isr177, default_type_attribute_interrupt);
    register_interrupt(178, isr178, default_type_attribute_interrupt);
    register_interrupt(179, isr179, default_type_attribute_interrupt);
    register_interrupt(180, isr180, default_type_attribute_interrupt);
    register_interrupt(181, isr181, default_type_attribute_interrupt);
    register_interrupt(182, isr182, default_type_attribute_interrupt);
    register_interrupt(183, isr183, default_type_attribute_interrupt);
    register_interrupt(184, isr184, default_type_attribute_interrupt);
    register_interrupt(185, isr185, default_type_attribute_interrupt);
    register_interrupt(186, isr186, default_type_attribute_interrupt);
    register_interrupt(187, isr187, default_type_attribute_interrupt);
    register_interrupt(188, isr188, default_type_attribute_interrupt);
    register_interrupt(189, isr189, default_type_attribute_interrupt);
    register_interrupt(190, isr190, default_type_attribute_interrupt);
    register_interrupt(191, isr191, default_type_attribute_interrupt);
    register_interrupt(192, isr192, default_type_attribute_interrupt);
    register_interrupt(193, isr193, default_type_attribute_interrupt);
    register_interrupt(194, isr194, default_type_attribute_interrupt);
    register_interrupt(195, isr195, default_type_attribute_interrupt);
    register_interrupt(196, isr196, default_type_attribute_interrupt);
    register_interrupt(197, isr197, default_type_attribute_interrupt);
    register_interrupt(198, isr198, default_type_attribute_interrupt);
    register_interrupt(199, isr199, default_type_attribute_interrupt);
    register_interrupt(200, isr200, default_type_attribute_interrupt);
    register_interrupt(201, isr201, default_type_attribute_interrupt);
    register_interrupt(202, isr202, default_type_attribute_interrupt);
    register_interrupt(203, isr203, default_type_attribute_interrupt);
    register_interrupt(204, isr204, default_type_attribute_interrupt);
    register_interrupt(205, isr205, default_type_attribute_interrupt);
    register_interrupt(206, isr206, default_type_attribute_interrupt);
    register_interrupt(207, isr207, default_type_attribute_interrupt);
    register_interrupt(208, isr208, default_type_attribute_interrupt);
    register_interrupt(209, isr209, default_type_attribute_interrupt);
    register_interrupt(210, isr210, default_type_attribute_interrupt);
    register_interrupt(211, isr211, default_type_attribute_interrupt);
    register_interrupt(212, isr212, default_type_attribute_interrupt);
    register_interrupt(213, isr213, default_type_attribute_interrupt);
    register_interrupt(214, isr214, default_type_attribute_interrupt);
    register_interrupt(215, isr215, default_type_attribute_interrupt);
    register_interrupt(216, isr216, default_type_attribute_interrupt);
    register_interrupt(217, isr217, default_type_attribute_interrupt);
    register_interrupt(218, isr218, default_type_attribute_interrupt);
    register_interrupt(219, isr219, default_type_attribute_interrupt);
    register_interrupt(220, isr220, default_type_attribute_interrupt);
    register_interrupt(221, isr221, default_type_attribute_interrupt);
    register_interrupt(222, isr222, default_type_attribute_interrupt);
    register_interrupt(223, isr223, default_type_attribute_interrupt);
    register_interrupt(224, isr224, default_type_attribute_interrupt);
    register_interrupt(225, isr225, default_type_attribute_interrupt);
    register_interrupt(226, isr226, default_type_attribute_interrupt);
    register_interrupt(227, isr227, default_type_attribute_interrupt);
    register_interrupt(228, isr228, default_type_attribute_interrupt);
    register_interrupt(229, isr229, default_type_attribute_interrupt);
    register_interrupt(230, isr230, default_type_attribute_interrupt);
    register_interrupt(231, isr231, default_type_attribute_interrupt);
    register_interrupt(232, isr232, default_type_attribute_interrupt);
    register_interrupt(233, isr233, default_type_attribute_interrupt);
    register_interrupt(234, isr234, default_type_attribute_interrupt);
    register_interrupt(235, isr235, default_type_attribute_interrupt);
    register_interrupt(236, isr236, default_type_attribute_interrupt);
    register_interrupt(237, isr237, default_type_attribute_interrupt);
    register_interrupt(238, isr238, default_type_attribute_interrupt);
    register_interrupt(239, isr239, default_type_attribute_interrupt);
    register_interrupt(240, isr240, default_type_attribute_interrupt);
    register_interrupt(241, isr241, default_type_attribute_interrupt);
    register_interrupt(242, isr242, default_type_attribute_interrupt);
    register_interrupt(243, isr243, default_type_attribute_interrupt);
    register_interrupt(244, isr244, default_type_attribute_interrupt);
    register_interrupt(245, isr245, default_type_attribute_interrupt);
    register_interrupt(246, isr246, default_type_attribute_interrupt);
    register_interrupt(247, isr247, default_type_attribute_interrupt);
    register_interrupt(248, isr248, default_type_attribute_interrupt);
    register_interrupt(249, isr249, default_type_attribute_interrupt);
    register_interrupt(250, isr250, default_type_attribute_interrupt);
    register_interrupt(251, isr251, default_type_attribute_interrupt);
    register_interrupt(252, isr252, default_type_attribute_interrupt);
    register_interrupt(253, isr253, default_type_attribute_interrupt);
    register_interrupt(254, isr254, default_type_attribute_interrupt);
    register_interrupt(255, isr255, default_type_attribute_interrupt);
    register_expections_isrs();
    kflantprint(ft_ctx, "Loading IDT Table NOW...", 25, 0xFFA500, "IDT", 4, true);
    load_idt(&idtptr);

    
}
void RegisterInterruptHandler(unsigned char interrupt, void(*handler)(struct interrupt_frame* frame))
{
		idt_handlers[interrupt] = handler;
}