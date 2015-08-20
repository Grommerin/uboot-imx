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
	u16	wcr;
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
	struct watchdog_regs *wdog = (struct watchdog_regs *)WDOG1_BASE_ADDR;
	printf("MY INSERT: hw_watchdog_init() wmcr\n");
	writew(0x0000, &wdog->wmcr);
	u16 reg_wcr = readw(&wdog->wcr);
	printf("MY INSERT: hw_watchdog_init() read wcr = %#08x\n", reg_wcr);
	reg_wcr &= 0x00FF;
	reg_wcr |= 0x1000;
	printf("MY INSERT: hw_watchdog_init() reg_wcr  = %#08x\n", reg_wcr);
	writew(reg_wcr, &wdog->wcr);
	reg_wcr |= 0x00a7;
	printf("MY INSERT: hw_watchdog_init() reg_wcr  = %#08x\n", reg_wcr);
	printf("MY INSERT: hw_watchdog_init() wcr\n");
	writew(reg_wcr, &wdog->wcr);
	reg_wcr = readw(&wdog->wcr);
	printf("MY INSERT: hw_watchdog_init() read wcr = %#08x\n", reg_wcr);
}
