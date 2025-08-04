@echo off
REM Guitar Procyon 36 ビルドスクリプト
REM 使用方法: build.bat [keymap] [target]

setlocal enabledelayedexpansion

REM デフォルト値の設定
set KEYMAP=default
set TARGET=compile

REM 引数の処理
if not "%1"=="" set KEYMAP=%1
if not "%2"=="" set TARGET=%2

echo ========================================
echo Guitar Procyon 36 ビルドスクリプト
echo ========================================
echo キーマップ: %KEYMAP%
echo ターゲット: %TARGET%
echo ========================================

REM QMK環境の確認
echo QMK環境を確認中...
qmk --version >nul 2>&1
if errorlevel 1 (
    echo エラー: QMK CLIが見つかりません
    echo MSYS2 MinGW 64-bitターミナルで実行してください
    pause
    exit /b 1
)

REM キーボードの存在確認
echo キーボード設定を確認中...
qmk list-keyboards | findstr "36_procyon_bwrs1" >nul 2>&1
if errorlevel 1 (
    echo エラー: 36_procyon_bwrs1/guitar_procyon36 が見つかりません
    echo QMKファームウェアのセットアップを確認してください
    pause
    exit /b 1
)

REM ビルド実行
echo ビルドを開始します...
if "%TARGET%"=="flash" (
    echo フラッシュモードでビルド中...
    qmk flash -kb 36_procyon_bwrs1/guitar_procyon36 -km %KEYMAP%
) else (
    echo コンパイルモードでビルド中...
    qmk compile -kb 36_procyon_bwrs1/guitar_procyon36 -km %KEYMAP%
)

REM 結果の確認
if errorlevel 1 (
    echo ========================================
    echo ビルドエラーが発生しました
    echo ========================================
    echo トラブルシューティング:
    echo 1. qmk doctor で環境を確認
    echo 2. 設定ファイルの構文を確認
    echo 3. 依存関係を確認
    pause
    exit /b 1
) else (
    echo ========================================
    echo ビルドが完了しました
    echo ========================================
    if "%TARGET%"=="flash" (
        echo ファームウェアがフラッシュされました
    ) else (
        echo ファームウェアファイルが生成されました
        echo 場所: .build/36_procyon_bwrs1_guitar_procyon36_%KEYMAP%.uf2
    )
)

pause 