#!/bin/bash
openssl genrsa -out ca.key
openssl req -x509 -key ca.key -out ca.crt
openssl genrsa -out pp.key 2048
openssl req -new -key pp.key -out pp.csr
openssl x509 -req -in pp.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out pp.crt -sha256
