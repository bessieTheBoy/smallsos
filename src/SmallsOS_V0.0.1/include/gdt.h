#include <stdint.h>

enum GDT_ACCESS_BYTE {
    GDT_PRESENT = 0x80,
    GDT_RING_KERNEL = 0x00,
    GDT_RING_MIDDLE_LOW = 0x20,
    GDT_RING_MIDDLE_HIGH = 0x40,
    GDT_RING_USER = 0x60,
    GDT_TASK_STATE_SEGMENT = 0x00,
    GDT_DATA_OR_CODE_SEGMENT = 0x10,
    GDT_CODE_SEGMENT = 0x08,
    GDT_DATA_SEGMENT = 0x00,
    GDT_DATA_GROW_DOWN = 0x04,
    GDT_DATA_GROW_UP = 0x00,
    GDT_CODE_ONLY_RING_SET = 0x00,
    GDT_CODE_RINGS_BELOW = 0x04,
    GDT_CODE_READABLE = 0x02,
    GDT_DATA_WRITEABLE = 0x02,
    GDT_ACCESSED = 0x01
};

enum GDT_FLAGS {
    GDT_GRANULARITY = 0x08,
    GDT_16BIT_PROTECTED_SEGMENT = 0x00,
    GDT_32BIT_PROTECTED_SEGMENT = 0x04,
    GDT_64BIT_CODE_SEGMENT = 0x02
};

typedef struct
{
    uint16_t size;
    uint32_t offset;
} __attribute__((packed)) GDTR;
GDTR g_GDTR;

uint64_t* gdt;

typedef struct {
    uint64_t limit;
    uint64_t base;
    uint64_t accessByte;
    uint64_t flags;
} SegmentDescriptor;

uint64_t GDTEntryToInt(SegmentDescriptor descriptor);

extern void loadGDT(uint16_t size, uint32_t offset);
extern void reloadSegments();

void GDT_Load();