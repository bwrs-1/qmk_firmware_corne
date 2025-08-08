/* Copyright 2022 LXF-YZP(yuezp)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/* ============================================================================
 * ブートローダー設定
 * ============================================================================ */
/* Double tap reset button to enter bootloader */
/* リセットボタンをダブルタップしてブートローダーに入る */

/* ============================================================================
 * ハンドネス（左右）設定
 * ============================================================================ */
/* Handedness. */
#define SPLIT_HAND_PIN GP29                    /* 左右判定用ピン */
#define SPLIT_HAND_PIN_LOW_IS_RIGHT            /* High -> right, Low -> left. */
                                              /* High = 右側、Low = 左側 */

/* ============================================================================
 * RP2040ブートローダー設定
 * ============================================================================ */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET     /* ダブルタップリセット機能を有効化 */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25  /* ブートローダー用LEDピン */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U  /* タイムアウト時間（ミリ秒） */

/* ============================================================================
 * シリアル通信設定
 * ============================================================================ */
// Serial config
#define SERIAL_USART_FULL_DUPLEX               /* 全二重通信を有効化 */
#define SERIAL_USART_TX_PIN GP0                /* 送信ピン */
#define SERIAL_USART_RX_PIN GP1                /* 受信ピン */
#define SERIAL_USART_DRIVER SIOD0              /* シリアルドライバー */

/* ============================================================================
 * ポインティングデバイス設定
 * ============================================================================ */
// Enable use of pointing device on slave split.
#define SPLIT_POINTING_ENABLE                  /* スプリットキーボードでのポインティングデバイスを有効化 */

// Pointing device is on the right split.
#define POINTING_DEVICE_RIGHT                  /* ポインティングデバイスは右側に配置 */

/* ============================================================================
 * CRC設定
 * ============================================================================ */
/* CRC. */
#define CRC8_USE_TABLE                         /* CRC8テーブルを使用 */
#define CRC8_OPTIMIZE_SPEED                    /* CRC8の速度最適化 */

/* ============================================================================
 * I2C設定
 * ============================================================================ */
#define I2C_DRIVER I2CD1                       /* I2Cドライバー */
#define I2C1_SDA_PIN GP2                       /* I2C SDAピン */
#define I2C1_SCL_PIN GP3                       /* I2C SCLピン */
#define I2C1_CLOCK_SPEED 1000000               /* I2Cクロック速度（1MHz） */

/* ============================================================================
 * デジタイザー設定
 * ============================================================================ */
#define DIGITIZER_MOTION_PIN GP11              /* デジタイザー動作検知ピン */
#define DIGITIZER_MOTION_PIN_ACTIVE_LOW yes    /* デジタイザーピンはアクティブLow */
#define PROCYON_42_50                          /* Procyon 42/50モデル用設定 */

/* ============================================================================
 * ソフトシリアル設定
 * ============================================================================ */
// Reduce soft serial speed: Work around rp2040 issues
#define SELECT_SOFT_SERIAL_SPEED 4             /* ソフトシリアル速度を4に設定（RP2040の問題回避） */

/* ============================================================================
 * レイヤー設定
 * ============================================================================ */
#define DYNAMIC_KEYMAP_LAYER_COUNT 5           /* 動的キーマップレイヤー数（5レイヤー対応） */

/* ============================================================================
 * VIA設定
 * ============================================================================ */
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2       /* VIA設定のEEPROMサイズ */
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 1200    /* 動的キーマップのEEPROM最大アドレス */
