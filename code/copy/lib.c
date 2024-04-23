#include "debug.h"
#include "i2c_tx.h"

const uint8_t OLED_I2C_ADDRESS = 0x78;

//registers Address
const uint8_t COMMAND_REG = 0x80;  // B1000 0000
const uint8_t DATA_REG = 0x40;  // B0100 0000

// commands
const uint8_t  ON_CMD = 0xAF;
const uint8_t  NORMAL_DISPLAY_CMD = 0xA6;
const uint8_t  PAGE_ADDRESSING_MODE = 0x02;

uint8_t Char_Verticle_Pages_Required = 3;
uint8_t Char_Horizontal_Columns_Required = 12;
uint8_t No_of_bytes_Char = 37;
uint8_t First_char_ascii_code = 32;

const uint8_t data[]= {0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA};
const uint8_t data2[]= { 0xFF, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55,0xAA, 0x55, 0xAA, 0x55,0xAA, 0x55, 0xAA, 0x55,0xAA, 0x55, 0xAA, 0x55,0xAA, 0x55, 0xAA, 0x55,0xAA, 0x55, 0xAA, 0x55,0xAA, 0x55, 0xAA, 0x55, 0xFF };
               
               //0x33, 0x33, 0x33, 0x33, 0xCC, 0xCC, 0xCC,
               //0xCC, 0x33, 0x33, 0x33, 0x33, 0xCC, 0xCC, 
               //0xCC, 0xCC, 0x33, 0x33, 0x33, 0x33, 0xCC, 
               //0xCC, 0xCC, 0xCC, 0x33, 0x33, 0x33, 0x33,
               //0xCC, 0xCC, 0xCC, 0xCC 
               
