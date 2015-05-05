CC=/opt/clanton-tiny/1.4.2/sysroots/i686-pokysdk-linux/usr/bin/i586-poky-linux-uclibc/i586-poky-linux-uclibc-gcc
all:
	$(CC) -o LL7_Api_test LL7_Api_test.c
	$(CC) -o LL7_SelfTest_test LL7_SelfTest_test.c
clean:
	rm LL7_Api_test LL7_SelfTest_test
send:
	scp LL7_Api_test LL7_SelfTest_test root@192.168.2.31:/home/root/LL7_Test
