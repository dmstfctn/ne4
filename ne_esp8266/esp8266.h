#include <ESP8266WiFi.h>

/*
  802.11 Frame Control on 2 bytes
*/

/* notes:
 *  uint8_t is a byte
 *  see: https://mrncciew.com/2014/09/27/cwap-mac-header-frame-control/
 *  for info about what's in the header's frame control field
 */
struct FrameControl {
  uint8_t version:2;
  uint8_t type:2; // 0: management, 1: control or 2: data
  uint8_t subtype:4;
  uint8_t toDS:1;
  uint8_t fromDS:1;
  uint8_t MF:1;
  uint8_t retry:1;
  uint8_t pwr:1;
  uint8_t more:1;
  uint8_t w:1;
  uint8_t o:1;
};

/*
  Following structs taken literally from Espressif SDK docs
*/
struct RxControl {
  signed rssi:8; // signal intensity of packet
  unsigned rate:4;
  unsigned is_group:1;
  unsigned:1;
  unsigned sig_mode:2; // 0:is 11n packet; 1:is not 11n packet;
  unsigned legacy_length:12; // if not 11n packet, shows length of packet.
  unsigned damatch0:1;
  unsigned damatch1:1;
  unsigned bssidmatch0:1;
  unsigned bssidmatch1:1;
  unsigned MCS:7; // if is 11n packet, shows the modulation and code used (range from 0 to 76)
  unsigned CWB:1; // if is 11n packet, shows if is HT40 packet or not
  unsigned HT_length:16;// if is 11n packet, shows length of packet.
  unsigned Smoothing:1;
  unsigned Not_Sounding:1;
  unsigned:1;
  unsigned Aggregation:1;
  unsigned STBC:2;
  unsigned FEC_CODING:1; // if is 11n packet, shows if is LDPC packet or not.
  unsigned SGI:1;
  unsigned rxend_state:8;
  unsigned ampdu_cnt:8;
  unsigned channel:4; //which channel this packet in.
  unsigned:12;
};

struct LenSeq{
  u16 len; // length of packet
  u16 seq; // serial number of packet, the high 12bits are serial number, low 14 bits are Fragment number (usually be 0)
  u8 addr3[6]; // the third address in packet
};

struct sniffer_buf{
  struct RxControl rx_ctrl;
  u8 buf[36]; // head of ieee80211 packet
  u16 cnt; // number count of packet
  struct LenSeq lenseq[1]; //length of packet
};

struct sniffer_buf2 {
  struct RxControl rx_ctrl;
  u8 buf[112];
  u16 cnt;
  u16 len; //length of packet
};


