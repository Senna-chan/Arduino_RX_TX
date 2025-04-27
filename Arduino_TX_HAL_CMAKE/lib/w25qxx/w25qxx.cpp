
#include "w25qxx.hpp"
#include "w25qxxConf.h"

#if (_W25QXX_DEBUG == 1)
#include <stdio.h>
#endif

#define W25QXX_DUMMY_BYTE 0xA5

// ###################################################################################################################
uint8_t W25qxx::readWriteSPI(uint8_t Data) {
    uint8_t ret;
    HAL_SPI_TransmitReceive(_hspi, &Data, &ret, 1, 100);
    return ret;
}
// ###################################################################################################################
uint32_t W25qxx::ReadID(void) {
    uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);
    readWriteSPI(0x9F);
    Temp0 = readWriteSPI(W25QXX_DUMMY_BYTE);
    Temp1 = readWriteSPI(W25QXX_DUMMY_BYTE);
    Temp2 = readWriteSPI(W25QXX_DUMMY_BYTE);
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
    Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
    return Temp;
}
// ###################################################################################################################
void W25qxx::ReadUniqID(void) {
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);
    readWriteSPI(0x4B);
    for (uint8_t i = 0; i < 4; i++) {
        readWriteSPI(W25QXX_DUMMY_BYTE);
    }
    for (uint8_t i = 0; i < 8; i++) {
        UniqID[i] = readWriteSPI(W25QXX_DUMMY_BYTE);
    }
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
}
// ###################################################################################################################
void W25qxx::WriteEnable(void) {
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);
    readWriteSPI(0x06);
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
}
// ###################################################################################################################
void W25qxx::WriteDisable(void) {
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);
    readWriteSPI(0x04);
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
}
// ###################################################################################################################
uint8_t W25qxx::ReadStatusRegister(uint8_t SelectStatusRegister_1_2_3) {
    uint8_t status = 0;
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);
    if (SelectStatusRegister_1_2_3 == 1) {
        readWriteSPI(0x05);
        status = readWriteSPI(W25QXX_DUMMY_BYTE);
        StatusRegister1 = status;
    } else if (SelectStatusRegister_1_2_3 == 2) {
        readWriteSPI(0x35);
        status = readWriteSPI(W25QXX_DUMMY_BYTE);
        StatusRegister2 = status;
    } else {
        readWriteSPI(0x15);
        status = readWriteSPI(W25QXX_DUMMY_BYTE);
        StatusRegister3 = status;
    }
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
    return status;
}
// ###################################################################################################################
void W25qxx::WriteStatusRegister(uint8_t SelectStatusRegister_1_2_3, uint8_t Data) {
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);
    if (SelectStatusRegister_1_2_3 == 1) {
        readWriteSPI(0x01);
        StatusRegister1 = Data;
    } else if (SelectStatusRegister_1_2_3 == 2) {
        readWriteSPI(0x31);
        StatusRegister2 = Data;
    } else {
        readWriteSPI(0x11);
        StatusRegister3 = Data;
    }
    readWriteSPI(Data);
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
}
// ###################################################################################################################
void W25qxx::WaitForWriteEnd(void) {
    HAL_Delay(1);
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);
    readWriteSPI(0x05);
    do {
        StatusRegister1 = readWriteSPI(W25QXX_DUMMY_BYTE);
        HAL_Delay(1);
    } while ((StatusRegister1 & 0x01) == 0x01);
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
}
// ###################################################################################################################
bool W25qxx::Init(SPI_HandleTypeDef* hspi, GPIO_TypeDef* CS_GPIO, uint32_t CS_Pin) {
    _hspi = hspi;
    _CS_GPIO = CS_GPIO;
    _CS_Pin = CS_Pin;
    Lock = 1;
    while (HAL_GetTick() < 100) {
        HAL_Delay(1);
    }
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
    HAL_Delay(100);
    uint32_t id;
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx Init Begin...\r\n");
#endif
    id = ReadID();

#if (_W25QXX_DEBUG == 1)
    printf("w25qxx ID:0x%X\r\n", id);
#endif
    switch (id & 0x000000FF) {
    case 0x20: // 	w25q512
        ID = W25Q512;
        BlockCount = 1024;
#if (_W25QXX_DEBUG == 1)
        printf("w25qxx Chip: w25q512\r\n");
#endif
        break;
    case 0x19: // 	w25q256
        ID = W25Q256;
        BlockCount = 512;
#if (_W25QXX_DEBUG == 1)
        printf("w25qxx Chip: w25q256\r\n");
#endif
        break;
    case 0x18: // 	w25q128
        ID = W25Q128;
        BlockCount = 256;
#if (_W25QXX_DEBUG == 1)
        printf("w25qxx Chip: w25q128\r\n");
#endif
        break;
    case 0x17: //	w25q64
        ID = W25Q64;
        BlockCount = 128;
#if (_W25QXX_DEBUG == 1)
        printf("w25qxx Chip: w25q64\r\n");
#endif
        break;
    case 0x16: //	w25q32
        ID = W25Q32;
        BlockCount = 64;
#if (_W25QXX_DEBUG == 1)
        printf("w25qxx Chip: w25q32\r\n");
#endif
        break;
    case 0x15: //	w25q16
        ID = W25Q16;
        BlockCount = 32;
#if (_W25QXX_DEBUG == 1)
        printf("w25qxx Chip: w25q16\r\n");
#endif
        break;
    case 0x14: //	w25q80
        ID = W25Q80;
        BlockCount = 16;
#if (_W25QXX_DEBUG == 1)
        printf("w25qxx Chip: w25q80\r\n");
#endif
        break;
    case 0x13: //	w25q40
        ID = W25Q40;
        BlockCount = 8;
#if (_W25QXX_DEBUG == 1)
        printf("w25qxx Chip: w25q40\r\n");
#endif
        break;
    case 0x12: //	w25q20
        ID = W25Q20;
        BlockCount = 4;
#if (_W25QXX_DEBUG == 1)
        printf("w25qxx Chip: w25q20\r\n");
#endif
        break;
    case 0x11: //	w25q10
        ID = W25Q10;
        BlockCount = 2;
#if (_W25QXX_DEBUG == 1)
        printf("w25qxx Chip: w25q10\r\n");
#endif
        break;
    default:
#if (_W25QXX_DEBUG == 1)
        printf("w25qxx Unknown ID\r\n");
#endif
        Lock = 0;
        return false;
    }
    PageSize = 256;
    SectorSize = 0x1000;
    SectorCount = BlockCount * 16;
    PageCount = (SectorCount * SectorSize) / PageSize;
    BlockSize = SectorSize * 16;
    CapacityInKiloByte = (SectorCount * SectorSize) / 1024;
    W25qxx::ReadUniqID();
    W25qxx::ReadStatusRegister(1);
    W25qxx::ReadStatusRegister(2);
    W25qxx::ReadStatusRegister(3);
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx Page Size: %d Bytes\r\n", PageSize);
    printf("w25qxx Page Count: %d\r\n", PageCount);
    printf("w25qxx Sector Size: %d Bytes\r\n", SectorSize);
    printf("w25qxx Sector Count: %d\r\n", SectorCount);
    printf("w25qxx Block Size: %d Bytes\r\n", BlockSize);
    printf("w25qxx Block Count: %d\r\n", BlockCount);
    printf("w25qxx Capacity: %d KiloBytes\r\n", CapacityInKiloByte);
    printf("w25qxx Init Done\r\n");
#endif
    Lock = 0;
    return true;
}
// ###################################################################################################################
void W25qxx::EraseChip(void) {
    while (Lock == 1) {
        HAL_Delay(1);
    }
    Lock = 1;
#if (_W25QXX_DEBUG == 1)
    uint32_t StartTime = HAL_GetTick();
    printf("w25qxx EraseChip Begin...\r\n");
#endif
    W25qxx::WriteEnable();
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);
    readWriteSPI(0xC7);
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
    W25qxx::WaitForWriteEnd();
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx EraseBlock done after %d ms!\r\n", HAL_GetTick() - StartTime);
#endif
    HAL_Delay(10);
    Lock = 0;
}
// ###################################################################################################################
void W25qxx::EraseSector(uint32_t SectorAddr) {
    while (Lock == 1) {
        HAL_Delay(1);
    }
    Lock = 1;
#if (_W25QXX_DEBUG == 1)
    uint32_t StartTime = HAL_GetTick();
    printf("w25qxx EraseSector %d Begin...\r\n", SectorAddr);
#endif
    W25qxx::WaitForWriteEnd();
    SectorAddr = SectorAddr * SectorSize;
    W25qxx::WriteEnable();
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);
    if (ID >= W25Q256) {
        readWriteSPI(0x21);
        readWriteSPI((SectorAddr & 0xFF000000) >> 24);
    } else {
        readWriteSPI(0x20);
    }
    readWriteSPI((SectorAddr & 0xFF0000) >> 16);
    readWriteSPI((SectorAddr & 0xFF00) >> 8);
    readWriteSPI(SectorAddr & 0xFF);
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
    W25qxx::WaitForWriteEnd();
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx EraseSector done after %d ms\r\n", HAL_GetTick() - StartTime);
#endif
    HAL_Delay(1);
    Lock = 0;
}
// ###################################################################################################################
void W25qxx::EraseBlock(uint32_t BlockAddr) {
    while (Lock == 1) {
        HAL_Delay(1);
    }
    Lock = 1;
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx EraseBlock %d Begin...\r\n", BlockAddr);
    HAL_Delay(100);
    uint32_t StartTime = HAL_GetTick();
#endif
    W25qxx::WaitForWriteEnd();
    BlockAddr = BlockAddr * SectorSize * 16;
    W25qxx::WriteEnable();
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);
    if (ID >= W25Q256) {
        readWriteSPI(0xDC);
        readWriteSPI((BlockAddr & 0xFF000000) >> 24);
    } else {
        readWriteSPI(0xD8);
    }
    readWriteSPI((BlockAddr & 0xFF0000) >> 16);
    readWriteSPI((BlockAddr & 0xFF00) >> 8);
    readWriteSPI(BlockAddr & 0xFF);
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
    W25qxx::WaitForWriteEnd();
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx EraseBlock done after %d ms\r\n", HAL_GetTick() - StartTime);
    HAL_Delay(100);
