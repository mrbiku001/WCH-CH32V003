// Please note PD7 is by default is configured as MCU reset pin, you need to configure it as GPIO by configuring it with WCH Link Programmer Utility or in the code.
// via code
FLASH_Unlock();
FLASH_EraseOptionBytes();
FLASH_UserOptionByteConfig(OB_STOP_NoRST, OB_STDBY_NoRST, OB_RST_NoEN, OB_PowerON_Start_Mode_USER);
FLASH_Unlock();