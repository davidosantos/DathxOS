cp ./bin/DathxKernel.bin ./boot
grub-mkrescue -o ./Dathx.iso ./boot
virtualbox --startvm Dathx -debug --start-running
#/usr/bin/qemu-system-i386 -enable-kvm -gdb tcp::1234 -readconfig '/home/david/.qemu-launcher/Default'