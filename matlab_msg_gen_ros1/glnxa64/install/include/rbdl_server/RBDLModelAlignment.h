// Generated by gencpp from file rbdl_server/RBDLModelAlignment.msg
// DO NOT EDIT!


#ifndef RBDL_SERVER_MESSAGE_RBDLMODELALIGNMENT_H
#define RBDL_SERVER_MESSAGE_RBDLMODELALIGNMENT_H

#include <ros/service_traits.h>


#include <rbdl_server/RBDLModelAlignmentRequest.h>
#include <rbdl_server/RBDLModelAlignmentResponse.h>


namespace rbdl_server
{

struct RBDLModelAlignment
{

typedef RBDLModelAlignmentRequest Request;
typedef RBDLModelAlignmentResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct RBDLModelAlignment
} // namespace rbdl_server


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::rbdl_server::RBDLModelAlignment > {
  static const char* value()
  {
    return "512094f17d3a6df4fdba917d89ebe481";
  }

  static const char* value(const ::rbdl_server::RBDLModelAlignment&) { return value(); }
};

template<>
struct DataType< ::rbdl_server::RBDLModelAlignment > {
  static const char* value()
  {
    return "rbdl_server/RBDLModelAlignment";
  }

  static const char* value(const ::rbdl_server::RBDLModelAlignment&) { return value(); }
};


// service_traits::MD5Sum< ::rbdl_server::RBDLModelAlignmentRequest> should match 
// service_traits::MD5Sum< ::rbdl_server::RBDLModelAlignment > 
template<>
struct MD5Sum< ::rbdl_server::RBDLModelAlignmentRequest>
{
  static const char* value()
  {
    return MD5Sum< ::rbdl_server::RBDLModelAlignment >::value();
  }
  static const char* value(const ::rbdl_server::RBDLModelAlignmentRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::rbdl_server::RBDLModelAlignmentRequest> should match 
// service_traits::DataType< ::rbdl_server::RBDLModelAlignment > 
template<>
struct DataType< ::rbdl_server::RBDLModelAlignmentRequest>
{
  static const char* value()
  {
    return DataType< ::rbdl_server::RBDLModelAlignment >::value();
  }
  static const char* value(const ::rbdl_server::RBDLModelAlignmentRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::rbdl_server::RBDLModelAlignmentResponse> should match 
// service_traits::MD5Sum< ::rbdl_server::RBDLModelAlignment > 
template<>
struct MD5Sum< ::rbdl_server::RBDLModelAlignmentResponse>
{
  static const char* value()
  {
    return MD5Sum< ::rbdl_server::RBDLModelAlignment >::value();
  }
  static const char* value(const ::rbdl_server::RBDLModelAlignmentResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::rbdl_server::RBDLModelAlignmentResponse> should match 
// service_traits::DataType< ::rbdl_server::RBDLModelAlignment > 
template<>
struct DataType< ::rbdl_server::RBDLModelAlignmentResponse>
{
  static const char* value()
  {
    return DataType< ::rbdl_server::RBDLModelAlignment >::value();
  }
  static const char* value(const ::rbdl_server::RBDLModelAlignmentResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // RBDL_SERVER_MESSAGE_RBDLMODELALIGNMENT_H
