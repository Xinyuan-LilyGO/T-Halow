To pair two TX-AH-RX00Ps, follow the following steps:

1. Check the screen printing on the lower right corner of the module. 7P means 700M, 868 means 868M, and 9P means 900M. Only modules with the same transmission frequency can be successfully equipped.

2. Suppose to use two modules that have downloaded USB firmware 7P of the development board, connect the two modules to the serial port, use the `AT+MODE=ap` command to set one device to ap mode, and use the `AT+mode=sta` command to set the other device to sta mode

3. When pairing, the AP device and STA device need to use the `AT+PAIR=1` command `AT+PAIR=0` command to stop the pairing

4. Note: The print serial port of USB firmware is A10/A11, and the print serial port of other firmware is A12/A13