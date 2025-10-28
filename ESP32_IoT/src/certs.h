#ifndef CERTS_H
#define CERTS_H

// CA certifikat (ca.crt)
const char* ca_cert = R"EOF(
-----BEGIN CERTIFICATE-----
[KLISTRA IN INNEHALLET FRAN ca.crt HAR]
-----END CERTIFICATE-----
)EOF";

// Klient-certifikat (esp32-client.crt)
const char* client_cert = R"EOF(
-----BEGIN CERTIFICATE-----
[KLISTRA IN INNEHALLET FRAN esp32-client.crt HAR]
-----END CERTIFICATE-----
)EOF";

// Klient-nyckel (esp32-client.key)
const char* client_key = R"EOF(
-----BEGIN PRIVATE KEY-----
[KLISTRA IN INNEHALLET FRAN esp32-client.key HAR]
-----END PRIVATE KEY-----
)EOF";



#endif // CERTS_H/