#endif
    HAL_Delay(1);
    Lock = 0;
}
// ###################################################################################################################
uint32_t W25qxx::PageToSector(uint32_t PageAddress) {
    return ((PageAddress * PageSize) / SectorSize);
}
// ###################################################################################################################
uint32_t W25qxx::PageToBlock(uint32_t PageAddress) {
    return ((PageAddress * PageSize) / BlockSize);
}
// ###################################################################################################################
uint32_t W25qxx::SectorToBlock(uint32_t SectorAddress) {
    return ((SectorAddress * SectorSize) / BlockSize);
}
// ###################################################################################################################
uint32_t W25qxx::SectorToPage(uint32_t SectorAddress) {
    return (SectorAddress * SectorSize) / PageSize;
}
// ###################################################################################################################
uint32_t W25qxx::BlockToPage(uint32_t BlockAddress) {
    return (BlockAddress * BlockSize) / PageSize;
}
// ###################################################################################################################
bool W25qxx::IsEmptyPage(uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_PageSize) {
    while (Lock == 1) {
        HAL_Delay(1);
    }
    Lock = 1;
    if (((NumByteToCheck_up_to_PageSize + OffsetInByte) > PageSize) || (NumByteToCheck_up_to_PageSize == 0)) {
        NumByteToCheck_up_to_PageSize = PageSize - OffsetInByte;
    }
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx CheckPage:%d, Offset:%d, Bytes:%d begin...\r\n", Page_Address, OffsetInByte, NumByteToCheck_up_to_PageSize);
    HAL_Delay(100);
    uint32_t StartTime = HAL_GetTick();
#endif
    uint8_t pBuffer[32];
    uint32_t WorkAddress;
    uint32_t i;
    for (i = OffsetInByte; i < PageSize; i += sizeof(pBuffer)) {
        HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);
        WorkAddress = (i + Page_Address * PageSize);
        if (ID >= W25Q256) {
            readWriteSPI(0x0C);
            readWriteSPI((WorkAddress & 0xFF000000) >> 24);
        } else {
            readWriteSPI(0x0B);
        }
        readWriteSPI((WorkAddress & 0xFF0000) >> 16);
        readWriteSPI((WorkAddress & 0xFF00) >> 8);
        readWriteSPI(WorkAddress & 0xFF);
        readWriteSPI(0);
        HAL_SPI_Receive(_hspi, pBuffer, sizeof(pBuffer), 100);
        HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
        for (uint8_t x = 0; x < sizeof(pBuffer); x++) {
            if (pBuffer[x] != 0xFF) {
                goto NOT_EMPTY;
            }
        }
    }
    if ((PageSize + OffsetInByte) % sizeof(pBuffer) != 0) {
        i -= sizeof(pBuffer);
        for (; i < PageSize; i++) {
            HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);
            WorkAddress = (i + Page_Address * PageSize);
            readWriteSPI(0x0B);
            if (ID >= W25Q256) {
                readWriteSPI(0x0C);
                readWriteSPI((WorkAddress & 0xFF000000) >> 24);
            } else {
                readWriteSPI(0x0B);
            }
            readWriteSPI((WorkAddress & 0xFF0000) >> 16);
            readWriteSPI((WorkAddress & 0xFF00) >> 8);
            readWriteSPI(WorkAddress & 0xFF);
            readWriteSPI(0);
            HAL_SPI_Receive(_hspi, pBuffer, 1, 100);
            HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
            if (pBuffer[0] != 0xFF) {
                goto NOT_EMPTY;
            }
        }
    }
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx CheckPage is Empty in %d ms\r\n", HAL_GetTick() - StartTime);
    HAL_Delay(100);
