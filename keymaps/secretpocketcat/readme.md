Use [QMK MSYS](https://msys.qmk.fm/) (or the command line tool of your choice) to compile it with this command:

``qmk compile -kb klor -km secretpocketcat`` 

This will create a file called **klor_default.hex** in your **qmk_firmware** folder.\
Open [QMK Toolbox](https://github.com/qmk/qmk_toolbox) and locate the **klor_default.hex** file.\
Connect the ProMicro/keyboard and press the reset button (or connect the RST and GND pins on the ProMicro). QMK toolbox should show a connected device.\
Press **flash** in QMK toolbox to flash the firmware on your microcontroller.
