SERIAL_DRIVER = vendor
I2C_DRIVER_REQUIRED = yes
# switch to QMK Digitizer (absolute pointing) using maxtouch backend
DIGITIZER_ENABLE = yes
DIGITIZER_DRIVER = maxtouch
# ensure pointing_device (relative) is not forcing a driver
# (leave disabled to avoid conflicts)
# POINTING_DEVICE_ENABLE = no
MAXTOUCH_DEBUG = no

# ============================================================================
# VIA設定
# ============================================================================
VIA_ENABLE = yes                                # VIA（Visual Input Assistant）を有効化
CONSOLE_ENABLE = yes                             # USBシリアルコンソールを有効化（uprintf出力）
RAW_ENABLE = yes                                 # Raw HIDを有効化（HID Console向けログ）