bin_boot.exe -f ..\Debug\Exe\CV0324.a90 -o CV0324_sys.bin -i "CleanPRJ CV0324 sys" -j -u 1 -h 0x01000324 -s 0x01000324
bin_boot.exe -f test.bin -o CV0324_user.bin -j -u 1 -h 0x01000324 -s 0x01000324