#if ARDUINO
#define DEBUGPRINTF Serial.printf

#elif PIO_UNIT_TESTING
#include <unity.h>
#define DEBUGPRINTF TEST_PRINTF
#else
#include <stdarg.h>
#include <stdio.h>
#define DEBUGPRINTF CLRPrintf

void CLRPrintf(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);

	vprintf(format, ap);
	va_end(ap);
}
#endif

#include "RobustCommunicationLib.h"

#define IGNORE_CRC

const uint8_t maxReadCyclesPerCall = 20;
uint8_t readCycleCounter = maxReadCyclesPerCall;
bool packetIsBinary = true;
RobustCommunication::BinaryPacket currentBinaryPacket;

RobustCommunication::CharPacket currentCharPacket;
uint16_t charPacketIndex = 0; /*<! Used to keep track of seperate buffers of the char packet */

uint16_t dataBytesToRead = 0;

typedef struct {
	const char* shortName;
	const char* scanfName;
	uint8_t byteSize;
} strTypeToFormat;

const strTypeToFormat strTypeToFormatMap[] = {
	{"u8", "%hhu", 1},
	{"s8", "%hhd", 1},
	{"u16", "%hu", 2},
	{"s16", "%hd", 2},
	{"u32", "%u", 4},
	{"s32", "%d", 4},
	{"u64", "%lu", 8},
	{"s64", "%ld", 8},
	{"int", "%d", 4},
	{"f", "%f", 8},
	{"d", "%f", 8},
	{"hex", "0x%02X", 2},
	{"s", "%s", 0}, // Datasize is dynamic so that why a 0
	{"c", "%c", 1}
};

const char* readStateStr[] = {
	"READING_HEADER",
	"READING_MODULE",
	"READING_COMMAND",
	"READING_STATUS",
	"READING_DATASIZE",
	"READING_CRC",
	"READING_DATA",
	"READING_FOOTER",
	"READING_DONE",
};



bool RobustCommunication::singleThreadLoop()
{
	while (hardware.available() || currentReadState == READING_DONE)
	{
		if (readCycleCounter == 0)
		{
			readCycleCounter = maxReadCyclesPerCall;
			return false;
		}
		readCycleCounter--;

		DEBUGPRINTF("Current read state %s byte to read %c(0x%02X)\n", readStateStr[currentReadState], hardware.peek(), hardware.peek());

		switch (currentReadState)
		{
		case READING_HEADER:
		{
			int b = hardware.read();
			if (b == 0xCC)
			{
				int p = hardware.peek();
				if (p == 0x44)
				{
					p = hardware.read();
					currentBinaryPacket.header = b << 8 | p;
					DEBUGPRINTF("Header found\n");
					currentReadState = READING_MODULE;
					packetIsBinary = true;
				}
				else
				{
					DEBUGPRINTF("Header not found correctly\n");
				}
			}
			else if (b == '@')
			{
				packetIsBinary = false;
				DEBUGPRINTF("Header found\n");
				currentReadState = READING_MODULE;
			}
			else if (b == '?')
			{
				if (hardware.peek() == '\n')
				{
					printHelp();
					currentReadState = READING_MODULE;
				}
			}
			else
			{
				DEBUGPRINTF("Header not found while in header state");
			}
		}
		break;

		default:
			if (packetIsBinary)
			{
				readForBinaryPacket();
			}
			else
			{
				readForCharPacket();
			}
		}
	}

	return true;
}

