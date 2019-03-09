#!/usr/bin/env bash
read -p "host: " srv
openssl s_client -showcerts -connect $srv:443 < /dev/null 2>/dev/null \
| openssl x509 -fingerprint -sha1 | sed  -r '/^SHA1/!d' | sed -r 's/^.*=//m' \
| tr ':' ',' | sed -r 's/[^,]{2}/0x\0/g' \
| sed -r 's/^/const uint8_t fingerprint[]={/' \
| sed -r 's/$/};/'
