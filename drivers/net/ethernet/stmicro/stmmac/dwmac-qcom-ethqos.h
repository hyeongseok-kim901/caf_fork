/* SPDX-License-Identifier: GPL-2.0-only */
/* Copyright (c) 2021, The Linux Foundation. All rights reserved.
 */
#ifndef	_DWMAC_QCOM_ETHQOS_H
#define	_DWMAC_QCOM_ETHQOS_H

#define DRV_NAME "qcom-ethqos"
#define ETHQOSDBG(fmt, args...) \
	pr_debug(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args)
#define ETHQOSERR(fmt, args...) \
	pr_err(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args)
#define ETHQOSINFO(fmt, args...) \
	pr_info(DRV_NAME " %s:%d " fmt, __func__, __LINE__, ## args)
#define RGMII_IO_MACRO_CONFIG		0x0
#define SDCC_HC_REG_DLL_CONFIG		0x4
#define SDCC_HC_REG_DDR_CONFIG		0xC
#define SDCC_HC_REG_DLL_CONFIG2		0x10
#define SDC4_STATUS			0x14
#define SDCC_USR_CTL			0x18
#define RGMII_IO_MACRO_CONFIG2		0x1C
#define EMAC_HW_NONE 0
#define EMAC_HW_v2_1_1 0x20010001
#define EMAC_HW_v2_1_2 0x20010002
#define EMAC_HW_v2_3_0 0x20030000
#define EMAC_HW_v2_3_1 0x20030001
#define EMAC_HW_vMAX 9

struct ethqos_emac_por {
	unsigned int offset;
	unsigned int value;
};

static const struct ethqos_emac_por emac_v2_3_0_por[] = {
	{ .offset = RGMII_IO_MACRO_CONFIG,	.value = 0x00C01343 },
	{ .offset = SDCC_HC_REG_DLL_CONFIG,	.value = 0x2004642C },
	{ .offset = SDCC_HC_REG_DDR_CONFIG,	.value = 0x00000000 },
	{ .offset = SDCC_HC_REG_DLL_CONFIG2,	.value = 0x00200000 },
	{ .offset = SDCC_USR_CTL,		.value = 0x00010800 },
	{ .offset = RGMII_IO_MACRO_CONFIG2,	.value = 0x00002060 },
};

static const struct ethqos_emac_por emac_v2_3_2_por[] = {
	{ .offset = RGMII_IO_MACRO_CONFIG,	.value = 0x00C01343 },
	{ .offset = SDCC_HC_REG_DLL_CONFIG,	.value = 0x2004642C },
	{ .offset = SDCC_HC_REG_DDR_CONFIG,	.value = 0x80040800 },
	{ .offset = SDCC_HC_REG_DLL_CONFIG2,	.value = 0x00200000 },
	{ .offset = SDCC_USR_CTL,		.value = 0x00010800 },
	{ .offset = RGMII_IO_MACRO_CONFIG2,	.value = 0x00002060 },
};

struct qcom_ethqos {
	struct platform_device *pdev;
	void __iomem *rgmii_base;

	unsigned int rgmii_clk_rate;
	struct clk *rgmii_clk;
	unsigned int speed;

	int gpio_phy_intr_redirect;
	u32 phy_intr;
	/* Work struct for handling phy interrupt */
	struct work_struct emac_phy_work;

	const struct ethqos_emac_por *por;
	unsigned int num_por;
	unsigned int emac_ver;

	struct regulator *gdsc_emac;
	struct regulator *reg_rgmii;
	struct regulator *reg_emac_phy;
	struct regulator *reg_rgmii_io_pads;
};

int ethqos_init_reqgulators(struct qcom_ethqos *ethqos);
void ethqos_disable_regulators(struct qcom_ethqos *ethqos);
int ethqos_init_gpio(struct qcom_ethqos *ethqos);
void ethqos_free_gpios(struct qcom_ethqos *ethqos);
#endif
