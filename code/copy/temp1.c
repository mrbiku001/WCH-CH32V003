#include "debug.h"
#include "i2c_tx.h"

const uint8_t OLED_I2C_ADDRESS = 0x78;

// registers Address
const uint8_t COMMAND_REG = 0x80; // B1000 0000
const uint8_t DATA_REG = 0x40;    // B0100 0000

// commands
const uint8_t ON_CMD = 0xAF;
const uint8_t NORMAL_DISPLAY_CMD = 0xA6;
const uint8_t PAGE_ADDRESSING_MODE = 0x02;

uint8_t Char_Verticle_Pages_Required = 8;
uint8_t Char_Horizontal_Columns_Required = 37;
int No_of_bytes_Char = 297;
uint8_t First_char_ascii_code = 0;
const uint8_t Arial_Narrow37x64[] = {
    0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xFC, 0xFF, 0x1F, 0x00, 0x00, 0xE0, 0xFF, 0x7F, 0xFC, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x7F, 0xFC, 0x1F, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x7F, 0xFE, 0x0F, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFE, 0x07, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0xFE, 0x07, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0xFE, 0x07, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0xFE, 0x07, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0xFE, 0x07, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0xFE, 0x0F, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0xFC, 0x1F, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x7F, 0xFC, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x7F, 0xFC, 0xFF, 0x0F, 0x00, 0x00, 0xE0, 0xFF, 0x7F, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char 0
    0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char 1
    0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0xF0, 0x07, 0x00, 0x00, 0x00, 0xE0, 0x7F, 0x00, 0xFE, 0x07, 0x00, 0x00, 0x00, 0xF8, 0x7F, 0x00, 0xFF, 0x07, 0x00, 0x00, 0x00, 0xFE, 0x7F, 0xC0, 0xFF, 0x07, 0x00, 0x00, 0x00, 0xFF, 0x7F, 0xE0, 0xFF, 0x0F, 0x00, 0x00, 0xC0, 0xFF, 0x7F, 0xF0, 0xFF, 0x0F, 0x00, 0x00, 0xE0, 0xFF, 0x7F, 0xF0, 0xFF, 0x0F, 0x00, 0x00, 0xF0, 0xFF, 0x7F, 0xF8, 0xFF, 0x0F, 0x00, 0x00, 0xFC, 0xFF, 0x7F, 0xF8, 0xFF, 0x0F, 0x00, 0x00, 0xFE, 0xFF, 0x7F, 0xFC, 0xFF, 0x01, 0x00, 0x00, 0xFF, 0xFF, 0x7F, 0xFC, 0x3F, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0x7F, 0xFC, 0x1F, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0x7F, 0xFE, 0x0F, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x7F, 0xFE, 0x07, 0x00, 0x00, 0xF0, 0xFF, 0xF7, 0x7F, 0xFE, 0x07, 0x00, 0x00, 0xFC, 0xFF, 0xF1, 0x7F, 0xFE, 0x07, 0x00, 0x00, 0xFE, 0xFF, 0xF0, 0x7F, 0xFE, 0x07, 0x00, 0x00, 0xFF, 0x7F, 0xF0, 0x7F, 0xFE, 0x07, 0x00, 0x80, 0xFF, 0x3F, 0xF0, 0x7F, 0xFE, 0x07, 0x00, 0xC0, 0xFF, 0x1F, 0xF0, 0x7F, 0xFE, 0x0F, 0x00, 0xF0, 0xFF, 0x0F, 0xF0, 0x7F, 0xFE, 0x0F, 0x00, 0xF8, 0xFF, 0x03, 0xF0, 0x7F, 0xFC, 0x3F, 0x00, 0xFE, 0xFF, 0x01, 0xF0, 0x7F, 0xFC, 0xFF, 0x80, 0xFF, 0xFF, 0x00, 0xF0, 0x7F, 0xFC, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0xF0, 0x7F, 0xF8, 0xFF, 0xFF, 0xFF, 0x3F, 0x00, 0xF0, 0x7F, 0xF8, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0xF0, 0x7F, 0xF0, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0xF0, 0x7F, 0xE0, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0xF0, 0x7F, 0xC0, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0xF0, 0x7F, 0x80, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0xF0, 0x7F, 0x00, 0xFE, 0xFF, 0x1F, 0x00, 0x00, 0xF0, 0x7F, 0x00, 0xF8, 0xFF, 0x07, 0x00, 0x00, 0xF0, 0x7F, 0x00, 0xC0, 0x7F, 0x00, 0x00, 0x00, 0xF0, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char 2
    0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xF0, 0x03, 0x00, 0x00, 0xC0, 0x1F, 0x00, 0x00, 0xFC, 0x03, 0x00, 0x00, 0xC0, 0x7F, 0x00, 0x00, 0xFF, 0x03, 0x00, 0x00, 0xC0, 0xFF, 0x01, 0xC0, 0xFF, 0x07, 0x00, 0x00, 0xC0, 0xFF, 0x03, 0xE0, 0xFF, 0x07, 0x00, 0x00, 0xE0, 0xFF, 0x07, 0xF0, 0xFF, 0x07, 0x00, 0x00, 0xE0, 0xFF, 0x0F, 0xF0, 0xFF, 0x07, 0x00, 0x00, 0xE0, 0xFF, 0x1F, 0xF8, 0xFF, 0x07, 0x00, 0x00, 0xE0, 0xFF, 0x3F, 0xFC, 0xFF, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x3F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x7F, 0xFC, 0x1F, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x7F, 0xFE, 0x0F, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x7F, 0xFE, 0x07, 0x00, 0xC0, 0x07, 0x00, 0xE0, 0xFF, 0xFE, 0x07, 0x00, 0xFF, 0x03, 0x00, 0xE0, 0xFF, 0xFE, 0x07, 0x00, 0xFF, 0x03, 0x00, 0xC0, 0xFF, 0xFE, 0x07, 0x00, 0xFF, 0x03, 0x00, 0xC0, 0xFF, 0xFE, 0x07, 0x00, 0xFF, 0x03, 0x00, 0xC0, 0xFF, 0xFE, 0x07, 0x80, 0xFF, 0x03, 0x00, 0xC0, 0xFF, 0xFE, 0x0F, 0x80, 0xFF, 0x03, 0x00, 0xE0, 0xFF, 0xFE, 0x1F, 0xC0, 0xFF, 0x07, 0x00, 0xE0, 0xFF, 0xFC, 0x3F, 0xF0, 0xFF, 0x0F, 0x00, 0xF0, 0x7F, 0xFC, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0xFC, 0x7F, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x7F, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xF0, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0xFF, 0xC7, 0xFF, 0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0xFF, 0xC7, 0xFF, 0xFF, 0xFF, 0x0F, 0x80, 0xFF, 0xFF, 0x83, 0xFF, 0xFF, 0xFF, 0x07, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0xFC, 0x7F, 0x00, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0xF0, 0x0F, 0x00, 0xFC, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char 3
    0x25, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x9F, 0xFF, 0x03, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x87, 0xFF, 0x03, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0x81, 0xFF, 0x03, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80, 0xFF, 0x03, 0x00, 0x00, 0xC0, 0xFF, 0x3F, 0x80, 0xFF, 0x03, 0x00, 0x00, 0xE0, 0xFF, 0x0F, 0x80, 0xFF, 0x03, 0x00, 0x00, 0xF8, 0xFF, 0x03, 0x80, 0xFF, 0x03, 0x00, 0x00, 0xFE, 0xFF, 0x01, 0x80, 0xFF, 0x03, 0x00, 0x80, 0xFF, 0x7F, 0x00, 0x80, 0xFF, 0x03, 0x00, 0xC0, 0xFF, 0x1F, 0x00, 0x80, 0xFF, 0x03, 0x00, 0xF0, 0xFF, 0x07, 0x00, 0x80, 0xFF, 0x03, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x03, 0x00, // Code for char 4
    0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xC0, 0x1F, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x07, 0xC0, 0x7F, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0x07, 0xC0, 0xFF, 0x01, 0x00, 0xF0, 0xFF, 0xFF, 0x07, 0xC0, 0xFF, 0x03, 0xE0, 0xFF, 0xFF, 0xFF, 0x0F, 0xE0, 0xFF, 0x07, 0xFC, 0xFF, 0xFF, 0xFF, 0x0F, 0xE0, 0xFF, 0x0F, 0xFC, 0xFF, 0xFF, 0xFF, 0x0F, 0xE0, 0xFF, 0x1F, 0xFC, 0xFF, 0xFF, 0xFF, 0x0F, 0xE0, 0xFF, 0x3F, 0xFC, 0xFF, 0xFF, 0xFF, 0x0F, 0xE0, 0xFF, 0x3F, 0xFC, 0xFF, 0xFF, 0xFF, 0x07, 0x00, 0xFF, 0x7F, 0xFC, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0xFC, 0x7F, 0xFC, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0xF8, 0x7F, 0xFC, 0xFF, 0x87, 0xFF, 0x01, 0x00, 0xF0, 0xFF, 0xFC, 0x1F, 0x80, 0xFF, 0x00, 0x00, 0xE0, 0xFF, 0xFC, 0x1F, 0x80, 0xFF, 0x00, 0x00, 0xC0, 0xFF, 0xFC, 0x1F, 0xC0, 0xFF, 0x00, 0x00, 0xC0, 0xFF, 0xFC, 0x1F, 0xC0, 0xFF, 0x00, 0x00, 0xC0, 0xFF, 0xFC, 0x1F, 0xC0, 0xFF, 0x00, 0x00, 0xC0, 0xFF, 0xFC, 0x1F, 0xC0, 0xFF, 0x00, 0x00, 0xC0, 0xFF, 0xFC, 0x1F, 0xC0, 0xFF, 0x01, 0x00, 0xE0, 0xFF, 0xFC, 0x1F, 0xC0, 0xFF, 0x01, 0x00, 0xE0, 0xFF, 0xFC, 0x1F, 0xC0, 0xFF, 0x03, 0x00, 0xF0, 0x7F, 0xFC, 0x1F, 0x80, 0xFF, 0x0F, 0x00, 0xFC, 0x7F, 0xFC, 0x1F, 0x80, 0xFF, 0x3F, 0x80, 0xFF, 0x3F, 0xFC, 0x1F, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xFC, 0x1F, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0xFC, 0x1F, 0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0x0F, 0xFC, 0x1F, 0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0x0F, 0xFC, 0x1F, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0x03, 0xFC, 0x1F, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0x01, 0xFC, 0x1F, 0x00, 0xE0, 0xFF, 0xFF, 0x7F, 0x00, 0xFC, 0x1F, 0x00, 0x80, 0xFF, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char 5
    0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0xF0, 0xFF, 0xFF, 0xF1, 0xFF, 0xFF, 0xFF, 0x1F, 0xF8, 0xFF, 0x03, 0xF8, 0x7F, 0x80, 0xFF, 0x3F, 0xF8, 0x7F, 0x00, 0xFC, 0x0F, 0x00, 0xFC, 0x7F, 0xFC, 0x3F, 0x00, 0xFE, 0x07, 0x00, 0xF8, 0x7F, 0xFC, 0x1F, 0x00, 0xFF, 0x03, 0x00, 0xF0, 0x7F, 0xFC, 0x0F, 0x00, 0xFF, 0x03, 0x00, 0xE0, 0xFF, 0xFE, 0x07, 0x80, 0xFF, 0x01, 0x00, 0xC0, 0xFF, 0xFE, 0x07, 0x80, 0xFF, 0x01, 0x00, 0xC0, 0xFF, 0xFE, 0x07, 0x80, 0xFF, 0x01, 0x00, 0xC0, 0xFF, 0xFE, 0x07, 0x80, 0xFF, 0x01, 0x00, 0xC0, 0xFF, 0xFE, 0x07, 0x80, 0xFF, 0x03, 0x00, 0xC0, 0xFF, 0xFE, 0x0F, 0x80, 0xFF, 0x03, 0x00, 0xE0, 0xFF, 0xFE, 0x1F, 0x80, 0xFF, 0x07, 0x00, 0xF0, 0xFF, 0xFC, 0x7F, 0x00, 0xFF, 0x0F, 0x00, 0xF8, 0x7F, 0xFC, 0xFF, 0x03, 0xFF, 0x7F, 0x00, 0xFE, 0x7F, 0xFC, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xF8, 0xFF, 0x03, 0xFE, 0xFF, 0xFF, 0xFF, 0x3F, 0xF0, 0xFF, 0x03, 0xFC, 0xFF, 0xFF, 0xFF, 0x1F, 0xF0, 0xFF, 0x03, 0xF8, 0xFF, 0xFF, 0xFF, 0x0F, 0xE0, 0xFF, 0x01, 0xF0, 0xFF, 0xFF, 0xFF, 0x07, 0x80, 0xFF, 0x01, 0xE0, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0xFF, 0x01, 0xC0, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0xF8, 0x01, 0x00, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0xC0, 0x01, 0x00, 0xFC, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char 6
    0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFC, 0x1F, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x7F, 0xFC, 0x1F, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0x7F, 0xFC, 0x1F, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x7F, 0xFC, 0x1F, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0x7F, 0xFC, 0x1F, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x7F, 0xFC, 0x1F, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0x7F, 0xFC, 0x1F, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0x7F, 0xFC, 0x1F, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0x7F, 0xFC, 0x1F, 0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0x7F, 0xFC, 0x1F, 0x80, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0xFC, 0x1F, 0xE0, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFC, 0x1F, 0xF8, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0xFC, 0x1F, 0xFE, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFC, 0x1F, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0xFC, 0xDF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char 7
    0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x03, 0x00, 0x00, 0xF0, 0x1F, 0x00, 0xE0, 0xFF, 0x3F, 0x00, 0x00, 0xFE, 0xFF, 0x00, 0xF8, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x01, 0xFC, 0xFF, 0xFF, 0x01, 0xC0, 0xFF, 0xFF, 0x07, 0xFE, 0xFF, 0xFF, 0x07, 0xE0, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0xFF, 0x8F, 0xFF, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0x1F, 0xF8, 0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0x3F, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x7F, 0xFC, 0x7F, 0xE0, 0xFF, 0x3F, 0x00, 0xF8, 0x7F, 0xFE, 0x1F, 0x80, 0xFF, 0x1F, 0x00, 0xF0, 0x7F, 0xFE, 0x0F, 0x00, 0xFF, 0x0F, 0x00, 0xE0, 0xFF, 0xFE, 0x0F, 0x00, 0xFF, 0x0F, 0x00, 0xE0, 0xFF, 0xFE, 0x07, 0x00, 0xFE, 0x07, 0x00, 0xC0, 0xFF, 0xFE, 0x07, 0x00, 0xFE, 0x07, 0x00, 0xC0, 0xFF, 0xFE, 0x07, 0x00, 0xFE, 0x07, 0x00, 0xC0, 0xFF, 0xFE, 0x07, 0x00, 0xFE, 0x07, 0x00, 0xC0, 0xFF, 0xFE, 0x07, 0x00, 0xFE, 0x0F, 0x00, 0xC0, 0xFF, 0xFE, 0x0F, 0x00, 0xFF, 0x0F, 0x00, 0xE0, 0xFF, 0xFE, 0x0F, 0x00, 0xFF, 0x1F, 0x00, 0xF0, 0x7F, 0xFC, 0x1F, 0x80, 0xFF, 0x3F, 0x00, 0xF8, 0x7F, 0xFC, 0x7F, 0xE0, 0xFF, 0xFF, 0x00, 0xFF, 0x7F, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xF8, 0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0x3F, 0xF8, 0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0x1F, 0xF0, 0xFF, 0xFF, 0x8F, 0xFF, 0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0x0F, 0xC0, 0xFF, 0xFF, 0x03, 0xFE, 0xFF, 0xFF, 0x07, 0x00, 0xFF, 0xFF, 0x01, 0xFC, 0xFF, 0xFF, 0x01, 0x00, 0xFC, 0xFF, 0x00, 0xF8, 0xFF, 0xFF, 0x00, 0x00, 0xF0, 0x1F, 0x00, 0xE0, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char 8
    0x23, 0x00, 0x00, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0x7F, 0x00, 0x00, 0x07, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x01, 0x00, 0x3F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x07, 0x00, 0xFF, 0x01, 0x80, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0xFF, 0x03, 0xC0, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0xFF, 0x0F, 0xE0, 0xFF, 0xFF, 0xFF, 0x3F, 0x80, 0xFF, 0x1F, 0xF0, 0xFF, 0xFF, 0xFF, 0x7F, 0x80, 0xFF, 0x1F, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0xFF, 0x3F, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0xFF, 0x7F, 0xFC, 0xFF, 0x01, 0xFC, 0xFF, 0x81, 0xFF, 0x7F, 0xFC, 0x3F, 0x00, 0xF0, 0xFF, 0x01, 0xFC, 0x7F, 0xFC, 0x1F, 0x00, 0xC0, 0xFF, 0x03, 0xF0, 0xFF, 0xFE, 0x0F, 0x00, 0x80, 0xFF, 0x03, 0xE0, 0xFF, 0xFE, 0x07, 0x00, 0x80, 0xFF, 0x03, 0xE0, 0xFF, 0xFE, 0x07, 0x00, 0x00, 0xFF, 0x03, 0xC0, 0xFF, 0xFE, 0x07, 0x00, 0x00, 0xFF, 0x03, 0xC0, 0xFF, 0xFE, 0x07, 0x00, 0x00, 0xFF, 0x03, 0xC0, 0xFF, 0xFE, 0x07, 0x00, 0x00, 0xFF, 0x03, 0xC0, 0xFF, 0xFE, 0x0F, 0x00, 0x00, 0xFF, 0x01, 0xC0, 0xFF, 0xFE, 0x0F, 0x00, 0x80, 0xFF, 0x01, 0xE0, 0x7F, 0xFC, 0x1F, 0x00, 0x80, 0xFF, 0x01, 0xF0, 0x7F, 0xFC, 0x3F, 0x00, 0xC0, 0xFF, 0x00, 0xF8, 0x7F, 0xF8, 0x7F, 0x00, 0xE0, 0x7F, 0x00, 0xFE, 0x3F, 0xF8, 0xFF, 0x03, 0xFC, 0x3F, 0xC0, 0xFF, 0x3F, 0xF0, 0xFF, 0xFF, 0xFF, 0x1F, 0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // Code for char 9
};