const uint8_t MS_Gothic12x24[] = {
       0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char  
        //0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x31, 0xF8, 0xFF, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char !
         0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x31, 0xF8, 0xFF, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char !
        0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x04, 0x00, 0x00, 0x20, 0x00, 0x00, 0x38, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char "
        0x0B, 0x00, 0x00, 0x00, 0x80, 0x81, 0x01, 0x80, 0x81, 0x3F, 0x80, 0xFF, 0x1F, 0xFC, 0x87, 0x01, 0x80, 0x81, 0x01, 0x80, 0x81, 0x01, 0x80, 0xE1, 0x3F, 0xF8, 0xFF, 0x01, 0xFC, 0x81, 0x01, 0x80, 0x81, 0x01, 0x00, 0x00, 0x00,  // Code for char #
        0x0A, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xE0, 0x83, 0x0F, 0xF0, 0x07, 0x0E, 0x18, 0x0E, 0x18, 0x18, 0x1C, 0x18, 0xFE, 0xFF, 0x7F, 0x18, 0x38, 0x18, 0xF0, 0xF0, 0x0F, 0xE0, 0xE0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char $
        0x0B, 0x00, 0x00, 0x00, 0xF8, 0x0F, 0x00, 0x08, 0x18, 0x20, 0x08, 0x18, 0x1C, 0xF8, 0x8F, 0x03, 0x00, 0x70, 0x00, 0x00, 0x0E, 0x00, 0xC0, 0xF1, 0x1F, 0x38, 0x10, 0x30, 0x04, 0x30, 0x30, 0x00, 0xE0, 0x1F, 0x00, 0x00, 0x00,  // Code for char %
        0x0B, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x07, 0xE0, 0xF8, 0x0F, 0xF8, 0x1F, 0x18, 0x18, 0x1F, 0x18, 0x08, 0x7E, 0x18, 0x18, 0xE3, 0x18, 0xF8, 0xC1, 0x1F, 0x60, 0x00, 0x0F, 0x00, 0xF0, 0x0F, 0x00, 0x70, 0x1C, 0x00, 0x00, 0x00,  // Code for char &
        0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4C, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char '
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x03, 0xE0, 0x00, 0x0F, 0x30, 0x00, 0x18, 0x1C, 0x00, 0x30, 0x04, 0x00, 0x60, 0x00, 0x00, 0x00,  // Code for char (
        0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x60, 0x1C, 0x00, 0x30, 0x30, 0x00, 0x1C, 0xE0, 0x01, 0x0F, 0x80, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char )
        0x0B, 0x00, 0x00, 0x00, 0x00, 0xC6, 0x00, 0x00, 0x66, 0x00, 0x00, 0x6C, 0x00, 0x00, 0x38, 0x00, 0x80, 0xFF, 0x03, 0x80, 0xFF, 0x03, 0x00, 0x38, 0x00, 0x00, 0x6C, 0x00, 0x00, 0x66, 0x00, 0x00, 0xC6, 0x00, 0x00, 0x00, 0x00,  // Code for char *
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x80, 0xFF, 0x03, 0x80, 0xFF, 0x03, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00,  // Code for char +
        0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char ,
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00,  // Code for char -
        0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char .
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x18, 0x00, 0x00, 0x07, 0x00, 0xC0, 0x01, 0x00, 0x70, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x03, 0x00, 0xE0, 0x00, 0x00, 0x38, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char /
        0x0B, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x01, 0xF0, 0xFF, 0x07, 0x78, 0x00, 0x0F, 0x18, 0x00, 0x1C, 0x08, 0x00, 0x18, 0x08, 0x00, 0x18, 0x18, 0x00, 0x1C, 0xF0, 0x00, 0x0F, 0xE0, 0xFF, 0x07, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00,  // Code for char 0
        0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x20, 0x00, 0x00, 0x20, 0x00, 0x00, 0xF0, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char 1
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0xF0, 0x01, 0x1E, 0xF8, 0x81, 0x1F, 0x18, 0xC0, 0x19, 0x08, 0xE0, 0x18, 0x08, 0x70, 0x18, 0x18, 0x1C, 0x18, 0xF8, 0x0F, 0x18, 0xF0, 0x07, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,  // Code for char 2
        0x0B, 0x00, 0x00, 0x00, 0x80, 0x80, 0x03, 0xF0, 0x80, 0x0F, 0x78, 0x00, 0x0C, 0x18, 0x00, 0x18, 0x08, 0x08, 0x18, 0x08, 0x0C, 0x18, 0x18, 0x1C, 0x1C, 0xF8, 0xF7, 0x0F, 0xF0, 0xE3, 0x07, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00,  // Code for char 3
        0x0B, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x01, 0x00, 0xF8, 0x01, 0x00, 0x9E, 0x01, 0x80, 0x8F, 0x01, 0xC0, 0x83, 0x01, 0xF0, 0x80, 0x01, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00, 0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00,  // Code for char 4
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x10, 0x03, 0xF8, 0x1F, 0x0F, 0xF8, 0x1F, 0x1C, 0x18, 0x04, 0x18, 0x18, 0x06, 0x18, 0x18, 0x06, 0x18, 0x18, 0x06, 0x1C, 0x18, 0xFC, 0x0F, 0x18, 0xF8, 0x07, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00,  // Code for char 5
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0xC0, 0xFF, 0x03, 0xF0, 0xFF, 0x0F, 0x38, 0x0C, 0x1C, 0x18, 0x06, 0x18, 0x08, 0x06, 0x18, 0x18, 0x06, 0x18, 0x78, 0x3C, 0x0F, 0x70, 0xFC, 0x07, 0x00, 0xE0, 0x01, 0x00, 0x00, 0x00,  // Code for char 6
        0x0A, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x18, 0x18, 0x80, 0x1F, 0x18, 0xF8, 0x07, 0x18, 0x7F, 0x00, 0xF8, 0x0F, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char 7
        0x0B, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x03, 0xF0, 0xF3, 0x0F, 0xF8, 0x37, 0x0E, 0x18, 0x1C, 0x18, 0x08, 0x08, 0x18, 0x08, 0x08, 0x18, 0x18, 0x1C, 0x18, 0xF8, 0x37, 0x0E, 0xF0, 0xE3, 0x07, 0x00, 0xC0, 0x03, 0x00, 0x00, 0x00,  // Code for char 8
        0x0B, 0x00, 0x00, 0x00, 0xC0, 0x07, 0x00, 0xF0, 0x1F, 0x06, 0x78, 0x3C, 0x0E, 0x18, 0x60, 0x18, 0x08, 0x60, 0x18, 0x08, 0x60, 0x18, 0x18, 0x30, 0x0E, 0xF0, 0xFF, 0x07, 0xE0, 0xFF, 0x03, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x00,  // Code for char 9
        0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x03, 0xC0, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char :
        0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x1B, 0xC0, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char ;
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x36, 0x00, 0x00, 0x63, 0x00, 0x80, 0xC1, 0x00, 0xC0, 0x80, 0x01, 0x60, 0x00, 0x03, 0x30, 0x00, 0x06, 0x18, 0x00, 0x0C, 0x08, 0x00, 0x18, 0x00, 0x00, 0x00,  // Code for char <
        0x0B, 0x00, 0x00, 0x00, 0x00, 0xC6, 0x00, 0x00, 0xC6, 0x00, 0x00, 0xC6, 0x00, 0x00, 0xC6, 0x00, 0x00, 0xC6, 0x00, 0x00, 0xC6, 0x00, 0x00, 0xC6, 0x00, 0x00, 0xC6, 0x00, 0x00, 0xC6, 0x00, 0x00, 0xC6, 0x00, 0x00, 0x00, 0x00,  // Code for char =
        0x0B, 0x00, 0x00, 0x00, 0x08, 0x00, 0x18, 0x18, 0x00, 0x0C, 0x30, 0x00, 0x06, 0x60, 0x00, 0x03, 0xC0, 0x80, 0x01, 0x80, 0xC1, 0x00, 0x00, 0x63, 0x00, 0x00, 0x36, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,  // Code for char >
        0x0A, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x00, 0xF0, 0x01, 0x00, 0x78, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0C, 0xE0, 0x31, 0x0C, 0xF0, 0x31, 0x18, 0x1C, 0x00, 0xF8, 0x0F, 0x00, 0xF0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char ?
        0x0B, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x07, 0x60, 0x00, 0x18, 0x10, 0xFE, 0x31, 0x88, 0x03, 0x23, 0xC4, 0x00, 0x43, 0xC4, 0x80, 0x41, 0x84, 0xFF, 0x23, 0x88, 0x07, 0x22, 0x10, 0x00, 0x01, 0xE0, 0xFF, 0x00, 0x00, 0x00, 0x00,  // Code for char @
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0xE0, 0x1F, 0x00, 0xFE, 0x01, 0xE0, 0xDF, 0x00, 0xF8, 0xC1, 0x00, 0xF8, 0xC1, 0x00, 0xE0, 0xDF, 0x00, 0x00, 0xFE, 0x01, 0x00, 0xE0, 0x1F, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00,  // Code for char A
        0x0B, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x18, 0x0C, 0x18, 0x18, 0x0C, 0x18, 0x18, 0x0C, 0x18, 0x18, 0x0C, 0x18, 0x18, 0x0E, 0x1C, 0x38, 0x1F, 0x0E, 0xF0, 0xF3, 0x07, 0xC0, 0xE0, 0x03, 0x00, 0x00, 0x00,  // Code for char B
        0x0B, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x00, 0xE0, 0xFF, 0x07, 0xF0, 0x00, 0x0F, 0x38, 0x00, 0x1C, 0x18, 0x00, 0x18, 0x08, 0x00, 0x18, 0x18, 0x00, 0x1C, 0x38, 0x00, 0x0E, 0xF0, 0xC1, 0x07, 0xE0, 0xC1, 0x03, 0x00, 0x00, 0x00,  // Code for char C
        0x0B, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x18, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x1C, 0x38, 0x00, 0x0C, 0xF0, 0x81, 0x0F, 0xE0, 0xFF, 0x03, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00,  // Code for char D
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x18, 0x0C, 0x18, 0x18, 0x0C, 0x18, 0x18, 0x0C, 0x18, 0x18, 0x0C, 0x18, 0x18, 0x0C, 0x18, 0x18, 0x0C, 0x18, 0x18, 0x00, 0x18, 0x00, 0x00, 0x00,  // Code for char E
        0x0B, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x18, 0x0C, 0x00, 0x18, 0x0C, 0x00, 0x18, 0x0C, 0x00, 0x18, 0x0C, 0x00, 0x18, 0x0C, 0x00, 0x18, 0x0C, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char F
        0x0B, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x01, 0xE0, 0xFF, 0x07, 0xF0, 0x00, 0x0F, 0x38, 0x00, 0x1C, 0x18, 0x00, 0x18, 0x08, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x38, 0x18, 0x0E, 0xF0, 0xF8, 0x1F, 0xC0, 0xF8, 0x1F, 0x00, 0x00, 0x00,  // Code for char G
        0x0B, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00, 0x0C, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x0C, 0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00, 0x00, 0x00,  // Code for char H
        0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x18, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x18, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char I
        0x0B, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x07, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x0F, 0xF8, 0xFF, 0x07, 0xF8, 0xFF, 0x00, 0x00, 0x00, 0x00,  // Code for char J
        0x0B, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00, 0x1C, 0x00, 0x00, 0x0F, 0x00, 0x80, 0x1F, 0x00, 0xC0, 0x7D, 0x00, 0xF0, 0xE0, 0x03, 0x38, 0x80, 0x0F, 0x18, 0x00, 0x1E, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,  // Code for char K
        0x0B, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,  // Code for char L
        0x0B, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0xF8, 0x03, 0x00, 0xC0, 0xFF, 0x00, 0x00, 0xF0, 0x1F, 0x00, 0xF0, 0x1F, 0xC0, 0xFF, 0x00, 0xF8, 0x03, 0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00, 0x00, 0x00,  // Code for char M
        0x0B, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0xF8, 0x00, 0x00, 0xE0, 0x07, 0x00, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x00, 0xE0, 0x07, 0x00, 0x00, 0x1F, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00, 0x00, 0x00,  // Code for char N
        0x0B, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x01, 0xF0, 0xFF, 0x07, 0x38, 0x00, 0x0E, 0x18, 0x00, 0x18, 0x08, 0x00, 0x18, 0x08, 0x00, 0x18, 0x18, 0x00, 0x1C, 0x78, 0x00, 0x0E, 0xF0, 0xFF, 0x07, 0xC0, 0xFF, 0x01, 0x00, 0x00, 0x00,  // Code for char O
        0x0B, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x38, 0x1C, 0x00, 0xF0, 0x0F, 0x00, 0xE0, 0x07, 0x00, 0x00, 0x00, 0x00,  // Code for char P
        0x0B, 0x00, 0x00, 0x00, 0xC0, 0xFF, 0x01, 0xF0, 0xFF, 0x07, 0x38, 0x00, 0x0E, 0x18, 0x00, 0x18, 0x08, 0x00, 0x18, 0x08, 0x80, 0x19, 0x18, 0x80, 0x1F, 0x78, 0x00, 0x1E, 0xF0, 0xFF, 0x1F, 0xC0, 0xFF, 0x01, 0x00, 0x00, 0x00,  // Code for char Q
        0x0B, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x18, 0x38, 0x00, 0x18, 0xFC, 0x01, 0x38, 0xEE, 0x07, 0xF0, 0x07, 0x1F, 0xE0, 0x03, 0x18, 0x00, 0x00, 0x00,  // Code for char R
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0xF0, 0x83, 0x0F, 0xF8, 0x07, 0x0C, 0x18, 0x0E, 0x18, 0x08, 0x0C, 0x18, 0x08, 0x18, 0x18, 0x18, 0x38, 0x18, 0xF8, 0x70, 0x0E, 0xF0, 0xE0, 0x0F, 0x80, 0xC0, 0x03, 0x00, 0x00, 0x00,  // Code for char S
        0x0B, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char T
        0x0B, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x03, 0xF8, 0xFF, 0x0F, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x0E, 0xF8, 0xFF, 0x0F, 0xF8, 0xFF, 0x03, 0x00, 0x00, 0x00,  // Code for char U
        0x0B, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0xF8, 0x07, 0x00, 0xC0, 0x7F, 0x00, 0x00, 0xF8, 0x07, 0x00, 0x80, 0x1F, 0x00, 0xC0, 0x1F, 0x00, 0xFC, 0x07, 0xC0, 0x3F, 0x00, 0xF8, 0x03, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char V
        0x0C, 0x18, 0x00, 0x00, 0xF8, 0x3F, 0x00, 0x80, 0xFF, 0x1F, 0x00, 0xC0, 0x1F, 0xC0, 0xFF, 0x03, 0xF8, 0x03, 0x00, 0xF8, 0x07, 0x00, 0x80, 0xFF, 0x07, 0x00, 0xC0, 0x1F, 0xE0, 0xFF, 0x1F, 0xF8, 0x1F, 0x00, 0x08, 0x00, 0x00,  // Code for char W
        0x0B, 0x00, 0x00, 0x00, 0x08, 0x00, 0x18, 0x38, 0x00, 0x1F, 0xF0, 0xC0, 0x07, 0xC0, 0xF7, 0x01, 0x00, 0x3F, 0x00, 0x00, 0x7F, 0x00, 0xE0, 0xF3, 0x01, 0xF8, 0xC0, 0x07, 0x38, 0x00, 0x1E, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,  // Code for char X
        0x0B, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x78, 0x00, 0x00, 0xE0, 0x01, 0x00, 0x80, 0x07, 0x00, 0x00, 0xFE, 0x1F, 0x00, 0xFE, 0x1F, 0x80, 0x07, 0x00, 0xF0, 0x01, 0x00, 0x78, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char Y
        0x0B, 0x00, 0x00, 0x00, 0x18, 0x00, 0x1C, 0x18, 0x00, 0x1F, 0x18, 0xC0, 0x1B, 0x18, 0xF0, 0x18, 0x18, 0x3C, 0x18, 0x18, 0x0F, 0x18, 0xD8, 0x03, 0x18, 0xF8, 0x01, 0x18, 0x78, 0x00, 0x18, 0x18, 0x00, 0x18, 0x00, 0x00, 0x00,  // Code for char Z
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0x0C, 0x00, 0xC0, 0x0C, 0x00, 0xC0, 0x0C, 0x00, 0xC0, 0x0C, 0x00, 0xC0, 0x0C, 0x00, 0xC0, 0x00, 0x00, 0x00,  // Code for char [
        0x0B, 0x00, 0x00, 0x00, 0x18, 0xF0, 0x00, 0xF8, 0xF0, 0x00, 0xE0, 0xF3, 0x00, 0x80, 0xFF, 0x00, 0x00, 0xFC, 0x1F, 0x00, 0xFE, 0x1F, 0x80, 0xF7, 0x00, 0xF0, 0xF1, 0x00, 0x78, 0xF0, 0x00, 0x18, 0xF0, 0x00, 0x00, 0x00, 0x00,  // Code for char BackSlash
        0x07, 0x00, 0x00, 0x00, 0x0C, 0x00, 0xC0, 0x0C, 0x00, 0xC0, 0x0C, 0x00, 0xC0, 0x0C, 0x00, 0xC0, 0xFC, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char ]
        0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x18, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char ^
        0x0C, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40,  // Code for char _
        0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x06, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char `
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x8C, 0x0F, 0x00, 0xCE, 0x1C, 0x00, 0x43, 0x18, 0x00, 0x63, 0x18, 0x00, 0x63, 0x18, 0x00, 0x33, 0x0C, 0x00, 0xFF, 0x1F, 0x00, 0xFE, 0x1F, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,  // Code for char a
        0x0B, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00, 0x04, 0x0C, 0x00, 0x02, 0x18, 0x00, 0x03, 0x18, 0x00, 0x03, 0x18, 0x00, 0x03, 0x18, 0x00, 0x0E, 0x0E, 0x00, 0xFE, 0x07, 0x00, 0xF0, 0x01, 0x00, 0x00, 0x00,  // Code for char b
        0x0B, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x03, 0x00, 0xFC, 0x07, 0x00, 0x0E, 0x0E, 0x00, 0x03, 0x18, 0x00, 0x03, 0x18, 0x00, 0x03, 0x18, 0x00, 0x03, 0x18, 0x00, 0x0E, 0x0E, 0x00, 0x8E, 0x07, 0x00, 0x80, 0x03, 0x00, 0x00, 0x00,  // Code for char c
        0x0B, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x03, 0x00, 0xFC, 0x07, 0x00, 0x06, 0x0C, 0x00, 0x03, 0x18, 0x00, 0x03, 0x18, 0x00, 0x03, 0x18, 0x00, 0x02, 0x0C, 0x00, 0x1E, 0x07, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00, 0x00, 0x00,  // Code for char d
        0x0B, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x01, 0x00, 0xFC, 0x07, 0x00, 0x6E, 0x0E, 0x00, 0x63, 0x1C, 0x00, 0x63, 0x18, 0x00, 0x63, 0x18, 0x00, 0x63, 0x18, 0x00, 0x6E, 0x0E, 0x00, 0x7C, 0x07, 0x00, 0x70, 0x03, 0x00, 0x00, 0x00,  // Code for char e
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0xF0, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x18, 0x03, 0x00, 0x08, 0x03, 0x00, 0x08, 0x03, 0x00, 0x08, 0x03, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char f
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0xBC, 0x7F, 0x00, 0xFE, 0xCE, 0x00, 0xC3, 0x8C, 0x00, 0x83, 0x8C, 0x00, 0xC3, 0x8C, 0x00, 0xFF, 0x8C, 0x00, 0x7E, 0xCC, 0x00, 0x03, 0x78, 0x00, 0x03, 0x30, 0x00, 0x00, 0x00,  // Code for char g
        0x0B, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00, 0x0C, 0x00, 0x00, 0x06, 0x00, 0x00, 0x03, 0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0F, 0x00, 0x00, 0xFE, 0x1F, 0x00, 0xF8, 0x1F, 0x00, 0x00, 0x00,  // Code for char h
        0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0xFF, 0x1F, 0x18, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char i
        0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0xC0, 0x00, 0x00, 0xC0, 0x00, 0x00, 0xC0, 0x00, 0x00, 0xC0, 0x18, 0xFF, 0x7F, 0x18, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char j
        0x0B, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00, 0xC0, 0x00, 0x00, 0x70, 0x00, 0x00, 0x38, 0x00, 0x00, 0xFC, 0x00, 0x00, 0xCE, 0x03, 0x00, 0x03, 0x0F, 0x00, 0x01, 0x1C, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,  // Code for char k
        0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x1F, 0xF8, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char l
        0x0B, 0x00, 0xFF, 0x1F, 0x00, 0xFF, 0x1F, 0x00, 0x06, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0xFF, 0x1F, 0x00, 0xFE, 0x1F, 0x00, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0xFF, 0x1F, 0x00, 0xFF, 0x1F, 0x00, 0x00, 0x00,  // Code for char m
        0x0B, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x1F, 0x00, 0xFF, 0x1F, 0x00, 0x1C, 0x00, 0x00, 0x06, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x07, 0x00, 0x00, 0xFE, 0x1F, 0x00, 0xFC, 0x1F, 0x00, 0x00, 0x00,  // Code for char n
        0x0B, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x03, 0x00, 0xFE, 0x07, 0x00, 0x06, 0x0E, 0x00, 0x03, 0x18, 0x00, 0x03, 0x18, 0x00, 0x03, 0x18, 0x00, 0x03, 0x18, 0x00, 0x0E, 0x0E, 0x00, 0xFC, 0x07, 0x00, 0xF8, 0x03, 0x00, 0x00, 0x00,  // Code for char o
        0x0B, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x0E, 0x0E, 0x00, 0x02, 0x1C, 0x00, 0x03, 0x18, 0x00, 0x03, 0x18, 0x00, 0x03, 0x18, 0x00, 0x0E, 0x0E, 0x00, 0xFE, 0x07, 0x00, 0xF8, 0x01, 0x00, 0x00, 0x00,  // Code for char p
        0x0B, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x03, 0x00, 0xFE, 0x0F, 0x00, 0x06, 0x1C, 0x00, 0x03, 0x18, 0x00, 0x03, 0x18, 0x00, 0x03, 0x18, 0x00, 0x02, 0x0C, 0x00, 0x1C, 0x07, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00,  // Code for char q
        0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x1F, 0x00, 0xFF, 0x1F, 0x00, 0x38, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x06, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char r
        0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x0F, 0x00, 0x3F, 0x0E, 0x00, 0x23, 0x18, 0x00, 0x63, 0x18, 0x00, 0x63, 0x18, 0x00, 0xC3, 0x18, 0x00, 0xCE, 0x0F, 0x00, 0x8C, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char s
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0xF0, 0xFF, 0x0F, 0xF0, 0xFF, 0x1F, 0x00, 0x03, 0x18, 0x00, 0x03, 0x18, 0x00, 0x03, 0x18, 0x00, 0x03, 0x18, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00,  // Code for char t
        0x0A, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x07, 0x00, 0xFF, 0x0F, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0C, 0x00, 0xFF, 0x1F, 0x00, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char u
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x1F, 0x00, 0x00, 0xFC, 0x00, 0x00, 0xE0, 0x0F, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x1F, 0x00, 0xE0, 0x07, 0x00, 0xFE, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,  // Code for char v
        0x0C, 0x00, 0x03, 0x00, 0x00, 0x7F, 0x00, 0x00, 0xFC, 0x0F, 0x00, 0x00, 0x1F, 0x00, 0xFC, 0x0F, 0x00, 0x3F, 0x00, 0x00, 0x7F, 0x00, 0x00, 0xF8, 0x1F, 0x00, 0x80, 0x1F, 0x00, 0xFE, 0x07, 0x00, 0x3F, 0x00, 0x00, 0x01, 0x00,  // Code for char w
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x03, 0x1C, 0x00, 0x0F, 0x0E, 0x00, 0xBC, 0x07, 0x00, 0xF0, 0x01, 0x00, 0xF0, 0x01, 0x00, 0x9C, 0x07, 0x00, 0x0F, 0x1E, 0x00, 0x03, 0x18, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,  // Code for char x
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x7C, 0xC0, 0x00, 0xF0, 0xC3, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x3F, 0x00, 0xE0, 0x07, 0x00, 0xFE, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,  // Code for char y
        0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x03, 0x1E, 0x00, 0x03, 0x1F, 0x00, 0x83, 0x19, 0x00, 0xE3, 0x18, 0x00, 0x33, 0x18, 0x00, 0x1F, 0x18, 0x00, 0x07, 0x18, 0x00, 0x03, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char z
        0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x38, 0x00, 0xFE, 0xFF, 0x7F, 0xFE, 0xC3, 0x7F, 0x02, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char {
        0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char |
        0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x40, 0x02, 0x00, 0x40, 0xFE, 0xE7, 0x7F, 0xFE, 0xFF, 0x7F, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char }
        0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char ~
        0x05, 0xC0, 0xFF, 0x0F, 0x40, 0x00, 0x08, 0x40, 0x00, 0x08, 0x40, 0x00, 0x08, 0xC0, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00   // Code for char 
        };

void IIC_Init(u32 bound, u16 address)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    I2C_InitTypeDef I2C_InitTSturcture={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE );
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOC, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOC, &GPIO_InitStructure );

    I2C_InitTSturcture.I2C_ClockSpeed = bound;
    I2C_InitTSturcture.I2C_Mode = I2C_Mode_I2C;
    I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_16_9;
    I2C_InitTSturcture.I2C_OwnAddress1 = address;
    I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;
    I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init( I2C1, &I2C_InitTSturcture );

    I2C_Cmd( I2C1, ENABLE );

    I2C_AcknowledgeConfig( I2C1, ENABLE );
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

void writeCommand(uint8_t command){
  I2C_start(OLED_I2C_ADDRESS);                   // start transmission to OLED
  I2C_write(COMMAND_REG);               // set command mode
  I2C_write(command);                     // set line
  I2C_stop();                             // stop transmission
}

void writeData(uint8_t data){
  I2C_start(OLED_I2C_ADDRESS);                   // start transmission to OLED
  I2C_write(DATA_REG);               // Data Reg Address
  I2C_write(data);                      //write data
  I2C_stop();                             // stop transmission
}

void setCursor(uint8_t X, uint8_t Y){
  writeCommand(0x00 + (X & 0x0F));        //set column lower address
  writeCommand(0x10 + ((X >> 4) & 0x0F)); //set column higher address
  writeCommand(0xB0 + Y);                 //set page address
  }
  
void turnON(){
  writeCommand(ON_CMD);
}

void NormalDisplayMode(){
  writeCommand(NORMAL_DISPLAY_CMD);
}

void setPageMode(){
  uint8_t addressingMode = PAGE_ADDRESSING_MODE;
  writeCommand(0x20);   //set addressing mode
  writeCommand(PAGE_ADDRESSING_MODE); //set page addressing mode
}

//clearFullDisplay()
// In this function we are setting X,Y=0
// then write data on 128 column and
// then change page and do same till 7th page
void clearFullDisplay(){
  for(uint8_t page = 0; page<8; page++){
    setCursor(0,page);
    for(uint8_t column = 0; column<128; column++){ //clear all columns
      writeData(0x00);
    }
  }
  setCursor(0,0);
}

void oled_begin(){
  I2C_init();
  turnON();
  NormalDisplayMode();
  setPageMode();
  writeCommand(0x8d); //Charge Pump
  writeCommand(0x14);
  clearFullDisplay();
}

void print_char(char ch, int x_cord, int y_cord)
{
  int ascii_to_array_index = ch - First_char_ascii_code;
  int char_start_in_array  = (ascii_to_array_index * No_of_bytes_Char) + 1;
  for (int j = x_cord; j < (x_cord + Char_Horizontal_Columns_Required); j++)
  {
    for (int i = y_cord; i < (y_cord + Char_Verticle_Pages_Required) ; i++)
    {
      setCursor(j, i);
      int array_index = (char_start_in_array + ((j - x_cord) * Char_Verticle_Pages_Required)) + (i - y_cord);
      writeData(MS_Gothic12x24[array_index]);
    }
  }
  I2C_stop();                             // stop transmission
}



int main(void)
{
  Delay_Init();
	//USART_Printf_Init(115200);
	//printf("SystemClk:%d\r\n",SystemCoreClock);

	// Setup internal peripherals
	I2C_init();
  
	oled_begin();
  setCursor(0,0);
  //send data in array to display
  //print_char('B',0,0);
  //print_char1();
    //send data in array to display
 print_char('J', 0,1);
  
    GPIO_Toggle_INIT();
    u8 i = 0;
    while(1) {
        Delay_Ms(500);
        GPIO_WriteBit(GPIOD, GPIO_Pin_0, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
    }
}
