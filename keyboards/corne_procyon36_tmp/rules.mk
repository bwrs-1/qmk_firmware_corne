SERIAL_DRIVER = vendor
I2C_DRIVER_REQUIRED = yes
DIGITIZER_ENABLE = yes          # DIGITIZER_DRIVER の代わりに ENABLE を使用
DIGITIZER_DRIVER = maxtouch
POINTING_DEVICE_DRIVER = procyon  # カスタムドライバーを使用
MAXTOUCH_DEBUG = no

# ============================================================================
# VIA設定
# ============================================================================
VIA_ENABLE = yes                                # VIA（Visual Input Assistant）を有効化