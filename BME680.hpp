/*
 * name:        BME680
 * description: Low-power gas, pressure, temperature and humidity sensor
 * manuf:       Bosch Sensortec
 * version:     0.1
 * url:         https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BME680-DS001-00.pdf
 * date:        2017-12-18
 * author       https://chisl.io/
 * file:        BME680.hpp
 */

#include <cinttypes>

/* Derive from class BME680_Base and implement the read and write functions! */

/* BME680: Low-power gas, pressure, temperature and humidity sensor */
class BME680_Base
{
public:
	/* Pure virtual functions that need to be implemented in derived class: */
	virtual uint8_t read8(uint16_t address, uint16_t n=8) = 0;  // 8 bit read
	virtual void write(uint16_t address, uint8_t value, uint16_t n=8) = 0;  // 8 bit write
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                            REG STATUS                                             *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG STATUS:
	 * 5.3.1.4
	 *       In SPI mode complete memory page is accessed using page 0 & page 1.
	 *       Register spi_mem_page is used for page selection. After power-on, spi_mem_page
	 *       is in its reset state and page 0(0x00 to 0x7F) will be active. Page1 (0x7F to 0xFF)
	 *       will be active on setting spi_mem_page. Please refer Table 15 for better
	 *       understanding. 
	 */
	struct STATUS
	{
		static const uint16_t __address = 115;
		
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint8_t dflt = 0b000; // 3'b0
			static const uint8_t mask = 0b11100000; // [5,6,7]
		};
		/* Bits spi_mem_page: */
		/* Selects memory map page in SPI mode */
		struct spi_mem_page
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00010000; // [4]
		};
		/* Bits unused_1: */
		struct unused_1
		{
			static const uint8_t dflt = 0b0001; // 4'b1
			static const uint8_t mask = 0b00001111; // [0,1,2,3]
		};
	};
	
	/* Set register STATUS */
	void setSTATUS(uint8_t value)
	{
		write(STATUS::__address, value, 8);
	}
	
	/* Get register STATUS */
	uint8_t getSTATUS()
	{
		return read8(STATUS::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                            REG RESET                                             *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG RESET:
	 * 5.3.1.5
	 *       Writing 0xB6 to this register initiates a soft-reset procedure, which has the
	 *       same effect like power-on reset. The default value stored in this register is 0x00. 
	 */
	struct RESET
	{
		static const uint16_t __address = 224;
		
		/* Bits Reset: */
		struct Reset
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
			static const uint8_t RESET = 0xb6; // 
		};
	};
	
	/* Set register RESET */
	void setRESET(uint8_t value)
	{
		write(RESET::__address, value, 8);
	}
	
	/* Get register RESET */
	uint8_t getRESET()
	{
		return read8(RESET::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                              REG Id                                               *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Id:
	 * 5.3.1.6
	 *       Chip id of the device 
	 */
	struct Id
	{
		static const uint16_t __address = 208;
		
		/* Bits chip_id: */
		struct chip_id
		{
			static const uint8_t dflt = 0b01100001; // 8'b1100001
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Id */
	void setId(uint8_t value)
	{
		write(Id::__address, value, 8);
	}
	
	/* Get register Id */
	uint8_t getId()
	{
		return read8(Id::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                            REG Config                                             *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Config:
	 * 5.3.1.2 Enable SPI 3 wire mode
	 *       5.3.2.4 IIR filter settings 
	 */
	struct Config
	{
		static const uint16_t __address = 117;
		
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint8_t dflt = 0b000; // 3'b0
			static const uint8_t mask = 0b11100000; // [5,6,7]
		};
		/* Bits filter: */
		/*
		 * IIR filter settings
		 *           IIR filter applies to temperature and pressure data but not to humidity and gas data.
		 *           The data coming from the ADC are filtered and then loaded into the data registers.
		 *           The temperature and pressure result registers are updated together at the same time
		 *           at the end of the measurement. IIR filter output resolution is 20 bits. The result
		 *           registers are reset to value 0x80000 when the temperature and/or pressure measurements
		 *           have been skipped (osrs_x=”000‟). The appropriate filter memory is kept unchanged
		 *           (the value from the last measurement is kept). When the appropriate OSRS register is
		 *           set back to nonzero, then the first value stored to the result registers are filtered. 
		 */
		struct filter
		{
			static const uint8_t dflt = 0b000; // 3'b0
			static const uint8_t mask = 0b00011100; // [2,3,4]
		};
		/* Bits unused_1: */
		struct unused_1
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000010; // [1]
		};
		/* Bits spi_3w_en: */
		/* Enable SPI 3 wire mode */
		struct spi_3w_en
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000001; // [0]
		};
	};
	
	/* Set register Config */
	void setConfig(uint8_t value)
	{
		write(Config::__address, value, 8);
	}
	
	/* Get register Config */
	uint8_t getConfig()
	{
		return read8(Config::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                          REG Ctrl_meas                                           *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG Ctrl_meas:
	 * 5.3.1.3 Select sensor power mode
	 *       5.3.2.2 Temperature oversampling settings
	 *       5.3.2.3 Pressure oversampling settings 
	 */
	struct Ctrl_meas
	{
		static const uint16_t __address = 116;
		
		/* Bits osrs_t: */
		/* Temperature oversampling settings  */
		struct osrs_t
		{
			static const uint8_t dflt = 0b000; // 3'b0
			static const uint8_t mask = 0b11100000; // [5,6,7]
			static const uint8_t SKIPPED = 0b00; // output set to 0x8000
			static const uint8_t X1 = 0b01; // oversampling ×1
			static const uint8_t X2 = 0b10; // oversampling ×2
			static const uint8_t X4 = 0b11; // oversampling ×4
			static const uint8_t X8 = 0b100; // oversampling ×8
			static const uint8_t X16 = 0b101; // oversampling ×16
		};
		/* Bits osrs_p: */
		/* Pressure oversampling settings  */
		struct osrs_p
		{
			static const uint8_t dflt = 0b000; // 3'b0
			static const uint8_t mask = 0b00011100; // [2,3,4]
			static const uint8_t SKIPPED = 0b00; // output set to 0x8000
			static const uint8_t X1 = 0b01; // oversampling ×1
			static const uint8_t X2 = 0b10; // oversampling ×2
			static const uint8_t X4 = 0b11; // oversampling ×4
			static const uint8_t X8 = 0b100; // oversampling ×8
			static const uint8_t X16 = 0b101; // oversampling ×16
		};
		/* Bits mode: */
		/* Select sensor power mode  */
		struct mode
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b00000011; // [0,1]
			static const uint8_t SLEEP = 0b00; // 
			static const uint8_t FORCED = 0b01; // 
		};
	};
	
	/* Set register Ctrl_meas */
	void setCtrl_meas(uint8_t value)
	{
		write(Ctrl_meas::__address, value, 8);
	}
	
	/* Get register Ctrl_meas */
	uint8_t getCtrl_meas()
	{
		return read8(Ctrl_meas::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                           REG Ctrl_hum                                            *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Ctrl_hum:
	 * 5.3.1.1 SPI 3 wire interrupt enable
	 *       5.3.2.1 Controls over sampling setting of humidity sensor 
	 */
	struct Ctrl_hum
	{
		static const uint16_t __address = 114;
		
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b10000000; // [7]
		};
		/* Bits spi_3w_int_en: */
		/*
		 * New data interrupt can be enabled if the device is in SPI 3 wire mode and pi_3w_int_en=1.
		 *         The new data interrupt is then indicated on the SDO pad. 
		 */
		struct spi_3w_int_en
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b01000000; // [6]
		};
		/* Bits unused_1: */
		struct unused_1
		{
			static const uint8_t dflt = 0b000; // 3'b0
			static const uint8_t mask = 0b00111000; // [3,4,5]
		};
		/* Bits osrs_h: */
		/* Controls over sampling setting of humidity sensor  */
		struct osrs_h
		{
			static const uint8_t dflt = 0b000; // 3'b0
			static const uint8_t mask = 0b00000111; // [0,1,2]
			static const uint8_t SKIPPED = 0b00; // output set to 0x8000
			static const uint8_t X1 = 0b01; // oversampling ×1
			static const uint8_t X2 = 0b10; // oversampling ×2
			static const uint8_t X4 = 0b11; // oversampling ×4
			static const uint8_t X8 = 0b100; // oversampling ×8
			static const uint8_t X16 = 0b101; // oversampling ×16
		};
	};
	
	/* Set register Ctrl_hum */
	void setCtrl_hum(uint8_t value)
	{
		write(Ctrl_hum::__address, value, 8);
	}
	
	/* Get register Ctrl_hum */
	uint8_t getCtrl_hum()
	{
		return read8(Ctrl_hum::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Ctrl_gas_1                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Ctrl_gas_1:
	 * 5.3.3.5 Heater profile selection
	 *       5.3.3.6 Run Gas 
	 */
	struct Ctrl_gas_1
	{
		static const uint16_t __address = 113;
		
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint8_t dflt = 0b000; // 3'b0
			static const uint8_t mask = 0b11100000; // [5,6,7]
		};
		/* Bits run_gas: */
		/* The gas conversions are started only in appropriate mode if run_gas = ‘1’  */
		struct run_gas
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00010000; // [4]
		};
		/* Bits nb_conv: */
		/* Indicates index of heater set point that will be used in forced mode  */
		struct nb_conv
		{
			static const uint8_t dflt = 0b0000; // 4'b0
			static const uint8_t mask = 0b00001111; // [0,1,2,3]
		};
	};
	
	/* Set register Ctrl_gas_1 */
	void setCtrl_gas_1(uint8_t value)
	{
		write(Ctrl_gas_1::__address, value, 8);
	}
	
	/* Get register Ctrl_gas_1 */
	uint8_t getCtrl_gas_1()
	{
		return read8(Ctrl_gas_1::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Ctrl_gas_0                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Ctrl_gas_0:
	 * 5.3.3.4 Heater off 
	 */
	struct Ctrl_gas_0
	{
		static const uint16_t __address = 112;
		
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint8_t dflt = 0b0000; // 4'b0
			static const uint8_t mask = 0b11110000; // [4,5,6,7]
		};
		/* Bits heat_off: */
		/* Turn off current injected to heater by setting bit to one  */
		struct heat_off
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00001000; // [3]
			static const uint8_t HEAT_OFF = 0b1; // 
			static const uint8_t HEAT_ON = 0b0; // 
		};
		/* Bits unused_1: */
		struct unused_1
		{
			static const uint8_t dflt = 0b000; // 3'b0
			static const uint8_t mask = 0b00000111; // [0,1,2]
		};
	};
	
	/* Set register Ctrl_gas_0 */
	void setCtrl_gas_0(uint8_t value)
	{
		write(Ctrl_gas_0::__address, value, 8);
	}
	
	/* Get register Ctrl_gas_0 */
	uint8_t getCtrl_gas_0()
	{
		return read8(Ctrl_gas_0::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Gas_wait_9                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Gas_wait_9:
	 * 5.3.3.3 Gas Sensor wait time
	 *       The time between the beginning of the heat phase and the start of gas sensor resistance
	 *       conversion depends on gas_wait_x setting as mentioned below. 
	 */
	struct Gas_wait_9
	{
		static const uint16_t __address = 109;
		
		/* Bits gas_wait_mult: */
		/* Gas sensor wait time multiplication factor  */
		struct gas_wait_mult
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b11000000; // [6,7]
			static const uint8_t X1 = 0b00; // 
			static const uint8_t X4 = 0b01; // 
			static const uint8_t X16 = 0b10; // 
			static const uint8_t X64 = 0b11; // 
		};
		/* Bits gas_wait_val: */
		/* 64 timer values with 1 ms step sizes, all zeros means no wait  */
		struct gas_wait_val
		{
			static const uint8_t dflt = 0b000000; // 6'b0
			static const uint8_t mask = 0b00111111; // [0,1,2,3,4,5]
		};
	};
	
	/* Set register Gas_wait_9 */
	void setGas_wait_9(uint8_t value)
	{
		write(Gas_wait_9::__address, value, 8);
	}
	
	/* Get register Gas_wait_9 */
	uint8_t getGas_wait_9()
	{
		return read8(Gas_wait_9::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Gas_wait_8                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Gas_wait_8:
	 * 5.3.3.3 Gas Sensor wait time 
	 */
	struct Gas_wait_8
	{
		static const uint16_t __address = 108;
		
		/* Bits gas_wait_mult: */
		/* Gas sensor wait time multiplication factor  */
		struct gas_wait_mult
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b11000000; // [6,7]
			static const uint8_t X1 = 0b00; // 
			static const uint8_t X4 = 0b01; // 
			static const uint8_t X16 = 0b10; // 
			static const uint8_t X64 = 0b11; // 
		};
		/* Bits gas_wait_val: */
		/* 64 timer values with 1 ms step sizes, all zeros means no wait  */
		struct gas_wait_val
		{
			static const uint8_t dflt = 0b000000; // 6'b0
			static const uint8_t mask = 0b00111111; // [0,1,2,3,4,5]
		};
	};
	
	/* Set register Gas_wait_8 */
	void setGas_wait_8(uint8_t value)
	{
		write(Gas_wait_8::__address, value, 8);
	}
	
	/* Get register Gas_wait_8 */
	uint8_t getGas_wait_8()
	{
		return read8(Gas_wait_8::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Gas_wait_7                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Gas_wait_7:
	 * 5.3.3.3 Gas Sensor wait time 
	 */
	struct Gas_wait_7
	{
		static const uint16_t __address = 107;
		
		/* Bits gas_wait_mult: */
		/* Gas sensor wait time multiplication factor  */
		struct gas_wait_mult
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b11000000; // [6,7]
			static const uint8_t X1 = 0b00; // 
			static const uint8_t X4 = 0b01; // 
			static const uint8_t X16 = 0b10; // 
			static const uint8_t X64 = 0b11; // 
		};
		/* Bits gas_wait_val: */
		/* 64 timer values with 1 ms step sizes, all zeros means no wait  */
		struct gas_wait_val
		{
			static const uint8_t dflt = 0b000000; // 6'b0
			static const uint8_t mask = 0b00111111; // [0,1,2,3,4,5]
		};
	};
	
	/* Set register Gas_wait_7 */
	void setGas_wait_7(uint8_t value)
	{
		write(Gas_wait_7::__address, value, 8);
	}
	
	/* Get register Gas_wait_7 */
	uint8_t getGas_wait_7()
	{
		return read8(Gas_wait_7::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Gas_wait_6                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Gas_wait_6:
	 * 5.3.3.3 Gas Sensor wait time 
	 */
	struct Gas_wait_6
	{
		static const uint16_t __address = 106;
		
		/* Bits gas_wait_mult: */
		/* Gas sensor wait time multiplication factor  */
		struct gas_wait_mult
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b11000000; // [6,7]
			static const uint8_t X1 = 0b00; // 
			static const uint8_t X4 = 0b01; // 
			static const uint8_t X16 = 0b10; // 
			static const uint8_t X64 = 0b11; // 
		};
		/* Bits gas_wait_val: */
		/* 64 timer values with 1 ms step sizes, all zeros means no wait  */
		struct gas_wait_val
		{
			static const uint8_t dflt = 0b000000; // 6'b0
			static const uint8_t mask = 0b00111111; // [0,1,2,3,4,5]
		};
	};
	
	/* Set register Gas_wait_6 */
	void setGas_wait_6(uint8_t value)
	{
		write(Gas_wait_6::__address, value, 8);
	}
	
	/* Get register Gas_wait_6 */
	uint8_t getGas_wait_6()
	{
		return read8(Gas_wait_6::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Gas_wait_5                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Gas_wait_5:
	 * 5.3.3.3 Gas Sensor wait time 
	 */
	struct Gas_wait_5
	{
		static const uint16_t __address = 105;
		
		/* Bits gas_wait_mult: */
		/* Gas sensor wait time multiplication factor  */
		struct gas_wait_mult
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b11000000; // [6,7]
			static const uint8_t X1 = 0b00; // 
			static const uint8_t X4 = 0b01; // 
			static const uint8_t X16 = 0b10; // 
			static const uint8_t X64 = 0b11; // 
		};
		/* Bits gas_wait_val: */
		/* 64 timer values with 1 ms step sizes, all zeros means no wait  */
		struct gas_wait_val
		{
			static const uint8_t dflt = 0b000000; // 6'b0
			static const uint8_t mask = 0b00111111; // [0,1,2,3,4,5]
		};
	};
	
	/* Set register Gas_wait_5 */
	void setGas_wait_5(uint8_t value)
	{
		write(Gas_wait_5::__address, value, 8);
	}
	
	/* Get register Gas_wait_5 */
	uint8_t getGas_wait_5()
	{
		return read8(Gas_wait_5::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Gas_wait_4                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Gas_wait_4:
	 * 5.3.3.3 Gas Sensor wait time 
	 */
	struct Gas_wait_4
	{
		static const uint16_t __address = 104;
		
		/* Bits gas_wait_mult: */
		/* Gas sensor wait time multiplication factor  */
		struct gas_wait_mult
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b11000000; // [6,7]
			static const uint8_t X1 = 0b00; // 
			static const uint8_t X4 = 0b01; // 
			static const uint8_t X16 = 0b10; // 
			static const uint8_t X64 = 0b11; // 
		};
		/* Bits gas_wait_val: */
		/* 64 timer values with 1 ms step sizes, all zeros means no wait  */
		struct gas_wait_val
		{
			static const uint8_t dflt = 0b000000; // 6'b0
			static const uint8_t mask = 0b00111111; // [0,1,2,3,4,5]
		};
	};
	
	/* Set register Gas_wait_4 */
	void setGas_wait_4(uint8_t value)
	{
		write(Gas_wait_4::__address, value, 8);
	}
	
	/* Get register Gas_wait_4 */
	uint8_t getGas_wait_4()
	{
		return read8(Gas_wait_4::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Gas_wait_3                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Gas_wait_3:
	 * 5.3.3.3 Gas Sensor wait time 
	 */
	struct Gas_wait_3
	{
		static const uint16_t __address = 103;
		
		/* Bits gas_wait_mult: */
		/* Gas sensor wait time multiplication factor  */
		struct gas_wait_mult
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b11000000; // [6,7]
			static const uint8_t X1 = 0b00; // 
			static const uint8_t X4 = 0b01; // 
			static const uint8_t X16 = 0b10; // 
			static const uint8_t X64 = 0b11; // 
		};
		/* Bits gas_wait_val: */
		/* 64 timer values with 1 ms step sizes, all zeros means no wait  */
		struct gas_wait_val
		{
			static const uint8_t dflt = 0b000000; // 6'b0
			static const uint8_t mask = 0b00111111; // [0,1,2,3,4,5]
		};
	};
	
	/* Set register Gas_wait_3 */
	void setGas_wait_3(uint8_t value)
	{
		write(Gas_wait_3::__address, value, 8);
	}
	
	/* Get register Gas_wait_3 */
	uint8_t getGas_wait_3()
	{
		return read8(Gas_wait_3::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Gas_wait_2                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Gas_wait_2:
	 * 5.3.3.3 Gas Sensor wait time 
	 */
	struct Gas_wait_2
	{
		static const uint16_t __address = 102;
		
		/* Bits gas_wait_mult: */
		/* Gas sensor wait time multiplication factor  */
		struct gas_wait_mult
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b11000000; // [6,7]
			static const uint8_t X1 = 0b00; // 
			static const uint8_t X4 = 0b01; // 
			static const uint8_t X16 = 0b10; // 
			static const uint8_t X64 = 0b11; // 
		};
		/* Bits gas_wait_val: */
		/* 64 timer values with 1 ms step sizes, all zeros means no wait  */
		struct gas_wait_val
		{
			static const uint8_t dflt = 0b000000; // 6'b0
			static const uint8_t mask = 0b00111111; // [0,1,2,3,4,5]
		};
	};
	
	/* Set register Gas_wait_2 */
	void setGas_wait_2(uint8_t value)
	{
		write(Gas_wait_2::__address, value, 8);
	}
	
	/* Get register Gas_wait_2 */
	uint8_t getGas_wait_2()
	{
		return read8(Gas_wait_2::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Gas_wait_1                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Gas_wait_1:
	 * 5.3.3.3 Gas Sensor wait time 
	 */
	struct Gas_wait_1
	{
		static const uint16_t __address = 101;
		
		/* Bits gas_wait_mult: */
		/* Gas sensor wait time multiplication factor  */
		struct gas_wait_mult
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b11000000; // [6,7]
			static const uint8_t X1 = 0b00; // 
			static const uint8_t X4 = 0b01; // 
			static const uint8_t X16 = 0b10; // 
			static const uint8_t X64 = 0b11; // 
		};
		/* Bits gas_wait_val: */
		/* 64 timer values with 1 ms step sizes, all zeros means no wait  */
		struct gas_wait_val
		{
			static const uint8_t dflt = 0b000000; // 6'b0
			static const uint8_t mask = 0b00111111; // [0,1,2,3,4,5]
		};
	};
	
	/* Set register Gas_wait_1 */
	void setGas_wait_1(uint8_t value)
	{
		write(Gas_wait_1::__address, value, 8);
	}
	
	/* Get register Gas_wait_1 */
	uint8_t getGas_wait_1()
	{
		return read8(Gas_wait_1::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Gas_wait_0                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Gas_wait_0:
	 * 5.3.3.3 Gas Sensor wait time 
	 */
	struct Gas_wait_0
	{
		static const uint16_t __address = 100;
		
		/* Bits gas_wait_mult: */
		/* Gas sensor wait time multiplication factor  */
		struct gas_wait_mult
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b11000000; // [6,7]
			static const uint8_t X1 = 0b00; // 
			static const uint8_t X4 = 0b01; // 
			static const uint8_t X16 = 0b10; // 
			static const uint8_t X64 = 0b11; // 
		};
		/* Bits gas_wait_val: */
		/* 64 timer values with 1 ms step sizes, all zeros means no wait  */
		struct gas_wait_val
		{
			static const uint8_t dflt = 0b000000; // 6'b0
			static const uint8_t mask = 0b00111111; // [0,1,2,3,4,5]
		};
	};
	
	/* Set register Gas_wait_0 */
	void setGas_wait_0(uint8_t value)
	{
		write(Gas_wait_0::__address, value, 8);
	}
	
	/* Get register Gas_wait_0 */
	uint8_t getGas_wait_0()
	{
		return read8(Gas_wait_0::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Res_heat_9                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Res_heat_9:
	 * 5.3.3.2 Target heater resistance 
	 */
	struct Res_heat_9
	{
		static const uint16_t __address = 99;
		
		/* Bits res_heat: */
		/* Decimal value that needs to be stored for achieving target heater resistance  */
		struct res_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Res_heat_9 */
	void setRes_heat_9(uint8_t value)
	{
		write(Res_heat_9::__address, value, 8);
	}
	
	/* Get register Res_heat_9 */
	uint8_t getRes_heat_9()
	{
		return read8(Res_heat_9::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Res_heat_8                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Res_heat_8:
	 * 5.3.3.2 Target heater resistance 
	 */
	struct Res_heat_8
	{
		static const uint16_t __address = 98;
		
		/* Bits res_heat: */
		/* Decimal value that needs to be stored for achieving target heater resistance  */
		struct res_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Res_heat_8 */
	void setRes_heat_8(uint8_t value)
	{
		write(Res_heat_8::__address, value, 8);
	}
	
	/* Get register Res_heat_8 */
	uint8_t getRes_heat_8()
	{
		return read8(Res_heat_8::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Res_heat_7                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Res_heat_7:
	 * 5.3.3.2 Target heater resistance 
	 */
	struct Res_heat_7
	{
		static const uint16_t __address = 97;
		
		/* Bits res_heat: */
		/* Decimal value that needs to be stored for achieving target heater resistance  */
		struct res_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Res_heat_7 */
	void setRes_heat_7(uint8_t value)
	{
		write(Res_heat_7::__address, value, 8);
	}
	
	/* Get register Res_heat_7 */
	uint8_t getRes_heat_7()
	{
		return read8(Res_heat_7::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Res_heat_6                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Res_heat_6:
	 * 5.3.3.2 Target heater resistance 
	 */
	struct Res_heat_6
	{
		static const uint16_t __address = 96;
		
		/* Bits res_heat: */
		/* Decimal value that needs to be stored for achieving target heater resistance  */
		struct res_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Res_heat_6 */
	void setRes_heat_6(uint8_t value)
	{
		write(Res_heat_6::__address, value, 8);
	}
	
	/* Get register Res_heat_6 */
	uint8_t getRes_heat_6()
	{
		return read8(Res_heat_6::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Res_heat_5                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Res_heat_5:
	 * 5.3.3.2 Target heater resistance 
	 */
	struct Res_heat_5
	{
		static const uint16_t __address = 95;
		
		/* Bits res_heat: */
		/* Decimal value that needs to be stored for achieving target heater resistance  */
		struct res_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Res_heat_5 */
	void setRes_heat_5(uint8_t value)
	{
		write(Res_heat_5::__address, value, 8);
	}
	
	/* Get register Res_heat_5 */
	uint8_t getRes_heat_5()
	{
		return read8(Res_heat_5::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Res_heat_4                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Res_heat_4:
	 * 5.3.3.2 Target heater resistance 
	 */
	struct Res_heat_4
	{
		static const uint16_t __address = 94;
		
		/* Bits res_heat: */
		/* Decimal value that needs to be stored for achieving target heater resistance  */
		struct res_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Res_heat_4 */
	void setRes_heat_4(uint8_t value)
	{
		write(Res_heat_4::__address, value, 8);
	}
	
	/* Get register Res_heat_4 */
	uint8_t getRes_heat_4()
	{
		return read8(Res_heat_4::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Res_heat_3                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Res_heat_3:
	 * 5.3.3.2 Target heater resistance 
	 */
	struct Res_heat_3
	{
		static const uint16_t __address = 93;
		
		/* Bits res_heat: */
		/* Decimal value that needs to be stored for achieving target heater resistance  */
		struct res_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Res_heat_3 */
	void setRes_heat_3(uint8_t value)
	{
		write(Res_heat_3::__address, value, 8);
	}
	
	/* Get register Res_heat_3 */
	uint8_t getRes_heat_3()
	{
		return read8(Res_heat_3::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Res_heat_2                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Res_heat_2:
	 * 5.3.3.2 Target heater resistance 
	 */
	struct Res_heat_2
	{
		static const uint16_t __address = 92;
		
		/* Bits res_heat: */
		/* Decimal value that needs to be stored for achieving target heater resistance  */
		struct res_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Res_heat_2 */
	void setRes_heat_2(uint8_t value)
	{
		write(Res_heat_2::__address, value, 8);
	}
	
	/* Get register Res_heat_2 */
	uint8_t getRes_heat_2()
	{
		return read8(Res_heat_2::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Res_heat_1                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Res_heat_1:
	 * 5.3.3.2 Target heater resistance 
	 */
	struct Res_heat_1
	{
		static const uint16_t __address = 91;
		
		/* Bits res_heat: */
		/* Decimal value that needs to be stored for achieving target heater resistance  */
		struct res_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Res_heat_1 */
	void setRes_heat_1(uint8_t value)
	{
		write(Res_heat_1::__address, value, 8);
	}
	
	/* Get register Res_heat_1 */
	uint8_t getRes_heat_1()
	{
		return read8(Res_heat_1::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG Res_heat_0                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Res_heat_0:
	 * 5.3.3.2 Target heater resistance 
	 */
	struct Res_heat_0
	{
		static const uint16_t __address = 90;
		
		/* Bits res_heat: */
		/* Decimal value that needs to be stored for achieving target heater resistance  */
		struct res_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Res_heat_0 */
	void setRes_heat_0(uint8_t value)
	{
		write(Res_heat_0::__address, value, 8);
	}
	
	/* Get register Res_heat_0 */
	uint8_t getRes_heat_0()
	{
		return read8(Res_heat_0::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                         REG Idac_heat_9                                          *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG Idac_heat_9:
	 * 5.3.3.1 Heater current
	 *       BME680 contains a heater control block that will inject enough current into the heater
	 *       resistance to achieve the requested heater temperature. There is a control loop which
	 *       periodically measures heater resistance value and adapts the value of current injected
	 *       from a DAC.
	 *       The heater operation could be speeded up by setting an initial heater current for a target
	 *       heater temperature by using register idac_heat_x<7:0>. This step is optional since the control
	 *       loop will find the current after a few iterations anyway. The current injected to the heater in
	 *       mA can be calculated by: (idac_heat_7_1 + 1) / 8, where idac_heat_7_1 is the decimal value
	 *       stored in idac_heat<7:1> (unsigned, value from 0 to 127). 
	 */
	struct Idac_heat_9
	{
		static const uint16_t __address = 89;
		
		/* Bits idac_heat: */
		/* idac_heat of particular heater set point */
		struct idac_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Idac_heat_9 */
	void setIdac_heat_9(uint8_t value)
	{
		write(Idac_heat_9::__address, value, 8);
	}
	
	/* Get register Idac_heat_9 */
	uint8_t getIdac_heat_9()
	{
		return read8(Idac_heat_9::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                         REG Idac_heat_8                                          *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG Idac_heat_8:
	 * 5.3.3.1 Heater current 
	 */
	struct Idac_heat_8
	{
		static const uint16_t __address = 88;
		
		/* Bits idac_heat: */
		/* idac_heat of particular heater set point */
		struct idac_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Idac_heat_8 */
	void setIdac_heat_8(uint8_t value)
	{
		write(Idac_heat_8::__address, value, 8);
	}
	
	/* Get register Idac_heat_8 */
	uint8_t getIdac_heat_8()
	{
		return read8(Idac_heat_8::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                         REG Idac_heat_7                                          *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG Idac_heat_7:
	 * 5.3.3.1 Heater current 
	 */
	struct Idac_heat_7
	{
		static const uint16_t __address = 87;
		
		/* Bits idac_heat: */
		/* idac_heat of particular heater set point */
		struct idac_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Idac_heat_7 */
	void setIdac_heat_7(uint8_t value)
	{
		write(Idac_heat_7::__address, value, 8);
	}
	
	/* Get register Idac_heat_7 */
	uint8_t getIdac_heat_7()
	{
		return read8(Idac_heat_7::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                         REG Idac_heat_6                                          *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG Idac_heat_6:
	 * 5.3.3.1 Heater current 
	 */
	struct Idac_heat_6
	{
		static const uint16_t __address = 86;
		
		/* Bits idac_heat: */
		/* idac_heat of particular heater set point */
		struct idac_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Idac_heat_6 */
	void setIdac_heat_6(uint8_t value)
	{
		write(Idac_heat_6::__address, value, 8);
	}
	
	/* Get register Idac_heat_6 */
	uint8_t getIdac_heat_6()
	{
		return read8(Idac_heat_6::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                         REG Idac_heat_5                                          *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG Idac_heat_5:
	 * 5.3.3.1 Heater current 
	 */
	struct Idac_heat_5
	{
		static const uint16_t __address = 85;
		
		/* Bits idac_heat: */
		/* idac_heat of particular heater set point */
		struct idac_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Idac_heat_5 */
	void setIdac_heat_5(uint8_t value)
	{
		write(Idac_heat_5::__address, value, 8);
	}
	
	/* Get register Idac_heat_5 */
	uint8_t getIdac_heat_5()
	{
		return read8(Idac_heat_5::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                         REG Idac_heat_4                                          *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG Idac_heat_4:
	 * 5.3.3.1 Heater current 
	 */
	struct Idac_heat_4
	{
		static const uint16_t __address = 84;
		
		/* Bits idac_heat: */
		/* idac_heat of particular heater set point */
		struct idac_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Idac_heat_4 */
	void setIdac_heat_4(uint8_t value)
	{
		write(Idac_heat_4::__address, value, 8);
	}
	
	/* Get register Idac_heat_4 */
	uint8_t getIdac_heat_4()
	{
		return read8(Idac_heat_4::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                         REG Idac_heat_3                                          *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG Idac_heat_3:
	 * 5.3.3.1 Heater current 
	 */
	struct Idac_heat_3
	{
		static const uint16_t __address = 83;
		
		/* Bits idac_heat: */
		/* idac_heat of particular heater set point */
		struct idac_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Idac_heat_3 */
	void setIdac_heat_3(uint8_t value)
	{
		write(Idac_heat_3::__address, value, 8);
	}
	
	/* Get register Idac_heat_3 */
	uint8_t getIdac_heat_3()
	{
		return read8(Idac_heat_3::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                         REG Idac_heat_2                                          *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG Idac_heat_2:
	 * 5.3.3.1 Heater current 
	 */
	struct Idac_heat_2
	{
		static const uint16_t __address = 82;
		
		/* Bits idac_heat: */
		/* idac_heat of particular heater set point */
		struct idac_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Idac_heat_2 */
	void setIdac_heat_2(uint8_t value)
	{
		write(Idac_heat_2::__address, value, 8);
	}
	
	/* Get register Idac_heat_2 */
	uint8_t getIdac_heat_2()
	{
		return read8(Idac_heat_2::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                         REG Idac_heat_1                                          *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG Idac_heat_1:
	 * 5.3.3.1 Heater current 
	 */
	struct Idac_heat_1
	{
		static const uint16_t __address = 81;
		
		/* Bits idac_heat: */
		/* idac_heat of particular heater set point */
		struct idac_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Idac_heat_1 */
	void setIdac_heat_1(uint8_t value)
	{
		write(Idac_heat_1::__address, value, 8);
	}
	
	/* Get register Idac_heat_1 */
	uint8_t getIdac_heat_1()
	{
		return read8(Idac_heat_1::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                         REG Idac_heat_0                                          *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG Idac_heat_0:
	 * 5.3.3.1 Heater current 
	 */
	struct Idac_heat_0
	{
		static const uint16_t __address = 80;
		
		/* Bits idac_heat: */
		/* idac_heat of particular heater set point */
		struct idac_heat
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register Idac_heat_0 */
	void setIdac_heat_0(uint8_t value)
	{
		write(Idac_heat_0::__address, value, 8);
	}
	
	/* Get register Idac_heat_0 */
	uint8_t getIdac_heat_0()
	{
		return read8(Idac_heat_0::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                          REG gas_r_lsb                                           *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG gas_r_lsb:
	 * 5.3.4.5 Gas resistance range
	 *       5.3.4.4 Gas resistance data
	 *       5.3.5.5 Gas valid status
	 *       5.3.5.6 Heater Stability Status 
	 */
	struct gas_r_lsb
	{
		static const uint16_t __address = 43;
		
		/* Bits gas_r: */
		/* Contains the LSB part gas resistance [1:0] of the raw gas resistance.  */
		struct gas_r
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b11000000; // [6,7]
		};
		/* Bits gas_valid_r: */
		/*
		 * Gas valid bit
		 *           In each TPHG sequence contains a gas measurement slot, either a real one which
		 *           result is used or a dummy one to keep a constant sampling rate and predictable
		 *           device timing. A real gas conversion (i.e., not a dummy one) is indicated by the
		 *           gas_valid_r status register. 
		 */
		struct gas_valid_r
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00100000; // [5]
		};
		/* Bits heat_stab_r: */
		/* Heater stability bit */
		struct heat_stab_r
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00010000; // [4]
		};
		/* Bits gas_range_r: */
		/* Contains ADC range of measured gas resistance */
		struct gas_range_r
		{
			static const uint8_t dflt = 0b0000; // 4'b0
			static const uint8_t mask = 0b00001111; // [0,1,2,3]
		};
	};
	
	/* Set register gas_r_lsb */
	void setgas_r_lsb(uint8_t value)
	{
		write(gas_r_lsb::__address, value, 8);
	}
	
	/* Get register gas_r_lsb */
	uint8_t getgas_r_lsb()
	{
		return read8(gas_r_lsb::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                          REG gas_r_msb                                           *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG gas_r_msb:
	 * 5.3.4.4 Gas resistance data 
	 */
	struct gas_r_msb
	{
		static const uint16_t __address = 42;
		
		/* Bits gas_r: */
		/* Contains the MSB part gas resistance [9:2] of the raw gas resistance.  */
		struct gas_r
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register gas_r_msb */
	void setgas_r_msb(uint8_t value)
	{
		write(gas_r_msb::__address, value, 8);
	}
	
	/* Get register gas_r_msb */
	uint8_t getgas_r_msb()
	{
		return read8(gas_r_msb::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                           REG hum_lsb                                            *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG hum_lsb:
	 * 5.3.4.3 Humidity data 
	 */
	struct hum_lsb
	{
		static const uint16_t __address = 38;
		
		/* Bits hum_lsb: */
		/* Contains the LSB part [7:0] of the raw humidity measurement output data.  */
		struct hum_lsb_
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register hum_lsb */
	void sethum_lsb(uint8_t value)
	{
		write(hum_lsb::__address, value, 8);
	}
	
	/* Get register hum_lsb */
	uint8_t gethum_lsb()
	{
		return read8(hum_lsb::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                           REG hum_msb                                            *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG hum_msb:
	 * 5.3.4.3 Humidity data 
	 */
	struct hum_msb
	{
		static const uint16_t __address = 37;
		
		/* Bits hum_msb: */
		/* Contains the MSB part [15:8] of the raw humidity measurement output data.  */
		struct hum_msb_
		{
			static const uint8_t dflt = 0b10000000; // 8'b10000000
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register hum_msb */
	void sethum_msb(uint8_t value)
	{
		write(hum_msb::__address, value, 8);
	}
	
	/* Get register hum_msb */
	uint8_t gethum_msb()
	{
		return read8(hum_msb::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                          REG temp_xlsb                                           *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG temp_xlsb:
	 * 5.3.4.2 Temp data 
	 */
	struct temp_xlsb
	{
		static const uint16_t __address = 36;
		
		/* Bits temp_xlsb: */
		/*
		 * Contains the XLSB part [3:0] of the raw temperature measurement output data.
		 *           Contents depend on temperature resolution controlled by oversampling setting. 
		 */
		struct temp_xlsb_
		{
			static const uint8_t dflt = 0b0000; // 4'b0
			static const uint8_t mask = 0b11110000; // [4,5,6,7]
		};
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint8_t dflt = 0b0000; // 4'b0
			static const uint8_t mask = 0b00001111; // [0,1,2,3]
		};
	};
	
	/* Set register temp_xlsb */
	void settemp_xlsb(uint8_t value)
	{
		write(temp_xlsb::__address, value, 8);
	}
	
	/* Get register temp_xlsb */
	uint8_t gettemp_xlsb()
	{
		return read8(temp_xlsb::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                           REG temp_lsb                                            *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG temp_lsb:
	 * 5.3.4.2 Temp data 
	 */
	struct temp_lsb
	{
		static const uint16_t __address = 35;
		
		/* Bits temp_lsb: */
		/* Contains the LSB part [11:4] of the raw temperature measurement output data.  */
		struct temp_lsb_
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register temp_lsb */
	void settemp_lsb(uint8_t value)
	{
		write(temp_lsb::__address, value, 8);
	}
	
	/* Get register temp_lsb */
	uint8_t gettemp_lsb()
	{
		return read8(temp_lsb::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                           REG temp_msb                                            *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG temp_msb:
	 * 5.3.4.2 Temp data 
	 */
	struct temp_msb
	{
		static const uint16_t __address = 34;
		
		/* Bits temp_msb: */
		/* Contains the MSB part [19:12] of the raw temperature measurement output data.  */
		struct temp_msb_
		{
			static const uint8_t dflt = 0b10000000; // 8'b10000000
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register temp_msb */
	void settemp_msb(uint8_t value)
	{
		write(temp_msb::__address, value, 8);
	}
	
	/* Get register temp_msb */
	uint8_t gettemp_msb()
	{
		return read8(temp_msb::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                          REG press_xlsb                                           *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG press_xlsb:
	 * 5.3.4.1 Pressure data 
	 */
	struct press_xlsb
	{
		static const uint16_t __address = 33;
		
		/* Bits press_xlsb: */
		/*
		 * Contains the XLSB part [3:0] of the raw pressure measurement output data.
		 *           Contents depend on pressure resolution controlled by oversampling setting. 
		 */
		struct press_xlsb_
		{
			static const uint8_t dflt = 0b0000; // 4'b0
			static const uint8_t mask = 0b11110000; // [4,5,6,7]
		};
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint8_t dflt = 0b0000; // 4'b0
			static const uint8_t mask = 0b00001111; // [0,1,2,3]
		};
	};
	
	/* Set register press_xlsb */
	void setpress_xlsb(uint8_t value)
	{
		write(press_xlsb::__address, value, 8);
	}
	
	/* Get register press_xlsb */
	uint8_t getpress_xlsb()
	{
		return read8(press_xlsb::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                          REG press_lsb                                           *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG press_lsb:
	 * 5.3.4.1 Pressure data 
	 */
	struct press_lsb
	{
		static const uint16_t __address = 32;
		
		/* Bits press_lsb: */
		/* Contains the LSB part [11:4] of the raw pressure measurement output data  */
		struct press_lsb_
		{
			static const uint8_t dflt = 0b00000000; // 8'b0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register press_lsb */
	void setpress_lsb(uint8_t value)
	{
		write(press_lsb::__address, value, 8);
	}
	
	/* Get register press_lsb */
	uint8_t getpress_lsb()
	{
		return read8(press_lsb::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                          REG press_msb                                           *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG press_msb:
	 * 5.3.4.1 Pressure data 
	 */
	struct press_msb
	{
		static const uint16_t __address = 31;
		
		/* Bits press_msb: */
		/* Contains the MSB part [19:12] of the raw pressure measurement output data.  */
		struct press_msb_
		{
			static const uint8_t dflt = 0b10000000; // 8'b10000000
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register press_msb */
	void setpress_msb(uint8_t value)
	{
		write(press_msb::__address, value, 8);
	}
	
	/* Get register press_msb */
	uint8_t getpress_msb()
	{
		return read8(press_msb::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                        REG meas_status_0                                         *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG meas_status_0:
	 * 5.3.5.1 New data status
	 *       5.3.5.2 Gas measuring status
	 *       5.3.5.3 Measuring status
	 *       5.3.5.4 Gas Measurement Index 
	 */
	struct meas_status_0
	{
		static const uint16_t __address = 29;
		
		/* Bits new_data_0: */
		/*
		 * New data flag
		 *           The measured data are stored into the output data registers at the end
		 *           of each TPHG conversion phase along with status flags and index of measurement. 
		 */
		struct new_data_0
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b10000000; // [7]
		};
		/* Bits gas_measuring: */
		/*
		 * Gas measuring status flag
		 *           Measuring bit is set to “1‟ only during gas measurements, goes to “0‟ as soon as
		 *           measurement is completed and data transferred to data registers. The registers storing
		 *           the configuration values for the measurement (gas_wait_shared, gas_wait_x, res_heat_x,
		 *           idac_heat_x, image registers) should not be changed when the device is measuring. 
		 */
		struct gas_measuring
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b01000000; // [6]
		};
		/* Bits measuring: */
		/*
		 * Measuring status flag
		 *           Measuring status will be set to ‘1’ whenever a conversion (temperature, pressure,
		 *           humidity and gas) is running and back to ‘0’ when the results have been transferred
		 *           to the data registers. 
		 */
		struct measuring
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00100000; // [5]
		};
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00010000; // [4]
		};
		/* Bits gas_meas_index_0: */
		/*
		 * Gas measurement index
		 *           User can program a sequence of up to 10 conversions by setting nb_conv<3:0>.
		 *           Each conversion has its own heater resistance target but 3 field registers to store
		 *           conversion results. The actual gas conversion number in the measurement sequence
		 *           (up to 10 conversions numbered from 0 to 9) is stored in gas_meas_index register. 
		 */
		struct gas_meas_index_0
		{
			static const uint8_t dflt = 0b0000; // 4'b0
			static const uint8_t mask = 0b00001111; // [0,1,2,3]
		};
	};
	
	/* Set register meas_status_0 */
	void setmeas_status_0(uint8_t value)
	{
		write(meas_status_0::__address, value, 8);
	}
	
	/* Get register meas_status_0 */
	uint8_t getmeas_status_0()
	{
		return read8(meas_status_0::__address, 8);
	}
	
};
