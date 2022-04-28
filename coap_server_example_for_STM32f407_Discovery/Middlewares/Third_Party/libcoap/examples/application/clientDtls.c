//
// Created by patrik on 19.8.2021.
//


#include "coap3/coap.h"
#include "shared.h"

#define BLOCK_SIZE 1024
#define NUMBER_OF_BLOCKS 10
#define BUFFER_SIZE (NUMBER_OF_BLOCKS * BLOCK_SIZE)

static char *certificate = ""; //zheng shu
static char *certificate_authority = "";
static char *private_key = ""; //mi yao

static coap_response_t response_handler(coap_session_t *session COAP_UNUSED,
                                        const coap_pdu_t *sent COAP_UNUSED,
                                        const coap_pdu_t *received,
                                        const coap_mid_t id COAP_UNUSED)
{

    coap_show_pdu(LOG_WARNING, received);
    return COAP_RESPONSE_OK;
}

int main(void)
{
    coap_set_log_level(LOG_WARNING);
    coap_context_t *ctx = NULL;
    coap_session_t *session = NULL;
    coap_address_t server_address;
    int result = EXIT_FAILURE;

    coap_startup();

    if (resolve_address("localhost", "5684", &server_address) < 0)
    {
        coap_log(LOG_CRIT, "failed to resolve server_address\n");
        goto end;
    }

    ctx = coap_new_context(NULL);
    coap_context_set_block_mode(ctx, COAP_BLOCK_USE_LIBCOAP);

    set_certificate(certificate);
    set_certificate_authority(certificate_authority);
    set_private_key(private_key);

    coap_dtls_pki_t *dtls_pki = setup_pki(COAP_DTLS_ROLE_CLIENT);
    session = coap_new_client_session_pki(ctx, NULL, &server_address, COAP_PROTO_DTLS, dtls_pki);
    if (!ctx || !session)
    {
        coap_log(LOG_EMERG, "cannot create client session\n");
        goto end;
    }

    coap_register_response_handler(ctx, response_handler);

    coap_pdu_t *pdu = coap_new_pdu(COAP_MESSAGE_CON, COAP_REQUEST_CODE_POST, session);
    if (!pdu)
    {
        coap_log(LOG_EMERG, "cannot create PDU\n");
        return -1;
    }

    coap_add_option(pdu, COAP_OPTION_URI_PATH, 7, (const uint8_t *) "example");

    uint8_t buffer[BUFFER_SIZE];
    memset(&buffer, 0, BUFFER_SIZE);

    coap_add_data_large_request(session, pdu, BUFFER_SIZE, buffer, NULL, NULL);

    coap_show_pdu(LOG_INFO, pdu);
    coap_send(session, pdu);

    while (1)
    {
        coap_io_process(ctx, COAP_IO_WAIT);
    }

    result = EXIT_SUCCESS;

    end:
    coap_session_release(session);
    coap_free_context(ctx);
    coap_cleanup();

    return result;
}