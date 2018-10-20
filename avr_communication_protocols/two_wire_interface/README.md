SDA -> serial data line
SCK -> serial clock line

*OVERVIEW*:

This is a bidirectional synchronous protocol that controls communication between a master 
device and multiple slave devices (ex: thermostats, EEPROM, etc.) using a 
timing signal from the clock master.

The SDA line is only allowed to change state (HIGH <-> LOW) when the clock line
is low.

Data is only read when the clock line is HIGH.

**START/STOP TRANSACTIONS**:

Start signals are designated as the falling edge while the clock line is held high.
Similarly, the stop signal is designated by a rising edge on the SDA while the SCK
is held high.

SDA: _______                                                                  _________
            \                                                                /
             \ (START - this falling edge)                                  / (STOP - this rising edge)
              \                                                            /
               \__________________________________________________________/
               
SCK: ________________ (clock line held high while this happens)      __________________
                     \                                              /
                      \                                            /
                       \__________________________________________/
                       

_These are the only two times that the SDA is allowed to change state when the SCK
is HIGH. This allows the START/STOP to be uniquely identified._

**DEVICE IDENTIFIERS AND DATA DIRECTION**: 

In order to allow multiple devices to share the same two lines, each slave device
needs to know when its being spoken to. To do this, they are designated unique
7 bit identifiers. 

The 8th bit is used to specify the read/write direction bit. That is, 
whether the master or slave device is going to send data over the line next.

  - 1/HIGH: when the master expects to read data off the line
  - 0/LOW : when the master writes data into the line
  
**ACKNOWLEDGEMENT**

In order to ensure that every byte of data is received successfully, a 9th bit
is sent by the receiver, immediately after each byte, designated the `ACK` bit.

  - 0/LOW:  byte is acknowledged and the sender should continue sending (`ACK`)
  - 1/HIGH: error in transmission and the sender should stop sending/transmission
  should end (`NACK`)
  
**SUMMARY OF ORDER**

So the order of data transmitted now would be:
  - _START_ (falling edge on SDA while the SCK is HIGH)
  - _ADDRESS_ of the targeted slave device
  - _DATA DIRECTION_ bit to let the target device know whether to read/write
  - _DATA_ by byte + `ACK` bit
  
*