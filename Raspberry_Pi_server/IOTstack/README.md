# Raspberry Pi IoT Server

Detta projekt visar hur du förvandlar en Raspberry Pi 5 (RPI) till en komplett IOT server.
Servern tar emot data från t.ex. en ESP32, bearbetar via Nodered, lagrar i InfluxDB och visualiserar med Grafana.  
Projektet bygger på guiden [“Easy Raspberry Pi IoT Server”](https://learnembeddedsystems.co.uk/easy-raspberry-pi-iot-server) av *Learn Embedded Systems*.
För att öka säkerheten har jag även lagt till certifikathantering (Open SSL) med mTLS samt använder SSH via Netbird.io.


# Översikt

  ESP32 -->|MQTT| Mosquitto
  Mosquitto --> NodeRED
  NodeRED --> InfluxDB
  InfluxDB --> Grafana
  Portainer -->|UI| DockerStack


# Kom igång

Installera IOT stack på din RPI: 
"curl -fsSL https://raw.githubusercontent.com/SensorsIot/IOTstack/master/install.sh | bash"
och starta därefter om den. IOTstack är ett enkelt sätt att hantera Docker-containrar på RPI. 
I terminalen navigera till din IOTstack-map och starta programmet med "./menu.sh". Här väljer du dina fem containrar (se # Översikt). När du gjort dina val och bekräftat med enter skapas automatiskt docker-compose.yml och dina containrar laddas ned. Notera att för att skapa mTLS (mutual Transport Layer Security) behövs några rader i docker-compose.yml, mosquitto.conf samt configurationen i Nodered justeras i efterhand. 

# Certifikat

mTLS ökar säkerheten avsevärt genom "three way handshake" och certifikat verifiering. Certifikaten i detta projekt är skapade genom OpenSSL. För mer info, se mTLS.txt



