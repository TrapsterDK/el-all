#include "simulator.h"

#define SCL 0
#define SDA 1

#define SCK 2
#define MASTER_MOSI 3
#define MASTER_MISO 4

#define SLAVE_MOSI 5
#define SLAVE_MISO 6

void I2C_Sender_Update(Controller *controller)
{
}

Controller *Create_I2C_Sender()
{
    Controller *i2c_sender = Create_Controller("I2C Sender", I2C_Sender_Update);

    return i2c_sender;
}

void I2C_To_SPI_Update(Controller *controller)
{
}

Controller *Create_I2C_To_SPI()
{
    Controller *i2c_to_spi = Create_Controller("I2C To SPI", I2C_To_SPI_Update);

    Set_Pin_Direction(i2c_to_spi, SCL, INPUT);
    Set_Pin_Direction(i2c_to_spi, SDA, INPUT);

    Set_Pin_Direction(i2c_to_spi, SCK, OUTPUT);
    Set_Pin_Direction(i2c_to_spi, MASTER_MOSI, OUTPUT);
    Set_Pin_Direction(i2c_to_spi, MASTER_MISO, INPUT);

    return i2c_to_spi;
}

void SPI_Reciver_Update(Controller *controller)
{
}

Controller *Create_SPI_Reciver()
{
    Controller *spi_reciver = Create_Controller("SPI Reciver", SPI_Reciver_Update);

    Set_Pin_Direction(spi_reciver, SCK, INPUT);
    Set_Pin_Direction(spi_reciver, SLAVE_MOSI, INPUT);
    Set_Pin_Direction(spi_reciver, SLAVE_MISO, OUTPUT);

    return spi_reciver;
}

int main()
{
    Connections *connections = Create_Connections();
    Controller *i2c_sender = Create_I2C_Sender();
    Controller *i2c_to_spi = Create_I2C_To_SPI();
    Controller *spi_reciver = Create_SPI_Reciver();

    Add_Connection(connections, Create_Connection(i2c_sender, i2c_to_spi));
    Add_Connection(connections, Create_Connection(i2c_to_spi, spi_reciver));

    while (1)
    {
        Update_Connections(connections);
    }

    Delete_Connections(connections);
    Delete_Controller(i2c_sender);
    Delete_Controller(i2c_to_spi);
    Delete_Controller(spi_reciver);
    return 0;
}