#endif
    Lock = 0;
    return true;
NOT_EMPTY:
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx CheckPage is Not Empty in %d ms\r\n", HAL_GetTick() - StartTime);
    HAL_Delay(100);
#endif
    Lock = 0;
    return false;
}
// ###################################################################################################################
bool W25qxx::IsEmptySector(uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_SectorSize) {
    while (Lock == 1) {
        HAL_Delay(1);
    }
    Lock = 1;
    if ((NumByteToCheck_up_to_SectorSize > SectorSize) || (NumByteToCheck_up_to_SectorSize == 0)) {
        NumByteToCheck_up_to_SectorSize = SectorSize;
    }
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx CheckSector:%d, Offset:%d, Bytes:%d begin...\r\n", Sector_Address, OffsetInByte, NumByteToCheck_up_to_SectorSize);
    HAL_Delay(100);
    uint32_t StartTime = HAL_GetTick();
#endif
    uint8_t pBuffer[32];
    uint32_t WorkAddress;
    uint32_t i;
    for (i = OffsetInByte; i < SectorSize; i += sizeof(pBuffer)) {
        HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);
        WorkAddress = (i + Sector_Address * SectorSize);
        if (ID >= W25Q256) {
            readWriteSPI(0x0C);
            readWriteSPI((WorkAddress & 0xFF000000) >> 24);
        } else {
            readWriteSPI(0x0B);
        }
        readWriteSPI((WorkAddress & 0xFF0000) >> 16);
        readWriteSPI((WorkAddress & 0xFF00) >> 8);
        readWriteSPI(WorkAddress & 0xFF);
        readWriteSPI(0);
        HAL_SPI_Receive(_hspi, pBuffer, sizeof(pBuffer), 100);
        HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
        for (uint8_t x = 0; x < sizeof(pBuffer); x++) {
            if (pBuffer[x] != 0xFF) {
                goto NOT_EMPTY;
            }
        }
    }
    if ((SectorSize + OffsetInByte) % sizeof(pBuffer) != 0) {
        i -= sizeof(pBuffer);
        for (; i < SectorSize; i++) {
            HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);
            WorkAddress = (i + Sector_Address * SectorSize);
            if (ID >= W25Q256) {
                readWriteSPI(0x0C);
                readWriteSPI((WorkAddress & 0xFF000000) >> 24);
            } else {
                readWriteSPI(0x0B);
            }
            readWriteSPI((WorkAddress & 0xFF0000) >> 16);
            readWriteSPI((WorkAddress & 0xFF00) >> 8);
            readWriteSPI(WorkAddress & 0xFF);
            readWriteSPI(0);
            HAL_SPI_Receive(_hspi, pBuffer, 1, 100);
            HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
            if (pBuffer[0] != 0xFF) {
                goto NOT_EMPTY;
            }
        }
    }
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx CheckSector is Empty in %d ms\r\n", HAL_GetTick() - StartTime);
    HAL_Delay(100);
