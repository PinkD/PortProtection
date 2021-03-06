# Process Port Protection

[简体中文](README-zh_CN.md) | [**English**](README.md)

Protect a port using `iptables`

It drops the connection to the protected port by default and starts a daemon to listen on a port to authorize client and add client to an access list so that client can access to the protected port

## Usage

### Server

Before you use it, you should generate your own ssl cert. Use [gen.sh](cert/gen.sh) to do that

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

Example:

```bash
PortProtection -p 12345 -pp 23456 -i eth0 -k 123 -cf ../cert/pp.crt -kf ../cert/pp.key -v # command line
PortProtection -c /etc/portpro/12345.conf # config file
```

### Client

TLS was used in the project, so you can use openssl or curl to request

NOTE: `time` can be omitted, default value is 1

#### openssl:

```bash
openssl s_client -connect server_ip:port
```

then you input `key=xxx&time=xxx` to authorize.

#### curl

```bash
curl -k https://server_ip:port/ -d "key=xxx&time=xxx" # POST
curl -k "https://server_ip:port/?key=xxx&time=xxx" # GET
```

#### parameter explanation

- key: the key to authorize
- time: can be number or number+unit, unit can be one of `h` (hour/default), `d` (day), `m` (month/30 days), `y` (year/365 days)
- e.g. : `key=123&time=2d` , `key=test&time=2`


## Build

```bash
mkdir build && cd build
cmake ..
make
```

## License

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
