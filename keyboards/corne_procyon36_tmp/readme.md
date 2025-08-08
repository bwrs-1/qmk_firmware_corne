# Corne Procyon 36 TMP - PCB

/* ============================================================================
 * Corne Procyon 36 TMP キーボード
 * ============================================================================
 * このキーボードはCorne Procyon 36のカスタムバージョンです。
 * ProcyonポインティングデバイスとRGBライト機能を搭載しています。
 */

![kafkasplit](https://i.imgur.com/fqxZGeHh.jpg)

A 44-key split keyboard with rgb

/* ============================================================================
 * ハードウェア情報
 * ============================================================================ */
* Keyboard Maintainer: https://github.com/LXF-YZP
* Hardware Supported: https://github.com/LXF-YZP/KafkaSplit

/* ============================================================================
 * ビルド方法
 * ============================================================================ */
Make example for this keyboard (after setting up your build environment):
    
    make corne_procyon36_tmp:default
    
/* ============================================================================
 * ファームウェア書き込み方法
 * ============================================================================ */
Flashing example for this keyboard:

    make corne_procyon36_tmp:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

/* ============================================================================
 * ブートローダー進入方法
 * ============================================================================ */
Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available