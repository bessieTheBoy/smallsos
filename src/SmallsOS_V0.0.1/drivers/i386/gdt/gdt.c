#include <gdt.h>

uint64_t GDTEntryToInt(SegmentDescriptor descriptor){
    uint64_t rv = 0;
    rv = rv | ((descriptor.limit & 0xFFFF) << 0);
    rv = rv | ((descriptor.base & 0xFFFFF) << 16);
    rv = rv | ((descriptor.accessByte & 0xFF) << 40);
    rv = rv | ((descriptor.limit & 0xF0000) << 48);
    rv = rv | ((descriptor.flags & 0xF) << 52);
    rv = rv | ((descriptor.base & 0xFF0000) << 56);
    return rv;
}


void GDT_Load(){
    gdt[0] = 0;
    SegmentDescriptor codeDescriptor;
    codeDescriptor.base = 0;
    codeDescriptor.limit = 0xFFFFF;
    codeDescriptor.accessByte = GDT_PRESENT | GDT_RING_KERNEL | GDT_DATA_OR_CODE_SEGMENT | GDT_CODE_SEGMENT | GDT_CODE_ONLY_RING_SET | GDT_CODE_READABLE | GDT_ACCESSED;
    codeDescriptor.flags = GDT_GRANULARITY | GDT_32BIT_PROTECTED_SEGMENT;
    SegmentDescriptor dataDescriptor;
    dataDescriptor.base = 0;
    dataDescriptor.limit = 0xFFFFF;
    dataDescriptor.accessByte = GDT_PRESENT | GDT_RING_KERNEL | GDT_DATA_OR_CODE_SEGMENT | GDT_DATA_SEGMENT | GDT_DATA_GROW_UP | GDT_DATA_WRITEABLE | GDT_ACCESSED;
    dataDescriptor.flags = 0xC;   //GDT_GRANULARITY | GDT_32BIT_PROTECTED_SEGMENT;
    gdt[1] = GDTEntryToInt(codeDescriptor);
    gdt[2] = GDTEntryToInt(dataDescriptor);
    g_GDTR.offset = (uint32_t)gdt;
    g_GDTR.size = sizeof(gdt) - 1;
    loadGDT(g_GDTR.size, g_GDTR.offset);
    reloadSegments();
}