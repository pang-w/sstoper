#include <stdint.h>
#include <sys/time.h>

/* System properties */
#define __UNSIGNED_LONG_LONG_MAX__ (~0LLU)
   
/* SSTP Properties */
#define SSTP_VERSION 0x10
#define SSTP_MIN_LEN 4 
#define SSTP_MAX_ATTR 256
#define SSTP_NEGOCIATION_TIMER 5
#define SSTP_MAX_BUFFER_SIZE 1024


/* SSTP Packet Type */
enum packet_types 
  {
    SSTP_DATA_PACKET = 0x00,
    SSTP_CONTROL_PACKET = 0x01
  };


/* SSTP Protocol Type */
enum sstp_encapsulated_protocol_types 
  {
    SSTP_ENCAPSULATED_PROTOCOL_PPP = 0x0001
  };


/* SSTP Status Message */
enum control_messages_types
  {
    SSTP_MSG_CALL_CONNECT_REQUEST = 0x0001,
    SSTP_MSG_CALL_CONNECT_ACK = 0x0002,
    SSTP_MSG_CALL_CONNECT_NAK = 0x0003,
    SSTP_MSG_CALL_CONNECTED = 0x0004,
    SSTP_MSG_CALL_ABORT = 0x0005,
    SSTP_MSG_CALL_DISCONNECT = 0x0006,
    SSTP_MSG_CALL_DISCONNECT_ACK = 0x0007,
    SSTP_MSG_ECHO_REQUEST = 0x0008,
    SSTP_MSG_ECHO_RESPONSE = 0x0009
  };
static char* control_messages_types_str[] =
  {"",
   "SSTP_MSG_CALL_CONNECT_REQUEST",
   "SSTP_MSG_CALL_CONNECT_ACK",
   "SSTP_MSG_CALL_CONNECT_NAK",
   "SSTP_MSG_CALL_CONNECTED",
   "SSTP_MSG_CALL_ABORT",
   "SSTP_MSG_CALL_DISCONNECT",
   "SSTP_MSG_CALL_DISCONNECT_ACK",
   "SSTP_MSG_ECHO_REQUEST",
   "SSTP_MSG_ECHO_RESPONSE",
  };


/* SSTP Attribute Message Type */
enum attr_types 
  {
    SSTP_ATTRIB_NO_ERROR = 0x00,
    SSTP_ATTRIB_ENCAPSULATED_PROTOCOL_ID = 0x01,
    SSTP_ATTRIB_STATUS_INFO = 0x02,
    SSTP_ATTRIB_CRYPTO_BINDING = 0x03,
    SSTP_ATTRIB_CRYPTO_BINDING_REQ = 0x04
  };
static char* attr_types_str[] =
  {
    "SSTP_ATTRIB_NO_ERROR", 
    "SSTP_ATTRIB_ENCAPSULATED_PROTOCOL_ID",
    "SSTP_ATTRIB_STATUS_INFO",
    "SSTP_ATTRIB_CRYPTO_BINDING",
    "SSTP_ATTRIB_CRYPTO_BINDING_REQ",
  };


/* Crypto Binding Request Attribute */
enum crypto_req_attrs 
  {
    CERT_HASH_PROTOCOL_SHA1 = 0x01,
    CERT_HASH_PROTOCOL_SHA256 = 0x02
  };

static char* crypto_req_attrs_str[]=
  {
    "CERT_HASH_PROTOCOL_SHA1",
    "CERT_HASH_PROTOCOL_SHA256"
  };


/* Status Info Attribute */
enum attr_status 
  {
    ATTRIB_STATUS_NO_ERROR = 0x00000000,
    ATTRIB_STATUS_DUPLICATE_ATTRIBUTE = 0x00000001,
    ATTRIB_STATUS_UNRECOGNIZED_ATTRIBUTE = 0x00000002,
    ATTRIB_STATUS_INVALID_ATTRIB_VALUE_LENGTH = 0x00000003,
    ATTRIB_STATUS_VALUE_NOT_SUPPORTED = 0x00000004,
    ATTRIB_STATUS_UNACCEPTED_FRAME_RECEIVED = 0x00000005,
    ATTRIB_STATUS_RETRY_COUNT_EXCEEDED = 0x00000006,
    ATTRIB_STATUS_INVALID_FRAME_RECEIVED = 0x00000007,
    ATTRIB_STATUS_NEGOTIATION_TIMEOUT = 0x00000008,
    ATTRIB_STATUS_ATTRIB_NOT_SUPPORTED_IN_MSG = 0x00000009,
    ATTRIB_STATUS_REQUIRED_ATTRIBUTE_MISSING = 0x0000000a,
    ATTRIB_STATUS_STATUS_INFO_NOT_SUPPORTED_IN_MSG = 0x0000000b
  };

