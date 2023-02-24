# M5Stack 用 LINE Notify ライブラリ

M5Stack で LINE Notify を使用するためのライブラリです。PlatformIO IDE 環境での使用を想定しています。

設定ファイル（JSON 形式，デフォルトは`line_notify.json`）を SPIFFS に置くことで，WiFi の接続情報や LINE Notify に必要なアクセス・トークンを切り替える仕組みも用意しています。

- `SPIFFSLoader`クラス  
  SPIFFS からファイルを読み込む
- `ConfigParser`クラス  
  SPIFFS から設定ファイルを読み込んで値を取り出す
- `LINENotify`クラス  
  LINE Notify の API に WiFi 経由で接続して通知する

## 実装例

`examples/m5stack-line-notify-sample/main.cpp`を参照してください。

### 実装例の設定ファイル

`data`ディレクトリ（`platformio.ini`の`[platformio]`セクションにある`data_dir`で指定したディレクトリ）に `ConfigParser::parse()`に渡す JSON ファイル（デフォルトは`ConfigParser::CONFIG_FILENAME`（`line_notify.json`））を置いて LINE Notify に接続するために必要な情報を記載します。

```json
{
  "ssid": "[SSID]",
  "password": "[パスワード]",
  "token": "[LINE Notifyのパーソナル・アクセス・トークン]"
}
```

※ここで指定するパーソナル・アクセス・トークンは[LINE Notify のマイページ](https://notify-bot.line.me/my/)から発行できます。

PlatformIO メニューから「Upload Filesystem Image」を選択するか，コマンドラインから`pio run --target uploadfs`を実行して設定ファイルを SPIFFS にアップロードし，設定を反映します。
