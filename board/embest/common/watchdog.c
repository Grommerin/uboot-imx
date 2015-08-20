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
	printf("MY INSERT: hw_watchdog_init()\n");
	struct watchdog_regs *wdog = (struct watchdog_regs *)WDOG1_BASE_ADDR;
	u16 reg_wcr = readw(&wdog->wcr);
	reg_wcr &= 0x00FF;
	reg_wcr |= 0x0300;
	writew(reg_wcr, &wdog->wcr);
	reg_wcr |= 0x00a7;
	writew(reg_wcr, &wdog->wcr);
}


void hw_watchdog_fin(void)
{
	printf("MY INSERT: hw_watchdog_fin()\n");
	struct watchdog_regs *wdog = (struct watchdog_regs *)WDOG1_BASE_ADDR;	
	u16 reg_wcr = readw(&wdog->wcr);
	printf("MY INSERT: hw_watchdog_fin()     wcr = %#08x\n", readw(&wdog->wcr));
	printf("MY INSERT: hw_watchdog_fin() reg_wcr = %#08x\n", reg_wcr);
	reg_wcr |= 0x0002;
	printf("MY INSERT: hw_watchdog_fin() reg_wcr = %#08x\n", reg_wcr);
	writew(reg_wcr, &wdog->wcr);
	writew(reg_wcr, &wdog->wcr);
	printf("MY INSERT: hw_watchdog_fin()     wcr = %#08x\n", readw(&wdog->wcr));
	reg_wcr &= 0xFFFB;
	printf("MY INSERT: hw_watchdog_fin() reg_wcr = %#08x\n", reg_wcr);
	writew(reg_wcr, &wdog->wcr);
	writew(reg_wcr, &wdog->wcr);
	writew(0x0000, &wdog->wmcr);
	printf("MY INSERT: hw_watchdog_fin()     wcr = %#08x\n", readw(&wdog->wcr));
	writew(0xFF00, &wdog->wcr);
	writew(0xFF00, &wdog->wcr);
	printf("MY INSERT: hw_watchdog_fin()     wcr = %#08x\n", readw(&wdog->wcr));
}