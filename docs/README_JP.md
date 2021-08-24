# 概要

このリポジトリはプログラムのためのものではなく，UbuntuがインストールされたRaspberry Piや同様のシングルボードコンピュータ上でROS2を使用するためのレクチャーシリーズです．

## 最終目標
ROS2を使用してハードウェアを使用する方法を学ぶ．
対象とする回路を下図に示しておく．
図ではRaspberry Piによってledを点灯/消灯させ，スイッチの状態を認識している．
それらをROS2を使用してコントロールすることを考える．<br>

<img src="figs/led_switch.png" width="500">

# 目次
## 管理者向け

1. [Raspberry PiへのUbuntu Serverのインストール](Installation_of_UbuntuServer_on_RaspberryPi_JP.md)
1. [Raspberry PiへのROS2のインストール](Installation_of_ROS2_on_RaspberryPi_JP.md)
1. [pigpioのインストール](Installation_of_pigpio_library_JP.md)
1. [一般ユーザの追加](Addition_of_general_users_JP.md)

## 一般ユーザ向け
### 準備

1. [初期設定](Initial_settings_of_general_users_JP.md)
1. [C++でのpigpiodの使用方法](Usage_of_pigpiod_in_cpp_JP.md)

### ROS2プログラミング
始める前に[公式のチュートリアル for foxy](https://docs.ros.org/en/foxy/Tutorials.html)を読むこと．

1. [スイッチのOn/OffによるTopicのpublish](Publishing_topic_by_pushing_releasing_a_switch_JP.md)
