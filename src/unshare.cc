#include <sched.h>
#include <node.h>
#include <errno.h>

namespace {

void Unshare(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();

  if (args.Length() != 1) {
    // TODO: make it raise a proper exception
    isolate->ThrowException(v8::Exception::TypeError(
        v8::String::NewFromUtf8(isolate, "`unshare` needs 1 parameter")));
    return;
  }

  int mask = args[0]->ToInt32(isolate)->Value();

  int unshareNum = unshare(mask);

  bool unshareAction = (unshareNum == 0) ? true : false;

  args.GetReturnValue().Set(v8::Boolean::New(isolate, unshareAction));
}

void init (v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "unshare", Unshare);

  NODE_DEFINE_CONSTANT(exports, CLONE_NEWNS);
  NODE_DEFINE_CONSTANT(exports, CLONE_NEWIPC);
  NODE_DEFINE_CONSTANT(exports, CLONE_NEWNET);
  NODE_DEFINE_CONSTANT(exports, CLONE_NEWUTS);
  NODE_DEFINE_CONSTANT(exports, CLONE_SYSVSEM);

  NODE_DEFINE_CONSTANT(exports, CLONE_FS);
  NODE_DEFINE_CONSTANT(exports, CLONE_FILES);
}
NODE_MODULE(unshare, init)

}
