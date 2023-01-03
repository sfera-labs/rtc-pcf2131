/*
 * PCF2131 RTC C code example
 *
 * To compile: gcc -s -Wall pcf2131_example.c -o pcf2131_example
 *
 *     Copyright (C) 2023 Sfera Labs S.r.l.
 *
 *     For information, visit https://www.sferalabs.cc
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * LICENSE.txt file for more details.
 *
 */

#include <errno.h>
#include <fcntl.h>
#include <linux/rtc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <unistd.h>

#define RTC_DEV "/dev/rtc0"

int main(int argc, char **argv) {
	int fd, ret = 0;
	unsigned int flags;
	struct rtc_time rtc_tm;

	fd = open(RTC_DEV, O_RDONLY);

	if (fd == -1) {
		perror(RTC_DEV);
		exit(errno);
	}

	ret = ioctl(fd, RTC_RD_TIME, &rtc_tm);
	if (ret == -1) {
		perror("ioctl RTC_RD_TIME");
		close(fd);
		exit(errno);
	}

	fprintf(stderr, "Date/time: %d-%d-%d %02d:%02d:%02d.\n",
			rtc_tm.tm_year + 1900, rtc_tm.tm_mon + 1, rtc_tm.tm_mday,
			rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);

	ret = ioctl(fd, RTC_VL_READ, &flags);
	if (ret == -1) {
		perror("ioctl RTC_VL_READ");
		close(fd);
		exit(errno);
	}

	printf("Voltage low flags: 0x%x\n", flags);
	if (flags & RTC_VL_DATA_INVALID)
		printf("> Voltage too low, RTC data is invalid\n");
	if (flags & RTC_VL_BACKUP_LOW)
		printf("> Backup voltage is low\n");
	if (flags & RTC_VL_BACKUP_EMPTY)
		printf("> Backup empty or not present\n");
	if (flags & RTC_VL_ACCURACY_LOW)
		printf("> Voltage is low, RTC accuracy is reduced\n");
	if (flags & RTC_VL_BACKUP_SWITCH)
		printf("> Backup switchover happened\n");

	close(fd);

	return 0;
}
