## このフォークの現状サマリー（Corne Procyon / Dilemma_3X6）

このレポジトリはQMK Firmwareベースのフォークで、`keyboards/corne_procyon36_tmp`（USB名: lucky_studio Dilemma_3X6）を対象に、以下の対応を進めています。

- RGB制御レイヤーの再設計（マウス操作レイヤー化の計画）
- Remap/VIA によるGUIキーマップ編集対応
- Procyonタッチパッド（MaxTouch相当）連携（カスタムポインティングデバイスドライバ）
- 分割（スプリット）キーボードの安定動作

### 現在のソース構成と主要設定

- キーマップ `keyboards/corne_procyon36_tmp/keymaps/default/keymap.c`
  - レイヤー: `_BASE`, `_LOWER`, `_RAISE`, `_ADJUST`, `_RGB`（現状はRGB制御レイヤーのまま）
  - エンコーダー: `_BASE`でマウスホイール/音量、`_ADJUST`/`_RGB`でRGB調整

- キーボード定義 `keyboards/corne_procyon36_tmp/keyboard.json`
  - features: `pointing_device: true`, `digitizer: true`（両方有効。競合の可能性があるため要見直し）
  - split.enabled: `true`。`transport.sync`で`indicators/layer_state/matrix_state/modifiers`を同期
  - USB VID/PID: `0xAFC6/0xBFC6`

- ビルド設定 `keyboards/corne_procyon36_tmp/rules.mk`
  - `POINTING_DEVICE_ENABLE = yes`
  - `POINTING_DEVICE_DRIVER = custom` / `POINTING_DEVICE_DRIVER_NAME = procyon`
  - `VIA_ENABLE = yes`

- ハード設定 `keyboards/corne_procyon36_tmp/config.h`
  - 左右判定: `SPLIT_HAND_PIN GP29`、`SPLIT_HAND_PIN_LOW_IS_RIGHT`（Low=右）
  - 分割通信: `SERIAL_USART_FULL_DUPLEX`、TX=`GP0` / RX=`GP1`、`SELECT_SOFT_SERIAL_SPEED 4`
  - I2C: SDA=`GP2` / SCL=`GP3`、`I2C1_CLOCK_SPEED 1000000`
  - ポインティング: `SPLIT_POINTING_ENABLE`、`POINTING_DEVICE_RIGHT`

- Procyonドライバ `drivers/sensors/procyon.c`
  - I2Cアドレス自動検出: `0x4B`→`0x4A`の順で`0x00`レジスタをping
  - データ取得: `0x01`から4バイト読み取り→相対移動に変換（Yは反転）
  - ログ: `uprintf`で初期化・読取状況を出力

### 既知の問題（ブロッカー）

- 分割通信エラーが継続（HID Consoleログに「Failed to execute slave_matrix」「Target disconnected」）。
- タッチパッドが未動作（I2C ACKが得られていない可能性）。
- RemapでJSONインポート直後に初期画面へ戻る事象（スキーマ/機能整合の不一致が疑い）。

### ビルド/フラッシュ手順（RP2040, UF2）

1. 右手用UF2生成:
   - `make -j4 corne_procyon36_tmp:default:uf2-split-right`
2. 左手用UF2生成:
   - `make -j4 corne_procyon36_tmp:default:uf2-split-left`
3. 各半分をブートモードにして、生成されたUF2を`RPI-RP2`ドライブへコピー

※ 同一バージョンのファームを左右双方へ書き込んでください。

### デバッグの要点

- Console/HID Console（`uprintf`）で初期化やI2Cエラーを確認
- 分割動作:
  - USB接続側がマスター
  - `SPLIT_HAND_PIN`（`GP29`）の入力状態で左右判定（Low=右）
- I2C配線/電源の再確認（SDA=`GP2`, SCL=`GP3`, 1MHz）

### Remap/VIA について

- `VIA_ENABLE = yes`。Remapは最新URLの使用を推奨（`https://remap-keys.app/latest`）。
- JSON定義は `keyboards/corne_procyon36_tmp/corne_procyon36_tmp_remap.json` を使用（物理配列/lighting/USB情報の整合が必要）。

### 変更・削除ファイル（最近）

- 主な編集ファイル:
  - `keyboards/corne_procyon36_tmp/keymaps/default/keymap.c`
  - `keyboards/corne_procyon36_tmp/config.h`
  - `keyboards/corne_procyon36_tmp/rules.mk`
  - `keyboards/corne_procyon36_tmp/keyboard.json`
  - `drivers/sensors/procyon.c`
- 削除:
  - `keyboards/corne_procyon36_tmp/test_keymap.c`
  - `keyboards/corne_procyon36_tmp/debug_config.h`

### 今後のアクション（推奨）

- 分割通信の復旧:
  - 左右双方へ同一ビルドを書き込み、データ線/電源/ケーブルを確認
  - `SPLIT_HAND_PIN`運用を継続するか、`SPLIT_USB_DETECT`へ変更するか検討
- 機能競合の解消:
  - `keyboard.json`の`digitizer`を`false`にし、`pointing_device`のみに統一（現状のカスタムドライバ設計に合わせる）
- Remap JSONの整合:
  - 物理配列・lighting・USB情報・`qmk.keyboard`・`version`の整合を再確認
- タッチパッド:
  - HID Consoleで`[PROCYON] init OK/FAIL`ログを確認し、I2C応答が無い場合は配線・電源・アドレスを再点検

---

# Quantum Mechanical Keyboard Firmware

[![Current Version](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/qmk)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

This is a keyboard firmware based on the [tmk\_keyboard firmware](https://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR and ARM controllers, and more specifically, the [OLKB product line](https://olkb.com), the [ErgoDox EZ](https://ergodox-ez.com) keyboard, and the Clueboard product line.

## Documentation

* [See the official documentation on docs.qmk.fm](https://docs.qmk.fm)

The docs are powered by [VitePress](https://vitepress.dev/). They are also viewable offline; see [Previewing the Documentation](https://docs.qmk.fm/#/contributing?id=previewing-the-documentation) for more details.

You can request changes by making a fork and opening a [pull request](https://github.com/qmk/qmk_firmware/pulls).

## Supported Keyboards

* [Planck](/keyboards/planck/)
* [Preonic](/keyboards/preonic/)
* [ErgoDox EZ](/keyboards/ergodox_ez/)
* [Clueboard](/keyboards/clueboard/)
* [Cluepad](/keyboards/clueboard/17/)
* [Atreus](/keyboards/atreus/)

The project also includes community support for [lots of other keyboards](/keyboards/).

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [ZSA Technology Labs](https://github.com/zsa), the Clueboard by [Zach White](https://github.com/skullydazed), and the Atreus by [Phil Hagelberg](https://github.com/technomancy).

## Official Website

[qmk.fm](https://qmk.fm) is the official website of QMK, where you can find links to this page, the documentation, and the keyboards supported by QMK.