static char* attrib_status_str[] =
  {
    "ATTRIB_STATUS_NO_ERROR",
    "ATTRIB_STATUS_DUPLICATE_ATTRIBUTE",
    "ATTRIB_STATUS_UNRECOGNIZED_ATTRIBUTE",
    "ATTRIB_STATUS_INVALID_ATTRIB_VALUE_LENGTH",
    "ATTRIB_STATUS_VALUE_NOT_SUPPORTED",
    "ATTRIB_STATUS_UNACCEPTED_FRAME_RECEIVED",
    "ATTRIB_STATUS_RETRY_COUNT_EXCEEDED",
    "ATTRIB_STATUS_INVALID_FRAME_RECEIVED",
    "ATTRIB_STATUS_NEGOTIATION_TIMEOUT",
    "ATTRIB_STATUS_ATTRIB_NOT_SUPPORTED_IN_MSG",
    "ATTRIB_STATUS_REQUIRED_ATTRIBUTE_MISSING",
    "ATTRIB_STATUS_STATUS_INFO_NOT_SUPPORTED_IN_MSG",
  };


/* sstp client status */
enum client_status
  {
    CLIENT_CALL_DISCONNECTED = 0,
    CLIENT_CONNECT_REQUEST_SENT = 1,
    CLIENT_CONNECT_ACK_RECEIVED = 2,
    CLIENT_CALL_CONNECTED = 3
  };

static char* client_status_str[] =
  {
    "CLIENT_CALL_DISCONNECTED",
    "CLIENT_CONNECT_REQUEST_SENT",
    "CLIENT_CONNECT_ACK_RECEIVED",
    "CLIENT_CALL_CONNECTED",
  };


/* data structures */
typedef struct __sstp_header
{
  uint8_t version;
  uint8_t reserved;
  uint16_t length;
} sstp_header_t; 

typedef struct __sstp_control_header 
{
  uint16_t message_type;
  uint16_t num_attributes;
} sstp_control_header_t; 

typedef struct __sstp_attribute_header 
{
  uint8_t reserved;
  uint8_t attribute_id;
  uint16_t packet_length;
} sstp_attribute_header_t; 

/* attribute structures */
typedef struct __sstp_attribute
{
  uint16_t length;
  void *data;
} sstp_attribute_t;

/* uint24_t n'existe pas */
/* uint24_t reserved1; */
#ifndef uint24_t
typedef struct _uint24_t
{
  uint8_t byte[3];
} uint24_t;
#endif

typedef struct __sstp_attribute_crypto_bind_req
{
  uint32_t hash_bitmask; /* 0-er les 3 octets de poids fort */
  uint32_t nonce[4];
} sstp_attribute_crypto_bind_req_t;

typedef struct __sstp_attribute_status_info
{
  uint32_t attrib_id; /* 0-er les 3 octets de poids fort */
  uint32_t status;
} sstp_attribute_status_info_t;

typedef struct __sstp_attribute_crypto_bind
{
  uint32_t hash_bitmask; /* 0-er les 3 octets de poids fort */
  uint32_t nonce[8];
  uint32_t certhash[8];
  uint32_t cmac[8];
} sstp_attribute_crypto_bind_t;


/* sstp client context */
typedef struct __sstp_context 
{
  unsigned char state;
  unsigned char retry;
  pid_t pppd_pid;
  struct timeval negociation_timer;
  struct timeval hello_timer;
  uint8_t hash_algorithm;
  uint32_t nonce[8];
  uint32_t certhash[8];
  uint32_t cmac[8];
} sstp_context_t;

static sstp_context_t* ctx;


/* functions declarations  */
int https_session_negociation();

void initialize_sstp();
void sstp_loop();
void sstp_send(void*, size_t);
void send_sstp_packet(uint8_t, void*, size_t);
void send_sstp_data_packet(void*, size_t);
void send_sstp_control_packet(uint16_t, void*, uint16_t, size_t);

void* create_attribute(uint8_t, void*, size_t);

int sstp_decode(void*, ssize_t);
int sstp_decode_attributes(uint16_t, void*, ssize_t);

int is_valid_header(void*, ssize_t);
int is_control_packet(sstp_header_t*);

int crypto_set_certhash();
int crypto_set_binding(void*);
int attribute_status_info(void*,uint16_t);