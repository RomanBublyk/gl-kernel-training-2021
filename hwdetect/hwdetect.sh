#!/bin/sh

echo "===== USB to TTL convertors: =====\n"
ls /dev/ttyUSB* /dev/ttyAMA* 2> /dev/null | tr -d "/dev/"
echo "\n"

echo "===== Flash drives: =====\n"
ls /dev/sdb* 2> /dev/null | tr -d "/dev/"
echo "\n"

echo "===== SD cards: =====\n"
ls /dev/mmcblk* 2> /dev/null | tr -d "/dev/"
echo "\n"

echo "===== I2C: =====\n"
ls /dev/i2c* 2> /dev/null | tr -d "/dev/"
echo "\n"

ls /dev/mmcblk* /dev/i2c* /dev/ttyUSB* \
    /dev/ttyAMA* /dev/sdb* 2> /dev/null | tr -d "/dev/" > tmp_old

echo "===== Changes in /dev tree: =====\n"
while [ 1 ]; do
    ls /dev/mmcblk* /dev/i2c* /dev/ttyUSB* \
        /dev/ttyAMA* /dev/sdb* 2> /dev/null | tr -d "/dev/" > tmp_new
    diff tmp_old tmp_new | sed '1d'
    cat tmp_new > tmp_old
    sleep 1
done
