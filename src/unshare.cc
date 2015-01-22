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

  int mask = args[0]->ToInt32()->Value();

  int unshareNum = unshare(mask);

  bool unshareAction = (unshareNum == 0) ? true : false;

  v8::Local<v8::Value> unshared = v8::Local<v8::Value>::New(v8::Boolean::New(unshareAction));

  return scope.Close(unshared);
}

#define EXPORT_CONST(__NAME__) exports->Set(v8::String::NewSymbol(#__NAME__), v8::Int32::New(__NAME__), v8::ReadOnly)

void init (v8::Handle<v8::Object> exports, v8::Handle<v8::Object> module) {
  exports->Set(v8::String::NewSymbol("unshare"), v8::FunctionTemplate::New(Unshare)->GetFunction());

  EXPORT_CONST(CLONE_NEWNS);
  EXPORT_CONST(CLONE_NEWIPC);
  EXPORT_CONST(CLONE_NEWNET);
  EXPORT_CONST(CLONE_NEWUTS);
  EXPORT_CONST(CLONE_SYSVSEM);

  EXPORT_CONST(CLONE_FS);
  EXPORT_CONST(CLONE_FILES);
}
NODE_MODULE(unshare, init)
