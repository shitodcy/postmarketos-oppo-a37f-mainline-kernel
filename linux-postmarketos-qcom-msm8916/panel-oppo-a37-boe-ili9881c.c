// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>
#include <linux/regulator/consumer.h>

#include <video/mipi_display.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>
#include <drm/drm_probe_helper.h>

struct oppo15399boe_ili9881c {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct regulator *supply;
	struct gpio_desc *reset_gpio;
};

static inline
struct oppo15399boe_ili9881c *to_oppo15399boe_ili9881c(struct drm_panel *panel)
{
	return container_of_const(panel, struct oppo15399boe_ili9881c, panel);
}

static void oppo15399boe_ili9881c_reset(struct oppo15399boe_ili9881c *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(1000, 2000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(15000, 16000);
}

static int oppo15399boe_ili9881c_on(struct oppo15399boe_ili9881c *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x98, 0x81, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x01, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x02, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x03, 0x73);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x04, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x05, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x06, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x07, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x08, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x09, 0x1b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0a, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0b, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0c, 0x0d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0d, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0e, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0f, 0x26);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x10, 0x26);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x11, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x12, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x13, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x14, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x15, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x16, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x17, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x18, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x19, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1a, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1b, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1c, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1d, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1e, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1f, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x20, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x21, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x22, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x23, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x24, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x25, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_GAMMA_CURVE, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x27, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x28, 0x33);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x29, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2a, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2b, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_MEMORY_START,
				     0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_LUT, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_MEMORY_START,
				     0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2f, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_ROWS, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_COLUMNS,
				     0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x32, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x33, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x34, 0x00);
	mipi_dsi_dcs_set_tear_on_multi(&dsi_ctx, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_ADDRESS_MODE, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x37, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x38, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x39, 0x00);
	mipi_dsi_dcs_set_pixel_format_multi(&dsi_ctx, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x3b, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_MEMORY_CONTINUE,
				     0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_3D_CONTROL, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_MEMORY_CONTINUE,
				     0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x3f, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_VSYNC_TIMING, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x41, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x42, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x43, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x44, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x50, 0x01);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0x0023);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x52, 0x45);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x67);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x54, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_POWER_SAVE, 0xab);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x56, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x57, 0x23);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x58, 0x45);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x59, 0x67);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5a, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5b, 0xab);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5c, 0xcd);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5d, 0xef);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_CABC_MIN_BRIGHTNESS,
				     0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5f, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x60, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x61, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x62, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x63, 0x0e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x64, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x65, 0x0c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x66, 0x0d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x67, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x68, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x69, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6a, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6b, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6c, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6d, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6e, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x70, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x71, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x72, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x73, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x74, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x75, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x76, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x77, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x78, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x79, 0x0e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7a, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7b, 0x0c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7c, 0x0d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7d, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7e, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7f, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x80, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x81, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x82, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x83, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x84, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x85, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x86, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x87, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x88, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x89, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8a, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x98, 0x81, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0b, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0e, 0x17);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6c, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6e, 0x1a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x25);
	mipi_dsi_dcs_set_pixel_format_multi(&dsi_ctx, 0xa4);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8d, 0x2a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x87, 0xba);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x3b, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7a, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x71, 0xb0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x98, 0x81, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x22, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x7d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_POWER_SAVE, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x50, 0x85);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0x0082);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_COLUMNS,
				     0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_VSYNC_TIMING, 0x33);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x43, 0x66);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x60, 0x19);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x61, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x62, 0x0c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x63, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x98, 0x81, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x80, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x98, 0x81, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x34, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa0, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_DDB_START, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_PPS_START, 0x21);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa3, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa4, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa5, 0x23);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa6, 0x1a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa7, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_DDB_CONTINUE,
				     0x77);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_PPS_CONTINUE,
				     0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xaa, 0x29);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xab, 0x6f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xac, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xad, 0x0d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xae, 0x3d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xaf, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x18);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb1, 0x61);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb2, 0x74);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb3, 0x39);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc0, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc1, 0x12);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc2, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x12);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc4, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc5, 0x24);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc6, 0x1a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc7, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc8, 0x76);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc9, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xca, 0x29);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcb, 0x6e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcc, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcd, 0x0d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xce, 0x3d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcf, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd0, 0x19);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd1, 0x60);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd2, 0x73);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd3, 0x39);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x98, 0x81, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x01, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x02, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x03, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x04, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x05, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x06, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x07, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x08, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x09, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0a, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0b, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0c, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0d, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0e, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0f, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x10, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x11, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x12, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x13, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x14, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x15, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x16, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x17, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x18, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x19, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1a, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1b, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1c, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1d, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1e, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1f, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x20, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x21, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x22, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x23, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x24, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x25, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_GAMMA_CURVE, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x27, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x28, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x29, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2a, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2b, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_MEMORY_START,
				     0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_LUT, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_MEMORY_START,
				     0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2f, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_ROWS, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_COLUMNS,
				     0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x32, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x33, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x34, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x35, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_ADDRESS_MODE, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x37, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x38, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x39, 0x84);
	mipi_dsi_dcs_set_pixel_format_multi(&dsi_ctx, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x3b, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_MEMORY_CONTINUE,
				     0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_3D_CONTROL, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_MEMORY_CONTINUE,
				     0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x3f, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_VSYNC_TIMING, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x41, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x42, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x43, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x44, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_GET_SCANLINE, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x46, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x47, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x48, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x49, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4a, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4b, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4c, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4d, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4e, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4f, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x50, 0x86);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0x0086);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x52, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x54, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_POWER_SAVE, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x56, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x57, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x58, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x59, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5a, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5b, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5c, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5d, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_CABC_MIN_BRIGHTNESS,
				     0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5f, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x60, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x61, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x62, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x63, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x64, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x65, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x66, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x67, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x68, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x69, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6a, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6b, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6c, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6d, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6e, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x70, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x71, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x72, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x73, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x74, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x75, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x76, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x77, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x78, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x79, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7a, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7b, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7c, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7d, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7e, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7f, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x98, 0x81, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x00, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x01, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x02, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x03, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x04, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x05, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x06, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x07, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x08, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x09, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0a, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0b, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0c, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0d, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0e, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0f, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x10, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x11, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x12, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x13, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x14, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x15, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x16, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x17, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x18, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x19, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1a, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1b, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1c, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1d, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1e, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1f, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x20, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x21, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x22, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x23, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x24, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x25, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_GAMMA_CURVE, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x27, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x28, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x29, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2a, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2b, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_MEMORY_START,
				     0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_LUT, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_MEMORY_START,
				     0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2f, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_ROWS, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_COLUMNS,
				     0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x32, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x33, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x34, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x35, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_ADDRESS_MODE, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x37, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x38, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x39, 0x8e);
	mipi_dsi_dcs_set_pixel_format_multi(&dsi_ctx, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x3b, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_MEMORY_CONTINUE,
				     0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_3D_CONTROL, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_MEMORY_CONTINUE,
				     0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x3f, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_VSYNC_TIMING, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x41, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x42, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x43, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x44, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_GET_SCANLINE, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x46, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x47, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x48, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x49, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4a, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4b, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4c, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4d, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4e, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4f, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x50, 0x8f);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0x0090);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x52, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x54, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_POWER_SAVE, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x56, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x57, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x58, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x59, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5a, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5b, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5c, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5d, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_CABC_MIN_BRIGHTNESS,
				     0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5f, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x60, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x61, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x62, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x63, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x64, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x65, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x66, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x67, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x68, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x69, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6a, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6b, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6c, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6d, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6e, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x70, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x71, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x72, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x73, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x74, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x75, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x76, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x77, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x78, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x79, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7a, 0x93);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7b, 0x93);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7c, 0x93);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7d, 0x93);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7e, 0x93);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7f, 0x93);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x98, 0x81, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x01, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x02, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x03, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x04, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x05, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x06, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x07, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x08, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x09, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0a, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0b, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0c, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0d, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0e, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0f, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x10, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x11, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x12, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x13, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x14, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x15, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x16, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x17, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x18, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x19, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1a, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1b, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1c, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1d, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1e, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1f, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x20, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x21, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x22, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x23, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x24, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x25, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_GAMMA_CURVE, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x27, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x28, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x29, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2a, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2b, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_MEMORY_START,
				     0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_LUT, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_MEMORY_START,
				     0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2f, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_ROWS, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_COLUMNS,
				     0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x32, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x33, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x34, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x35, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_ADDRESS_MODE, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x37, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x38, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x39, 0x84);
	mipi_dsi_dcs_set_pixel_format_multi(&dsi_ctx, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x3b, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_MEMORY_CONTINUE,
				     0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_3D_CONTROL, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_MEMORY_CONTINUE,
				     0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x3f, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_VSYNC_TIMING, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x41, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x42, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x43, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x44, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_GET_SCANLINE, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x46, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x47, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x48, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x49, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4a, 0x85);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4b, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4c, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4d, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4e, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4f, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x50, 0x86);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0x0086);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x52, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x54, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_POWER_SAVE, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x56, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x57, 0x86);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x58, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x59, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5a, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5b, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5c, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5d, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_CABC_MIN_BRIGHTNESS,
				     0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5f, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x60, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x61, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x62, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x63, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x64, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x65, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x66, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x67, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x68, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x69, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6a, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6b, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6c, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6d, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6e, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x70, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x71, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x72, 0x88);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x73, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x74, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x75, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x76, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x77, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x78, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x79, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7a, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7b, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7c, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7d, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7e, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7f, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x98, 0x81, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x00, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x01, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x02, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x03, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x04, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x05, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x06, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x07, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x08, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x09, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0a, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0b, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0c, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0d, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0e, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0f, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x10, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x11, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x12, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x13, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x14, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x15, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x16, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x17, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x18, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x19, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1a, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1b, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1c, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1d, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1e, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1f, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x20, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x21, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x22, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x23, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x24, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x25, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_GAMMA_CURVE, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x27, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x28, 0x8c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x29, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2a, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2b, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_MEMORY_START,
				     0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_LUT, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_MEMORY_START,
				     0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2f, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_ROWS, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_COLUMNS,
				     0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x32, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x33, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x34, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x35, 0x8d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_ADDRESS_MODE, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x37, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x38, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x39, 0x8e);
	mipi_dsi_dcs_set_pixel_format_multi(&dsi_ctx, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x3b, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_MEMORY_CONTINUE,
				     0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_3D_CONTROL, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_MEMORY_CONTINUE,
				     0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x3f, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_VSYNC_TIMING, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x41, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x42, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x43, 0x8e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x44, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_GET_SCANLINE, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x46, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x47, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x48, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x49, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4a, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4b, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4c, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4d, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4e, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4f, 0x8f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x50, 0x8f);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0x0090);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x52, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x54, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_POWER_SAVE, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x56, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x57, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x58, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x59, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5a, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5b, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5c, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5d, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_CABC_MIN_BRIGHTNESS,
				     0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5f, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x60, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x61, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x62, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x63, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x64, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x65, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x66, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x67, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x68, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x69, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6a, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6b, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6c, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6d, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6e, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x70, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x71, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x72, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x73, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x74, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x75, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x76, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x77, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x78, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x79, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7a, 0x93);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7b, 0x93);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7c, 0x93);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7d, 0x93);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7e, 0x93);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7f, 0x93);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x98, 0x81, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x01, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x02, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x03, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x04, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x05, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x06, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x07, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x08, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x09, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0a, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0b, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0c, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0d, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0e, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0f, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x10, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x11, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x12, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x13, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x14, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x15, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x16, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x17, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x18, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x19, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1a, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1b, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1c, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1d, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1e, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1f, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x20, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x21, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x22, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x23, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x24, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x25, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_GAMMA_CURVE, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x27, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x28, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x29, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2a, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2b, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_MEMORY_START,
				     0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_LUT, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_MEMORY_START,
				     0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2f, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_ROWS, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_COLUMNS,
				     0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x32, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x33, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x34, 0x00);
	mipi_dsi_dcs_set_tear_on_multi(&dsi_ctx, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_ADDRESS_MODE, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x37, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x38, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x39, 0x00);
	mipi_dsi_dcs_set_pixel_format_multi(&dsi_ctx, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x3b, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_MEMORY_CONTINUE,
				     0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_3D_CONTROL, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_MEMORY_CONTINUE,
				     0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x3f, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_VSYNC_TIMING, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x41, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x42, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x43, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x44, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_GET_SCANLINE, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x46, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x47, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x48, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x49, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4a, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4b, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4c, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4d, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4e, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4f, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x50, 0x00);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0x0000);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x52, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x54, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_POWER_SAVE, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x56, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x57, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x58, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x59, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5a, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5b, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5c, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5d, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_CABC_MIN_BRIGHTNESS,
				     0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5f, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x60, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x61, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x62, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x63, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x64, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x65, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x66, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x67, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x68, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x69, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6a, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6b, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6c, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6d, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6e, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x70, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x71, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x72, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x73, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x74, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x75, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x76, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x77, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x78, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x79, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7a, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7b, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7c, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7d, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7e, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7f, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x98, 0x81, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x01, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x02, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x03, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x04, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x05, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x06, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x07, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x08, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x09, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0a, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0b, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0c, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0d, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0e, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0f, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x10, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x11, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x12, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x13, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x14, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x15, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x16, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x17, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x18, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x19, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1a, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1b, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1c, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1d, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1e, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1f, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x20, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x21, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x22, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x23, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x24, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x25, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_GAMMA_CURVE, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x27, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x28, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x29, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2a, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2b, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_MEMORY_START,
				     0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_LUT, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_MEMORY_START,
				     0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2f, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_ROWS, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_COLUMNS,
				     0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x32, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x33, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x34, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x35, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_ADDRESS_MODE, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x37, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x38, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x39, 0x81);
	mipi_dsi_dcs_set_pixel_format_multi(&dsi_ctx, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x3b, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_MEMORY_CONTINUE,
				     0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_3D_CONTROL, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_MEMORY_CONTINUE,
				     0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x3f, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_VSYNC_TIMING, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x41, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x42, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x43, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x44, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_GET_SCANLINE, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x46, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x47, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x48, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x49, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4a, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4b, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4c, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4d, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4e, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4f, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x50, 0x81);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0x0081);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x52, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x54, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_POWER_SAVE, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x56, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x57, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x58, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x59, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5a, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5b, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5c, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5d, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_CABC_MIN_BRIGHTNESS,
				     0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5f, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x60, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x61, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x62, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x63, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x64, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x65, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x66, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x67, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x68, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x69, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6a, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6b, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6c, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6d, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6e, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x70, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x71, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x72, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x73, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x74, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x75, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x76, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x77, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x78, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x79, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7a, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7b, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7c, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7d, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7e, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7f, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x98, 0x81, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf3, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x98, 0x81, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x06, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x07, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x98, 0x81, 0x00);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0xff0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x2c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_POWER_SAVE, 0x80);
	mipi_dsi_dcs_set_tear_on_multi(&dsi_ctx, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	mipi_dsi_dcs_exit_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);
	mipi_dsi_dcs_set_display_on_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 20);

	return dsi_ctx.accum_err;
}

