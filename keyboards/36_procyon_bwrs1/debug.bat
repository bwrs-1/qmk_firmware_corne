@echo off
REM Guitar Procyon 36 デバッグスクリプト
REM タッチパッドの問題診断用

echo ========================================
echo Guitar Procyon 36 デバッグスクリプト
echo ========================================
echo タッチパッドの問題診断を開始します
echo ========================================

REM 環境チェック
echo 1. QMK環境の確認...
qmk --version >nul 2>&1
if errorlevel 1 (
    echo エラー: QMK CLIが見つかりません
    echo MSYS2 MinGW 64-bitターミナルで実行してください
    pause
    exit /b 1
)
echo ✓ QMK CLI: OK

REM キーボード設定の確認
echo 2. キーボード設定の確認...
qmk list-keyboards | findstr "36_procyon_bwrs1" >nul 2>&1
if errorlevel 1 (
    echo エラー: 36_procyon_bwrs1/guitar_procyon36 が見つかりません
    pause
    exit /b 1
)
echo ✓ キーボード設定: OK

REM 設定ファイルの確認
echo 3. 設定ファイルの確認...
if not exist "keyboards\36_procyon_bwrs1\guitar_procyon36\config.h" (
    echo エラー: config.h が見つかりません
    pause
    exit /b 1
)
echo ✓ config.h: OK

if not exist "keyboards\36_procyon_bwrs1\guitar_procyon36\rules.mk" (
    echo エラー: rules.mk が見つかりません
    pause
    exit /b 1
)
echo ✓ rules.mk: OK

REM タッチパッド設定の確認
echo 4. タッチパッド設定の確認...
findstr "I2C1_CLOCK_SPEED 100000" keyboards\36_procyon_bwrs1\guitar_procyon36\config.h >nul 2>&1
if errorlevel 1 (
    echo 警告: I2C通信速度が100kHzに設定されていません
    echo 現在の設定を確認してください
) else (
    echo ✓ I2C通信速度: 100kHz
)

findstr "POINTING_DEVICE_DEBOUNCE_TIME" keyboards\36_procyon_bwrs1\guitar_procyon36\config.h >nul 2>&1
if errorlevel 1 (
    echo 警告: デバウンス設定が見つかりません
) else (
    echo ✓ デバウンス設定: OK
)

findstr "POINTING_DEVICE_FILTER_ENABLE" keyboards\36_procyon_bwrs1\guitar_procyon36\config.h >nul 2>&1
if errorlevel 1 (
    echo 警告: フィルタリング設定が見つかりません
) else (
    echo ✓ フィルタリング設定: OK
)

findstr "MAXTOUCH_DEBUG = yes" keyboards\36_procyon_bwrs1\guitar_procyon36\rules.mk >nul 2>&1
if errorlevel 1 (
    echo 警告: デバッグが有効になっていません
) else (
    echo ✓ デバッグ設定: 有効
)

REM ビルドテスト
echo 5. ビルドテスト...
echo デバッグ版ファームウェアをビルド中...
qmk compile -kb 36_procyon_bwrs1/guitar_procyon36 -km default > build.log 2>&1
if errorlevel 1 (
    echo エラー: ビルドに失敗しました
    echo build.log を確認してください
    type build.log
    pause
    exit /b 1
) else (
    echo ✓ ビルド: 成功
    echo ファームウェアファイル: .build\36_procyon_bwrs1_guitar_procyon36_default.uf2
)

REM デバッグ情報の表示
echo ========================================
echo デバッグ情報
echo ========================================
echo キーボード: 36_procyon_bwrs1/guitar_procyon36
echo キーマップ: default
echo ファームウェア: .build\36_procyon_bwrs1_guitar_procyon36_default.uf2
echo ========================================

REM 次のステップの案内
echo 次のステップ:
echo 1. キーボードをブートローダーモードで接続
echo 2. ファームウェアをフラッシュ
echo 3. シリアルモニターでデバッグ情報を確認
echo 4. タッチパッドの動作をテスト
echo ========================================

echo デバッグスクリプトが完了しました
pause 