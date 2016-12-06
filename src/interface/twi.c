#include "twi.h"

static volatile uint8_t i2c_state;
static volatile uint8_t i2c_slarw;
static volatile uint8_t i2c_sendStop;			// should the transaction end with a stop
static volatile uint8_t i2c_inRepStart;			// in the middle of a repeated start

static void (*i2c_onSlaveTransmit)(void);
static void (*i2c_onSlaveReceive)(uint8_t*, int);

static uint8_t i2c_masterBuffer[I2C_BUFFER_LENGTH];
static volatile uint8_t i2c_masterBufferIndex;
static volatile uint8_t i2c_masterBufferLength;

static uint8_t i2c_txBuffer[I2C_BUFFER_LENGTH];
static volatile uint8_t i2c_txBufferIndex;
static volatile uint8_t i2c_txBufferLength;

static uint8_t i2c_rxBuffer[I2C_BUFFER_LENGTH];
static volatile uint8_t i2c_rxBufferIndex;

static volatile uint8_t i2c_error;

#define I2C_DELAY 0
/* 
 * Function i2c_init
 * Desc     readys twi pins and sets twi bitrate
 * Input    none
 * Output   none
 */
void i2c_init(void)
{
  // initialize state
  i2c_state = I2C_READY;
  i2c_sendStop = true;		// default value
  i2c_inRepStart = false;

  I2C_PIN_SET;
  I2C_CLK_LOW;
  i2c_stop();
}

/* 
 * Function i2c_disable
 * Desc     disables twi pins
 * Input    none
 * Output   none
 */
void i2c_disable(void)
{
	I2C_PIN_SET;
}

/* 
 * Function i2c_slaveInit
 * Desc     sets slave address and enables interrupt
 * Input    none
 * Output   none
 */
void i2c_setAddress(uint8_t address)
{

}

/* 
 * Function i2c_setClock
 * Desc     sets twi bit rate
 * Input    Clock Frequency
 * Output   none
 */
void i2c_setFrequency(uint32_t frequency)
{

}

/* 
 * Function i2c_readFrom
 * Desc     attempts to become twi bus master and read a
 *          series of bytes from a device on the bus
 * Input    address: 7bit i2c device address
 *          data: pointer to byte array
 *          length: number of bytes to read into array
 *          sendStop: Boolean indicating whether to send a stop at the end
 * Output   number of bytes read
 */
uint8_t i2c_readFrom(uint8_t address, uint8_t* data, uint8_t length, uint8_t sendStop)
{
	  uint8_t i;

	  // ensure data will fit into buffer
	  if(I2C_BUFFER_LENGTH < length){
	    return 0;
	  }

	  i2c_state = I2C_MRX;
	  i2c_sendStop = sendStop;
	  // reset error state (0xFF.. no error occured)
	  i2c_error = 0xFF;

	  // initialize buffer iteration vars
	  i2c_masterBufferIndex = 0;
	  i2c_masterBufferLength = length-1;  // This is not intuitive, read on...
	  // On receive, the previously configured ACK/NACK setting is transmitted in
	  // response to the received byte before the interrupt is signalled.
	  // Therefor we must actually set NACK when the _next_ to last byte is
	  // received, causing that NACK to be sent in response to receiving the last
	  // expected byte of data.

	  // build sla+w, slave device address + w bit
	  i2c_slarw = I2C_READ;
	  i2c_slarw |= address << 1;
//******************************************
	irq_disable();
	i2c_start();
	i2c_sendChar(i2c_slarw);
	for (i=0; i<length; i++) {
		*data=i2c_getChar();
		data++;
		i2c_masterBufferIndex++;
	}
	if (sendStop) {
		i2c_stop();
		irq_enable();
	}
	else {
		  i2c_inRepStart = true;	// we're gonna send the START
		  // don't enable the interrupt. We'll generate the start, but we
		  // avoid handling the interrupt until we're in the next transaction,
		  // at the point where we would normally issue the start.
		  i2c_state = I2C_READY;
	}
//********************************************
  if (i2c_masterBufferIndex < length)
    length = i2c_masterBufferIndex;

  // copy twi buffer to data
  for(i = 0; i < length; ++i){
    data[i] = i2c_masterBuffer[i];
  }
	
  return length;
}

/* 
 * Function i2c_writeTo
 * Desc     attempts to become twi bus master and write a
 *          series of bytes to a device on the bus
 * Input    address: 7bit i2c device address
 *          data: pointer to byte array
 *          length: number of bytes in array
 *          wait: boolean indicating to wait for write or not
 *          sendStop: boolean indicating whether or not to send a stop at the end
 * Output   0 .. success
 *          1 .. length to long for buffer
 *          2 .. address send, NACK received
 *          3 .. data send, NACK received
 *          4 .. other twi error (lost bus arbitration, bus error, ..)
 */
