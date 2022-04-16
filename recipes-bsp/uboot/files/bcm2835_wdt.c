// SPDX-License-Identifier: GPL-2.0
/*
 * Watchdog driver for Broadcom BCM2835
 *
 * Copyright (C) 2017 Paolo Pisati <p.pisati@gmail.com>
 */

#define DEBUG 1

#include <common.h>
#include <efi_loader.h>
#include <asm/io.h>
#include <asm/arch/wdog.h>
#include <dm.h>
#include <log.h>
#include <wdt.h>
#include <clk.h>
#include <asm/io.h>


#define SECS_TO_WDOG_TICKS(x) ((x) << 16)
#define WDOG_TICKS_TO_SECS(x) ((x) >> 16)
#define MAX_TIMEOUT   0xf /* ~15s */

#define PM_RSTC				0x1c
#define PM_RSTS				0x20
#define PM_WDOG				0x24

#define PM_PASSWORD			0x5a000000

#define PM_WDOG_TIME_SET		0x000fffff
#define PM_RSTC_WRCFG_CLR		0xffffffcf
#define PM_RSTS_HADWRH_SET		0x00000040
#define PM_RSTC_WRCFG_SET		0x00000030
#define PM_RSTC_WRCFG_FULL_RESET	0x00000020
#define PM_RSTC_RESET			0x00000102


struct bcm2835_wdt_priv {
	void __iomem *regs;
};


#define PM_RSTC				0x1c
#define PM_RSTS				0x20
#define PM_WDOG				0x24

#define PM_PASSWORD			0x5a000000

#define PM_WDOG_TIME_SET		0x000fffff

#define PM_RSTC_WRCFG_CLR		0xffffffcf
#define PM_RSTS_HADWRH_SET		0x00000040
#define PM_RSTC_WRCFG_SET		0x00000030
#define PM_RSTC_WRCFG_FULL_RESET	0x00000020
#define PM_RSTC_RESET			0x00000102
#define PM_RSTS_PARTITION_CLR          0xfffffaaa


static __efi_runtime_data bool enabled = true;

extern void reset_cpu(ulong ticks);

void hw_watchdog_reset(void)
{
//	if (enabled)
//		reset_cpu(SECS_TO_WDOG_TICKS(MAX_TIMEOUT));
}

void hw_watchdog_init(void)
{
	hw_watchdog_reset();
}



static int bcm2835_wdt_start(struct udevice *dev, u64 timeout, ulong flags)
{
	struct bcm2835_wdt_priv *priv = dev_get_priv(dev);
	uint32_t cur;

	debug("Trying to start ...\n");

	// From linux kernel
//	writel_relaxed(PM_PASSWORD | (SECS_TO_WDOG_TICKS(timeout) &
//				PM_WDOG_TIME_SET), priv->regs + PM_WDOG);
//	cur = readl_relaxed(priv->regs + PM_RSTC);
//	writel_relaxed(PM_PASSWORD | (cur & PM_RSTC_WRCFG_CLR) |
//			PM_RSTC_WRCFG_FULL_RESET, priv->regs + PM_RSTC);
//


	// FROM u-boot bcm6345_wdt.c
/* WDT Value register */
#define WDT_VAL_REG		0x0
#define WDT_VAL_MIN		0x00000002
#define WDT_VAL_MAX		0xfffffffe

/* WDT Control register */
#define WDT_CTL_REG		0x4
#define WDT_CTL_START1_MASK	0x0000ff00
#define WDT_CTL_START2_MASK	0x000000ff
#define WDT_CTL_STOP1_MASK	0x0000ee00
#define WDT_CTL_STOP2_MASK	0x000000ee
	writel(WDOG_TICKS_TO_SECS(66000), priv->regs + WDT_VAL_REG);
	writel(WDT_CTL_START1_MASK, priv->regs + WDT_CTL_REG);
	writel(WDT_CTL_START2_MASK, priv->regs + WDT_CTL_REG);



//	debug("Caling reset_CPU(SECS_TO_WDOG_TICKS(MAX_TIMEOUT) \n");
//	reset_cpu(SECS_TO_WDOG_TICKS(MAX_TIMEOUT));

	return 0;
}

static int bcm2835_wdt_stop(struct udevice *dev)
{
	struct bcm2835_wdt_priv *priv = dev_get_priv(dev);

	writel_relaxed(PM_PASSWORD | PM_RSTC_RESET, priv->regs + PM_RSTC);

	return 0;
}

static int dummy_f1(struct udevice *dev, ulong flags)
{
	debug("NOT IMPLEMENTED ...\n");
	return 0;
}
static int dummy_f2(struct udevice *dev)
{
	debug("NOT IMPLEMENTED ...\n");
	return 0;
}

static const struct wdt_ops bcm2835_wdt_ops = {
	.expire_now = dummy_f1,
	.reset = dummy_f2,
	.start = bcm2835_wdt_start,
	.stop = bcm2835_wdt_stop,
};

static const struct udevice_id bcm2835_wdt_ids[] = {
	{ .compatible = "brcm,bcm2835-pm-wdt" },
	{ /* sentinel */ }
};


static int bcm2835_wdt_probe(struct udevice *dev)
{
	struct bcm2835_wdt_priv *priv = dev_get_priv(dev);

	priv->regs = dev_remap_addr(dev);
	if (!priv->regs)
		return -EINVAL;

	bcm2835_wdt_stop(dev);

	return 0;
}

U_BOOT_DRIVER(wdt_bcm2835) = {
	.name = "wdt_bcm2835",
	.id = UCLASS_WDT,
	.of_match = bcm2835_wdt_ids,
	.ops = &bcm2835_wdt_ops,
	.priv_auto_alloc_size = sizeof(struct bcm2835_wdt_priv),
	.probe = bcm2835_wdt_probe,
};

