[Topページへ](README_JP.md)

# 概要
ここでは一般ユーザ追加の方法を紹介する．
特段変わった方法ではなく，普通のLinuxでのユーザ追加方法である．
このリポジトリでは，pigpioデーモンを使用することで一般ユーザでのRaspberry Piの制御を行う．

# ユーザの追加
以下は，ユーザ名`nek`とした例となる．

```shell
$ sudo adduser nek
New password:  # <- nek用のパスワード入力．
Retype new password: # <-入力したパスワードのチェック．
... # 少しメッセージが流れる．
  Full Name []: # ここから以下は必要に応じて入力．空でもよい(Enterキー連打でok)
  Room Number []:
  ...
```
