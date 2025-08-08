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

#include QMK_KEYBOARD_H

/* ============================================================================
 * カスタムキーコード定義
 * ============================================================================ */
enum custom_keycodes {
    RGB_BREATH = SAFE_RANGE,                    /* 呼吸効果 */
    RGB_RAINBOW,                                /* レインボー効果 */
    RGB_STATIC,                                 /* 静的色 */
    RGB_GRADIENT,                               /* グラデーション効果 */
    RGB_TYPING_HEATMAP,                         /* タイピングヒートマップ */
    RGB_LAYER_INDICATOR,                        /* レイヤーインジケーター */
    RGB_BRIGHTNESS_UP,                          /* 明度アップ */
    RGB_BRIGHTNESS_DOWN,                        /* 明度ダウン */
    RGB_SPEED_UP,                               /* 速度アップ */
    RGB_SPEED_DOWN,                             /* 速度ダウン */
    RGB_PRESET_1,                               /* プリセット1 */
    RGB_PRESET_2,                               /* プリセット2 */
    RGB_PRESET_3,                               /* プリセット3 */
    RGB_PRESET_4,                               /* プリセット4 */
    RGB_PRESET_5                                /* プリセット5 */
};

/* ============================================================================
 * レイヤー定義
 * ============================================================================ */
enum layer_names {
    _BASE,                                      /* ベースレイヤー（通常入力） */
    _LOWER,                                     /* ロワーレイヤー（機能キー） */
    _RAISE,                                     /* レイズレイヤー（記号・数字） */
    _ADJUST,                                    /* 調整レイヤー（設定） */
    _RGB                                        /* RGB制御レイヤー（LED制御専用） */
};

/* ============================================================================
 * RGBプリセット設定
 * ============================================================================ */
void rgb_preset_1(void) {
    rgb_matrix_sethsv(HSV_RED);
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
}

void rgb_preset_2(void) {
    rgb_matrix_sethsv(HSV_BLUE);
    rgb_matrix_mode(RGB_MATRIX_BREATHING);
}

void rgb_preset_3(void) {
    rgb_matrix_sethsv(HSV_GREEN);
    rgb_matrix_mode(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
}

void rgb_preset_4(void) {
    rgb_matrix_sethsv(HSV_PURPLE);
    rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
}

void rgb_preset_5(void) {
    rgb_matrix_sethsv(HSV_ORANGE);
    rgb_matrix_mode(RGB_MATRIX_GRADIENT_LEFT_RIGHT);
}

/* ============================================================================
 * カスタムキーコード処理
 * ============================================================================ */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case RGB_BREATH:
                rgb_matrix_mode(RGB_MATRIX_BREATHING);
                return false;
            case RGB_RAINBOW:
                rgb_matrix_mode(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
                return false;
            case RGB_STATIC:
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                return false;
            case RGB_GRADIENT:
                rgb_matrix_mode(RGB_MATRIX_GRADIENT_LEFT_RIGHT);
                return false;
            case RGB_TYPING_HEATMAP:
                rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
                return false;
            case RGB_LAYER_INDICATOR:
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
                return false;
            case RGB_BRIGHTNESS_UP:
                rgb_matrix_increase_val();
                return false;
            case RGB_BRIGHTNESS_DOWN:
                rgb_matrix_decrease_val();
                return false;
            case RGB_SPEED_UP:
                rgb_matrix_increase_speed();
                return false;
            case RGB_SPEED_DOWN:
                rgb_matrix_decrease_speed();
                return false;
            case RGB_PRESET_1:
                rgb_preset_1();
                return false;
            case RGB_PRESET_2:
                rgb_preset_2();
                return false;
            case RGB_PRESET_3:
                rgb_preset_3();
                return false;
            case RGB_PRESET_4:
                rgb_preset_4();
                return false;
            case RGB_PRESET_5:
                rgb_preset_5();
                return false;
        }
    }
    return true;
}

