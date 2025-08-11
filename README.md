Description: A multi-node embedded system using CAN Bus to simulate a vehicle dashboard displaying engine temperature, fuel percentage, and left/right indicators. 
Key Components:
Main Node: Reads DS18B20 temperature sensor, shows RTC and fuel level on LCD, handles indicator signals.
Fuel Node: Reads fuel via ADC and sends data to Main Node.
Indicator Node: Receives indicator status from Main Node and toggles LEDs. 
Hardware: LPC2129 microcontroller, MCP2551 CAN transceiver, LCD, LEDs, switches, DS18B20 temperature sensor, fuel gauge,USB to UART converter. 
Software: Embedded C, Keil µVision, Flash Magic.
SEQUENCE TO BE FOLLOWED FOR IMPLEMENTATION:
->Create New Folder in your server/laptop/PC and save that folder with your project name
->Individually can check each and every module.
->First check lcd to display character constant, string constant and integer constant.
->Next check the on-chip ADC by connecting variable voltage (from potentiometer) and display input value on LCD.
->Then develop logic for reading the Fuel gauge sensor information by using on-chip ADC and display it (Fuel %) on LCD.
->Then develop logic for reading the temperature sensor (Engine temperature) information and display it (engine temperature) on LCD. (refer LMS for DS18B20 temperature working code)
->Then check the external interrupt (EINT0 & EINT1) working condition with the help of basic program. 
->Then refer the LMS for on-chip RTC working code and test it on hardware board.
->Then download the CAN basic code from LMS and test it on hardware boards.
->Once all the above modules are checked then start preparing the main code for each node
