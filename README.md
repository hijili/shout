# shout

ネタのためのクソコマンドです...

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
