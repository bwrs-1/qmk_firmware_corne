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

// 接続側検出用の変数
static bool is_left_connected = false;
static bool macbook_mode_active = false;

// 右側キーボード接続時の最適化設定
#ifdef MASTER_RIGHT
    // 右側がマスターの場合の設定
    #define RIGHT_HAND_OPTIMIZATION
    #define POINTING_DEVICE_MASTER
#endif

// レイヤー切り替えの安定性向上設定
#define TAPPING_TERM 200
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD

enum layer_names {
    _BASE,
    _RAISE,
    _MOUSE,
    _LOWER,
    _MEDIA,
    _PROGRAM,  // プログラミング作業専用レイヤー
    _MACBOOK,  // MacBook用レイアウト
    _ADJUST
};

// レイヤーごとのRGB色定義
const HSV layer_colors[] = {
    [_BASE]  = {HSV_CYAN},      // シアン（基本レイヤー）
    [_RAISE] = {HSV_GREEN},     // 緑（記号・数字）
    [_MOUSE] = {HSV_PURPLE},    // 紫（マウス操作）
    [_LOWER] = {HSV_RED},       // 赤（ファンクションキー）
    [_MEDIA] = {HSV_PINK},      // ピンク（メディア制御）
    [_PROGRAM] = {HSV_BLUE},    // 青（プログラミング作業）
    [_MACBOOK] = {HSV_YELLOW},  // 黄色（MacBook用レイアウト）
    [_ADJUST] = {HSV_ORANGE}    // オレンジ（RGB設定）
};

