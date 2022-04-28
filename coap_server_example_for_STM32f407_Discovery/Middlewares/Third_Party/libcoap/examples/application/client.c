/* minimal CoAP client
 *
 * Copyright (C) 2018-2021 Olaf Bergmann <bergmann@tzi.org>
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#include "sys/socket.h"
#include "lwip/netdb.h"
#include "common.h"

//#include "cmsis_os.h"
#include "main.h"
////////////////////
static coap_tid_t
clear_obs(coap_context_t *ctx, coap_session_t *session);
/////////////////////////////////////////////////////
int coap_rec;
int coap_obs_time;
#define no_of_coap_retries 2
int retries ;

#define COAP_DEFAULT_TIME_SEC 6
#define COAP_DEFAULT_DEMO_URI "coap://coap.thingsboard.cloud/api/v1/abkn6xwUk3m2GgRngCkq/telemetry" //"coap://coap.me/hello"//
//"coap://coap.thingsboard.cloud/api/v1/abkn6xwUk3m2GgRngCkq/attributes?clientKeys=client_attr"
//coap://coap.thingsboard.cloud/api/v1/abkn6xwUk3m2GgRngCkq/attributes
//"coap://coap.me/path/sub1"
//""coap://coap.thingsboard.cloud/api/v1/abkn6xwUk3m2GgRngCkq/telemetry"

static int resp_wait = 1;
static coap_optlist_t *optlist = NULL;
static int wait_ms;

///////////////////////////////////////////////////////////////////////
/***************************************************
 handle payload -e in command line  3 functions
***************************************************/
coap_string_t payload = { 0, NULL };
#define hexchar_to_dec(c) ((c) & 0x40 ? ((c) & 0x0F) + 9 : ((c) & 0x0F))
static void
decode_segment(const uint8_t *seg, size_t length, unsigned char *buf) {

  while (length--) {

    if (*seg == '%') {
      *buf = (hexchar_to_dec(seg[1]) << 4) + hexchar_to_dec(seg[2]);

      seg += 2; length -= 2;
    } else {
      *buf = *seg;
    }

    ++buf; ++seg;
  }
}


static int
check_segment(const uint8_t *s, size_t length) {

  size_t n = 0;

  while (length) {
    if (*s == '%') {
      if (length < 2 || !(isxdigit(s[1]) && isxdigit(s[2])))
        return -1;

      s += 2;
      length -= 2;
    }

    ++s; ++n; --length;
  }

  return n;
}

static int
cmdline_input(char *text, coap_string_t *buf) {
  int len;
  len = check_segment((unsigned char *)text, strlen(text));

  if (len < 0)
    return 0;

  buf->s = (unsigned char *)coap_malloc(len);
  if (!buf->s)
    return 0;

  buf->length = len;
  decode_segment((unsigned char *)text, strlen(text), buf->s);
  return 1;
}


/****************************************************/

static void message_handler(coap_context_t *ctx, coap_session_t *session,
                            coap_pdu_t *sent, coap_pdu_t *received,
                            const coap_tid_t id)
{
    unsigned char *data = NULL;
    size_t data_len;
    coap_pdu_t *pdu = NULL;
    coap_opt_t *block_opt;
    coap_opt_iterator_t opt_iter;
    unsigned char buf[4];
    coap_optlist_t *option;
    coap_tid_t tid;

    if (COAP_RESPONSE_CLASS(received->code) == 2) {
        /* Need to see if blocked response */
        block_opt = coap_check_option(received, COAP_OPTION_BLOCK2, &opt_iter);
        if (block_opt) {
            uint16_t blktype = opt_iter.type;

            if (coap_opt_block_num(block_opt) == 0) {
                //printf("Received:\n");
            }
            if (coap_get_data(received, &data_len, &data)) {
                //printf("%.*s", (int)data_len, data);
            }
            if (COAP_OPT_BLOCK_MORE(block_opt)) {
                /* more bit is set */

                /* create pdu with request for next block */
                pdu = coap_new_pdu(session);
                if (!pdu) {
                    //ESP_LOGE(TAG, "coap_new_pdu() failed");
                    goto clean_up;
                }
                pdu->type = COAP_MESSAGE_CON;
                pdu->tid = coap_new_message_id(session);
                pdu->code = COAP_REQUEST_GET;

                /* add URI components from optlist */
                for (option = optlist; option; option = option->next ) {
                    switch (option->number) {
                    case COAP_OPTION_URI_HOST :
                    case COAP_OPTION_URI_PORT :
                    case COAP_OPTION_URI_PATH :
                    case COAP_OPTION_URI_QUERY :
                        coap_add_option(pdu, option->number, option->length,
                                        option->data);
                        break;
                    default:
                        ;     /* skip other options */
                    }
                }

                /* finally add updated block option from response, clear M bit */
                /* blocknr = (blocknr & 0xfffffff7) + 0x10; */
                coap_add_option(pdu,
                                blktype,
                                coap_encode_var_safe(buf, sizeof(buf),
                                                     ((coap_opt_block_num(block_opt) + 1) << 4) |
                                                     COAP_OPT_BLOCK_SZX(block_opt)), buf);

                tid = coap_send(session, pdu);

                if (tid != COAP_INVALID_TID) {
                    resp_wait = 1;
                    wait_ms = COAP_DEFAULT_TIME_SEC * 1000;
                    return;
                }
            }
            //printf("\n");
        } else {
            if (coap_get_data(received, &data_len, &data)) {
                printf("Received: %.*s\n", (int)data_len, data);
            	//BSP_LED_On(LED2);
            	//BSP_LED_Toggle(LED2);
            	coap_rec=1;
            }
        }
        BSP_LED_Toggle(LED2);
        coap_rec=1;
    }
clean_up:
    resp_wait = 0;
}



