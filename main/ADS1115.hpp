#pragma once

#include "driver/i2c_master.h"

enum ads1115_i2c_addr_t
{
    ADS1115_ADDR_GND = 0x48,
    ADS1115_ADDR_VCC = 0x49,
    ADS1115_ADDR_SDA = 0x4a,
    ADS1115_ADDR_SCL = 0x4b
};

#define ADS1115_MAX_VALUE 0x7fff //!< Maximum ADC value

/**
 * Gain amplifier
 */
typedef enum
{
    ADS1115_GAIN_6V144 = 0, //!< +-6.144V
    ADS1115_GAIN_4V096,     //!< +-4.096V
    ADS1115_GAIN_2V048,     //!< +-2.048V (default)
    ADS1115_GAIN_1V024,     //!< +-1.024V
    ADS1115_GAIN_0V512,     //!< +-0.512V
    ADS1115_GAIN_0V256,     //!< +-0.256V
    ADS1115_GAIN_0V256_2,   //!< +-0.256V (same as ADS1115_GAIN_0V256)
    ADS1115_GAIN_0V256_3,   //!< +-0.256V (same as ADS1115_GAIN_0V256)
} ADS1115_gain_t;

/**
 * Gain amplifier values
 */
constexpr float ADS1115_gain_multipliers[] = {
    [ADS1115_GAIN_6V144]   = 6.144,
    [ADS1115_GAIN_4V096]   = 4.096,
    [ADS1115_GAIN_2V048]   = 2.048,
    [ADS1115_GAIN_1V024]   = 1.024,
    [ADS1115_GAIN_0V512]   = 0.512,
    [ADS1115_GAIN_0V256]   = 0.256,
    [ADS1115_GAIN_0V256_2] = 0.256,
    [ADS1115_GAIN_0V256_3] = 0.256
};

/**
 * Input multiplexer configuration (ADS1115 only)
 */
typedef enum
{
    ADS1115_MUX_0_1 = 0, //!< positive = AIN0, negative = AIN1 (default)
    ADS1115_MUX_0_3,     //!< positive = AIN0, negative = AIN3
    ADS1115_MUX_1_3,     //!< positive = AIN1, negative = AIN3
    ADS1115_MUX_2_3,     //!< positive = AIN2, negative = AIN3
    ADS1115_MUX_0_GND,   //!< positive = AIN0, negative = GND
    ADS1115_MUX_1_GND,   //!< positive = AIN1, negative = GND
    ADS1115_MUX_2_GND,   //!< positive = AIN2, negative = GND
    ADS1115_MUX_3_GND,   //!< positive = AIN3, negative = GND
} ADS1115_mux_t;

/**
 * Data rate
 */
typedef enum
{
    ADS1115_DATA_RATE_8 = 0, //!< 8 samples per second
    ADS1115_DATA_RATE_16,    //!< 16 samples per second
    ADS1115_DATA_RATE_32,    //!< 32 samples per second
    ADS1115_DATA_RATE_64,    //!< 64 samples per second
    ADS1115_DATA_RATE_128,   //!< 128 samples per second (default)
    ADS1115_DATA_RATE_250,   //!< 250 samples per second
    ADS1115_DATA_RATE_475,   //!< 475 samples per second
    ADS1115_DATA_RATE_860    //!< 860 samples per second
} ADS1115_data_rate_t;

/**
 * Operational mode
 */
typedef enum
{
    ADS1115_MODE_CONTINUOUS = 0, //!< Continuous conversion mode
    ADS1115_MODE_SINGLE_SHOT    //!< Power-down single-shot mode (default)
} ADS1115_mode_t;

/**
 * Comparator mode (ADS1114 and ADS1115 only)
 */
typedef enum
{
    ADS1115_COMP_MODE_NORMAL = 0, //!< Traditional comparator with hysteresis (default)
    ADS1115_COMP_MODE_WINDOW      //!< Window comparator
} ADS1115_comp_mode_t;

/**
 * Comparator polarity (ADS1114 and ADS1115 only)
 */
typedef enum
{
    ADS1115_COMP_POLARITY_LOW = 0, //!< Active low (default)
    ADS1115_COMP_POLARITY_HIGH     //!< Active high
} ADS1115_comp_polarity_t;

/**
 * Comparator latch (ADS1114 and ADS1115 only)
 */
typedef enum
{
    ADS1115_COMP_LATCH_DISABLED = 0, //!< Non-latching comparator (default)
    ADS1115_COMP_LATCH_ENABLED       //!< Latching comparator
} ADS1115_comp_latch_t;

/**
 * Comparator queue
 */
typedef enum
{
    ADS1115_COMP_QUEUE_1 = 0,   //!< Assert ALERT/RDY pin after one conversion
    ADS1115_COMP_QUEUE_2,       //!< Assert ALERT/RDY pin after two conversions
    ADS1115_COMP_QUEUE_4,       //!< Assert ALERT/RDY pin after four conversions
    ADS1115_COMP_QUEUE_DISABLED //!< Disable comparator (default)
} ADS1115_comp_queue_t;

// Register defaults
#define ADS1115_CONVERSION_REG_DEF		0x0000
#define ADS1115_CONFIG_REG_DEF			0x8583
#define ADS1115_LOW_TRESH_REG_DEF		0x8000
#define ADS1115_HIGH_TRESH_REG_DEF		0x7FFF

struct ads1115_config_t
{
    unsigned int os : 1;
    unsigned int mux : 3;
    unsigned int gain : 3;
    unsigned int mode : 1;
    unsigned int data_rate : 3;
    unsigned int comp_mode : 1;
    unsigned int comp_pol : 1;
    unsigned int comp_latch : 1;
    unsigned int comp_queue : 2;

    uint16_t toInt()
    {
        uint16_t flags = 0;
        flags |= os; flags <<= 3;
        flags |= mux; flags <<= 3;
        flags |= gain; flags <<= 1;
        flags |= mode; flags <<= 3;
        flags |= data_rate; flags <<= 1;
        flags |= comp_mode; flags <<= 1;
        flags |= comp_pol; flags <<= 1;
        flags |= comp_latch; flags <<= 2;
        flags |= comp_queue;

        return flags;
    };
    void setFromInt(uint16_t flags)
    {
        comp_queue = flags & 0b11; flags >>= 2;
        comp_latch = flags & 0b1; flags >>= 1;
        comp_pol = flags & 0b1; flags >>= 1;
        comp_mode = flags & 0b1; flags >>= 1;
        data_rate = flags & 0b111; flags >>= 3;
        mode = flags & 0b1; flags >>= 1;
        gain = flags & 0b111; flags >>= 3;
        mux = flags & 0b111; flags >>= 3;
        os = flags;
    };
};

enum ads1115_reg_addr_t
{
    ADS1115_REG_ADDR_CONVERSION = 0,
    ADS1115_REG_ADDR_CONFIG,
    ADS1115_REG_ADDR_LO_THRESH,
    ADS1115_REG_ADDR_HI_THRESH
};

class ADS1115
{
public:
    ADS1115(
        i2c_master_bus_handle_t i2cMasterBusHandle,
        ads1115_i2c_addr_t address = ADS1115_ADDR_GND
    );
    void writeRegister(ads1115_reg_addr_t address, uint16_t data);
    uint16_t readRegister(ads1115_reg_addr_t address);
    int16_t readRawValue();
    void writeConfig();

    ads1115_config_t config;
private:
    i2c_master_bus_handle_t i2cBusHandle;
    i2c_master_dev_handle_t i2cDeviceHandle;
};
