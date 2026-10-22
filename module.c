// SPDX-License-Identifier: GPL-2.0-only
/*
 * rtc-pcf2131 module
 * Copyright (C) 2026 Sfera Labs S.r.l.
 */

#include <linux/init.h>
#include <linux/module.h>

#include "commons/pcf21xx/pcf21xx.h"

static int __init pcf2131_init(void)
{
	int ret;

	ret = pcf21xx_i2c_register_driver();
	if (ret) {
		pr_err("Failed to register pcf2131 i2c driver: %d\n", ret);
		return ret;
	}

	ret = pcf21xx_spi_register_driver();
	if (ret) {
		pr_err("Failed to register pcf2131 spi driver: %d\n", ret);
		pcf21xx_i2c_unregister_driver();
	}

	return ret;
}
module_init(pcf2131_init)

static void __exit pcf2131_exit(void)
{
	pcf21xx_spi_unregister_driver();
	pcf21xx_i2c_unregister_driver();
}
module_exit(pcf2131_exit)

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Sfera Labs - http://sferalabs.cc");
MODULE_DESCRIPTION("NXP PCF2127/29/31 RTC driver");
MODULE_VERSION(RTC_PCF2131_MODULE_VERSION);
