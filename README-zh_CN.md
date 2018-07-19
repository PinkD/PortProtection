# Process Port Protection

[**简体中文**](README-zh_CN.md) | [English](README.md)

该软件使用 `iptables` 来保护一个端口

通过默认丢弃被保护端口的连接，开启另一个端口来授权，将被授权的客户端地址添加进白名单，白名单中客户端即可连接被保护的端口

## 用法

### 服务端

在使用本软件之前，你需要手动生成ssl证书，本软件提供了脚本： [gen.sh](cert/gen.sh)

```
Usage: ./PortProtection 
        -p, --port <listen port>
        -pp, --protect <protect port>
        -i, --interface <interface>
        -k, --key <key>
        -f, --file <key file>
        -cf, --cert-file <ssl cert file>
        -kf, --key-file <ssl key file>
        -v, --verbose
Options explanation:
        -p      listen port
        -pp     protect port
        -i      bind interface
        -k      authorization key
        -f      file with authorization key(optional)
        -cf     ssl cert file
        -kf     ssl key file
        -v      show verbose/debug messages
```

### 客户端

该软件使用了TLS来加密，因此你需要使用 `openssl` 或 `curl` 来进行请求

提示： `time` 选项可以省略，默认为1

#### openssl:

`openssl s_client -connect server_ip:port`

然后输入 `key=xxx&time=xxx` 来授权


#### curl

`curl -k https://server_ip:port/ -d "key=xxx&time=xxx"`

## 编译

```bash
mkdir build && cd build
cmake ..
make
```
