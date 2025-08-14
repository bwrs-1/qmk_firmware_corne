SERIAL_DRIVER = vendor
I2C_DRIVER_REQUIRED = yes
# Use digitizer+mouse fallback (Maxtouch → mouse). This preserves existing Procyon stack.
DIGITIZER_ENABLE = yes
DIGITIZER_DRIVER = maxtouch
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = digitizer
MAXTOUCH_DEBUG = no

# ============================================================================
# VIA設定
# ============================================================================
VIA_ENABLE = yes                                # VIA（Visual Input Assistant）を有効化