/*************************************
.		SPI_FLASH(M25P64:  $1.87) 
--NOR Flash Serial-SPI 3.3V 64Mbit 8M x 8bit 8ns 8-Pin VDFPN EP Tray

++BSP_SERIAL_FLASH_Init()
	--FLASH_SPI_IO_Init()
		--FLASH_SPI_CS_GPIO_Init();	
		--SPIx_Init();
				1.DeInitializes the SPI peripheral 
					HAL_SPI_DeInit();				
				2.SPI Config				
					GPIO_CLK_ENABLE();
					HAL_GPIO_Init();
					SPI_HandleTypeDef Config				
				3.HAL_SPI_Init();		
		--FLASH_SPI_CS_HIGH();	
++FlashID = BSP_SERIAL_FLASH_ReadID();
		--BSP_SERIAL_FLASH_ReadID()
			--FLASH_SPI_IO_ReadID()
				1.Select the FLASH: Chip Select low
					FLASH_SPI_CS_LOW();
				2.Send "RDID " instruction 
				  SPIx_Write(0x9F);
				3.Read a byte from the FLASH
				  Temp0 = SPIx_Write(FLASH_SPI_DUMMY_BYTE);
					Temp1 = SPIx_Write(FLASH_SPI_DUMMY_BYTE);
				4.Deselect the FLASH: Chip Select high
					FLASH_SPI_CS_HIGH();
					Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
				
				--SPIx_Write();
					HAL_SPI_TransmitReceive(&heval_Spi, (uint8_t*) &WriteValue, (uint8_t*) &ReadValue, 1, SpixTimeout);
++BSP_SERIAL_FLASH_WritePage(FLASH_WriteSector12, Tx_Buffer, BufferSize);					
	--FLASH_SPI_IO_WriteEnable()
		FLASH_SPI_CS_LOW();
		SPIx_Write(FLASH_SPI_CMD_WREN);
		FLASH_SPI_CS_HIGH();
		FLASH_SPI_CS_LOW();
	--FLASH_SPI_IO_WriteByte(FLASH_SPI_CMD_WRITE);
		SPIx_Write();
	--FLASH_SPI_IO_WriteByte((uwStartAddress & 0xFF0000) >> 16);
	--FLASH_SPI_IO_WriteByte((uwStartAddress & 0xFF00) >> 8);
	--FLASH_SPI_IO_WriteByte(uwStartAddress & 0xFF);
	--while (uwDataSize--)
		FLASH_SPI_IO_WriteByte(*pData);pData++;
	--FLASH_SPI_IO_WaitForWriteEnd()
		FLASH_SPI_CS_LOW();
		SPIx_Write(FLASH_SPI_CMD_RDSR);
		flashstatus = SPIx_Write(FLASH_SPI_DUMMY_BYTE);
		FLASH_SPI_CS_HIGH();
++BSP_SERIAL_FLASH_EraseSector(FLASH_AddrSector12);
	--FLASH_SPI_IO_WriteEnable();
	--FLASH_SPI_IO_WriteByte(FLASH_SPI_CMD_SE);
	--FLASH_SPI_IO_WriteByte((SectorAddr & 0xFF0000) >> 16);
	--FLASH_SPI_IO_WriteByte((SectorAddr & 0xFF00) >> 8);
	--FLASH_SPI_IO_WriteByte(SectorAddr & 0xFF);
	--FLASH_SPI_IO_WaitForWriteEnd()
++BSP_SERIAL_FLASH_ReadData(FLASH_WriteSector12, Rx_Buffer, BufferSize);
	--FLASH_SPI_IO_ReadData(uwStartAddress, pData, uwDataSize)
		FLASH_SPI_CS_LOW();
		SPIx_Write(FLASH_SPI_CMD_READ);
		SPIx_Write((MemAddress & 0xFF0000) >> 16);
		SPIx_Write((MemAddress& 0xFF00) >> 8);
		SPIx_Write(MemAddress & 0xFF);
		
		while (BufferSize--)
		*pBufferSPIx_Write(FLASH_SPI_DUMMY_BYTE); pBuffer++;
		
		FLASH_SPI_CS_HIGH();		
*************************************/