void RobustCommunication::readForBinaryPacket()
{

	switch (currentReadState)
	{
	case READING_HEADER:
	{
		DEBUGPRINTF("OI, this cannot happen");
	}
	break;

	case READING_MODULE:
	{
		currentBinaryPacket.moduleClass = dataReadBuffer[dataReadBufferIndex++] = hardware.read();
		currentReadState = READING_COMMAND;
	}
	break;

	case READING_COMMAND:
	{
		currentBinaryPacket.command = dataReadBuffer[dataReadBufferIndex++] = hardware.read();
		currentReadState = READING_STATUS;
	}
	break;

	case READING_STATUS:
	{
		currentBinaryPacket.status.binary = dataReadBuffer[dataReadBufferIndex++] = hardware.read();
		currentReadState = READING_DATASIZE;
	}
	break;

	case READING_DATASIZE:
	{
		int b = hardware.read();
		currentBinaryPacket.dataSize = b << 8;
		dataReadBuffer[dataReadBufferIndex++] = b;
		b = hardware.read();
		currentBinaryPacket.dataSize |= b;
		dataReadBuffer[dataReadBufferIndex++] = b;
		dataBytesToRead = currentBinaryPacket.dataSize;
		currentReadState = READING_CRC;
		if (currentBinaryPacket.dataSize != 0)
		{
			currentBinaryPacket.data = (uint8_t*)malloc(currentBinaryPacket.dataSize);
		}
	}
	break;

	case READING_CRC:
	{
		int b = hardware.read();
		currentBinaryPacket.crc = b << 8;
		dataReadBuffer[dataReadBufferIndex++] = b;
		b = hardware.read();
		currentBinaryPacket.crc |= b;
		dataReadBuffer[dataReadBufferIndex++] = b;
		if (dataBytesToRead > 0)
		{
			currentReadState = READING_DATA;
		}
		else
		{
			currentReadState = READING_DONE;
		}
	}
	break;

	case READING_DATA:
	{
		for (int i = 0; i < maxReadCyclesPerCall; i++)
		{
			dataReadBuffer[dataReadBufferIndex++] = hardware.read();
			readCycleCounter--;
			dataBytesToRead--;
			if (dataBytesToRead == 0)
			{
				currentReadState = READING_DONE;
				break;
			}
		}

	}
	break;

	case READING_DONE:
	{
		parseBinaryPacket();
	}
	break;
	}
}

void RobustCommunication::readForCharPacket()
{
	switch (currentReadState)
	{
	case READING_HEADER:
	{
		DEBUGPRINTF("OI, this cannot happen");
	}
	break;

	case READING_MODULE:
	{
		currentCharPacket.moduleName[charPacketIndex++] = hardware.read();
		if (hardware.peek() == charSeperator)
		{
			hardware.read();
			currentReadState = READING_COMMAND;
			charPacketIndex = 0;
		}
	}
	break;

	case READING_COMMAND:
	{
		currentCharPacket.commandName[charPacketIndex++] = hardware.read();
		if (hardware.peek() == charSeperator)
		{
			hardware.read();
			currentReadState = READING_DATA;
			charPacketIndex = 0;
		}
	}
	break;

	case READING_STATUS:
	case READING_DATASIZE:
	case READING_CRC:
	{
		DEBUGPRINTF("OI, these states do not exist for char packets");
	}
	break;

	case READING_DATA:
	{
		currentCharPacket.data[charPacketIndex++] = hardware.read();
		if (hardware.peek() == '\n')
		{
			hardware.read();
			currentReadState = READING_DONE;
			charPacketIndex = 0;
		}
	}
	break;

	case READING_DONE:
	{
		parseCharPacket();
	}
	break;
	}
}

void RobustCommunication::parseBinaryPacket()
{
	bool moduleFound = false;
	bool commandFound = false;
	int defIndex;
	for (defIndex = 0; defIndex < freeDefinitionIndex; defIndex++)
	{
		if (definitions[defIndex].moduleClass == currentBinaryPacket.moduleClass)
		{
			moduleFound = true;
			if (definitions[defIndex].commandClass == currentBinaryPacket.command)
			{
				commandFound = true;
			}
		}
		if (moduleFound && commandFound)
		{
			break;
		}
	}

	if (moduleFound && commandFound)
	{
		if (!definitions[defIndex].commandFunction(&currentBinaryPacket))
		{
			currentBinaryPacket.status.internalError = 1;
		}
	}

	if (!moduleFound)
	{
		currentBinaryPacket.status.unknownModule = 1;
	}
	else if (!commandFound)
	{
		currentBinaryPacket.status.unknownCommand = 1;
	}

	if (!currentBinaryPacket.status.oneshot)
	{
		if (!currentBinaryPacket.status.requestType)
		{
			free(currentBinaryPacket.data);
			currentBinaryPacket.dataSize = 0;
		}
	}

	writeBinaryPacket(&currentBinaryPacket);
	if (currentBinaryPacket.dataSize != 0)
	{
		free(currentBinaryPacket.data);
	}
	currentReadState = READING_HEADER;
}

