#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <hal.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

typedef enum {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
} vgaColor;

typedef struct{
    int Foreground;
    int Background;
    uint8_t ColorValue;
} Color;

typedef struct
{
    Color color;
    char character;
    uint16_t printableCharacter;
} Character;


Color generateColor(vgaColor fg, vgaColor bg){
    Color returnValue;
    returnValue.Foreground = fg;
    returnValue.Background = bg;
    returnValue.ColorValue = (fg | bg << 4);
    return returnValue;
}

Character generateCharacter(Color color, char character){
    Character returnValue;
    returnValue.character = character;
    returnValue.color = color;
    returnValue.printableCharacter = (character | color.ColorValue << 8);
    return returnValue;
}

uint16_t* buffer = (uint16_t*)0xB8000;
uint8_t consoleX = 0;
uint8_t consoleY = 0;

void printChar(Character character){
    buffer[(consoleY * VGA_WIDTH + consoleX)] = character.printableCharacter;
}

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void kprint(char* string, Color color){
    for (int i = 0; i < strlen(string); i++){
        if (string[i] == '\n'){
            consoleY++;
            consoleX = 0;
        } else {
            if (consoleX < VGA_WIDTH){
                printChar(generateCharacter(color, string[i]));
                consoleX++;
            } else {
                printChar(generateCharacter(color, string[i]));
                consoleY++;
                consoleX = 0;
            }
        }
        
    }
}

void cls(){
    Character character = generateCharacter(generateColor(VGA_COLOR_BLACK, VGA_COLOR_RED), ' ');
    for (int x = 0; x < VGA_WIDTH; x++){
        for (int y = 0; y < VGA_HEIGHT; y++){
            buffer[(y * VGA_WIDTH + x)] = character.printableCharacter;
        }
    }
    consoleX = 0;
    consoleY = 0;
}


void kernel_main(){
    cls();
    kprint("GDT LOADED!!!!!", generateColor(VGA_COLOR_BLACK, VGA_COLOR_WHITE));
    HAL_Init();
}