#endif
    Lock = 0;
    return true;
NOT_EMPTY:
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx CheckSector is Not Empty in %d ms\r\n", HAL_GetTick() - StartTime);
    HAL_Delay(100);
#endif
    Lock = 0;
    return false;
}
// ###################################################################################################################
bool W25qxx::IsEmptyBlock(uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_BlockSize) {
    while (Lock == 1) {
        HAL_Delay(1);
    }
    Lock = 1;
    if ((NumByteToCheck_up_to_BlockSize > BlockSize) || (NumByteToCheck_up_to_BlockSize == 0)) {
        NumByteToCheck_up_to_BlockSize = BlockSize;
    }
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx CheckBlock:%d, Offset:%d, Bytes:%d begin...\r\n", Block_Address, OffsetInByte, NumByteToCheck_up_to_BlockSize);
    HAL_Delay(100);
    uint32_t StartTime = HAL_GetTick();
#endif
    uint8_t pBuffer[32];
    uint32_t WorkAddress;
    uint32_t i;
    for (i = OffsetInByte; i < BlockSize; i += sizeof(pBuffer)) {
        HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);
        WorkAddress = (i + Block_Address * BlockSize);

        if (ID >= W25Q256) {
            readWriteSPI(0x0C);
            readWriteSPI((WorkAddress & 0xFF000000) >> 24);
        } else {
            readWriteSPI(0x0B);
        }
        readWriteSPI((WorkAddress & 0xFF0000) >> 16);
        readWriteSPI((WorkAddress & 0xFF00) >> 8);
        readWriteSPI(WorkAddress & 0xFF);
        readWriteSPI(0);
        HAL_SPI_Receive(_hspi, pBuffer, sizeof(pBuffer), 100);
        HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
        for (uint8_t x = 0; x < sizeof(pBuffer); x++) {
            if (pBuffer[x] != 0xFF) {
                goto NOT_EMPTY;
            }
        }
    }
    if ((BlockSize + OffsetInByte) % sizeof(pBuffer) != 0) {
        i -= sizeof(pBuffer);
        for (; i < BlockSize; i++) {
            HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);
            WorkAddress = (i + Block_Address * BlockSize);

            if (ID >= W25Q256) {
                readWriteSPI(0x0C);
                readWriteSPI((WorkAddress & 0xFF000000) >> 24);
            } else {
                readWriteSPI(0x0B);
            }
            readWriteSPI((WorkAddress & 0xFF0000) >> 16);
            readWriteSPI((WorkAddress & 0xFF00) >> 8);
            readWriteSPI(WorkAddress & 0xFF);
            readWriteSPI(0);
            HAL_SPI_Receive(_hspi, pBuffer, 1, 100);
            HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
            if (pBuffer[0] != 0xFF) {
                goto NOT_EMPTY;
            }
        }
    }
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx CheckBlock is Empty in %d ms\r\n", HAL_GetTick() - StartTime);
    HAL_Delay(100);
