// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: TollMessage.proto

#ifndef PROTOBUF_TollMessage_2eproto__INCLUDED
#define PROTOBUF_TollMessage_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_TollMessage_2eproto();
void protobuf_AssignDesc_TollMessage_2eproto();
void protobuf_ShutdownFile_TollMessage_2eproto();

class TollMessage;

// ===================================================================

class TollMessage : public ::google::protobuf::Message {
 public:
  TollMessage();
  virtual ~TollMessage();

  TollMessage(const TollMessage& from);

  inline TollMessage& operator=(const TollMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const TollMessage& default_instance();

  void Swap(TollMessage* other);

  // implements Message ----------------------------------------------

  TollMessage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TollMessage& from);
  void MergeFrom(const TollMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 laneid = 1;
  inline bool has_laneid() const;
  inline void clear_laneid();
  static const int kLaneidFieldNumber = 1;
  inline ::google::protobuf::int32 laneid() const;
  inline void set_laneid(::google::protobuf::int32 value);

  // required uint32 price = 2;
  inline bool has_price() const;
  inline void clear_price();
  static const int kPriceFieldNumber = 2;
  inline ::google::protobuf::uint32 price() const;
  inline void set_price(::google::protobuf::uint32 value);

  // required bytes timestamp = 3;
  inline bool has_timestamp() const;
  inline void clear_timestamp();
  static const int kTimestampFieldNumber = 3;
  inline const ::std::string& timestamp() const;
  inline void set_timestamp(const ::std::string& value);
  inline void set_timestamp(const char* value);
  inline void set_timestamp(const void* value, size_t size);
  inline ::std::string* mutable_timestamp();
  inline ::std::string* release_timestamp();
  inline void set_allocated_timestamp(::std::string* timestamp);

  // required bytes staffname = 4;
  inline bool has_staffname() const;
  inline void clear_staffname();
  static const int kStaffnameFieldNumber = 4;
  inline const ::std::string& staffname() const;
  inline void set_staffname(const ::std::string& value);
  inline void set_staffname(const char* value);
  inline void set_staffname(const void* value, size_t size);
  inline ::std::string* mutable_staffname();
  inline ::std::string* release_staffname();
  inline void set_allocated_staffname(::std::string* staffname);

  // required bytes platenumber = 5;
  inline bool has_platenumber() const;
  inline void clear_platenumber();
  static const int kPlatenumberFieldNumber = 5;
  inline const ::std::string& platenumber() const;
  inline void set_platenumber(const ::std::string& value);
  inline void set_platenumber(const char* value);
  inline void set_platenumber(const void* value, size_t size);
  inline ::std::string* mutable_platenumber();
  inline ::std::string* release_platenumber();
  inline void set_allocated_platenumber(::std::string* platenumber);

  // required bytes vehicleclass = 6;
  inline bool has_vehicleclass() const;
  inline void clear_vehicleclass();
  static const int kVehicleclassFieldNumber = 6;
  inline const ::std::string& vehicleclass() const;
  inline void set_vehicleclass(const ::std::string& value);
  inline void set_vehicleclass(const char* value);
  inline void set_vehicleclass(const void* value, size_t size);
  inline ::std::string* mutable_vehicleclass();
  inline ::std::string* release_vehicleclass();
  inline void set_allocated_vehicleclass(::std::string* vehicleclass);

  // required bytes cameralaneip = 7;
  inline bool has_cameralaneip() const;
  inline void clear_cameralaneip();
  static const int kCameralaneipFieldNumber = 7;
  inline const ::std::string& cameralaneip() const;
  inline void set_cameralaneip(const ::std::string& value);
  inline void set_cameralaneip(const char* value);
  inline void set_cameralaneip(const void* value, size_t size);
  inline ::std::string* mutable_cameralaneip();
  inline ::std::string* release_cameralaneip();
  inline void set_allocated_cameralaneip(::std::string* cameralaneip);

  // @@protoc_insertion_point(class_scope:TollMessage)
 private:
  inline void set_has_laneid();
  inline void clear_has_laneid();
  inline void set_has_price();
  inline void clear_has_price();
  inline void set_has_timestamp();
  inline void clear_has_timestamp();
  inline void set_has_staffname();
  inline void clear_has_staffname();
  inline void set_has_platenumber();
  inline void clear_has_platenumber();
  inline void set_has_vehicleclass();
  inline void clear_has_vehicleclass();
  inline void set_has_cameralaneip();
  inline void clear_has_cameralaneip();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 laneid_;
  ::google::protobuf::uint32 price_;
  ::std::string* timestamp_;
  ::std::string* staffname_;
  ::std::string* platenumber_;
  ::std::string* vehicleclass_;
  ::std::string* cameralaneip_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(7 + 31) / 32];

