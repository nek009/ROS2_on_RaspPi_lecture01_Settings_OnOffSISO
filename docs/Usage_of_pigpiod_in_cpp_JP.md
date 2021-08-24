[Topページへ](README_JP.md)

# 概要
ここではpigpiodを使ってハードウェアにアクセスする仕方を簡単に紹介する．
対象言語はc++である．<br>
まず，このリポジトリで使用する回路を下図に示す．

![target circuit](figs/led_switch.png)

# 回路の作成
図のとおり，回路を作成する．

# プログラムの作成
プログラムを作成するための諸情報は公式の[pigpiod C Interface](http://abyz.me.uk/rpi/pigpio/pdif2.html)を参照のこと．
特に，`ESSENTIAL`と`BASIC`は重要となる．<br>
プログラムの流れは以下のようになる．

1. pigpiodを使用するための初期化(pigpio_start)
1. 使用するGPIOのモード設定(set_mode)
1. GPIOの利用(gpio_read), gpio_write)
1. pigpiodの終了処理(pigpio_stop)

pigpioデーモンはネットワークを通して複数のRasperry Piを扱うことができる．
そのため，どのRaspberry Piへの指令なのか区別する必要があり，pigpio_start関数の返り値でそれを行っている．

## 簡単な使用方法

* ソースファイル
  * [src/pigpio_library_test/src/on_off_siso.cpp](../src/pigpio_library_test/src/on_off_siso.cpp)

### ビルドと実行
ソースファイルをDLするか自分でつくって準備し，以下ようにビルド・実行する．

```shell
$ g++ -Wall -pthread -o on_off_siso on_off_siso.cpp -lpigpiod_if2
$ ./on_off_siso
```

実行後，スイッチを押すとledが消灯し，スイッチを離すとledが点灯する．

### 説明

<details><summary>pigpiodを使用するための初期化</summary><div>

[on_off_siso.cppの7行目から11行目](../src/pigpio_library_test/src/on_off_siso.cpp#L7-L10)で初期化を行っており，引数で使用するRasperry Piを指定している．
一つ目の引数が`NULL`の場合は接続先がlocalhostとなり，二つ目の引数が`NULL`の場合接続ポートが8888となる．
プログラムを実行しているRaspberry Piを使用する(ネット経由で他のRaspberry Piを使用しない)のであれば，`NULL`でよい．
</div></details>
<details><summary>使用するGPIOのモード設定</summary><div>

[on_off_siso.cppの13行目から16行目](../src/pigpio_library_test/src/on_off_siso.cpp#L13-L16)でGPIOの使用モードを指定している．<br>
GPIO21にはledがつながっており，`出力`として使用する．
そこで[on_off_siso.cppの14行目](../src/pigpio_library_test/src/on_off_siso.cpp#L14)にてGPIO21を出力(OUTPUT)として設定している．<br>
またGPIO26にはスイッチがつながっており，`入力`として使用する．
同じように[on_off_siso.cppの16行目](../src/pigpio_library_test/src/on_off_siso.cpp#L16)にてGPIO26を入力(INPUT)として設定している．
</div></details>
<details><summary>GPIOの利用</summary><div>

[on_off_siso.cppの18行目から22行目](../src/pigpio_library_test/src/on_off_siso.cpp#L18-L22)でスイッチの状態によってledの点灯/消灯を制御している．<br>
[on_off_siso.cppの19行目](../src/pigpio_library_test/src/on_off_siso.cpp#L19)ではGPIO26の状態を読んで，変数`input`に保存している．
ここでGPIO26のプルダウン抵抗によって，スイッチが押されるとGPIO26はHIGHになり`input`に`1`が保存される．
またスイッチが離されるとGPIO26はLOWになり，`input`には`0`が保存される．<br>
[on_off_siso.cppの20行目](../src/pigpio_library_test/src/on_off_siso.cpp#L20)では`input`の値がGPIO21に出力される．
ここでGPIO21が`0`の時ledが点灯し`1`の時ledは消灯する回路となっている(シンクロジック)．
そのため，スイッチを押すと`input`が`1`になりGPIO21が`1`を出力し，ledが消灯する．<br>
また[on_off_siso.cppの21行目](../src/pigpio_library_test/src/on_off_siso.cpp#L21)にて1秒間スリープし，ledの状態を保っている．
</div></details>
<details><summary>pigpiodの終了処理</summary><div>

[on_off_siso.cppの24行目](../src/pigpio_library_test/src/on_off_siso.cpp#L24)にてpigpiodの終了処理をしている．
</div></details>

## callback関数を使用した方法

* ソースファイル
  * [src/pigpio_library_test/src/on_off_siso_with_callback.cpp](../src/pigpio_library_test/src/on_off_siso_with_callback.cpp)

### ビルドと実行
ソースファイルをDLするか自分でつくって準備し，以下ようにビルド・実行する．

```shell
$ g++ -Wall -pthread -o on_off_siso_with_callback on_off_siso_with_callback.cpp -lpigpiod_if2
$ ./on_off_siso_with_callback
```

実行後，スイッチを押すとledが消灯し，スイッチを離すとledが点灯する．

### 説明
簡単な使用方法ではループとsleep関数を使ってスイッチ(GPIO26)の状態を認識しledを点灯/消灯させるプログラムを紹介した．
ここでもしsleep(10)とし10秒間停止させていたら，スイッチが押されてから認識するまで最大で10秒近く遅延が生じる．<br>
この章では遅延をなるべく少なくするためにcallback関数を用いた状態認識の方法を紹介する．
callback関数を用いた方法では，プログラムを一行一行実行するのではなく，背後でGPIOの状態を監視して変化があれば動的にcallback関数を呼び出す．
流れとしては，1)GPIOの状態が変化したときにやってほしい処理をcallback関数として作成し，2)callback関数を登録する．callback関数の登録では，監視対象のGPIOをどれにするか，そのGPIOがどのように変化したときにcallback関数を呼び出すか(信号がLOWからHIGHか，HIGHからLOWか，その両方か)を設定する．<br>


[on_off_siso_with_callback.cppの5行目](../src/pigpio_library_test/src/on_off_siso_with_callback.cpp#L5)ではcallback関数の宣言を行っており，[on_off_siso_with_callback.cppの29-32行目](../src/pigpio_library_test/src/on_off_siso_with_callback.cpp#L29-L32)で実装を行っている．
そして[on_off_siso_with_callback.cppの20行目](../src/pigpio_library_test/src/on_off_siso_with_callback.cpp#L20)にてcallback関数の登録をしている．
この行にて，GPIO26を監視対象として，信号の変化があったときにcallback_push_switch関数を呼び出すように設定している．
プログラムが終了すると監視も終わるので，[on_off_siso_with_callback.cppの23行目](../src/pigpio_library_test/src/on_off_siso_with_callback.cpp#L20)で10秒停止している．
この間，バックグラウンドでGPIOの監視が行われ，スイッチが押されたり離されたりするごとにcallback_push_switch関数が呼ばれいている．