static int oppo15399boe_ili9881c_off(struct oppo15399boe_ili9881c *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x98, 0x81, 0x0b);
	mipi_dsi_msleep(&dsi_ctx, 50);
	mipi_dsi_dcs_set_display_off_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 50);
	mipi_dsi_dcs_enter_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);

	return dsi_ctx.accum_err;
}

static int oppo15399boe_ili9881c_prepare(struct drm_panel *panel)
{
	struct oppo15399boe_ili9881c *ctx = to_oppo15399boe_ili9881c(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = regulator_enable(ctx->supply);
	if (ret < 0) {
		dev_err(dev, "Failed to enable regulator: %d\n", ret);
		return ret;
	}

	oppo15399boe_ili9881c_reset(ctx);

	ret = oppo15399boe_ili9881c_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		regulator_disable(ctx->supply);
		return ret;
	}

	return 0;
}

static int oppo15399boe_ili9881c_unprepare(struct drm_panel *panel)
{
	struct oppo15399boe_ili9881c *ctx = to_oppo15399boe_ili9881c(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = oppo15399boe_ili9881c_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	regulator_disable(ctx->supply);

	return 0;
}

static const struct drm_display_mode oppo15399boe_ili9881c_mode = {
	.clock = (720 + 164 + 2 + 160) * (1280 + 24 + 8 + 24) * 60 / 1000,
	.hdisplay = 720,
	.hsync_start = 720 + 164,
	.hsync_end = 720 + 164 + 2,
	.htotal = 720 + 164 + 2 + 160,
	.vdisplay = 1280,
	.vsync_start = 1280 + 24,
	.vsync_end = 1280 + 24 + 8,
	.vtotal = 1280 + 24 + 8 + 24,
	.width_mm = 62,
	.height_mm = 110,
	.type = DRM_MODE_TYPE_DRIVER,
};

static int oppo15399boe_ili9881c_get_modes(struct drm_panel *panel,
					   struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &oppo15399boe_ili9881c_mode);
}

