SERIAL_DRIVER = vendor
I2C_DRIVER_REQUIRED = yes
# Use digitizer+mouse fallback (Maxtouch → mouse). This preserves existing Procyon stack.
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = custom
POINTING_DEVICE_DRIVER_NAME = procyon
MAXTOUCH_DEBUG = no

# ============================================================================
# VIA設定
# ============================================================================
VIA_ENABLE = yes                                # VIA（Visual Input Assistant）を有効化
CONSOLE_ENABLE = yes                             # USBシリアルコンソールを有効化（uprintf出力）
RAW_ENABLE = yes                                 # Raw HIDを有効化（HID Console向けログ）