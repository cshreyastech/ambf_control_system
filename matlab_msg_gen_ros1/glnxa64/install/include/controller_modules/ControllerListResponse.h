// Generated by gencpp from file controller_modules/ControllerListResponse.msg
// DO NOT EDIT!


#ifndef CONTROLLER_MODULES_MESSAGE_CONTROLLERLISTRESPONSE_H
#define CONTROLLER_MODULES_MESSAGE_CONTROLLERLISTRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace controller_modules
{
template <class ContainerAllocator>
struct ControllerListResponse_
{
  typedef ControllerListResponse_<ContainerAllocator> Type;

  ControllerListResponse_()
    : controllers()  {
    }
  ControllerListResponse_(const ContainerAllocator& _alloc)
    : controllers(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , typename ContainerAllocator::template rebind<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::other >  _controllers_type;
  _controllers_type controllers;





  typedef boost::shared_ptr< ::controller_modules::ControllerListResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::controller_modules::ControllerListResponse_<ContainerAllocator> const> ConstPtr;

}; // struct ControllerListResponse_

typedef ::controller_modules::ControllerListResponse_<std::allocator<void> > ControllerListResponse;

typedef boost::shared_ptr< ::controller_modules::ControllerListResponse > ControllerListResponsePtr;
typedef boost::shared_ptr< ::controller_modules::ControllerListResponse const> ControllerListResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::controller_modules::ControllerListResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::controller_modules::ControllerListResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace controller_modules

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'geometry_msgs': ['/usr/local/MATLAB/R2021a/sys/ros1/glnxa64/ros1/share/geometry_msgs/cmake/../msg'], 'trajectory_msgs': ['/usr/local/MATLAB/R2021a/sys/ros1/glnxa64/ros1/share/trajectory_msgs/cmake/../msg'], 'std_msgs': ['/usr/local/MATLAB/R2021a/sys/ros1/glnxa64/ros1/share/std_msgs/cmake/../msg', '/usr/local/MATLAB/R2021a/sys/ros1/glnxa64/ros1/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::controller_modules::ControllerListResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::controller_modules::ControllerListResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::controller_modules::ControllerListResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::controller_modules::ControllerListResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::controller_modules::ControllerListResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::controller_modules::ControllerListResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::controller_modules::ControllerListResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "8242783a458107f102bce0800c333f0a";
  }

  static const char* value(const ::controller_modules::ControllerListResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x8242783a458107f1ULL;
  static const uint64_t static_value2 = 0x02bce0800c333f0aULL;
};

template<class ContainerAllocator>
struct DataType< ::controller_modules::ControllerListResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "controller_modules/ControllerListResponse";
  }

  static const char* value(const ::controller_modules::ControllerListResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::controller_modules::ControllerListResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string[] controllers\n"
;
  }

  static const char* value(const ::controller_modules::ControllerListResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::controller_modules::ControllerListResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.controllers);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ControllerListResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::controller_modules::ControllerListResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::controller_modules::ControllerListResponse_<ContainerAllocator>& v)
  {
    s << indent << "controllers[]" << std::endl;
    for (size_t i = 0; i < v.controllers.size(); ++i)
    {
      s << indent << "  controllers[" << i << "]: ";
      Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.controllers[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // CONTROLLER_MODULES_MESSAGE_CONTROLLERLISTRESPONSE_H
