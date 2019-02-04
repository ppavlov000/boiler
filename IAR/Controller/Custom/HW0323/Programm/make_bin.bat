bin_boot.exe -f ..\Debug\Exe\CV0323.a90 -o CV0323_sys.bin -i "CleanPRJ CV0323 sys" -j -u 1 -h 0x01000323 -s 0x01000323
bin_boot.exe -f kotel_V01_Cont2.bin -o CV0323_user.bin -j -u 1 -h 0x01000323 -s 0x01000323
 bin_boot.exe -f test_2.bin -o CV0323_user.bin -j -u 1 -h 0x01000323 -s 0x01000323