  friend void  protobuf_AddDesc_TollMessage_2eproto();
  friend void protobuf_AssignDesc_TollMessage_2eproto();
  friend void protobuf_ShutdownFile_TollMessage_2eproto();

  void InitAsDefaultInstance();
  static TollMessage* default_instance_;
};
// ===================================================================


// ===================================================================

// TollMessage

// required int32 laneid = 1;
inline bool TollMessage::has_laneid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TollMessage::set_has_laneid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TollMessage::clear_has_laneid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TollMessage::clear_laneid() {
  laneid_ = 0;
  clear_has_laneid();
}
inline ::google::protobuf::int32 TollMessage::laneid() const {
  return laneid_;
}
inline void TollMessage::set_laneid(::google::protobuf::int32 value) {
  set_has_laneid();
  laneid_ = value;
}

// required uint32 price = 2;
inline bool TollMessage::has_price() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TollMessage::set_has_price() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TollMessage::clear_has_price() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TollMessage::clear_price() {
  price_ = 0u;
  clear_has_price();
}
inline ::google::protobuf::uint32 TollMessage::price() const {
  return price_;
}
inline void TollMessage::set_price(::google::protobuf::uint32 value) {
  set_has_price();
  price_ = value;
}

// required bytes timestamp = 3;
inline bool TollMessage::has_timestamp() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void TollMessage::set_has_timestamp() {
  _has_bits_[0] |= 0x00000004u;
}
inline void TollMessage::clear_has_timestamp() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void TollMessage::clear_timestamp() {
  if (timestamp_ != &::google::protobuf::internal::kEmptyString) {
    timestamp_->clear();
  }
  clear_has_timestamp();
}
inline const ::std::string& TollMessage::timestamp() const {
  return *timestamp_;
}
inline void TollMessage::set_timestamp(const ::std::string& value) {
  set_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    timestamp_ = new ::std::string;
  }
  timestamp_->assign(value);
}
inline void TollMessage::set_timestamp(const char* value) {
  set_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    timestamp_ = new ::std::string;
  }
  timestamp_->assign(value);
}
inline void TollMessage::set_timestamp(const void* value, size_t size) {
  set_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    timestamp_ = new ::std::string;
  }
  timestamp_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TollMessage::mutable_timestamp() {
  set_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    timestamp_ = new ::std::string;
  }
  return timestamp_;
}
inline ::std::string* TollMessage::release_timestamp() {
  clear_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = timestamp_;
    timestamp_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void TollMessage::set_allocated_timestamp(::std::string* timestamp) {
  if (timestamp_ != &::google::protobuf::internal::kEmptyString) {
    delete timestamp_;
  }
  if (timestamp) {
    set_has_timestamp();
    timestamp_ = timestamp;
  } else {
    clear_has_timestamp();
    timestamp_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required bytes staffname = 4;
inline bool TollMessage::has_staffname() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void TollMessage::set_has_staffname() {
  _has_bits_[0] |= 0x00000008u;
}
inline void TollMessage::clear_has_staffname() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void TollMessage::clear_staffname() {
  if (staffname_ != &::google::protobuf::internal::kEmptyString) {
    staffname_->clear();
  }
  clear_has_staffname();
}
inline const ::std::string& TollMessage::staffname() const {
  return *staffname_;
}
inline void TollMessage::set_staffname(const ::std::string& value) {
  set_has_staffname();
  if (staffname_ == &::google::protobuf::internal::kEmptyString) {
    staffname_ = new ::std::string;
  }
  staffname_->assign(value);
}
inline void TollMessage::set_staffname(const char* value) {
  set_has_staffname();
  if (staffname_ == &::google::protobuf::internal::kEmptyString) {
    staffname_ = new ::std::string;
  }
  staffname_->assign(value);
}
inline void TollMessage::set_staffname(const void* value, size_t size) {
  set_has_staffname();
  if (staffname_ == &::google::protobuf::internal::kEmptyString) {
    staffname_ = new ::std::string;
  }
  staffname_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TollMessage::mutable_staffname() {
  set_has_staffname();
  if (staffname_ == &::google::protobuf::internal::kEmptyString) {
    staffname_ = new ::std::string;
  }
  return staffname_;
}
inline ::std::string* TollMessage::release_staffname() {
  clear_has_staffname();
  if (staffname_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = staffname_;
    staffname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void TollMessage::set_allocated_staffname(::std::string* staffname) {
  if (staffname_ != &::google::protobuf::internal::kEmptyString) {
    delete staffname_;
  }
  if (staffname) {
    set_has_staffname();
    staffname_ = staffname;
  } else {
    clear_has_staffname();
    staffname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required bytes platenumber = 5;
inline bool TollMessage::has_platenumber() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void TollMessage::set_has_platenumber() {
  _has_bits_[0] |= 0x00000010u;
}
inline void TollMessage::clear_has_platenumber() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void TollMessage::clear_platenumber() {
  if (platenumber_ != &::google::protobuf::internal::kEmptyString) {
    platenumber_->clear();
  }
  clear_has_platenumber();
}
inline const ::std::string& TollMessage::platenumber() const {
  return *platenumber_;
}
inline void TollMessage::set_platenumber(const ::std::string& value) {
  set_has_platenumber();
  if (platenumber_ == &::google::protobuf::internal::kEmptyString) {
    platenumber_ = new ::std::string;
  }
  platenumber_->assign(value);
}
inline void TollMessage::set_platenumber(const char* value) {
  set_has_platenumber();
  if (platenumber_ == &::google::protobuf::internal::kEmptyString) {
    platenumber_ = new ::std::string;
  }
  platenumber_->assign(value);
}
inline void TollMessage::set_platenumber(const void* value, size_t size) {
  set_has_platenumber();
  if (platenumber_ == &::google::protobuf::internal::kEmptyString) {
    platenumber_ = new ::std::string;
  }
  platenumber_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TollMessage::mutable_platenumber() {
  set_has_platenumber();
  if (platenumber_ == &::google::protobuf::internal::kEmptyString) {
    platenumber_ = new ::std::string;
  }
  return platenumber_;
}
inline ::std::string* TollMessage::release_platenumber() {
  clear_has_platenumber();
  if (platenumber_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = platenumber_;
    platenumber_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void TollMessage::set_allocated_platenumber(::std::string* platenumber) {
  if (platenumber_ != &::google::protobuf::internal::kEmptyString) {
    delete platenumber_;
  }
  if (platenumber) {
    set_has_platenumber();
    platenumber_ = platenumber;
  } else {
    clear_has_platenumber();
    platenumber_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required bytes vehicleclass = 6;
inline bool TollMessage::has_vehicleclass() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void TollMessage::set_has_vehicleclass() {
  _has_bits_[0] |= 0x00000020u;
}
inline void TollMessage::clear_has_vehicleclass() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void TollMessage::clear_vehicleclass() {
  if (vehicleclass_ != &::google::protobuf::internal::kEmptyString) {
    vehicleclass_->clear();
  }
  clear_has_vehicleclass();
}
inline const ::std::string& TollMessage::vehicleclass() const {
  return *vehicleclass_;
}
inline void TollMessage::set_vehicleclass(const ::std::string& value) {
  set_has_vehicleclass();
  if (vehicleclass_ == &::google::protobuf::internal::kEmptyString) {
    vehicleclass_ = new ::std::string;
  }
  vehicleclass_->assign(value);
}
inline void TollMessage::set_vehicleclass(const char* value) {
  set_has_vehicleclass();
  if (vehicleclass_ == &::google::protobuf::internal::kEmptyString) {
    vehicleclass_ = new ::std::string;
  }
  vehicleclass_->assign(value);
}
inline void TollMessage::set_vehicleclass(const void* value, size_t size) {
  set_has_vehicleclass();
  if (vehicleclass_ == &::google::protobuf::internal::kEmptyString) {
    vehicleclass_ = new ::std::string;
  }
  vehicleclass_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TollMessage::mutable_vehicleclass() {
  set_has_vehicleclass();
  if (vehicleclass_ == &::google::protobuf::internal::kEmptyString) {
    vehicleclass_ = new ::std::string;
  }
  return vehicleclass_;
}
inline ::std::string* TollMessage::release_vehicleclass() {
  clear_has_vehicleclass();
  if (vehicleclass_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = vehicleclass_;
    vehicleclass_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void TollMessage::set_allocated_vehicleclass(::std::string* vehicleclass) {
  if (vehicleclass_ != &::google::protobuf::internal::kEmptyString) {
    delete vehicleclass_;
  }
  if (vehicleclass) {
    set_has_vehicleclass();
    vehicleclass_ = vehicleclass;
  } else {
    clear_has_vehicleclass();
    vehicleclass_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required bytes cameralaneip = 7;
inline bool TollMessage::has_cameralaneip() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void TollMessage::set_has_cameralaneip() {
  _has_bits_[0] |= 0x00000040u;
}
inline void TollMessage::clear_has_cameralaneip() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void TollMessage::clear_cameralaneip() {
  if (cameralaneip_ != &::google::protobuf::internal::kEmptyString) {
    cameralaneip_->clear();
  }
  clear_has_cameralaneip();
}
inline const ::std::string& TollMessage::cameralaneip() const {
  return *cameralaneip_;
}
inline void TollMessage::set_cameralaneip(const ::std::string& value) {
  set_has_cameralaneip();
  if (cameralaneip_ == &::google::protobuf::internal::kEmptyString) {
    cameralaneip_ = new ::std::string;
  }
  cameralaneip_->assign(value);
}
inline void TollMessage::set_cameralaneip(const char* value) {
  set_has_cameralaneip();
  if (cameralaneip_ == &::google::protobuf::internal::kEmptyString) {
    cameralaneip_ = new ::std::string;
  }
  cameralaneip_->assign(value);
}
inline void TollMessage::set_cameralaneip(const void* value, size_t size) {
  set_has_cameralaneip();
  if (cameralaneip_ == &::google::protobuf::internal::kEmptyString) {
    cameralaneip_ = new ::std::string;
  }
  cameralaneip_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* TollMessage::mutable_cameralaneip() {
  set_has_cameralaneip();
  if (cameralaneip_ == &::google::protobuf::internal::kEmptyString) {
    cameralaneip_ = new ::std::string;
  }
  return cameralaneip_;
}
inline ::std::string* TollMessage::release_cameralaneip() {
  clear_has_cameralaneip();
  if (cameralaneip_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = cameralaneip_;
    cameralaneip_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void TollMessage::set_allocated_cameralaneip(::std::string* cameralaneip) {
  if (cameralaneip_ != &::google::protobuf::internal::kEmptyString) {
    delete cameralaneip_;
  }
  if (cameralaneip) {
    set_has_cameralaneip();
    cameralaneip_ = cameralaneip;
  } else {
    clear_has_cameralaneip();
    cameralaneip_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_TollMessage_2eproto__INCLUDED