static const struct drm_panel_funcs oppo15399boe_ili9881c_panel_funcs = {
	.prepare = oppo15399boe_ili9881c_prepare,
	.unprepare = oppo15399boe_ili9881c_unprepare,
	.get_modes = oppo15399boe_ili9881c_get_modes,
};

static int oppo15399boe_ili9881c_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct oppo15399boe_ili9881c *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	drm_panel_init(&ctx->panel, dev, &oppo15399boe_ili9881c_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ctx->supply = devm_regulator_get(dev, "power");
	if (IS_ERR(ctx->supply))
		return dev_err_probe(dev, PTR_ERR(ctx->supply),
				     "Failed to get power regulator\n");

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 3;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_VIDEO_HSE |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS |
			  MIPI_DSI_MODE_VIDEO_NO_HFP |
			  MIPI_DSI_MODE_VIDEO_NO_HBP |
			  MIPI_DSI_MODE_VIDEO_NO_HSA;

	ctx->panel.prepare_prev_first = true;

	ret = drm_panel_of_backlight(&ctx->panel);
	if (ret)
		return dev_err_probe(dev, ret, "Failed to get backlight\n");

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		drm_panel_remove(&ctx->panel);
		return dev_err_probe(dev, ret, "Failed to attach to DSI host\n");
	}

	return 0;
}

static void oppo15399boe_ili9881c_remove(struct mipi_dsi_device *dsi)
{
	struct oppo15399boe_ili9881c *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id oppo15399boe_ili9881c_of_match[] = {
	{ .compatible = "oppo,a37-boe-ili9881c" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, oppo15399boe_ili9881c_of_match);

static struct mipi_dsi_driver oppo15399boe_ili9881c_driver = {
	.probe = oppo15399boe_ili9881c_probe,
	.remove = oppo15399boe_ili9881c_remove,
	.driver = {
		.name = "panel-oppo-a37-boe-ili9881c",
		.of_match_table = oppo15399boe_ili9881c_of_match,
	},
};
module_mipi_dsi_driver(oppo15399boe_ili9881c_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for oppo15399boe ili9881c 720p video mode dsi panel");
MODULE_LICENSE("GPL");
