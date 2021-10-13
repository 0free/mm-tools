#include <stdio.h>
#include <stdint.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "iic.h"

static int g_i2cfd;
static uint8_t curslave_addr = 0;

static int i2c_open(char *dev)
{
	if ((g_i2cfd = open(dev, O_RDWR)) < 0) {
		printf("Failed to open i2c port\n");
		return 1;
	}
	return 0;
}

static int i2c_close()
{
	close(g_i2cfd);
	g_i2cfd = -1;
	return 0;
}

static int i2c_setslave(uint8_t addr)
{
	curslave_addr = addr;
	if (ioctl(g_i2cfd, I2C_SLAVE, addr) < 0) {
		printf("Unable to find slave addr %x\n", addr);
		return 1;
	}
	return 0;
}

static int i2c_write(unsigned char *wbuf, unsigned int wlen)
{
	ssize_t ret;

	ret = write(g_i2cfd, wbuf, wlen);
	if (ret != wlen) {
		printf("Write to %x failed!(%d-%d)\n", curslave_addr, (int)ret, wlen);
		if (ret < 0)
			return -1;

		return 1;
	}

	return 0;
}

static int i2c_read(unsigned char *rbuf, unsigned int rlen)
{
	ssize_t ret;

	ret = read(g_i2cfd, rbuf, rlen);
	if (ret != rlen) {
		printf("Read from %x failed!(%d-%d)\n", curslave_addr, (int)ret, rlen);
		if (ret < 0)
			return -1;
		return 1;
	}

	return 0;
}

struct i2c_drv rpi_drv = {
	.name = "rpi",
	.i2c_open = i2c_open,
	.i2c_close = i2c_close,
	.i2c_setslave = i2c_setslave,
	.i2c_write = i2c_write,
	.i2c_read = i2c_read,
};
