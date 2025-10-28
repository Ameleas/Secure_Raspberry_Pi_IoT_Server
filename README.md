# Secure Raspberry Pi IoT Server

A secure IoT server built for Raspberry Pi using MQTT over TLS/SSL, designed to ensure encrypted communication between sensors (e.g., ESP32 with PIR) and a central broker.

## 🔒 Features
- Secure MQTT connection (port 8883)
- Mutual TLS authentication (mTLS)
- JSON-based sensor data (motion detection)
- Compatible with ESP32, ESP8266, and Raspberry Pi
- Local MQTT broker support (e.g., Mosquitto)

## ⚙️ Setup Instructions

### 1. Clone the repository
```bash
git clone https://github.com/Ameleas/Secure_Raspberry_Pi_IoT_Server.git
cd Secure_Raspberry_Pi_IoT_Server
2. Generate SSL certificates
You can use OpenSSL to generate CA, server, and client certificates:

bash
Copy code
./scripts/generate_certs.sh
Make sure to update your ESP32 sketch with:

cpp
Copy code
espClient.setCACert(ca_cert);
espClient.setCertificate(client_cert);
espClient.setPrivateKey(client_key);
3. Configure Mosquitto
Edit /etc/mosquitto/mosquitto.conf:

swift
Copy code
listener 8883
cafile /etc/mosquitto/certs/ca.crt
certfile /etc/mosquitto/certs/server.crt
keyfile /etc/mosquitto/certs/server.key
require_certificate true
use_identity_as_username true
Restart Mosquitto:

bash
Copy code
sudo systemctl restart mosquitto
4. Flash ESP32
Upload the provided sketch in the ESP32_Client folder using the Arduino IDE or PlatformIO.

🧠 Example JSON Payload
json
Copy code
{
  "motion": true
}
📄 Documentation
Additional project documentation can be found in:

Documentation.docx (Word format)

/docs/ folder (if available)

🧑‍💻 Author
Amelea
GitHub: @Ameleas

🛡️ License
This project is licensed under the MIT License — see the LICENSE file for details.
git add README.md
git commit -m "Add README.md"
git push origin main
