bin_boot.exe -f ..\Debug\Exe\CV050.a90 -o CV050_sys.bin -i "CleanPRJ CV050 sys" -j -u 1 -h 0x01000500 -s 0x01000500
bin_boot.exe -f kotel_V01_Cont1.bin -o CV050_user.bin -j -u 1 -h 0x01000500 -s 0x01000500
rem bin_boot.exe -f test_2.bin -o CV050_user.bin -j -u 1 -h 0x01000500 -s 0x01000500