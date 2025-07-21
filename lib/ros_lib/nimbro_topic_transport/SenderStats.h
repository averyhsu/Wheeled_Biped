#ifndef _ROS_nimbro_topic_transport_SenderStats_h
#define _ROS_nimbro_topic_transport_SenderStats_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "nimbro_topic_transport/TopicBandwidth.h"

namespace nimbro_topic_transport
{

  class SenderStats : public ros::Msg
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
      typedef const char* _destination_type;
      _destination_type destination;
      typedef uint16_t _destination_port_type;
      _destination_port_type destination_port;
      typedef uint16_t _source_port_type;
      _source_port_type source_port;
      typedef bool _fec_type;
      _fec_type fec;
      typedef float _bandwidth_type;
      _bandwidth_type bandwidth;
      uint32_t topics_length;
      typedef nimbro_topic_transport::TopicBandwidth _topics_type;
      _topics_type st_topics;
      _topics_type * topics;

    SenderStats():
      header(),
      node(""),
      protocol(""),
      label(""),
      host(""),
      destination(""),
      destination_port(0),
      source_port(0),
      fec(0),
      bandwidth(0),
      topics_length(0), st_topics(), topics(nullptr)
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
      uint32_t length_destination = strlen(this->destination);
      varToArr(outbuffer + offset, length_destination);
      offset += 4;
      memcpy(outbuffer + offset, this->destination, length_destination);
      offset += length_destination;
      *(outbuffer + offset + 0) = (this->destination_port >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->destination_port >> (8 * 1)) & 0xFF;
      offset += sizeof(this->destination_port);
      *(outbuffer + offset + 0) = (this->source_port >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->source_port >> (8 * 1)) & 0xFF;
      offset += sizeof(this->source_port);
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
      *(outbuffer + offset + 0) = (this->topics_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->topics_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->topics_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->topics_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->topics_length);
      for( uint32_t i = 0; i < topics_length; i++){
      offset += this->topics[i].serialize(outbuffer + offset);
      }
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
      uint32_t length_destination;
      arrToVar(length_destination, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_destination; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_destination-1]=0;
      this->destination = (char *)(inbuffer + offset-1);
      offset += length_destination;
      this->destination_port =  ((uint16_t) (*(inbuffer + offset)));
      this->destination_port |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->destination_port);
      this->source_port =  ((uint16_t) (*(inbuffer + offset)));
      this->source_port |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->source_port);
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
      uint32_t topics_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      topics_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      topics_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      topics_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->topics_length);
      if(topics_lengthT > topics_length)
        this->topics = (nimbro_topic_transport::TopicBandwidth*)realloc(this->topics, topics_lengthT * sizeof(nimbro_topic_transport::TopicBandwidth));
      topics_length = topics_lengthT;
      for( uint32_t i = 0; i < topics_length; i++){
      offset += this->st_topics.deserialize(inbuffer + offset);
        memcpy( &(this->topics[i]), &(this->st_topics), sizeof(nimbro_topic_transport::TopicBandwidth));
      }
     return offset;
    }

    virtual const char * getType() override { return "nimbro_topic_transport/SenderStats"; };
    virtual const char * getMD5() override { return "785e5b5b423320e1379bc0c4ba6dbaa3"; };

  };

}
#endif