/* ============================================================================
 * キーマップ定義
 * ============================================================================ */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* ============================================================================
     * ベースレイアウト（通常入力）
     * ============================================================================ */
    [_BASE] = LAYOUT(
        /* 左側キー */
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
        /* |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
        KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
        /* |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
        /* |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------| */
                        KC_LGUI,    KC_LGUI,   MO(1),  KC_SPC,                        KC_ENT,   MO(2),  RGB_TOG,  MO(4)
                                /* `----------------------------------'  `------------------------------------' */
    ),

    /* ============================================================================
     * ロワーレイヤー（機能キー）
     * ============================================================================ */
    [_LOWER] = LAYOUT(
        /* 左側キー */
        XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4, KC_MINS,                       KC_INS, KC_HOME,   KC_UP,  KC_END, KC_PGUP, KC_BSPC,
        /* |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
        KC_LCTL,   KC_F5,   KC_F6,   KC_F7,   KC_F8, KC_EQL,                        KC_DEL, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX,
        /* |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
        KC_LSFT,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_PAUS,                      XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS, KC_RSFT,
        /* |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------| */
                          _______,  KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, RGB_MOD, KC_LALT
                                /* `-----------------------------------'  `----------------------------------' */
    ),

    /* ============================================================================
     * レイズレイヤー（記号・数字）
     * ============================================================================ */
    [_RAISE] = LAYOUT(
        /* 左側キー */
        KC_CAPS, KC_EXLM, KC_DQUO, KC_HASH, KC_CIRC, XXXXXXX,                      KC_ASTR,    KC_7,    KC_8,    KC_9, KC_MINS, KC_BSPC,
        /* |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
        KC_LCTL, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, XXXXXXX,                      KC_SLSH,    KC_4,    KC_5,    KC_6, KC_PLUS, KC_QUOT,
        /* |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
        KC_LSFT, KC_LBRC, KC_RBRC, KC_LABK, KC_RABK,  KC_EQL,                         KC_0,    KC_1,    KC_2,    KC_3,  KC_DOT, KC_RSFT,
        /* |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------| */
                         _______,  KC_LGUI, _______,  KC_SPC,     KC_ENT, _______,  RGB_HUI, _______
                                /* `----------------------------------'  `------------------------------------' */
    ),

    /* ============================================================================
     * 調整レイヤー（設定）
     * ============================================================================ */
    [_ADJUST] = LAYOUT(
        /* 左側キー */
        XXXXXXX, XXXXXXX,   KC_AT, XXXXXXX,  KC_DLR, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
        /* |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
        KC_LCTL, XXXXXXX, KC_AMPR, KC_PIPE, KC_BSLS, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TILD,  KC_GRV,
        /* |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, KC_PERC, XXXXXXX,                      MO(4), RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, KC_RSFT,
        /* |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------| */
                          _______, KC_LGUI, _______,  KC_SPC,     KC_ENT, _______,  KC_LALT, _______
                                 /* `---------------------------------'  `-----------------------------------' */
    ),

    /* ============================================================================
     * RGB制御レイヤー（LED制御専用）
     * ============================================================================ */
    [_RGB] = LAYOUT(
        /* 左側キー */
        RGB_PRESET_1, RGB_PRESET_2, RGB_PRESET_3, RGB_PRESET_4, RGB_PRESET_5, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        /* |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
        RGB_BREATH, RGB_RAINBOW, RGB_STATIC, RGB_GRADIENT, RGB_TYPING_HEATMAP, RGB_LAYER_INDICATOR,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        /* |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------| */
        RGB_BRIGHTNESS_DOWN, RGB_BRIGHTNESS_UP, RGB_SPEED_DOWN, RGB_SPEED_UP, XXXXXXX, XXXXXXX,          RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,
        /* |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------| */
                          _______, _______, _______, _______,     _______, _______,  _______, _______
                                 /* `---------------------------------'  `-----------------------------------' */
    )
};

/* ============================================================================
 * RGB制御使用方法
 * ============================================================================ */
/*
 * RGB制御レイヤーへのアクセス方法:
 * 1. ベースレイヤー: 右側の親指キー（MO(4)）を押す
 * 2. ADJUSTレイヤー: LOWER + RAISE（同時押し）でADJUSTレイヤーに入り、右側のMO(4)キーを押す
 * 
 * RGB制御レイヤーの機能:
 * 
 * プリセット（上段）:
 * - RGB_PRESET_1: 赤色の静的ライト
 * - RGB_PRESET_2: 青色の呼吸効果
 * - RGB_PRESET_3: 緑色のレインボー効果
 * - RGB_PRESET_4: 紫色のタイピングヒートマップ
 * - RGB_PRESET_5: オレンジ色のグラデーション
 * 
 * エフェクト（中段）:
 * - RGB_BREATH: 呼吸効果
 * - RGB_RAINBOW: レインボー効果
 * - RGB_STATIC: 静的色
 * - RGB_GRADIENT: グラデーション効果
 * - RGB_TYPING_HEATMAP: タイピングヒートマップ
 * - RGB_LAYER_INDICATOR: レイヤーインジケーター
 * 
 * 調整（下段）:
 * - RGB_BRIGHTNESS_DOWN/UP: 明度調整
 * - RGB_SPEED_DOWN/UP: 速度調整
 * - RGB_TOG: RGB ON/OFF
 * - RGB_MOD: エフェクトモード切り替え
 * - RGB_HUI/SAI/VAI: 色相/彩度/明度調整
 * 
 * エンコーダー機能:
 * - エンコーダー1: 明度調整（時計回りで明度アップ、反時計回りで明度ダウン）
 * - エンコーダー2: 速度調整（時計回りで速度アップ、反時計回りで速度ダウン）
 */

/* ============================================================================
 * エンコーダーマップ定義
 * ============================================================================ */
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { 
        ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP),      /* エンコーダー1: マウスホイール上下 */
        ENCODER_CCW_CW(KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN) /* エンコーダー2: 音量上下 */
    },
    [_LOWER] = { 
        ENCODER_CCW_CW(_______, _______),                /* エンコーダー1: 無効 */
        ENCODER_CCW_CW(_______, _______)                 /* エンコーダー2: 無効 */
    },
    [_RAISE] = { 
        ENCODER_CCW_CW(_______, _______),                /* エンコーダー1: 無効 */
        ENCODER_CCW_CW(_______, _______)                 /* エンコーダー2: 無効 */
    },
    [_ADJUST] = { 
        ENCODER_CCW_CW(RGB_HUD, RGB_HUI),                /* エンコーダー1: 色相調整 */
        ENCODER_CCW_CW(RGB_SAD, RGB_SAI)                 /* エンコーダー2: 彩度調整 */
    },
    [_RGB] = { 
        ENCODER_CCW_CW(RGB_VAD, RGB_VAI),                /* エンコーダー1: 明度調整 */
        ENCODER_CCW_CW(RGB_SPD, RGB_SPI)                 /* エンコーダー2: 速度調整 */
    }
};
#endif
