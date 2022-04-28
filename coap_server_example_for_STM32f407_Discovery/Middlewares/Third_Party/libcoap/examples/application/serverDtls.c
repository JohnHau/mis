//
// Created by patrik on 19.8.2021.
//

#include "coap3/coap.h"
#include "shared.h"

static char *certificate = "";
static char *certificate_authority = "";
static char *private_key = "";

void post_example_handler(coap_resource_t *resource COAP_UNUSED,
                          coap_session_t *session,
                          const coap_pdu_t *request,
                          const coap_string_t *query COAP_UNUSED,
                          coap_pdu_t *response)
{
    size_t size;
    const uint8_t *data;
    size_t offset;
    size_t total;
    coap_binary_t *data_so_far;

    if (coap_get_data_large(request, &size, &data, &offset, &total) && size != total)
    {
        coap_cache_entry_t *cache_entry = coap_cache_get_by_pdu(session,
                                                                request,
                                                                COAP_CACHE_IS_SESSION_BASED);

        if (offset == 0)
        {
            if (!cache_entry)
            {
                cache_entry = coap_new_cache_entry(session, request,
                                                   COAP_CACHE_NOT_RECORD_PDU,
                                                   COAP_CACHE_IS_SESSION_BASED,
                                                   0);

            }
            else
            {
                data_so_far = coap_cache_get_app_data(cache_entry);
                if (data_so_far)
                {
                    coap_delete_binary(data_so_far);
                    data_so_far = NULL;
                }
                coap_cache_set_app_data(cache_entry, NULL, NULL);
            }
        }

        if (!cache_entry)
        {
            if (offset == 0)
            {
                coap_log(LOG_WARNING, "Unable to create a new cache entry\n");
            }
            else
            {
                coap_log(LOG_WARNING, "No cache entry available for the non-first BLOCK\n");
            }
            coap_pdu_set_code(response, COAP_RESPONSE_CODE_INTERNAL_ERROR);
            return;
        }

        if (size)
        {
            data_so_far = coap_cache_get_app_data(cache_entry);
            data_so_far = coap_block_build_body(data_so_far, size, data,
                                                offset, total);

            coap_cache_set_app_data(cache_entry, data_so_far, NULL);
        }

        if (offset + size == total)
        {
            data_so_far = coap_cache_get_app_data(cache_entry);
            coap_cache_set_app_data(cache_entry, NULL, NULL);
            coap_pdu_set_code(response, COAP_RESPONSE_CODE_CREATED);
        }
        else
        {
            coap_pdu_set_code(response, COAP_RESPONSE_CODE_CONTINUE);
            return;
        }
    }
    else
    {
        data_so_far = coap_new_binary(size);
        if (data_so_far)
        {
            memcpy(data_so_far->s, data, size);
        }

        coap_pdu_set_code(response, COAP_RESPONSE_CODE_CREATED);
    }
}

int main()
{
    coap_set_log_level(LOG_DEBUG);
    coap_context_t *ctx = NULL;
    coap_address_t dst;
    int result = EXIT_FAILURE;
    uint16_t cache_ignore_options[] = { COAP_OPTION_BLOCK1,
                                        COAP_OPTION_BLOCK2,
                                        COAP_OPTION_MAXAGE,
                                        COAP_OPTION_IF_NONE_MATCH };

    coap_startup();

    if (resolve_address("localhost", "5684", &dst) < 0)
    {
        coap_log(LOG_CRIT, "failed to resolve address\n");
        goto end;
    }

    ctx = coap_new_context(NULL);
    coap_context_set_block_mode(ctx, COAP_BLOCK_USE_LIBCOAP);
    coap_cache_ignore_options(ctx, cache_ignore_options,
                              sizeof(cache_ignore_options)/sizeof(cache_ignore_options[0]));

    set_certificate(certificate);
    set_certificate_authority(certificate_authority);
    set_private_key(private_key);
    fill_keystore(ctx);

    coap_endpoint_t *endpoint = coap_new_endpoint(ctx, &dst, COAP_PROTO_DTLS);
    if (!ctx || !endpoint)
    {
        coap_log(LOG_EMERG, "cannot initialize context\n");
        goto end;
    }

    coap_resource_t *resource = coap_resource_init(coap_make_str_const("example"), 0);
    coap_register_handler(resource, COAP_REQUEST_POST, post_example_handler);

    coap_add_resource(ctx, resource);

    while (1)
    {
        coap_io_process(ctx, COAP_IO_WAIT);
    }

    result = EXIT_SUCCESS;
    end:

    coap_free_context(ctx);
    coap_cleanup();

    return result;
}

