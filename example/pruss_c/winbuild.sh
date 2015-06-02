
# compile support library without optimization
# enabled to keep argument passing convention

D:\BBB/pru_sdk/pru_2.0.0B2/bin/clpru --silicon_version=2 --hardware_mac=on -iD:\BBB/pru_sdk/pru_2.0.0B2/include -iD:\BBB/pru_sdk/pru_2.0.0B2/lib -c pru_hal.c


D:\BBB/pru_sdk/pru_2.0.0B2/bin/clpru \
--silicon_version=2 \
--hardware_mac=on \
-iD:\BBB/pru_sdk/pru_2.0.0B2/include \
-iD:\BBB/pru_sdk/pru_2.0.0B2/lib \
-O3 \
-c \
pru_main.c


# compile and link
# optimizations allowed

D:\BBB/pru_sdk/pru_2.0.0B2/bin/clpru \
--silicon_version=2 \
--hardware_mac=on \
-iD:\BBB/pru_sdk/pru_2.0.0B2/include \
-iD:\BBB/pru_sdk/pru_2.0.0B2/lib \
-z \
pru_main.obj pru_hal.obj -llibc.a \
-m pru_main.map \
-o pru_main.elf \
D:\BBB/pru_sdk/pru_2.0.0B2/example/AM3359_PRU.cmd


# convert ELF to binary file pru_main.bin

D:\BBB/pru_sdk/pru_2.0.0B2/bin/hexpru \
D:\BBB/pru_sdk/pru_2.0.0B2/bin.cmd \
./pru_main.elf


# build host program

make clean
make START_ADDR=`./get_start_addr.sh ./pru_main.elf`