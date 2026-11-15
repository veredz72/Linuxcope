rmmod Tio
rmmod Linuxcope

insmod ../../driver/Tio/Tio.ko
insmod ../../driver/Linuxcope/Linuxcope.ko
../LogControl/Main.out
taskset -c 1-5 ./Main.out


