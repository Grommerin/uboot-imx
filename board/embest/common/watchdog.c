/*
 * watchdog.c - driver for i.mx on-chip watchdog
 *
 * Licensed under the GPL-2 or later.
 */

#include <common.h>
#include <asm/io.h>
#include <watchdog.h>
#include <asm/arch/mx6.h>

struct watchdog_regs {
	u8	wcr_time;
	u8	wcr_ctrl;
	u16	wsr;
	u16	wrsr;
	u16	wicr;
	u16	wmcr;
};

void hw_watchdog_reset(void)
{
        printf("MY INSERT: hw_watchdog_reset()\n");
	struct watchdog_regs *wdog = (struct watchdog_regs *)WDOG1_BASE_ADDR;
	writew(0x5555, &wdog->wsr);
	writew(0xaaaa, &wdog->wsr);
}

void hw_watchdog_init(void)
{
	printf("MY INSERT: hw_watchdog_init()\n");
	struct watchdog_regs *wdog = (struct watchdog_regs *)WDOG1_BASE_ADDR;
	writew(0x03, &wdog->wcr_time);
	writew(0xa7, &wdog->wcr_ctrl);
}


void hw_watchdog_fin(void)
{
	printf("MY INSERT: hw_watchdog_fin()\n");
	struct watchdog_regs *wdog = (struct watchdog_regs *)WDOG1_BASE_ADDR;
	writew(0x30, &wdog->wcr_ctrl);
}