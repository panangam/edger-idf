#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"

#include "ADS1115.hpp"

ADS1115::ADS1115(
    i2c_master_bus_handle_t i2cMasterBusHandle,
    ads1115_i2c_addr_t address
) : i2cBusHandle(i2cMasterBusHandle)
{
    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = address,
        .scl_speed_hz = 400000,
        .scl_wait_us = 0,
        .flags = {
            .disable_ack_check = false
        }
    };
    ESP_ERROR_CHECK(
        i2c_master_bus_add_device(this->i2cBusHandle, &dev_config, &this->i2cDeviceHandle)
    );

    this->config.setFromInt(ADS1115_CONFIG_REG_DEF);
    writeConfig();
}

void ADS1115::writeRegister(ads1115_reg_addr_t address, uint16_t data)
{
    uint8_t buffer[3];
    buffer[0] = address;
    buffer[1] = data >> 8;
    buffer[2] = data & 0xff;
    ESP_ERROR_CHECK(i2c_master_transmit(this->i2cDeviceHandle, buffer, 3, -1));
}

uint16_t ADS1115::readRegister(ads1115_reg_addr_t address)
{
    uint8_t writeBuffer[1];
    uint8_t readBuffer[2];
    writeBuffer[0] = address;
    ESP_ERROR_CHECK(i2c_master_transmit_receive(i2cDeviceHandle, writeBuffer, 1, readBuffer, 2, -1));
    uint16_t result = readBuffer[1];
    result += readBuffer[0] << 8;
    return result;
}

constexpr uint16_t OS_MASK = 0x8000;

int16_t ADS1115::readRawValue()
{
    writeConfig();
    // wait until a conversion is ready
    while (!(this->readRegister(ADS1115_REG_ADDR_CONFIG) & OS_MASK))
    {
        vTaskDelay(1);
    }
    return (int16_t) (this->readRegister(ADS1115_REG_ADDR_CONVERSION));
}

void ADS1115::writeConfig()
{
    this->writeRegister(ADS1115_REG_ADDR_CONFIG, this->config.toInt());
}
