# M5Stack 用 LINE Notify ライブラリ

M5Stack で LINE Notify を使用するためのライブラリです。PlatformIO IDE 環境での使用を想定しています。

設定ファイル（JSON）を SPIFFS に置くことで，WiFi の接続情報や LINE Notify に必要なアクセス・トークンを切り替える仕組みも用意しています。

- `SPIFFSLoader`クラス  
  SPIFFS からファイルを読み出す
- `ConfigParser`クラス  
  `line_notify.json`を解析して値を取り出す
- `LINENotify`クラス  
  LINE Notify の API に WiFi 経由で接続して通知する

## 設定ファイル `line_notify.json`

`data`ディレクトリ（`platformio.ini`の`[platformio]`セクションにある`data_dir`で指定したディレクトリ）に`line_notify.json`という名前で LINE Notify に必要な情報を記載します。

```line_notify.json
{
  "ssid": "[SSID]",
  "password": "[パスワード]",
  "token": "[LINE Notifyのパーソナル・アクセス・トークン]"
}
```

※パーソナル・アクセス・トークンは[LINE Notify のマイページ](https://notify-bot.line.me/my/)から発行できます。

`line_notify.json`を SPIFFS にアップロードすることで設定を反映できます。PlatformIO メニューから「Upload Filesystem Image」を選択するか，コマンドラインから`pio run --target uploadfs`を実行するとアップロードできます。

## 実装例

`examples/m5stack-line-notify-sample/main.cpp`を参照してください。
