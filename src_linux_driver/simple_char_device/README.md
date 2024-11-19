```
make
insmod simple_char_driver.ko

# major_number in dmesg or /var/log/kernel.log
mknod /dev/simple_char_device c <major_number> 0

echo "Hello, World!" > /dev/simple_char_device
cat /dev/simple_char_device

rmmod simple_char_driver
rm /dev/simple_char_device

```