// Copyright 2024 George Norton (@george-norton)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "i2c_master.h"
#include "procyon.h"
#include "digitizer.h"
#include "print.h"
#include "raw_hid.h"

/* ============================================================================
 * Procyon Keyboard Custom Pointing Device Driver
 * ============================================================================
 * このファイルはProcyonキーボード専用のポインティングデバイスドライバーです。
 * Maxtouchデジタイザーを使用してポインティング機能を提供します。
 * george-nortonのmaxtouchドライバーをベースにしています。
 */

/* ============================================================================
 * 定数定義
 * ============================================================================ */
#define PROCYON_I2C_ADDR_4A (0x4A << 1)
#define PROCYON_I2C_ADDR_4B (0x4B << 1)
#define PROCYON_I2C_TIMEOUT 1000                 /* I2Cタイムアウト（ミリ秒） */

/* ============================================================================
 * グローバル変数
 * ============================================================================ */
static bool procyon_initialized = false;         /* 初期化フラグ */
static uint8_t procyon_i2c_addr = PROCYON_I2C_ADDR_4B; /* 検出されたアドレス */

/* ============================================================================
 * 内部関数
 * ============================================================================ */

/**
 * @brief Procyonデバイスの初期化
 * @return 初期化成功時true、失敗時false
 */
static bool procyon_init_device(void) {
    i2c_init();
    uint8_t data = 0x00;
    /* 0x4B→0x4A の順で疎通確認 */
    uint8_t ret = i2c_read_register(PROCYON_I2C_ADDR_4B, 0x00, &data, 1, PROCYON_I2C_TIMEOUT);
    if (ret == I2C_STATUS_SUCCESS) {
        procyon_i2c_addr = PROCYON_I2C_ADDR_4B;
        dprintf("[PROCYON] init OK addr=0x%02X data=0x%02X\n", procyon_i2c_addr, data);
        uint8_t pkt[RAW_EPSIZE] = { 'P','I','N','I', (uint8_t)(procyon_i2c_addr>>1), data };
        raw_hid_send(pkt, RAW_EPSIZE);
    } else {
        ret = i2c_read_register(PROCYON_I2C_ADDR_4A, 0x00, &data, 1, PROCYON_I2C_TIMEOUT);
        if (ret == I2C_STATUS_SUCCESS) {
            procyon_i2c_addr = PROCYON_I2C_ADDR_4A;
            dprintf("[PROCYON] init OK addr=0x%02X data=0x%02X\n", procyon_i2c_addr, data);
            uint8_t pkt[RAW_EPSIZE] = { 'P','I','N','I', (uint8_t)(procyon_i2c_addr>>1), data };
            raw_hid_send(pkt, RAW_EPSIZE);
        } else {
            dprintf("[PROCYON] init FAIL (no I2C ACK at 0x4B/0x4A) ret=%d\n", ret);
            uint8_t pkt[RAW_EPSIZE] = { 'P','F','A','I', (uint8_t)ret };
            raw_hid_send(pkt, RAW_EPSIZE);
            return false;
        }
    }
    
    return true;
}

/**
 * @brief Procyonデバイスからデータを読み取り
 * @param mouse_report マウスレポート構造体
 * @return 更新されたマウスレポート
 */
static report_mouse_t procyon_read_data(report_mouse_t mouse_report) {
    uint8_t data[4] = {0};
    uint8_t ret = i2c_read_register(procyon_i2c_addr, 0x01, data, 4, PROCYON_I2C_TIMEOUT);
    
    if (ret == I2C_STATUS_SUCCESS) {
        /* データの解析（実際のハードウェアに合わせて調整が必要） */
        int16_t x = (int16_t)((data[0] << 8) | data[1]);
        int16_t y = (int16_t)((data[2] << 8) | data[3]);
        /* Digitizer（絶対座標）として送る */
        float xn = (float)x / 32767.0f;
        float yn = (float)(-y) / 32767.0f;
        if (xn < 0) xn = 0; if (xn > 1) xn = 1;
        if (yn < 0) yn = 0; if (yn > 1) yn = 1;
        digitizer_in_range_on();
        digitizer_set_position(xn, yn);
        dprintf("[PROCYON][ABS] x=%.3f y=%.3f\n", xn, yn);
        uint8_t pkt[RAW_EPSIZE] = { 'P','A','B','S', (uint8_t)(xn * 255), (uint8_t)(yn * 255) };
        raw_hid_send(pkt, RAW_EPSIZE);
    } else {
        dprintf("[PROCYON] read err ret=%d addr=0x%02X\n", ret, procyon_i2c_addr);
        uint8_t pkt[RAW_EPSIZE] = { 'P','E','R','R', (uint8_t)ret, (uint8_t)(procyon_i2c_addr>>1) };
        raw_hid_send(pkt, RAW_EPSIZE);
    }
    
    return mouse_report;
}

/* ============================================================================
 * ポインティングデバイスドライバー関数
 * ============================================================================ */

/**
 * @brief ドライバーの初期化
 */
void pointing_device_driver_init(void) {
    if (!procyon_initialized) {
        if (procyon_init_device()) {
            procyon_initialized = true;
        }
    }
}

/**
 * @brief マウスレポートの取得
 * @param mouse_report 現在のマウスレポート
 * @return 更新されたマウスレポート
 */
report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
    if (procyon_initialized) {
        return procyon_read_data(mouse_report);
    }
    return mouse_report;
}

/**
 * @brief CPIの取得（現在は固定値）
 * @return CPI値
 */
uint16_t pointing_device_driver_get_cpi(void) {
    return 1000;  /* 固定CPI値 */
}

/**
 * @brief CPIの設定（現在は無効）
 * @param cpi CPI値
 */
void pointing_device_driver_set_cpi(uint16_t cpi) {
    /* 現在はCPI設定をサポートしていません */
    (void)cpi;
}

/* ============================================================================
 * ドライバー構造体定義
 * ============================================================================ */
const pointing_device_driver_t procyon_pointing_device_driver = {
    .init       = pointing_device_driver_init,
    .get_report = pointing_device_driver_get_report,
    .get_cpi    = pointing_device_driver_get_cpi,
    .set_cpi    = pointing_device_driver_set_cpi,
}; 