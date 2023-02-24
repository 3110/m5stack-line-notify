# LINE Notify 用ライブラリ

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
