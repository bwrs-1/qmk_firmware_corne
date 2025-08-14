// Copyright 2024 George Norton (@george-norton)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "i2c_master.h"
#include "procyon.h"
#include "pointing_device.h"

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
#define PROCYON_I2C_ADDR 0x4B                    /* Procyon I2Cアドレス: hardware uses 0x4B */
#define PROCYON_I2C_TIMEOUT 1000                 /* I2Cタイムアウト（ミリ秒） */

/* ============================================================================
 * グローバル変数
 * ============================================================================ */
static bool procyon_initialized = false;         /* 初期化フラグ */

/* ============================================================================
 * 内部関数
 * ============================================================================ */

/**
 * @brief Procyonデバイスの初期化
 * @return 初期化成功時true、失敗時false
 */
static bool procyon_init_device(void) {
    uint8_t data = 0x00;
    uint8_t ret = i2c_write_register(PROCYON_I2C_ADDR, 0x00, &data, 1, PROCYON_I2C_TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        return false;
    }
    
    return true;
}

/**
 * @brief Procyonデバイスからデータを読み取り
 * @param mouse_report マウスレポート構造体
 * @return 更新されたマウスレポート
 */
static report_mouse_t procyon_read_data(report_mouse_t mouse_report) {
    uint8_t data[4];
    uint8_t ret = i2c_read_register(PROCYON_I2C_ADDR, 0x01, data, 4, PROCYON_I2C_TIMEOUT);
    
    if (ret == I2C_STATUS_SUCCESS) {
        /* データの解析（実際のハードウェアに合わせて調整が必要） */
        int16_t x = (int16_t)((data[0] << 8) | data[1]);
        int16_t y = (int16_t)((data[2] << 8) | data[3]);
        
        /* マウスレポートの更新 */
        mouse_report.x = (mouse_xy_report_t)(x / 256);  /* スケーリング */
        mouse_report.y = (mouse_xy_report_t)(y / 256);  /* スケーリング */
        
        /* ボタン状態の確認（必要に応じて） */
        if (data[0] & 0x80) {
            mouse_report.buttons |= MOUSE_BTN1;
        }
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