#include "sys.h"

FILE_STRUCT* 			tempFile;
FILE_STRUCT* 			tempCache;
FAT*					driver;

DIR_STATE_STRUCT		*dp;
DIR_ENTRY				*ep;

struct rtc 				sysTimeClock;
struct key_buf 			input;

unsigned int 			timerz;
unsigned int 			key;

void ds2_main() {

	if(ds2io_init(1024))
		goto _failure;

	if(ConsoleInit(BLACK_COLOR, WHITE_COLOR, DOWN_SCREEN, 10))
		goto _failure;

	if(fat_init())
		goto _failure;

	tempFile = fat_fopen("fat:/DATA/log/unidaOS.txt", "r+");
	tempCache = fat_fopen("fat:/DATA/TEMP/temp", "r+");

	Start();

_failure:
	ds2_plug_exit();
}

void Start() {

	ClearConsole();

	printf("Welcome to unidaOS %s\n", VERSION);
	printf("\t\tPress Select to Exit.\n"
		   "\t\tPress Y for Soft Reset.\n"
	   	   "\t\t\tInput Control\n"
		   "(A) - Program Counter\n"
	       "(B) - System Time\n"
		   "(X) - Filesystem Information\n");

	while(1) {
		Update();
		Draw(0);
	}
}

void Update() {

	key = getInput(&input);

	if(key) {
		if(input.key & KEY_TOUCH) {
			ClearConsole();
		} else if(input.key & KEY_UP) {
			printf("Up\n");
		} else if(input.key & KEY_DOWN) {
			printf("Down\n");
		} else if(input.key & KEY_LEFT) {
			printf("Left\n");
		} else if(input.key & KEY_RIGHT) {
			printf("Right\n");
		} else if(input.key & KEY_A) {
			Time();
		} else if(input.key & KEY_B) {
			ReadClock();
		} else if(input.key & KEY_X) {
			SettingInfo();
		} else if(input.key & KEY_Y) {
			Start();
		} else if(input.key & KEY_START) {
			printf("Start\n");
		} else if(input.key & KEY_SELECT) {
			SystemExit();
		} else if(input.key & KEY_R) {
			printf("R\n");
		} else if(input.key & KEY_LID) {
			printf("Lid Was Closed\n");
		} else if(input.key & KEY_L) {
			printf("L\n");
		}
	}
}

void Draw(int screen) {

	if (!screen) {
		ds2_clearScreen(UP_SCREEN, BACK_COLOR);
		ds2_flipScreen(UP_SCREEN, 0);
	} else if (screen) {
		ds2_clearScreen(DOWN_SCREEN, BACK_COLOR);
		ds2_flipScreen(DOWN_SCREEN, 0);
	}
}

void ReadClock() {

	ClearConsole();

	printf("\n\t\t[Time]\n");

	ds2_getTime(&sysTimeClock);

	unsigned char year = sysTimeClock.year;
	unsigned char month = sysTimeClock.month;
	unsigned char day = sysTimeClock.day;

	fat_fprintf(tempFile, "\n24Hr Cloc - %d : %d : %d ", sysTimeClock.hours, sysTimeClock.minutes, sysTimeClock.seconds);
	fat_fprintf(tempFile, "\nTodays Date - %d : %d : %d ", sysTimeClock.month, sysTimeClock.day, sysTimeClock.year);

	printf("24Hr Clock   - %d : %d : %d \n", sysTimeClock.hours, sysTimeClock.minutes, sysTimeClock.seconds);
	printf("Todays Date  - %d-%d-%d\n", sysTimeClock.month, sysTimeClock.day, sysTimeClock.year);
}

void ReadDir() {

	key = getInput(&input);

	ClearConsole();

	printf("\n\t[Device Read]\n");

	//TODO:

	printf("\nCouldn't open the directory\n");
}

void ClearConsole() {
	int i = 0;
	do {
		printf("\n");
		++i;
	} while (i < MAX_LINES);
}

void SystemExit() {

	ClearConsole();

	printf("\n\tClosing Files...\n");

	fat_fclose(tempFile);
	fat_fclose(tempCache);

	sleep(256);

	printf("\n\tSuccess!\n\tSend Term Signal...\n");

	sleep(128);

	ds2_plug_exit();
}

int Load() {

	ClearConsole();

	//TODO:

	return 1;
}

int Time() {

	ClearConsole();

	struct key_buf input;
	unsigned int key = getInput(&input);

	printf("\n\t\t[Timer]\n");

	char *strz = "Welcome To unidaOS";

	timerz = getSysTime();

	printf("%s - %d\n", strz, timerz);

	if(!fat_fprintf(tempFile, "\n%s - %d", strz, timerz))
		return -1;

	return 1;
}

int SettingInfo() {

	ClearConsole();

	unsigned int fStart 		= 	driver->fatStart;
	unsigned int fSectorPer 	= 	driver->sectorsPerFat;
	unsigned int fLastCluster 	=	driver->lastCluster;

	unsigned int fSize			=	((fLastCluster - fStart) * fSectorPer);

	unsigned int totalSectors 	= 	tempCache->partition->numberOfSectors;
	unsigned int secPerCluster	=	tempCache->partition->sectorsPerCluster;
	unsigned int bytePerSec 	= 	tempCache->partition->bytesPerSector;
	unsigned int partitionSize  = 	tempCache->partition->totalSize;
	unsigned int rootStart 		= 	tempCache->partition->rootDirStart;

	//unsigned int calc1			=	(totalSectors * bytePerSec);
	unsigned int buffer 		= 	(partitionSize - (partitionSize * 2));
	unsigned int megaSize 		= 	((buffer / 1000) / 8);
	float gigaSize				=	((megaSize / 1000) / 10);


	fat_fprintf(tempFile, "\n[Device Info] ");
	fat_fprintf(tempFile, "\nPartition Size        - %d ", buffer);
	fat_fprintf(tempFile, "\nPartition Size MB     - %d ", megaSize);
	fat_fprintf(tempFile, "\nPartition Size GB     - %.2f ", gigaSize);
	fat_fprintf(tempFile, "\nTotal Sectors         - %d ", totalSectors);
	fat_fprintf(tempFile, "\nBytes Per Sec         - %d ", bytePerSec);
	fat_fprintf(tempFile, "\nRoot on Disk          - %d ", rootStart);

	printf("\t[Device Info] \n");
	printf("Partition Size		- %d\n", buffer);
	printf("Partition Size MB	- %d\n", megaSize);
	printf("Partition Size GB	- %.2f\n", gigaSize);
	printf("Total Sectors		- %d\n", totalSectors);
	printf("Bytes Per Sec		- %d\n", bytePerSec);
	printf("Root on Disk		- %d\n", rootStart);

	return 1;
}
