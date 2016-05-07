cp ./bin/DathxKernel.bin ./boot
grub-mkrescue -o ./Dathx.iso ./boot
virtualbox --startvm Dathx --dbg 
#/usr/bin/qemu-system-i386  -gdb tcp::1234 -readconfig "/home/david/.qemu-launcher/Default"