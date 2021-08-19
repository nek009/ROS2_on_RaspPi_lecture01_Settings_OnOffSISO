[Topページへ](README_JP.md)

# 概要

Raspberry PiのスタンダードなOSはRaspbian OSですが，これはDebianベースのものとなる．
目的はROS2を走らせることで，ROS2をDebianにインストールするのは面倒なので，ここではUbuntuをインストールして使用する．<br>
本ページではUbuntuのインストールについて簡単に説明する．

## ネットワーク環境の変動に対する考え方
Rasp. Piの場合，使用状況が色々変わる．企業や研究室のようにちゃんと設計されたところもあれば屋外のように全然用意されていないところもある．特にDNSやDHCP，その他のネットワークサービスが使えるか使えないか分からない．
これらを考えて，LANの設定方針を述べておく．

### 無線LANの場合
無線LANの場合，IPアドレスが自動で割り振られる状況(DHCP serverがある状況)のみを想定する．
IPアドレスが自動で割り振られない場合，そもそも無線サービスが使えないと考える．

* 設定方針
  * IPアドレスはDHCP serverによって設定されるものとする．
  * DNS serverがないことも考え，avahi-daemonを使って名前解決をする．
    * DNS serverも使えれば使う．

### 有線LANの場合
有線LANの場合，以下の状況が考えられる．

1. ケーブルが抜けている．
1. DHCP serverがないネットワークに接続しちゃった
1. DHCP serverがあってちゃんとIPアドレスなどが割り振られるネットワークに接続できた．
1. 固定IPアドレスを設定しなければならないネットワークに接続した．

このうち4番目の場合は考えず(個別の環境なので適切に設定してね，とまるなげ)，1番目から3番目までに対応できるように考える．
特にRaspberry Piを持ち運ぶ場合，動的にネットワーク環境が変わることもあるので，出来るだけ対応できるようにしたい．

* 設定方針
  * link-localによるプライベートIP(169.254.0.0/16)の割り当て．
  * DNS serverがないことも考え，avahi-daemonを使って名前解決をする．
    * DNS serverも使えれば使う．

# Ubuntu Serverのインストール・設定
## microSDカードへのインストール
[このページ](https://ubuntu.com/download/raspberry-pi)の"Follow our desktop or server tutorials."にある[server](https://ubuntu.com/tutorials/how-to-install-ubuntu-on-your-raspberry-pi#1-overview)をクリックして手順通りにインストール．<br>
Raspberry Pi Imagerを使用してインストールすることになるが，特に気を付ける点は以下のところ．

* CHOOSE OS
  * "Other general purpose OS"を選択
    * "Ubuntu Server 20.04.2 LTS(RPi 3/4/400) 64bit"を選択

## Ubuntu Serverの起動
microSDカード，HDMI, キーボード，マウスをRapberry Piにつなげて起動すると，Ubuntu Serverのインストールと基本設定が行われるので，数分待つ．
最初の起動後，ID: ubuntu, password: ubuntuでログイン可．
ログイン後，すぐにパスワードの変更を求められるので，新しいパスワードを設定する．

## ネットワークの設定

* 設定ファイル
  * /etc/netplan/[50-cloud-init.yaml](../yaml/50-cloud-init.yaml)
* 追加説明
  * [renderer: networkd](../yaml/50-cloud-init.yaml#L3)を使用.
    * netplanの場合，rendererにnetworkdとNetworkManagerを選択できる．しかしNetworkManagerの場合，dhcp4: trueにするとlink-localのオプションが無効化されてしまう([link-local option in netplan reference](https://netplan.io/reference/#common-properties-for-all-device-types)を参照)．よってnetworkdを使用する．

設定後，以下のコマンドでネットワークの設定を有効化．

```shell
$ sudo netplan apply
```

## avahi-daemon(と諸々)のインストール

```shell
$ sudo apt install avahi-daemon ssh git
$ sudo systemctl enable avahi-daemon
$ sudo systemctl start avahi-daemon
```

これで/etc/hostnameに格納されているホスト名でアクセスできる．
正確には，ホスト名+".local"でアクセスできる．
まず以下のコマンドで名前を確認してみる．

```shell
$ cat /etc/hostname
raspberry pi
```

この例の場合，ホスト名が`raspberrypi`となる．
よって，以下のコマンドでアクセスできる．

```shell
$ ssh ubuntu@raspberrypi.local
```

ここで，`.`(ピリオド，ドット)が名前の一部として使えないことに注意する．例えば，`raspberry.pi`のホスト名はだめ(`raspberry.pi.local`ではアクセスできない)．
