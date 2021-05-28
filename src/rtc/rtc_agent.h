#ifndef RTC_RTC_AGENT_H_
#define RTC_RTC_AGENT_H_

#include <pthread.h>
#include <string>

#include "MQTTClient.h"

extern "C"
{
#include "pear.h"
}


class RtcAgent {

 public:
  RtcAgent(std::string device_code, std::string device_key) {
   device_code_ = device_code;
   device_key_ = device_key;
  }

  ~RtcAgent() {}
  void Start();
  int InitPeerConnection();
  int Connect();
  void Disconnect();
  static int OnMessage(void *context, char *topic, int len, MQTTClient_message *message);
  static void OnTransportReady(void *context);
  static void OnIcecandidate(char *sdp, void *context);
  static void* SendVideoThread(void *context);

 private:
  peer_connection_t peer_connection_;
  std::string device_code_;
  std::string device_key_;
  std::string ice_candidate_;
  MQTTClient client_;
  MQTTClient_connectOptions conn_opts_ = MQTTClient_connectOptions_initializer;
  MQTTClient_SSLOptions ssl_opts_ = MQTTClient_SSLOptions_initializer;
  void SendAnswer();
  pthread_t media_thread_id_;
};

#endif // RTC_RTC_AGENT_H_
