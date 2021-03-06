# Process Port Protection

[**简体中文**](README-zh_CN.md) | [English](README.md)

该软件使用 `iptables` 来保护一个端口

通过默认丢弃被保护端口的连接，开启另一个端口来授权，将被授权的客户端地址添加进白名单，白名单中客户端即可连接被保护的端口

## 用法

### 服务端

在使用本软件之前，你需要手动生成ssl证书，本软件提供了脚本： [gen.sh](cert/gen.sh)

```
PortProtection: 
        A program to protect port with iptables by authorizing client on another port
Usage: ./PortProtection 
        -c, --config <config file>
        -p, --port <listen port>
        -pp, --protect <protect port>
        -i, --interface <interface>
        -k, --key <key>
        -f, --file <key file>
        -cf, --cert-file <ssl cert file>
        -kf, --key-file <ssl key file>
        -t, --tcp
        -u, --udp
        -v, --verbose
Options explanation:
        -p      config file(params in config file will overwrite command line options)
        -p      listen port
        -pp     protect port
        -i      bind interface
        -k      authorization key
        -f      file with authorization key(optional)
        -cf     ssl cert file
        -kf     ssl key file
        -t      tcp protocol(default)
        -u      udp protocol
        -v      show verbose/debug messages
```

例：

```bash
PortProtection -p 12345 -pp 23456 -i eth0 -k 123 -cf ../cert/pp.crt -kf ../cert/pp.key -v # command line
PortProtection -c /etc/portpro/12345.conf # config file
```

### 客户端

该软件使用了TLS来加密，因此你需要使用 `openssl` 或 `curl` 来进行请求

提示： `time` 选项可以省略，默认为1


#### openssl:

```bash
openssl s_client -connect server_ip:port
```

然后输入 `key=xxx&time=xxx` 来授权


#### curl

```bash
curl -k https://server_ip:port/ -d "key=xxx&time=xxx" # POST
curl -k "https://server_ip:port/?key=xxx&time=xxx" # GET
```

#### 参数

- key: 授权的密码
- time: 持续时间，可以是数字，也可以是数字加单位，单位可以是 `h` (小时/缺省值), `d` (天), `m` (月份/按30天算), `y` (年/按365天算)
- 例： `key=123&time=2d` ， `key=test&time=2`

## 编译

```bash
mkdir build && cd build
cmake ..
make
```

## 开源协议

```license
 Copyright (C) 2018  PinkD

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
```
