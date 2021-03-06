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
//        printf("MY INSERT: hw_watchdog_reset()\n");
	struct watchdog_regs *wdog = (struct watchdog_regs *)WDOG1_BASE_ADDR;
	writew(0x5555, &wdog->wsr);
	writew(0xaaaa, &wdog->wsr);
}

void hw_watchdog_init(void)
{
//	printf("MY INSERT: hw_watchdog_init()\n");
	struct watchdog_regs *wdog = (struct watchdog_regs *)WDOG1_BASE_ADDR;
	u16 reg_wcr = readw(&wdog->wcr);
	reg_wcr &= 0x00FF;
	reg_wcr |= 0x0100;
	writew(reg_wcr, &wdog->wcr);
	reg_wcr |= 0x008F;
	writew(reg_wcr, &wdog->wcr);
}


void hw_watchdog_fin(void)
{
	hw_watchdog_reset();
//	printf("MY INSERT: hw_watchdog_fin()\n");
	struct watchdog_regs *wdog = (struct watchdog_regs *)WDOG1_BASE_ADDR;	
	u16 reg_wcr = readw(&wdog->wcr);
	reg_wcr &= 0x00FF;
	reg_wcr |= 0x1300;
	writew(reg_wcr, &wdog->wcr);
}