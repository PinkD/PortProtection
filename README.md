# Process Port Protection

[简体中文](README-zh_CN.md) | [**English**](README.md)

Protect a port using `iptables`

It drops the connection to the protected port by default and starts a daemon to listen on a port to authorize client and add client to an access list so that client can access to the protected port

## Usage

### Server

Before you use it, you should generate your own ssl cert. Use [gen.sh](certs/gen.sh) to do that

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

### Client

TLS was used in the project, so you can use openssl or curl to request

NOTE: `time` can be omitted, default value is 1

#### openssl:

`openssl s_client -connect server_ip:port`

then you input `key=xxx&time=xxx` to authorize.

#### curl

`curl -k https://server_ip:port/ -d "key=xxx&time=xxx"`

## Build

```bash
mkdir build && cd build
cmake ..
make
```
