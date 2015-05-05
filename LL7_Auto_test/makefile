CC=/opt/clanton-tiny/1.4.2/sysroots/i686-pokysdk-linux/usr/bin/i586-poky-linux-uclibc/i586-poky-linux-uclibc-gcc
all:

	$(CC) -o single_connect single_connect.c

	$(CC) -o connect_parser connect_parser.c

	$(CC) -o single_w_r single_w_r.c

	$(CC) -o write_read_parser write_read_parser.c

	$(CC) -o repeat_data repeat_data.c

	$(CC) -o repeat_data_parser repeat_data_parser.c

	$(CC) -o Api_test Api_test.c

	$(CC) -o api_parser api_parser.c

	$(CC) -o error_data error_data.c

	$(CC) -o error_data_parser error_data_parser.c

	$(CC) -o LL7_Auto_test LL7_Auto_test.c

clean:
	rm -r single_connect connect_parser single_w_r write_read_parser repeat_data repeat_data_parser Api_test api_parser error_data error_data_parser LL7_Auto_test
send:
	scp single_connect connect_parser single_w_r write_read_parser repeat_data repeat_data_parser Api_test api_parser error_data error_data_parser LL7_Auto_test kill.sh  run_program.sh root@192.168.2.31:/home/root/LL7_Test
	

