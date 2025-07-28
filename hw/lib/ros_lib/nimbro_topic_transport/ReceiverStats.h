#ifndef _ROS_nimbro_topic_transport_ReceiverStats_h
#define _ROS_nimbro_topic_transport_ReceiverStats_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace nimbro_topic_transport
{

  class ReceiverStats : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef const char* _node_type;
      _node_type node;
      typedef const char* _protocol_type;
      _protocol_type protocol;
      typedef const char* _label_type;
      _label_type label;
      typedef const char* _host_type;
      _host_type host;
      typedef const char* _remote_type;
      _remote_type remote;
      typedef uint16_t _local_port_type;
      _local_port_type local_port;
      typedef uint16_t _remote_port_type;
      _remote_port_type remote_port;
      typedef bool _fec_type;
      _fec_type fec;
      typedef float _bandwidth_type;
      _bandwidth_type bandwidth;
      typedef float _drop_rate_type;
      _drop_rate_type drop_rate;

    ReceiverStats():
      header(),
      node(""),
      protocol(""),
      label(""),
      host(""),
      remote(""),
      local_port(0),
      remote_port(0),
      fec(0),
      bandwidth(0),
      drop_rate(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      uint32_t length_node = strlen(this->node);
      varToArr(outbuffer + offset, length_node);
      offset += 4;
      memcpy(outbuffer + offset, this->node, length_node);
      offset += length_node;
      uint32_t length_protocol = strlen(this->protocol);
      varToArr(outbuffer + offset, length_protocol);
      offset += 4;
      memcpy(outbuffer + offset, this->protocol, length_protocol);
      offset += length_protocol;
      uint32_t length_label = strlen(this->label);
      varToArr(outbuffer + offset, length_label);
      offset += 4;
      memcpy(outbuffer + offset, this->label, length_label);
      offset += length_label;
      uint32_t length_host = strlen(this->host);
      varToArr(outbuffer + offset, length_host);
      offset += 4;
      memcpy(outbuffer + offset, this->host, length_host);
      offset += length_host;
      uint32_t length_remote = strlen(this->remote);
      varToArr(outbuffer + offset, length_remote);
      offset += 4;
      memcpy(outbuffer + offset, this->remote, length_remote);
      offset += length_remote;
      *(outbuffer + offset + 0) = (this->local_port >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->local_port >> (8 * 1)) & 0xFF;
      offset += sizeof(this->local_port);
      *(outbuffer + offset + 0) = (this->remote_port >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->remote_port >> (8 * 1)) & 0xFF;
      offset += sizeof(this->remote_port);
      union {
        bool real;
        uint8_t base;
      } u_fec;
      u_fec.real = this->fec;
      *(outbuffer + offset + 0) = (u_fec.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->fec);
      union {
        float real;
        uint32_t base;
      } u_bandwidth;
      u_bandwidth.real = this->bandwidth;
      *(outbuffer + offset + 0) = (u_bandwidth.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_bandwidth.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_bandwidth.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_bandwidth.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->bandwidth);
      union {
        float real;
        uint32_t base;
      } u_drop_rate;
      u_drop_rate.real = this->drop_rate;
      *(outbuffer + offset + 0) = (u_drop_rate.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_drop_rate.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_drop_rate.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_drop_rate.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->drop_rate);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t length_node;
      arrToVar(length_node, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_node; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_node-1]=0;
      this->node = (char *)(inbuffer + offset-1);
      offset += length_node;
      uint32_t length_protocol;
      arrToVar(length_protocol, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_protocol; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_protocol-1]=0;
      this->protocol = (char *)(inbuffer + offset-1);
      offset += length_protocol;
      uint32_t length_label;
      arrToVar(length_label, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_label; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_label-1]=0;
      this->label = (char *)(inbuffer + offset-1);
      offset += length_label;
      uint32_t length_host;
      arrToVar(length_host, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_host; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_host-1]=0;
      this->host = (char *)(inbuffer + offset-1);
      offset += length_host;
      uint32_t length_remote;
      arrToVar(length_remote, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_remote; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_remote-1]=0;
      this->remote = (char *)(inbuffer + offset-1);
      offset += length_remote;
      this->local_port =  ((uint16_t) (*(inbuffer + offset)));
      this->local_port |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->local_port);
      this->remote_port =  ((uint16_t) (*(inbuffer + offset)));
      this->remote_port |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->remote_port);
      union {
        bool real;
        uint8_t base;
      } u_fec;
      u_fec.base = 0;
      u_fec.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->fec = u_fec.real;
      offset += sizeof(this->fec);
      union {
        float real;
        uint32_t base;
      } u_bandwidth;
      u_bandwidth.base = 0;
      u_bandwidth.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_bandwidth.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_bandwidth.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_bandwidth.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->bandwidth = u_bandwidth.real;
      offset += sizeof(this->bandwidth);
      union {
        float real;
        uint32_t base;
      } u_drop_rate;
      u_drop_rate.base = 0;
      u_drop_rate.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_drop_rate.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_drop_rate.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_drop_rate.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->drop_rate = u_drop_rate.real;
      offset += sizeof(this->drop_rate);
     return offset;
    }

    virtual const char * getType() override { return "nimbro_topic_transport/ReceiverStats"; };
    virtual const char * getMD5() override { return "c542f1d59c474dba7ffccf1c3fa1ceab"; };

  };

}
#endif