uint8_t i2c_writeTo(uint8_t address, uint8_t* data, uint8_t length, uint8_t wait, uint8_t sendStop)
{
	  uint8_t i;

	  // ensure data will fit into buffer
	  if(I2C_BUFFER_LENGTH < length){
	    return 1;
	  }

	  i2c_state = I2C_MTX;
	  i2c_sendStop = sendStop;
	  // reset error state (0xFF.. no error occured)
	  i2c_error = 0xFF;

	  // initialize buffer iteration vars
	  i2c_masterBufferIndex = 0;
	  i2c_masterBufferLength = length;

	  // copy data to twi buffer
	  for(i = 0; i < length; ++i){
	    i2c_masterBuffer[i] = data[i];
	  }

	  // build sla+w, slave device address + w bit
	  i2c_slarw = I2C_WRITE;
	  i2c_slarw |= address << 1;

//*************************************
	irq_disable();
	i2c_start();
	i2c_sendChar(i2c_slarw);
	for (i=0; i<length; i++) {
		i2c_sendChar(*data);
		data++;
	}
	if (sendStop) {
		i2c_stop();
		irq_enable();
	}
	else {
		  i2c_inRepStart = true;	// we're gonna send the START
		  // don't enable the interrupt. We'll generate the start, but we
		  // avoid handling the interrupt until we're in the next transaction,
		  // at the point where we would normally issue the start.
		  i2c_state = I2C_READY;
	}
//*************************************
	  if (i2c_error == 0xFF)
	    return 0;	// success
	  else
	    return 4;	// other twi error
}

/* 
 * Function i2c_transmit
 * Desc     fills slave tx buffer with data
 *          must be called in slave tx event callback
 * Input    data: pointer to byte array
 *          length: number of bytes in array
 * Output   1 length too long for buffer
 *          2 not slave transmitter
 *          0 ok
 */
uint8_t i2c_transmit(const uint8_t* data, uint8_t length)
{
  uint8_t i;

  // ensure data will fit into buffer
  if(I2C_BUFFER_LENGTH < (i2c_txBufferLength+length)){
    return 1;
  }
  
  // ensure we are currently a slave transmitter
  if(I2C_STX != i2c_state){
    return 2;
  }
  
  // set length and copy data into tx buffer
  for(i = 0; i < length; ++i){
    i2c_txBuffer[i2c_txBufferLength+i] = data[i];
  }
  i2c_txBufferLength += length;
  
  return 0;
}

/* 
 * Function i2c_attachSlaveRxEvent
 * Desc     sets function called before a slave read operation
 * Input    function: callback function to use
 * Output   none
 */
void i2c_attachSlaveRxEvent( void (*function)(uint8_t*, int) )
{
  i2c_onSlaveReceive = function;
}

/* 
 * Function i2c_attachSlaveTxEvent
 * Desc     sets function called before a slave write operation
 * Input    function: callback function to use
 * Output   none
 */
void i2c_attachSlaveTxEvent( void (*function)(void) )
{
  i2c_onSlaveTransmit = function;
}

/* 
 * Function i2c_reply
 * Desc     sends byte or readys receive line
 * Input    ack: byte indicating to ack or to nack
 * Output   none
 */
void i2c_reply(uint8_t ack)
{
  // transmit master read ready signal, with or without ack

	if (ack) {
		I2C_DATA_LOW;
		delay_us(I2C_DELAY);
		I2C_CLK_HIGH;
		delay_us(I2C_DELAY);

		I2C_CLK_LOW;
		delay_us(I2C_DELAY);
		I2C_DATA_HIGH;
	}
	else {
		I2C_DATA_HIGH;
		delay_us(I2C_DELAY);
		I2C_CLK_HIGH;
		delay_us(I2C_DELAY);

		I2C_CLK_LOW;
		delay_us(I2C_DELAY);
		I2C_DATA_HIGH;
	}

}

void i2c_start(void)
{
	I2C_DATA_HIGH;
	delay_us(I2C_DELAY);
	I2C_CLK_HIGH;
	delay_us(I2C_DELAY);
	I2C_DATA_LOW;
	delay_us(I2C_DELAY);
	I2C_CLK_LOW;
	delay_us(I2C_DELAY);
}
/* 
 * Function i2c_stop
 * Desc     relinquishes bus master status
 * Input    none
 * Output   none
 */
void i2c_stop(void)
{
  // send stop condition

  // wait for stop condition to be exectued on bus
  // TWINT is not set after a stop condition!

	I2C_CLK_LOW;
	delay_us(I2C_DELAY);
	I2C_DATA_LOW;
	delay_us(I2C_DELAY);
	I2C_CLK_HIGH;
	delay_us(I2C_DELAY);
	I2C_DATA_HIGH;
	delay_us(I2C_DELAY);

  // update twi state
  i2c_state = I2C_READY;
}

/* 
 * Function i2c_releaseBus
 * Desc     releases bus control
 * Input    none
 * Output   none
 */
void i2c_releaseBus(void)
{
  // release bus
	 I2C_PIN_SET;
  // update twi state
  i2c_state = I2C_READY;
}

void i2c_sendChar(unsigned char data)
{
	unsigned char i=0;
	for(i=0;i<8;i++)
	{
		if((data<<i)&BIT7)
			I2C_DATA_HIGH;
		else
			I2C_DATA_LOW;
		I2C_CLK_HIGH;
		delay_us(I2C_DELAY);
		I2C_CLK_LOW ;
		delay_us(I2C_DELAY);
	}
	//----最后1个CLK，接收从机应答位，但不作判断----
	I2C_CLK_HIGH  ;
	delay_us(I2C_DELAY);
	I2C_CLK_LOW;
	delay_us(I2C_DELAY);
}

unsigned char i2c_getChar(void)
{
	unsigned char i=0;
	unsigned char Temp=0;
	I2C_DATA_HIGH;
	for(i=0;i<8;i++)
	{
		I2C_CLK_HIGH;
		delay_us(I2C_DELAY);
		Temp=Temp<<1;
		if((I2C_DATA_IN)==BIT7)		//先收高位
			Temp |=BIT0;
		delay_us(I2C_DELAY);
		I2C_CLK_LOW ;
		delay_us(I2C_DELAY);
	}
	//-----应答位-----
	i2c_reply(1);
	return(Temp);
}