#endif
    Lock = 0;
    return true;
NOT_EMPTY:
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx CheckBlock is Not Empty in %d ms\r\n", HAL_GetTick() - StartTime);
    HAL_Delay(100);
#endif
    Lock = 0;
    return false;
}
// ###################################################################################################################
void W25qxx::WriteByte(uint8_t pBuffer, uint32_t WriteAddr_inBytes) {
    while (Lock == 1) {
        HAL_Delay(1);
    }
    Lock = 1;
#if (_W25QXX_DEBUG == 1)
    uint32_t StartTime = HAL_GetTick();
    printf("w25qxx WriteByte 0x%02X at address %d begin...", pBuffer, WriteAddr_inBytes);
#endif
    W25qxx::WaitForWriteEnd();
    W25qxx::WriteEnable();
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);

    if (ID >= W25Q256) {
        readWriteSPI(0x12);
        readWriteSPI((WriteAddr_inBytes & 0xFF000000) >> 24);
    } else {
        readWriteSPI(0x02);
    }
    readWriteSPI((WriteAddr_inBytes & 0xFF0000) >> 16);
    readWriteSPI((WriteAddr_inBytes & 0xFF00) >> 8);
    readWriteSPI(WriteAddr_inBytes & 0xFF);
    readWriteSPI(pBuffer);
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
    W25qxx::WaitForWriteEnd();
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx WriteByte done after %d ms\r\n", HAL_GetTick() - StartTime);
#endif
    Lock = 0;
}
// ###################################################################################################################
void W25qxx::WritePage(uint8_t* pBuffer, uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_PageSize) {
    while (Lock == 1) {
        HAL_Delay(1);
    }
    Lock = 1;
    if (((NumByteToWrite_up_to_PageSize + OffsetInByte) > PageSize) || (NumByteToWrite_up_to_PageSize == 0)) {
        NumByteToWrite_up_to_PageSize = PageSize - OffsetInByte;
    }
    if ((OffsetInByte + NumByteToWrite_up_to_PageSize) > PageSize) {
        NumByteToWrite_up_to_PageSize = PageSize - OffsetInByte;
    }
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx WritePage:%d, Offset:%d ,Writes %d Bytes, begin...\r\n", Page_Address, OffsetInByte, NumByteToWrite_up_to_PageSize);
    HAL_Delay(100);
    uint32_t StartTime = HAL_GetTick();
#endif
    W25qxx::WaitForWriteEnd();
    W25qxx::WriteEnable();
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);
    Page_Address = (Page_Address * PageSize) + OffsetInByte;
    if (ID >= W25Q256) {
        readWriteSPI(0x12);
        readWriteSPI((Page_Address & 0xFF000000) >> 24);
    } else {
        readWriteSPI(0x02);
    }
    readWriteSPI((Page_Address & 0xFF0000) >> 16);
    readWriteSPI((Page_Address & 0xFF00) >> 8);
    readWriteSPI(Page_Address & 0xFF);
    HAL_SPI_Transmit(_hspi, pBuffer, NumByteToWrite_up_to_PageSize, 100);
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
    W25qxx::WaitForWriteEnd();
