#include "enc28j60.h"

/* Documents
 *
 * https://narodstream.ru/arm/download/LESSON68/ENC28J60_errata.pdf
 * https://ww1.microchip.com/downloads/en/devicedoc/80349c.pdf
 * https://ww1.microchip.com/downloads/en/devicedoc/39662c.pdf
 * 
 */

#define ENC_HOST        SPI2_HOST

#define PIN_NUM_MISO    25
#define PIN_NUM_MOSI    23
#define PIN_NUM_CLK     19
#define PIN_NUM_CS      22

static inline esp_err_t SPI_Transmit(spi_device_handle_t handle, uint8_t* tx_buffer, uint8_t* rx_buffer, int length) {
    return spi_device_polling_transmit(handle, &(spi_transaction_t) {
        .flags = SPI_TRANS_USE_RXDATA | SPI_TRANS_USE_TXDATA | SPI_TRANS_CS_KEEP_ACTIVE,
        .length = length * 8,
        .tx_buffer = tx_buffer,
        .rx_buffer = rx_buffer,
    });
}

void ENC28J60_PowerOnReset(void)
{
    esp_err_t ret;
    spi_device_handle_t enc_spi_handle;

    ret = spi_bus_initialize(ENC_HOST, &(spi_bus_config_t) {
        .miso_io_num = PIN_NUM_MISO,
        .mosi_io_num = PIN_NUM_MOSI,
        .sclk_io_num = PIN_NUM_CLK,
        .max_transfer_sz = SOC_SPI_MAXIMUM_BUFFER_SIZE
    }, SPI_DMA_CH_AUTO);

    ESP_ERROR_CHECK(ret);

    ret = spi_bus_add_device(ENC_HOST, &(spi_device_interface_config_t) {
        .clock_speed_hz = SPI_MASTER_FREQ_10M,  //Clock out at 10 MHz
        .mode = 0,                              //SPI mode 0
        .spics_io_num = PIN_NUM_CS,             //CS pin
        .queue_size = 7,                        //We want to be able to queue 7 transactions at a time
    }, &enc_spi_handle);

    ESP_ERROR_CHECK(ret);

    return;
}

