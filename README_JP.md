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

1. [Raspberry PiへのUbuntu Serverのインストール](docs/Installation_of_UbuntuServer_on_RaspberryPi_JP.md)
1. [Raspberry PiへのROS2のインストール](docs/Installation_of_ROS2_on_RaspberryPi_JP.md)
1. [pigpioのインストール](docs/Installation_of_pigpio_library_JP.md)
1. [一般ユーザの追加](docs/Addition_of_general_users_JP.md)

## 一般ユーザ向け
### 準備

1. [初期設定](docs/Initial_settings_of_general_users_JP.md)
1. [C++でのpigpiodの使用方法](docs/Usage_of_pigpiod_in_cpp_JP.md)

### ROS2プログラミング
始める前に[公式のチュートリアル for foxy](https://docs.ros.org/en/foxy/Tutorials.html)を読むこと．

1. [スイッチの状態に関するtopicメッセージの作成](docs/Create_a_topic_message_for_a_state_of_a_switch_JP.md)
1. [スイッチのOn/OffによるTopicのpublish](docs/Publishing_topic_by_pushing_releasing_a_switch_JP.md)
