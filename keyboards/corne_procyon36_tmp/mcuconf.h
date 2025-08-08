/* Copyright 2022 JasonRen(biu)
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

#include_next <mcuconf.h>

/* ============================================================================
 * MCU設定ファイル
 * ============================================================================ */
/* このファイルはマイクロコントローラー（RP2040）の設定を定義します */

/* ============================================================================
 * SPI設定
 * ============================================================================ */
#undef RP_SPI_USE_SPI0                           /* SPI0の既存定義を削除 */
#define RP_SPI_USE_SPI0 TRUE                     /* SPI0を有効化 */

/* ============================================================================
 * I2C設定
 * ============================================================================ */
#undef RP_I2C_USE_I2C0                           /* I2C0の既存定義を削除 */
#define RP_I2C_USE_I2C0 FALSE                    /* I2C0を無効化 */

#undef RP_I2C_USE_I2C1                           /* I2C1の既存定義を削除 */
#define RP_I2C_USE_I2C1 TRUE                     /* I2C1を有効化（デジタイザー用） */