// カスタムキーコード定義
enum custom_keycodes {
    KC_SCR_L = SAFE_RANGE,
    KC_SCR_R,
    KC_ZOOM_IN,
    KC_ZOOM_OUT,
    KC_BRIGHT_UP,
    KC_BRIGHT_DOWN,
    KC_SPOTIFY,
    KC_DISCORD,
    KC_TERMINAL,
    // プログラミング用追加キーコード
    KC_COPY,
    KC_PASTE,
    KC_CUT,
    KC_UNDO,
    KC_REDO,
    KC_FIND,
    KC_REPLACE,
    KC_COMMENT,
    KC_SAVE,
    KC_SAVE_AS,
    KC_NEW_FILE,
    KC_OPEN_FILE,
    KC_CLOSE_FILE,
    KC_RUN_CODE,
    KC_DEBUG,
    KC_GIT_ADD,
    KC_GIT_COMMIT,
    KC_GIT_PUSH,
    KC_GIT_PULL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] =	LAYOUT(
 
         KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                    KC_LGUI,     KC_LCTL,   KC_LGUI,   MO(1),  KC_SPC,    KC_ENT,   MO(2),  KC_BSPC,  KC_LALT,  KC_RGUI
                                //`----------------------------------'  `------------------------------------'
	),

	[_RAISE] =	LAYOUT(
    
        KC_CAPS, KC_EXLM, KC_DQUO, KC_HASH, KC_CIRC, KC_PERC,                      KC_ASTR,    KC_7,    KC_8,    KC_9, KC_MINS, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_AMPR,                      KC_SLSH,    KC_4,    KC_5,    KC_6, KC_PLUS, KC_QUOT,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, KC_LBRC, KC_RBRC, KC_LABK, KC_RABK,  KC_EQL,                         KC_0,    KC_1,    KC_2,    KC_3,  KC_DOT, KC_RSFT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                         _______,  _______,  KC_LGUI, _______,  KC_SPC,     KC_ENT, _______,  _______, _______, _______
                                //`----------------------------------'  `------------------------------------'
	),
    [_MOUSE] =	LAYOUT(
    
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_WH_U, KC_MS_U, KC_WH_D, XXXXXXX, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4, KC_BTN5, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                         _______,  _______,  KC_LGUI, _______,  KC_SPC,     KC_ENT, _______,  _______, _______, _______
                                //`----------------------------------'  `------------------------------------'
	),
    [_LOWER] =	LAYOUT(
     
        XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4, KC_MINS,                       KC_INS, KC_HOME,   KC_UP,  KC_END, KC_PGUP, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL,   KC_F5,   KC_F6,   KC_F7,   KC_F8, KC_EQL,                        KC_DEL, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_PAUS,                      XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS, KC_RSFT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                        _______,  _______,  KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, _______, KC_LALT, _______
                                //`-----------------------------------'  `----------------------------------'
	),
    [_MEDIA] =	LAYOUT(
    
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_MEDIA_PREV_TRACK, KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_BRIGHT_UP, KC_BRIGHT_DOWN, KC_ZOOM_IN, KC_ZOOM_OUT, KC_SPOTIFY, KC_DISCORD,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_TERMINAL, KC_CALCULATOR, KC_MAIL, KC_MY_COMPUTER, KC_WWW_SEARCH, KC_WWW_HOME,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                         _______,  _______,  KC_LGUI, _______,  KC_SPC,     KC_ENT, _______,  _______, _______, _______
                                //`----------------------------------'  `------------------------------------'
	),
       [_PROGRAM] =	LAYOUT(
    
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TAB,  KC_COPY, KC_PASTE,KC_CUT,  KC_UNDO, KC_REDO,                       KC_FIND, KC_REPLACE,KC_COMMENT,KC_SAVE, KC_SAVE_AS, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, KC_NEW_FILE,KC_OPEN_FILE,KC_CLOSE_FILE,KC_RUN_CODE,KC_DEBUG,       KC_GIT_ADD, KC_GIT_COMMIT, KC_GIT_PUSH, KC_GIT_PULL, KC_TERMINAL, KC_RSFT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                         _______,  _______,  KC_LGUI, _______,  KC_SPC,     KC_ENT, _______,  _______, _______, _______
                                //`----------------------------------'  `------------------------------------'
	),

    [_MACBOOK] =	LAYOUT(
    
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                    KC_LGUI,     KC_LALT,   KC_LGUI,   MO(1),  KC_SPC,    KC_ENT,   MO(2),  KC_BSPC,  KC_LALT,  KC_RGUI
                                //`----------------------------------'  `------------------------------------'
	),
   [_ADJUST] =	LAYOUT(
    
        XXXXXXX, XXXXXXX,   KC_AT, XXXXXXX,  KC_DLR, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL, XXXXXXX, KC_AMPR, KC_PIPE, KC_BSLS, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_TILD,  KC_GRV,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, KC_PERC, XXXXXXX,                      RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_RSFT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                         _______,   _______, KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, _______, KC_LALT, _______
                                 //`---------------------------------'  `-----------------------------------'
	)

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP), ENCODER_CCW_CW(KC_MS_WH_LEFT, KC_MS_WH_RIGHT) },
    [_RAISE] = { ENCODER_CCW_CW(KC_ZOOM_OUT, KC_ZOOM_IN), ENCODER_CCW_CW(KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK) },
    [_MOUSE] = { ENCODER_CCW_CW(KC_MS_WH_LEFT, KC_MS_WH_RIGHT), ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP) },
    [_LOWER] = { ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP), ENCODER_CCW_CW(KC_BRIGHT_DOWN, KC_BRIGHT_UP) },
    [_MEDIA] = { ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP), ENCODER_CCW_CW(KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK) },
    [_PROGRAM] = { ENCODER_CCW_CW(KC_UNDO, KC_REDO), ENCODER_CCW_CW(KC_ZOOM_OUT, KC_ZOOM_IN) },
    [_MACBOOK] = { ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP), ENCODER_CCW_CW(KC_MS_WH_LEFT, KC_MS_WH_RIGHT) },
    [_ADJUST] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(RGB_HUD, RGB_HUI) }
};
#endif