const uint8_t temp14x16[] = {
    0x0D, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x07, 0xFC, 0x1F, 0xFE, 0x3F, 0x0F, 0x78, 0x03, 0x60, 0x03, 0x60, 0x03, 0x60, 0x07, 0x70, 0x1E, 0x3C, 0x1E, 0x3C, 0x08, 0x08, 0x00, 0x00, // Code for char C
    0x0E, 0x00, 0x00, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0x1F, 0x00, 0xF8, 0x03, 0x80, 0x7F, 0x00, 0x78, 0x80, 0x7F, 0xF8, 0x03, 0x1F, 0x00, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, // Code for char M
    0x0D, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x07, 0xFC, 0x1F, 0xFE, 0x3F, 0x0F, 0x78, 0x03, 0x60, 0x03, 0x60, 0x03, 0x60, 0x0F, 0x78, 0xFE, 0x3F, 0xFC, 0x1F, 0xF0, 0x07, 0x00, 0x00, // Code for char O
    0x0B, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xC3, 0x00, 0xC3, 0x00, 0xC3, 0x00, 0xC3, 0x00, 0xC3, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char F
    0x0C, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xFF, 0x7F, 0xFF, 0x7F, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, // Code for char H
    0x0A, 0x00, 0x00, 0x0C, 0x60, 0x0E, 0x78, 0x0F, 0x7C, 0x03, 0x7F, 0x83, 0x6F, 0xC3, 0x67, 0xFF, 0x63, 0xFE, 0x61, 0x7C, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Code for char 2
};