#if (_W25QXX_DEBUG == 1)
    StartTime = HAL_GetTick() - StartTime;
    for (uint32_t i = 0; i < NumByteToWrite_up_to_PageSize; i++) {
        if ((i % 8 == 0) && (i > 2)) {
            printf("\r\n");
            HAL_Delay(10);
        }
        printf("0x%02X,", pBuffer[i]);
    }
    printf("\r\n");
    printf("w25qxx WritePage done after %d ms\r\n", StartTime);
    HAL_Delay(100);
#endif
    HAL_Delay(1);
    Lock = 0;
}
// ###################################################################################################################
void W25qxx::WriteSector(uint8_t* pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_SectorSize) {
    if ((NumByteToWrite_up_to_SectorSize > SectorSize) || (NumByteToWrite_up_to_SectorSize == 0)) {
        NumByteToWrite_up_to_SectorSize = SectorSize;
    }
#if (_W25QXX_DEBUG == 1)
    printf("+++w25qxx WriteSector:%d, Offset:%d ,Write %d Bytes, begin...\r\n", Sector_Address, OffsetInByte, NumByteToWrite_up_to_SectorSize);
    HAL_Delay(100);
#endif
    if (OffsetInByte >= SectorSize) {
#if (_W25QXX_DEBUG == 1)
        printf("---w25qxx WriteSector Faild!\r\n");
        HAL_Delay(100);
#endif
        return;
    }
    uint32_t StartPage;
    int32_t BytesToWrite;
    uint32_t LocalOffset;
    if ((OffsetInByte + NumByteToWrite_up_to_SectorSize) > SectorSize) {
        BytesToWrite = SectorSize - OffsetInByte;
    } else {
        BytesToWrite = NumByteToWrite_up_to_SectorSize;
    }
    StartPage = W25qxx::SectorToPage(Sector_Address) + (OffsetInByte / PageSize);
    LocalOffset = OffsetInByte % PageSize;
    do {
        W25qxx::WritePage(pBuffer, StartPage, LocalOffset, BytesToWrite);
        StartPage++;
        BytesToWrite -= PageSize - LocalOffset;
        pBuffer += PageSize - LocalOffset;
        LocalOffset = 0;
    } while (BytesToWrite > 0);
#if (_W25QXX_DEBUG == 1)
    printf("---w25qxx WriteSector Done\r\n");
    HAL_Delay(100);
#endif
}
// ###################################################################################################################
void W25qxx::WriteBlock(uint8_t* pBuffer, uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_BlockSize) {
    if ((NumByteToWrite_up_to_BlockSize > BlockSize) || (NumByteToWrite_up_to_BlockSize == 0)) {
        NumByteToWrite_up_to_BlockSize = BlockSize;
    }
#if (_W25QXX_DEBUG == 1)
    printf("+++w25qxx WriteBlock:%d, Offset:%d ,Write %d Bytes, begin...\r\n", Block_Address, OffsetInByte, NumByteToWrite_up_to_BlockSize);
    HAL_Delay(100);
#endif
    if (OffsetInByte >= BlockSize) {
#if (_W25QXX_DEBUG == 1)
        printf("---w25qxx WriteBlock Faild!\r\n");
        HAL_Delay(100);
#endif
        return;
    }
    int32_t BytesToWrite;
    if ((OffsetInByte + NumByteToWrite_up_to_BlockSize) > BlockSize) {
        BytesToWrite = BlockSize - OffsetInByte;
    } else {
        BytesToWrite = NumByteToWrite_up_to_BlockSize;
    }
    uint32_t StartPage = BlockToPage(Block_Address) + (OffsetInByte / PageSize);
    uint32_t LocalOffset = OffsetInByte % PageSize;
    do {
        W25qxx::WritePage(pBuffer, StartPage, LocalOffset, BytesToWrite);
        StartPage++;
        BytesToWrite -= PageSize - LocalOffset;
        pBuffer += PageSize - LocalOffset;
        LocalOffset = 0;
    } while (BytesToWrite > 0);
#if (_W25QXX_DEBUG == 1)
    printf("---w25qxx WriteBlock Done\r\n");
    HAL_Delay(100);
#endif
}
// ###################################################################################################################
void W25qxx::ReadByte(uint8_t* pBuffer, uint32_t Bytes_Address) {
    while (Lock == 1) {
        HAL_Delay(1);
    }
    Lock = 1;
#if (_W25QXX_DEBUG == 1)
    uint32_t StartTime = HAL_GetTick();
    printf("w25qxx ReadByte at address %d begin...\r\n", Bytes_Address);
#endif
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);

    if (ID >= W25Q256) {
        readWriteSPI(0x0C);
        readWriteSPI((Bytes_Address & 0xFF000000) >> 24);
    } else {
        readWriteSPI(0x0B);
    }
    readWriteSPI((Bytes_Address & 0xFF0000) >> 16);
    readWriteSPI((Bytes_Address & 0xFF00) >> 8);
    readWriteSPI(Bytes_Address & 0xFF);
    readWriteSPI(0);
    *pBuffer = readWriteSPI(W25QXX_DUMMY_BYTE);
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx ReadByte 0x%02X done after %d ms\r\n", *pBuffer, HAL_GetTick() - StartTime);
#endif
    Lock = 0;
}
// ###################################################################################################################
void W25qxx::ReadBytes(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead) {
    while (Lock == 1) {
        HAL_Delay(1);
    }
    Lock = 1;
#if (_W25QXX_DEBUG == 1)
    uint32_t StartTime = HAL_GetTick();
    printf("w25qxx ReadBytes at Address:%d, %d Bytes  begin...\r\n", ReadAddr, NumByteToRead);
#endif
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);

    if (ID >= W25Q256) {
        readWriteSPI(0x0C);
        readWriteSPI((ReadAddr & 0xFF000000) >> 24);
    } else {
        readWriteSPI(0x0B);
    }
    readWriteSPI((ReadAddr & 0xFF0000) >> 16);
    readWriteSPI((ReadAddr & 0xFF00) >> 8);
    readWriteSPI(ReadAddr & 0xFF);
    readWriteSPI(0);
    HAL_SPI_Receive(_hspi, pBuffer, NumByteToRead, 2000);
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
#if (_W25QXX_DEBUG == 1)
    StartTime = HAL_GetTick() - StartTime;
    for (uint32_t i = 0; i < NumByteToRead; i++) {
        if ((i % 8 == 0) && (i > 2)) {
            printf("\r\n");
            HAL_Delay(10);
        }
        printf("0x%02X,", pBuffer[i]);
    }
    printf("\r\n");
    printf("w25qxx ReadBytes done after %d ms\r\n", StartTime);
    HAL_Delay(100);
