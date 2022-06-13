# esp32 series build rules

# Setup the toolchain
CROSS_PREFIX=$(patsubst "%",%,$(CONFIG_CROSS_PREFIX))
MCU=$(patsubst "%",%,$(CONFIG_MCU))

# Libraries source

dirs-y += src/esp32 \
	src/generic

CFLAGS += -Ilib/esp32/config/$(MCU) \
	-Ilib/esp32/esp_common/include \
	-Ilib/esp32/xtensa/include \
	-Ilib/esp32/xtensa/$(MCU)/include \
	-Ilib/esp32/soc/include \
	-Ilib/esp32/soc/$(MCU)/include \
	-Ilib/esp32/hal/include \
	-Ilib/esp32/hal/$(MCU)/include \
	-Ilib/esp32/hal/platform_port/include

CFLAGS_klipper.elf += --specs=nano.specs --specs=nosys.specs
CFLAGS_klipper.elf += -T lib/esp32/ld/$(MCU)/memory.ld -T lib/esp32/ld/$(MCU)/sections.ld -T lib/esp32/soc/$(MCU)/ld/$(MCU).peripherals.ld

# Add source files
src-y += esp32/main.c esp32/gpio.c
src-y += generic/crc16_ccitt.c
src-$(CONFIG_HAVE_GPIO_ADC) += esp32/adc.c
src-$(CONFIG_HAVE_GPIO_I2C) += esp32/i2c.c
src-$(CONFIG_HAVE_GPIO_SPI) += esp32/spi.c
src-$(CONFIG_USBSERIAL) += esp32/usbserial.c esp32/chipid.c
src-$(CONFIG_USBSERIAL) += generic/usb_cdc.c
src-$(CONFIG_SERIAL) += esp32/serial.c generic/serial_irq.c
src-$(CONFIG_HAVE_GPIO_HARD_PWM) += esp32/hard_pwm.c

# Build the additional bin output file
target-y += $(OUT)klipper.bin

$(OUT)klipper.bin: $(OUT)klipper.elf
	@echo "  Creating bin file $@"
	$(Q)$(OBJCOPY) -O binary $< $@

# Flash rules
flash: $(OUT)klipper.bin
	@echo "  Flashing $< to $(FLASH_DEVICE)"
	$(Q)$(PYTHON) ./scripts/flash_usb.py -t $(CONFIG_MCU) -d "$(FLASH_DEVICE)" $(if $(NOSUDO),--no-sudo) $(OUT)klipper.bin
