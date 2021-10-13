/*
 * MM Upgrade program for avalon4
 *
 * Upgrade MM firmware through i2c
 *
 * By Mikeqin, 2014
 */
#include "stdio.h"
#include "getopt.h"
#include "api.h"

static void help(void)
{
	printf("Usage: mm-tools [options] ...\n"
		"  -h --help\t\t\tPrint this help message\n"
		"  -c --coretest\t\t\tEnter coretest function\n"
		"  -r --radiator\t\t\tEnter radiator mode\n"
		"  -f --file\t\t\tSpecifies the upgrade file\n"
		"  -R --reboot\t\t\tReboot mm modulars\n"
		" <run without options will enter the basic function>\n\n"
		);
}

static struct option opts[] = {
	{ "help", 0, 0, 'h' },
	{ "coretest", 0, 0, 'c' },
	{ "radiator", 0, 0, 'r' },
	{ "file", 1, 0, 'f' },
	{ "reboot", 0, 0, 'R' },
	{ 0, 0, 0, 0 }
};

int main(int argc, char **argv)
{
	int c, option_index = 0;
	uint16_t freq[3], voltage = 200;

	c = getopt_long(argc, argv, "hcrf:R", opts, &option_index);
	switch (c) {
		case 'f':
			printf("Enter mboot mode with upgrade file: %s\n", optarg);
			mboot(optarg);
			break;
		case 'h':
			help();
			break;
		case 'c':
			printf("Enter coretest function\n");
			mm_coretest(64, freq, voltage);
			break;
		case 'r':
			printf("Enter radiator mode\n");
			set_radiator_mode();
			break;
		case 'R':
			printf("Rebooting mm modulars\n");
			mreboot();
			break;
		default:
			printf("Enter mboot mode\n");
			mboot("./mm.mcs");
			break;
	}

	return 0;
}

