#include <sched.h>
#include <v8.h>
#include <node.h>
#include <errno.h>

v8::Handle<v8::Value> Unshare(const v8::Arguments &args) {
  v8::HandleScope scope;

  if (args.Length() != 1) {
    // TODO: make it raise a proper exception
    return v8::ThrowException(v8::String::New("`unshare` needs 1 parameter"));
  }
  
  v8::Handle<v8::Array> options = v8::Handle<v8::Array>::Cast(args[0]);
  
  int mask = 0;
  for (unsigned int i = 0; i < options->Length(); i++) {
    v8::Local<v8::String> opt = v8::Local<v8::String>::Cast(options->Get(i));
    if(opt == v8::String::New("newns")) {
      mask |= CLONE_NEWNS;
    } else if(opt == v8::String::New("newnet")) {
      mask |= CLONE_NEWNET;
    } else if(opt == v8::String::New("newuts")) {
      mask |= CLONE_NEWUTS;
    } else if(opt == v8::String::New("newipc")) {
	  mask |= CLONE_NEWIPC;
	} else if(opt == v8::String::New("fs")) {
	  mask |= CLONE_FS;
	} else if(opt == v8::String::New("files")) {
	  mask |= CLONE_FILES;
	} else if(opt == v8::String::New("sysvsem")) {
	  mask |= CLONE_SYSVSEM;
	}
  }
  
  return v8::Local<v8::Value>::New(v8::Boolean::New(unshare(mask) == 0));
}

void init (v8::Handle<v8::Object> exports, v8::Handle<v8::Object> module) {
  exports->Set(v8::String::NewSymbol("unshare"), v8::FunctionTemplate::New(Unshare)->GetFunction());
}
NODE_MODULE(mount, init)
