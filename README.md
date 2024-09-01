# M5Stack 用 LINE Notify ライブラリ

M5Stack で LINE Notify を使用するためのライブラリです。PlatformIO IDE 環境での使用を想定しています。

- `LINENotify`クラス  
  LINE Notify の API に WiFi 経由で接続して通知する

WiFi の接続情報や LINE Notify に必要なアクセス・トークンをソースにベタ書きせずに自由に切り替えられるよう，SPIFFS に設定ファイルを置いて読み出す仕組みも用意しています。

- `SPIFFSLoader`クラス  
  SPIFFS からファイルを読み込む
- `ConfigParser`クラス  
  SPIFFS から設定ファイルを読み込んで値を取り出す
- `LINENotifyConfigParser`クラス  
  WiFi に接続するための SSID・パスワード，LINE Notify に必要なアクセス・トークン値を設定ファイルから取り出す

## 実装例

いずれの実装例も 設定ファイル（JSON 形式）を SPIFFS に置くことで，WiFi の接続情報や LINE Notify に必要なアクセス・トークンを切り替えられます。

ATOM シリーズ（S3 も含む）を対象としていますが，他の機種でも`platformio.ini`に設定を追加すれば使えるはずです。

### 実装例の設定ファイル

`data`ディレクトリ（`platformio.ini`の`[platformio]`セクションにある`data_dir`で指定したディレクトリ）に `LINENotifyConfigParser::parse()`に渡す JSON ファイル（`line_notify.json`）を置いて LINE Notify に接続するために必要な情報を記載します。

```json
{
  "ssid": "[SSID]",
  "password": "[パスワード]",
  "token": "[LINE Notifyのパーソナル・アクセス・トークン]",
  "message": "[LINE Notifyで通知するメッセージ]"
}
```

ここで指定するパーソナル・アクセス・トークンは[LINE Notify のマイページ](https://notify-bot.line.me/my/)から発行できます。

`message`には UTF-8 で約 48 文字までのメッセージを指定できます。変更したい場合は`LINENotifyConfigParser`クラスの`MAX_MESSAGE_LEN`を変更してください。

ファームウェアを書き込んだ後，PlatformIO メニューから「Upload Filesystem Image」を選択するか，コマンドラインから`pio run --target uploadfs`を実行して設定ファイルを SPIFFS にアップロードし，設定を反映します。

### 実装例：ボタンを押すたびに押したことを通知する

`examples/m5stack-line-notify-push/main.cpp`は，ボタンが押されるたびに押されたことを通知します。

### 実装例：起動するたびに IP アドレスを通知する

`examples/m5stack-line-notify-ip-address/main.cpp`は，起動するたびに自分の IP アドレスを通知します。
