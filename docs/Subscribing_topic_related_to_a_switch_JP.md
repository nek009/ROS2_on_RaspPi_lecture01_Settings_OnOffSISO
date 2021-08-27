[Topページへ](../README_JP.md)

# 概要

ここではスイッチの状態を受け取るsubscriberノードの作成を行う．
このノードは受け取ったメッセージによってledの点灯/消灯をコントロールする．
スイッチが押されていたら点灯し，離れされていたら消灯する．
トピックメッセージは[ここ](Creation_of_a_topic_message_for_a_state_of_a_switch_JP.md)で作成したものを用いる．

# コンポーネントとしてのSubscriberノード
作成するsubscriberノードは以下のトピックを通してメッセージを受信する．

* トピック名
  * pub_gpio_state

## ROS2プログラミング
ノードを`--library-name`オプション付きで作成するので，諸々準備してくれる．
例えば，visibility_control.hなどは自動で準備してくれる．

### ROS2 packageの準備

```shell
$ colcon_cd
$ ros2 pkg create gpio_led_control_node --build-type ament_cmake --dependencies rclcpp rclcpp_components gpio_msgs --library-name gpio_led_control_component_node
```

以下のファイルが自動作成される．

- gpio_led_control_node/
  - include/gpio_led_control_node/visibility_control.h
  - include/gpio_led_control_node/gpio_led_control_component_node.hpp
  - src/gpio_led_control_component_node.cpp
  - CMakeLists.txt
  - package.xml

またいくつかの名前は以下のようになる．

- package name
  - gpio_led_control_node
- namespace
  - gpio_led_control_node
- ヘッダファイルで使用するmacro，exportしたいやつには全部つける必要あり
  - GPIO_LED_CONTROL_NODE_PUBLIC
- library name
  - gpio_led_control_component_node
- class name
  - GpioLedControlComponentNode


### プログラミング

* 設定ファイル
  * gpio_led_control_node/include/gpio_led_control_node/[gpio_led_control_component_node.hpp](../src/gpio_led_control_node/include/gpio_led_control_node/gpio_led_control_component_node.hpp)
  * gpio_led_control_node/src/[gpio_led_control_component_node.cpp](../src/gpio_led_control_node/src/gpio_led_control_component_node.cpp)

### CMakeLists.txtの編集

* 設定ファイル
  * gpio_led_control_node/[CMakeLists.txt](../src/gpio_led_control_node/CMakeLists.txt)

## ビルド & 確認
### ビルド

```shell
$ colcon_cd
$ colcon build --symlink-install --packages-up-to gpio_led_control_node
$ . install/local_setup.bash
```

### 確認1
ターミナルを二つ(term1とterm2とする)起動する．
term1でノードを実行する．

```shell
$ . install/local_setup.bash
$ ros2 component standalone gpio_state_recognition_node ros2rasp_lecture::PubGpioStateComponentNode
```

term2でノードがメッセージを発信しているか，ROS2コマンドで確認する．

```shell
$ . install/local_setup.bash
$ ros2 topic echo /pub_gpio_state
```

スイッチを押したり離したりしてledが点灯/消灯することを確認する．

### 確認2
他の方法として`ros2 component load`コマンドを使用する方法を紹介する．
詳細な使い方は[こちら](PubGpioStateComponentNode)を参照のこと．<br>
ターミナルを二つ(term1とterm2とする)起動する．
コンポーネントを管理し複数のノードを取り扱うものをterm1で実行する．
このコンポーネントマネージャが，スイッチに関するpublisherノードとledをコントロールするsubscriberを取り扱うことになる．

```shell
$ . install/local_setup.bash
$ ros2 run rclcpp_components component_container
```

term2でコンポーネントマネージャにノードをロードしていく．

```shell
$ . install/local_setup.bash
$ ros2 component load /ComponentManager gpio_state_recognition_node ros2rasp_lecture::PubGpioStateComponentNode
$ ros2 component load /ComponentManager gpio_led_control_node ros2rasp_lecture::GpioLedControlComponentNode
```

スイッチを押したり離したりしてledが点灯/消灯することを確認する．