void IIC_Init(u32 bound, u16 address)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    I2C_InitTypeDef I2C_InitTSturcture = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    I2C_InitTSturcture.I2C_ClockSpeed = bound;
    I2C_InitTSturcture.I2C_Mode = I2C_Mode_I2C;
    I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_16_9;
    I2C_InitTSturcture.I2C_OwnAddress1 = address;
    I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;
    I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C1, &I2C_InitTSturcture);

    I2C_Cmd(I2C1, ENABLE);

    I2C_AcknowledgeConfig(I2C1, ENABLE);
}

void GPIO_Toggle_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void writeCommand(uint8_t command)
{
    I2C_start(OLED_I2C_ADDRESS); // start transmission to OLED
    I2C_write(COMMAND_REG);      // set command mode
    I2C_write(command);          // set line
    I2C_stop();                  // stop transmission
}

void writeData(uint8_t data)
{
    I2C_start(OLED_I2C_ADDRESS); // start transmission to OLED
    I2C_write(DATA_REG);         // Data Reg Address
    I2C_write(data);             // write data
    I2C_stop();                  // stop transmission
}

void setCursor(uint8_t X, uint8_t Y)
{
    writeCommand(0x00 + (X & 0x0F));        // set column lower address
    writeCommand(0x10 + ((X >> 4) & 0x0F)); // set column higher address
    writeCommand(0xB0 + Y);                 // set page address
}

