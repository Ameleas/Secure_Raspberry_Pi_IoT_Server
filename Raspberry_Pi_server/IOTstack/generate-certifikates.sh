#!/bin/bash
# Skapa certifikat för mTLS

# Skapa katalog för certifikat
mkdir -p ~/IOTstack/mosquitto/certs
cd ~/IOTstack/mosquitto/certs

# 1. Skapa CA (Certificate Authority)
echo "Skapar CA..."
openssl genrsa -out ca.key 2048
openssl req -new -x509 -days 3650 -key ca.key -out ca.crt -subj "/C=SE/ST=Stockholm/L=Huddinge/O=HomeIoT/CN=IoT-CA"

# 2. Skapa server-certifikat för Mosquitto
echo "Skapar server-certifikat..."
openssl genrsa -out server.key 2048
openssl req -new -key server.key -out server.csr -subj "/C=SE/ST=Stockholm/L=Huddinge/O=HomeIoT/CN=ANVÄND-DIN-RPI-IPADRESS"

# Signera server-certifikatet med CA
openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days 3650

# 3. Skapa klient-certifikat för ESP32
echo "Skapar klient-certifikat..."
openssl genrsa -out esp32-client.key 2048
openssl req -new -key esp32-client.key -out esp32-client.csr -subj "/C=SE/ST=Stockholm/L=Huddinge/O=HomeIoT/CN=ESP32-Client"

# Signera klient-certifikatet med CA
openssl x509 -req -in esp32-client.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out esp32-client.crt -days 3650

# 4. Skapa klient-certifikat för Node-RED
echo "Skapar Node-RED klient-certifikat..."
openssl genrsa -out nodered-client.key 2048
openssl req -new -key nodered-client.key -out nodered-client.csr -subj "/C=SE/ST=Stockholm/L=Huddinge/O=HomeIoT/CN=NodeRED-Client"

# Signera Node-RED certifikatet med CA
openssl x509 -req -in nodered-client.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out nodered-client.crt -days 3650

# Rensa temporära filer
rm *.csr

# Sätt rätt rättigheter
chmod 644 *.crt
chmod 600 *.key