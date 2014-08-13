#CHUCKWAGON Firmware

This is the demo code used during our [DEF CON 22 talk](https://www.defcon.org/html/defcon-22/dc-22-speakers.html#Datko). The full slides are [here](https://cryptotronix.files.wordpress.com/2014/08/dc_22_diy_hardware_implant.pdf).

The Arduino sketch can be uploaded to the ATmega32p on the CryptoCape and the bash scripts are used by the target and host.

## Hardware Files

In the Hardware folder, you'll find the schematic, EAGLE CAD files, and BOM for the CHUCKWAGON. You can get the board directly from [OSH Park](https://oshpark.com/shared_projects/FfikIrhc).

### Connecting the CHUCKWAGON

Attach the male VGA adapter to your target. The LED will indicate if power is being supplied from your target. If so, then you can probably receive up to 1A for your implant. If you are using a 5V Logic system, use the SDA and SCL pins directly. If you are using a 3.3V system, use the 3.3V versions. If you do this, you must supply 3.3V to the 3.3V pin.