void RobustCommunication::parseCharPacket()
{
	bool moduleFound = false;
	bool commandFound = false;
	int defIndex;

	for (defIndex = 0; defIndex < freeDefinitionIndex; defIndex++)
	{
		if (!strcmp(definitions[defIndex].moduleName, currentCharPacket.moduleName))
		{
			moduleFound = true;
			if (!strcmp(definitions[defIndex].commandName, currentCharPacket.commandName))
			{
				commandFound = true;
			}
		}
		if (moduleFound && commandFound)
		{
			break;
		}
	}

	if (moduleFound && commandFound)
	{
		currentBinaryPacket.dataSize = 0;
		currentBinaryPacket.data = (uint8_t*)malloc(2024);
		uint8_t* bufPtr = currentBinaryPacket.data;
		const char* data = currentCharPacket.data;
		const char* dataP = data;

		char* formatStrTok = strdup(definitions[defIndex].sscanfFormat);

		char* formatToken;
		formatToken = strtok(formatStrTok, ",");
		while (formatToken != NULL)
		{
			char format[20];
			char* formatP = format;

			strcpy(formatP, formatToken);
			formatP += strlen(formatToken);

			strcpy(formatP, "%n%[^,]");

			int charsRead = 0;
			int sscanfResult = sscanf(dataP, format, bufPtr, &charsRead);
			if (sscanfResult != 1)
			{
				DEBUGPRINTF("Something went wrong\n");
				break;
			}
			if (charsRead == 0)
			{
				DEBUGPRINTF("Uh... didn't read anything\n");
			}
			dataP += charsRead;
			bufPtr += charsRead;
			if (format[1] == 's') // We have read a string
			{
				currentBinaryPacket.dataSize += charsRead;
			}
			if (*dataP == ',')
			{
				dataP++;
			}
			formatToken = strtok(NULL, ",");
		}
		free(formatStrTok);
		currentBinaryPacket.dataSize += definitions[defIndex].expectedDataSize;
		currentBinaryPacket.status.ack = 1;
		if (!definitions[defIndex].commandFunction(&currentBinaryPacket))
		{
			currentBinaryPacket.status.internalError = 1;
		}
	}

	DEBUGPRINTF("WORK IN PROGRESS!");

	//writeBinaryPacket(&currentBinaryPacket);
	if (currentBinaryPacket.dataSize != 0)
	{
		free(currentBinaryPacket.data);
	}
	currentReadState = READING_HEADER;
}

void RobustCommunication::attachHardwareAccess(HardwareAccess access)
{
	//if(access.read == nullptr)  Error_Handler();
	//if(access.write == nullptr)  Error_Handler();
	//if(access.available == nullptr)  Error_Handler();
	hardware = access;
}

bool RobustCommunication::binaryPacketToDataArray(RobustCommunication::BinaryPacket* packet, uint8_t* buffer, bool ignoreData)
{
	uint16_t bufferIndex = 0;
	buffer[bufferIndex++] = 0xCC;
	buffer[bufferIndex++] = 0x44;
	buffer[bufferIndex++] = packet->moduleClass;
	buffer[bufferIndex++] = packet->command;
	buffer[bufferIndex++] = packet->status.binary;
	buffer[bufferIndex++] = (uint8_t)(packet->dataSize >> 8);
	buffer[bufferIndex++] = (uint8_t)(packet->dataSize & 0xFF);
	buffer[bufferIndex++] = (uint8_t)(packet->crc >> 8);
	buffer[bufferIndex++] = (uint8_t)(packet->crc & 0xFF);
	if (!ignoreData)
	{
		memcpy(&buffer[bufferIndex], packet->data, packet->dataSize);
	}
	return true;
}

