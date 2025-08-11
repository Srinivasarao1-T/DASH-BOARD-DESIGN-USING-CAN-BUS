DASH BOARD DESIGN USING CAN BUS

Description: A multi-node embedded system using CAN Bus to simulate a vehicle dashboard displaying engine temperature, fuel percentage, and left/right indicators. 

Key Components:
Main Node: Reads DS18B20 temperature sensor, shows RTC and fuel level on LCD, handles indicator signals.

Fuel Node: 
Reads fuel via ADC and sends data to Main Node.

Indicator Node:
Receives indicator status from Main Node and toggles LEDs. 

Hardware: 
LPC2129 microcontroller, MCP2551 CAN transceiver, LCD, LEDs, switches, DS18B20 temperature sensor, fuel gauge,USB to UART convertor.

Software: 
Embedded C, Keil µVision, Flash Magic. 

MAIN NODE:
Read the temperature information and display it on LCD along with RTC information (TIME, DATE & DAY). And based on the interrupt generated, need to send the indicator signal to the indicator node and display the indicators status also on LCD. And one more task of this main node is receiving the fuel node information and display it on LCD. 

INDICATOR NODE:
Continuously waiting for the data from the main NODE using CAN.  If any data is received from main NODE, based on that it is controlling the indicator signals connected to microcontroller. Refer the block diagram for how to give the indicator signals with the help of LED’S

FUEL NODE: 
Continuously reading the Fuel gauge sensor information with the help of on chip ADC and send that information to the main node.