#endif
    HAL_Delay(1);
    Lock = 0;
}
// ###################################################################################################################
void W25qxx::ReadPage(uint8_t* pBuffer, uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_PageSize) {
    while (Lock == 1) {
        HAL_Delay(1);
    }
    Lock = 1;
    if ((NumByteToRead_up_to_PageSize > PageSize) || (NumByteToRead_up_to_PageSize == 0)) {
        NumByteToRead_up_to_PageSize = PageSize;
    }
    if ((OffsetInByte + NumByteToRead_up_to_PageSize) > PageSize) {
        NumByteToRead_up_to_PageSize = PageSize - OffsetInByte;
    }
#if (_W25QXX_DEBUG == 1)
    printf("w25qxx ReadPage:%d, Offset:%d ,Read %d Bytes, begin...\r\n", Page_Address, OffsetInByte, NumByteToRead_up_to_PageSize);
    HAL_Delay(100);
    uint32_t StartTime = HAL_GetTick();
#endif
    Page_Address = Page_Address * PageSize + OffsetInByte;
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_RESET);
    if (ID >= W25Q256) {
        readWriteSPI(0x0C);
        readWriteSPI((Page_Address & 0xFF000000) >> 24);
    } else {
        readWriteSPI(0x0B);
    }
    readWriteSPI((Page_Address & 0xFF0000) >> 16);
    readWriteSPI((Page_Address & 0xFF00) >> 8);
    readWriteSPI(Page_Address & 0xFF);
    readWriteSPI(0);
    HAL_SPI_Receive(_hspi, pBuffer, NumByteToRead_up_to_PageSize, 100);
    HAL_GPIO_WritePin(_CS_GPIO, _CS_Pin, GPIO_PIN_SET);