//void coap_client(void const * argument)
void coap_client()
{
    struct hostent *hp;
    coap_address_t    dst_addr;
    static coap_uri_t uri;
    const char *server_uri = COAP_DEFAULT_DEMO_URI;
    char *phostname = NULL;

    coap_set_log_level(LOG_EMERG);
    retries=no_of_coap_retries;
    coap_rec=0;
    while (1) {
#define BUFSIZE 45
        unsigned char _buf[BUFSIZE];
        unsigned char *buf;
        size_t buflen;
        int res;
        coap_context_t *ctx = NULL;
        coap_session_t *session = NULL;
        coap_pdu_t *request = NULL;

        optlist = NULL;
        if (coap_split_uri((const uint8_t *)server_uri, strlen(server_uri), &uri) == -1) {
            //ESP_LOGE(TAG, "CoAP server uri error");
            break;
        }


        phostname = (char *)calloc(1, uri.host.length + 1);
        if (phostname == NULL) {
            //ESP_LOGE(TAG, "calloc failed");
            break;
        }

        memcpy(phostname, uri.host.s, uri.host.length);
        hp = gethostbyname(phostname);
        free(phostname);

        if (hp == NULL) {
            //ESP_LOGE(TAG, "DNS lookup failed");
            //vTaskDelay(1000 / portTICK_PERIOD_MS);
            osDelay(1000);
            free(phostname);
            continue;
        }
        char tmpbuf[INET6_ADDRSTRLEN];
        coap_address_init(&dst_addr);
        switch (hp->h_addrtype) {
            case AF_INET:
                dst_addr.addr.sin.sin_family      = AF_INET;
                dst_addr.addr.sin.sin_port        = htons(uri.port);
                memcpy(&dst_addr.addr.sin.sin_addr, hp->h_addr, sizeof(dst_addr.addr.sin.sin_addr));
                inet_ntop(AF_INET, &dst_addr.addr.sin.sin_addr, tmpbuf, sizeof(tmpbuf));
                //ESP_LOGI(TAG, "DNS lookup succeeded. IP=%s", tmpbuf);
                break;
            case AF_INET6:
                dst_addr.addr.sin6.sin6_family      = AF_INET6;
                dst_addr.addr.sin6.sin6_port        = htons(uri.port);
                memcpy(&dst_addr.addr.sin6.sin6_addr, hp->h_addr, sizeof(dst_addr.addr.sin6.sin6_addr));
                inet_ntop(AF_INET6, &dst_addr.addr.sin6.sin6_addr, tmpbuf, sizeof(tmpbuf));
                //ESP_LOGI(TAG, "DNS lookup succeeded. IP=%s", tmpbuf);
                break;
            default:
                //ESP_LOGE(TAG, "DNS lookup response failed");
                goto clean_up;
        }

        if (uri.path.length) {
            buflen = BUFSIZE;
            buf = _buf;
            res = coap_split_path(uri.path.s, uri.path.length, buf, &buflen);

            while (res--) {
                coap_insert_optlist(&optlist,
                                    coap_new_optlist(COAP_OPTION_URI_PATH,
                                                     coap_opt_length(buf),
                                                     coap_opt_value(buf)));

                buf += coap_opt_size(buf);
            }
        }

        if (uri.query.length) {
            buflen = BUFSIZE;
            buf = _buf;
            res = coap_split_query(uri.query.s, uri.query.length, buf, &buflen);

            while (res--) {
                coap_insert_optlist(&optlist,
                                    coap_new_optlist(COAP_OPTION_URI_QUERY,
                                                     coap_opt_length(buf),
                                                     coap_opt_value(buf)));

                buf += coap_opt_size(buf);
            }
        }
        //////////////////////// observe option add
//        if (!coap_insert_optlist(&optlist,
//                                 coap_new_optlist(COAP_OPTION_OBSERVE,
//                                             COAP_OBSERVE_ESTABLISH, NULL)))
//        {    goto clean_up;}

    ///////////////////////////////////

        ctx = coap_new_context(NULL);
        if (!ctx) {
            //ESP_LOGE(TAG, "coap_new_context() failed");
            goto clean_up;
        }

		session = coap_new_client_session(ctx, NULL, &dst_addr,COAP_PROTO_UDP);

        if (!session) {
            //ESP_LOGE(TAG, "coap_new_client_session() failed");
            goto clean_up;
        }

        coap_register_response_handler(ctx, message_handler);
     while(!coap_rec && retries>0){
        request = coap_new_pdu(session);
        if (!request) {
            //ESP_LOGE(TAG, "coap_new_pdu() failed");
            goto clean_up;
        }
        request->type = COAP_MESSAGE_CON;
        request->tid = coap_new_message_id(session);
        //request->code = COAP_REQUEST_GET;
        request->code =COAP_REQUEST_POST;
        coap_add_optlist_pdu(request, &optlist);

        // for posting data if there is payload
        //if (!cmdline_input("{\"client_attr\": 333}", &payload))
        if (!cmdline_input("{\"ccid\":\"324354545434545\",\"ip\":\"192.168.1.23\",\"imsi\":\"1223435443543534\",\"mmc\":206,\"mnc\":02,\"imei\":\"14333424334343\",\"manu\":\"quectel\",\"fmv\":\"bg96.23.04.2021.6\",\"rssi\":32,\"ber\":323,\"bat\":32,\"lat\":32,\"long\":232,\"ninfo\":\"lte.m1\",\"band\":20}", &payload))
        {
          payload.length = 0;
        }
        if (payload.length)
        {
          coap_add_data(request, payload.length, payload.s);
        }

        ////////////////////////

        resp_wait = 1;

        coap_send(session, request);

        wait_ms = COAP_DEFAULT_TIME_SEC * 1000;

        while (resp_wait) {
//        	int result = coap_run_once(ctx,1000);
//        	coap_obs_time++;
//        	if(coap_obs_time>30)
//        	{
//        		coap_obs_time=0;
//        		clear_obs(ctx,session);
//        		break;
//        	}

            int result = coap_run_once(ctx, wait_ms > 1000 ? 1000 : wait_ms);
            if (result >= 0) {
                if (result >= wait_ms) {
                    //ESP_LOGE(TAG, "select timeout");
                    break;
                } else {
                    wait_ms -= result;
                }
            }

        }
        retries--;
        osDelay(1000);
      } //  while(!coap_rec)
clean_up:
        if (optlist) {
            coap_delete_optlist(optlist);
            optlist = NULL;
        }
        if (session) {
            coap_session_release(session);
        }
        if (ctx) {
            coap_free_context(ctx);
        }
        coap_cleanup();
        /*
         * change the following line to something like sleep(2)
         * if you want the request to continually be sent
         */
        break;
    }

    //vTaskDelete(NULL);
    //osThreadTerminate(NULL);
}




