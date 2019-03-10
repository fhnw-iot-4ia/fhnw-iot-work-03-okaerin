#!/usr/bin/env bash
read -p "host:" srv
#obtain public key in binary form
openssl s_client -showcerts -verify 5 -connect $srv:443 < /dev/null 2>/dev/null| openssl x509 -outform der > $srv.crt
#convert to c include
xxd -i < $srv.crt | sed -r '1 s/^/const unsigned char caCert[] PROGMEM = {/m' \
| sed -r '$ s/$/};/' > ${srv}_cert.h
#count entries
cnt=$[1+`cat ${srv}_cert.h|tr -cd ',' | wc -c`]
sed -ri "1i const unsigned int caCertLen=$cnt;" ${srv}_cert.h
