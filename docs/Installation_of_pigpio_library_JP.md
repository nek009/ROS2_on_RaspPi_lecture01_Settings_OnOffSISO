[Topページへ](README_JP.md)

# 概要
pigpio ライブラリに関する情報をまとめたページ．
メインの言語はC/C++とする．

# pigpio ライブラリのインストール

[公式ページ](http://abyz.me.uk/rpi/pigpio/index.html)の[Download & Install page](http://abyz.me.uk/rpi/pigpio/download.html)を見ながらインストール.

# pigpioを用いたプログラミング
## 基本的な使い方

[pigpio C I/F](http://abyz.me.uk/rpi/pigpio/cif.html)のページを見ながら作成すれば大体大丈夫．基本的な情報としては以下の通り．

* ヘッダ情報
  * #include <pigpio.h>
* ビルド/コンパイル情報
  * オプション
    * `-Wall -pthread`
  * リンカ
    * `-lpigpio`
    * `-lrt`
      * [pigpio C I/F](http://abyz.me.uk/rpi/pigpio/cif.html)ページでは使用されているが不必要．libgccに含まれたとかなんとか．

## ROS2での使用
ROS2でpigpioを使用する場合，CMakeLists.txtは以下のように書く(関係する部分を抜粋)．

```CMakeLists
target_compile_options([ターゲット名]
  PUBLIC -Wall -pthread
)
target_link_libraries([ターゲット名]
  pigpio
)
```

## GPIOピンについて
Raspberry Piの場合，チップによるピンの数え方と基板上からみたピンの数え方が違う．pigpioではチップによるピンの数え方をしているので注意．例えば，下図の右下のピンを使いたい場合は40ではなく21の数字を指定することになる．

![gpio_assin](./figs/gpio_pin.png)