void turnON()
{
    writeCommand(ON_CMD);
}

void NormalDisplayMode()
{
    writeCommand(NORMAL_DISPLAY_CMD);
}

void setPageMode()
{
    uint8_t addressingMode = PAGE_ADDRESSING_MODE;
    writeCommand(0x20);                 // set addressing mode
    writeCommand(PAGE_ADDRESSING_MODE); // set page addressing mode
}

// clearFullDisplay()
//  In this function we are setting X,Y=0
//  then write data on 128 column and
//  then change page and do same till 7th page
void clearFullDisplay()
{
    for (uint8_t page = 0; page < 8; page++)
    {
        setCursor(0, page);
        for (uint8_t column = 0; column < 128; column++)
        { // clear all columns
            writeData(0x00);
        }
    }
    setCursor(0, 0);
}

void oled_begin()
{
    I2C_init();
    turnON();
    NormalDisplayMode();
    setPageMode();
    writeCommand(0x8d); // Charge Pump
    writeCommand(0x14);
    clearFullDisplay();
}

void print_char(uint8_t dig, int x_cord, int y_cord)
{
    // int ascii_to_array_index = ch - First_char_ascii_code;
    int char_start_in_array = (dig * No_of_bytes_Char) + 1;
    for (int j = x_cord; j < (x_cord + Char_Horizontal_Columns_Required); j++)
    {
        for (int i = y_cord; i < (y_cord + Char_Verticle_Pages_Required); i++)
        {
            setCursor(j, i);
            int array_index = (char_start_in_array + ((j - x_cord) * Char_Verticle_Pages_Required)) + (i - y_cord);
            writeData(Arial_Narrow37x64[array_index]);
        }
    }
    I2C_stop(); // stop transmission
}

