/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef rpc_H
#define rpc_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "tutorial_types.h"

namespace tutorial {

#ifdef _WIN32
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class rpcIf {
 public:
  virtual ~rpcIf() {}

  /**
   * A method definition looks like C code. It has a return type, arguments,
   * and optionally a list of exceptions that it may throw. Note that argument
   * lists and exception lists are specified using the exact same syntax as
   * field lists in struct or exception definitions.
   * 
   * @param url
   */
  virtual void get_data(std::string& _return, const std::string& url) = 0;
  virtual void print_statistics(Stats& _return) = 0;
};

class rpcIfFactory {
 public:
  typedef rpcIf Handler;

  virtual ~rpcIfFactory() {}

  virtual rpcIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(rpcIf* /* handler */) = 0;
};

class rpcIfSingletonFactory : virtual public rpcIfFactory {
 public:
  rpcIfSingletonFactory(const boost::shared_ptr<rpcIf>& iface) : iface_(iface) {}
  virtual ~rpcIfSingletonFactory() {}

  virtual rpcIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(rpcIf* /* handler */) {}

 protected:
  boost::shared_ptr<rpcIf> iface_;
};

class rpcNull : virtual public rpcIf {
 public:
  virtual ~rpcNull() {}
  void get_data(std::string& /* _return */, const std::string& /* url */) {
    return;
  }
  void print_statistics(Stats& /* _return */) {
    return;
  }
};

typedef struct _rpc_get_data_args__isset {
  _rpc_get_data_args__isset() : url(false) {}
  bool url :1;
} _rpc_get_data_args__isset;

class rpc_get_data_args {
 public:

  rpc_get_data_args(const rpc_get_data_args&);
  rpc_get_data_args& operator=(const rpc_get_data_args&);
  rpc_get_data_args() : url() {
  }

  virtual ~rpc_get_data_args() throw();
  std::string url;

  _rpc_get_data_args__isset __isset;

  void __set_url(const std::string& val);

  bool operator == (const rpc_get_data_args & rhs) const
  {
    if (!(url == rhs.url))
      return false;
    return true;
  }
  bool operator != (const rpc_get_data_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const rpc_get_data_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class rpc_get_data_pargs {
 public:


  virtual ~rpc_get_data_pargs() throw();
  const std::string* url;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _rpc_get_data_result__isset {
  _rpc_get_data_result__isset() : success(false) {}
  bool success :1;
} _rpc_get_data_result__isset;

class rpc_get_data_result {
 public:

  rpc_get_data_result(const rpc_get_data_result&);
  rpc_get_data_result& operator=(const rpc_get_data_result&);
  rpc_get_data_result() : success() {
  }

  virtual ~rpc_get_data_result() throw();
  std::string success;

  _rpc_get_data_result__isset __isset;

  void __set_success(const std::string& val);

  bool operator == (const rpc_get_data_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const rpc_get_data_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const rpc_get_data_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _rpc_get_data_presult__isset {
  _rpc_get_data_presult__isset() : success(false) {}
  bool success :1;
} _rpc_get_data_presult__isset;

class rpc_get_data_presult {
 public:


  virtual ~rpc_get_data_presult() throw();
  std::string* success;

  _rpc_get_data_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class rpc_print_statistics_args {
 public:

  rpc_print_statistics_args(const rpc_print_statistics_args&);
  rpc_print_statistics_args& operator=(const rpc_print_statistics_args&);
  rpc_print_statistics_args() {
  }

  virtual ~rpc_print_statistics_args() throw();

  bool operator == (const rpc_print_statistics_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const rpc_print_statistics_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const rpc_print_statistics_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class rpc_print_statistics_pargs {
 public:


  virtual ~rpc_print_statistics_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _rpc_print_statistics_result__isset {
  _rpc_print_statistics_result__isset() : success(false) {}
  bool success :1;
} _rpc_print_statistics_result__isset;

class rpc_print_statistics_result {
 public:

  rpc_print_statistics_result(const rpc_print_statistics_result&);
  rpc_print_statistics_result& operator=(const rpc_print_statistics_result&);
  rpc_print_statistics_result() {
  }

  virtual ~rpc_print_statistics_result() throw();
  Stats success;

  _rpc_print_statistics_result__isset __isset;

  void __set_success(const Stats& val);

  bool operator == (const rpc_print_statistics_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const rpc_print_statistics_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const rpc_print_statistics_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _rpc_print_statistics_presult__isset {
  _rpc_print_statistics_presult__isset() : success(false) {}
  bool success :1;
} _rpc_print_statistics_presult__isset;

class rpc_print_statistics_presult {
 public:


  virtual ~rpc_print_statistics_presult() throw();
  Stats* success;

  _rpc_print_statistics_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class rpcClient : virtual public rpcIf {
 public:
  rpcClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  rpcClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void get_data(std::string& _return, const std::string& url);
  void send_get_data(const std::string& url);
  void recv_get_data(std::string& _return);
  void print_statistics(Stats& _return);
  void send_print_statistics();
  void recv_print_statistics(Stats& _return);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class rpcProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<rpcIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (rpcProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_get_data(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_print_statistics(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  rpcProcessor(boost::shared_ptr<rpcIf> iface) :
    iface_(iface) {
    processMap_["get_data"] = &rpcProcessor::process_get_data;
    processMap_["print_statistics"] = &rpcProcessor::process_print_statistics;
  }

  virtual ~rpcProcessor() {}
};

class rpcProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  rpcProcessorFactory(const ::boost::shared_ptr< rpcIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< rpcIfFactory > handlerFactory_;
};

class rpcMultiface : virtual public rpcIf {
 public:
  rpcMultiface(std::vector<boost::shared_ptr<rpcIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~rpcMultiface() {}
 protected:
  std::vector<boost::shared_ptr<rpcIf> > ifaces_;
  rpcMultiface() {}
  void add(boost::shared_ptr<rpcIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void get_data(std::string& _return, const std::string& url) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->get_data(_return, url);
    }
    ifaces_[i]->get_data(_return, url);
    return;
  }

  void print_statistics(Stats& _return) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->print_statistics(_return);
    }
    ifaces_[i]->print_statistics(_return);
    return;
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class rpcConcurrentClient : virtual public rpcIf {
 public:
  rpcConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  rpcConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void get_data(std::string& _return, const std::string& url);
  int32_t send_get_data(const std::string& url);
  void recv_get_data(std::string& _return, const int32_t seqid);
  void print_statistics(Stats& _return);
  int32_t send_print_statistics();
  void recv_print_statistics(Stats& _return, const int32_t seqid);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _WIN32
  #pragma warning( pop )
#endif

} // namespace

#endif