bool RobustCommunication::charPacketToDataArray(RobustCommunication::CharPacket* packet, uint8_t* buffer)
{
	uint8_t* bufferPtr = buffer;
	*bufferPtr++ = packet->header;

	memcpy(bufferPtr, packet->moduleName, strlen(packet->moduleName));
	bufferPtr += strlen(packet->moduleName);

	*bufferPtr++ = charSeperator;

	memcpy(bufferPtr, packet->commandName, strlen(packet->commandName));
	bufferPtr += strlen(packet->commandName);

	*bufferPtr++ = charSeperator;

	memcpy(bufferPtr, packet->data, strlen(packet->data));
	bufferPtr += strlen(packet->data);

	*bufferPtr++ = packet->footer;
	*bufferPtr++ = '\0';

	DEBUGPRINTF("Databuffer is %s", (char*)buffer);
	return true;
}

void RobustCommunication::addCommsDefinition(CommsDefinition* definition)
{
	if (freeDefinitionIndex != definitionSize)
	{
		CommsDefinition newDefinition = *definition;
		if (newDefinition.dataStringLayout != "")
		{
			newDefinition.expectedDataSize = 0;
			char dataFormat[128];
			uint8_t dataFormatIndex = 0;
			char dataLayout[128];
			strcpy(dataLayout, newDefinition.dataStringLayout);
			char* dataLayoutToken;
			dataLayoutToken = strtok(dataLayout, ",");
			while (dataLayoutToken != NULL)
			{
				strTypeToFormat foundFormat;
				foundFormat.byteSize = 255;

				for (strTypeToFormat strTypeFormat : strTypeToFormatMap)
				{
					if (!strcmp(strTypeFormat.shortName, dataLayoutToken))
					{
						foundFormat = strTypeFormat;
						break;
					}
				}

				if (foundFormat.byteSize == 255)
				{
					DEBUGPRINTF("ERROR, token %s not found\n", dataLayoutToken);
				}
				else
				{
					strcpy(&dataFormat[dataFormatIndex], foundFormat.scanfName);
					dataFormatIndex += strlen(foundFormat.scanfName);
					strcpy(&dataFormat[dataFormatIndex], ",");
					dataFormatIndex++;
					newDefinition.expectedDataSize += foundFormat.byteSize;
				}
				dataLayoutToken = strtok(NULL, ",");
			}
			dataFormat[--dataFormatIndex] = '\0';
			newDefinition.sscanfFormat = (char*)malloc(dataFormatIndex);
			strcpy(newDefinition.sscanfFormat, dataFormat);
			free(dataLayoutToken);
		}
		definitions[freeDefinitionIndex++] = newDefinition;
	}
}

void RobustCommunication::printHelp()
{
	DEBUGPRINTF("Available commands: \n");
	for (int i = 0; i < freeDefinitionIndex; i++)
	{
		if (definitions[i].moduleName != NULL)
		{
			DEBUGPRINTF("- ASCII: module %s, command %s, dataformat %s ", definitions[i].moduleName, definitions[i].commandName, definitions[i].dataStringLayout);
			if (definitions[i].shortDesc != NULL)
			{
				DEBUGPRINTF("%s", definitions[i].shortDesc);
			}
			DEBUGPRINTF("\n");
		}
	}

}

void RobustCommunication::writeBinaryPacket(BinaryPacket* packet)
{
	uint8_t returnPacket[BinaryPacketInformationSize];
	binaryPacketToDataArray(packet, returnPacket, true);
	for (int i = 0; i < BinaryPacketInformationSize; i++)
	{
		hardware.write(returnPacket[i]);
	}
	for (int i = 0; i < packet->dataSize; i++)
	{
		hardware.write(packet->data[i]);
	}
}

void RobustCommunication::writeCharPacket(CharPacket* packet)
{
	uint8_t returnPacket[2024];
	charPacketToDataArray(packet, returnPacket);
	for (int i = 0; i < BinaryPacketInformationSize; i++)
	{
		hardware.write(returnPacket[i]);
	}
}


RobustCommunication::CommsDefinition RobustCommunication::definitions[definitionSize];
uint16_t RobustCommunication::freeDefinitionIndex = 0;
uint8_t RobustCommunication::instanceAmount = 0;