void print_unit_char(uint8_t dig, int x_cord, int y_cord)
{
    // int ascii_to_array_index = ch - First_char_ascii_code;
    int char_start_in_array = (dig * 29) + 1;
    for (int j = x_cord; j < (x_cord + 14); j++)
    {
        for (int i = y_cord; i < (y_cord + 2); i++)
        {
            setCursor(j, i);
            int array_index = (char_start_in_array + ((j - x_cord) * 2)) + (i - y_cord);
            writeData(temp14x16[array_index]);
        }
    }
    I2C_stop(); // stop transmission
}

void print_unit_temp(void)
{
    print_unit_char(1, 112, 2);
    print_unit_char(0, 98, 2);
    print_unit_char(3, 112, 4);
    print_unit_char(2, 98, 4);
    print_unit_char(2, 112, 6);
    print_unit_char(5, 100, 6);
    print_unit_char(4, 85, 6);
}

int pow(int x, int y)
{
    int result = 1;
    for (; y > 0; y--)
    {
        result *= x;
    }
    return result;
}

int setPosCenter(int count)
{
    int result;
    if (count == 1)
    {
        result = 24;
    }
    else
    {
        result = 5;
    }
    return result;
}

void print_d(int num)
{
    int i = num, count = 0;
    if (num == 0)
        count = 1;
    else if (num < 0)
    {
        print_char(12, 24, 0); // print U
        return;
    }
    else if (num > 99)
    {
        print_char(11, 24, 0); // print O
        return;
    }
    else
    {
        i = num;
    }
    while (i)
    {
        i /= 10;
        count++;
    }
    int x = setPosCenter(count);
    i = num;
    for (int j = count; j > 0; j--)
    {
        int div = pow(10, j - 1);
        int f_print = i / div;
        print_char(f_print, x, 0);
        i %= div;
        x += 38;
    }
}

int main(void)
{
    Delay_Init();
    // USART_Printf_Init(115200);
    // printf("SystemClk:%d\r\n",SystemCoreClock);

    // Setup internal peripherals
    I2C_init();

    oled_begin();
    setCursor(0, 0);
    // send data in array to display
    // print_char('B',0,0);
    // print_char1();
    // send data in array to display
    // print_char(7,0,0);
    // print_d(25);
    print_unit_temp();
    print_d(5);
    // print_minus();
    // print_unit();
    GPIO_Toggle_INIT();
    u8 i = 0;
    while (1)
    {
        Delay_Ms(500);
        GPIO_WriteBit(GPIOD, GPIO_Pin_0, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
    }
}
