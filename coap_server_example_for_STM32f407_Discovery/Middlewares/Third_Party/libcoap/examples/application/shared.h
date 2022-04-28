//
// Created by patrik on 19.8.2021.
//

#ifndef EXAMPLE_SHARED_H
#define EXAMPLE_SHARED_H

typedef struct coap_address_t coap_address_t;

int resolve_address(const char *host, const char *port, coap_address_t *address);

void fill_keystore(coap_context_t *ctx);

coap_dtls_pki_t *setup_pki(coap_dtls_role_t role);

void set_certificate(char *full_file_path);

void set_certificate_authority(char *full_file_path);

void set_private_key(char *full_file_path);

#endif //EXAMPLE_SHARED_H