// カスタムキーコードの処理
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_SCR_L:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_LEFT))));
            }
            return false;
        case KC_SCR_R:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_RIGHT))));
            }
            return false;
        case KC_ZOOM_IN:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_EQUAL)));
            }
            return false;
        case KC_ZOOM_OUT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_MINUS)));
            }
            return false;
        case KC_BRIGHT_UP:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_UP)));
            }
            return false;
        case KC_BRIGHT_DOWN:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_DOWN)));
            }
            return false;
        case KC_SPOTIFY:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("r"));
                wait_ms(100);
                SEND_STRING("spotify\n");
            }
            return false;
        case KC_DISCORD:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("r"));
                wait_ms(100);
                SEND_STRING("discord\n");
            }
            return false;
        case KC_TERMINAL:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_T))));
            }
            return false;
        // プログラミング用キーコード処理
        case KC_COPY:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c"));
            }
            return false;
        case KC_PASTE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("v"));
            }
            return false;
        case KC_CUT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x"));
            }
            return false;
        case KC_UNDO:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("z"));
            }
            return false;
        case KC_REDO:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LSFT("z")));
            }
            return false;
        case KC_FIND:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("f"));
            }
            return false;
        case KC_REPLACE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("h"));
            }
            return false;
        case KC_COMMENT:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_SLASH)));
            }
            return false;
        case KC_SAVE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("s"));
            }
            return false;
        case KC_SAVE_AS:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LSFT("s")));
            }
            return false;
        case KC_NEW_FILE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("n"));
            }
            return false;
        case KC_OPEN_FILE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("o"));
            }
            return false;
        case KC_CLOSE_FILE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("w"));
            }
            return false;
        case KC_RUN_CODE:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_F5)));
            }
            return false;
        case KC_DEBUG:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_F9)));
            }
            return false;
        case KC_GIT_ADD:
            if (record->event.pressed) {
                SEND_STRING("git add .\n");
            }
            return false;
        case KC_GIT_COMMIT:
            if (record->event.pressed) {
                SEND_STRING("git commit -m \"");
            }
            return false;
        case KC_GIT_PUSH:
            if (record->event.pressed) {
                SEND_STRING("git push\n");
            }
            return false;
        case KC_GIT_PULL:
            if (record->event.pressed) {
                SEND_STRING("git pull\n");
            }
            return false;
    }
    return true;
}

// 接続側検出関数
bool detect_left_connection(void) {
    // SPLIT_HAND_PINを使用して左側接続を検出
    // 右側マスターの場合、左側が接続されるとピンがHIGHになる
    #ifdef SPLIT_HAND_PIN_LOW_IS_RIGHT
        return !readPin(SPLIT_HAND_PIN);
    #else
        return readPin(SPLIT_HAND_PIN);
    #endif
}

// レイヤー変更時にRGB色を自動変更
layer_state_t layer_state_set_user(layer_state_t state) {
    // アクティブなレイヤーを取得
    uint8_t layer = get_highest_layer(state);
    
    // MacBookモードがアクティブな場合、MacBookレイヤーを優先
    if (macbook_mode_active && layer == _BASE) {
        layer = _MACBOOK;
    }
    
    // レイヤーが有効な範囲内かチェック
    if (layer < sizeof(layer_colors) / sizeof(layer_colors[0])) {
        // RGB色を設定
        rgb_matrix_sethsv(layer_colors[layer].h, layer_colors[layer].s, layer_colors[layer].v);
    }
    
    return state;
}

// キーボード初期化時の処理
void keyboard_post_init_user(void) {
    // 右側キーボード接続時の最適化
    #ifdef MASTER_RIGHT
        // 右側がマスターの場合の初期化
        wait_ms(100);  // 起動時の安定化待機
        
        // RGB設定の初期化
        rgb_matrix_enable();
        rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
        
        // タッチパッドの初期化確認
        #ifdef POINTING_DEVICE_RIGHT
            pointing_device_init();
        #endif
        
        // 接続側検出の初期化
        setPinInput(SPLIT_HAND_PIN);
        is_left_connected = detect_left_connection();
        macbook_mode_active = is_left_connected;
        
        // MacBookモードがアクティブな場合、MacBookレイヤーに切り替え
        if (macbook_mode_active) {
            layer_move(_MACBOOK);
        }
    #endif
    
    // デフォルトレイヤーのRGB色を設定
    rgb_matrix_sethsv(layer_colors[_BASE].h, layer_colors[_BASE].s, layer_colors[_BASE].v);
}

// 右側キーボード接続時の追加設定
#ifdef MASTER_RIGHT
void matrix_scan_user(void) {
    // 接続状態の継続的な監視
    bool current_left_connected = detect_left_connection();
    
    // 接続状態が変更された場合
    if (current_left_connected != is_left_connected) {
        is_left_connected = current_left_connected;
        macbook_mode_active = is_left_connected;
        
        // MacBookモードの切り替え
        if (macbook_mode_active) {
            // MacBookレイヤーに切り替え
            layer_move(_MACBOOK);
        } else {
            // 通常レイヤーに戻す
            layer_move(_BASE);
        }
        
        // RGB色を更新
        uint8_t active_layer = macbook_mode_active ? _MACBOOK : _BASE;
        rgb_matrix_sethsv(layer_colors[active_layer].h, layer_colors[active_layer].s, layer_colors[active_layer].v);
    }
}
#endif