#if (_W25QXX_DEBUG == 1)
    StartTime = HAL_GetTick() - StartTime;
    for (uint32_t i = 0; i < NumByteToRead_up_to_PageSize; i++) {
        if ((i % 8 == 0) && (i > 2)) {
            printf("\r\n");
            HAL_Delay(10);
        }
        printf("0x%02X,", pBuffer[i]);
    }
    printf("\r\n");
    printf("w25qxx ReadPage done after %d ms\r\n", StartTime);
    HAL_Delay(100);
#endif
    HAL_Delay(1);
    Lock = 0;
}
// ###################################################################################################################
void W25qxx::ReadSector(uint8_t* pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_SectorSize) {
    if ((NumByteToRead_up_to_SectorSize > SectorSize) || (NumByteToRead_up_to_SectorSize == 0)) {
        NumByteToRead_up_to_SectorSize = SectorSize;
    }
#if (_W25QXX_DEBUG == 1)
    printf("+++w25qxx ReadSector:%d, Offset:%d ,Read %d Bytes, begin...\r\n", Sector_Address, OffsetInByte, NumByteToRead_up_to_SectorSize);
    HAL_Delay(100);
#endif
    if (OffsetInByte >= SectorSize) {
#if (_W25QXX_DEBUG == 1)
        printf("---w25qxx ReadSector Faild!\r\n");
        HAL_Delay(100);
#endif
        return;
    }
    uint32_t StartPage;
    int32_t BytesToRead;
    uint32_t LocalOffset;
    if ((OffsetInByte + NumByteToRead_up_to_SectorSize) > SectorSize) {
        BytesToRead = SectorSize - OffsetInByte;
    } else {
        BytesToRead = NumByteToRead_up_to_SectorSize;
    }
    StartPage = SectorToPage(Sector_Address) + (OffsetInByte / PageSize);
    LocalOffset = OffsetInByte % PageSize;
    do {
        ReadPage(pBuffer, StartPage, LocalOffset, BytesToRead);
        StartPage++;
        BytesToRead -= PageSize - LocalOffset;
        pBuffer += PageSize - LocalOffset;
        LocalOffset = 0;
    } while (BytesToRead > 0);
#if (_W25QXX_DEBUG == 1)
    printf("---w25qxx ReadSector Done\r\n");
    HAL_Delay(100);
#endif
}
// ###################################################################################################################
void W25qxx::ReadBlock(uint8_t* pBuffer, uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_BlockSize) {
    if ((NumByteToRead_up_to_BlockSize > BlockSize) || (NumByteToRead_up_to_BlockSize == 0)) {
        NumByteToRead_up_to_BlockSize = BlockSize;
    }
#if (_W25QXX_DEBUG == 1)
    printf("+++w25qxx ReadBlock:%d, Offset:%d ,Read %d Bytes, begin...\r\n", Block_Address, OffsetInByte, NumByteToRead_up_to_BlockSize);
    HAL_Delay(100);
#endif
    if (OffsetInByte >= BlockSize) {
#if (_W25QXX_DEBUG == 1)
        printf("w25qxx ReadBlock Faild!\r\n");
        HAL_Delay(100);
#endif
        return;
    }
    uint32_t StartPage;
    int32_t BytesToRead;
    uint32_t LocalOffset;
    if ((OffsetInByte + NumByteToRead_up_to_BlockSize) > BlockSize) {
        BytesToRead = BlockSize - OffsetInByte;
    } else {
        BytesToRead = NumByteToRead_up_to_BlockSize;
    }
    StartPage = W25qxx::BlockToPage(Block_Address) + (OffsetInByte / PageSize);
    LocalOffset = OffsetInByte % PageSize;
    do {
        W25qxx::ReadPage(pBuffer, StartPage, LocalOffset, BytesToRead);
        StartPage++;
        BytesToRead -= PageSize - LocalOffset;
        pBuffer += PageSize - LocalOffset;
        LocalOffset = 0;
    } while (BytesToRead > 0);
#if (_W25QXX_DEBUG == 1)
    printf("---w25qxx ReadBlock Done\r\n");
    HAL_Delay(100);
#endif
}
// ###################################################################################################################
