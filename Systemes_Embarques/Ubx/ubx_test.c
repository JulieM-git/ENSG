/* Par Julie Marcuzzi */

#include <stdio.h>

typedef struct 
{
	unsigned char header1; // 1
	unsigned char header2;  // 1
	unsigned char id1;  // 1
	unsigned char id2;  // 1
	short length; // 2
	unsigned char payload[200];
	unsigned char ck_a; // 1
	unsigned char ck_b; // 1
} Message;

typedef struct 
{
	unsigned int iTOW; // 4
	unsigned int tAcc; // 4
	unsigned int nano; // 4 	
	short year; // 2 	
	unsigned char month; // 1
	unsigned char day; // 1 
	unsigned char hour; // 1 
	unsigned char min; // 1 
	unsigned char sec; // 1
	unsigned char valid; // 1
} MessageUTC;

int main (int argc, char *argv[])
{

	unsigned char data[] = {0xb5, 0x62, 0x01, 0x21, 0x14, 0x00, 0x60, 0x12, 0xe7, 0x1e, 0x0d, 0x00, 0x00, 0x00, 0x6c, 0x77, 0x00, 0x00, 0xe0, 0x07, 0x07, 0x17, 0x00, 0x00, 0x2b, 0x07, 0xd4, 0x01};

	Message message;
	message = *(Message*)&data;

	printf("%x\n", message.payload[message.length]);
	printf("%x\n", message.payload[message.length+1]);
	message.ck_a = message.payload[message.length];
	message.ck_b = message.payload[message.length + 1];
	
	// Verification de Checksum
	unsigned char CK_A=0;
	unsigned char CK_B=0;
	unsigned int i;
	for (i=2;i<sizeof(data)-2;i++)
	{
		CK_A = CK_A + data[i];
		CK_B = CK_B + CK_A;
	}
	
	printf("%x\n", CK_A);
	printf("%x\n", CK_B);
	
	// Affiche si le checksum correspond
	if (CK_A == message.ck_a && CK_B ==message.ck_b)
	{
		printf("OK!!!!!\n");
		MessageUTC messageUTC;
		messageUTC = *(MessageUTC*)&message.payload;

		printf("%d %d %d %d-%d-%d %d:%d:%d %d\n", messageUTC.iTOW, messageUTC.tAcc, messageUTC.nano, messageUTC.year, messageUTC.month, messageUTC.day, messageUTC.hour, messageUTC.min, messageUTC.sec,messageUTC.valid);
	}
	else
	{
		printf("BAD!!!!!\n");
	}
}


	
