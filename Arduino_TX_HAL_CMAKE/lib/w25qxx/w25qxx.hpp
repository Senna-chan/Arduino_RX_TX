#ifndef W25QXX_H
#define W25QXX_H

#ifdef __cplusplus
extern "C" {
#endif
#include <main.h>

#ifdef __cplusplus
    }
#endif

class W25qxx {
public:
    typedef enum {
        W25Q10 = 1,
        W25Q20,
        W25Q40,
        W25Q80,
        W25Q16,
        W25Q32,
        W25Q64,
        W25Q128,
        W25Q256,
        W25Q512,
    } W25QXX_ID_t;

    bool Init(SPI_HandleTypeDef* hspi, GPIO_TypeDef* CS_GPIO, uint32_t CS_Pin);
    void EraseChip();
    void EraseSector(uint32_t sector_address);
    void EraseBlock(uint32_t block_address);

    uint32_t PageToSector(uint32_t page_address);
    uint32_t PageToBlock(uint32_t block_address);

    uint32_t SectorToBlock(uint32_t SectorAddress);
    uint32_t SectorToPage(uint32_t SectorAddress);
    uint32_t BlockToPage(uint32_t BlockAddress);
    bool IsEmptyPage(uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_PageSize);
    bool IsEmptySector(uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_SectorSize);
    bool IsEmptyBlock(uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToCheck_up_to_BlockSize);

    void WriteByte(uint8_t pBuffer, uint32_t Bytes_Address);
    void WritePage(uint8_t* pBuffer, uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_PageSize);
    void WriteSector(uint8_t* pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_SectorSize);
    void WriteBlock(uint8_t* pBuffer, uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToWrite_up_to_BlockSize);

    void ReadByte(uint8_t* pBuffer, uint32_t Bytes_Address);
    void ReadBytes(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);
    void ReadPage(uint8_t* pBuffer, uint32_t Page_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_PageSize);
    void ReadSector(uint8_t* pBuffer, uint32_t Sector_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_SectorSize);
    void ReadBlock(uint8_t* pBuffer, uint32_t Block_Address, uint32_t OffsetInByte, uint32_t NumByteToRead_up_to_BlockSize);

private:
    uint8_t readWriteSPI(uint8_t data);
    uint32_t ReadID();
    void ReadUniqID();
    void WriteEnable();
    void WriteDisable();
    uint8_t ReadStatusRegister(uint8_t SelectStatusRegister_1_2_3);
    void WriteStatusRegister(uint8_t SelectStatusRegister_1_2_3, uint8_t Data);
    void WaitForWriteEnd();
    W25QXX_ID_t ID;
    uint8_t UniqID[8];
    uint16_t PageSize;
    uint32_t PageCount;
    uint32_t SectorSize;
    uint32_t SectorCount;
    uint32_t BlockSize;
    uint32_t BlockCount;
    uint32_t CapacityInKiloByte;
    uint8_t StatusRegister1;
    uint8_t StatusRegister2;
    uint8_t StatusRegister3;
    uint8_t Lock;

    SPI_HandleTypeDef* _hspi;
    GPIO_TypeDef* _CS_GPIO;
    uint32_t _CS_Pin;
};

#endif
