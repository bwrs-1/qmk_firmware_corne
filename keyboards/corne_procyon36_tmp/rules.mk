SERIAL_DRIVER = vendor
I2C_DRIVER_REQUIRED = yes
# Use custom pointing device driver (Procyon mouse), not HID digitizer
# DIGITIZER_ENABLE/DIGITIZER_DRIVER would disable POINTING_DEVICE; do not enable here
# DIGITIZER_ENABLE = no
# DIGITIZER_DRIVER = maxtouch
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = custom
POINTING_DEVICE_DRIVER_NAME = procyon
MAXTOUCH_DEBUG = no

# ============================================================================
# VIA設定
# ============================================================================
VIA_ENABLE = yes                                # VIA（Visual Input Assistant）を有効化