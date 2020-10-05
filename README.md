# shout

ネタのためのクソコマンドです...

ネタ元: こわくない、rpmbuild
https://qiita.com/hijili/items/ab2e162acbe05f86b7b0v

## Build

```sh
$ make
```

## Usage

```sh
$ ./shout yeah
yeaaaah!!!!!
```

### Config

```sh
$ cat <<EOF > hoge.conf
EXCLAMATION=10
CYCLES=10
EOF
$ ./shout -c hoge.conf yeah
yeaaaaaaaaaah!!!!!!!!!!
```
