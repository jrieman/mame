// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
#ifndef __SNS_SGB_H
#define __SNS_SGB_H

#include "snes_slot.h"
#include "rom.h"

#include "cpu/lr35902/lr35902.h"
#include "bus/gameboy/gb_slot.h"
#include "bus/gameboy/rom.h"
#include "bus/gameboy/mbc.h"
#include "video/gb_lcd.h"
#include "sound/gb.h"


// ======================> sns_rom_sgb_device

class sns_rom_sgb_device : public sns_rom_device
{
public:
	// construction/destruction
	sns_rom_sgb_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source);

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;

	// reading and writing
	virtual DECLARE_READ8_MEMBER(read_l) override;
	virtual DECLARE_READ8_MEMBER(read_h) override;
	virtual DECLARE_READ8_MEMBER(chip_read) override;
	virtual DECLARE_WRITE8_MEMBER(chip_write) override;

	virtual DECLARE_READ8_MEMBER(gb_cart_r);
	virtual DECLARE_WRITE8_MEMBER(gb_bank_w);
	virtual DECLARE_READ8_MEMBER(gb_ram_r);
	virtual DECLARE_WRITE8_MEMBER(gb_ram_w);
	virtual DECLARE_READ8_MEMBER(gb_echo_r);
	virtual DECLARE_WRITE8_MEMBER(gb_echo_w);
	virtual DECLARE_READ8_MEMBER(gb_io_r);
	virtual DECLARE_WRITE8_MEMBER(gb_io_w);
	virtual DECLARE_READ8_MEMBER(gb_ie_r);
	virtual DECLARE_WRITE8_MEMBER(gb_ie_w);
	virtual DECLARE_WRITE8_MEMBER(gb_timer_callback);

protected:
	required_device<lr35902_cpu_device> m_sgb_cpu;
	required_device<gameboy_sound_device> m_sgb_apu;
	required_device<sgb_ppu_device> m_sgb_ppu;
	required_device<gb_cart_slot_device> m_cartslot;
	required_memory_region m_region_bios;

	void lcd_render(UINT32 *source);

	// ICD2 regs
	UINT8 m_sgb_ly;
	UINT8 m_sgb_row;
	UINT8 m_vram;
	UINT8 m_port;
	UINT8 m_joy1, m_joy2, m_joy3, m_joy4;
	UINT8 m_joy_pckt[16];
	UINT16 m_vram_offs;
	UINT8 m_mlt_req;

	UINT32 m_lcd_buffer[4 * 160 * 8];
	UINT16 m_lcd_output[320];
	UINT16 m_lcd_row;

	// input bits
	int m_packetsize;
	UINT8 m_packet_data[64][16];

	bool m_bios_disabled;
};


class sns_rom_sgb1_device : public sns_rom_sgb_device
{
public:
	// construction/destruction
	sns_rom_sgb1_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual machine_config_constructor device_mconfig_additions() const override;
	virtual const tiny_rom_entry *device_rom_region() const override;
};


class sns_rom_sgb2_device : public sns_rom_sgb_device
{
public:
    // construction/destruction
    sns_rom_sgb2_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

    // device-level overrides
    virtual machine_config_constructor device_mconfig_additions() const override;
	virtual const tiny_rom_entry *device_rom_region() const override;
};

// device type definition
extern const device_type SNS_LOROM_SUPERGB;
extern const device_type SNS_LOROM_SUPERGB2;

#endif