////////////////////////////////////////////////////////////////////////////////

static coap_tid_t
clear_obs(coap_context_t *ctx, coap_session_t *session) {
  coap_pdu_t *pdu;
  coap_optlist_t *option;
  coap_tid_t tid = COAP_INVALID_TID;
  unsigned char buf[2];
  (void)ctx;

  /* create bare PDU w/o any option  */
  pdu = coap_pdu_init(COAP_MESSAGE_CON,
                      COAP_REQUEST_GET,
                      coap_new_message_id(session),
                      coap_session_max_pdu_size(session));

  if (!pdu) {
    return tid;
  }

//  if (!coap_add_token(pdu, the_token.length, the_token.s)) {
//    coap_log(LOG_CRIT, "cannot add token\n");
//    goto error;
//  }

  for (option = optlist; option; option = option->next ) {
    if (option->number == COAP_OPTION_URI_HOST) {
      if (!coap_add_option(pdu, option->number, option->length,
                           option->data)) {
        goto error;
      }
      break;
    }
  }

  if (!coap_add_option(pdu,
      COAP_OPTION_OBSERVE,
      coap_encode_var_safe(buf, sizeof(buf), COAP_OBSERVE_CANCEL),
      buf)) {
    //coap_log(LOG_CRIT, "cannot add option Observe: %u\n", COAP_OBSERVE_CANCEL);
    goto error;
  }

  for (option = optlist; option; option = option->next ) {
    switch (option->number) {
    case COAP_OPTION_URI_PORT :
    case COAP_OPTION_URI_PATH :
    case COAP_OPTION_URI_QUERY :
      if (!coap_add_option(pdu, option->number, option->length,
                           option->data)) {
        goto error;
      }
      break;
      default:
      ;
    }
  }

//  if (flags & FLAGS_BLOCK) {
//    block.num = 0;
//    block.m = 0;
//    coap_add_option(pdu,
//      COAP_OPTION_BLOCK2,
//      coap_encode_var_safe(buf, sizeof(buf), (block.num << 4 | block.m << 3 | block.szx)),
//      buf);
//  }

//  if (coap_get_log_level() < LOG_DEBUG)
//    coap_show_pdu(LOG_INFO, pdu);


  tid = coap_send(session, pdu);

  if (tid == COAP_INVALID_TID)
    //coap_log(LOG_DEBUG, "clear_obs: error sending new request\n");

  return tid;
 error:

  coap_delete_pdu(pdu);
  return tid;
}



////////////////////


